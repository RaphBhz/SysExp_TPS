CC=gcc
CFLAGS=-W -Wall -ansi -pedantic

all: gestionFichiers test1c test2b1 test2b2 test2b3 test2b4 test2b5 test3b1 test3b2 test3b3

gestionFichiers: gestionFichiers.o test1c.o
	$(CC) -o gestionFichiers gestionFichiers.o test1c.o $(CFLAGS)

gestionFichiers.o: gestionFichiers.c
	$(CC) -o gestionFichiers.o -c gestionFichiers.c $(CFLAGS)

test1c: test1c.o gestionFichiers.o
	$(CC) -o test1c test1c.o gestionFichiers.o $(CFLAGS)

test1c.o: test1c.c gestionFichiers.h
	$(CC) -o test1c.o -c test1c.c $(CFLAGS)

test2b1: test2b1.o gestionFichiers.o
	$(CC) -o test2b1 test2b1.o gestionFichiers.o $(CFLAGS)

test2b1.o: test2b1.c gestionFichiers.h
	$(CC) -o test2b1.o -c test2b1.c $(CFLAGS)

test2b2: test2b2.o gestionFichiers.o
	$(CC) -o test2b2 test2b2.o gestionFichiers.o $(CFLAGS)

test2b2.o: test2b2.c gestionFichiers.h
	$(CC) -o test2b2.o -c test2b2.c $(CFLAGS)

test2b3: test2b3.o gestionFichiers.o
	$(CC) -o test2b3 test2b3.o gestionFichiers.o $(CFLAGS)

test2b3.o: test2b3.c gestionFichiers.h
	$(CC) -o test2b3.o -c test2b3.c $(CFLAGS)

test2b4: test2b4.o gestionFichiers.o
	$(CC) -o test2b4 test2b4.o gestionFichiers.o $(CFLAGS)

test2b4.o: test2b4.c gestionFichiers.h
	$(CC) -o test2b4.o -c test2b4.c $(CFLAGS)

test2b5: test2b5.o gestionFichiers.o
	$(CC) -o test2b5 test2b5.o gestionFichiers.o $(CFLAGS)

test2b5.o: test2b5.c gestionFichiers.h
	$(CC) -o test2b5.o -c test2b5.c $(CFLAGS)

test3b1: test3b1.o gestionFichiers.o
	$(CC) -o test3b1 test3b1.o gestionFichiers.o $(CFLAGS)

test3b1.o: test3b1.c gestionFichiers.h
	$(CC) -o test3b1.o -c test3b1.c $(CFLAGS)

test3b2: test3b2.o gestionFichiers.o
	$(CC) -o test3b2 test3b2.o gestionFichiers.o $(CFLAGS)

test3b2.o: test3b2.c gestionFichiers.h
	$(CC) -o test3b2.o -c test3b2.c $(CFLAGS)

test3b3: test3b3.o gestionFichiers.o
	$(CC) -o test3b3 test3b3.o gestionFichiers.o $(CFLAGS)

test3b3.o: test3b3.c gestionFichiers.h
	$(CC) -o test3b3.o -c test3b3.c $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm rf gestionFichiers
