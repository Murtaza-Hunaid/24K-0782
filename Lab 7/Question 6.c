#include <stdio.h>
int main() {
    int arr[10], freq[100] = {0}, valid_input;
    printf("Enter 10 integer numbers between 0 and 99:\n");
    for (int i = 0; i < 10; i++) {
        valid_input = 0;
        while (!valid_input) { 
            printf("Enter number %d: ", i+1);
            scanf("%d", &arr[i]);
            if (arr[i] >= 0 && arr[i] <= 99) {
                freq[arr[i]]++;
                valid_input = 1; } 
            else {
                printf("Error! Invalid input, enter a number between 0 and 99\n"); } } }
    printf("\nFrequency of numbers entered:\n");
    for (int j = 0; j < 100; j++) {
        if (freq[j] > 0) {
            printf("Number %d: %d times\n", j, freq[j]); } }
}
