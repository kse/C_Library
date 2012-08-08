/*
Copyright (c) 2012, Kasper Sacharias Roos Eenberg
All rights reserved.                                                           
                                                                               
Redistribution and use in source and binary forms, with or without             
modification, are permitted provided that the following conditions are met:    
    * Redistributions of source code must retain the above copyright           
      notice, this list of conditions and the following disclaimer.            
    * Redistributions in binary form must reproduce the above copyright        
      notice, this list of conditions and the following disclaimer in the      
      documentation and/or other materials provided with the distribution.     
    * Neither the name of the <organization> nor the                           
      names of its contributors may be used to endorse or promote products     
      derived from this software without specific prior written permission.    
                                                                               
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED  
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE         
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY             
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES     
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;   
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND    
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT     
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS  
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                   
 * ============================================================================
 *
 *       Filename:  sudoku.c
 *
 *    Description:  Sudoku solving Code
 *
 *        Version:  1.0
 *        Created:  06-08-2012 20:39:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kasper Sacharias Roos Eenberg (kse@mahavira.dk)
 *
 * ============================================================================
 */
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "sudoku.h"

int
sd_solve_by_unique(sd_t *sd) {
	int i, j, p, k, z;
	int changed = 0;

	for(i = 0; i < 81; i++) {
		int val[10];
		memset(val, 0, 10*sizeof(int));

		p = (i % 9) - (i % 9) % 3 + 27*(i/27);

		for(j = p; j < p + 3; j++) {
			for(k = 1; k < 10; k++) {
				if(sd->field[j].c[k] == 1)
					val[k] += 1;

				if(sd->field[j + 9].c[k] == 1)
					val[k] += 1;

				if(sd->field[j + 18].c[k] == 1)
					val[k] += 1;
			}
		}

		for(k = 1; k < 10; k++) {
			if(val[k] == 1) {
				for(j = p; j < p + 3; j++) {
					if(sd->field[j].c[k] == 1) {
						sd->field[j].val = k;
						sd->field[j].c[k] = 0;
						changed = 1;
						for(z = j - (j % 9); z < j - (j % 9) + 9; z++)
							sd->field[z].c[k] = 0;

						for(z = (j % 9); z < 81; z += 9)
							sd->field[z].c[k] = 0;

						for(z = 1; z < 10; z++)
							sd->field[j].c[z] = 0;
					}

					if(sd->field[j + 9].c[k] == 1) {
						int f = j + 9;
						sd->field[j + 9].val = k;
						sd->field[j + 9].c[k] = 0;
						changed = 1;

						for(z = f - (f % 9); z < f - (f % 9) + 9; z++)
							sd->field[z].c[k] = 0;

						for(z = ((f % 9)); z < 81; z += 9)
							sd->field[z].c[k] = 0;

						for(z = 1; z < 10; z++)
							sd->field[j + 9].c[z] = 0;
					}

					if(sd->field[j + 18].c[k] == 1) {
						int f = j + 18;

						sd->field[j + 18].val = k;
						sd->field[j + 18].c[k] = 0;
						changed = 1;

						for(z = f - (f % 9); z < f - (f % 9) + 9; z++)
							sd->field[z].c[k] = 0;

						for(z = ((f % 9)); z < 81; z += 9)
							sd->field[z].c[k] = 0;

						for(z = 1; z < 10; z++)
							sd->field[j + 18].c[z] = 0;
					}
				}
			}
		}
	}


	for(i = 0; i < 81; i += 9) {
		int val[10];

		memset(val, 0, 10*sizeof(int));
		for(j = i; j < i + 9; j++) {
			for(k = 1; k < 10; k++) {
				if(sd->field[j].c[k] == 1)
					val[k]++;
			}
		}

		for(k = 1; k < 10; k++) {
			if(val[k] == 1) {
				for(j = i - (i % 9); j < i - (i % 9) + 9; j++) {
					if(sd->field[j].c[k] == 1) {
						sd->field[j].val = k;
						sd->field[j].c[k] = 0;
						changed = 1;

						for(z = 1; z < 10; z++)
							sd->field[j].c[z] = 0;

						for(z = ((j % 9)); z < 81; z += 9)
							sd->field[z].c[k] = 0;

						p = (j % 9) - (j % 9) % 3 + 27*(j/27);
						for(z = p; z < p + 3; z++) {
							sd->field[z].c[k] = 0;
							sd->field[z + 9].c[k] = 0;
							sd->field[z + 18].c[k] = 0;
						}
						break;
					}
				}
			}
		}
	}
	for(i = 0; i < 9; i++) {
		int val[10];

		memset(val, 0, 10*sizeof(int));
		for(j = (i % 9); j < 81; j += 9) {
			for(k = 1; k < 10; k++) {
				if(sd->field[j].c[k] == 1)
					val[k]++;
			}
		}

		for(k = 1; k < 10; k++) { 
			if(val[k] == 1) {
				for(j = ((i % 9)); j < 81; j += 9) {
					if(sd->field[j].c[k] == 1) {
						sd->field[j].val = k;
						sd->field[j].c[k] = 0;
						changed = 1;

						for(z = 1; z < 10; z++)
							sd->field[j].c[z] = 0;

						for(z = j - (j % 9); z < j - (j % 9) + 9; z++)
							sd->field[z].c[k] = 0;

						p = (j % 9) - (j % 9) % 3 + 27*(j/27);
						for(z = p; z < p + 3; z++) {
							sd->field[z].c[k] = 0;
							sd->field[z + 9].c[k] = 0;
							sd->field[z + 18].c[k] = 0;
						}

						break;
					}
				}
			}
		}
	}

	sd->solved = SD_SOLVED;
	for(i = 0; i < 81; i++) {
		if(sd->field[i].val == 0) {
			sd->solved = SD_NOT_SOLVED;
		}
	}

	return changed;
}

