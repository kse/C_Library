CC		= gcc
CFLAGS	= -pipe -Wall -Wextra -fomit-frame-pointer -pedantic -std=c99 -O3 -fPIC -g
OBJECTS = sudoku.o

all: $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) $< -c

so: $(OBJECTS)
	$(CC) $(CFLAGS) -shared $(OBJECTS) -o libsudoku.so

clean:
	-rm $(OBJECTS)
	-rm *.so
	-rm solve

solver: $(OBJECTS)
	$(CC) $(CFLAGS) -o solve solve.c $(OBJECTS)
