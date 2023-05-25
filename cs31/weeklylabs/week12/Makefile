# to build
#  % make
#
# to clean up all stuff that can be re-built:
#  % make clean
#

C = gcc
C++ = g++
CFLAGS = -g -Wall -Wvla -Werror -Wno-error=unused-variable


TARGET = synch deadlock first second third hello racecond
LIBS =  -lpthread


.PHONY: clean

all: $(TARGET)

first: first.c
	$(CC) $(INDIRS) $(CFLAGS) -o first first.c  $(LIBS)

second: second.c
	$(CC) $(INDIRS) $(CFLAGS) -o second second.c  $(LIBS)

third: third.c
	$(CC) $(INDIRS) $(CFLAGS) -o third third.c  $(LIBS)

hello: hello.c
	$(CC) $(INDIRS) $(CFLAGS) -o hello hello.c  $(LIBS)

synch: synch.c
	$(CC) $(INDIRS) $(CFLAGS) -o synch synch.c  $(LIBS)

deadlock: deadlock.c
	$(CC) $(INDIRS) $(CFLAGS) -o deadlock deadlock.c  $(LIBS)

racecond: racecond.c
	$(CC) $(INDIRS) $(CFLAGS) -o racecond racecond.c  $(LIBS)


clean:
	$(RM) *.o core $(TARGET)
