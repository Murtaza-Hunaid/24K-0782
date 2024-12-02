#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    int n, id_length, i;
    char *dyn_arr, full_name[100], student_Id[100];
    printf("Enter the total number of characters in your full name: ");
    scanf("%d", &n);
    getchar(); 
    dyn_arr = (char *)malloc((n + 1) * sizeof(char));
    if (dyn_arr == NULL) {
        printf("Memory allocation failed\n");
        return 1; }
    printf("Enter your full name: ");
    fgets(full_name, sizeof(full_name), stdin);
    full_name[strcspn(full_name, "\n")] = '\0';  
    strcpy(dyn_arr, full_name);
    printf("Enter your student ID: ");
    fgets(student_Id, sizeof(student_Id), stdin);
    student_Id[strcspn(student_Id, "\n")] = '\0'; 
    id_length = strlen(student_Id);
    dyn_arr = (char *)realloc(dyn_arr, (n + id_length + 2) * sizeof(char));
    if (dyn_arr == NULL) {
        printf("Memory reallocation failed\n");
        return 1; }
    for (i = n; i >= 0; i--) {
        dyn_arr[i + id_length + 1] = dyn_arr[i]; }
    for (i = 0; i < id_length; i++) {
        dyn_arr[i] = student_Id[i]; }
    dyn_arr[id_length] = ' '; 
    printf("Dynamic Array = %s\n", dyn_arr);
    free(dyn_arr);
    return 0;
}
