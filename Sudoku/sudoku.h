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
 *       Filename:  sudoku.h
 *
 *    Description:  Header for sudoku solving code
 *
 *        Version:  1.0
 *        Created:  06-08-2012 20:51:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kasper Sacharias Roos Eenberg (kse@mahavira.dk)
 *
 * ============================================================================
 */

enum SD_STATUS {
	SD_UNSOLVABLE,
	SD_SOLVED,
	SD_NOT_SOLVED
};

typedef struct SUDOKU_FIELD {
	int val;
	char c[9];
} sd_field_t;

typedef struct SUDOKU {
	sd_field_t field[81];
	char solved;
} sd_t;

sd_t *
sd_parse(char *sudoku);

void
sd_print(sd_t *sd);

void                                                                            
sd_solve(FILE *input);
