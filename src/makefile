# Makefile for variational quantum circuit c++ project

CC = g++
CFLAGS = -Wall -g
OBJFILES = main.o vqe.o timeslice.o gate.o binary.o write.o
TARGET = main 

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)

clean:
	rm *.o $(TARGET)
	cd hdl && ./remove_files.sh && cd ..
