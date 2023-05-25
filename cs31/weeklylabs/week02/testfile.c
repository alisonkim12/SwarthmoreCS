/*
 * Swarthmore College, CS 31
 * Copyright (c) 2019 Swarthmore College Computer Science Department,
 * Swarthmore PA, Professor Tia Newhall
 */

/* This is a program to test the readfile library.
 * It takes a command line argument that is the name  of a file to read.
 * To run:
 *   ./testfile <filename>
 *   ./testfile values1
 *   ./testfile values2
 */

#include <stdio.h>      // the C standard I/O library
#include <stdlib.h>     // the C standard library
#include <string.h>     // the C string library
#include "readfile.h"   // the readfile library

#define MAXFILENAME 256

void get_filename_from_commandline(char filename[], int argc, char *argv[]);

/***********************************************************/
int main (int argc, char *argv[]) { 

  char filename[MAXFILENAME]; 
  int  val, ret;

  /* initialize filename string from the command line arguments */
  get_filename_from_commandline(filename, argc, argv);

  ret = open_file(filename); /* try to open file */

  if(ret == -1) {
    printf("ERROR: can't open %s\n", filename);
    exit(1);   /* quit the program */
  }

  /* once open, read values from the file */
  /* if the first value in the file is an int, call read_int to read it
   * in.  read_int is passed the address of an int variable into which
   * the value read in will be stored */
  ret = read_int(&val); 
  if(ret == -1) {
    printf("ERROR: read_int failed\n");
    exit(1);
  }
  printf("read in %d\n", val);

  /* TODO: look at the contents of an example input file and 
   *       try reading in the next few values and print them out
   */

  close_file();  /* close file */
  return 0;
}

/***********************************************************/
/* 
 * This function gets the filename passed in as a command line option
 * and copies it into the filename parameter. It exits with an error
 * message if the command line is badly formed.
 *
 * NOTE: it uses some C features we do not yet know.  It is not 
 *       important that you understand these now.  
 *
 *   filename: the string to fill with the passed filename
 *   argc, argv: the command line parameters from main
 *               (number and strings array)
 */
void get_filename_from_commandline(char filename[], int argc, char *argv[]) {

  if(argc != 2) {
    printf("Usage: ./exp integer_file\n");
    exit(1);
  }
  if(strlen(argv[1]) >= MAXFILENAME) {
    printf("Filename, %s, is too long, cp to shorter name and try again\n",
        filename);
    exit(1);
  }
  strcpy(filename, argv[1]);
}


