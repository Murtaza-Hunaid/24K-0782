#include<stdio.h>
void calculation(float num1, float num2, char operation);
int main(){
    float num1, num2;
    char op;
    printf("Enter your first number: ");
    scanf("%f", &num1);
    printf("Enter your second number: ");
    scanf("%f", &num2);
    printf("Enter the symbol of the operation to be performed: ");
    scanf(" %c", &operation);
    calculation(num1, num2, operation);
    return 0;
}

void calculation(float num1, float num2, char operation){
    if(op=='+') {
       printf("The result is %.2f", num1+num2); }
    else if(op=='-') {
       printf("The result is %.2f", num1-num2); }
    else if(op=='*') {
       printf("The result is %.2f", num1*num2); }
    else if(op=='/') {
       if(num2!=0) {
          printf("The result is %.2f", num1/num2); }
       else {
          printf("Math Error. Denominator(Number 2) should not be zero for division"); } }
    else {
       printf("Invalid symbol entered"); }
}
