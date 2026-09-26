#include <stdio.h>
int main() {
    int start, end, is_prime, i, j;    
    printf("Enter the start of the range: ");
    scanf("%d", &start);
    printf("Enter the end of the range: ");
    scanf("%d", &end);
    printf("Prime numbers between %d and %d are:\n", start, end);
    for (i = start; i <= end; i++) {
        is_prime = 1; 
        if (i >= 2) {
            for (j = 2; j * j <= i && is_prime; j++) {
                if (i % j == 0) {
                    is_prime = 0; } }
            if (is_prime) {
                printf("%d ", i); } } }
    printf("\n");
}
