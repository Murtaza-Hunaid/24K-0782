#include <stdio.h> 
int main() {
   int rows, i, j;
   printf("Enter the number of rows for the upper half of the diamond: ");
   scanf("%d", &rows);  
   for(i=1 ; i<=rows-1 ; i++) {
       for(j=1 ; j<=(rows+1)-i ; j++) {
           printf(" "); }
       for(j=1 ; j<=i ; j++) {
           printf("* "); }
       printf("\n");}
   for(i=1 ; i<=rows ; i++) {
       for(j=1 ; j<=i ; j++) {
           printf(" "); }
       for(j=1 ; j<=(rows+1)-i ; j++) {
           printf("* "); }
       printf("\n"); }
}
