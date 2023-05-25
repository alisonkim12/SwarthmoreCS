/* A sample pthreads program to demonstrate create and join functions
 * Example shows how to pass a local thread ID to each thread as
 * an argument
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
 * pass a local thread ID to each thread.
 */
void *hello(void *arg);

int main() {

  /* a small array to store the thread IDs returned by
     pthread_create. Use this ID for join */
  pthread_t tid[2];
  int ret;

  /* an array were we can pick a sensible ID for each
     thread, perhaps for later computation or easier
     reference */
  int my_id[2];

  my_id[0] = 0;
  my_id[1] = 1;

  /* create a new thread running the function hello
     store the thread ID in tid[0], and passing a
     int pointer to the ID of each thread as hello's
     argument */
  ret = pthread_create(&tid[0], NULL, hello, &my_id[0]);
  if (ret) {
    perror("Error pthread_create\n");
    exit(1);
  }

  ret = pthread_create(&tid[1], NULL, hello, &my_id[1]);
  if (ret) {
    perror("Error pthread_create\n");
    exit(1);
  }
  /* wait for threads to finish */
  pthread_join(tid[0], NULL);
  pthread_join(tid[1], NULL);
  printf("Main thread done\n");
  return 0;
}
/**************************
 * thread main function for second hello. 
 *
 * arg: a pointer to an int value specifying the threads
 *      logical tid
 * returns: NULL
 */
void *hello(void *arg) {
  /* the pthread prototype requires a void* parameter for
     general use. But we know for this example our parameter
     is a pointer to an int storing an ID. recast and
     dereference */
  int id = *((int *)arg);
  printf("Hello from local thread ID: %d", id);
  /* pthread_self() is a unique ID created by the library */
  printf(" (pthread id: %lu)\n", pthread_self());
  return NULL;
}
