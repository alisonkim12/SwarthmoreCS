
CC = gcc
CFLAGS = -g -Wall -Wvla -Werror -Wno-error=unused-variable

# the path to the parsecmd.o library implementation:
#    ls /home/newhall/public/cs31/parsecmd.o
#    file /home/newhall/public/cs31/parsecmd.o
LIBDIR=/home/newhall/public/cs31


TARGET = globalvars
TARGET2 = signals
TARGET3 = circqueue
TARGET4 = testparsecmd

all: $(TARGET) $(TARGET2)  $(TARGET3) $(TARGET4)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o  $(TARGET) $(TARGET).c

$(TARGET2): $(TARGET2).c
	$(CC) $(CFLAGS) -o  $(TARGET2) $(TARGET2).c

$(TARGET3): $(TARGET3).c
	$(CC) $(CFLAGS) -o  $(TARGET3) $(TARGET3).c

$(TARGET4): $(TARGET4).c
	$(CC) $(CFLAGS) -o  $(TARGET4) $(TARGET4).c $(LIBDIR)/parsecmd.o
clean:
	$(RM) $(TARGET) $(TARGET2) $(TARGET3) $(TARGET4)


