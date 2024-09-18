#include<stdio.h>

int main(){
	int customer_id;
	char customer_name[20];
	float unit_consumed, unit_charge, total_bill, surcharge_amount = 0;
	
	printf("Enter Customer Id: ");
	scanf("%d", &customer_id);
	printf("Enter Customer Name: ");
	scanf("%s", &customer_name);
	printf("Enter Unit Consumed: ");
	scanf("%f", &unit_consumed);
	
	if (unit_consumed < 200){
		unit_charge = 16.20;}
	else if (unit_consumed >= 200 && unit_consumed < 300){
		unit_charge = 20.10;}
	else if (unit_consumed >= 300 && unit_consumed < 500){
		unit_charge = 27.10;}
	else if (unit_consumed >= 500){
		unit_charge = 35.90;}
	total_bill = unit_consumed * unit_charge;
	if(total_bill >= 18000){
		surcharge_amount = (total_bill*0.15);}
	printf("\nCustomer Id: %d\n", customer_id);
	printf("Customer Name: %s\n", customer_name);
	printf("Unit Consumed: %.2f\n", unit_consumed);
	printf("Amount Charges @Rs %.2f per unit: %.2f\n", unit_charge, total_bill);
	printf("Surcharge Amount: %.2f\n", surcharge_amount);
	printf("Net amount Paid by the Customer: %.2f\n", total_bill + surcharge_amount);
}
