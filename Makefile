.PHONY: all clean clean_bin clean_ojb build_run_vm run_vm build_run_asm run_asm version

MAKE = make
GXX = g++ -std=c++20

VOLGA = src/volga
OBJ_VOLGA = obj/volga

VOLGA_ASM = src/volga-asm
OBJ_VOLGA_ASM = obj/volga-asm

all: version clean volga volga_asm

version:
	@echo "MAKE:" && $(MAKE) --version
	@echo "GXX:" && $(GXX) --version

clean_bin:
	@rm -f bin/volga
	@rm -f bin/volga-asm
	@rm -f bin/*.so
	@echo "Binaries cleaned"
clean_obj:
	@rm -f $(OBJ_VOLGA)/*.o
	@rm -f $(OBJ_VOLGA_ASM)/*.o
	@echo "Object files cleaned"
clean: clean_bin clean_obj

obj/volga/main.o: src/volga/main.cpp
	@echo "Compiling src/volga/main.cpp"
	@$(GXX) -c -o $@ $<
obj/volga/vm.o: src/volga/vm/vm.cpp
	@echo "Compiling src/volga/vm/vm.cpp"
	@$(GXX) -c -o $@ $<
obj/volga/mem.o: src/volga/vm/mem.cpp
	@echo "Compiling src/volga/vm/mem.cpp"
	@$(GXX) -c -o $@ $<
volga: obj/volga/main.o obj/volga/vm.o obj/volga/mem.o
	@echo "Combining volga"
	@$(GXX) -o bin/volga $^
run_vm:
	@./bin/volga
build_run_vm: volga run_vm

obj/volga-asm/main.o: src/volga-asm/main.cpp
	@echo "Compiling src/volga-asm/main.cpp"
	@$(GXX) -c -o $@ $<
obj/volga-asm/d_asm.o: src/volga-asm/d_asm/d_asm.cpp
	@echo "Compiling src/volga-asm/d_asm/d_asm.cpp"
	@$(GXX) -c -o $@ $<
obj/volga-asm/asm.o: src/volga-asm/asm/asm.cpp
	@echo "Compiling src/volga-asm/asm/asm.cpp"
	@$(GXX) -c -o $@ $<
volga_asm: obj/volga-asm/main.o obj/volga-asm/d_asm.o obj/volga-asm/asm.o
	@echo "Combining volga-asm"
	@$(GXX) -o bin/volga-asm $^
run_asm:
	@./bin/volga
build_run_asm: volga run_vm
