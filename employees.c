#include <stdio.h>
#include <string.h>
#include "employees.h"
#include "utils.h"

/* Simplified monthly payroll rules (N$) - assumptions made for this project. */
#define TAX_LIMIT_1  8000.00    /* no tax up to this gross salary          */
#define TAX_LIMIT_2  20000.00   /* second band ends here                   */
#define TAX_RATE_1   0.18       /* tax rate on the band 8,000 - 20,000     */
#define TAX_RATE_2   0.25       /* tax rate above 20,000                   */
#define SSC_RATE     0.009      /* social security contribution (0.9%)     */

/* Employee records are stored in parallel arrays (same index = same person). */
static char   empId[MAX_EMPLOYEES][EMP_ID_LEN];
static char   empName[MAX_EMPLOYEES][EMP_NAME_LEN];
static char   empDept[MAX_EMPLOYEES][EMP_DEPT_LEN];
static char   empTitle[MAX_EMPLOYEES][EMP_TITLE_LEN];
static double empBasic[MAX_EMPLOYEES];
static double empHousing[MAX_EMPLOYEES];
static double empTransport[MAX_EMPLOYEES];
static double empOther[MAX_EMPLOYEES];
static int    empCount = 0;

/* ------------------------------------------------------------------ */
/* Helpers                                                             */
/* ------------------------------------------------------------------ */

int findEmployeeById(const char *id)
{
    int i;
    for (i = 0; i < empCount; i++) {
        if (equalsIgnoreCase(empId[i], id))
            return i;
    }
    return -1;
}

int getEmployeeCount(void)            { return empCount; }
double getEmployeeGross(int index)    { return calculateGross(index); }
const char *getEmployeeName(int index){ return empName[index]; }

static void storeEmployee(const char *id, const char *name, const char *dept,
                          const char *title, double basic, double housing,
                          double transport, double other)
{
    strcpy(empId[empCount], id);
    strcpy(empName[empCount], name);
    strcpy(empDept[empCount], dept);
    strcpy(empTitle[empCount], title);
    empBasic[empCount]     = basic;
    empHousing[empCount]   = housing;
    empTransport[empCount] = transport;
    empOther[empCount]     = other;
    empCount++;
}

static void printEmployeeHeader(void)
{
    printf("%-8s %-22s %-14s %-16s %12s\n",
           "ID", "Name", "Department", "Job Title", "Gross (N$)");
    printLine('-', LINE_WIDTH);
}

static void printEmployeeRow(int i)
{
    printf("%-8.8s %-22.22s %-14.14s %-16.16s %12.2f\n",
           empId[i], empName[i], empDept[i], empTitle[i], calculateGross(i));
}

/* ------------------------------------------------------------------ */
/* Calculations                                                        */
/* ------------------------------------------------------------------ */

double calculateGross(int index)
{
    return empBasic[index] + empHousing[index] + empTransport[index] + empOther[index];
}

double calculateTax(double gross)
{
    if (gross <= TAX_LIMIT_1)
        return 0.0;
    else if (gross <= TAX_LIMIT_2)
        return (gross - TAX_LIMIT_1) * TAX_RATE_1;
    else
        return (TAX_LIMIT_2 - TAX_LIMIT_1) * TAX_RATE_1
               + (gross - TAX_LIMIT_2) * TAX_RATE_2;
}

double calculateSocialSecurity(double gross)
{
    return gross * SSC_RATE;
}

double calculateNetSalary(double gross, double tax, double ssc)
{
    return gross - tax - ssc;
}

static void showSalaryInfo(int i)
{
    double gross = calculateGross(i);
    double tax   = calculateTax(gross);
    double ssc   = calculateSocialSecurity(gross);
    double net   = calculateNetSalary(gross, tax, ssc);

    printHeader("SALARY INFORMATION");
    printf("Employee ID   : %s\n", empId[i]);
    printf("Name          : %s\n", empName[i]);
    printf("Department    : %s\n", empDept[i]);
    printf("Job Title     : %s\n", empTitle[i]);
    printLine('-', LINE_WIDTH);
    printf("%-26s N$ %12.2f\n", "Basic salary", empBasic[i]);
    printf("%-26s N$ %12.2f\n", "Housing allowance", empHousing[i]);
    printf("%-26s N$ %12.2f\n", "Transport allowance", empTransport[i]);
    printf("%-26s N$ %12.2f\n", "Other allowance", empOther[i]);
    printf("%-26s N$ %12.2f\n", "GROSS SALARY", gross);
    printLine('-', LINE_WIDTH);
    printf("%-26s N$ %12.2f\n", "Income tax (estimate)", tax);
    printf("%-26s N$ %12.2f\n", "Social security (0.9%)", ssc);
    printf("%-26s N$ %12.2f\n", "Total deductions", tax + ssc);
    printLine('-', LINE_WIDTH);
    printf("%-26s N$ %12.2f\n", "NET SALARY", net);
}

