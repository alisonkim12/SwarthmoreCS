/*
 * A simple C program with variable declarations and printf 
 * and a function
 * (newhall, 2013)
 */

#include <stdio.h>   

int mystery(int x, int y);

int main() { 
  
  int x, y;  
  float z; 

  x = 10;  
  y = 8;
  z = y/x;  
  printf("x = %d y = %d z = %3.2f\n", x, y, z);
  z = mystery(x, y);
  printf("x = %d y = %d z = %3.2f\n", x, y, z);

  return 0;
}
/******************************************************************/
// a mystery function
int mystery(int a, int b) {

  int i;
  float c;

  c = b;
  for(i=0; i < a; i++) {
    c += i;
  }
  return c;
}
