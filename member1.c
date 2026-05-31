#include <stdio.h>
#include <string.h>
#include "common.h"

void calculateDynamicEcoRating(Building *b, SmartRoom rooms[], int roomCount) {
    int totalRooms = 0;
    for (int i = 0; i < roomCount; i++) {
        if (strcmp(rooms[i].buildingCode, b->buildingCode) == 0) {
            totalRooms++;
        }
    }
    if (totalRooms == 0) totalRooms = 1;
    double factor = b->monthlyKWh / totalRooms;
    if (factor < 50.0) b->ecoRating = 'A';
    else if (factor < 150.0) b->ecoRating = 'B';
    else if (factor < 300.0) b->ecoRating = 'C';
    else if (factor < 500.0) b->ecoRating = 'D';
    else b->ecoRating = 'F';
}

void addBuilding(Building arr[], int *count, SmartRoom rooms[], int roomCount) {
    if (activeClearanceLevel < 3) {
        printf("[DENIED] Requires Tier 3 Admin clearance.\n");
        return;
    }
    if (*count >= MAX_BUILDINGS) {
        printf("[!] Building capacity reached.\n");
        return;
    }
    printf("Enter Building Unique Code: ");
    scanf("%9s", arr[*count].buildingCode);
    printf("Enter Building Description Name: ");
    clearBuffer();
    fgets(arr[*count].buildingName, 50, stdin);
    arr[*count].buildingName[strcspn(arr[*count].buildingName, "\n")] = 0;
    printf("Enter Total Level Floors: ");
    scanf("%d", &arr[*count].totalFloors);
    printf("Enter Baseline Monthly KWh: ");
    scanf("%lf", &arr[*count].monthlyKWh);
    printf("Enter Baseline Monthly Water Consumption (Liters): ");
    scanf("%lf", &arr[*count].monthlyWaterLiters);
    calculateDynamicEcoRating(&arr[*count], rooms, roomCount);
    (*count)++;
    printf("[*] Building logged and Eco-Rating dynamically assigned.\n");
}

void displayBuildingReport(Building arr[], int count) {
    if (count == 0) {
        printf("[-] No infrastructure tracked in runtime ledger yet.\n");
        return;
    }
    printf("\n--- CAMPUS SUSTAINABILITY INTEGRATED REPORT ---\n");
    printf("%-12s %-20s %-8s %-12s %-12s %-6s\n", "CODE", "NAME", "FLOORS", "KWH USED", "WATER (L)", "RATING");
    for (int i = 0; i < count; i++) {
        printf("%-12s %-20s %-8d %-12.2f %-12.2f %-6c\n",
               arr[i].buildingCode, arr[i].buildingName, arr[i].totalFloors,
               arr[i].monthlyKWh, arr[i].monthlyWaterLiters, arr[i].ecoRating);
    }
}

int findHighestEnergyConsumer(Building arr[], int count) {
    if (count == 0) return -1;
    int highIndex = 0;
    for (int i = 1; i < count; i++) {
        if (arr[i].monthlyKWh > arr[highIndex].monthlyKWh) {
            highIndex = i;
        }
    }
    return highIndex;
}

void updateUtilityUsage(Building arr[], int count, char code[], SmartRoom rooms[], int roomCount) {
    if (activeClearanceLevel < 3) {
        printf("[DENIED] Requires Tier 3 Admin privileges.\n");
        return;
    }
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(arr[i].buildingCode, code) == 0) {
            printf("Updating fields for matching record: %s\n", arr[i].buildingName);
            printf("Enter New Revised Monthly KWh consumption: ");
            scanf("%lf", &arr[i].monthlyKWh);
            printf("Enter New Revised Monthly Water Liters consumption: ");
            scanf("%lf", &arr[i].monthlyWaterLiters);
            calculateDynamicEcoRating(&arr[i], rooms, roomCount);
            found = 1;
            printf("[*] Core utility updates mapped and rating recalculated.\n");
            break;
        }
    }
    if (!found) printf("[!] Match query failed for code: %s\n", code);
}

void sortBuildingsByEcoRating(Building arr[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (arr[j].ecoRating > arr[j + 1].ecoRating) {
                Building temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    printf("[*] Ledger sorted by Eco-Rating successfully.\n");
}

void member1Menu(Building arr[], int *count, SmartRoom rooms[], int roomCount) {
    int choice;
    char searchCode[10];
    do {
        printf("\n--- MODULE 1: BUILDING UTILITY INTERFACE ---\n");
        printf("1. Register New Campus Structure\n");
        printf("2. Display Macro Infrastructure Audit Table\n");
        printf("3. Calculate Highest Electrical Power Consumer Node\n");
        printf("4. Update Building Real-World Metrics\n");
        printf("5. Sort Campus Infrastructure Profiles by Eco-Rating\n");
        printf("6. Return to Primary Core Executive Dashboard\n");
        printf("Select choice: ");
        if (scanf("%d", &choice) != 1) { clearBuffer(); continue; }

        switch (choice) {
            case 1: addBuilding(arr, count, rooms, roomCount); break;
            case 2: displayBuildingReport(arr, *count); break;
            case 3: {
                int idx = findHighestEnergyConsumer(arr, *count);
                if (idx != -1) printf("[*] Outlier Target Profile: %s consuming %.2f KWh\n", arr[idx].buildingName, arr[idx].monthlyKWh);
                else printf("[-] Array initialization empty.\n");
                break;
            }
            case 4:
                printf("Enter target building code to update: ");
                scanf("%9s", searchCode);
                updateUtilityUsage(arr, *count, searchCode, rooms, roomCount);
                break;
            case 5: sortBuildingsByEcoRating(arr, *count); displayBuildingReport(arr, *count); break;
        }
    } while (choice != 6);
}
