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
       			else {
         			continue;}}
