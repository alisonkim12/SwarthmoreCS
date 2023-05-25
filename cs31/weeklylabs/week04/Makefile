CC = gcc
# these extra flags generate easier to read assembly
CFLAGS = -Wall

EXECUTABLES = conditions

# these are the compilation rules:
all:  $(EXECUTABLES)

conditions: conditions.c
	$(CC) $(CFLAGS) -g -o conditions conditions.c


clean:
	$(RM) $(EXECUTABLES)
