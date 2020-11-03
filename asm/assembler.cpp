//
//  assembler.cpp
//  processor
//
//  Created by Alexandra Korabulina on 27.10.2020.
//

#ifdef DEBUG
#include "../tests/tests_asm.h"
#endif

#include "assembler.h"
#include "getword.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>

//--------------------------------------------------------------------------------

//! Closes all files and frees all buffers used in Assembly() function
//!
//! @param [in] f1 input file
//! @param [in] f2 ouput file
//! @param [in] word first word buffer
//! @param [in] word2 second word biffer
//! @param [in] new_filename name of output file
//! @param [in] prog assembled program storage
//! @param [in] labels  array of labels of the programm
//! @param [in] labels_num number of labels of the programm
void FreeAll(FILE * f1, FILE * f2, char * word, char * word2, char * new_filename, double * prog,
             struct Label * labels, unsigned long long labels_num) {
    if (word != NULL) {
        free(word);
    }
    if (word2 != NULL) {
        free(word2);
    }
    free(new_filename);
    if (prog != NULL) {
        free(prog);
    }
    fclose(f1);
    fclose(f2);
    unsigned long long i = 0;
    if (labels != NULL) {
        for (i = 0; i < labels_num; i++) {
            free(labels[i].name);
        }
        free(labels);
    }
}

//--------------------------------------------------------------------------------

