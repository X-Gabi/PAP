#include <stdio.h>

typedef struct { int id; char name[50]; char dept[30]; float net; } Employee;
Employee employees[100] = {{1,"Gabi","Finance",15000}};
int empCount=1;

typedef struct { int id; char dept[30]; float allocated, expenditure, remaining; } Budget;
Budget budgets[100] = {{1,"Finance",50000,60000,-10000}};
int budCount=1;

typedef struct { int id; char name[50]; char town[30]; } Supplier;
Supplier suppliers[100] = {{1,"NBC","Windhoek"}};
int supCount=1;

typedef struct { int id; char name[50]; float value; char department[30]; } Asset;
Asset assets[100] = {{1,"Laptop",12000,"IT"}};
int assetCount=1;

void clearBuffer(){ int c; while((c=getchar())!='\n' && c!=EOF); }

void employeeReport(){
    if(empCount==0){ printf("No employees!\n"); return; }
    float total=0, high=employees[0].net, low=employees[0].net;
    for(int i=0;i<empCount;i++){ total+=employees[i].net; }
    printf("\nTotal: %d Avg: N$%.2f\n", empCount, total/empCount);
}
void budgetReport(){ printf("\nBudget report working\n"); }
void supplierReport(){ printf("\nSupplier report working\n"); }
void assetReport(){ printf("\nAsset report working\n"); }

int main(){ employeeReport(); budgetReport(); 
      return 0;
}
