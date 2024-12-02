#include <stdio.h>
#include <stdlib.h>
int main() {
    int *arr;
    int n, new_size, i, largest_num;
    printf("Enter the initial size of the array: ");
    scanf("%d", &n);
    arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1; }
    printf("Enter %d elements for the array:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]); }
    largest_num = arr[0];
    for (i = 1; i < n; i++) {
        if (arr[i] > largest_num) {
            largest_num = arr[i]; } }
    printf("The largest number in the array is: %d\n", largest_num);
    printf("Enter the new size of the array: ");
    scanf("%d", &new_size);
    arr = (int *)realloc(arr, new_size * sizeof(int));
    if (arr == NULL) {
        printf("Memory reallocation failed\n");
        return 1; }
    if (new_size > n) {
        printf("Enter %d additional elements for the array:\n", new_size - n);
        for (i = n; i < new_size; i++) {
            scanf("%d", &arr[i]); } }

    largest_num = arr[0];
    for (i = 1; i < new_size; i++) {
        if (arr[i] > largest_num) {
            largest_num = arr[i]; } }
    printf("The largest number in the resized array is: %d\n", largest_num);
    free(arr);
    return 0;
}
