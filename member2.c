#include <stdio.h>
#include <string.h>
#include "common.h"

void initializeRooms(SmartRoom arr[], int *count) {
    arr[0] = (SmartRoom){101, "ENG01", 60, 22.5, 0, 1.2};
    arr[1] = (SmartRoom){204, "ENG01", 45, 19.0, 1, 4.5};
    arr[2] = (SmartRoom){102, "IT02",  30, 26.0, 0, 0.0};
    arr[3] = (SmartRoom){402, "BUS03", 120, 21.0, 1, 8.2};
    arr[4] = (SmartRoom){105, "IT02",  50, 18.5, 0, 3.1};
    *count = 5;
}

void bookSmartRoom(SmartRoom arr[], int count, char bCode[], int rNum) {
    for (int i = 0; i < count; i++) {
        if (strcmp(arr[i].buildingCode, bCode) == 0 && arr[i].roomNumber == rNum) {
            if (arr[i].isOccupied) {
                printf("[!] Scheduling Conflict: Room %d is already active.\n", rNum);
            } else {
                arr[i].isOccupied = 1;
                printf("[*] Booking complete! Intelligent environmental nodes activated.\n");
            }
            return;
        }
    }
    printf("[!] Targeted room address could not be found.\n");
}

void flagEnergyWasterRooms(SmartRoom arr[], int count, Building bArr[], int bCount) {
    printf("\n--- ANOMALY REPORT: ROOM CLIMATE VULNERABILITIES ---\n");
    int issuesDetected = 0;
    for (int i = 0; i < count; i++) {
        if (arr[i].isOccupied == 0 && arr[i].acRunTimeHours > 1.0) {
            double cost = arr[i].acRunTimeHours * 15.50;
            printf("[ALERT] Room %d in %s is VACANT but AC has been active for %.1f hours. Estimated Waste: LKR %.2f\n",
                   arr[i].roomNumber, arr[i].buildingCode, arr[i].acRunTimeHours, cost);
            for (int j = 0; j < bCount; j++) {
                if (strcmp(bArr[j].buildingCode, arr[i].buildingCode) == 0) {
                    bArr[j].monthlyKWh += (arr[i].acRunTimeHours * 1.5);
                }
            }
            issuesDetected++;
        }
    }
    if(issuesDetected == 0) printf("[*] Infrastructure check clean. No open waste metrics mapped.\n");
}

void updateRoomTemperature(SmartRoom arr[], int count, int rNum, double newTemp, MaintenanceTicket tArr[], int *tCount) {
    for (int i = 0; i < count; i++) {
        if (arr[i].roomNumber == rNum) {
            arr[i].currentTempCelsius = newTemp;
            printf("[*] Telemetry update processed. Room %d temperature set to %.2f C\n", rNum, newTemp);
            if (newTemp > 28.0 && *tCount < MAX_TICKETS) {
                tArr[*tCount].ticketID = 3001 + *tCount;
                strcpy(tArr[*tCount].targetBuildingCode, arr[i].buildingCode);
                sprintf(tArr[*tCount].issueDescription, "Automated AC Failure Warning Room %d", rNum);
                strcpy(tArr[*tCount].assignedTechnician, "Unassigned");
                tArr[*tCount].priorityLevel = 5;
                strcpy(tArr[*tCount].status, "Pending");
                (*tCount)++;
                printf("[AUTOMATED ALERT] High temperature triggered automated maintenance ticket enrollment.\n");
            }
            return;
        }
    }
    printf("[!] No internal matching record available.\n");
}

void searchVacantRoomsByCapacity(SmartRoom arr[], int count, int minCapacity) {
    printf("\n--- FILTER SEARCH: AVAILABLE LECTURE SPACES (CAPACITY >= %d) ---\n", minCapacity);
    for (int i = 0; i < count; i++) {
        if (!arr[i].isOccupied && arr[i].capacity >= minCapacity) {
            printf("-> Building %s Room %d | Seats: %d | Climate: %.1f C\n",
                   arr[i].buildingCode, arr[i].roomNumber, arr[i].capacity, arr[i].currentTempCelsius);
        }
    }
}

void member2Menu(SmartRoom arr[], int *count, Building bArr[], int bCount, MaintenanceTicket tArr[], int *tCount) {
    int choice, roomNum, minCap;
    char bCode[10];
    double newTemp;
    do {
        printf("\n--- MODULE 2: ECO SMART-ROOM DASHBOARD ---\n");
        printf("1. List All Configured Micro Rooms & Live Status\n");
        printf("2. Request Smart Room Reservation Booking\n");
        printf("3. Audit Active Environmental Waste Warnings\n");
        printf("4. Set Climate Telemetry Temperature Variable\n");
        printf("5. Query Free Capacity Spaces\n");
        printf("6. Return to Primary Core Executive Dashboard\n");
        printf("Select choice: ");
        if (scanf("%d", &choice) != 1) { clearBuffer(); continue; }

        switch (choice) {
            case 1:
                for(int i=0; i<*count; i++) {
                    printf("Room %d [%s] - Cap: %d | Status: %s | Climate: %.1fC | AC runtime: %.1f hrs\n",
                           arr[i].roomNumber, arr[i].buildingCode, arr[i].capacity,
                           arr[i].isOccupied ? "OCCUPIED" : "VACANT", arr[i].currentTempCelsius, arr[i].acRunTimeHours);
                }
                break;
            case 2:
                printf("Enter Target Building Code and Room Number: ");
                scanf("%9s %d", bCode, &roomNum);
                bookSmartRoom(arr, *count, bCode, roomNum);
                break;
            case 3: flagEnergyWasterRooms(arr, *count, bArr, bCount); break;
            case 4:
                printf("Enter target Room Number: ");
                scanf("%d", &roomNum);
                printf("Enter real-time Celsius reading: ");
                scanf("%lf", &newTemp);
                updateRoomTemperature(arr, *count, roomNum, newTemp, tArr, tCount);
                break;
            case 5:
                printf("Enter structural target floor threshold capacity: ");
                scanf("%d", &minCap);
                searchVacantRoomsByCapacity(arr, *count, minCap);
                break;
        }
    } while (choice != 6);
}
