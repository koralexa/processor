//
//  processor.h
//  processor
//
//  Created by Alexandra Korabulina on 27.10.2020.
//

#ifndef processor_h
#define processor_h

//--------------------------------------------------------------------------------

#include <stdio.h>

#undef TYPE
#define TYPE double
#include "../stack/stack.h"
#undef TYPE

//--------------------------------------------------------------------------------

typedef struct Processor_t {
    Stack_double stack;
    double rax;
    double rbx;
    double rcx;
    double rdx;
    double * program;
    long long rip;
} Processor;

//--------------------------------------------------------------------------------

int ExecuteProgram(const char * filename, Processor * p);

int ReadProgram(const char * filename, Processor * p);

int NextCommand(Processor * p);

double * CaseRegister(Processor * p, int command);

int In(Processor * p);       // 1

int Out(Processor * p);      // 2

int Push_reg(Processor * p); // 3

int Push_num(Processor * p); // 4

int Pop(Processor * p);      // 5

int Sub(Processor * p);      // 6

int Add(Processor * p);      // 7

int Mul(Processor * p);      // 8

int Div(Processor * p);      // 9

int Sqrt(Processor * p);     // 10

int Jmp(Processor * p);      // 11

//--------------------------------------------------------------------------------

#endif