sd_t *
sd_enforce_constraints(sd_t *sd) {
	int i, j, p;

	for(i = 0; i < 81; i++) {
		memset(sd->field[i].c, 1, 10);

		/* Check unit */
		p = (i % 9) - (i % 9) % 3 + 27*(i/27);
		for(j = p; j < p + 3; j++) {
			sd->field[i].c[sd->field[j].val] = 0;
			sd->field[i].c[sd->field[j + 9].val] = 0;
			sd->field[i].c[sd->field[j + 18].val] = 0;
		}

		/* Check row */
		for(j = i - (i % 9); j < i - (i % 9) + 9; j++) {
			sd->field[i].c[sd->field[j].val] = 0;
		}

		/* Check column */
		for(j = ((i % 9)); j < 81; j += 9) {
			sd->field[i].c[sd->field[j].val] = 0;
		}

		/* Zero out all fields with a value set */
		if(sd->field[i].val != 0) {
			for(j = 0; j < 10; j++) {
				sd->field[i].c[j] = 0;
			}
		}
	}

	return sd;
}

int
sd_solve_by_constraints(sd_t *sd) {
	int changed = 1, nval, val;
	int i, j;

	while(changed) {
		changed = 0;

		for(i = 0; i < 81; i++) {
			nval = 0;
			val = 0;
			for(j = 1; j < 10; j++) {
				if(sd->field[i].c[j] != 0) {
					val = j;
					nval++;
				}
			}

			if(nval == 1) {
				changed = 1;

				sd->field[i].val = val;

				/* Progate changes by :*/
				/* Column */
				for(j = ((i % 9)); j < 81; j += 9) {
					sd->field[j].c[val] = 0;
				}

				/* Row */
				for(j = i - (i % 9); j < i - (i % 9) + 9; j++) {
					sd->field[j].c[val] = 0;
				}

				/* Unit */
				int p;
				p = (i % 9) - (i % 9) % 3 + 27*(i/27);
				for(j = p; j < p + 3; j++) {
					sd->field[j].c[val] = 0;
					sd->field[j + 9].c[val] = 0;
					sd->field[j + 18].c[val] = 0;
				}
			} else if(nval == 0 && sd->field[i].val == 0) {
				/* Unsolvable sudoku */
				return SD_UNSOLVABLE;
			}
		}
	}

	sd->solved = SD_SOLVED;
	for(i = 0; i < 81; i++) {
		if(sd->field[i].val == 0) {
			sd->solved = SD_NOT_SOLVED;
		}
	}

	if(sd->solved == SD_SOLVED) {
		return SD_SOLVED;
	} else {
		return SD_NOT_SOLVED;
	}
}

sd_t *
sd_solve_by_guessing(sd_t *sd) {
	int min = 20, mini = 0;
	int i, j, k;
	sd_t *nsd = malloc(sizeof(sd_t));

	/* Sanity check to not bother solving, if already solved */
	if(sd->solved == SD_SOLVED) {
		return sd;
	}

	sd->solved = SD_NOT_SOLVED;
	memset(nsd, 0, sizeof(sd_t));

	for(i = 0; i < 81; i++) {
		k = 0;		
		for(j = 1; j < 10; j++) {
			if(sd->field[i].c[j] == 1)
				k++;
		}

		if(k > 0 && k < min) {
			min = k;
			mini = i;
		}

	}

	for(i = 0; i < 10; i++) {
		if(sd->field[mini].c[i] == 0)
			continue;

		memcpy(nsd, sd, sizeof(sd_t));


		nsd->field[mini].val = i;
		memset(nsd->field[mini].c, 0, 10);
		nsd->solved = SD_NOT_SOLVED;

		sd_enforce_constraints(nsd);

		while(nsd->solved != SD_UNSOLVABLE) {
			do {
				if(nsd->solved == SD_SOLVED) {
					free(sd);
					return nsd;
				}

				enum SD_STATUS st = sd_solve_by_constraints(nsd);

				if(st == SD_SOLVED) {
					free(sd);
					nsd->solved = SD_SOLVED;
					return nsd;
				} else if(st == SD_UNSOLVABLE) {
					nsd->solved = SD_UNSOLVABLE;
					break;
				}
			} while(sd_solve_by_unique(nsd));

			nsd = sd_solve_by_guessing(nsd);
		}
	}

	if(!nsd->solved == SD_SOLVED) {
		free(nsd);
		sd->solved = SD_UNSOLVABLE;
		return sd;
	}

	free(sd);
	return nsd;
}

