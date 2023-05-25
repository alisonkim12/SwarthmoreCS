//
// This is the implementation of the mylib library: its C code functions
// and any helper functions and state that it needs to implement the
// functions it exports (whose prototypes are defined in the mylib.h file)
//
// Anything that is internal to this library is declared static
// Anything that is exported by this library to users of the library
// is NOT declared to be static
//
// (newhall, 2013)
//
#include <stdio.h>
// include the header file that defines the function prototypes 
// for this library
#include "mylib.h"

// global variable declaration and initialization
// You do not need to initialize global variables
// when you declare them, and you can only initialize them
// to a scalar value in their declaration.
int my_counter=0;  

// "static" means that the scope of the global variable is limited to 
// this module (.c file).  This means that other .c files could have 
// a static  variable or function also named private_val, and  there 
// will be no name conflict with this one.  It is good practice to 
// declare all functions and globals variables that are not shared between 
// modules to be static.
static int private_val;

// a function prototype for a function defined later in this module. This
// is a static function, so its prototype should not appear in a .h file
static void update_old_val();

/*
 * This is an example global function definition that modifies a global 
 * variable shared by two modules (main.c and counter.c)
 * notice how the global is declared in main.c only.
 * notice how the function only used within main.c is declared static
 *
 * functions exported by the library, like this one, should not be
 * declared static
 */
int inc_and_return_count() {
  update_old_val();
  my_counter++;
  return my_counter;
}

/*
 * an example of a static function
 * (a function whose scope is limited to this .c file)
 */
static void update_old_val() {
  private_val = my_counter;
}
