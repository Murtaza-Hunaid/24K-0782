#include<stdio.h>
int main() {
    int length = 0;
    char str[100], *ptr, *rev, temp;
    printf("Enter a string: ");
    scanf("%s", str);
    ptr = str;
    while (*ptr != '\0') {
        length++;
        ptr++; }
    printf("The length of the string entered is: %d", length);
    ptr = str;               
    rev = str + length - 1;  
    while (ptr < rev) {
        temp = *ptr;
        *ptr = *rev;
        *rev = temp;
        ptr++;
        rev--; }
    printf("\nReversed String: %s", str);
    return 0;
}
