# to build 
#  % make
#
# to clean up all stuff that can be re-built:
#  % make clean
#

CC = gcc
CFLAGS = -g -Wall -Wvla -Werror -Wno-error=unused-variable -Wno-error=unused-function

LIBS = -lpthread

TARGET = max
TARGET1 = hello

.PHONY: clean

all: $(TARGET1) $(TARGET) 

$(TARGET1): $(TARGET1).c
	$(CC) $(INDIRS) $(CFLAGS) -o $(TARGET1) $(TARGET1).c  $(LIBS) 


$(TARGET): $(TARGET).c
	$(CC) $(INDIRS) $(CFLAGS) -o $(TARGET) $(TARGET).c  $(LIBS) 

clean:
	$(RM) *.o $(TARGET)  $(TARGET1)

