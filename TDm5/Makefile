CC=gcc
CFLAGS=-W -Wall -ansi -pedantic
ARGS=-lpthread -lrt
EXEC=main
OBJ=$(EXEC:=.o)
SRC=$(EXEC:=.c)
DEPS=../TDm1/gestionFichiers.h

all: $(EXEC)

$(EXEC): % : %.o ../TDm1/gestionFichiers.o
	$(CC) -o $@ $^ $(ARGS)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< $(ARGS)

gestionFichiers.o: ../TDm1/gestionFichiers.c
	$(CC) $(CFLAGS) -c -o $@ $< $(ARGS)

.PHONY: clean mrproper

clean:
	rm -f *.o

mrproper: clean
	rm -f $(EXEC)