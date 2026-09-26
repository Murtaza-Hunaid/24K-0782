#include <stdio.h>
#include <string.h>
void reverse_string(char str[], char reversed[]);
int main() {
    char input[100], reversed[100];
    printf("Enter a string to reverse: ");
    scanf("%s", input);
    reverse_string(input, reversed);
    printf("Reversed string: %s\n", reversed);
    return 0;
}

void reverse_string(char str[], char reversed[]) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        reversed[i] = str[len - 1 - i]; }
    reversed[len] = '\0';
}
