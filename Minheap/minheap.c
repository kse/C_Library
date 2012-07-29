/*
 * =====================================================================================
 *
 *       Filename:  minheap.c
 *
 *    Description:  Implementation of minimum heaps.
 *
 *        Version:  1.0
 *        Created:  29-07-2012 01:01:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kasper Sacharias Roos Eenberg
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <assert.h>
#include "minheap.h"

min_heap_t*
min_heap_extract_min(min_heap_t *A, min_heap_key_t **key) {
	min_heap_key_t *t_key = NULL;
	*key = A->key;
	A->size--;

	if(A->size == 0) {
		free(A);
		return NULL;
	} else if(A->left == NULL) {
		A->right = min_heap_extract_min(A->right, &t_key);
		A->key = t_key;
	} else if(A->right == NULL) {
		A->left = min_heap_extract_min(A->left, &t_key);
		A->key = t_key;
	} else if(A->left->key->val > A->right->key->val) {
		A->right = min_heap_extract_min(A->right, &t_key);
		A->key = t_key;
	} else {
		A->left = min_heap_extract_min(A->left, &t_key);
		A->key = t_key;
	}

	return A;
}

min_heap_t* 
min_heap_insert(min_heap_t *A, min_heap_key_t *k) {
	if(A == NULL) {
		min_heap_t *heap = malloc(sizeof(min_heap_t));
		
		heap->key = k;
		heap->left      = NULL;
		heap->right     = NULL;
		heap->parent    = NULL;
		heap->size      = 1;

		return heap;
	}

	if(A->left == NULL) {
		min_heap_t *new = malloc(sizeof(min_heap_t));
		new->size   = 1;
		new->key    = k;
		new->left   = NULL;
		new->right  = NULL;
		new->parent = A;

		A->size++;
		A->left = new;

		return(min_heap_increase_key(A->left));
	} else if(A->right == NULL) {
		min_heap_t *new = malloc(sizeof(min_heap_t));
		new->size   = 1;
		new->key    = k;
		new->left   = NULL;
		new->right  = NULL;
		new->parent = A;

		A->size++;
		A->right = new;

		return(min_heap_increase_key(A->right));
	} else if(A->left->size > A->right->size) {
		A->size++;
		return min_heap_insert(A->right, k);
	} else {
		A->size++;
		return min_heap_insert(A->left, k);
	}
}

min_heap_t *
min_heap_increase_key(min_heap_t *A) {
	min_heap_key_t *t_key;

	if(A->parent == NULL)
		return A;

	if(A->parent->key->val < A->key->val)
		return min_heap_increase_key(A->parent);

	t_key = A->parent->key;
	A->parent->key = A->key;
	A->key = t_key;

	return min_heap_increase_key(A->parent);
}

void
min_heap_free(min_heap_t *A) {
	if(A == NULL)
		return;

	min_heap_free(A->left);
	min_heap_free(A->right);

	if(A->key->data != NULL)
		free(A->key->data);

	free(A->key);
	free(A);
}
