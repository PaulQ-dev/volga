#pragma once

typedef unsigned char vm_byte;
typedef unsigned short vm_addr;

struct memory_block{
    vm_addr start;
    vm_addr end;
};