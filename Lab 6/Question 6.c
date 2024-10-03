#include<stdio.h>
int main(){
  int i=0;
  do {
    if (i == 0 || i == 5){
      printf("*       *\n");}
    else {
      printf("* * * * *\n");}
    i += 1;}
  while (i <= 5);
}
