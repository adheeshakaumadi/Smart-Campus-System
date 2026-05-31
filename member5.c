#include <stdio.h>
#include <string.h>
#include "common.h"

char activeUserRole[20] = "None";
int activeClearanceLevel = 0;

void clearBuffer() {
    while (getchar() != '\n');
}

void simpleEncrypt(char *pass) {
    for (int i = 0; pass[i] != '\0'; i++) {
        pass[i] = pass[i] ^ 42;
    }
}

void registerUser(UserAccount arr[], int *count) {
    if (*count >= MAX_USERS) {
        printf("[!] Administration Identity index buffer limits exceeded.\n");
        return;
    }
    char rawPassword[30];
    printf("Enter Authorized Security Personnel ID Card Token: ");
    scanf("%14s", arr[*count].staffID);
    printf("Assign Identity Profile Access Capacity Group (Admin/Technician/Faculty): ");
    scanf("%19s", arr[*count].userRole);
    printf("Enter Identity System Security Alpha Secret Phrase Pass: ");
    scanf("%29s", rawPassword);
    simpleEncrypt(rawPassword);
    strcpy(arr[*count].passwordHash, rawPassword);

    printf("Assign Strategic Command Clearance Hierarchy Tier (1-3): ");
    scanf("%d", &arr[*count].clearanceLevel);
    arr[*count].lastLoginDate = (Date){1, 1, 2026};

    printf("[*] User Clearance Credentials securely mapped and password encrypted inside infrastructure layer.\n");
    (*count)++;
}

int authenticateUser(UserAccount arr[], int count, char enteredID[], char enteredPass[]) {
    char checkPass[30];
    strcpy(checkPass, enteredPass);
    simpleEncrypt(checkPass);
    for (int i = 0; i < count; i++) {
        if (strcmp(arr[i].staffID, enteredID) == 0 && strcmp(arr[i].passwordHash, checkPass) == 0) {
            arr[i].lastLoginDate = (Date){30, 5, 2026};
            strcpy(activeUserRole, arr[i].userRole);
            activeClearanceLevel = arr[i].clearanceLevel;
            return arr[i].clearanceLevel;
        }
    }
    return 0;
}

void updateCredentials(UserAccount arr[], int count, char sID[]) {
    char rawPassword[30];
    for (int i = 0; i < count; i++) {
        if (strcmp(arr[i].staffID, sID) == 0) {
            printf("Verifying Profile: Matching Identity Entity Uncovered.\n");
            printf("Enter New Identity System Security Alpha Secret Phrase Pass: ");
            scanf("%29s", rawPassword);
            simpleEncrypt(rawPassword);
            strcpy(arr[i].passwordHash, rawPassword);
            printf("[*] Cryptographic password block override verified across running instance.\n");
            return;
        }
    }
    printf("[!] Account mapping lookup token unverified.\n");
}

void listUsersByRole(UserAccount arr[], int count, char role[]) {
    printf("\n--- AUDIT LAYER: ACTIVE PROFILE SESSIONS MATCHING: %s ---\n", role);
    for (int i = 0; i < count; i++) {
        if (strcmp(arr[i].userRole, role) == 0) {
            printf("User Reference: %s | Privileges Tier: %d | Chrono Active Signature Check-in: %02d/%02d/%04d\n",
                   arr[i].staffID, arr[i].clearanceLevel, arr[i].lastLoginDate.day,
                   arr[i].lastLoginDate.month, arr[i].lastLoginDate.year);
        }
    }
}

void revokeAccess(UserAccount arr[], int count, char targetID[]) {
    for (int i = 0; i < count; i++) {
        if (strcmp(arr[i].staffID, targetID) == 0) {
            arr[i].clearanceLevel = 0;
            strcpy(arr[i].userRole, "REVOKED");
            printf("[*] Security Quarantine applied. Identity clearance dropped to 0.\n");
            if (strcmp(targetID, activeUserRole) == 0 || activeClearanceLevel == arr[i].clearanceLevel) {
                activeClearanceLevel = 0;
                strcpy(activeUserRole, "None");
            }
            return;
        }
    }
    printf("[!] target security identifier target profile skipped or not found.\n");
}

