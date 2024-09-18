#include<stdio.h>

int main(){
	float amount, saved_amount, amount_after_discount, discount, discounted_price;
	printf("Enter cost of items: ");
	scanf("%f", &amount);
	if (amount >= 500 && amount < 2000){
		discount = 5.0/100.0;}
	else if (amount >= 2000 && amount < 4000){
		discount = 10.0/100.0;}
	else if (amount >= 4000 && amount < 6000){
		discount = 20.0/100.0;}
	else if (amount >= 6000){
		discount = 35.0/100.0;}
	else{
		printf("Invalid Input");}
	discounted_price = amount * discount;
	total = amount - discounted_price;
	saved = amount - total;
	printf("Actual Amount: %.2f\n", amount);
	printf("Saved Amount: %.2f\n", saved);
	printf("Total Amount after discount: %.2f\n", total);
}
