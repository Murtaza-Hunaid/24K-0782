#include <stdio.h>
void max_and_min(int arr[], int size, int *max, int *min);
int main() {
    int size, max, min, i;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &size);
    int arr[size];
    printf("Enter the elements of the array:\n");
    for (i = 0; i < size; i++) {
        scanf("%d", &arr[i]); }
    max_and_min(arr, size, &max, &min);
    printf("The maximum element is: %d\n", max);
    printf("The minimum element is: %d\n", min);
    return 0;
}

void max_and_min(int arr[], int size, int *max, int *min) {
    *max = arr[0];
    *min = arr[0];
    int i;
    for (i = 1; i < size; i++) {
        if (arr[i] > *max) {
            *max = arr[i]; }
        if (arr[i] < *min) {
            *min = arr[i]; } }
}
