# Processor
This project is created to provide the ability to execute calculations with the use of stack and some simple commands.

## Description

Commands available are:

Code | Command | Result
------ | ------------ | --------
0 | hlt | stop execution
1 | in | get float number from stdin
2 | out | output float number from the top of stack
3, 4 | push | push number or register to the stack
5 | pop | pop number from stack to some register
6 | sub | subtract one number from another
7 | add | add two numbers from the top of stack
8 | mul | multiply two numbers
9 | div | divide one number by another
10 | sqrt | take square root from the top value
11 | jmp | jump to a label

There are four double registers in processor provided: rax, rbx, rcx and rdx.

You can write a program in .txt file, then assembly it with ./assembler and execute it with ./processor.
Ability to disassembly the program back is also provided (use ./disassembler).
You can see examples of programs in Test files.

## Getting Started

### Installing

* Download the project from GitHub or clone it by
```
 git clone https://github.com/koralexa/processor.git
```

### Executing program

* Go to the project folder through your terminal.
* To compile release versions of all programms run
```
make
```
* You can also compile all programms separate with
```
make processor
make assembler
make disassembler
```
* To assembly your .txt programm run
```
./assembler <your_prog.txt>
```
* To disassembly a program run
```
./disassembler <your_prog>
```
* To execute assembled program run
```
./processor <your_prog>
```

* To get debug versions of all programs run
```
make debug
```
* You can also compile all programms in debug version separate with
```
make processor_debug
make assembler_debug
make disassembler_debug
```
* To run tests for processor run
```
./processor_debug
```
* To run tests for assembler run
```
./assembler_debug
```
* To run tests for disassembler run
```
./disassembler_debug
```

