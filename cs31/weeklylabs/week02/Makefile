# make is a unix tool that we will use to simpifying the C compilation
# process.  Instead of typing in 'gcc -g -Wall -o outfile sourcefile.c'
# to build a single executable file.  You can just type in 'make' to 
# build one or more executable files.  Typing in 'make clean' will remove
# all executable files (this should be done prior to submitting lab
# assignments).
#
# This makefile has rules for building 3 different executable files,
# one for each of the .c files in this directory.
#
# We will talk about makefile syntax over the course of the semester, for
# now you can just use this makefile, but note that there are "rules" that
# look very similar to the gcc commands you would type in by hand.

# define some makefile variables: which compiler and complier flags to use
CC = gcc
CFLAGS = -g -Wall -Wvla -Werror -Wno-error=unused-variable

EXECUTABLES = testprog arrays 

# these are the compilation rules:  
all:  $(EXECUTABLES) testfile

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

testfile:  testfile.c readfile.c readfile.h
	$(CC) $(CFLAGS) -o $@ testfile.c readfile.c

clean:
	$(RM) $(EXECUTABLES) testfile