void
sd_solve(FILE *input) {
	sd_t *sd = malloc(sizeof(sd_t));
	int i = 0;
	int puzzles = 0;
	char c;
	clock_t start, diff;

	while(!feof(input)) {
		memset(sd, 0, sizeof(sd_t));
		i = 0;
		while(i < 81) {
			if(feof(input))
				break;

			if(fread(&c, 1, 1, input) == 0) {
				/* We've exhausted out input */
				break;
			}

			if(!isdigit(c) && c != '.') {
				continue;
			}

			if(c == '.') {
				sd->field[i].val = 0;
			} else {
				sd->field[i].val = c - '0';
			}

			i++;
		}

		if(i != 81) {
			/* We've not found enough to allocate sudoku */
			break;
		}

		start = clock();

		/* Mark what values are possible in what fields */
		sd_enforce_constraints(sd);

		/* First, try solving by simple constraint checking */
		do {
			enum SD_STATUS st = sd_solve_by_constraints(sd);

			if(st == SD_SOLVED) {
				sd->solved = SD_SOLVED;
				break;
			} else if(st == SD_UNSOLVABLE) {
				sd->solved = SD_UNSOLVABLE;
				break;
			}

		} while(sd_solve_by_unique(sd));

		/* If constraint checking fails, the try making random guesses */
		if(sd->solved != SD_SOLVED) {
			sd = sd_solve_by_guessing(sd);
		}

		diff = clock() - start;

		puzzles++;
		i = diff * 1000 / CLOCKS_PER_SEC;

		printf("Solved is: %d\n", sd->solved);

		if(sd->solved == SD_SOLVED) {
			printf("Successfully solved puzzle %d in %d.%ds:\n", 
					puzzles, i/1000, i%1000);
		} else if(sd->solved == SD_UNSOLVABLE) {
			printf("Failed unsolvable puzzle %d:\n", puzzles);
		} else {
			printf("Failed solving puzzle %d:\n", puzzles);
		}
		sd_print(sd);
	}

	free(sd);
}

sd_t *
sd_parse(char *sudoku) {
	sd_t *sd = malloc(sizeof(sd_t));
	int i = 0, p = 0;
	char c;

	memset(sd, 0, sizeof(sd_t));

	while(i < 81) {
		c = sudoku[p];

		/* Premature end of stream */
		if(c == '\0')
			break;

		if(!isdigit(c) && c != '.') {
			p++;
			continue;
		}

		if(c == '.') {
			sd->field[i].val = 0;
		} else {
			sd->field[i].val = c - '0';
		}

		p++;
		i++;
	}

	if(i != 81) {
		/* We've not found enough to allocate sudoku */
		return NULL;
	}

	/* Mark what values are possible in what fields */
	sd_enforce_constraints(sd);

	/* First, try solving by simple constraint checking */
	do {
		enum SD_STATUS st = sd_solve_by_constraints(sd);

		if(st == SD_SOLVED)
			return sd;
		else if(st == SD_UNSOLVABLE) {
			sd->solved = SD_UNSOLVABLE;
			return sd;
		}

	} while(sd_solve_by_unique(sd));

	/* If constraint checking fails, the try making random guesses */
	sd = sd_solve_by_guessing(sd);

	return sd;
}

void
sd_print(sd_t *sd) {
	int i;

#ifdef DEBUG
	int j;
#endif

	printf("+-------+-------+-------+\n");
	for(i = 0; i < 81; i++) {
		if(i == 0) 
			printf("| ");

		if((i % 9) == 3 || (i % 9) == 6) {
			printf(" ");
		}

		printf("%d ", sd->field[i].val);


		if((i % 9) == 2 || (i % 9) == 5) {
			printf("|");
		}

		if(i > 0 && (i%9) == 8 && !(i == (3*9) || i == (6*9))) {
			printf("|");
		}

		if(i > 0 && (i%9) == 8) {
			printf("\n");
		}

		if(i == (3*9-1) || i == (6*9-1)) {
			printf("+-------+-------+-------+\n");
		}

		if(i > 0 && (i%9) == 8 && !(i == (3*9) || i == (6*9)) && i != 80) {
			printf("| ");
		}
	}
	printf("+-------+-------+-------+\n");

#ifdef DEBUG
	for(i = 0; i < 81; i++) {
		unsigned int v = 0;
		for(j = 1; j < 10; j++) {
			if(sd->field[i].c[j] == 1) {
				v = v * 10;
				v += j;
			}
		}

		printf("%9d", v);

		if(i > 0 && (i%9) == 8) {
			printf("\n");
		}

		if((i % 9) == 2 || (i % 9) == 5) {
			printf(" |");
		}

		if(i == (3*9-1) || i == (6*9-1)) {
			printf("----------------------------+");
			printf("----------------------------+");
			printf("----------------------------\n");
		}
	}
#endif
}
