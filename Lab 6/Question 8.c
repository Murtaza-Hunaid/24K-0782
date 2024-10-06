#include<stdio.h>
int main(){ 
  char i; 
  for(i = 'A' ; i <= 'E' ; i ++){
    if(i == 'A' || i == 'E'){
      printf("%c %c %c %c %c\n", i, i+1, i+2, i+3, i+4);}
    else if(i == 'B' || i == 'D'){
      printf("  %C   %c\n", i+1,i+4);}
    else {
      printf("    %C   \n", i+2);}}
}
