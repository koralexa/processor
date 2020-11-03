//
//  processor.cpp
//  processor
//
//  Created by Alexandra Korabulina on 27.10.2020.
//


#ifdef DEBUG
#include "../tests/tests_proc.h"
#endif

#include "processor.h"

#include <string.h>
#include <stdlib.h>
#include <math.h>

#define CHECK_TYPE 3
#include "../stack/stack_errors.h"

#undef TYPE
#define TYPE double
#include "../stack/stack.cpp"
#undef TYPE

#include <iostream>

//--------------------------------------------------------------------------------

//! Initializes the processor (creates stack, sets rip to 0, calls for ReadProgram() 
//! and starts to execute commands). Destructs the stack and program array after execution.
//!
//! @param [in] filename name of file with programm text
//! @param [in] p pointer to the processor
//!
//! @return 0 in case operation finished successfully, 1 otherwise
//!
//! @note otputs error message in case there is error in the program
int ExecuteProgram(const char * filename, Processor * p) {
    if ((filename == NULL) || (p == NULL)) {
        return 1;
    }
    StackInit(&(p->stack), 1024);
    if (ReadProgram(filename, p) != 0) {
        return 1;
    }
    p->rip = 0;
    int result = NextCommand(p);
    while (result > 0) {
        result = NextCommand(p);
    }
    free(p->program);
    StackDestructor(&(p->stack));
    if (result != 0) {
        printf("Error during executing program.\n");
    }
    return result;
}

//--------------------------------------------------------------------------------

//! Opens file with programm^ assemblyes it and fills program array with command codes
//!
//! @param [in] filename name of file with programm text
//! @param [in] p pointer to the processor
//!
//! @return 0 in case operation finished successfully, 1 otherwise
int ReadProgram(const char * filename, Processor * p) {
    FILE * f = fopen(filename, "rb");
    long long count = 0;
    p->program = (double *)calloc(sizeof(double), 100);
    long long prog_size = 100;
    double command = 0.0;
    while (fread(&command, sizeof(double), 1, f) != 0) {
        if (count == prog_size) {
            prog_size = prog_size * 2;
            p->program = (double *)realloc(p->program, prog_size);
        }
        p->program[count] = command;
        count++;
    }
    fclose(f);
    return 0;
}

//--------------------------------------------------------------------------------

//! Looks for the next command in program array and calls for needed function
//!
//! @param [in] p pointer to the processor
//!
//! @return 0 in case operation finished successfully, 1 otherwise
//!
//! @note increases rip for the next command
int NextCommand(Processor * p) {
    switch ((int)p->program[p->rip]) {
        case 0:
            return 0;
            break;
        case 1:
            p->rip++;
            if (In(p) != 0) {
                return -1;
            }
            break;
        case 2:
            p->rip++;
            if (Out(p) != 0) {
                return -1;
            }
            break;
        case 3:
            p->rip++;
            if (Push_reg(p) != 0) {
                return -1;
            }
            break;
        case 4:
            p->rip++;
            if (Push_num(p) != 0) {
                return -1;
            }
            break;
        case 5:
            p->rip++;
            if (Pop(p) != 0) {
                return -1;
            }
            break;
        case 6:
            p->rip++;
            if (Sub(p) != 0) {
                return -1;
            }
            break;
        case 7:
            p->rip++;
            if (Add(p) != 0) {
                return -1;
            }
            break;
        case 8:
            p->rip++;
            if (Mul(p) != 0) {
                return -1;
            }
            break;
        case 9:
            p->rip++;
            if (Div(p) != 0) {
                return -1;
            }
            break;
        case 10:
            p->rip++;
            if (Sqrt(p) != 0) {
                return -1;
            }
            break;
        case 11:
            p->rip++;
            if (Jmp(p) != 0) {
                return -1;
            }
            break;
        default:
            return -1;
    }
    return 1;
}

//--------------------------------------------------------------------------------

//! Chooses register of processor depending on it's number
//!
//! @param [in] p pointer to the processor
//! @param [in] command register number
//!
//! @return pointer to the register in case it exists, null pointer otherwise
double * CaseRegister(Processor * p, int command) {
    switch (command) {
        case 0:
            return (double *)&p->rax;
        case 1:
            return (double *)&p->rbx;
        case 2:
            return (double *)&p->rcx;
        case 3:
            return (double *)&p->rdx;
        default:
            return NULL;
    }
}

//--------------------------------------------------------------------------------

//! Takes value from input and pushes it in stack
//!
//! @param [in] p pointer to the processor
//!
//! @return 0 in case operation finished successfully, 1 otherwise
int In(Processor * p) {
    double num = 0;
    printf("in: ");
    scanf("%lf", &num);
    if (StackPush(&(p->stack), num) != 0) {
        return 1;
    } else {
        return 0;
    }
}

//--------------------------------------------------------------------------------

//! Pops number from stack and outputs it's value
//!
//! @param [in] p pointer to the processor
//!
//! @return 0 in case operation finished successfully, 1 otherwise
int Out(Processor * p) {
    double num = 0;
    if (StackPop(&(p->stack), &num) != 0) {
        return 1;
    } else {
        printf("%lf\n", num);
        return 0;
    }
}

//--------------------------------------------------------------------------------

