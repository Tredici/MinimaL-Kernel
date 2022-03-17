
#ifndef VM64_HELPERS
#define VM64_HELPERS

struct vm64_registers
{
    long RAX;
    long RBX;
    long RCX;
    long RDX;

    long RDI;
    long RSI;
    long RBP;

    long R8;
    long R9;
    long R10;
    long R11;
    long R12;
    long R13;
    long R14;
    long R15;

    long RSP;
    long RIP;
};

void vmx_debug_vmx(struct vm64_registers* registers);

#endif
