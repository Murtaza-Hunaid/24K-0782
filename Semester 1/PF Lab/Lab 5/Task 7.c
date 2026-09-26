#include<stdio.h>
int main(){
	int num;
	printf("Enter Number: ");
	scanf("%d",&num);
	(num%10==0) ? printf("Last Digit is Zero") : printf("Last Digit is Non-Zero");
}
