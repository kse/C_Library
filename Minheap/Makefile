CC		= gcc
CFLAGS	= -pipe -Wall -Wextra -fomit-frame-pointer -pedantic -std=c99 -O3
OBJECTS = minheap.o

all: $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	-rm $(OBJECTS)
