Sudoku solver implementation
============================

Solving techniques
------------------

This solver implements 3 different ways of trying to solve a puzzle.

1. If there are fields that only have one option 
possible, if true, it fills these in.
2. It check each row/column/unit to see if there is a value
only represented once, which means it has to be in the field it is
possible.
3. The final method involves finding the field with the fewest possible values,
and trying each of these values in turn, eliminating branches that fail.

When attempting to solve a sudoku, first we try check (1)->(2) until nothing is 
changed by either. Then we run (3), and (1)->(2) until nothing changes or 
the solution is invalid. If nothing changes, we try running (3) again. 
If solution is invalid, it ends this branch, and attempts with the next 
possible value in a field. If no other possible values exist, we terminate
and mark this sudoku puzzle as unsolvable.

Usage
-----

Simply feed `sd_parse(char *sudoku)` a null-terminated string that contains all
the characters of a sudoku. It will skip unusable characters, but will use
`'.'` as a `0`. It ends before or on receiving a null character.

If you want to use it from the command line, you can compile it with 
`make solver`, which will produce a file called *solve*.
You can then feed solve input a few different way:
    $ ./solve < <filename>
	$ cat <filename> | ./solve
	$ ./solve
	<sudoku followed by ctrl-d>

The above approach uses the function `void sd_solve(FILE *f)`, which reads 
from filehandle *f* until it's seen enough characters to try and solve 
a sudoku, and the prints it to stdout.

Future
------

The names of the functions are quite silly, but i had a slight fever while
coming up with them, so i blame that. 

No validation is done on input sudoku puzzles, just so you know.
