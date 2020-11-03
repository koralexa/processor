//
//  assembler.h
//  processor
//
//  Created by Alexandra Korabulina on 27.10.2020.
//

#ifndef assembler_h
#define assembler_h

#include <stdio.h>

//--------------------------------------------------------------------------------

struct Label {
    char * name;
    double addr;
};

//--------------------------------------------------------------------------------

void FreeAll(FILE * f1, FILE * f2, char * word, char * word2, char * new_filename,
             double * prog, struct Label * labels, unsigned long long labels_num);

int Assembly(const char * filename);

//--------------------------------------------------------------------------------

#endif

