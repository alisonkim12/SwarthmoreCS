/* An program to test functions defined in the parsecmd library
 * the parsecmd.h file contains the function prototypes for 
 * library.  Look at these, and their comments, to determine
 * what functions are in the library and how to call them
 * (newhall, 2015)
 */
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include <sys/types.h> 

// here is the syntax for including a local header file:
#include"parsecmd.h"

int main( ){ 

  char cmdline[MAXLINE];
  char *args[MAXARGS];   
  int bg, i, ret;

  printf("This program tests out the parsecmd library\n");
  printf("To exit this program type CNTL-D (or CNTL-C)\n");

  while(1) { // loop forever

    printf("\nEnter a sample command line: ");  
    fflush(stdout);

    // fgets: reads in a full line entered by the user (or up to
    //        MAXLINE chars) and stores it in cmdline
    if ((fgets(cmdline, MAXLINE, stdin) == NULL) && ferror(stdin)) {
      perror("fgets error");
    }
    if (feof(stdin)) { /* End of file (ctrl-d) */
      fflush(stdout);
      exit(0);
    }

    printf("The command line string entered was: %s\n", cmdline);

    // call the parse_cmd function:
    ret = parse_cmd(cmdline, args, &bg);
    if(ret) {
      printf("parse_cmd return error value %d, exiting...\n", ret);
      exit(1);
    }

    // print out each string created from a token in the command string
    i = 0;
    while(args[i] != NULL) {
      printf("args[%d] = %s\n", i, args[i]);
      i++;
    }
    if(bg) {
      printf("command line has & at the end\n");
    }

  }
  return 0;
}
/******************************************************************/
