//
//  getword.cpp
//  processor
//
//  Created by Alexandra Korabulina on 27.10.2020.
//

//--------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

//--------------------------------------------------------------------------------

//! Gets next word from .txt file
//!
//! @param [in] f pointer to the opened file
//!
//! @return pointer to string with word in case there are still some words, NULL otherwise
//!
//! @note caller must provide free of allocated memory
char * GetNextWord(FILE * f) {
    int current_position = 0;
    char current_symbol = fgetc(f);
    while ((current_symbol == ' ') || (current_symbol == '\n')) {
        current_symbol = fgetc(f);
    }
    if (current_symbol == EOF) {
        return NULL;
    }
    char * word = (char *)calloc(sizeof(char), 1024);
    while ((current_symbol != '\n') && (current_symbol != ' ') && (current_symbol != EOF)) {
        word[current_position] = current_symbol;
        current_symbol = fgetc(f);
        current_position++;
    }
    word[current_position] = '\0';
    return word;
}

//--------------------------------------------------------------------------------