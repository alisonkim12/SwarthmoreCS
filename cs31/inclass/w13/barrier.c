/*
 * A small pthread barrier example
 * (adanner, 2021)
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// the thread main routine must match this prototype:
void *worker_loop(void *arg);

/* A wrapper around malloc. Try to allocate size bytes
   and return a pointer. But if malloc() returns an
   error, print error with perror and exit
     size: number of bytes to allocate
     returns: pointer to malloced memory on heap
*/
static void *my_malloc(size_t size);


/* global synchronization variables */
static pthread_barrier_t my_barrier;

/* struct definition used to pass several values to
   the worker_loop function (via its args parameter)
*/
struct worker_args {
  int mytid; // worker id for this thread.
};

/***************************************************************/
int main(int argc, char **argv) {

  pthread_t *tids;
  int ret, i, ntids;
  struct worker_args *tid_args;

  if(argc != 2) {
    printf("usage: %s num_threads\n", argv[0]);
    exit(1);
  }
  ntids = atoi(argv[1]);
  if((ntids < 1) || (ntids > 100)) { ntids = 10; }

  // Allocate space for pthread ids and args
  tids = (pthread_t *)my_malloc(sizeof(pthread_t)*ntids);
  tid_args =
    (struct worker_args *)my_malloc(sizeof(struct worker_args)*ntids);

  // initialize the barrier with the number of threads that will
  // synchronize on it
  if(pthread_barrier_init(&my_barrier, 0, ntids)) {
    printf("pthread_barrier_init error\n");
    exit(1);
  }

  // create threads
  for (i=0; i < ntids; i++) {
    tid_args[i].mytid = i;

    ret = pthread_create(&tids[i], 0, worker_loop, &tid_args[i]);
    if(ret) {
      perror("Error pthread_create\n");
      exit(1);
    }
  }

  // wait for threads to finish
  for (i=0; i < ntids; i++) {
    pthread_join(tids[i], 0);
  }

  // clean up
  pthread_barrier_destroy(&my_barrier);
  free ((int *)tid_args); tid_args = NULL;
  free ((pthread_t *)tids); tids = NULL;
  exit(0);
}

/****************************************************************/
// a wrapper function around malloc that calls perror and exit
// on error
//    size: number of bytes to malloc on heap
//    returns: pointer to allocated space on heap
static void *my_malloc(size_t size){
  void *ret;
  ret = malloc(size);
  if(!ret) {
    perror("malloc array for threads");
    exit(1);
  }
  return ret;
}

/****************************************************************/
// thread main loop
//   arg: a struct worker_args *, containing mytid
//   returns: NULL
void *worker_loop(void *arg) {

  struct worker_args info = *(struct worker_args*)arg;
  printf("Hello from thread %d\n", info.mytid);


  /* with the barrier in place, all threads must print
     hello before any thread starts its tasks */

  // Every thread must get here before proceeding
  pthread_barrier_wait(&my_barrier);

  printf("Task A %d\n", info.mytid);
  printf("Task B %d\n", info.mytid);

  pthread_barrier_wait(&my_barrier);

  /* with the barrier in place, all threads must
     print both tasks before any thread prints goodbye */
  printf("Goodbye from thread %d\n", info.mytid);

  return (void *)NULL;
}