/* ------------------------------------------------------------------ */
/* Menu operations                                                     */
/* ------------------------------------------------------------------ */

void addEmployee(void)
{
    char id[EMP_ID_LEN], name[EMP_NAME_LEN], dept[EMP_DEPT_LEN], title[EMP_TITLE_LEN];
    double basic, housing, transport, other;

    printHeader("ADD EMPLOYEE");
    if (empCount >= MAX_EMPLOYEES) {
        printf("The employee list is full (%d employees).\n", MAX_EMPLOYEES);
        return;
    }

    while (1) {
        readRequiredString("Employee ID (e.g. E001): ", id, EMP_ID_LEN);
        if (findEmployeeById(id) == -1)
            break;
        printf("  Error: an employee with ID %s already exists.\n", id);
    }
    readRequiredString("Full name: ", name, EMP_NAME_LEN);
    readRequiredString("Department: ", dept, EMP_DEPT_LEN);
    readRequiredString("Job title: ", title, EMP_TITLE_LEN);
    basic     = readAmount("Basic salary (N$ per month): ", 0);
    housing   = readAmount("Housing allowance (N$): ", 1);
    transport = readAmount("Transport allowance (N$): ", 1);
    other     = readAmount("Other allowance (N$): ", 1);

    storeEmployee(id, name, dept, title, basic, housing, transport, other);
    printf("\nEmployee %s added successfully.\n", name);
}

void displayEmployees(void)
{
    int i;

    printHeader("EMPLOYEE LIST");
    if (empCount == 0) {
        printf("No employees have been recorded yet.\n");
        return;
    }
    printEmployeeHeader();
    for (i = 0; i < empCount; i++)
        printEmployeeRow(i);
    printf("\nTotal employees: %d\n", empCount);
}

void searchEmployee(void)
{
    char term[EMP_NAME_LEN];
    int option, i, found = 0;

    printHeader("SEARCH EMPLOYEE");
    if (empCount == 0) {
        printf("No employees have been recorded yet.\n");
        return;
    }
    printf("1. Search by Employee ID (exact)\n");
    printf("2. Search by name (partial)\n");
    printf("3. Search by department (partial)\n");
    option = readIntInRange("Choose search type: ", 1, 3);
    readRequiredString("Search for: ", term, EMP_NAME_LEN);

    printf("\n");
    printEmployeeHeader();
    for (i = 0; i < empCount; i++) {
        int match = 0;
        if (option == 1)
            match = equalsIgnoreCase(empId[i], term);
        else if (option == 2)
            match = containsIgnoreCase(empName[i], term);
        else
            match = containsIgnoreCase(empDept[i], term);

        if (match) {
            printEmployeeRow(i);
            found++;
        }
    }
    if (found == 0)
        printf("No matching employee found.\n");
    else
        printf("\n%d employee(s) found.\n", found);
}

void calculateSalary(void)
{
    char id[EMP_ID_LEN];
    int index;

    printHeader("CALCULATE EMPLOYEE SALARY");
    if (empCount == 0) {
        printf("No employees have been recorded yet.\n");
        return;
    }
    readRequiredString("Enter Employee ID: ", id, EMP_ID_LEN);
    index = findEmployeeById(id);
    if (index == -1) {
        printf("No employee with ID %s was found.\n", id);
        return;
    }
    showSalaryInfo(index);
}

void loadSampleEmployees(void)
{
    storeEmployee("E001", "Ndapewa Shikongo", "Finance",     "Accountant",     14000, 3500, 1200, 500);
    storeEmployee("E002", "Johannes Amutenya","Engineering", "Civil Engineer", 22000, 5000, 1800, 0);
    storeEmployee("E003", "Maria Haufiku",    "Health",      "Health Officer", 11000, 2500, 900,  300);
    storeEmployee("E004", "Petrus Nghidinwa", "Finance",     "Clerk",           7000, 1500, 600,  0);
    storeEmployee("E005", "Selma Kandjii",    "Water",       "Supervisor",     16500, 4000, 1500, 750);
    storeEmployee("E006", "Daniel Uushona",   "Roads",       "Foreman",         9500, 2000, 1000, 0);
}

void employeeMenu(void)
{
    int choice;

    do {
        printHeader("EMPLOYEE MANAGEMENT");
        printf("1. Add employee\n");
        printf("2. Display all employees\n");
        printf("3. Search for an employee\n");
        printf("4. Calculate employee salary\n");
        printf("5. Back to main menu\n");
        choice = readIntInRange("Enter your choice: ", 1, 5);

        switch (choice) {
            case 1: addEmployee();      break;
            case 2: displayEmployees(); break;
            case 3: searchEmployee();   break;
            case 4: calculateSalary();  break;
            case 5: break;
        }
        if (choice != 5)
            pressEnter();
    } while (choice != 5);
}
