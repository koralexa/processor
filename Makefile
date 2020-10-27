CXX = g++
CFLAGS = -Wall -Wextra
DEBUGFLAGS = -Wall -Wextra -g -DDEBUG

FILES = main.cpp processor/processor.cpp assembler/assembler.cpp disassembler/disassembler.cpp getword/getword.cpp
DEBUGFILES = tests/tests.cpp
HEADERS = stack/stack_errors.h stack/stack.h processor/processor.h assembler/assembler.h disassembler/disassembler.h getword/getword.h
TESTS = tests/tests.h tests/tests.cpp

all: $(FILES) $(HEADERS)
	$(CXX) $(CFLAGS) -o main $(FILES)

debug: $(FILES) $(HEADERS) $(TESTS)
	$(CXX) $(DEBUGFLAGS) -o main $(FILES) $(DEBUGFILES)

clean: 
	rm main