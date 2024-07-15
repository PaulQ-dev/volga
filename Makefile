.PHONY: all clean clean_bin clean_obj clean_all run run_only

GXX-O = g++ -c -o
GXX = g++ -o

VOLGA = src/volga

all: volga

clean_bin:
	@rm -f bin/volga
	@rm -f bin/*.so
	@echo "Binaries cleaned"
clean_obj:
	@rm -f obj/*.o
	@echo "Object files cleaned"
clean: clean_obj
clean_all: clean_obj clean_bin

main.o:
	@echo "GXX $(VOLGA)/main.cpp -> obj/volga.o"
	@$(GXX-O) obj/$@ $(VOLGA)/main.cpp  -I $(VOLGA)
vm.o:
	@echo "GXX $(VOLGA)/vm/vm.cpp -> obj/vm.o"
	@$(GXX-O) obj/$@ $(VOLGA)/vm/vm.cpp -I $(VOLGA)

volga: clean_obj main.o vm.o
	@echo "LD  obj/main.o obj/vm.o -> bin/volga"
	@$(GXX) bin/volga obj/main.o obj/vm.o -I $(VOLGA)

run_only:
	@./bin/volga
run: volga run_only
