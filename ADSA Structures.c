#include <stdio.h>

struct Employee {
    int empID;
    char name[50];
    char department[50];
    float basicSalary;
    float hra;
    float da;
    float grossSalary;
};

int main() {
    struct Employee emp[100], temp;
    int n, i, j;

    printf("Enter the number of employees: ");
    scanf("%d", &n);

    // Input employee details
    for(i = 0; i < n; i++) {
        printf("\nEmployee %d\n", i + 1);

        printf("Enter Employee ID: ");
        scanf("%d", &emp[i].empID);

        printf("Enter Name: ");
        scanf("%s", emp[i].name);

        printf("Enter Department: ");
        scanf("%s", emp[i].department);

        printf("Enter Basic Salary: ");
        scanf("%f", &emp[i].basicSalary);

        // Calculate HRA, DA and Gross Salary
        emp[i].hra = emp[i].basicSalary * 0.20;
        emp[i].da = emp[i].basicSalary * 0.15;
        emp[i].grossSalary = emp[i].basicSalary + emp[i].hra + emp[i].da;
    }

    // Sort employees by Gross Salary (Descending Order)
    for(i = 0; i < n - 1; i++) {
        for(j = i + 1; j < n; j++) {
            if(emp[i].grossSalary < emp[j].grossSalary) {
                temp = emp[i];
                emp[i] = emp[j];
                emp[j] = temp;
            }
        }
    }

    // Display employee details
    printf("\nEmployee Details Sorted by Gross Salary\n");
    printf("---------------------------------------------------------------\n");
    printf("ID\tName\tDept\tBasic\tHRA\tDA\tGross\n");
    printf("---------------------------------------------------------------\n");

    for(i = 0; i < n; i++) {
        printf("%d\t%s\t%s\t%.2f\t%.2f\t%.2f\t%.2f\n",
               emp[i].empID,
               emp[i].name,
               emp[i].department,
               emp[i].basicSalary,
               emp[i].hra,
               emp[i].da,
               emp[i].grossSalary);
    }

    return 0;
}