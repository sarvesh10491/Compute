# the compiler: gcc for C program
CC = gcc
LIBS = -pthread -lm -lrt
CFLAGS  = -Wall
DEPS = mqueue_ops.h datapkt_ops.h
TARGET = mqueue

all: $(TARGET)

$(TARGET): $(TARGET).c $(DEPS)
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(LIBS)

clean:
	$(RM) $(TARGET)