CXX = g++
CFLAGS = -Wall -Wextra
DEBUGFLAGS = -Wall -Wextra -g -DDEBUG


STACKFILES = stack/stack_errors.h stack/stack.h stack/stack.cpp

GETWORDFILES = asm/getword.h asm/getword.cpp

PROCFILES = proc/processor.cpp proc/processor.h
TESTPROCFILES = tests/tests_proc.h tests/tests_proc.cpp

ASMFILES = asm/assembler.cpp asm/assembler.h
TESTASMFILES = tests/tests_asm.h tests/tests_asm.cpp

DISASMFILES = disasm/disassembler.cpp disasm/disassembler.h
TESTDISASMFILES = tests/tests_disasm.h tests/tests_disasm.cpp


all: processor assembler disassembler

debug: processor_debug assembler_debug disassembler_debug

processor: $(PROCFILES) $(STACKFILES)
	$(CXX) $(CFLAGS) -o processor proc/processor.cpp

processor_debug: $(PROCFILES) $(STACKFILES) $(TESTPROCFILES)
	$(CXX) $(DEBUGFLAGS) -o processor_debug proc/processor.cpp tests/tests_proc.cpp

assembler: $(ASMFILES) $(GETWORDFILES)
	$(CXX) $(CFLAGS) -o assembler asm/assembler.cpp asm/getword.cpp

assembler_debug: $(ASMFILES) $(GETWORDFILES) $(TESTASMFILES)
	$(CXX) $(DEBUGFLAGS) -o assembler_debug asm/assembler.cpp tests/tests_asm.cpp asm/getword.cpp

disassembler: $(DISASMFILES)
	$(CXX) $(CFLAGS) -o disassembler disasm/disassembler.cpp

disassembler_debug: $(DISASMFILES) $(TESTDISASMFILES)
	$(CXX) $(DEBUGFLAGS) -o disassembler_debug disasm/disassembler.cpp tests/tests_disasm.cpp

clean: 
	rm processor
	rm assembler
	rm disassembler
	rm processor_debug
	rm assembler_debug
	rm disassembler_debug