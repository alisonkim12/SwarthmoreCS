# This is a simple makefile with rules for compiling two
# executable programs (functions and firstprog) from their 
# corresponding C program files (functions.c and firstprog.c)
#
# make       : to compile the programs
# make clean : to remove the compiled executable files
#

all: firstprog functions 

functions: functions.c 
	gcc -g -o functions functions.c

firstprog: firstprog.c 
	gcc -g -o firstprog firstprog.c

clean:
	$(RM) functions firstprog  
