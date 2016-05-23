#Compiler
CC=gcc

# Openssl Locations for brew installed openssl on OS X
OPENSSL_LIB=/usr/local/opt/openssl/lib
OPENSSL_INC=/usr/local/opt/openssl/include

# compiler flags
# -g 	include debugging information
# -Wall throw all (maybe all) compiler warnings 
CFLAGS=-g -Wall -I$(OPENSSL_INC)
LDFLAGS=-L$(OPENSSL_LIB) -lcrypto

# Executables are just the problem number
EXECS=1 2

RM=rm -rf

all: $(EXECS)

1: 1.c
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@

2: 2.c
	$(CC) $(CFLAGS) $< -o $@
clean:
	$(RM) *.o *.dSYM $(EXECS)

cleano:
	$(RM) *.o
