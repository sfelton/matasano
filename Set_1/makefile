#Compiler
CC=gcc

# compiler flags
# -g 	include debugging information
# -Wall throw all (maybe all) compiler warnings 
CFLAGS=-g -Wall

# Executables are just the problem number
EXECS=1 2

RM=rm -rf

all: $(EXECS)

1: 1.c
	$(CC) $(CFLAGS) $< -o $@

2: 2.c
	$(CC) $(CFLAGS) $< -o $@
clean:
	$(RM) *.o *.dSYM $(EXECS)

cleano:
	$(RM) *.o
