#include <stdio.h>
int main() {
    int mat[3][3], is_saddle_point, i, j, k;
    printf("Enter the elements of the 3x3 matrix:\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            scanf("%d", &mat[i][j]); } }
    printf("Saddle Point(s) in the matrix:\n");
    for (i = 0; i < 3; i++) {
        int min_row = mat[i][0];
        int col_index = 0;
        for (j = 1; j < 3; j++) {
            if (mat[i][j] < min_row) {
                min_row = mat[i][j];
                col_index = j; } }
        is_saddle_point = 1; 
        for (k = 0; k < 3; k++) {
            if (mat[k][col_index] > min_row) {
                is_saddle_point = 0; 
                break; } }
        if (is_saddle_point) {
            printf("Saddle Point: %d at position (%d, %d)\n", min_row, i, col_index); } }
}
