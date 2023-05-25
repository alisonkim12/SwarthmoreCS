/*
 * Jack/Zach condition wait example
 * (adanner 2021)
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


/* various thread helper functions */
// print jack or zach with no synchronization at all
void jack_writer_nosynch(void);
void zach_writer_nosynch(void);

// print jack or zach with only a mutex around the printf
void jack_writer_mux(void);
void zach_writer_mux(void);

// writers with condition variables
void jack_writer_cond(void);
void zach_writer_cond(void);

// global condition variables and mutex
pthread_cond_t jack = PTHREAD_COND_INITIALIZER;
pthread_cond_t zach = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mux = PTHREAD_MUTEX_INITIALIZER;

// shared global state
int jack_written = 0;

// struct definition used to pass several values to
// the worker_loop function (via its args parameter)
struct worker_args {
  int mytid; //unique thread id
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

  // create threads
  for (i=0; i < ntids; i++) {
    tid_args[i].mytid = i;

    ret = pthread_create(&tids[i], 0, worker_loop, &tid_args[i]);
    if(ret) {
      perror("Error pthread_create\n");
      exit(1);
    }
  }

  // wait for threads to finis
  for (i=0; i < ntids; i++) {
    pthread_join(tids[i], 0);
  }

  // clean up
  free ((int *)tid_args); tid_args = NULL;
  free ((pthread_t *)tids);  tids = NULL;
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
void *worker_loop(void *arg) {

  struct worker_args info = *(struct worker_args*)arg;

  /* assign even threads to write Jack,
     odd threads to write Zach */
  if(info.mytid % 2 == 0 ){
    jack_writer_cond();
  } else {
    zach_writer_cond();
  }

  return (void *)NULL;
}

/****************************************************************/
// Print Jack with no synchronization
void jack_writer_nosynch(void){
  printf("Jack\n");
}

/****************************************************************/
// Print Jack using a mutex to make print atomic
void jack_writer_mux(void){
  pthread_mutex_lock(&mux);
  printf("Jack\n");
  pthread_mutex_unlock(&mux);
}

/****************************************************************/
// Print Jack using a condition variable to ensure
// Jack is always written before a Zach
void jack_writer_cond(void){
  pthread_mutex_lock(&mux);
  while(jack_written) {
    // block and wait until Zach is written
    pthread_cond_wait(&jack, &mux);
  }
  printf("Jack\n");
  // set global state to indicate Jack was last written
  jack_written = 1;
  // notify zach condition var that it is safe to write Zach
  pthread_cond_signal(&zach);
  pthread_mutex_unlock(&mux);
}

/****************************************************************/
// Print Zach with no synchronization
void zach_writer_nosynch(void){
  printf("Zach\n");
}

/****************************************************************/
// Print Zach using a mutex to make print atomic
void zach_writer_mux(void){
  pthread_mutex_lock(&mux);
  printf("Zach\n");
  pthread_mutex_unlock(&mux);
}

/****************************************************************/
// Print Zach using a condition variable to ensure
// Zach is always written after a Jack
void zach_writer_cond(void){
  pthread_mutex_lock(&mux);
  while(!jack_written) {
    // block and wait until Jack is written
    pthread_cond_wait(&zach, &mux);
  }
  printf("Zach\n");
  // set global state to indicate Zach was last written
  jack_written = 0;
  // notify jack condition var that it is safe to write Jack
  pthread_cond_signal(&jack);
  pthread_mutex_unlock(&mux);
}
