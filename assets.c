#include <stdio.h>
#include <string.h>
#include "assets.h"
#include "utils.h"

#define CONDITION_COUNT 4

static const char *assetTypes[ASSET_TYPE_COUNT] = {
    "Vehicle", "Computer", "Building", "Equipment", "Furniture"
};
static const char *conditions[CONDITION_COUNT] = {
    "Excellent", "Good", "Fair", "Poor"
};

static char   assetId[MAX_ASSETS][ASSET_ID_LEN];
static char   assetName[MAX_ASSETS][ASSET_NAME_LEN];
static char   assetType[MAX_ASSETS][ASSET_TYPE_LEN];
static double assetValue[MAX_ASSETS];
static char   assetDept[MAX_ASSETS][ASSET_DEPT_LEN];
static char   assetCond[MAX_ASSETS][ASSET_COND_LEN];
static int    assetCount = 0;

int findAssetById(const char *id)
{
    int i;
    for (i = 0; i < assetCount; i++) {
        if (equalsIgnoreCase(assetId[i], id))
            return i;
    }
    return -1;
}

int getAssetCount(void)                  { return assetCount; }
double getAssetValue(int index)          { return assetValue[index]; }
const char *getAssetType(int index)      { return assetType[index]; }
const char *getAssetTypeName(int t)      { return assetTypes[t]; }

static void storeAsset(const char *id, const char *name, const char *type,
                       double value, const char *dept, const char *cond)
{
    strcpy(assetId[assetCount], id);
    strcpy(assetName[assetCount], name);
    strcpy(assetType[assetCount], type);
    assetValue[assetCount] = value;
    strcpy(assetDept[assetCount], dept);
    strcpy(assetCond[assetCount], cond);
    assetCount++;
}

static void printAssetHeader(void)
{
    printf("%-8s %-20s %-10s %14s %-12s %-9s\n",
           "ID", "Asset", "Type", "Value (N$)", "Department", "Condition");
    printLine('-', LINE_WIDTH);
}

static void printAssetRow(int i)
{
    printf("%-8.8s %-20.20s %-10.10s %14.2f %-12.12s %-9.9s\n",
           assetId[i], assetName[i], assetType[i], assetValue[i],
           assetDept[i], assetCond[i]);
}

/* Shows a numbered list and returns the chosen item (0-based index). */
static int chooseFromList(const char *title, const char *items[], int count)
{
    int i;
    printf("%s\n", title);
    for (i = 0; i < count; i++)
        printf("  %d. %s\n", i + 1, items[i]);
    return readIntInRange("Select: ", 1, count) - 1;
}

void addAsset(void)
{
    char id[ASSET_ID_LEN], name[ASSET_NAME_LEN], dept[ASSET_DEPT_LEN];
    double value;
    int type, cond;

    printHeader("ADD ASSET");
    if (assetCount >= MAX_ASSETS) {
        printf("The asset register is full (%d assets).\n", MAX_ASSETS);
        return;
    }
    while (1) {
        readRequiredString("Asset ID (e.g. A001): ", id, ASSET_ID_LEN);
        if (findAssetById(id) == -1)
            break;
        printf("  Error: an asset with ID %s already exists.\n", id);
    }
    readRequiredString("Asset name: ", name, ASSET_NAME_LEN);
    type  = chooseFromList("Asset type:", assetTypes, ASSET_TYPE_COUNT);
    value = readAmount("Purchase value (N$): ", 0);
    readRequiredString("Department: ", dept, ASSET_DEPT_LEN);
    cond  = chooseFromList("Condition:", conditions, CONDITION_COUNT);

    storeAsset(id, name, assetTypes[type], value, dept, conditions[cond]);
    printf("\nAsset %s added successfully.\n", name);
}

void displayAssets(void)
{
    int i;

    printHeader("ASSET REGISTER");
    if (assetCount == 0) {
        printf("No assets have been registered yet.\n");
        return;
    }
    printAssetHeader();
    for (i = 0; i < assetCount; i++)
        printAssetRow(i);
    printf("\nTotal assets: %d\n", assetCount);
}

void searchAsset(void)
{
    char term[ASSET_NAME_LEN];
    int option, i, found = 0;

    printHeader("SEARCH ASSET");
    if (assetCount == 0) {
        printf("No assets have been registered yet.\n");
        return;
    }
    printf("1. Asset ID (exact)\n");
    printf("2. Asset name (partial)\n");
    printf("3. Asset type (partial)\n");
    printf("4. Department (partial)\n");
    printf("5. Condition (partial)\n");
    option = readIntInRange("Choose search type: ", 1, 5);
    readRequiredString("Search for: ", term, ASSET_NAME_LEN);

    printf("\n");
    printAssetHeader();
    for (i = 0; i < assetCount; i++) {
        int match = 0;
        switch (option) {
            case 1: match = equalsIgnoreCase(assetId[i], term);   break;
            case 2: match = containsIgnoreCase(assetName[i], term);break;
            case 3: match = containsIgnoreCase(assetType[i], term);break;
            case 4: match = containsIgnoreCase(assetDept[i], term);break;
            case 5: match = containsIgnoreCase(assetCond[i], term);break;
        }
        if (match) {
            printAssetRow(i);
            found++;
        }
    }
    if (found == 0)
        printf("No matching asset found.\n");
    else
        printf("\n%d asset(s) found.\n", found);
}

void loadSampleAssets(void)
{
    storeAsset("A001", "Toyota Hilux Bakkie",   "Vehicle",   485000, "Roads",       "Good");
    storeAsset("A002", "Dell Laptop x10",       "Computer",  185000, "Finance",     "Excellent");
    storeAsset("A003", "Civic Centre",          "Building", 7500000, "Admin",       "Good");
    storeAsset("A004", "Water Pump Unit",       "Equipment", 320000, "Water",       "Fair");
    storeAsset("A005", "Council Boardroom Set", "Furniture",  68000, "Admin",       "Poor");
}

void assetMenu(void)
{
    int choice;

    do {
        printHeader("ASSET MANAGEMENT");
        printf("1. Add asset\n");
        printf("2. Display asset register\n");
        printf("3. Search for an asset\n");
        printf("4. Back to main menu\n");
        choice = readIntInRange("Enter your choice: ", 1, 4);

        switch (choice) {
            case 1: addAsset();      break;
            case 2: displayAssets(); break;
            case 3: searchAsset();   break;
            case 4: break;
        }
        if (choice != 4)
            pressEnter();
    } while (choice != 4);
}
