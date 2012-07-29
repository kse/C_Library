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
 * ============================================================================
 */

/* TODO: Change this structure to make it contain what you need */
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
