/*
 * An example of reading beyond the bounds of an array.
 * (newhall, 2021)
 */
#include <stdio.h>

int main() {
  int i;
  int a[10];

  for (i=0; i<10; i++){
    a[i] = i*i;
  }

  for (i=0; i<=15; i++){
    printf("a[%d] =  %d\n", i, a[i]);
  }

  return 0;
}
