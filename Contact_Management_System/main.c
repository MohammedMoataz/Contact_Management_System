#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONTACTS 10
#define CHARACTERS 15
#define NUMBER 11
#define EMAIL 20
#define ADDRESS 10

void readFile();
void writeFile();
void sortCont();
int binarySearch(char key[CHARACTERS]);
int linerSearch(int key);
void menu();

void addCont();
void listCont();
int searchCont();
void editCont();
void deleteCont();

int contCounter = 0;
struct contact {
    char name[CHARACTERS];
    long int phoneNumber;
    char address[ADDRESS];
    char email[EMAIL];
};
typedef struct contact Contact;
Contact contacts[CONTACTS];

int main()
{
    puts("================================================");
    puts("***** Welcome to Contact Management System *****");
    puts("================================================");
    menu();

    return 0;
}

void readFile()
{
    FILE *rfPtr;

    if((rfPtr = fopen("Contacts.txt", "r")) == NULL)
        puts("File is not exist!");

    else {
        contCounter = 0;

        while(!feof(rfPtr)) {
            fscanf(rfPtr, "%14s%11ld%14s%19s", contacts[contCounter].name, &contacts[contCounter].phoneNumber, contacts[contCounter].address, contacts[contCounter].email);

            contCounter++;

        }

        fclose(rfPtr);
    }

    sortCont();
}

void writeFile()
{
    FILE *wfPtr;

    if((wfPtr = fopen("Contacts.txt", "w")) == NULL) {
        puts("File is not exist!");
    }

    else {
        for(contCounter = 0; contCounter < CONTACTS; contCounter++) {
            if(contacts[contCounter].phoneNumber != 0) {
                fprintf(wfPtr, "%14s %15ld %15s %25s\n", contacts[contCounter].name, contacts[contCounter].phoneNumber, contacts[contCounter].address, contacts[contCounter].email);
            }
        }
        fclose(wfPtr);
    }
}

void menu()
{
    int choice;

    puts("");
    puts("");
    puts("\tMAIN MENU");
    puts("=========================");
    puts(" [1] Add a new Contact");
    puts(" [2] List all Contacts");
    puts(" [3] Search for Contact");
    puts(" [4] Edit a Contact");
    puts(" [5] Delete a Contact");
    puts(" [0] Exit");
    puts("====================");
    printf(" Enter a choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            addCont();
            break;

        case 2:
            listCont();
            break;

        case 3:
            searchCont();
            break;

        case 4:
            editCont();
            break;

        case 5:
            deleteCont();
            break;

        case 0:
            break;

        default:
            puts("Invalid value!");
            puts("");
            break;
    }

    menu();
}

void addCont()
{
    FILE *afPtr;

    if((afPtr = fopen("Contacts.txt", "a")) == NULL)
        printf("File is not exist!");

    else {
        puts("");
        puts("");
        puts("   =================================================");
        puts("\t\t ADD CONTACTS ");
        puts("   =================================================");
        puts("");

        printf("Name: ");
        scanf("%s", contacts[contCounter].name);

        printf("Phone number: ");
        scanf("%ld", &contacts[contCounter].phoneNumber);

        printf("Address: ");
        scanf("%s", contacts[contCounter].address);

        printf("Email: ");
        scanf("%s", contacts[contCounter].email);

        fprintf(afPtr, "%-14s %-15ld %-15s %s\n", contacts[contCounter].name, contacts[contCounter].phoneNumber, contacts[contCounter].address, contacts[contCounter].email);

        contCounter++;

        fclose(afPtr);
    }

    sortCont();
}

void listCont()
{
    readFile();

    puts("");
    puts("");
    puts("   =================================================");
    puts("\t\t LIST CONTACTS ");
    puts("   =================================================");
    puts("");

    printf("%-20s %-25s %-20s %s\n", "Name", "Phone No.", "Address", "E-Mail");
    puts("==================================================================================================================");

    int i = 0;
    while(i < CONTACTS) {
        if(contacts[i].phoneNumber != 0) {
            printf("%-20s %-25ld %-20s %s\n", contacts[i].name, contacts[i].phoneNumber, contacts[i].address, contacts[i].email);
        }

        i++;
    }
}

int searchCont()
{
    int o,
        index,
        number;
    char contName[CHARACTERS];

    sortCont();

    puts("");
    puts("");
    puts("   =================================================");
    puts("\t\t SEARCH CONTACTS ");
    puts("   =================================================");
    puts("");

    puts("[1] Search by name: ");
    puts("[2] Search by number: ");
    puts("====================");
    printf("Enter the choice: ");
    scanf("%d", &o);

    switch(o) {
        case 1:
            printf("Enter the name of contact: ");
            getc(stdin);gets(contName);
            index = binarySearch(contName);

            if(index != -1) {
                puts("");
                printf("%s: %s\n", "Name", contacts[index].name);
                printf("%s: %ld\n", "Phone number", contacts[index].phoneNumber);
                printf("%s: %s\n", "Address", contacts[index].address);
                printf("%s: %s\n", "E-Mali", contacts[index].email);
            }
            return index;
            break;

        case 2:
            printf("Enter the number of contact: ");
            scanf("%d", &number);
            index = linerSearch(number);

            if(index != -1) {
                puts("");
                printf("%s: %s\n", "Name", contacts[index].name);
                printf("%s: %ld\n", "Phone number", contacts[index].phoneNumber);
                printf("%s: %s\n", "Address", contacts[index].address);
                printf("%s: %s\n", "E-Mali", contacts[index].email);
            }
            return index;
            break;

        default:
            puts("Invalid value!");
            break;
    }
    return -1;
}

void editCont()
{
    puts("");
    puts("");
    puts("   =================================================");
    puts("\t\t EDIT CONTACTS ");
    puts("   =================================================");
    puts("");

    int index = searchCont();

    if(index > -1) {
        puts("");
        printf("Name: ");
        scanf("%s", contacts[index].name);

        printf("Phone number: ");
        scanf("%ld", &contacts[index].phoneNumber);

        printf("Address: ");
        scanf("%s", contacts[index].address);

        printf("Email: ");
        scanf("%s", contacts[index].email);
    }

    else {
        puts("Not found!");
    }

}

void deleteCont()
{
    int index = searchCont();

    if(index > -1) {
        contacts[index].phoneNumber = 0;

        writeFile();
    }
}

void sortCont()
{
    for(int i = 0; i < CONTACTS; i++) {
        for(int j = 0; j < CONTACTS - 1; j++) {
            if(strcmp(contacts[j].name, contacts[j + 1].name) > 0) {
                Contact temp = contacts[j];
                contacts[j] = contacts[j + 1];
                contacts[j + 1] = temp;
            }
        }
    }
}

int binarySearch(char key[CHARACTERS])
{
    int low = 0,
        middle,
        high = CONTACTS - 1;

    while(low <= high) {
        middle = (low + high) / 2;

        if((strcmp(key, contacts[middle].name)) == 0) {
            return middle;
        }

        else if((strcmp(key, contacts[middle].name)) < 0) {
            high = middle - 1;
        }

        else if((strcmp(key, contacts[middle].name)) > 0) {
            low = middle + 1;
        }
    }
    puts("Not found!");
    return -1;
}

int linerSearch(int key)
{
    for(int i = 0; i < CONTACTS; i++) {
        if(contacts[i].phoneNumber == key) {
            return i;
        }
    }

    puts("Not found!");
    return -1;
}
