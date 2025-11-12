#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


// Global variables for guest information


int guestStayLengths[6];
int guestnumber[6];
int guestRoomChoices[6];
char guestBoardTypes[6][3];
char guestBookingIDs[6][80];
bool guestNewspapers[6];
int guestCount = 0;

char firstName[50];
char surName[50];
int adults;
int children;
int stayLength;
int roomChoice;
char boardType[3];
char bookingID[80];
bool newspaper;
bool namecheck;
bool roomsAvailable[6] = {true, true, true, true, true, true};
int roomPrices[6] = {100, 100, 85, 75, 75, 50};
int boardPrices[3] = {20, 15, 5};
int nameCheck(const char *s ) {
    int k=0;
    if (strlen(s) >16 || strlen(s) <=0) {
        printf(" The name you etered is ethier too long or too short \n");
        k++;
    }

        for(int i=0;i<strlen(s);i++) {
            if ((s[i] <65 )||(s[i] <97 && s[i]>90)||( s[i]>122)  ) {
               k++;
            }
        }

    if (k>0){ printf(" The name cant have any unusuall characthers\n");}
    else if (k==0){return 1;}
}

int daysInMonth(int month) {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return 28;
        default: return 0;
    }

}

int confirmOrQuit(const char* question) {
    char c;
    printf("%s (Y/N, Q to quit): ", question);
    scanf(" %c", &c);
    c = toupper(c);
    if (c == 'Q') {return -1;}
    if (c == 'N') {return 0;}
     if (c == 'Y') {return 1;}
    else { return 2;}
}


int getBoardPrice(const char* type) {
    if (strcmp(type, "FB") == 0) return boardPrices[0];
    if (strcmp(type, "HB") == 0) return boardPrices[1];
    if (strcmp(type, "BB") == 0) return boardPrices[2];
    return 0;
}

void checkin() {
    int day, month, year;

    printf("************* Welcome to Kap Hotel Check-in ***********\n");
    printf("You can quit at any question by pressing 'Q'.\n");

    while (true) {
        int p=0;
        do {
            printf("Enter main guest's first name: ");
            scanf("%s", firstName);
            p= nameCheck(firstName );
        }while(p != 1);

        int d= (confirmOrQuit("Is this correct?"));
        if (d == 1) break;
        if (d == 0) continue;
        if (d == -1) return;
    }

    while (true) {
        int q=0;
       do {
           printf("Enter main guest's surname: ");
           scanf("%s", surName);
            q= nameCheck(surName);
       }while (q != 1);
        int d= (confirmOrQuit("Is this correct?"));
        if (d == 1) break;
        if (d == 0) continue;
        if (d == -1) return;
    }

    while (true) {
        printf("Enter main guest's DOB (DD/MM/YY): ");
        if (scanf("%d/%d/%d", &day, &month, &year) != 3) {
            printf("Invalid format.\n");
            while (getchar() != '\n');
            continue;
        }
        if (month < 1 || month > 12 || day < 1 || day > daysInMonth(month)) {
            printf("Invalid date.\n");
            continue;
        }
        if (year>2007) {
            printf("children cant sign up plaese bring and adult.\n");

        }
        if (year<1925) {
            printf("You cant be more tahn 100 years old that is not possible.\n");
            continue;
        }
        int d= (confirmOrQuit("Is this correct?"));
        if (d == 1) break;
        if (d == 0) continue;
        if (d == -1) return;

    }


    while (true) {
        printf("Enter number of adults (16+): ");
        scanf("%d", &adults);
        printf("Enter number of children (15 or under): ");
        scanf("%d", &children);

        if (children > 0 && adults < 1) {
            printf("Children must be accompanied by at least one adult.\n");
            continue;
        }
        if (adults + children > 4) {
            printf("Maximum guests allowed is 4.\n");
            continue;
        }
        int d= (confirmOrQuit("Is this correct?"));
        if (d == 1) break;
        if (d == 0) continue;
        if (d == -1) return;
    }

    while (true) {
        printf("Enter number of days to stay (max 15): ");
        scanf("%d", &stayLength);
        if (stayLength < 1 || stayLength > 15) {
            printf("Invalid stay length.\n");
            continue;
        }
        int d= (confirmOrQuit("Is this correct?"));
        if (d == 1) break;
        if (d == 0) continue;
        if (d == -1) return;
    }


    while (true) {
        printf("Enter board type (HB/FB/BB): ");
        scanf("%s", boardType);
        if (strcmp(boardType, "HB") != 0 &&
            strcmp(boardType, "FB") != 0 &&
            strcmp(boardType, "BB") != 0) {
            printf("Invalid board type.\n");
            continue;
        }
        int d= (confirmOrQuit("Is this correct?"));
        if (d == 1) break;
        if (d == 0) continue;
        if (d == -1) return;
    }


    while (true) {
        printf("\nAvailable rooms:\n");
        for (int i = 0; i < 6; i++)
            printf("Room %d - GDP%d - %s\n", i + 1, roomPrices[i], roomsAvailable[i] ? "Available" : "Occupied");

        printf("Choose room number: ");
        scanf("%d", &roomChoice);

        if (roomChoice < 1 || roomChoice > 6 || !roomsAvailable[roomChoice - 1]) {
            printf("Room unavailable or invalid.\n");
            continue;
        }
        int d= (confirmOrQuit("Is this correct?"));
        if (d == 1) break;
        if (d == 0) continue;
        if (d == -1) return;
    }


    while (true) {
        printf("Do you want a newspaper? (Y/N): ");
        char c;
        scanf(" %c", &c);
        if (toupper(c) == 'Q') return;
        newspaper = (toupper(c) == 'Y');
        int d= (confirmOrQuit("Is this correct?"));
        if (d == 1) break;
        if (d == 0) continue;
        if (d == -1) return;
    }


    roomsAvailable[roomChoice - 1] = false;

    strcpy(bookingID, surName);

    printf("\nBooking Summary:\n");
    printf("Guest: %s %s\n", firstName, surName);
    printf("Adults: %d, Children: %d\n", adults, children);
    printf("Stay: %d days\n", stayLength);
    printf("Board type: %s (GDP%d per person per day)\n", boardType, getBoardPrice(boardType));
    printf("Room: %d (GDP%d)\n", roomChoice, roomPrices[roomChoice - 1]);
    printf("Newspaper: %d\n", newspaper );
    printf("Booking ID: %s\n", bookingID);
    printf("\n************* Check-in Complete ***********\n");
}

