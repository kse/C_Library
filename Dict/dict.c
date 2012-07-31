/*
 * ============================================================================
 *
 *       Filename:  dict.c
 *
 *    Description:  Create a dictionary over a list of words.
 *
 *        Version:  1.0
 *        Created:  31-07-2012 18:08:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kasper Sacharias Roos Eenberg (), kse@mahavira.dk
 *
 * ============================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dict.h"

int c_dict = 0;
int c_dict_e = 0;

void 
dict_free(dict_t *D) {
	int i;

	if(D == NULL)
		return;

	for(i = 0; i < D->n; i++) {
		dict_free(D->i[i].p);
	}

	if(D->n != 0)
		free(D->i);

	free(D);

	return;
}

int
dict_lookup(dict_t *D, char *word) {
	int i = 0, j;
	dict_t *old;
	char c;

	if(D == NULL) {
		return 0;
	}

	old = D;
	while((c = word[i++]) != '\0') {
		int match = 0;

		for(j = 0; j < old->n; j++) {
			if(old->i[j].c == c) {
				match = 1;
				break;
			}
		}

		if(match)
			old = old->i[j].p;
		else
			return 0;
	}

	if(old->word == 1)
		return 1;
	else 
		return 0;
}

dict_t*
dict_insert(dict_t *D, char *word) {
	int i = 0, j;
	char c;
	dict_t *old;

	if(D == NULL) {
		D = malloc(sizeof(dict_t));
		memset(D, 0, sizeof(dict_t));
		D->n = 0;
		c_dict++;
	}

	old = D;
	while((c = word[i++]) != '\0') {
		int match = 0;

		for(j = 0; j < old->n; j++) {
			if(old->i[j].c == c) {
				match = 1;
				break;
			}
		}

		if(!match) {
			dict_t *d = malloc(sizeof(dict_t));
			if(d == NULL) {
				printf("Allocation of new dict_t failed!");
				exit(EXIT_FAILURE);
			}
			memset(d, 0, sizeof(dict_t));
			c_dict++;

			old->i = realloc(old->i, sizeof(dict_element_t) * (old->n + 1));
			c_dict_e++;
			old->n++;
			old->i[old->n - 1].c = c;
			old->i[old->n - 1].p = d;
			d->parent = old;
			d->n = 0;
			d->i = NULL;

			j = old->n - 1;
		}

		old = old->i[j].p;
	}

	old->word = (char)1;

	return D;
}
