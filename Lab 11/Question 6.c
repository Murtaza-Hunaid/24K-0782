#include <stdio.h>

struct Address {
    char city[50];
    char zip_code[20];
};

struct Employee {
    char name[50];
    int id;
    float salary;
    struct Address address;
};

int main() {
    int n, i;
    FILE *file;
    printf("Enter number of employees: ");
    scanf("%d", &n);
    struct Employee employees[n];
    for (i = 0; i < n; i++) {
        printf("\nEnter details for employee %d:\n", i + 1);
        printf("Name: ");
        scanf(" %[^\n]", employees[i].name); 
        printf("ID: ");
        scanf("%d", &employees[i].id);
        printf("Salary: ");
        scanf("%f", &employees[i].salary);
        printf("City: ");
        scanf(" %[^\n]", employees[i].address.city); 
        printf("Zip Code: ");
        scanf(" %[^\n]", employees[i].address.zip_code); 
    }
    file = fopen("employees.dat", "wb");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return 1; }
    fwrite(employees, sizeof(struct Employee), n, file);
    fclose(file);
    printf("Employee data saved to file\n");
    file = fopen("employees.dat", "rb");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return 1; }
    printf("\nEmployee Details:\n");
    while (fread(&employees[0], sizeof(struct Employee), 1, file)) {
        for (i = 0; i < n; i++) {
            printf("\nName: %s\n", employees[i].name);
            printf("ID: %d\n", employees[i].id);
            printf("Salary: %.2f\n", employees[i].salary);
            printf("City: %s\n", employees[i].address.city);
            printf("Zip Code: %s\n", employees[i].address.zip_code); } }
    fclose(file);
    return 0;
}
