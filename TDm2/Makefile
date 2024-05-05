CC=gcc
CFLAGS=-W -Wall -ansi -pedantic
EXEC=testIB1 testIB2 testIB3 testII
OBJ=$(EXEC:=.o)
SRC=$(OBJ:.o=.c)
DEPS=gestionProcess.h

all: $(EXEC)

$(EXEC): % : %.o gestionProcess.o
	$(CC) -o $@ $^

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

gestionProcess.o: gestionProcess.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean mrproper

clean:
	rm -f *.o

mrproper: clean
	rm -f $(EXEC)