#include<stdio.h>
int main() {
    int rows, i, j;
    printf("Enter the number of rows: ");
    scanf("%d", &rows);
    int arr[rows][rows]; 
    for(i=0 ; i<rows ; i++) {
        for(j=0 ; j<rows ; j++) {
            arr[i][j]=0; } }
    for(i=0 ; i<rows ; i++) {
        arr[i][0]=1; 
        for(j=1 ; j<=i ; j++) {
            arr[i][j] = arr[i-1][j-1] + arr[i-1][j]; } }
    for(i=1 ; i<=rows ; i++) {
        for(j=1 ; j<=(rows+1)-i ; j++) {
            printf(" "); }
        for(j=1 ; j<=i ; j++) {
            printf("%d ", arr[i-1][j-1]); }
        printf("\n"); }
}
