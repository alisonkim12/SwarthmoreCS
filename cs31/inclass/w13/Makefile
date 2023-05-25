# to build
#  % make
#
# to clean up all stuff that can be re-built:
#  % make clean
#

CC = gcc
CFLAGS = -Wall -g

LIBDIR = -L./
INCDIR = -I./

LIBS = $(LIBDIRS) -lpthread

TARGET = barrier cond prodcons

.PHONY: clean

all: $(TARGET)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

clean:
	$(RM) *.o core $(TARGET)
