# makefile variables specifying the compiler and compiler flags
CC = gcc
CFLAGS = -g -Wall -Wvla -Werror -Wno-error=unused-variable

# makefile variable for a library
LIB = mylib.o

# makefile variables  for executable files to compile
TARGET1 = prog
TARGET2 = str
TARGET3 = twoD_method2

# phony targets are not names of files, but just rules to execute
.PHONY: clean

# this is the target for make building executables and the library:
all: $(TARGET1) $(TARGET2) $(TARGET3) 

# compiles prog: notice that it is linking in the mylib.o library
$(TARGET1): $(TARGET1).c $(LIB)
	$(CC) $(CFLAGS) -o $(TARGET1) $(TARGET1).c $(LIB)

# compiles str: notice that it is linking in the readline library
$(TARGET2): $(TARGET2).c
	$(CC) $(CFLAGS) -o $(TARGET2)  $(TARGET2).c  -lreadline

# compiles twoD_method2
$(TARGET3): $(TARGET3).c
	$(CC) $(CFLAGS) -o $(TARGET3)  $(TARGET3).c  

# builds mylib.o
$(LIB): mylib.c mylib.h
	$(CC) $(CFLAGS) -c mylib.c

# this is the target for make clean:
clean:
	$(RM) $(LIB) $(TARGET1) $(TARGET2) $(TARGET3) *.o
