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
*/

/*
 * ============================================================================
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
 * ============================================================================
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
		/* TODO: Change comparison above to fit your usage */
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

	/* TODO: Change comparison below to fit your usage */
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
