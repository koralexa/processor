//
//  tests.cpp
//  
//
//  Created by Alexandra Korabulina on 12.10.2020.
//

#include "tests.h"
#include <iostream>

//--------------------------------------------------------------------------------

#include "../processor/processor.h"
#include "../assembler/assembler.h"
#include "../disassembler/disassembler.h"

//--------------------------------------------------------------------------------

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define WHITE "\033[0;37m"

//--------------------------------------------------------------------------------

void Test1() {
    Processor p;
    if (ExecuteProgram("test1.txt", &p) != 0) {
        std::cout << "Test1: " << RED << " ERROR" << WHITE << std::endl;
        return;
    }
    std::cout << "Test1: " << GREEN << "PASSED" << WHITE << std::endl;
}

//--------------------------------------------------------------------------------

void Test2() {
    Processor p;
    if (ExecuteProgram("test2.txt", &p) == 0) {
        std::cout << "Test2: " << RED << " ERROR" << WHITE << std::endl;
        return;
    }
    std::cout << "Test2: " << GREEN << "PASSED" << WHITE << std::endl;
}

//--------------------------------------------------------------------------------

void Test3() {
    if (Assembly("test3.txt") != 0) {
        std::cout << "Test3: " << RED << " ERROR" << WHITE << std::endl;
        return;
    }
    std::cout << "Test3: " << GREEN << "PASSED" << WHITE << std::endl;
}

//--------------------------------------------------------------------------------

void Test4() {
    if (Assembly("test4.txt") == 0) {
        std::cout << "Test4: " << RED << " ERROR" << WHITE << std::endl;
        return;
    }
    std::cout << "Test4: " << GREEN << "PASSED" << WHITE << std::endl;
}

//--------------------------------------------------------------------------------

void Test5() {
    if (Disassembly("test5.txt") != 0) {
        std::cout << "Test5: " << RED << " ERROR" << WHITE << std::endl;
        return;
    }
    std::cout << "Test5: " << GREEN << "PASSED" << WHITE << std::endl;
}

//--------------------------------------------------------------------------------

void Test6() {
    if (Disassembly("test6.txt") == 0) {
        std::cout << "Test6: " << RED << " ERROR" << WHITE << std::endl;
        return;
    }
    std::cout << "Test6: " << GREEN << "PASSED" << WHITE << std::endl;
}

//--------------------------------------------------------------------------------