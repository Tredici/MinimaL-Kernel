#include "vm64_helpers.h"
#include "video64bit.h"
#include "error64.h"


void vmx_debug_virtual_machine(struct vm64_registers* registers)
{
    printline64("***** DEBUGGING VM *****");
    if (!registers)
    {
        panic("No data!");
    }

    putstr64("RAX = "); puthex64(registers->RAX); newline64();
    putstr64("RBX = "); puthex64(registers->RBX); newline64();
    putstr64("RCX = "); puthex64(registers->RCX); newline64();
    putstr64("RDX = "); puthex64(registers->RDX); newline64();

    putstr64("RSI = "); puthex64(registers->RSI); newline64();
    putstr64("RDI = "); puthex64(registers->RDI); newline64();
    putstr64("RBP = "); puthex64(registers->RBP); newline64();
    putstr64("RSP = "); puthex64(registers->RSP); newline64();

    putstr64("R8  = "); puthex64(registers->R8); newline64();
    putstr64("R9  = "); puthex64(registers->R9); newline64();
    putstr64("R10 = "); puthex64(registers->R10); newline64();
    putstr64("R11 = "); puthex64(registers->R11); newline64();
    putstr64("R12 = "); puthex64(registers->R12); newline64();
    putstr64("R13 = "); puthex64(registers->R13); newline64();
    putstr64("R14 = "); puthex64(registers->R14); newline64();
    putstr64("R15 = "); puthex64(registers->R15); newline64();

    putstr64("RIP = "); puthex64(registers->RIP); newline64();
}
