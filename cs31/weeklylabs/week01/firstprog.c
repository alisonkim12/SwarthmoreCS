/*
 * Top-level comment should briefly describe the program,
 * and include your name (the author of the code) and the date.
 *
 * A first C program with variable declarations and printf
 * (newhall, 2021)
 */

/* include the stdio.h (the standard I/O) library (like import in Python) */
#include <stdio.h>

/* declare constants in C (note: these are outside a function body) */
#define SEMESTER "spring"
#define YEAR 2021

/*
 * Every C program has a main function (main's return type is int)
 * curly braces indicate the start and end of a body of statements
 * (here they indicate all statements associated with the function main)
 * each statement in C ends in a semicolon.
 */
int main() {

  /* All local variables declared at the beginning of the function body
   *    variable declaration: <type name> <variable name>;
   */
  int x;      // declare x of type int
  float y, z; // declare 2 variables, y and z, of type float

  /* Next, add code for the body of the function.
   * Here, we're assigning values to variables.
   */
  x = 10;
  y = 8.6;
  z = y - x;  /* combining an int with a float evaluates to a float result */

  /* call C's output function, printf, with a string or format string
   * and arguments (printf is similar to Python's formatted print function)
   * %s is a placeholder for a string value, %d for an int value
   */
  printf("Hello CS31 class of %s %d\n", SEMESTER, YEAR);

  /* %d is a placeholder for an int, %f or %g can be used for float */
  printf("x = %d y = %f z = %g\n", x, y, z);

  /* TODO: add code to print out the result of x divided by y */
  printf("x/y is %f", x/y);

  /* main returns an int value. (return 0 indicates successful termination) */
  return 0;
}
