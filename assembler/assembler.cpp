//
//  assembler.cpp
//  processor
//
//  Created by Alexandra Korabulina on 27.10.2020.
//

#include "assembler.h"
#include "../getword/getword.h"

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
    FILE * f1 = fopen(filename, "r");
    FILE * f2 = fopen(new_filename, "w+");
    char * word = GetNextWord(f1);
    while (word != NULL) {
        if (strcmp(word, "hlt") == 0) {
            fwrite("0", sizeof(char), 1, f2);
            char * word2 = GetNextWord(f1);
            if (word2 != NULL) {
                free(word);
                free(word2);
                fclose(f1);
                fclose(f2);
                return 1;
            }
        } else if (strcmp(word, "in") == 0) {
            fwrite("1", sizeof(char), 1, f2);
        } else if (strcmp(word, "out") == 0) {
            fwrite("2", sizeof(char), 1, f2);
        } else if (strcmp(word, "push") == 0) {
            char * word2 = GetNextWord(f1);
            if (word2 == NULL) {
                free(word);
                fclose(f1);
                fclose(f2);
                return 1;
            }
            if (strcmp(word2, "rax") == 0) {
                fwrite("3 0", sizeof(char), 3, f2);
            } else if (strcmp(word2, "rbx") == 0) {
                fwrite("3 1", sizeof(char), 3, f2);
            } else if (strcmp(word2, "rcx") == 0) {
                fwrite("3 2", sizeof(char), 3, f2);
            } else if (strcmp(word2, "rdx") == 0) {
                fwrite("3 3", sizeof(char), 3, f2);
            } else {
                if ((strcmp(word2, "0") == 0) || (strcmp(word2, "0.0") == 0)) {
                    fwrite("4 0", sizeof(char), 3, f2);
                } else {
                    double var = atof(word2);
                    if (var != 0) {
                        fwrite("4 ", sizeof(char), 2, f2);
                        fwrite(word2, sizeof(char), strlen(word2), f2);
                    } else {
                        free(word);
                        free(word2);
                        fclose(f1);
                        fclose(f2);
                        return 1;
                    }
                }
            }
        } else if (strcmp(word, "pop") == 0) {
            char * word2 = GetNextWord(f1);
            if (word2 == NULL) {
                free(word);
                fclose(f1);
                fclose(f2);
                return 1;
            }
            if (strcmp(word2, "rax") == 0) {
                fwrite("5 0", sizeof(char), 3, f2);
            } else if (strcmp(word2, "rbx") == 0) {
                fwrite("5 1", sizeof(char), 3, f2);
            } else if (strcmp(word2, "rcx") == 0) {
                fwrite("5 2", sizeof(char), 3, f2);
            } else if (strcmp(word2, "rdx") == 0) {
                fwrite("5 3", sizeof(char), 3, f2);
            } else {
                free(word);
                free(word2);
                fclose(f1);
                fclose(f2);
                return 1;
            }
        } else if (strcmp(word, "sub") == 0) {
            fwrite("6", sizeof(char), 1, f2);
        } else if (strcmp(word, "add") == 0) {
            fwrite("7", sizeof(char), 1, f2);
        } else if (strcmp(word, "mul") == 0) {
            fwrite("8", sizeof(char), 1, f2);
        } else if (strcmp(word, "div") == 0) {
            fwrite("9", sizeof(char), 1, f2);
        } else if (strcmp(word, "sqrt") == 0) {
            fwrite("10", sizeof(char), 2, f2);
        } else {
            free(word);
            fclose(f1);
            fclose(f2);
            return 1;
        }
        fwrite("\n", sizeof(char), 1, f2);
        free(word);
        word = GetNextWord(f1);
    }
    fclose(f1);
    fclose(f2);
    return 0;
}

//--------------------------------------------------------------------------------