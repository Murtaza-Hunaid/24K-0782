#include <stdio.h>

struct Company {
    char name[50];
    int year_established;
    char departments[5][50]; 
};

int main() {
    struct Company company;
    int j, i;
    printf("Enter company name: ");
    scanf(" %[^\n]", company.name); 
    printf("Enter year established: ");
    scanf("%d", &company.year_established);
    printf("Enter up to 5 departments (type 'end' to stop):\n");
    for (i = 0; i < 5; i++) {
        printf("Department %d: ", i + 1);
        scanf(" %[^\n]", company.departments[i]);
        if (strcmp(company.departments[i], "end") == 0) {
            break; } }
    printf("\nCompany Details:\n");
    printf("Name: %s\n", company.name);
    printf("Year Established: %d\n", company.year_established);
    printf("Departments:\n");
    for (j = 0; j < i; j++) {
        printf("%d. %s\n", j + 1, company.departments[j]); }
    return 0;
}
