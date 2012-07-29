/*
 * =====================================================================================
 *
 *       Filename:  minheap.h
 *
 *    Description:  Header for minheap.c
 *
 *        Version:  1.0
 *        Created:  29-07-2012 01:03:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kasper Sacharis Roos Eenberg
 *
 * =====================================================================================
 */

typedef struct min_heap_key {
	int   val;
	void *data;
} min_heap_key_t;

typedef struct min_heap {
	struct min_heap            *parent;
	struct min_heap            *left;
	struct min_heap            *right;
	struct min_heap_key        *key;
	int                         size;
} min_heap_t;

min_heap_t *min_heap_insert(min_heap_t *A, min_heap_key_t *k);
min_heap_t *min_heap_extract_min(min_heap_t *A, min_heap_key_t **key);

min_heap_t *min_heap_increase_key(min_heap_t *A);
void min_heap_free(min_heap_t *A);
