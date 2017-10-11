# Makefile
IDIR=include/
LDIR=libs/
CFLAGS=-lncurses
CC=g++

drawler: src/*.cpp
	$(CC) -o drawler src/*.cpp -I $(IDIR) -L $(LDIR) $(CFLAGS)
