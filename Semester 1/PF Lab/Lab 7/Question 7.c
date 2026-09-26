#include <stdio.h>
int main() {
    int repeated_number = 0, size, index = 0, current_index = 0;
    printf("Enter the size of the array: ");
    scanf("%d", &size);    
    int arr[size];
    for (int i = 0; i < size; i++) {
        printf("Enter number %d: ", i+1);
        scanf("%d", &arr[i]); }
    while (index < size) {
        current_index = index + 1;
        while (current_index < size) {
            if (arr[index] == arr[current_index]) {
                repeated_number = arr[index];
                break; }
            current_index++; }
        if (repeated_number != 0) {
            break; }
        index++; }
    if (repeated_number != 0) {
        printf("Number %d occurs more than once\n", repeated_number); } 
    else {
        printf("No repeated number\n"); }
}
