#include <stdio.h>
int main() {
	int weekday, vacation;
	printf("Is this Weekday (1 for true or 0 for false): ");
	scanf("%d", &weekday);
	printf("Is this Vacation (1 for true or 0 for false): ");
	scanf("%d", &vacation);
	if (weekday == 1 && vacation == 0){
		printf("False");}
	else if (weekday == 0 && vacation == 1){		
	printf("True");}
	else if (weekday == 0 && vacation == 0){
		printf("True");}
	else{
		printf("Invalid Input");}
}