//! Pushes register in stack (register number is in the programm array)
//!
//! @param [in] p pointer to the processor
//!
//! @return 0 in case operation finished successfully, 1 otherwise
//!
//! @note increases rip for the next command
int Push_reg(Processor * p) {
    double * reg = CaseRegister(p, (int)p->program[p->rip]);
    if (reg != NULL) {
        if (StackPush(&(p->stack), *reg) != 0) {
            return 1;
        } else {
            p->rip++;
            return 0;
        }
    } else {
        return 1;
    }
}

//--------------------------------------------------------------------------------

//! Pushes number in stack (number is in the programm array)
//!
//! @param [in] p pointer to the processor
//!
//! @return 0 in case operation finished successfully, 1 otherwise
//!
//! @note increases rip for the next command
int Push_num(Processor * p) {
    if (StackPush(&(p->stack), p->program[p->rip]) != 0) {
        return 1;
    } else {
        p->rip++;
        return 0;
    }
}

//--------------------------------------------------------------------------------

//! Pops number from stack and puts it into a register (register number is in the programm array)
//!
//! @param [in] p pointer to the processor
//!
//! @return 0 in case operation finished successfully, 1 otherwise
//!
//! @note increases rip for the next command
int Pop(Processor * p) {
    double * reg = CaseRegister(p, (int)p->program[p->rip]);
    if (reg != NULL) {
        if (StackPop(&(p->stack), reg) != 0) {
            return 1;
        } else {
            p->rip++;
            return 0;
        }
    } else {
        return 1;
    }
}

//--------------------------------------------------------------------------------

//! Pops two numbers from stack, subtracts first from second and pushes result to stack
//!
//! @param [in] p pointer to the processor
//!
//! @return 0 in case operation finished successfully, 1 otherwise
int Sub(Processor * p) {
    double num1 = 0;
    double num2 = 0;
    if (StackPop(&(p->stack), &num1) != 0) {
        return 1;
    }
    if (StackPop(&(p->stack), &num2) != 0) {
        return 1;
    }
    num2 = num2 - num1;
    if (StackPush(&(p->stack), num2) != 0) {
        return 1;
    }
    return 0;
}

//--------------------------------------------------------------------------------

//! Pops two numbers from stack, adds them and pushes result to stack
//!
//! @param [in] p pointer to the processor
//!
//! @return 0 in case operation finished successfully, 1 otherwise
int Add(Processor * p) {
    double num1 = 0;
    double num2 = 0;
    if (StackPop(&(p->stack), &num1) != 0) {
        return 1;
    }
    if (StackPop(&(p->stack), &num2) != 0) {
        return 1;
    }
    num2 = num2 + num1;
    if (StackPush(&(p->stack), num2) != 0) {
        return 1;
    }
    return 0;
}

//--------------------------------------------------------------------------------

//! Pops two numbers from stack, multiples them and pushes result to stack
//!
//! @param [in] p pointer to the processor
//!
//! @return 0 in case operation finished successfully, 1 otherwise
int Mul(Processor * p) {
    double num1 = 0;
    double num2 = 0;
    if (StackPop(&(p->stack), &num1) != 0) {
        return 1;
    }
    if (StackPop(&(p->stack), &num2) != 0) {
        return 1;
    }
    num2 = num2 * num1;
    if (StackPush(&(p->stack), num2) != 0) {
        return 1;
    }
    return 0;
}

//--------------------------------------------------------------------------------

//! Pops two numbers from stack, divides second by first and pushes result to stack
//!
//! @param [in] p pointer to the processor
//!
//! @return 0 in case operation finished successfully, 1 otherwise
int Div(Processor * p) {
    double num1 = 0;
    double num2 = 0;
    if (StackPop(&(p->stack), &num1) != 0) {
        return 1;
    }
    if (StackPop(&(p->stack), &num2) != 0) {
        return 1;
    }
    if (num1 == 0) {
        return 1;
    }
    num2 = num2 / num1;
    if (StackPush(&(p->stack), num2) != 0) {
        return 1;
    }
    return 0;
}

//--------------------------------------------------------------------------------

//! Pops number from stack, salculates square root of this number and pushes result to stack
//!
//! @param [in] p pointer to the processor
//!
//! @return 0 in case operation finished successfully, 1 otherwise
int Sqrt(Processor * p) {
    double num = 0;
    if (StackPop(&(p->stack), &num) != 0) {
        return 1;
    }
    if (num < 0) {
        return 1;
    }
    num = sqrt(num);
    if (StackPush(&(p->stack), num) != 0) {
        return 1;
    }
    return 0;
}

//--------------------------------------------------------------------------------

//! Jimps to the label
//!
//! @param [in] p pointer to the processor
//!
//! @return 0 in case operation finished successfully, 1 otherwise
int Jmp(Processor * p) {
    if (p->program[p->rip] < 0) {
        return 1;
    }
    p->rip = (long long)p->program[p->rip];
    return 0;
}

//--------------------------------------------------------------------------------

int main(int argc, const char * argv[]) {
#ifdef DEBUG
    (void)argc;
    (void)argv;
    Test1_proc();
    Test2_proc();
    Test3_proc();
    return 0;
#else
    if (argc != 2) {
        std::cout << "Wrong parameters, you must provide filename (and only filename) as command line argument." << std::endl;
        return 0;
    }
    Processor p;
    if (ExecuteProgram(argv[1], &p) == 0) {
        std::cout << "Successfull execution." << std::endl;
    }
    return 0;
#endif
}