void storeInfo() {
    guestStayLengths[guestCount] = stayLength;
    guestRoomChoices[guestCount] = roomChoice;
    strcpy(guestBoardTypes[guestCount], boardType);
    strcpy(guestBookingIDs[guestCount], bookingID);
    guestNewspapers[guestCount] = newspaper;
    guestnumber[guestCount] = children + adults;
    guestCount++;

    printf("\nGuest stay info has been stored under booking ID: %s\n", bookingID);
}

void findAndPrintByID() {
    char searchID[80];
    printf("\nEnter Booking ID to search: ");
    scanf("%s", searchID);

    for (int i = 0; i < guestCount; i++) {
        if (strcmp(guestBookingIDs[i], searchID) == 0) {

            printf("\n=== Guest Found ===\n");
            printf("Booking ID: %s\n", guestBookingIDs[i]);
            printf("Room: %d\n", guestRoomChoices[i]);
            printf("Stay Length: %d nights\n", guestStayLengths[i]);
            printf("number of guests: %d nights\n", guestnumber[i]);
            printf("Board Type: %s\n", guestBoardTypes[i]);
            printf("Newspaper: %d\n", guestNewspapers[i]);
            printf("====================\n");
            return;
        }
    }

    printf("\nNo guest found with Booking ID: %s\n", searchID);
}

int main() {
for (int i=0;i<100000;i++) {
    char choice;

    printf("Do you want to Check In (C), Check Out (O), Dinner (D), CHECK info(I), or Quit (Q)? ");
    scanf(" %c", &choice);
    choice = toupper(choice);

    if (choice == 'C') {
        checkin();
        storeInfo();

    }
    else if (choice == 'O') {
        printf("Check Out function not added yet.\n");
    }
    else if (choice == 'D') {
        printf("Dinner function not added yet.\n");
    }
    else if (choice == 'I') {
        findAndPrintByID();
    }
    else if (choice == 'Q') {
        printf("Goodbye!\n");
    }
    else {
        printf("Invalid option.\n");
    }
}
    return 0;
}
