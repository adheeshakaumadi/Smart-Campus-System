#include <stdio.h>
#include <string.h>
#include "common.h"

void registerAsset(HardwareAsset arr[], int *count) {
    if (*count >= MAX_ASSETS) {
        printf("[!] IoT Registry tracking array buffer full.\n");
        return;
    }
    printf("Enter Device Serialization Unique Code: ");
    scanf("%14s", arr[*count].assetID);
    printf("Enter Hardware Module Type Description: ");
    clearBuffer();
    fgets(arr[*count].deviceType, 30, stdin);
    arr[*count].deviceType[strcspn(arr[*count].deviceType, "\n")] = 0;

    printf("Enter Deployment Date Day, Month, Year separated by spaces: ");
    scanf("%d %d %d", &arr[*count].installationDate.day, &arr[*count].installationDate.month, &arr[*count].installationDate.year);
    printf("Enter Mapped Smart Room Target Assignment Code: ");
    scanf("%d", &arr[*count].assignedRoomNumber);
    arr[*count].operationalStatus = 1;

    printf("[*] IoT Node deployment mapping registered locally using nested date structures.\n");
    (*count)++;
}

void locateAssetByID(HardwareAsset arr[], int count, char searchID[]) {
    for (int i = 0; i < count; i++) {
        if (strcmp(arr[i].assetID, searchID) == 0) {
            printf("[MATCH FOUND] Type: %s | Deployed: %02d-%02d-%04d | Target Room: %d | Health: %s\n",
                   arr[i].deviceType, arr[i].installationDate.day, arr[i].installationDate.month,
                   arr[i].installationDate.year, arr[i].assignedRoomNumber,
                   arr[i].operationalStatus == 1 ? "OPERATIONAL" : "FAULTY REPORTED");
            return;
        }
    }
    printf("[-] Asset lookup failed. Key token out of bounds.\n");
}

void reportFaultyAssets(HardwareAsset arr[], int count, MaintenanceTicket tArr[], int *tCount) {
    printf("\n--- ISOLATING NETWORK CRITICAL LOSS INSTANCES ---\n");
    int faultyDevices = 0;
    for (int i = 0; i < count; i++) {
        if (arr[i].operationalStatus == 0) {
            printf("[FAULT WARNING] Asset %s (%s) offline inside interior workspace context %d.\n",
                   arr[i].assetID, arr[i].deviceType, arr[i].assignedRoomNumber);

            int ticketExists = 0;
            for(int j = 0; j < *tCount; j++) {
                if(strstr(tArr[j].issueDescription, arr[i].assetID) != NULL) {
                    ticketExists = 1;
                    break;
                }
            }
            if(!ticketExists && *tCount < MAX_TICKETS) {
                tArr[*tCount].ticketID = 3001 + *tCount;
                strcpy(tArr[*tCount].targetBuildingCode, "UNKNOWN");
                sprintf(tArr[*tCount].issueDescription, "Hardware network node failure flag: %s", arr[i].assetID);
                strcpy(tArr[*tCount].assignedTechnician, "Unassigned");
                tArr[*tCount].priorityLevel = 4;
                strcpy(tArr[*tCount].status, "Pending");
                (*tCount)++;
                printf("[AUTOMATED WORK ORDER] Logged a maintenance tracking sheet for node %s.\n", arr[i].assetID);
            }
            faultyDevices++;
        }
    }
    if (faultyDevices == 0) printf("[*] Network diagnostic clean. All remote hardware processing normal.\n");
}

void transferAssetLocation(HardwareAsset arr[], int count, char aID[], int newRoom, SmartRoom rArr[], int rCount) {
    int roomValid = 0;
    for (int i = 0; i < rCount; i++) {
        if (rArr[i].roomNumber == newRoom) {
            roomValid = 1;
            break;
        }
    }
    if (!roomValid) {
        printf("[!] Core Topology Reject: Room %d does not exist in configuration tables.\n", newRoom);
        return;
    }
    for (int i = 0; i < count; i++) {
        if (strcmp(arr[i].assetID, aID) == 0) {
            arr[i].assignedRoomNumber = newRoom;
            printf("[*] Topology update complete. Asset %s relocated inside internal workspace %d.\n", aID, newRoom);
            return;
        }
    }
    printf("[!] No resource located matching asset descriptor token.\n");
}

void countAssetsByType(HardwareAsset arr[], int count, char type[]) {
    int accumulationMatches = 0;
    for (int i = 0; i < count; i++) {
        if (strstr(arr[i].deviceType, type) != NULL) {
            accumulationMatches++;
        }
    }
    printf("[*] Metric Query Analytics: Discovered %d device entities containing signature token '%s'\n", accumulationMatches, type);
}

void member4Menu(HardwareAsset arr[], int *count, SmartRoom rArr[], int rCount, MaintenanceTicket tArr[], int *tCount) {
    int choice, roomAllocation;
    char assetToken[15], typeFilter[30];
    do {
        printf("\n--- MODULE 4: EMBEDDED SMART HARDWARE REGISTRY ---\n");
        printf("1. Log Newly Dispatched Physical Smart Node\n");
        printf("2. Search Asset Attributes via Unique Serialization ID\n");
        printf("3. Trigger Hardware Self-Diagnostic Fault Scan\n");
        printf("4. Transfer Hardware Node Physical Room Allocation\n");
        printf("5. Count Hardware Sub-Assets via Taxonomy String\n");
        printf("6. Return to Primary Core Executive Dashboard\n");
        printf("Select choice: ");
        if (scanf("%d", &choice) != 1) { clearBuffer(); continue; }

        switch (choice) {
            case 1: registerAsset(arr, count); break;
            case 2:
                printf("Enter target validation asset ID string: ");
                scanf("%14s", assetToken);
                locateAssetByID(arr, *count, assetToken);
                break;
            case 3:
                if(*count > 0) {
                    arr[0].operationalStatus = 0;
                }
                reportFaultyAssets(arr, *count, tArr, tCount);
                break;
            case 4:
                printf("Enter Target Asset Identifier: ");
                scanf("%14s", assetToken);
                printf("Enter Target Room Number Destination: ");
                scanf("%d", &roomAllocation);
                transferAssetLocation(arr, *count, assetToken, roomAllocation, rArr, rCount);
                break;
            case 5:
                printf("Enter text pattern matching target key: ");
                clearBuffer();
                fgets(typeFilter, 30, stdin);
                typeFilter[strcspn(typeFilter, "\n")] = 0;
                countAssetsByType(arr, *count, typeFilter);
                break;
        }
    } while (choice != 6);
}
