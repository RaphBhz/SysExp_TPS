CC=gcc
CFLAGS=-W -Wall -ansi -pedantic
EXEC=serveurs vault
OBJ=$(EXEC:=.o)
SRC=$(EXEC:=.c)
DEPS=../TDm1/gestionFichiers gestionServeurs

all: $(EXEC)

$(EXEC): % : %.o gestionServeurs.o ../TDm1/gestionFichiers.o
	$(CC) -o $@ $^

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

gestionFichiers.o: ../TDm1/gestionFichiers.c
	$(CC) $(CFLAGS) -c -o $@ $<

gestionServeurs.o: gestionServeurs.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean mrproper

clean:
	rm -f *.o

mrproper: clean
	rm -f $(EXEC)