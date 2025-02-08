CFLAGS=-Wall -ggdb -std=c17 -pedantic
LIBS=

gp: main.c
	$(CC) $(CFLAGS) -o gp main.c $(LIBS)
