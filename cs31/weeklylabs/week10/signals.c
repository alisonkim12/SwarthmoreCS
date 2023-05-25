/* An example of a program with a signal handler
 *
 * kill -INT pid  will send a SIGINT 
 * or CNTL-C will send a SIGINT
 *
 * kill -CONT pid  will send a SIGCONT 
 *
 * man 7 signal   # is a man page containing an overviw of signals
 *                # among other info, it list the set of defined signals 
 *                # on this system
 *
 * (newhall, 2013)
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sigcont_handler(int sig);
void sigint_handler(int sig);
void sigalarm_handler(int sig);

/***************************************************/
int main() {

  signal(SIGCONT, sigcont_handler);
  signal(SIGINT, sigint_handler);
  signal(SIGALRM, sigalarm_handler);

  printf("kill -18 %d to send SIGCONT\n", getpid());

  alarm(5);  // sends a SIGALRM in 5 seconds
  while(1) {
    pause(); // wait for a signal to happen
  }
}
/***************************************************/
void sigalarm_handler(int sig) { 
  printf("BEEP, signal number %d\n", sig); 
  fflush(stdout);
  alarm(5);  // sends a SIGALRM in 5 seconds
}
/***************************************************/
void sigcont_handler(int sig) { 
  printf("in sigcont handler function, signal number %d\n.", sig); 
  fflush(stdout);
}
/***************************************************/
void sigint_handler(int sig) { 
  printf("in sigint handler function, signal number %d...exiting\n.", sig); 
  fflush(stdout);
  exit(0);
}
