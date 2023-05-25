/*
 * A C program with variable declarations and printf and a function
 * (newhall, 2021)
 */

#include <stdio.h>

/* this is a function prototype, it defined the type of a function */
int sum_if_positive(int val1, int val2);
// TODO: if you add functions, make sure to add their prototypes here
int if_bigger(int val1, int val2);

int main() {

  int x, y, sum;   // declare all local vars at the top

  x = 10;
  y = 8;
  sum = sum_if_positive(x, y);  // function call
  printf("the sum of %d and %d is %d\n", x, y, sum);

  x = y - x;
  y = x*x;
  sum = sum_if_positive(x, y);
  printf("the sum of %d and %d is %d (this is weird)\n", x, y, sum);
  // TODO: add code to only print out sum result if sum_if_positive
  //       does not return -1, and and error message if it does

  // TODO: call is_bigger here and print out its result
  int result;
  result = if_bigger(x,y);
  printf("the result of is_bigger is %d\n", result);
  return 0;
}
/*****************************************
 * This function computes the sum of two values
 *
 * val1: one value
 * val2: the other value
 * return: the sum of val1 and val2, or -1 if
 *          one or both of the values are not positive
 */
int sum_if_positive(int val1, int val2) {

  int result;   // declare all local variables first at top of function

  result = -1;
  if((val1 > 0) && (val2 > 0)) {
    result = val1 + val2;
  }

  return result;
}
/*****************************************
 *
 * TODO: add a function named is_bigger that takes
 *       two input values and returns the larger of the two
 */

 int if_bigger(int val1, int val2) {
    if(val1 > val2) {
        return val1;
    }

    else {
        return val2;
    }
 }
