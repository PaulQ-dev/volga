#include "vm.h"

using namespace paulq::volga;

vm_byte volga_vm::read(vm_addr address){
    if(address <= stack_blk.end || address == con_out || address >= rom_blk.start) rdB = memory[address];
    return rdB;
}
void volga_vm::write(vm_addr address, vm_byte data){
    if(address == con_out) { memory[address] = data; cout << data; }
    if(address == halt) { cpuFlags = cpuFlags | hF; dtB0 = data; }
    else if(address <= stack_blk.end) memory[address] = data; 
}
vm_addr volga_vm::readAddr(vm_addr address){
    return read(address) | (read(address + 1) << 8);
}
void volga_vm::writeAddr(vm_addr address, vm_addr data){
    write(address, (vm_byte)(data & 0xFF));
    write(address + 1, (vm_byte)(data >> 8));
}
vm_byte volga_vm::readPC(){
    vm_byte result = read(pC);
    pC++;
    return result;
}
vm_addr volga_vm::readAddrPC(){
    vm_addr result = readAddr(pC);
    pC+=2;
    return result;
}

vm_byte volga_vm::pull(){
    rdB = stack[sPtr];
    sPtr--;
    return rdB;
}
void volga_vm::push(vm_byte data){
    sPtr++;
    stack[sPtr] = data;
}
vm_addr volga_vm::pullAddr(){
    return pull() | (pull() << 8);
}
void volga_vm::pushAddr(vm_addr data){
    push((vm_byte)(data & 0xFF));
    push((vm_byte)(data >> 8));
}