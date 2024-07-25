#include "vm.h"

using namespace paulq::volga;

int volgavm::load(vm_byte* rom_bytes, short rom_len){
    if(rom_len > rom.end - rom.start) return 1;
    else if(rom_len < 1) return -1;
    else{
        memcpy(memory + rom.start, rom_bytes, rom_len);
        return 0;
    }
}
int volgavm::load(FILE* file){
    fseek(file, 0L, SEEK_END);
    short size = ftell(file);
    rewind(file);
    vm_byte rom[size] = {0};
    fread(rom, size, 1, file);
    return load(rom, size);
}
int volgavm::load(string file){
    FILE* f = fopen(file.c_str(), "r");
    int retVal = load(f);
    fclose(f);
    return retVal;
}

vm_byte volgavm::read(vm_addr address){
    if(address <= stack.end || address == con_out || address >= rom.start) _readBuff = memory[address];
    return _readBuff;
}
void volgavm::write(vm_addr address, vm_byte data){
    if(address == con_out) { memory[address] = data; cout << data; }
    if(address == halt) { _procFlags = _procFlags | 0b00000001; _dataBuff0 = data; }
    else if(address <= stack.end) memory[address] = data; 
}
vm_addr volgavm::readAddr(vm_addr address){
    return read(address) | (read(address + 1) << 8);
}
void volgavm::writeAddr(vm_addr address, vm_addr data){
    write(address, (vm_byte)(data & 0xFF));
    write(address + 1, (vm_byte)(data >> 8));
}
vm_byte volgavm::readPC(){
    vm_byte result = read(_progCount);
    _progCount++;
    return result;
}
vm_addr volgavm::readAddrPC(){
    vm_addr result = readAddr(_progCount);
    _progCount+=2;
    return result;
}

vm_byte volgavm::pull(){
    _readBuff = memory[stack.start + _stackPtr];
    _stackPtr--;
    return _readBuff;
}
void volgavm::push(vm_byte data){
    _stackPtr++;
    memory[stack.start + _stackPtr] = data;
}
vm_addr volgavm::pullAddr(){
    return pull() | (pull() << 8);
}
void volgavm::pushAddr(vm_addr data){
    push((vm_byte)(data & 0xFF));
    push((vm_byte)(data >> 8));
}

int volgavm::run(){
    _progCount = rom.start;
    while(true){
        readPC();
        if(_readBuff >> 4 == 0){
            return _readBuff & 0x0F;
        } else {
            switch (_readBuff)
            {
            case 0x40:
                _dataBuff0 = readPC();
                _dataBuff1 = readPC();
                regs[_dataBuff1 & 0xF] = _dataBuff0;
                break;
            case 0x90:
                _dataBuff1 = readPC();
                _addrBuff0 = readAddrPC();
                _dataBuff0 = regs[_dataBuff1 & 0xF];
                write(_addrBuff0, _dataBuff0);
                break;
            case 0xB0:
                _dataBuff1 = readPC();
                _dataBuff0 = readPC();
                if(regs[_dataBuff1 & 0xF] == _dataBuff0) goto jp_a;
                break;
            case 0xD0:
            jp_a:
                _addrBuff0 = readAddrPC();
                _progCount = _addrBuff0;
                break;
            default:
                break;
            }
        }
        if(_procFlags & 0b00000001 == 1) return _dataBuff0;
    }
}


volgavm::volgavm(){
    for (char i = 0; i < 16; i++){
        regs[i] = 0x00;
    }
    for (char i = 0; i < 4; i++){
        aRegs[i] = 0x0000;
    }
    memory = (vm_byte*)calloc(mem_len,1);
    _procFlags = 0b00000000;
    _stackPtr = 0x00;
    _readBuff = 0x00;
    _dataBuff0 = 0x00;
    _dataBuff1 = 0x00;
    _addrBuff0 = 0x0000;
    _addrBuff1 = 0x0000;
    zp.start = 0x0000;
    zp.end = 0x00FF;
    ram.start = 0x0100;
    ram.end = 0x80FF;
    stack.start = 0x8100;
    stack.end = 0x81FF;
    rom.start = 0xA000;
    rom.end = 0xFFFF;
}