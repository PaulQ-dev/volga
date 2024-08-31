#pragma once

#include <stdio.h>
#include <iostream>
#include <stdint.h>
#include <string>
#include <cstring>
#include "../mem.h"

using namespace std;

namespace paulq::volga{
	class volga_vm{
	private:
		vm_byte* memory;
		vm_byte* stack;
		

		vm_byte regs[16];
		vm_byte cpuFlags, dtB0, dtB1, rdB, sPtr;

		vm_addr aRegs[4];
		vm_addr adB0, adB1, pC;

		const vm_addr halt = 0x8FFF;
		const vm_addr con_out = 0x9000;
		memory_block zp_blk, ram_blk, stack_blk, rom_blk;
		const int mem_len = 0x10000;

		const vm_byte cF = 0b10000000;
		const vm_byte zF = 0b01000000;
		const vm_byte nF = 0b00100000;
		const vm_byte hF = 0b00000001;

		vm_byte read(vm_addr address); void write(vm_addr address, vm_byte data);
		vm_addr readAddr(vm_addr address); void writeAddr(vm_addr address, vm_addr data);
		vm_byte readPC(); vm_addr readAddrPC();
		vm_byte pull(); void push(vm_byte data);
		vm_addr pullAddr(); void pushAddr(vm_addr data);
	public:
		int run();
		int load(vm_byte* rom, short rom_len); int load(FILE* file); int load(string file);

		volga_vm();
		~volga_vm();
	};
}
