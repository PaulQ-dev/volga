.PHONY: all clean clean_bin run_vm run_only_vm run_asm run_only_asm version

MAKE = make
GXX = g++

VOLGA = src/volga
VOLGA_ASM = src/volga-asm

VOLGA_FILES = $(VOLGA)/main.cpp $(VOLGA)/vm/*.cpp
VOLGA_ASM_FILES = $(VOLGA_ASM)/main.cpp $(VOLGA_ASM)/asm/*.cpp $(VOLGA_ASM)/d_asm/*.cpp

all: version clean volga volga-asm

version:
	@echo "MAKE:" && $(MAKE) --version
	@echo "GXX:" && $(GXX) --version

clean_bin:
	@rm -f bin/volga
	@rm -f bin/volga-asm
	@rm -f bin/*.so
	@echo "Binaries cleaned"
clean: clean_bin

volga:
	@echo "Compiling volga"
	@$(GXX) -o bin/$@ $(VOLGA_FILES) -I $(VOLGA) && echo "Done! Written to ./bin/volga"

volga_asm: 
	@ehco "Not Implemented"

run_only_vm:
	@./bin/volga
run_vm: volga run_only_vm

run_only_asm:
	@./bin/volga-asm
run_asm: volga-asm run_only_asm
