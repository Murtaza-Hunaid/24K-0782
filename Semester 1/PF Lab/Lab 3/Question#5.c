#include<stdio.h>
int main(){
    float principal, rate, time, simple_interest;
    printf("Enter the principal amount between 100 Rs and 1000000 Rs: ");
    scanf("%f", &principal);
    printf("Enter the rate of interest between 5% and 10%: ");
    scanf("%f", &rate);
    printf("Enter the time period in years between 1 year and 10 years: ");
    scanf("%f", &time);
    if (principal < 100 || principal > 1000000 || rate < 5 || rate > 10 || time < 1 || time > 10)
        printf("Invalid input, try again");
    else
        simple_interest = (principal * rate * time) / 100;
        printf("The Simple Interest is: %.2f Rs\n", simple_interest);
}
