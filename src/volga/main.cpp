#include <iostream>
#include "vm/vm.h"

using namespace std;
using namespace paulq::volga;

int main(){
	vm_byte rom[] = {
		0x40, 0x41, 0x00, 0x90, 0x00, 0x00, 0x90,
		0x40, 0x0A, 0x00, 0x90, 0x00, 0x00, 0x90
	};
	volgavm vm = volgavm();
	vm.load(rom, size(rom));
	vm.run();
}
