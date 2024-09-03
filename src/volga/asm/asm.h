#pragma once

#include <string>
#include <iostream>
#include "../mem.h"

using namespace std;

struct asm_block
{
    vm_addr addr_start;
    int line_start;
    string name;
};


namespace paulq::volga{
    class volga_asm{
    private:
        int blocks_len;
        asm_block* blocks;
        void skip(const char* orig, char target, int* index);
        void skipTo(const char* orig, char target, int* index);
    public:
        vm_byte* assemble(string code);
    };
}