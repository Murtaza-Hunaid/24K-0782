#include<stdio.h>
#include<string.h>
void is_palindrome(char arr[], int index);
int main() {
    int i;
    char arr[5][20];
    printf("Enter your strings\n");
    for(i=0 ; i<5 ; i++) {
        printf("Enter string %d: ", i+1);
        scanf("%s", arr[i]); }
    printf("\n");
    for(int i=0 ; i<5 ; i++)
        is_palindrome(arr[i], i); }
    return 0;
}

void is_palindrome(char arr[], int index) {
    int flag=1, length=strlen(arr), i;
    for(i=0 ; i<(length/2) ; i++) {
        if(arr[i]!=arr[length-1-i]) {
           flag=0;
           break; } }
    if(flag) {
        printf("String %d is a palindrome\n", index+1); }
    else {
        printf("String %d is not a palindrome\n", index+1); }
}
