//
//  tests_asm.cpp
//  
//
//  Created by Alexandra Korabulina on 12.10.2020.
//

#include "tests_asm.h"
#include <iostream>

//--------------------------------------------------------------------------------

#include "../asm/assembler.h"

//--------------------------------------------------------------------------------

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define WHITE "\033[0;37m"

//--------------------------------------------------------------------------------

void Test1_asm() {
    if (Assembly("test1_asm.txt") != 0) {
        std::cout << "Test1_asm: " << RED << " ERROR" << WHITE << std::endl;
        return;
    }
    std::cout << "Test1_asm: " << GREEN << "PASSED" << WHITE << std::endl;
}

//--------------------------------------------------------------------------------

void Test2_asm() {
    if (Assembly("test2_asm.txt") != 0) {
        std::cout << "Test2_asm: " << RED << " ERROR" << WHITE << std::endl;
        return;
    }
    std::cout << "Test2_asm: " << GREEN << "PASSED" << WHITE << std::endl;
}

//--------------------------------------------------------------------------------

void Test3_asm() {
    if (Assembly("test3_asm.txt") == 0) {
        std::cout << "Test3_asm: " << RED << " ERROR" << WHITE << std::endl;
        return;
    }
    std::cout << "Test3_asm: " << GREEN << "PASSED" << WHITE << std::endl;
}

//--------------------------------------------------------------------------------
