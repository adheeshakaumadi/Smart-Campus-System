#ifndef COMMON_H
#define COMMON_H

#define MAX_BUILDINGS 5
#define MAX_ROOMS 5
#define MAX_TICKETS 5
#define MAX_ASSETS 5
#define MAX_USERS 5

extern char activeUserRole[20];
extern int activeClearanceLevel;

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    char buildingCode[10];
    char buildingName[50];
    int totalFloors;
    double monthlyKWh;
    double monthlyWaterLiters;
    char ecoRating;
} Building;

typedef struct {
    int roomNumber;
    char buildingCode[10];
    int capacity;
    double currentTempCelsius;
    int isOccupied;
    double acRunTimeHours;
} SmartRoom;

typedef struct {
    int ticketID;
    char targetBuildingCode[10];
    char issueDescription[100];
    char assignedTechnician[50];
    int priorityLevel;
    char status[15];
} MaintenanceTicket;

typedef struct {
    char assetID[15];
    char deviceType[30];
    Date installationDate;
    int operationalStatus;
    int assignedRoomNumber;
} HardwareAsset;

typedef struct {
    char staffID[15];
    char userRole[20];
    char passwordHash[30];
    Date lastLoginDate;
    int clearanceLevel;
} UserAccount;

void clearBuffer();
void simpleEncrypt(char *pass);

#endif
