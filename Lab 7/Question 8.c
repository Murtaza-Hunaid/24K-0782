#include <stdio.h>
int main() {
    char expression[100], operator = '+', ch;
    int result = 0, temp = 0, valid = 1, i = 0; 
    printf("Enter the expression: ");
    while ((ch = getchar()) != '\n' && i < 100) {
        expression[i++] = ch; }
    expression[i] = '\0'; 
    for (i = 0; expression[i] != '\0'; i++) {
        if (expression[i] >= '0' && expression[i] <= '9') {
            temp = temp * 10 + (expression[i] - '0'); } 
        else if (expression[i] == '+' || expression[i] == '-') {
            if (operator == '+') {
                result += temp; } 
            else if (operator == '-') {
                result -= temp; }
            temp = 0;
            operator = expression[i]; } 
        else {
            valid = 0;
            break; } }
    if (operator == '+') {
        result += temp; } 
    else if (operator == '-') {
        result -= temp; }
    if (valid) {
        printf("Result: %d\n", result); } 
    else {
        printf("Invalid expression\n"); }
    return 0;
}
