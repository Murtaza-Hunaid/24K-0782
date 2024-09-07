#include <stdio.h>
int main() {
    float fuel_avg;
    printf("Enter the car's fuel average in km per liter: ");
    scanf("%f", &fuel_avg);
    if (fuel_avg <= 0) {
        printf("Invalid input! Fuel average must be positive.")
    else
        float distance= 1207.0;  
        float forward_price= 118.0; 
        float return_price= 123.0;
        float fuel_consumed_forward = distance/fuel_avg;
        float fuel_consumed_return = distance/fuel_avg;
        float total_fuel_consumed = fuel_consumed_forward + fuel_consumed_return;
        float forward_cost = fuel_consumed_forward * forward_price;
        float return_cost = fuel_consumed_return * return_price;
        float total_fuel_price = forward_cost + return_cost;
        printf("Total fuel consumed in the entire trip in liters: %f liters \n", total_fuel_consumed);
        printf("Total fuel price for the entire trip: RS. %f \n", total_fuel_price);
 }
