#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *first_file = fopen("first.txt", "w");
    if (first_file == NULL) {
        perror("Error! ");
        return 1; }
    fprintf(first_file, "My Name is Murtaza.\n");
    fclose(first_file);
    first_file = fopen("first.txt", "r");
    if (first_file == NULL) {
        perror("Error!");
        return 1; }
    FILE *second_file = fopen("second.txt", "w");
    if (second_file == NULL) {
        perror("Error!");
        fclose(first_file);
        return 1; }
    char ch;
    while ((ch = fgetc(first_file)) != EOF) {
        fputc(ch, second_file); }
    fclose(first_file);
    fclose(second_file);
    printf("Date Copied\n");
    return 0; 
}
