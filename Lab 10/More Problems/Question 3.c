#include <stdio.h>
#define MAX_TEMPERATURE 50.0

void checkTemperature(float temperature) {
    static int exceed_count = 0;
    if (temperature > MAX_TEMPERATURE) {
        exceed_count++;
        printf("Temperature %.2f°C exceeds the maximum allowable limit of %.2f°C.\n", temperature, MAX_TEMPERATURE); } 
    else {
        printf("Temperature %.2f°C is within the allowable limit.\n", temperature); }
    printf("Number of times temperatures exceeded the limit: %d\n", exceed_count);
}

int main() {
    float inp_temp;
    char continuee;
    do {
        printf("Enter a temperature in Celsius: ");
        scanf("%f", &inp_temp);
        checkTemperature(inp_temp);
        printf("Do you want to enter another temperature? (y/n): ");
        scanf(" %c", &continuee); } 
    while (continuee == 'y' || continuee == 'Y');
}
