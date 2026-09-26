#include<stdio.h>
int main()
{
 float water, sugar, mix1, coffee, milk, mix2, total_time;
 char coffee_type, cup_size;
 printf("Enter the type of coffee you would like, 'B' for black coffee or 'W' for white coffee: ");
 scanf(" %c", &coffee_type);
 printf("Enter the size of cup, 'S' for single or 'D' for double: ");
 scanf(" %c", &cup_size);
 switch(coffee_type){
  case 'B':
  case 'b':
    switch(cup_size){
     case 'S':
     case 's':
       water = 20.0;
       sugar = 20.0;
       mix1 = 25.0;
       coffee = 15.0;
       milk = 0.0;
       mix2 = 25.0;
       total_time = water + sugar + mix1 + coffee + milk + mix2;
       printf("Put water, time taken: %.2f\n", water);
       printf("Add sugar, time taken: %.2f\n", sugar);
       printf("Mix well, time taken: %.2f\n", mix1);
       printf("Add coffee, time taken: %.2f\n", coffee);
       printf("Add milk, time taken: %.2f\n", milk);
       printf("Mix well, time taken: %.2f\n", mix2);
       printf("Total time taken: %.2f\n", total_time);
     break;
     case 'D':
     case 'd':
       water = 20.0 * 1.5;
       sugar = 20.0 * 1.5;
       mix1 = 25.0 * 1.5;
       coffee = 15.0 * 1.5;
       milk = 0.0 * 1.5;
       mix2 = 25.0 * 1.5;
       total_time = water + sugar + mix1 + coffee + milk + mix2;
       printf("Put water, time taken: %.2f\n", water);
       printf("Add sugar, time taken: %.2f\n", sugar);
       printf("Mix well, time taken: %.2f\n", mix1);
       printf("Add coffee, time taken: %.2f\n", coffee);
       printf("Add milk, time taken: %.2f\n", milk);
       printf("Mix well, time taken: %.2f\n", mix2);
       printf("Total time taken: %.2f\n", total_time);
     break;
     default:
       printf("Invalid Input\n");}
  break;
  case 'W':
  case 'w':
    switch(cup_size){
     case 'S':
     case 's':
       water = 15.0;
       sugar = 15.0;
       mix1 = 20.0;
       coffee = 2.0;
       milk = 4.0;
       mix2 = 20.0;
       total_time = water + sugar + mix1 + coffee + milk + mix2;
       printf("Put water, time taken: %.2f\n", water);
       printf("Add sugar, time taken: %.2f\n", sugar);
       printf("Mix well, time taken: %.2f\n", mix1);
       printf("Add coffee, time taken: %.2f\n", coffee);
       printf("Add milk, time taken: %.2f\n", milk);
       printf("Mix well, time taken: %.2f\n", mix2);
       printf("Total time taken: %.2f\n", total_time);
     break;
     case 'D':
     case 'd':
       water = 15.0 * 1.5;
       sugar = 15.0 * 1.5;
       mix1 = 20.0 * 1.5;
       coffee = 2.0 * 1.5;
       milk = 4.0 * 1.5;
       mix2 = 20.0 * 1.5;
       total_time = water + sugar + mix1 + coffee + milk + mix2;
       printf("Put water, time taken: %.2f\n", water);
       printf("Add sugar, time taken: %.2f\n", sugar);
       printf("Mix well, time taken: %.2f\n", mix1);
       printf("Add coffee, time taken: %.2f\n", coffee);
       printf("Add milk, time taken: %.2f\n", milk);
       printf("Mix well, time taken: %.2f\n", mix2);
       printf("Total time taken: %.2f\n", total_time);
     break;
     default:
       printf("Invalid Input\n");}
  break;
  default:
    printf("Invalid Input\n");}
 return 0;
}  
