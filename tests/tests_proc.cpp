//
//  tests_proc.cpp
//  processor
//
//  Created by Alexandra Korabulina on 27.10.2020.
//

#include "tests_proc.h"
#include <iostream>

//--------------------------------------------------------------------------------

#include "../proc/processor.h"

//--------------------------------------------------------------------------------

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define WHITE "\033[0;37m"

//--------------------------------------------------------------------------------

void Test1_proc() {
    Processor p;
    if (ExecuteProgram("test1_proc", &p) != 0) {
        std::cout << "Test1_proc: " << RED << " ERROR" << WHITE << std::endl;
        return;
    }
    std::cout << "Test1_proc: " << GREEN << "PASSED" << WHITE << std::endl;
}

//--------------------------------------------------------------------------------

void Test2_proc() {
    Processor p;
    if (ExecuteProgram("test2_proc", &p) == 0) {
        std::cout << "Test2_proc: " << RED << " ERROR" << WHITE << std::endl;
        return;
    }
    std::cout << "Test2_proc: " << GREEN << "PASSED" << WHITE << std::endl;
}

//--------------------------------------------------------------------------------

void Test3_proc() {
    Processor p;
    if (ExecuteProgram("test3_proc", &p) != 0) {
        std::cout << "Test3_proc: " << RED << " ERROR" << WHITE << std::endl;
        return;
    }
    std::cout << "Test3_proc: " << GREEN << "PASSED" << WHITE << std::endl;
}

//--------------------------------------------------------------------------------
