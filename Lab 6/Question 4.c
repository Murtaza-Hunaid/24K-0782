#include<stdio.h>
#include<math.h>
int main(){
	int num, digit=0, sum=0, exp = 3;
	
	printf("Enter Number to check if its ARMSTRONG or NOT: ");
	scanf("%d",&num);
	int temp = num;
	while(temp>0){
		digit = temp%10;
		sum += pow(digit, exp);
		temp/=10;
	}
	if (sum == num)
		printf("Number is ARMSTRONG...");
	else
		printf("Number is not ARMSTRONG...");
	
}
