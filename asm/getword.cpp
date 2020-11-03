//
//  getword.cpp
//  processor
//
//  Created by Alexandra Korabulina on 27.10.2020.
//

//--------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//--------------------------------------------------------------------------------

//! Gets next word from .txt file
//!
//! @param [in] f pointer to the opened file
//! @param [out] word place to write the next word with '\0' symbol at last position
//!
//! @return quantity of symbols in the next word, or 0 if next word can't be read
int GetNextWord(FILE * f, char * word) {
    if (word == NULL) {
        return 0;
    }
    int current_position = 0;
    char current_symbol = fgetc(f);
    while ((current_symbol == ' ') || (current_symbol == '\n')) {
        current_symbol = fgetc(f);
    }
    if (current_symbol == EOF) {
        return 0;
    }
    while ((current_symbol != '\n') && (current_symbol != ' ') && (current_symbol != EOF)) {
        word[current_position] = current_symbol;
        current_symbol = fgetc(f);
        current_position++;
        if (current_position >= 99) {
            return 0;
        }
    }
    word[current_position] = '\0';
    return current_position;
}

//--------------------------------------------------------------------------------
