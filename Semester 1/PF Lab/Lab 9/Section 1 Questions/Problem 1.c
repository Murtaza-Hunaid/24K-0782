#include<stdio.h>
float product(float a, float b);
int main() {
    float num1, num2, result;
    printf("Enter the first number: ");
    scanf("%f", &num1);
    printf("Enter the second number: ");
    scanf("%f", &num2);
    result = product(num1,num2);
    printf("The product of the 2 numbers is %.2f", result);
    return 0;
}

float product(float a, float b) {
    return a * b;
}
