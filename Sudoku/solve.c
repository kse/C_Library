/*
 * =====================================================================================
 *
 *       Filename:  solve.c
 *
 *    Description:  Reads sudoku from stdin and prints
 *
 *        Version:  1.0
 *        Created:  07-08-2012 14:16:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kasper Sacharias Roos Eenberg (), kse@mahavira.dk
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>

#include "sudoku.h"

int main() {
	sd_solve(stdin);
	return EXIT_SUCCESS;
}
