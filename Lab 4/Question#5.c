#include<stdio.h>
int main(){
	char character;
	printf("Enter any Character: ");
	scanf("%c", &character);
	if(character >= 'a' && character <= 'z'){
		printf("%c is a small alphabet", character);} 
  else if(character >= 'A' && character <= 'Z'){
		printf("%c is capital letter", character);}
  else if(character >= '0' && character <= '9'){
		printf("%c is a digit", character);}
  else {
		printf("%c is a special character", character);}
	}
