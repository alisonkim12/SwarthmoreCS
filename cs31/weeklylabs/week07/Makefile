CC = gcc
C++ = g++
CFLAGS = -g -Wall -Wvla -Werror -Wno-error=unused-variable


TARGET = twoDarray
TARGET2 = fileio
TARGET3 = commandlineargs

all: $(TARGET) $(TARGET2) $(TARGET3) 

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o  $(TARGET) $(TARGET).c

$(TARGET2): $(TARGET2).c
	$(CC) $(CFLAGS) -o  $(TARGET2) $(TARGET2).c

$(TARGET3): $(TARGET3).c
	$(CC) $(CFLAGS) -o  $(TARGET3) $(TARGET3).c


clean:
	$(RM) $(TARGET) $(TARGET2) $(TARGET3)
