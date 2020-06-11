# the compiler: gcc for C program
CC = gcc
LIBS = -pthread -lm -lrt
CFLAGS  = -Wall
# DEPS = queue_ops.h
TARGET = base

all: $(TARGET)

$(TARGET): $(TARGET).c $(DEPS)
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(LIBS)

clean:
	$(RM) $(TARGET)