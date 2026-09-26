#include<stdio.h>
int main(){ 
 float gpa;
 printf("Enter GPA: ");
 scanf("%f", &gpa);
 (gpa <= 4.0 && gpa >= 3.5) ? printf("Highest honors for semester") :
 (gpa < 3.5 && gpa >= 3.0) ? printf("Dean's list for semester") :
 (gpa < 3.0 && gpa >= 2.0) ? printf(" ") :
 (gpa < 2.0 && gpa >= 1.0) ? printf("On probation for next semester") :
 (gpa >= 0.0 && gpa <= 0.99) ? printf("Failed semester - registration suspended") :
 printf("Invalid GPA") :
 return 0;
}
