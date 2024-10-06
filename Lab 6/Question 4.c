#include <stdio.h>
int main(){
	int num, sum = 0, temp, digit;
   	printf("Enter a number: ");
    	scanf("%d", &num);
    	temp = num;
    	while (temp != 0){
        	digit = temp % 10;
        	sum = sum + (digit * digit * digit);
        	temp = temp / 10;}
   	if (sum == num){
        	printf("%d is an Armstrong number\n", num);}
    	else {
        	printf("%d is not an Armstrong number\n", num);}
}
