CFLAGS=-c -g -std=c23 `pkg-config --cflags xcb`
LDFLAGS=-lxcb `pkg-config --libs xcb`

all: mog

mog: mog.o font.o
	$(CC) $(LDFLAGS) mog.o font.o -o $@

mog.o: mog.c
	$(CC) $(CFLAGS) $< -o $@

font.o: font.c
	$(CC) $(CFLAGS) $< -o $@
