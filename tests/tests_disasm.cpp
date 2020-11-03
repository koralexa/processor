//
//  tests_disasm.cpp
//  
//
//  Created by Alexandra Korabulina on 27.10.2020.
//

#include "tests_disasm.h"
#include <iostream>

//--------------------------------------------------------------------------------

#include "../disasm/disassembler.h"

//--------------------------------------------------------------------------------

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define WHITE "\033[0;37m"

//--------------------------------------------------------------------------------

void Test1_disasm() {
    if (Disassembly("test1_disasm") != 0) {
        std::cout << "Test1_disasm: " << RED << " ERROR" << WHITE << std::endl;
        return;
    }
    std::cout << "Test1_disasm: " << GREEN << "PASSED" << WHITE << std::endl;
}

//--------------------------------------------------------------------------------

void Test2_disasm() {
    if (Disassembly("test2_disasm") != 0) {
        std::cout << "Test2_disasm: " << RED << " ERROR" << WHITE << std::endl;
        return;
    }
    std::cout << "Test2_disasm: " << GREEN << "PASSED" << WHITE << std::endl;
}

//--------------------------------------------------------------------------------

void Test3_disasm() {
    if (Disassembly("test3_disasm") != 0) {
        std::cout << "Test3_disasm: " << RED << " ERROR" << WHITE << std::endl;
        return;
    }
    std::cout << "Test3_disasm: " << GREEN << "PASSED" << WHITE << std::endl;
}

//--------------------------------------------------------------------------------
