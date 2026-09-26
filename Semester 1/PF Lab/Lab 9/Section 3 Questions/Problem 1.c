#include <stdio.h>
#include <string.h>
int main() {
    char words[5][20] = {"cat", "dog", "gorilla", "panda", "wolf"};
    char input[20];
    int found = 0, i;
    printf("Enter a word to search: ");
    scanf("%s", input);
    for (i = 0; i < 5; i++) {
        if (strcmp(words[i], input) == 0) {
            found = 1;
            break; } }
    if (found) {
        printf("Found\n"); } 
    else {
        printf("Not Found\n"); }
    return 0;
}
