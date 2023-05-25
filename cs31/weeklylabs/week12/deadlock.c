/*
 * pthreads program with deadlock
 * use gdb on this
 * (newhall, 2012)
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// the thread main routine must match this prototype:
void *worker_loop(void *arg);

// global variables shared by all threads
static unsigned long long count;
static pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

/***************************************************************/
int main(int argc, char **argv) {

    pthread_t *tids;
    int ret, i, ntids, *tid_args;

    if(argc != 2) {
      printf("usage: ./deadlock num_threads\n");
      exit(1);
    }
    ntids = atoi(argv[1]);
    // make ntids a sane value if insane
    if((ntids < 1) || (ntids > 100)) { ntids = 10; }

    tids = (pthread_t *)malloc(sizeof(pthread_t)*ntids);
    if(!tids) {
      perror("malloc pthread_t array");
      exit(1);
    }
    if(!(tid_args = (int *)malloc(sizeof(int)*ntids))) {
      perror("malloc tid_args array");
      exit(1);
    }

    count = 0;
    for (i=0; i < ntids; i++) {
        tid_args[i] = i;
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
// thread main loop
//   arg: an int value specifying a logical tid value
void *worker_loop(void *arg) {

  int myid, i, j;
  myid = *((int *)arg);
  printf("hello I'm thread %d with pthread_id %lu\n",
      myid, pthread_self());

  for(j = 0; j < 100; j++) {
    pthread_mutex_lock(&mutex1);
    pthread_mutex_lock(&mutex2);
    count =0;
    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);
    for(i = 0; i < 10000; i++) {
      pthread_mutex_lock(&mutex2);
      pthread_mutex_lock(&mutex1);
      count += i;
      pthread_mutex_unlock(&mutex2);
      pthread_mutex_unlock(&mutex1);
    }
  }

  return (void *)0;
}
