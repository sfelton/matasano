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

EXECS=1 2 3 4 5 6
OBJECTS=crypto_lib.o decode_encode.o

# Executables are just the problem number
all: $(EXECS)

######## MAIN EXECUTABLES ########
1: 1.c decode_encode.o 
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

2: 2.c $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

3: 3.c $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

4: 4.c $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

5: 5.c $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

6: 6.c $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@
######## OBJECTS ########
%.o: $(MY_SRC)/%.c $(MY_INC)/%.h
	$(CC) -c $< $(CFLAGS) -o $@

######## CLEANING ########
clean:
	$(RM) *.o *.dSYM $(EXECS)

cleano:
	$(RM) *.o
