#include<stdio.h>
int main(){
	int num, isPrime=1;
	printf("Enter any number: ");
	scanf("%d", &num);
	
	for (int i=2; i<num; i++){
		if(num%i==0){
			isPrime = 0;
		}
	}
	if (isPrime){
		printf("Number is Prime...");
	}else{
		printf("Number is not Prime...");
	}
	
}
