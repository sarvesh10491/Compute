# the compiler: gcc for C program
CC = mpicc
LIBS = -lm -lrt
CFLAGS  = -Wall
# DEPS = queue_ops.h
TARGET = hello

all: $(TARGET)

$(TARGET): $(TARGET).c $(DEPS)
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(LIBS)

clean:
	$(RM) $(TARGET)