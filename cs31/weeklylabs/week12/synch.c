/* 
 * Demo of some pthred synchronization primatives
 * (newhall, 2012)
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// the thread main routine must match this prototype:
void *worker_loop(void *arg);

static void *my_malloc(size_t size);

// global variables shared by all threads
static unsigned long long count = 0;
// semaphore
static pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;
// barrier
static pthread_barrier_t my_barrier;

// condition variable


// struct definition used to pass several values to
// the worker_loop function (via its args parameter)
struct worker_args {
  int mytid;
  int work_unit;
};

/***************************************************************/
int main(int argc, char **argv) {

  pthread_t *tids;
  int ret, i, ntids;
  struct worker_args *tid_args;

  if(argc != 2) {
    printf("usage: ./synch num_threads\n");
    exit(1);
  }
  ntids = atoi(argv[1]);
  if((ntids < 1) || (ntids > 100)) { ntids = 10; }

  tids = (pthread_t *)my_malloc(sizeof(pthread_t)*ntids);
  tid_args = 
    (struct worker_args *)my_malloc(sizeof(struct worker_args)*ntids);

  // initialize the barrier with the number of threads that will
  // synchronize on it:
  if(pthread_barrier_init(&my_barrier, 0, ntids)) {
    printf("pthread_barrier_init error\n");
    exit(1);
  }

  for (i=0; i < ntids; i++) {
    // make higher numbered tids have a lot more work to do
    tid_args[i].work_unit = (i+1)*(i+1)*(i+1);
    tid_args[i].work_unit *= tid_args[i].work_unit;
    tid_args[i].mytid = i;

    ret = pthread_create(&tids[i], 0, worker_loop, &tid_args[i]);
    if(ret) {
      perror("Error pthread_create\n");
      exit(1);
    }
  }

  for (i=0; i < ntids; i++) {
    pthread_join(tids[i], 0);
  }
  printf("count = %llu\n", count);

  free ((int *)tid_args);
  free ((pthread_t *)tids);
  exit(0);
}
/****************************************************************/
// a wrapper function around malloc that calls perror and exit
// on error
static void *my_malloc(size_t size){
  void *ret;
  ret = malloc(size);
  if(!ret) {
    perror("malloc tid_args array");
    exit(1);
  }
  return ret;
}
/****************************************************************/
// thread main loop
//   arg: a struct worker_args *, with mytid and work_unit fields{
void *worker_loop(void *arg) {

  int myid, wu, i, j;
  unsigned long long local;

  myid = ((struct worker_args *)arg)->mytid;
  wu = ((struct worker_args *)arg)->work_unit;
  printf("hello I'm thread %d with pthread_id %lu work unit %d\n", 
      myid, pthread_self(), wu);

  for(i = 0; i < 100; i++) {
    local = i;
    for(j = 0; j < wu; j++) {
      local += j;  // update private local variable
    }

    // atommically add local value into shared global count 
    pthread_mutex_lock(&my_mutex);
    count += local; 
    pthread_mutex_unlock(&my_mutex);

    if((i % 10) == 0) { 
      printf("\t%d:%llu\n", myid, local);
      fflush(stdout);
      // reset every 10th iteration
      // need to wait for all to finish their 
      // tenth iteration
      pthread_barrier_wait(&my_barrier);

      if(myid == 0) {
        printf("Global iteration %d count %llu\n", i, count);
        fflush(stdout);
        count = 0;
      }

      // wait for tid 0 to print message and set count to zero
      pthread_barrier_wait(&my_barrier);
    }
  }
  return (void *)0;
}

