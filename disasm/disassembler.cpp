//
//  disassembler.cpp
//  processor
//
//  Created by Alexandra Korabulina on 27.10.2020.
//

#include "disassembler.h"

#ifdef DEBUG
#include "../tests/tests_disasm.h"
#endif

#include <iostream>
#include <string.h>
#include <stdlib.h>

//--------------------------------------------------------------------------------

//! Closes all files used in Disassembly() function
//!
//! @param [in] f1 input file
//! @param [in] f2 ouput file
//! @param [in] labels  array of labels of the programm
//! @param [in] labels_num number of labels of the programm
void FreeAll(FILE * f1, FILE * f2, struct Label * labels, unsigned long labels_num) {
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
    strcat(new_filename, ".txt");
    FILE * f1 = fopen(filename, "rb");
    FILE * f2 = fopen(new_filename, "w+");
    
    double command = 0.0;
    double command2 = 0.0;
    unsigned long labels_num = 0;
    unsigned long labels_capacity = 100;
    struct Label * labels = (struct Label *)calloc(sizeof(struct Label), 100);
    char * buf = (char *)calloc(sizeof(char), (int)(labels_num + 1) / 10 + 1);
    strcpy(buf, "label_");
    while (fread(&command, sizeof(double), 1, f1) != 0) {
        if (labels_num >= labels_capacity - 1) {
            labels_capacity = labels_capacity * 2;
            labels = (struct Label *)realloc(labels, labels_capacity);
        }
        if (command == 11.0) {
            if (fread(&command2, sizeof(double), 1, f1) == 0) {
                free(buf);
                FreeAll(f1, f2, labels, labels_num);
                std::cout << "Error: jmp must have an operand." << std::endl;
                return 1;
            }
            strcat(buf, "1");
            labels[labels_num].name = (char *)calloc(sizeof(char), strlen(buf));
            strcpy(labels[labels_num].name, buf);
            labels[labels_num].addr = command2;
            labels_num++;
        }
    }
    free(buf);
    fclose(f1);
    
    f1 = fopen(filename, "rb");
    unsigned long long line = 0;
    unsigned long i = 0;
    unsigned long long command_num = 0;
    while (fread(&command, sizeof(double), 1, f1) != 0) {
        for (i = 0; i < labels_num; i++) {
            if ((double)command_num == labels[i].addr) {
                long j = 0;
                long len = strlen(labels[i].name);
                for (j = 0; j < len; j++) {
                    fprintf(f2, "%c", labels[i].name[j]);
                }
                fprintf(f2, ":\n");
            }
        }
        line++;
        command_num++;
        if (command == 0.0) {
            fwrite("hlt", sizeof(char), 3, f2);
            if (fread(&command2, sizeof(double), 1, f1) != 0) {
                FreeAll(f1, f2, labels, labels_num);
                std::cout << "Line " << line << ": Error: command was founded after hlt." << std::endl;
                return 1;
            }
        } else if (command == 1.0) {
            fwrite("in", sizeof(char), 2, f2);
        } else if (command == 2.0) {
            fwrite("out", sizeof(char), 3, f2);
        } else if (command == 3.0) {
            if (fread(&command2, sizeof(double), 1, f1) == 0) {
                FreeAll(f1, f2, labels, labels_num);
                std::cout << "Line " << line << ": Error: push must have an operand." << std::endl;
                return 1;
            }
            if (command2 == 0.0) {
                fwrite("push rax", sizeof(char), 8, f2);
                command_num++;
            } else if (command2 == 1.0) {
                fwrite("push rbx", sizeof(char), 8, f2);
                command_num++;
            } else if (command2 == 2.0) {
                fwrite("push rcx", sizeof(char), 8, f2);
                command_num++;
            } else if (command2 == 3.0) {
                fwrite("push rdx", sizeof(char), 8, f2);
                command_num++;
            } else {
                FreeAll(f1, f2, labels, labels_num);
                std::cout << "Line " << line << ": Error: wrong operand for push." << std::endl;
                return 1;
            }
        } else if (command == 4.0) {
            fwrite("push ", sizeof(char), 5, f2);
            if (fread(&command2, sizeof(double), 1, f1) == 0) {
                FreeAll(f1, f2, labels, labels_num);
                std::cout << "Line " << line << ": Error: push must have an operand." << std::endl;
                return 1;
            }
            fprintf(f2, "%lf", command2);
            command_num++;
        } else if (command == 5.0) {
            if (fread(&command2, sizeof(double), 1, f1) == 0) {
                FreeAll(f1, f2, labels, labels_num);
                std::cout << "Line " << line << ": Error: pop must have an operand." << std::endl;
                return 1;
            }
            if (command2 == 0.0) {
                command_num++;
                fwrite("pop rax", sizeof(char), 7, f2);
            } else if (command2 == 1.0) {
                command_num++;
                fwrite("pop rbx", sizeof(char), 7, f2);
            } else if (command2 == 2.0) {
                command_num++;
                fwrite("pop rcx", sizeof(char), 7, f2);
            } else if (command2 == 3.0) {
                command_num++;
                fwrite("pop rdx", sizeof(char), 7, f2);
            } else {
                FreeAll(f1, f2, labels, labels_num);
                return 1;
            }
        } else if (command == 6.0) {
            fwrite("sub", sizeof(char), 3, f2);
        } else if (command == 7.0) {
            fwrite("add", sizeof(char), 3, f2);
        } else if (command == 8.0) {
            fwrite("mul", sizeof(char), 3, f2);
        } else if (command == 9.0) {
            fwrite("div", sizeof(char), 3, f2);
        } else if (command == 10.0) {
            fwrite("sqrt", sizeof(char), 4, f2);
        } else if (command == 11.0) {
            command_num++;
            fwrite("jmp ", sizeof(char), 4, f2);
            fread(&command2, sizeof(double), 1, f1);
            for (i = 0; i < labels_num; i++) {
                if (command2 == labels[i].addr) {
                    long j = 0;
                    long len = strlen(labels[i].name);
                    for (j = 0; j < len; j++) {
                        fprintf(f2, "%c", labels[i].name[j]);
                    }
                }
            }
        } else {
            FreeAll(f1, f2, labels, labels_num);
            std::cout << "Line " << line << ": Error: unrecognised command was found." << std::endl;
            return 1;
        }
        fwrite("\n", sizeof(char), 1, f2);
    }
    free(new_filename);
    FreeAll(f1, f2, labels, labels_num);
    return 0;
}

//--------------------------------------------------------------------------------

int main(int argc, const char * argv[]) {
#ifdef DEBUG
    (void)argc;
    (void)argv;
    Test1_disasm();
    Test2_disasm();
    Test3_disasm();
    return 0;
#else
    if (argc != 2) {
        std::cout << "Wrong parameters, you must provide filename (and only filename) as command line argument." << std::endl;
        return 0;
    }
    if (Disassembly(argv[1]) == 0) {
        std::cout << "File was successfully disassembled." << std::endl;
    }
    return 0;
#endif
}
