//
// This program shows examples of 2 different ways of declaring,
// and accessing 2D arrays and of how they are layed out in memory
//  (1) statically allocated:
//      row-major order, all buckets contigous
//  (2) dynamically allocated in a single malloc:
//      all buckets contiguous
//
// (newhall, 2012)
//
#include <stdio.h>
#include <stdlib.h>

#define N  4
#define M  5

void init_static(int array[][M], int rows);
void init_dynamic(int *array, int rows, int cols) ;

void print_static_addrs(int array[][M], int rows) ;
void print_dynamic_addrs(int *array, int rows, int cols) ;

void print_static_array(int array[][M], int rows) ;
void print_dynamic_array(int *array, int rows, int cols) ;

int main() {

  int sarr[N][M];  // a statically allocated 2D array with N rows and M columns
  int *darr;       // a dynamically allocated "2D" array using 1 malloc

  // (1) statically declared 2D array: let's see how these are
  //     layed out in RAM
  printf("\n");
  print_static_addrs(sarr, N);

  // (2) a dynamically allocated 2D array as a single malloc
  darr = malloc(sizeof(int)*N*M);  // NxM int values
  if(!darr) {
    printf("malloc failed\n");
    exit(1);
  }
  // let's see how these are layed out in RAM
  print_dynamic_addrs(darr, N, M);

  // let's initialize these arrays, we need separate functions
  // for each type:
  init_static(sarr, N);
  init_dynamic(darr, N, M);

  printf("\nsarr values:\n");
  print_static_array(sarr, N);
  printf("\ndarr values:\n");
  print_dynamic_array(darr, N, M);

  // free space for darr: in one call to free
  free(darr);
  darr = 0;

  return 0;
}
/**************************************************************/
/*
 * print out the addresses of each bucket value in the passed
 * statically declared array
 *   array: the array of ints
 *   rows: the number of rows in the passed array
 */
void print_static_addrs(int array[][M], int rows) {

  int i,j;

  printf("Statically Declared 2D Array addresses:\n");
  printf("(note all contigous addresses in row-major order)\n");
  printf("-------------------------------------------------\n");
  for(i=0; i < rows; i++) {
    for(j=0; j < M; j++) {
       printf("[%d][%d]:%p  ", i, j, &array[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}
/**************************************************************/
/*
 * print out the addresses of each bucket value in the passed
 * dynamically declared 2D array
 *   array: the array of ints
 *   rows: the number of rows in the passed array
 *   cols: the number of rows in the passed array
 */
void print_dynamic_addrs(int *array, int rows, int cols) {

  int i,j;

  printf("Dynamically allocated 2D array (single malloc version) addresses:\n");
  printf("(note all contigous addresses in row-major order)\n");
  printf("-----------------------------------------------------------------\n");
  for(i=0; i < N; i++) {
    for(j=0; j < M; j++) {
       // note the difference in how we are accessing array buckets
       // in static (print_static_addrs) vs. this dynamically declared
       // 2D array
       printf("[%d][%d]:%p  ", i, j, &array[i*M + j]);
    }
    printf("\n");
  }
  printf("\n");
}
/**************************************************************/
/*
 * intialize a statically declared array
 *   array: the array to init, M is the column dimension
 *          the row dimension does not need to be specified here
 *   rows: the number of rows in this array
 *
 * We need to specify the column index to the array parameter
 * so that the compiler can  generate code that will compute where
 * the start of each * row is in memory is.
 * Passing in rows as a second parameter just makes this more
 * generic than specifying both the exact row and column dimentions
 * in the parameter.
*/
void init_static(int array[][M], int rows) {

  int i, j;
  for(i=0; i < rows; i++) {
    for(j=0; j < M; j++) {
      array[i][j] = i+j;
    }
  }
}
/**************************************************************/
/*
 * intialize a dynamically declared array 2D array
 * (the single malloc of an NxM contiguous chunk of ints kind)
 *   array: the array to init
 *   rows: the number of rows
 *   cols: the number of cols
 *
 *   we CANNOT use [i][j] syntax in here to access elements because
 *   the compiler cannot generate the right code to find the start
 *   of the next row (it depends on the col dimension).  As a result
 *   we will do the calculation in this code to get the rigth values.
 */
void init_dynamic(int *array, int rows, int cols) {
  int i, j;
  for(i=0; i < rows; i++) {
    for(j=0; j < cols; j++) {
      array[i*cols + j] = i+j;
    }
  }
  printf("Test: %d\n", array[0]);
}
/**************************************************************/
/*
 * prints out the array values, one row per line
 *   array: the array to init
 *   rows: the number of rows
 *   cols: the number of cols
 */
void print_dynamic_array(int *array, int rows, int cols) {
  int i, j;
  for(i=0; i < rows; i++) {
    for(j=0; j < cols; j++) {
      printf(" %3d", array[i*cols + j]);
    }
    printf("\n");
  }
}
/**************************************************************/
/*
 * prints out the array values, one row per line
 *   array: the 2D array of ints init
 *   rows: the number of rows
 */
void print_static_array(int array[][M], int rows) {
  int i, j;
  for(i=0; i < rows; i++) {
    for(j=0; j < M; j++) {
      printf(" %3d", array[i][j]);
    }
    printf("\n");
  }
}
