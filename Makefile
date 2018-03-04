# Makefile
IDIR=include/
LDIR=libs/
CFLAGS=-lncurses -lboost_filesystem -lboost_system
CC=g++

drawler: src/*.cpp
	$(CC) -o drawler src/*.cpp -I $(IDIR) -L $(LDIR) $(CFLAGS)
