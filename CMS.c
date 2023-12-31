#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct courier {
    int trackingNumber;
    char senderName[40];
    char senderAddress[50];
    char recieverName[40];
    char recieverAddress[50];    
    char dateOfDispatch[20];
} record;

int isPresent(int tno) {
    FILE *fptr;
    fptr = fopen("Record.txt", "r");
    if (fptr == NULL) {
        printf("\n\tError: Requested file does not exist\n");
        exit(1);
    }

    while (fread(&record, sizeof(record), 1, fptr)) {
        if (record.trackingNumber == tno) {
            return 1;
        }
    }
    fclose(fptr);
}

void insertRecords() {
    FILE *fptr;
    fptr = fopen("Record.txt", "a");
    if (fptr == NULL) {
        printf("\n\tError: Requested file does not exist\n");
        exit(1);
    }
    printf("\n\tEnter tracking number: ");
            scanf("%d", &record.trackingNumber);
            printf("\tEnter sender name: ");
            scanf("%s", &record.senderName);
            printf("\tEnter sender address: ");
            scanf("%s", &record.senderAddress);
            printf("\tEnter reciever name: ");
            scanf("%s", &record.recieverName);
            printf("\tEnter reciever address: ");
            scanf("%s", &record.recieverAddress);
            printf("\tEnter date of dispatch: ");
            scanf("%s", &record.dateOfDispatch);
    fwrite(&record, sizeof(record), 1, fptr);
    printf("\n\tRecord inserted successfully. \n");
    fclose(fptr);
}

void displayRecords() {
    FILE *fptr;
    fptr = fopen("Record.txt", "r");
    if (fptr == NULL) {
        printf("\n\tError: Requested file does not exist\n");
        exit(1);
    }
    printf("\n\tTRACKING NUMBER | SENDER'S NAME | SENDER'S ADDRESS | RECIEVER'S NAME | RECIEVER'S ADDRESS | DATE OF DISPATCH\n");
    printf("\t---------------- --------------- ------------------ ----------------- -------------------- -----------------\n");
    while (fread(&record, sizeof(record), 1, fptr)) {
        printf("\t%-16d| %-14s| %-17s| %-16s| %-19s| %s \n", record.trackingNumber, record.senderName, record.senderAddress, record.recieverName, record.recieverAddress, record.dateOfDispatch);
    }
    printf("\t---------------- --------------- ------------------ ----------------- -------------------- -----------------\n");
    fclose(fptr);
}

void deleteRecord() {
    FILE *fptr;
    FILE *tfptr;    
    int tno;
    printf("\n\tEnter the tracking number of the record to be deleted: ");
    scanf("%d", &tno);

    if (isPresent(tno)) {

        fptr = fopen("Record.txt", "r");
        tfptr = fopen("Temp.txt", "w");

        if (fptr == NULL) {
            printf("\n\tError: Requested file does not exist\n");
            exit(1);
        }
        while(fread(&record, sizeof(record), 1, fptr)) {
            if (record.trackingNumber != tno) {
                fwrite(&record, sizeof(record), 1, tfptr);
            }
        } 

        fclose(fptr);
        fclose(tfptr);

        fptr = fopen("Record.txt", "w");
        tfptr = fopen("Temp.txt", "r");  

        while(fread(&record, sizeof(record), 1, tfptr)) {            
                fwrite(&record, sizeof(record), 1, fptr);            
        }

        printf("\tRecord deleted successfully \n");
        fclose(fptr);
        fclose(tfptr);       

    } else {
        printf("\tTracking number %d does not exist \n", tno);
    }
}

void updateRecord() {
    FILE *fptr;
    FILE *tfptr;
    int tno;
    printf("\n\tEnter the tracking number of the record to be updated: ");
    scanf("%d", &tno);
    if (isPresent(tno)) {
        fptr = fopen("Record.txt", "r");
        tfptr = fopen("Temp.txt", "w");
        while (fread(&record, sizeof(record), 1, fptr)) {
            if (record.trackingNumber != tno) {
                fwrite(&record, sizeof(record), 1, tfptr);
            } else {
                int c;
                do {
                    printf("\n\t--------------------SELECT AN OPTION--------------------\n");
                    printf("\t1. Update sender's name\n");
                    printf("\t2. Update sender's address\n");
                    printf("\t3. Update reciever's name\n");
                    printf("\t4. Update reciever's address\n");
                    printf("\t5. Update date of dispatch\n");
                    printf("\t6. Exit\n");
                    printf("\tEnter choice: ");
                    scanf("%d", &c);

                    switch (c) {
                        case 1: 
                        printf("\n\tEnter new name: ");
                        scanf("%s", record.senderName);
                        break;
                        case 2: 
                        printf("\n\tEnter new address: ");
                        scanf("%s", record.senderAddress);
                        break;
                        case 3: 
                        printf("\n\tEnter new name: ");
                        scanf("%s", record.recieverName);
                        break;
                        case 4: 
                        printf("\n\tEnter new address: ");
                        scanf("%s", record.recieverAddress);
                        break;
                        case 5: 
                        printf("\n\tEnter new date of dispatch: ");
                        scanf("%s", record.dateOfDispatch);
                        break;
                        case 6: 
                        break;
                        default: 
                        printf("\n\tInvalid Selection \n");
                    }                    
                } while (c != 6);
                fwrite(&record, sizeof(record), 1, tfptr);
            }
        }

        fclose(fptr);
        fclose(tfptr);

        fptr = fopen("Record.txt", "w");
        tfptr = fopen("Temp.txt", "r");

        while (fread(&record, sizeof(record), 1, tfptr)) {
            fwrite(&record, sizeof(record), 1, fptr);
        }

        printf("\tRecord updated successfully. \n");

        fclose(fptr);
        fclose(tfptr);

    }
}

void main() {
    int ch;    
    printf("\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ COURIER MANAGEMENT SYSTEM ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    do {        
        printf("\n\t--------------------SELECT AN OPTION--------------------\n");
        printf("\t1. Insert a new record\n");
        printf("\t2. Display all records\n");
        printf("\t3. Delete a record\n");
        printf("\t4. Update a record\n");
        printf("\t5. Exit\n");
        printf("\n\tEnter choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: insertRecords();
            break;
            case 2: displayRecords();
            break;
            case 3: deleteRecord();
            break;
            case 4: updateRecord();
            break;
            case 5: printf("\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ YOU'VE EXITED THE SYSTEM. ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");            
            break;
            default:
            printf("\tInvalid selection. \n");
        }
    } while(ch != 5);
}