//! Converts file with program to file with maschine codes
//!
//! @param [in] filename name of the file with program
//!
//! @return 0 in case convertion finished successfully, 1 otherwise
int Assembly(const char * filename) {
    char * new_filename = (char *)calloc(sizeof(char), strlen(filename) + 5);
    new_filename[0] = 'a';
    new_filename[1] = 's';
    new_filename[2] = 'm';
    new_filename[3] = '_';
    new_filename[4] = '\0';
    strcat(new_filename, filename);
    new_filename[strlen(new_filename) - 4] = '\0';
    FILE * f1 = fopen(filename, "r");
    FILE * f2 = fopen(new_filename, "w+b");
    
    unsigned long long line = 0;
    unsigned long long command_num = 0;
    double * prog = (double *)calloc(sizeof(double), 100);
    unsigned long long prog_size = 100;
    char * word = (char *)calloc(sizeof(char), 100);
    
    unsigned long long labels_num = 0;
    unsigned long long labels_capacity = 100;
    struct Label * labels = (struct Label *)calloc(sizeof(struct Label), 100);
    while (GetNextWord(f1, word) != 0) {
        if (labels_num >= labels_capacity - 1) {
            labels_capacity = labels_capacity * 2;
            labels = (struct Label *)realloc(labels, labels_capacity);
        }
        if (word[strlen(word) - 1] == ':') {
            labels[labels_num].name = (char *)calloc(sizeof(char), strlen(word) + 1);
            strcpy(labels[labels_num].name, word);
            labels[labels_num].name[strlen(word) - 1] = '\0';
            labels[labels_num].addr = (double)(command_num);
            labels_num++;
        } else {
            command_num++;
        }
    }
    fclose(f1);
    
    command_num = 0;
    f1 = fopen(filename, "r");
    while (GetNextWord(f1, word) != 0) {
        if (command_num >= prog_size - 1) {
            prog_size = prog_size * 2;
            prog = (double *)realloc(prog, prog_size);
        }
        line++;
        if (strcmp(word, "hlt") == 0) {
            prog[command_num] = 0.0;
            command_num++;
            char * word2 = (char *)calloc(sizeof(char), 100);
            if (GetNextWord(f1, word2) != 0) {
                FreeAll(f1, f2, word, word2, new_filename, prog, labels, labels_num);
                std::cout << "Line " << line << ": Error: command was founded after hlt." << std::endl;
                return 1;
            }
            free(word2);
        } else if (strcmp(word, "in") == 0) {
            prog[command_num] = 1.0;
            command_num++;
        } else if (strcmp(word, "out") == 0) {
            prog[command_num] = 2.0;
            command_num++;
        } else if (strcmp(word, "push") == 0) {
            char * word2 = (char *)calloc(sizeof(char), 100);
            if (GetNextWord(f1, word2) == 0) {
                FreeAll(f1, f2, word, word2, new_filename, prog, labels, labels_num);
                std::cout << "Line " << line << ": Error: push must have an operand." << std::endl;
                return 1;
            }
            if (strcmp(word2, "rax") == 0) {
                prog[command_num] = 3.0;
                command_num++;
                prog[command_num] = 0.0;
                command_num++;
            } else if (strcmp(word2, "rbx") == 0) {
                prog[command_num] = 3.0;
                command_num++;
                prog[command_num] = 1.0;
                command_num++;
            } else if (strcmp(word2, "rcx") == 0) {
                prog[command_num] = 3.0;
                command_num++;
                prog[command_num] = 2.0;
                command_num++;
            } else if (strcmp(word2, "rdx") == 0) {
                prog[command_num] = 3.0;
                command_num++;
                prog[command_num] = 3.0;
                command_num++;
            } else {
                if ((strcmp(word2, "0") == 0) || (strcmp(word2, "0.0") == 0)) {
                    prog[command_num] = 4.0;
                    command_num++;
                    prog[command_num] = 0.0;
                    command_num++;
                } else {
                    double var = atof(word2);
                    if (var != 0) {
                        prog[command_num] = 4.0;
                        command_num++;
                        prog[command_num] = var;
                        command_num++;
                    } else {
                        FreeAll(f1, f2, word, word2, new_filename, prog, labels, labels_num);
                        std::cout << "Line " << line << ": Error: wrong operand for push." << std::endl;
                        return 1;
                    }
                }
            }
            free(word2);
        } else if (strcmp(word, "pop") == 0) {
            char * word2 = (char *)calloc(sizeof(char), 100);;
            if (GetNextWord(f1, word2) == 0) {
                FreeAll(f1, f2, word, word2, new_filename, prog, labels, labels_num);
                std::cout << "Line " << line << ": Error: pop must have an operand." << std::endl;
                return 1;
            }
            if (strcmp(word2, "rax") == 0) {
                prog[command_num] = 5.0;
                command_num++;
                prog[command_num] = 0.0;
                command_num++;
            } else if (strcmp(word2, "rbx") == 0) {
                prog[command_num] = 5.0;
                command_num++;
                prog[command_num] = 1.0;
                command_num++;
            } else if (strcmp(word2, "rcx") == 0) {
                prog[command_num] = 5.0;
                command_num++;
                prog[command_num] = 2.0;
                command_num++;
            } else if (strcmp(word2, "rdx") == 0) {
                prog[command_num] = 5.0;
                command_num++;
                prog[command_num] = 3.0;
                command_num++;
            } else {
                FreeAll(f1, f2, word, word2, new_filename, prog, labels, labels_num);
                std::cout << "Line " << line << ": Error: wrong operand for pop." << std::endl;
                return 1;
            }
            free(word2);
        } else if (strcmp(word, "sub") == 0) {
            prog[command_num] = 6.0;
            command_num++;
        } else if (strcmp(word, "add") == 0) {
            prog[command_num] = 7.0;
            command_num++;
        } else if (strcmp(word, "mul") == 0) {
            prog[command_num] = 8.0;
            command_num++;
        } else if (strcmp(word, "div") == 0) {
            prog[command_num] = 9.0;
            command_num++;
        } else if (strcmp(word, "sqrt") == 0) {
            prog[command_num] = 10.0;
            command_num++;
        } else if (strcmp(word, "jmp") == 0) {
            prog[command_num] = 11.0;
            command_num++;
            unsigned long long i = 0;
            char * word2 = (char *)calloc(sizeof(char), 100);;
            if (GetNextWord(f1, word2) == 0) {
                FreeAll(f1, f2, word, word2, new_filename, prog, labels, labels_num);
                std::cout << "Line " << line << ": Error: jmp must have an operand." << std::endl;
                return 1;
            }
            double address = -1.0;
            for (i = 0; i < labels_num; i++) {
                if (strcmp(word2, labels[i].name) == 0) {
                    address = labels[i].addr;
                    break;
                }
            }
            if (address == -1.0) {
                FreeAll(f1, f2, word, word2, new_filename, prog, labels, labels_num);
                std::cout << "Line " << line << ": Error: no such label in the program." << std::endl;
                return 1;
            } else {
                prog[command_num] = address;
                command_num++;
            }
        } else if (word[strlen(word) - 1] == ':') {
        } else {
            free(word);
            free(prog);
            fclose(f1);
            fclose(f2);
            if (labels != NULL) {
                unsigned long long i = 0;
                for (i = 0; i < labels_num; i++) {
                    free(labels[i].name);
                }
                free(labels);
            }
            std::cout << "Line " << line << ": Error: unrecognised command was found." << std::endl;
            return 1;
        }
    }
    fwrite(prog, sizeof(double), command_num, f2);
    free(word);
    free(prog);
    fclose(f1);
    fclose(f2);
    free(new_filename);
    if (labels != NULL) {
        unsigned long long i = 0;
        for (i = 0; i < labels_num; i++) {
            free(labels[i].name);
        }
        free(labels);
    }
    return 0;
}

//--------------------------------------------------------------------------------

int main(int argc, const char * argv[]) {
#ifdef DEBUG
    (void)argc;
    (void)argv;
    Test1_asm();
    Test2_asm();
    Test3_asm();
    return 0;
#else
    if (argc != 2) {
        std::cout << "Wrong parameters, you must provide filename (and only filename) as command line argument." << std::endl;
        return 0;
    }
    if (Assembly(argv[1]) == 0) {
        std::cout << "File was successfully assembled." << std::endl;
    }
    return 0;
#endif
}
