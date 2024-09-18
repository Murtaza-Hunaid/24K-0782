#include<stdio.h>
int main(){
	int num;
	printf("Enter any number: ");
	scanf("%d", &num);
	if (num > 0 && num%2 == 0 && num%10 == 0){
		printf("%d is acceptable", num);} 
  else{
		printf("%d is not acceptable", num);}
}
