#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    int n;
    char *dyn_arr, full_name[100];
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
    printf("Dynamic Array = %s\n", dyn_arr);
    free(dyn_arr);
    return 0;
}
