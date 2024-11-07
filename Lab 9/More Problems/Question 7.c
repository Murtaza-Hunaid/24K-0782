#include <stdio.h>
#include <string.h>
void arrange_in_order(char words[][100], int n);
int main() {
    int n, i;
    printf("Enter the number of words: ");
    scanf("%d", &n);
    getchar(); 
    char words[n][100];
    for (i = 0; i < n; i++) {
        printf("Enter word %d: ", i + 1);
        fgets(words[i], 100, stdin);
        words[i][strcspn(words[i], "\n")] = '\0'; }
    arrange_in_order(words, n);
    return 0;
}

void arrange_in_order(char words[][100], int n) {
    char temp[100];
    int i, j;
    for (i = 0; i < n - 1; i++) { 
        for (j = 0; j < n - i - 1; j++) { 
            if (words[j][0] > words[j + 1][0]) {
                strcpy(temp, words[j]);
                strcpy(words[j], words[j + 1]);
                strcpy(words[j + 1], temp); } } }
    printf("The ordered list of words is as follows: \n");
    for (int i = 0; i < n; i++) {
        printf("%s\t", words[i]); }
}
