#include <stdio.h>
int main() {
    int A[3][3], B[3][3], result[3][3], subtract_result[3][3], i, j, k;
    printf("Enter elements of Matrix A (3x3):\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            scanf("%d", &A[i][j]); } }
    printf("Enter elements of Matrix B (3x3):\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            scanf("%d", &B[i][j]); } }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            result[i][j] = 0; 
            for (k = 0; k < 3; k++) {
                int temp = A[i][k] * B[k][j];
                result[i][j] = result[i][j] + temp; } } }
    printf("\nResultant Matrix (A * B):\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%d ", result[i][j]); }
        printf("\n"); }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            subtract_result[i][j] = A[i][j] - result[i][j]; } }
    printf("\nSubtraction of Resultant Matrix from Matrix A:\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%d ", subtract_result[i][j]); }
        printf("\n"); }
}
