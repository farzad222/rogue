CC = gcc
CFLAGS = -g -Wall -std=c99

ODIR = objectFiles
LDIR = ../lib 

LIBS = -lncurses

DEPS = gameGlobal.h

_OBJ = test-main.o mapgen.o player.c
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

%(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test-main:	$(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY:	clean

clean:
		rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~