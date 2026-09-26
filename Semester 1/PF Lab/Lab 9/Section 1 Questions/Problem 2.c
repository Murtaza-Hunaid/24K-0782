#include <stdio.h>
void EvenOrOdd(int number);
int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    EvenOrOdd(num);
    return 0;
}

void EvenOrOdd(int number) {
    if (number % 2 == 0) {
        printf("%d is even\n", number); } 
    else {
        printf("%d is odd\n", number); }
}
