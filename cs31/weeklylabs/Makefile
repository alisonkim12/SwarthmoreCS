# Makefile for inclass code
# make: compile all example code
# make clean: clean it up
# make soln: compiles dosomethingAnswer.s for an answer to the IA32 assembly 

# CC for regular build and for valgrind build
CC = gcc

# gcc flags for IA32 compiling
C32FLAGS = -Wall -m32 -O0 -fno-asynchronous-unwind-tables -fno-pic


OBJS = $(SRCS:.c=.o)

all: prog

prog: prog.c dosomething.s
	$(CC) $(C32FLAGS) -o prog prog.c dosomething.s 

soln: dosomething.c
	$(CC) $(C32FLAGS) -S -o dosomethingAnswer.s dosomething.c

clean: 
	rm -f  dosomethingAnswer.s prog

