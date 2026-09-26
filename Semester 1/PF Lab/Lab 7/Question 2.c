#include<stdio.h>
int main() {
  char arr[50];
  int a_count=0, e_count=0, i_count=0, o_count=0, u_count=0;
  printf("Enter a string: ");
  scanf("%s", arr);  
  for(int i=0; arr[i] != '\0' ; i++) {
    switch(arr[i]) {
      case 'A':
      case 'a':
        a_count++;
        break;
      case 'E':
      case 'e':
        e_count++;
        break;
      case 'I':
      case 'i':
        i_count++;
        break;
      case 'O':
      case 'o':
        o_count++;
        break;
      case 'U':
      case 'u':
        u_count++;
        break; } }  
  printf("a=%d, e=%d, i=%d, o=%d, u=%d", a_count, e_count, i_count, o_count, u_count);
  return 0;
}
