#include<stdio.h>
int main(){
	int num, i, prime = 1;
  	printf("Enter a number: ");
  	scanf("%d", &num);
  	if(num <= 1){
		printf("The number entered is not a prime number.");}
	else {
    		for(i=2 ; i<num ; i++){
      			if(num % i == 0){
         			prime = 0;
          			break;} 
    	if (prime == 1){
        	printf("%d is a prime number\n", num);
        	printf("Fibonacci series up to %d:\n", num);
        	int a = 0, b = 1;
	        while (a <= num){
            		printf("%d ", a);
            		int temp = a;
            		a = b;
            		b = temp + b;}}
	else {
        	printf("%d is not a prime number", num);}
}
