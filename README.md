# Processor
This project is created to provide the ability to execute calculations with the use of stack and some simple commands.

## Description

You must provide a .txt file with your program text.
The programm will be converted into maschine codes and then executed.
Commands available are:
in (get float number from stdin)
out (output float number from the top of stack)
hlt (stop executing)
add (add two numbers from the top of stack)
sub (subtract one value from another)
mul (multiply two numbers)
div (divide one number by another)
sqrt (take square root from the top value)
push (push number or register to the stack)
pop (pop number from stack to some register)

There are four double registers in processor provided: rax, rbx, rcx and rdx.
You can see an example of program which calculates discriminat of quadratic equation in example.txt file.
Ability to disassembly program is also provided (disassmbler.cpp and disassembler.h).
There is a simple example of using processor in main.cpp.

## Getting Started

### Installing

* Download the project from GitHub or clone it by
```
 git clone https://github.com/koralexa/processor.git
```

### Executing program

* Go to the project folder through your terminal.
* To execute example run
```
make
```
* Then run
```
./main
```

* To execute example  in debug mode run
```
make debug
```
* Then run
```
./main
```

* To delete executable files run
```
make clean
```

