CC=gcc
CFLAGS=-c -Wall -std=c99

all: hashTable

hashTable: main.o data.o data_cstring.o data_person.o ioutils.o mymalloc.o table.o
	$(CC) main.o data.o data_cstring.o data_person.o ioutils.o mymalloc.o table.o -o hashTable

main: main.c
	$(CC) $(CFLAGS) main.c

table:
	$(CC) $(CFLAGS) table.c

data: 
	$(CC) $(CFLAGS) data.c
	
data_cstring: 
	$(CC) $(CFLAGS) data_cstring.c

data_person: 
	$(CC) $(CFLAGS) data_person.c
	
ioutils: 
	$(CC) $(CFLAGS) ioutils.c

mymalloc: 
	$(CC) $(CFLAGS) mymalloc.c
	
clean:
	rm *.o hashTable
