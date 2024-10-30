#include <stdio.h>
int main() {
    int n, start, even, odd, i, j;
    printf("Enter the value of n (number of pairs): ");
    scanf("%d", &n);
    printf("Enter the starting number: ");
    scanf("%d", &start);
    int arr[2][n][2];
    if (start % 2 == 0) {
        even = start;
        odd = start - 1; } 
    else {
        odd = start;
        even = start - 1; }
    for (i = 0; i < n; i++) {   
        for (j = 0; j < 2; j++) {
            arr[0][i][j] = even;
            even -= 2;
            arr[1][i][j] = odd;
            odd -= 2; } }
    printf("\nEven Array [0]:\n");
    for (i = 0; i < n; i++) {
        printf("{ ");
        for (j = 0; j < 2; j++) {
            printf("%d ", arr[0][i][j]); }
        printf("}\n"); }
    printf("\nOdd Array [1]:\n");
    for (i = 0; i < n; i++) {
        printf("{ ");
        for (j = 0; j < 2; j++) {
            printf("%d ", arr[1][i][j]); }
        printf("}\n"); }
}
