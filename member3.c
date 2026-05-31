#include <stdio.h>
#include <string.h>
#include "common.h"

void logNewTicket(MaintenanceTicket arr[], int *count) {
    if (*count >= MAX_TICKETS) {
        printf("[!] Maintenance logging capacity maxed out.\n");
        return;
    }
    arr[*count].ticketID = 3001 + *count;
    printf("Enter Broken Infrastructure Building Target Code: ");
    scanf("%9s", arr[*count].targetBuildingCode);
    printf("Provide Incident Hazard Description: ");
    clearBuffer();
    fgets(arr[*count].issueDescription, 100, stdin);
    arr[*count].issueDescription[strcspn(arr[*count].issueDescription, "\n")] = 0;

    printf("Set Critical Priority Level Rating Scale (1 Low - 5 Critical): ");
    scanf("%d", &arr[*count].priorityLevel);
    strcpy(arr[*count].status, "Pending");
    strcpy(arr[*count].assignedTechnician, "Unassigned");

    printf("[*] Ticket Created successfully! Generated ID: %d\n", arr[*count].ticketID);
    (*count)++;
}

void assignTechnician(MaintenanceTicket arr[], int count, int tID, UserAccount uArr[], int uCount) {
    int foundTicket = -1, foundTech = 0;
    char techName[50];
    for (int i = 0; i < count; i++) {
        if (arr[i].ticketID == tID) {
            foundTicket = i;
            break;
        }
    }
    if (foundTicket == -1) {
        printf("[!] No ticket verified with that ID.\n");
        return;
    }
    printf("\nAvailable Technicians in System Identity Registries:\n");
    for (int i = 0; i < uCount; i++) {
        if (strcmp(uArr[i].userRole, "Technician") == 0) {
            printf("- ID: %s (Clearance Level %d)\n", uArr[i].staffID, uArr[i].clearanceLevel);
            foundTech = 1;
        }
    }
    if (!foundTech) {
        printf("[-] No operational staff registered with technician taxonomy parameters.\n");
        return;
    }
    printf("Enter Name/ID of Technician to assign: ");
    clearBuffer();
    fgets(techName, 50, stdin);
    techName[strcspn(techName, "\n")] = 0;
    strcpy(arr[foundTicket].assignedTechnician, techName);
    strcpy(arr[foundTicket].status, "In Progress");
    printf("[*] Asset Dispatch Complete. Technician '%s' assigned to Ticket %d.\n", techName, tID);
}

void updateTicketStatus(MaintenanceTicket arr[], int count, int tID, char newStatus[], HardwareAsset hArr[], int hCount) {
    for (int i = 0; i < count; i++) {
        if (arr[i].ticketID == tID) {
            if (strcmp(newStatus, "Resolved") == 0) {
                for (int j = 0; j < hCount; j++) {
                    if (strstr(arr[i].issueDescription, hArr[j].assetID) != NULL) {
                        hArr[j].operationalStatus = 1;
                        printf("[INTEGRATION] Hardware Node tracking reference %s updated to operational status.\n", hArr[j].assetID);
                    }
                }
            }
            strcpy(arr[i].status, newStatus);
            printf("[*] Status validation verified updated to: %s\n", newStatus);
            return;
        }
    }
    printf("[!] Target ticket not uncovered.\n");
}

void displayTicketsByPriority(MaintenanceTicket arr[], int count, int targetPriority) {
    printf("\n--- ACTIVE SECURITY/TICKETS MATCHING CRITERIA: %d ---\n", targetPriority);
    for (int i = 0; i < count; i++) {
        if (arr[i].priorityLevel == targetPriority) {
            printf("ID: %d | Loc: %s | Issue: %s | Tech: %s | Status: %s\n",
                   arr[i].ticketID, arr[i].targetBuildingCode, arr[i].issueDescription,
                   arr[i].assignedTechnician, arr[i].status);
        }
    }
}

void generateOpenTicketsSummary(MaintenanceTicket arr[], int count) {
    int pendingCount = 0;
    printf("\n--- WORK ORDER SUMMARY AUDIT PROFILE ---\n");
    for (int i = 0; i < count; i++) {
        if (strcmp(arr[i].status, "Resolved") != 0) {
            pendingCount++;
            printf("[!] Ticket ID %d [%s Priority %d] - Status: %s\n",
                   arr[i].ticketID, arr[i].targetBuildingCode, arr[i].priorityLevel, arr[i].status);
        }
    }
    printf("Total Unresolved Backlog Count: %d active instances\n", pendingCount);
}

void member3Menu(MaintenanceTicket arr[], int *count, UserAccount uArr[], int uCount, HardwareAsset hArr[], int hCount) {
    int choice, ticketID, pLevel;
    char statusStr[15];
    do {
        printf("\n--- MODULE 3: INFRASTRUCTURE REPAIR MATRIX ---\n");
        printf("1. Issue Campus Facility Repair Log Request\n");
        printf("2. Dispatch Technician Personnel Asset\n");
        printf("3. Overwrite Active Ticket Status Structure\n");
        printf("4. Filter Tickets by Priority Severity\n");
        printf("5. Review Outstanding Open Backlog Metrics\n");
        printf("6. Return to Primary Core Executive Dashboard\n");
        printf("Select choice: ");
        if (scanf("%d", &choice) != 1) { clearBuffer(); continue; }

        switch (choice) {
            case 1: logNewTicket(arr, count); break;
            case 2:
                printf("Enter target tracking Ticket ID: ");
                scanf("%d", &ticketID);
                assignTechnician(arr, *count, ticketID, uArr, uCount);
                break;
            case 3:
                printf("Enter target tracking Ticket ID: ");
                scanf("%d", &ticketID);
                printf("Enter transition token target status (Pending/In Progress/Resolved): ");
                scanf("%14s", statusStr);
                updateTicketStatus(arr, *count, ticketID, statusStr, hArr, hCount);
                break;
            case 4:
                printf("Select priority scaling target query bounds (1-5): ");
                scanf("%d", &pLevel);
                displayTicketsByPriority(arr, *count, pLevel);
                break;
            case 5: generateOpenTicketsSummary(arr, *count); break;
        }
    } while (choice != 6);
}
