/*
 * Starting point for in-class problem:
 *    find the maximum value in a set of N values using M threads
 *    parallelize the finding the max part
 * (newhall, 2013)
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_M 64
#define MAX_RANGE 1000000  // restrict the range of values generated
                           // you can set this to something small for
                           // testing for correctness (so you can more
                           // easily see the max value)

// TODO: your thread main routine must match this prototype:
//void *thread_mainloop(void *arg);

// TODO: global variables shared by all threads
// (you may add more if you like):
static long *values; // the array of values from which max is found
static long result;

// TODO:if you want some shared synchronization primatives, declare
// them here (you can also init them here too).  For example:
//static pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;


// TODO:if you want to pass each thread's main function more than a single
// value, you should define a new struct type with field values for
// each argument you want to pass it


// some functions I've implemented to create the array fo values from
// which your threads should compute max
void init_values(long *values, unsigned long n);
// print function to test for correctness (just try on very small n):
void print_values(long *values, unsigned long n);

/***************************************************************/
int main(int argc, char **argv) {

    int i, ntids, *tid_args;
    unsigned long n;
    pthread_t *tids;


    printf("This is a parallization of finding the max in an array\n");
    printf("of N values, using M threads (between 1 and %d)\n", MAX_M);

    if(argc != 3) {
      printf("usage: ./max N num_threads\n");
      exit(1);
    }
    result = 0;
    n = atol(argv[1]);
    ntids = atoi(argv[2]);
    // make ntids a sane value if insane
    if((ntids < 1)) { ntids = 1; }
    if((ntids > MAX_M)) { ntids = MAX_M; }
    printf("%d threads finding max of %lu values\n", ntids, n);

    values = malloc(sizeof(long)*n);
    if(!values) {
      printf("mallocing up %lu longs failed\n", n);
      exit(1);
    }

    init_values(values, n);
    // TODO: you can uncomment this to see all the values...but don't
    //       run for large size N if you do this
    //print_values(values, n);

    // TODO: add your soution here /////////////////////////

    int j;
    int divide = n / ntids -1;
    maxarrays[divide];
    int maxvalues;
    for (j = 0; j<ntids; j++) {
      tid_args[i] = j;
      ret = pthread_create(&tids[j], 0, thread_hello, &tid_args[j]);
      max_values = find_max(values,j*divide,(j*divide+divide - 1));
      pthread_mutex_lock(&my_mutex);
      maxarrays[j] = maxvalues;
      pthread_mutex_unlock(&my_mutex);
    }



    for (i = 0; i<ntids){

      find_max(values, )

    }




    ///////////////////////////
    printf("max value is: %ld\n", result);
    free(values);
    values = 0;
    exit(0);
}
/****************************************************************/
// TODO: add your thread main loop function here, and any others
//       you need
//       its prototype must match
//       void * thr_mainloop(void *args);

/****************************************************************/
// inits an array to random values
//   values: the array to init
//   n: size of the array
void init_values(long *values, unsigned long n) {

  unsigned long i;

  // seed the random number generator: a different start based on current time
  srand(time(0));
  for(i=0; i < n; i++) {
    values[i] = rand() % MAX_RANGE;  // let's just make these a sane range
  }
}
/****************************************************************/
// prints out an array of values
//   values: the array to init
//   n: size of the array
void print_values(long *values, unsigned long n) {
  unsigned long i;
  for(i=0; i < n; i++) {
    printf("%6ld ", values[i]);
    if((i<(n-1)) && (((i+1)%10) == 0)) {
      printf("\n");
    }
  }
  printf("\n");
}
