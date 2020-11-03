//
//  disassembler.h
//  processor
//
//  Created by Alexandra Korabulina on 27.10.2020.
//

#ifndef disassembler_h
#define disassembler_h

#include <stdio.h>

//--------------------------------------------------------------------------------

struct Label {
    char * name;
    double addr;
};

//--------------------------------------------------------------------------------

void FreeAll(FILE * f1, FILE * f2, struct Label * labels, unsigned long labels_num);

int Disassembly(const char * filename);

//--------------------------------------------------------------------------------

#endif

