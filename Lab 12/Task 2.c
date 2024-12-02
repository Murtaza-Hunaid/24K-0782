#include <stdio.h>

void swaped(int *aPtr, int *bPtr, int *cPtr);

int main() {
    int a, b, c;
    printf("Enter the values of a, b, and c: ");
    scanf("%d %d %d", &a, &b, &c);
    printf("Values before swapping:\n");
    printf("a = %d , b = %d , c = %d", a, b, c);
    swaped(&a, &b, &c);
    printf("\nValue after swapping:\n");
    printf("a = %d, b = %d , c = %d\n", a, b, c);
    return 0;
}

void swaped(int *aPtr, int *bPtr, int *cPtr) {
    int temp;
    temp = *bPtr;
    *bPtr = *aPtr;
    *aPtr = *cPtr;
    *cPtr = temp;
}
