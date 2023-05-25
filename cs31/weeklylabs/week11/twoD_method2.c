// Some practice with 2D arrays using the Method 2 way of
// dynamically allocating them (an array of arrays):
// A 2D array as an array of 1D arrays:
//   row-number 1D arrays, each storing col-number elements in each row
//
// This form of 2D array supports double indexing syntax: array[i][j]
//    array[i] is ith bucket of outer array, which stores base address
//    of inner array
//    array[i][j] is jth bucket of ith inner array:
//     (array[i])[j] : (base address of ith inner array)[j]
//
// (newhall, 2021)
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void init_values(int **values, int rows, int cols);
void print_values(int **values, int rows, int cols);

int main() {

  int i, rows, cols;
  int **two_d;  // 2D array that it an array of int arrays
                // each bucket stores an (int *) so it stores
                // address of an (int *) or an (int **)
  rows = 3;
  cols = 5;

  // dynamically allocating space requires rows + 1 mallocs
  // (1) malloc an array of rows dimension, of int *
  two_d = malloc(sizeof(int *)*rows);
  if(two_d == NULL) {
    printf("ERROR: malloc failed\n");
    exit(1);
  }
  // (2) maloc an array of cols dimension ints, one for each row
  for(i = 0; i < rows; i++) {
    // two_d[i] stores base address of int array of the ith row's values
    two_d[i] = malloc(sizeof(int)*cols);
    if(two_d[i] == NULL) {
      printf("ERROR: malloc failed\n");
      exit(1);
    }
  }

  // initialize two_d array
  // TODO: complete the implementation of this function below
  init_values(two_d, rows, cols);

  // print out two_d array
  // TODO: complete the implementation of this function below
  print_values(two_d, rows, cols);

  // TODO: add code to free the 2D array
  // NOTE: you need one call to free for each call to malloc

  return 0;
}
/**************************************************
 * initialize each [i][j] value to i+j
 * values: two D array of int values
 * rows: row dimension
 * cols: column dimension
 */
void init_values(int **values, int rows, int cols){

  int i, j;

  // TODO: complete this function
  // note: can use double indexing  values[i][j]

}
/**************************************************
 * prints out values of 2D array, each row's values
 * on a separate line
 *
 * values: two D array of int values
 * rows: row dimension
 * cols: column dimension
 */
void print_values(int **values, int rows, int cols) {

  int i, j;


  // TODO: complete this function

  // printf("%3d, ", values[i][j]); // %3d print int value in field with of 3


}
