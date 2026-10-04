#include <stdio.h>
#include <string.h>
#include "suppliers.h"
#include "utils.h"

#define MAX_SUPPLIERS 50

typedef struct {
    int supplierID;
    char supplierName[50];
    char email[50];
    char phone[20];
    char town[30];
} Supplier;

static Supplier suppliers[MAX_SUPPLIERS];
static int supplierCount = 0;

static void addSupplier(void);
static void displaySuppliers(void);
static void searchSupplier(void);

void loadSampleSuppliers(void)
{
    suppliers[0].supplierID = 1001;
    strcpy(suppliers[0].supplierName, "ABC Stationers");
    strcpy(suppliers[0].email, "abc@gmail.com");
    strcpy(suppliers[0].phone, "0811234567");
    strcpy(suppliers[0].town, "Windhoek");

    suppliers[1].supplierID = 1002;
    strcpy(suppliers[1].supplierName, "Tech Solutions");
    strcpy(suppliers[1].email, "tech@gmail.com");
    strcpy(suppliers[1].phone, "0817654321");
    strcpy(suppliers[1].town, "Swakopmund");

    supplierCount = 2;
}

static void addSupplier(void)
{
    if (supplierCount >= MAX_SUPPLIERS) {
        printf("Supplier storage full.\n");
        return;
    }

    printf("Supplier ID: ");
    scanf("%d", &suppliers[supplierCount].supplierID);

    printf("Supplier Name: ");
    scanf(" %[^\n]", suppliers[supplierCount].supplierName);

    printf("Email: ");
    scanf("%s", suppliers[supplierCount].email);

    printf("Phone Number: ");
    scanf("%s", suppliers[supplierCount].phone);

    printf("Town/Location: ");
    scanf(" %[^\n]", suppliers[supplierCount].town);

    supplierCount++;
    printf("Supplier added successfully.\n");
}

static void displaySuppliers(void)
{
    printf("\n========== SUPPLIER LIST ==========\n");

    for(int i = 0; i < supplierCount; i++) {
        printf("\nSupplier ID: %d\n", suppliers[i].supplierID);
        printf("Name: %s\n", suppliers[i].supplierName);
        printf("Email: %s\n", suppliers[i].email);
        printf("Phone: %s\n", suppliers[i].phone);
        printf("Town: %s\n", suppliers[i].town);
    }
}

static void searchSupplier(void)
{
    char name[50];
    int found = 0;

    printf("Enter Supplier Name: ");
    scanf(" %[^\n]", name);

    for(int i = 0; i < supplierCount; i++) {
        if(strcmp(name, suppliers[i].supplierName) == 0) {
            printf("\nSupplier Found\n");
            printf("ID: %d\n", suppliers[i].supplierID);
            printf("Name: %s\n", suppliers[i].supplierName);
            printf("Email: %s\n", suppliers[i].email);
            printf("Phone: %s\n", suppliers[i].phone);
            printf("Town: %s\n", suppliers[i].town);
            found = 1;
            break;
        }
    }

    if(!found)
        printf("Supplier not found.\n");
}

void supplierMenu(void)
{
    int choice;

    do {
        printf("\n========== SUPPLIER MANAGEMENT ==========\n");
        printf("1. Add Supplier\n");
        printf("2. Display Suppliers\n");
        printf("3. Search Supplier\n");
        printf("4. Return to Main Menu\n");

        choice = readIntInRange("Enter your choice: ", 1, 4);

        switch(choice) {
            case 1: addSupplier(); break;
            case 2: displaySuppliers(); break;
            case 3: searchSupplier(); break;
        }

    } while(choice != 4);
}
