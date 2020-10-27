//
//  disassembler.cpp
//  processor
//
//  Created by Alexandra Korabulina on 27.10.2020.
//

#include "disassembler.h"
#include "../getword/getword.h"

//--------------------------------------------------------------------------------

//! Converts file with maschine codes to file with program
//!
//! @param [in] filename name of the file with maschine codes
//!
//! @return 0 in case convertion finished successfully, 1 otherwise
int Disassembly(const char * filename) {
    char * new_filename = (char *)calloc(sizeof(char), strlen(filename) + 8);
    new_filename[0] = 'd';
    new_filename[1] = 'i';
    new_filename[2] = 's';
    new_filename[3] = 'a';
    new_filename[4] = 's';
    new_filename[5] = 'm';
    new_filename[6] = '_';
    new_filename[7] = '\0';
    strcat(new_filename, filename);
    FILE * f1 = fopen(filename, "r");
    FILE * f2 = fopen(new_filename, "w+");
    char * word = GetNextWord(f1);
    while (word != NULL) {
        if (strcmp(word, "0") == 0) {
            fwrite("hlt", sizeof(char), 3, f2);
            char * word2 = GetNextWord(f1);
            if (word2 != NULL) {
                free(word);
                free(word2);
                fclose(f1);
                fclose(f2);
                return 1;
            }
        } else if (strcmp(word, "1") == 0) {
            fwrite("in", sizeof(char), 2, f2);
        } else if (strcmp(word, "2") == 0) {
            fwrite("out", sizeof(char), 3, f2);
        } else if (strcmp(word, "3") == 0) {
            char * word2 = GetNextWord(f1);
            if (word2 == NULL) {
                free(word);
                fclose(f1);
                fclose(f2);
                return 1;
            }
            if (strcmp(word2, "0") == 0) {
                fwrite("push rax", sizeof(char), 8, f2);
            } else if (strcmp(word2, "1") == 0) {
                fwrite("push rbx", sizeof(char), 8, f2);
            } else if (strcmp(word2, "2") == 0) {
                fwrite("push rcx", sizeof(char), 8, f2);
            } else if (strcmp(word2, "3") == 0) {
                fwrite("push rdx", sizeof(char), 8, f2);
            } else {
                free(word);
                free(word2);
                fclose(f1);
                fclose(f2);
                return 1;
            }
        } else if (strcmp(word, "4") == 0) {
            fwrite("push ", sizeof(char), 5, f2);
            char * word2 = GetNextWord(f1);
            if (word2 == NULL) {
                free(word);
                fclose(f1);
                fclose(f2);
                return 1;
            }
            if ((strcmp(word2, "0") == 0) || (strcmp(word2, "0.0") == 0)) {
                fwrite("0", sizeof(char), 1, f2);
            } else {
                double var = atof(word2);
                if (var != 0) {
                    fwrite(word2, sizeof(char), strlen(word2), f2);
                } else {
                    free(word);
                    free(word2);
                    fclose(f1);
                    fclose(f2);
                    return 1;
                }
            }
        } else if (strcmp(word, "5") == 0) {
            char * word2 = GetNextWord(f1);
            if (word2 == NULL) {
                free(word);
                fclose(f1);
                fclose(f2);
                return 1;
            }
            if (strcmp(word2, "0") == 0) {
                fwrite("pop rax", sizeof(char), 7, f2);
            } else if (strcmp(word2, "1") == 0) {
                fwrite("pop rbx", sizeof(char), 7, f2);
            } else if (strcmp(word2, "2") == 0) {
                fwrite("pop rcx", sizeof(char), 7, f2);
            } else if (strcmp(word2, "3") == 0) {
                fwrite("pop rdx", sizeof(char), 7, f2);
            } else {
                free(word);
                free(word2);
                fclose(f1);
                fclose(f2);
                return 1;
            }
        } else if (strcmp(word, "6") == 0) {
            fwrite("sub", sizeof(char), 3, f2);
        } else if (strcmp(word, "7") == 0) {
            fwrite("add", sizeof(char), 3, f2);
        } else if (strcmp(word, "8") == 0) {
            fwrite("mul", sizeof(char), 3, f2);
        } else if (strcmp(word, "9") == 0) {
            fwrite("div", sizeof(char), 3, f2);
        } else if (strcmp(word, "10") == 0) {
            fwrite("sqrt", sizeof(char), 4, f2);
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