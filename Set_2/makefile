#Compiler
CC=gcc

# Openssl Locations for brew installed openssl on OS X
OPENSSL_LIB=/usr/local/opt/openssl/lib
OPENSSL_INC=/usr/local/opt/openssl/include

MY_INC=../inc
MY_SRC=../src

# compiler flags
# -g 	include debugging information
# -Wall throw all (maybe all) compiler warnings 
CFLAGS=-g -Wall -Werror -I$(MY_INC) -I$(OPENSSL_INC)
LDFLAGS=-lcrypto


RM=rm -rf

EXECS=9 10 test
OBJECTS=crypto_lib.o decode_encode.o

# Executables are just the problem number
all: $(EXECS) 

######## MAIN EXECUTABLES ########
9: 9.c  
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

10: 10.c $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

test: test.c $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

######## OBJECTS ########
%.o: $(MY_SRC)/%.c $(MY_INC)/%.h
	$(CC) -c $< $(CFLAGS) -o $@

######## CLEANING ########
clean:
	$(RM) *.o *.dSYM $(EXECS)

cleano:
	$(RM) *.o
