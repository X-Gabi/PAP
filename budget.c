#include <stdio.h>
#include <string.h>
#include "budget.h"
#include "utils.h"

#define MAX_BUDGETS 50

typedef struct {
    char department[50];
    float allocatedBudget;
    float expenditure;
} Budget;

static Budget budgets[MAX_BUDGETS];
static int budgetCount = 0;

static void addBudget(void);
static void displayBudgets(void);
static void showExceededBudgets(void);

void loadSampleBudgets(void)
{
    strcpy(budgets[0].department, "Finance");
    budgets[0].allocatedBudget = 500000;
    budgets[0].expenditure = 420000;

    strcpy(budgets[1].department, "Human Resources");
    budgets[1].allocatedBudget = 250000;
    budgets[1].expenditure = 300000;

    budgetCount = 2;
}

static void addBudget(void)
{
    if (budgetCount >= MAX_BUDGETS) {
        printf("Budget storage full.\n");
        return;
    }

    printf("Department Name: ");
    scanf(" %[^\n]", budgets[budgetCount].department);

    printf("Allocated Budget: ");
    scanf("%f", &budgets[budgetCount].allocatedBudget);

    printf("Expenditure: ");
    scanf("%f", &budgets[budgetCount].expenditure);

    budgetCount++;
    printf("Budget added successfully.\n");
}

static void displayBudgets(void)
{
    float remaining;

    printf("\n========== BUDGET REPORT ==========\n");

    for(int i = 0; i < budgetCount; i++) {
        remaining = budgets[i].allocatedBudget - budgets[i].expenditure;

        printf("\nDepartment: %s\n", budgets[i].department);
        printf("Allocated Budget: N$ %.2f\n", budgets[i].allocatedBudget);
        printf("Expenditure: N$ %.2f\n", budgets[i].expenditure);
        printf("Remaining Budget: N$ %.2f\n", remaining);

        if(remaining >= 0)
            printf("Status: WITHIN BUDGET\n");
        else
            printf("Status: EXCEEDED BUDGET\n");
    }
}

static void showExceededBudgets(void)
{
    int found = 0;

    printf("\nDepartments Exceeding Budget\n");

    for(int i = 0; i < budgetCount; i++) {
        if(budgets[i].expenditure > budgets[i].allocatedBudget) {
            printf("- %s\n", budgets[i].department);
            found = 1;
        }
    }

    if(!found)
        printf("No departments exceeded budget.\n");
}

void budgetMenu(void)
{
    int choice;

    do {
        printf("\n========== BUDGET MANAGEMENT ==========\n");
        printf("1. Add Budget\n");
        printf("2. Display Budgets\n");
        printf("3. Departments Exceeding Budget\n");
        printf("4. Return to Main Menu\n");

        choice = readIntInRange("Enter your choice: ", 1, 4);

        switch(choice) {
            case 1: addBudget(); break;
            case 2: displayBudgets(); break;
            case 3: showExceededBudgets(); break;
        }

    } while(choice != 4);
}
