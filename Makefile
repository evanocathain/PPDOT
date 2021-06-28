CC = gcc
CFLAGS = -c -O3 -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64
INCL = -I./ #-I/home/pulsar/pgplot/
LIBS = -lm

all: ppdot strip clean

ppdot: ppdot.o
	$(CC) ppdot.o -o ppdot $(LIBS)

ppdot.o: ppdot.c
	$(CC) $(CFLAGS) $(INCL) ppdot.c

strip:
	strip ppdot

clean:
	rm -f *~ *.o
