#include <stdio.h>
#include <string.h>

#define MAX_SIZE 10000 

void replaceWord(const char *str, const char *old_word, const char *new_word, char *result) {
    char *pos, temp[MAX_SIZE];
    int index = 0, old_word_len = strlen(old_word);
    strcpy(temp, str);
    while ((pos = strstr(temp, old_word)) != NULL) {
        int len = pos - temp;
        strncpy(result + index, temp, len);
        index += len;
        strcpy(result + index, new_word);
        index += strlen(new_word);
        strcpy(temp, pos + old_word_len); }
    strcpy(result + index, temp);
}

int main() {
    FILE *file;
    char file_name[100], old_word[50], new_word[50];
    char content[MAX_SIZE], new_content[MAX_SIZE];
    printf("Enter the file name: ");
    scanf("%s", file_name);
    printf("Enter the word to be replaced: ");
    scanf("%s", old_word);
    printf("Enter the replacement word: ");
    scanf("%s", new_word);
    file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Error! Could not open file.\n");
        return 0; }
    fread(content, sizeof(char), MAX_SIZE, file);
    fclose(file);
    replaceWord(content, old_word, new_word, new_content);
    file = fopen(file_name, "w");
    if (file == NULL) {
        printf("Error!Could not open file for writing.\n");
        return 0; }
    fprintf(file, "%s", new_content);
    fclose(file);
    printf("Word replaced done\n");
    return 0;
}