void member5Menu(UserAccount arr[], int *count) {
    int choice, executionStatus;
    char inputID[15], inputPass[30], roleQuery[20];
    do {
        printf("\n--- MODULE 5: SECURE ADMINISTRATIVE IDENTITY SYSTEMS ---\n");
        printf("Current Session Role: %s | Clearance: Tier %d\n", activeUserRole, activeClearanceLevel);
        printf("1. Register Network Operational Account Context\n");
        printf("2. Request Verification System Access Authentication\n");
        printf("3. Modify Existing Profile Cryptographic Access String\n");
        printf("4. Display Connected Operators Categorized by Role Base\n");
        printf("5. Enforce Account Level Quarantine/Clearance Revocation\n");
        printf("6. Return to Primary Core Executive Dashboard\n");
        printf("Select choice: ");
        if (scanf("%d", &choice) != 1) { clearBuffer(); continue; }

        switch (choice) {
            case 1: registerUser(arr, count); break;
            case 2:
                printf("Enter Target ID: ");
                scanf("%14s", inputID);
                printf("Enter Target Password: ");
                scanf("%29s", inputPass);
                executionStatus = authenticateUser(arr, *count, inputID, inputPass);
                if(executionStatus > 0) {
                    printf("[SUCCESS] Identity Verified. Access granted to Hierarchy Tier Clearance Level %d.\n", executionStatus);
                } else {
                    printf("[DENIED] Cryptographic verification failure or record unknown.\n");
                }
                break;
            case 3:
                printf("Enter Personnel Target ID: ");
                scanf("%14s", inputID);
                updateCredentials(arr, *count, inputID);
                break;
            case 4:
                printf("Enter targeted search authorization group criteria: ");
                scanf("%19s", roleQuery);
                listUsersByRole(arr, *count, roleQuery);
                break;
            case 5:
                printf("Enter Identity Profile Targeted for Immediate Lockout: ");
                scanf("%14s", inputID);
                revokeAccess(arr, *count, inputID);
                break;
        }
    } while (choice != 6);
}

extern void member1Menu(Building arr[], int *count, SmartRoom rooms[], int roomCount);
extern void member2Menu(SmartRoom arr[], int *count, Building bArr[], int bCount, MaintenanceTicket tArr[], int *tCount);
extern void member3Menu(MaintenanceTicket arr[], int *count, UserAccount uArr[], int uCount, HardwareAsset hArr[], int hCount);
extern void member4Menu(HardwareAsset arr[], int *count, SmartRoom rArr[], int rCount, MaintenanceTicket tArr[], int *tCount);
extern void initializeRooms(SmartRoom arr[], int *count);

int main() {
    Building campusBuildings[MAX_BUILDINGS];
    int buildingCount = 0;

    SmartRoom campusRooms[MAX_ROOMS];
    int roomCount = 0;
    initializeRooms(campusRooms, &roomCount);

    MaintenanceTicket systemTickets[MAX_TICKETS];
    int ticketCount = 0;

    HardwareAsset networkAssets[MAX_ASSETS];
    int assetCount = 0;

    UserAccount registeredUsers[MAX_USERS];
    int userCount = 0;

    int mainChoice;

    do {
        printf("\n===================================================\n");
        printf("      SMART CAMPUS ENERGY & FACILITY SYSTEM        \n");
        printf("===================================================\n");
        printf("Current Active Session Privilege Level: Tier %d (%s)\n", activeClearanceLevel, activeUserRole);
        printf("1. Building & Utility Tracking (Member 1)\n");
        printf("2. Smart Room Booking & Sensors  (Member 2)\n");
        printf("3. Facility Maintenance Tickets  (Member 3)\n");
        printf("4. Smart Hardware Asset Manager  (Member 4)\n");
        printf("5. User Access & Security Logs   (Member 5)\n");
        printf("6. Exit Global Application\n");
        printf("===================================================\n");
        printf("Enter System Selection (1-6): ");

        if (scanf("%d", &mainChoice) != 1) {
            printf("[!] Invalid numeric format entry.\n");
            clearBuffer();
            continue;
        }

        switch (mainChoice) {
            case 1:
                member1Menu(campusBuildings, &buildingCount, campusRooms, roomCount);
                break;
            case 2:
                member2Menu(campusRooms, &roomCount, campusBuildings, buildingCount, systemTickets, &ticketCount);
                break;
            case 3:
                member3Menu(systemTickets, &ticketCount, registeredUsers, userCount, networkAssets, assetCount);
                break;
            case 4:
                member4Menu(networkAssets, &assetCount, campusRooms, roomCount, systemTickets, &ticketCount);
                break;
            case 5:
                member5Menu(registeredUsers, &userCount);
                break;
            case 6:
                printf("\n[*] Shutting down Campus Operational Core Dashboard. Terminated safely.\n");
                break;
            default:
                printf("[!] Evaluation choice out of bounds. Select 1 to 6.\n");
        }
    } while (mainChoice != 6);

    return 0;
}
