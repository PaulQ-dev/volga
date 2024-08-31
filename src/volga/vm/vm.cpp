#include "vm.h"

using namespace paulq::volga;

int volga_vm::load(vm_byte* rom_bytes, short rom_len){
    if(rom_len > rom_blk.end - rom_blk.start) return 1;
    else if(rom_len < 1) return -1;
    else{
        memcpy(memory + rom_blk.start, rom_bytes, rom_len);
        return 0;
    }
}
int volga_vm::load(FILE* file){
    fseek(file, 0L, SEEK_END);
    short size = ftell(file);
    rewind(file);
    vm_byte rom[size] = {0};
    fread(rom, size, 1, file);
    return load(rom, size);
}
int volga_vm::load(string file){
    FILE* f = fopen(file.c_str(), "r");
    int retVal = load(f);
    fclose(f);
    return retVal;
}

int volga_vm::run(){
    pC = rom_blk.start;
    while(true){
        readPC();
        if(rdB >> 4 == 0){ //ht b
            return rdB & 0x0F;
        } else {
            switch (rdB)
            {
            case 0x40: //ld #,r
                dtB0 = readPC();
                dtB1 = readPC() & 0xF;
                regs[dtB1] = dtB0;
                break;
            case 0x90: //st r,a
                dtB1 = readPC() & 0xF;
                adB0 = readAddrPC();
                dtB0 = regs[dtB1];
                write(adB0, dtB0);
                break;
            case 0xA0: //add #,r
                dtB0 = readPC();
                dtB1 = readPC() & 0xF;
                if((regs[dtB1] + dtB0) > 0xFF ) cpuFlags = cpuFlags | cF;
                else cpuFlags = cpuFlags & (!cF);
                regs[dtB1] += dtB0;
                break;
            case 0xB0: //bre r,#,a
                dtB1 = readPC() & 0xF;
                dtB0 = readPC();
                if(regs[dtB1] == dtB0) goto jump_to_read_address;
                readAddrPC();
                break;
            case 0xC0: //bcc a
                if(cpuFlags&cF) goto jump_to_read_address;
                readAddrPC();
                break;
            case 0xD0: //jp a
            jump_to_read_address:
                adB0 = readAddrPC();
                pC = adB0;
                break;
            default:
                break;
            }
        }
        if(cpuFlags & 0b00000001 == 1) return dtB0;
    }
}


volga_vm::volga_vm(){
    cpuFlags = 0b00000000; //CZN----H
    sPtr = 0x00;
    rdB = 0x00;
    dtB0 = 0x00;
    dtB1 = 0x00;
    adB0 = 0x0000;
    adB1 = 0x0000;
    zp_blk.start = 0x0000;
    zp_blk.end = 0x00FF;
    ram_blk.start = 0x0100;
    ram_blk.end = 0x80FF;
    stack_blk.start = 0x8100;
    stack_blk.end = 0x81FF;
    rom_blk.start = 0xA000;
    rom_blk.end = 0xFFFF;
    for (char i = 0; i < 16; i++){
        regs[i] = 0x00;
    }
    for (char i = 0; i < 4; i++){
        aRegs[i] = 0x0000;
    }
    memory = (vm_byte*)calloc(mem_len,1);
    stack = memory + stack_blk.start;
}
volga_vm::~volga_vm(){
    free(memory);
}