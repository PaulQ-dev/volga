.PHONY: all clean clean_bin clean_obj version

MAKE = make
GXX = g++ -std=c++20

VOLGA = src/volga
OBJ_VOLGA = obj/volga

all: version clean volga

version:
	@echo "MAKE:" && $(MAKE) --version
	@echo "GXX:" && $(GXX) --version

clean_bin:
	@rm -f bin/volga
	@rm -f bin/*.so
	@echo "Binaries cleaned"
clean_obj:
	@rm -f $(OBJ_VOLGA)/*.o
	@echo "Object files cleaned"
clean: clean_bin clean_obj

obj/volga/main.o: src/volga/main.cpp
	@echo "Compiling src/volga/main.cpp"
	@$(GXX) -c -o $@ $< -Isrc/volga
obj/volga/d_asm.o: src/volga/d_asm/d_asm.cpp
	@echo "Compiling src/volga/d_asm/d_asm.cpp"
	@$(GXX) -c -o $@ $< -Isrc/volga
obj/volga/asm.o: src/volga/asm/asm.cpp
	@echo "Compiling src/volga/asm/asm.cpp"
	@$(GXX) -c -o $@ $< -Isrc/volga
obj/volga/vm.o: src/volga/vm/vm.cpp
	@echo "Compiling src/volga/vm/vm.cpp"
	@$(GXX) -c -o $@ $< -Isrc/volga
obj/volga/vm_mem.o: src/volga/vm/vm_mem.cpp
	@echo "Compiling src/volga/vm/vm_mem.cpp"
	@$(GXX) -c -o $@ $< -Isrc/volga
volga: obj/volga/main.o obj/volga/d_asm.o obj/volga/asm.o obj/volga/vm.o obj/volga/vm_mem.o
	@echo "Combining volga"
	@$(GXX) -o bin/volga $^ -Isrc/volga
