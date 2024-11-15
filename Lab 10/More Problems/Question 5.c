#include <stdio.h>

void bubbleSort(int arr[], int size) {
    int temp, i; 
    if (size == 1) {
        return; }
    for (i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            temp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = temp; } }
    bubbleSort(arr, size - 1);
}

void displayArray(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]); }
    printf("\n");
}

int main() {
    int size, i;
    printf("Enter the size of the array: ");
    scanf("%d", &size);
    int arr[size];
    printf("Enter %d elements of the array: \n", size);
    for (i = 0; i < size; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", &arr[i]); }
    printf("\nOriginal array:\n");
    displayArray(arr, size);
    bubbleSort(arr, size); 
    printf("\nSorted array:\n");
    displayArray(arr, size);    
    return 0;
}
