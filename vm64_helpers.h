
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

/**
 * Return a statically allocated string
 * describing the given error.
 */
const char *vmx_error_reason(int number);

/**
 * During VMX operation not all values for
 * CRO are supported.
 *
 * The function return 0 if the given value
 * is valid, nozero otherwise.
 */
int vmx_validate_cr0(long cr0);
/**
 * During VMX operation not all values for
 * CR4 are supported.
 *
 * The function return 0 if the given value
 * is valid, nozero otherwise.
 */
int vmx_validate_cr4(long cr4);

#endif
