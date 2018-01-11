CC=gcc
CFLAGS=-std=c99 -pedantic -Wall
XFT_CFLAGS=$(shell pkg-config --cflags freetype2)
LDFLAGS=-lX11
XFT_LDFLAGS=$(shell pkg-config --libs freetype2) -lXft

main: main.c
	$(CC) $(CFLAGS) $(XFT_CFLAGS) $(LDFLAGS) $(XFT_LDFLAGS) main.c -o main

clean:
	rm -f main
