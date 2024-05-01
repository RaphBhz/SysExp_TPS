include test.sh

CC=gcc
CFLAGS=-W -Wall -ansi -pedantic

all: gestionFichiers

gestionFichiers: gestionFichiers.o test1c.o
	$(CC) -o gestionFichiers gestionFichiers.o test1c.o

gestionFichiers.o: gestionFichiers.c
	$(CC) -o gestionFichiers.o -c gestionFichiers.c $(CFLAGS)

test1c: test1c.o gestionFichiers.o
	$(CC) -o test1c test1c.o gestionFichiers.o $(CFLAGS)

test1c.o: test1c.c gestionFichiers.h
	$(CC) -o test1c.o -c test1c.c $(CFLAGS)

test: gestionFichiers.o test1c.o
	@$(call test1)	

clean:
	rm -rf *.o

mrproper: clean
	rm rf gestionFichiers
