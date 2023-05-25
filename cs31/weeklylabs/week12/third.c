/* A example pthreads program with the following features
 *  1) number of threads can be set by the command line
 *  2) thread arrays created dynamically
 *  3) thread info struct used to pass more complex information to
       thread main function
 *  4) an array of structs
 *  5) using usleep as a proxy for "work", so you measure speedup
 *
 *  Usage  ./third [total work time in seconds] [number of threads]
 *  program will divide work across total number of threads.
 * A. Danner Spring 2021
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* A standard pthreads main function prototype
 * all pthreads functions must be of return type
 * void* and accept one void* argument for general input.
 * This program shows how to use the arg parameter to
 * pass a struct to each thread.
 */
void *work(void *arg);

/* Info needed for each thread */
struct thread_info {
  int id;
  float work_time;
  int ntids;
};

int main(int argc, char **argv) {

  pthread_t *tids;
  int ret, i, ntids;
  float nsecs;

  struct thread_info basic_info;
  struct thread_info *tid_args;

  if (argc != 3) {
    printf("usage: %s total_work_seconds num_threads\n", argv[0]);
    exit(1);
  }

  ntids = atoi(argv[2]);
  // make ntids a sane value if insane
  if ((ntids < 1) || (ntids > 100)) {
    ntids = 10;
  }

  nsecs = atof(argv[1]);
  if ((nsecs < 1.) || (nsecs > 30.)) {
    nsecs = 10.;
  }

  /* now that we know how many threads we want,
     dynamically allocate space for thread IDs and args
  */
  tids = (pthread_t *)malloc(sizeof(pthread_t) * ntids);
  if (!tids) {
    perror("malloc pthread_t array");
    exit(1);
  }

  /* an array of structs */
  tid_args = (struct thread_info *)malloc(sizeof(struct thread_info) * ntids);
  if (!tid_args) {
    perror("malloc tid_args array");
    exit(1);
  }

  basic_info.ntids = ntids;
  /* split up "work" amongst threads */
  basic_info.work_time = nsecs / ntids;

  for (i = 0; i < ntids; i++) {
    basic_info.id = i; /* change ID for each thread */
    tid_args[i] = basic_info; /* make a private copy for each thread */

    ret = pthread_create(&tids[i], 0, work, &tid_args[i]);

    // try this call to pthread_create instead of the above
    // one. run a few times and see what happens to the value
    // passed in as the arg (do you understand what is going on?):
  //  ret = pthread_create(&tids[i], 0, work, &basic_info);

    if (ret) {
      perror("Error pthread_create\n");
      exit(1);
    }
  }

  // wait for all worker threads to exit
  for (i = 0; i < ntids; i++) {
    pthread_join(tids[i], 0);
  }

  printf("Main thread done\n");
  free(tid_args);
  tid_args = NULL;
  free(tids);
  tids = NULL;
  return 0;
}

/**************************
 * thread main function
 *
 * arg: a pointer to a thr_info struct with this thread's
 *      information
 * returns: NULL
 */
void *work(void *arg) {
  /* the pthread prototype requires a void* parameter for
     general use. But we know for this example our parameter
     is a pointer to an struct thread_info. recast and
     dereference */
  struct thread_info info = *((struct thread_info *)arg); //casting
  printf("Hello from local thread ID: %d (pthread id: %lu)\n ", info.id,
         pthread_self());
  /* sleep is work */
  usleep(info.work_time * 1000000);
  return NULL;
}
