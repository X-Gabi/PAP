#include <stdio.h>
#include <string.h>
#include "Assets.h"

#define MAX_ASSETS 50

struct Asset
{
    int assetID;
    char assetName[50];
    char assetType[50];
    float purchaseValue;
    char department[50];
    char condition[30];
};

struct Asset assets[MAX_ASSETS];
int assetCount = 0;

void addAsset(void)
{
    if(assetCount >= MAX_ASSETS)
    {
        printf("Asset storage is full.\n");
        return;
    }

    printf("\nEnter Asset ID: ");
    scanf("%d", &assets[assetCount].assetID);

    printf("Enter Asset Name: ");
    scanf(" %[^\n]", assets[assetCount].assetName);

    printf("Enter Asset Type: ");
    scanf(" %[^\n]", assets[assetCount].assetType);

    printf("Enter Purchase Value: ");
    scanf("%f", &assets[assetCount].purchaseValue);

    printf("Enter Department: ");
    scanf(" %[^\n]", assets[assetCount].department);

    printf("Enter Condition: ");
    scanf(" %[^\n]", assets[assetCount].condition);

    assetCount++;

    printf("Asset added successfully.\n");
}

void displayAssets(void)
{
    int i;

    if(assetCount == 0)
    {
        printf("\nNo assets available.\n");
        return;
    }

    for(i = 0; i < assetCount; i++)
    {
        printf("\n=====================\n");
        printf("Asset ID: %d\n", assets[i].assetID);
        printf("Asset Name: %s\n", assets[i].assetName);
        printf("Asset Type: %s\n", assets[i].assetType);
        printf("Purchase Value: %.2f\n", assets[i].purchaseValue);
        printf("Department: %s\n", assets[i].department);
        printf("Condition: %s\n", assets[i].condition);
    }
}

void searchAsset(void)
{
    int id;
    int i;
    int found = 0;

    printf("\nEnter Asset ID to search: ");
    scanf("%d", &id);

    for(i = 0; i < assetCount; i++)
    {
        if(assets[i].assetID == id)
        {
            printf("\nAsset Found\n");
            printf("Asset ID: %d\n", assets[i].assetID);
            printf("Asset Name: %s\n", assets[i].assetName);
            printf("Asset Type: %s\n", assets[i].assetType);
            printf("Purchase Value: %.2f\n", assets[i].purchaseValue);
            printf("Department: %s\n", assets[i].department);
            printf("Condition: %s\n", assets[i].condition);

            found = 1;
            break;
        }
    }

    if(found == 0)
    {
        printf("Asset not found.\n");
    }
}

void assetMenu(void)
{
    int choice;

    do
    {
        printf("\n========================\n");
        printf("ASSET MANAGEMENT SYSTEM\n");
        printf("========================\n");
        printf("1. Add Asset\n");
        printf("2. Display Assets\n");
        printf("3. Search Asset\n");
        printf("4. Exit\n");
        printf("Enter choice: ");

        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addAsset();
                break;

            case 2:
                displayAssets();
                break;

            case 3:
                searchAsset();
                break;

            case 4:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }
    }
    while(choice != 4);
}
