/* Do while is the suitable option as firstly, it gives the user a choice whether the user wants to continue or 
exit and secondly, the loop will run atleast once regardless if the condition inside while is true or not*/

#include<stdio.h>
int main(){
  int num, sum=0;
  do {
    printf("Enter a number: ");
    scanf("%d", &num);
    if(num == 0)
      break;
    sum = sum + num;
    printf("Current Sum: %d\n", sum);}
    while(num != 0);
}
