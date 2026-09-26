#include<stdio.h>
#include<string.h>
int main(){
    char destination[20]; char source[20];
    int n;
    printf("Enter your destination string: ");
    scanf("%s", destination);
    printf("Enter your source string: ");
    scanf("%s", source);
    printf("Enter the number of characters of source string to be concatenated: ");
    scanf("%d", &n);
    strncat(destination, source, n);
    printf("Concatenated String: %s", destination);
    return 0;
}
