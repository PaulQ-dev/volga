#pragma once

#include <stdio.h>
#include <stdint.h>
#include <string>
#include <cstring>
#include "mem.h"

using namespace std;

namespace paulq::volga{
	class volgavm{
	private:
		vm_byte* memory;

		vm_byte regs[16];
		vm_byte _procFlags, _dataBuff0, _dataBuff1, _readBuff, _stackPtr;

		vm_addr aRegs[4];
		vm_addr _addrBuff0, _addrBuff1, _progCount;

		const vm_addr con_out = 0x9000;
		memory_block zp, ram, stack, rom;
		const int mem_len = 0x10000;

		vm_byte read(vm_addr address); void write(vm_addr address, vm_byte data);
		vm_addr readAddr(vm_addr address); void writeAddr(vm_addr address, vm_addr data);
		vm_byte pull(); void push(vm_byte data);
		vm_addr pullAddr(); void pushAddr(vm_addr data);
	public:
		int run();
		int load(vm_byte* rom, short rom_len); int load(FILE* file); int load(string file);

		volgavm();
	};
}
