#include <stdio.h>
int main() {
    float tax_rate, salary, tax, new_salary;
    printf("Enter the tax rate: ");
    scanf("%f", &tax_rate);
    printf("Enter the salary: ");
    scanf("%f", &salary);
    tax = salary * (tax_rate / 100);
    new_salary = salary - tax;
    printf("The tax you have to pay is: %.2f\n", tax);
    printf("Your net salary after paying tax is: %.2f\n", new_salary);
    return 0;
}
