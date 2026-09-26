#include <stdio.h>
int main() {
    int n, sum = 0;
    int *ptr;
    printf("Enter the size of the array: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the elements of the array below:\n");
    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i+1);
        scanf("%d", &arr[i]); }
    ptr = arr;
    for (int i = 0; i < n; i++) {
        sum += *(ptr + i); }
    printf("The sum of the elements in the array is %d.\n", sum);
    return 0;
}
