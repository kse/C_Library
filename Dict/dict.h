/*
 * ============================================================================
 *
 *       Filename:  dict.h
 *
 *    Description:  Create a dictionary over a list of words.
 *
 *        Version:  1.0
 *        Created:  31-07-2012 18:13:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kasper Sacharias Roos Eenberg (), kse@mahavira.dk
 *
 * ============================================================================
 */

struct DICT;
struct DICT_ELEMENT;

typedef struct DICT_ELEMENT {
	char         c;
	struct DICT *p;
} dict_element_t;

typedef struct DICT {
	/* Defines if this is a word */
	char            word;

	/*
	 * Points to parent, if this is the element,
	 * it's null.
	 */
	//struct DICT    *parent;

	int             n;
	dict_element_t *i;
} dict_t;

/* Insert a word into the dictionary D. 
 * if D is null, create a new dictionary */
dict_t* dict_insert(dict_t *D, char *word);

/* Check if word is in dict D */
int dict_lookup(dict_t *D, char *word);

/* Free dictionary D */
void dict_free(dict_t *D);
