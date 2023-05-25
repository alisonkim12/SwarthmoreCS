// A simple example program that uses the mylib library
// (note that we need to #include its .h file and link in its
//  .o file in the Makefile to compile this code)
//
// (newhall, 2013)
//
#include <stdio.h>
#include <stdlib.h>

// #include the header file for mylib library 
// because this header file is not a standard header file,
// it is one I wrote in the current directory, use " " rather
// than < > around the name of the .h file.
#include "mylib.h"

#define NUM 5

int main(int argc, char *argv[]) {

  int i;

  // access a global variable 
  // (typically a library would not export its global variables, but
  // this is just to show you how it is in scope within this function)
  my_counter = 8;

  // call a global function
  for (i=0; i < NUM; i++) {
     printf("next counter value: %d\n", inc_and_return_count());
  }

  exit(0);

}
