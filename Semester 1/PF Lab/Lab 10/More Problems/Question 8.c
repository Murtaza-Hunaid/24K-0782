#include <stdio.h>

int linearSearch(int arr[], int size, int search_num, int currentIndex) {
    if (currentIndex == size) {
        return -1; }
    if (arr[currentIndex] == search_num) {
        return currentIndex; }
    return linearSearch(arr, size, search_num, currentIndex + 1);
}

int main() {
    int size, search_num, i;
    printf("Enter the size of the array: ");
    scanf("%d", &size);
    int arr[size];
    printf("Enter %d elements of the array:\n", size);
    for (i = 0; i < size; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", &arr[i]); }
    printf("Enter the number to search for: ");
    scanf("%d", &search_num);
    int result = linearSearch(arr, size, search_num, 0);
    if (result == -1) {
        printf("Element not found\n"); } 
    else {
        printf("Element found at index %d\n", result); }
    return 0;
}
