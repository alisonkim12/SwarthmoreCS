/* A sample pthreads program to demonstrate create and join functions
 * A. Danner Spring 2021
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* A standard pthreads main function prototype
 * all pthreads functions must be of return type
 * void* and accept one void* argument for general input.
 * This sample program will not use these features so it
 * is safe to pass NULL to the function and return NULL
 * from the function, but other thread functions may  behave
 * differently.
 */
void *hello(void *arg);

int main() {

  /* a small array to store the thread IDs returned by
     pthread_create  */
  pthread_t tid[2];
  int ret;

  /* create a new thread running the function hello
     store the thread ID in tid[0] */
  ret = pthread_create(&tid[0], NULL, hello, NULL);
  if (ret) {
    perror("Error pthread_create\n");
    exit(1);
  }

  ret = pthread_create(&tid[1], NULL, hello, NULL);
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
 * thread main function for first hello. 
 * (note it must have exactly this function prototype)
 * arg: not used by this function
 * returns: NULL
 */
void *hello(void *arg) {
  printf("Hello, world!\n");
  return NULL;
}
