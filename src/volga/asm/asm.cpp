#include "asm.h"

using namespace paulq::volga;

void volga_asm::skip(const char* orig, char target, int* index){
    while(orig[*index] == target) index[0]++;
}

void volga_asm::skipTo(const char* orig, char target, int* index){
    while(orig[*index] != target) index[0]++;
}

vm_byte* volga_asm::assemble(string _code){
    const char* code = _code.c_str();
    int index = 0;
    int old_index = 0;
    while(true){
        skip(code, '\n', &index);
        skip(code, ' ', &index);
        skip(code, '\t', &index);
        if(old_index == index) break;
        old_index = index;
    }
    
}