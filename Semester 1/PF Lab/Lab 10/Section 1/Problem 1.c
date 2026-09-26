#include <stdio.h>
int sumOfDigits(int n);
int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);
    if (number < 0) {
        number = -number; }
    printf("The sum of the digits is: %d\n", sumOfDigits(number));
    return 0;
}

int sumOfDigits(int n) {
    if (n == 0) {
        return 0;
    }
    return (n % 10) + sumOfDigits(n / 10); 
}
