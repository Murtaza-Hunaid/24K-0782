#include<stdio.h>
int main() {
	int Num1, Num2, temp;
	printf("Enter first number: ");
	scanf("%d", &Num1);
	printf("Enter second number: ");
	scanf("%d", &Num2);
	temp = Num1;
	Num1 = Num2;
	Num2 = temp;
	printf("%d\n%d", Num1, Num2);
}