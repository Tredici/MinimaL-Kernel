#include "vm64_helpers.h"
#include "video64bit.h"
#include "error64.h"
#include "vm64_guest.h"

void vmx_debug_virtual_machine(struct vm64_registers* registers)
{
    clear_screen64();
    printline64("***** DEBUGGING VM *****");
    if (!registers)
    {
        panic64("No data!");
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

    //  putstr64("    code  = "); puthex64(vmx_get_guest_code()); newline64();
    //  putstr64("    stack = "); puthex64(vmx_get_guest_stack()); newline64();
    putstr64("Guest Activity state = "); puti64(vmx_guest_read_activity_state()); newline64();
}

/**
 * See Intel Manual Vol. 3
 *  [29.4 VM INSTRUCTION ERROR NUMBERS]
 *  For certain error conditions, the VM-instruction
 *  error field is loaded with an error number to indicate
 *  the source of the error.
 *  Table 29-1 lists VM-instruction error numbers.
 */
static const char *vmx_errors[] = {
/*[ 0]*/  "Success",
/*[ 1]*/  "VMCALL executed in VMX root operation",
/*[ 2]*/  "VMCLEAR with invalid physical address",
/*[ 3]*/  "VMCLEAR with VMXON pointer",
/*[ 4]*/  "VMLAUNCH with non-clear VMCS",
/*[ 5]*/  "VMRESUME with non-launched VMCS",
/*[ 6]*/  "VMRESUME after VMXOFF (VMXOFF and VMXON between VMLAUNCH and VMRESUME)",
/*[ 7]*/  "VM entry with invalid control field(s)",
/*[ 8]*/  "VM entry with invalid host-state field(s)",
/*[ 9]*/  "VMPTRLD with invalid physical address",
/*[10]*/  "VMPTRLD with VMXON pointer",
/*[11]*/  "VMPTRLD with incorrect VMCS revision identifier",
/*[12]*/  "VMREAD/VMWRITE from/to unsupported VMCS component",
/*[13]*/  "VMWRITE to read-only VMCS component",
/*[14]*/  "UNKNOWN",
/*[15]*/  "VMXON executed in VMX root operation",
/*[16]*/  "VM entry with invalid executive-VMCS pointer",
/*[17]*/  "VM entry with non-launched executive VMCS",
/*[18]*/  "VM entry with executive-VMCS pointer not VMXON pointer (when attempting to deactivate the dual-monitor treatment of SMIs and SMM)",
/*[19]*/  "VMCALL with non-clear VMCS (when attempting to activate the dual-monitor treatment of SMIs and SMM)",
/*[20]*/  "VMCALL with invalid VM-exit control fields",
/*[21]*/  "UNKNOWN",
/*[22]*/  "VMCALL with incorrect MSEG revision identifier (when attempting to activate the dual-monitor treatment of SMIs and SMM)",
/*[23]*/  "VMXOFF under dual-monitor treatment of SMIs and SMM",
/*[24]*/  "VMCALL with invalid SMM-monitor features (when attempting to activate the dual-monitor treatment of SMIs and SMM)",
/*[25]*/  "VM entry with invalid VM-execution control fields in executive VMCS (when attempting to return from SMM)",
/*[26]*/  "VM entry with events blocked by MOV SS.",
/*[27]*/  "UNKNOWN",
/*[28]*/  "Invalid operand to INVEPT/INVVPID."
};

const char *vmx_error_reason(int number)
{
    if (number < 0 || number >= sizeof(vmx_errors)/sizeof(*vmx_errors))
    {
        return (void*)0;
    }

    return vmx_errors[number];
}
