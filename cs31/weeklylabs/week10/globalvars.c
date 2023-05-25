/* An example of using global variables in C
 *
 * In general YOU SHOULD NOT USE GLOBAL VARIABLES; values needed by
 * functions should be passed in as parameters.  globals can make your
 * program harder to debug and they make functions that refer to them
 * less generic. However, there are some cases when globals are necessary 
 * (this is not one of them).
 *
 * (newhall, 2013)
 */
#include <stdio.h>
#include <stdlib.h>

/* a GLOBAL VARIABLE is declared outside of any function  definition
 * global variables are always in scope and space for them persists
 * for the entire run of the program
 *
 * static: limits the scope of this global to functions in this .c 
 *         file only (its space still persists, it just cannot be named
 *         in code that is in other .c files: it is private but persistant)
 */
static int counter = 0;

int mystery(int a, int b);

/***************************************************/
int main() {

  int x, y, i;

  printf("Enter two int values: ");
  scanf("%d%d", &x, &y);
  printf("counter starts at: %d\n", counter);
  for(i=0; i < x; i++) {
    y = mystery(y, i);
  }
  printf("counter ends at: %d\n", counter);

  exit(0);
}
/***************************************************/
/* This function changes the value of counter by a+b
 *   a: one int value
 *   a: the other int value
 * returns: the larger of a and b (why? why not.)
 */
int mystery(int a, int b) {

  counter = counter + (a + b);  // change global var's value
  if(a > b) {
    return a;
  }
  return b;
}
