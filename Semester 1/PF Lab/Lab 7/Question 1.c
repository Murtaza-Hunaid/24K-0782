#include <stdio.h>
int main(){
    int arr[6], temp;
    printf("Enter 6 values:\n");
    for (int i = 0; i < 6; i++) {
        printf("Value %d: ", i + 1);
        scanf("%d", &arr[i]);}
    temp = arr[5];
    for (int i = 5; i > 0; i--) {
        arr[i] = arr[i - 1];}
    arr[0] = temp;
    printf("Output: {");
    for (int i = 0; i < 6; i++) {
        printf("%d", arr[i]);
        if (i < 5) {
            printf(", ");}}
    printf("}\n");
}
