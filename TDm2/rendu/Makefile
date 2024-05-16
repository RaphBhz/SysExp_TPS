CC=gcc
CFLAGS=-W -Wall -ansi -pedantic
EXEC=testIB1 testIB2 testIB3 testII testIII1 testIII2 testIII3
OBJ=$(EXEC:=.o)
SRC=$(OBJ:.o=.c)
DEPS=gestionProcess.h ../TDm1/gestionFichiers.h

all: $(EXEC)

$(EXEC): % : %.o gestionProcess.o ../TDm1/gestionFichiers.o
	$(CC) -o $@ $^

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

gestionProcess.o: gestionProcess.c
	$(CC) $(CFLAGS) -c -o $@ $<

gestionFichiers.o: gestionFichiers.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean mrproper

clean:
	rm -f *.o

mrproper: clean
	rm -f $(EXEC)