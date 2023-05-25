/*
 * A program that calls dosomething function
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* computes a kooky arithmetic function of n
 * n: an int value
 * returns: some arithmetic function applied to n
 */
int dosomething(int n);


int main() {

  int res, n;

  printf("Enter an int value: ");
  scanf("%d", &n);
  res = dosomething(n);
  printf("dosomething(%d) computes %d\n", n, res);

  return 0;
}
