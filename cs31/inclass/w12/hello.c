/* 
 * Simple pthreads program with a race condition
 * (newhall, 2012)
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// the thread main routine must match this prototype:
void *thread_hello(void *arg);

// global variables shared by all threads
static unsigned long long count;
static pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;

/***************************************************************/
int main(int argc, char **argv) {

    pthread_t *tids;
    int ret, i, ntids, *tid_args;

    if(argc != 2) {
      printf("usage: ./hello num_threads\n");
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
        // The third parameter is a function pointer, we pass
        // the name of a function with a matching prototype of
        // the parameter.  thread_create calls thread_hello via 
        // the function ptr parmeter.
        ret = pthread_create(&tids[i], 0, thread_hello, &tid_args[i]);

        // try this call to pthread_create instead of the above
        // one. run a few times and see what happens to the value 
        // passed in as the arg (do you understand what is going on?):
        //ret = pthread_create(&tids[i], 0, thread_hello, &i);
        
        if(ret) {
           perror("Error pthread_create\n");
           exit(1);
        }
    }
    // wait for all worker threads to exit
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
void *thread_hello(void *arg) {

  int myid, i, bogus, j;

  myid = *((int *)arg);
  printf("hello I'm thread %d with pthread_id %lu\n", 
      myid, pthread_self());
  fflush(stdout);

  // RACE CONDITION:  try running this program a few times,
  //                  you should see different final results
  for(i = 0; i < 1000000; i++) {
    count += i;
  }

  // FIX TO RACE CONDITION:
  // add mutex lock and unlock around count access in above
  // code to avoid race condition:
  //  pthread_mutex_lock(&my_mutex);
  //  count += i; 
  //  pthread_mutex_unlock(&my_mutex);
  //
 
  // uncomment the below code to make hello threads 
  // run longer so we can see them when we run top -H
  /*
  for(i = 0; i < 1000000; i++) {
    bogus = (bogus*i)/((i%3)+1);
    for(j = 0; j < 2000; j++) {
      if(bogus > 10) {
        bogus = bogus -1;
      } else {
        bogus = bogus + 0.1;
      }
    }

  }
  */

  
  printf("goodbye I'm thread %d with pthread_id %lu\n", 
      myid, pthread_self());
  fflush(stdout);
  
  return (void *)0;
}

