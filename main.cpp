#include <iostream>

#ifdef DEBUG
#include "tests/tests.h"
#else
#include "processor/processor.h"
#endif

int main() {

#ifdef DEBUG
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    return 0;
#else

    Processor p;
    if (ExecuteProgram("example.txt", &p) != 0) {
        std::cout << "Error." << std::endl;
    } else {
        std::cout << "Successful execution." << std::endl;
    }
    return 0;
#endif
}
