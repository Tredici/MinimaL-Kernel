#include "vm64_helpers.h"
#include "../video64bit.h"
#include "../error64.h"
#include "vm64_guest.h"
#include "../msr.h"
#include "vm64_control.h"

int test = 0;

void vmx_print_vm_gp_registers(struct vm64_registers* registers)
{
    putstr64("RAX = "); puthex64(registers->RAX);
    putstr64("    RBX = "); puthex64(registers->RBX); newline64();
    putstr64("RCX = "); puthex64(registers->RCX);
    putstr64("    RDX = "); puthex64(registers->RDX); newline64();

    putstr64("RSI = "); puthex64(registers->RSI);
    putstr64("    RDI = "); puthex64(registers->RDI); newline64();
    putstr64("RBP = "); puthex64(registers->RBP);
    putstr64("    RSP = "); puthex64(registers->RSP); newline64();

    putstr64("R8  = "); puthex64(registers->R8);
    putstr64("    R9  = "); puthex64(registers->R9); newline64();
    putstr64("R10 = "); puthex64(registers->R10);
    putstr64("    R11 = "); puthex64(registers->R11); newline64();
    putstr64("R12 = "); puthex64(registers->R12);
    putstr64("    R13 = "); puthex64(registers->R13); newline64();
    putstr64("R14 = "); puthex64(registers->R14);
    putstr64("    R15 = "); puthex64(registers->R15); newline64();

    putstr64("RIP = "); puthex64(registers->RIP); newline64();
}

void vmx_debug_virtual_machine(struct vm64_registers* registers)
{
    clear_screen64();
    printline64("***** DEBUGGING VM *****");
    if (!registers)
    {
        panic64("No data!");
    }

    vmx_print_vm_gp_registers(registers);

    putstr64("test = "); puti64(test); newline64();

    //  putstr64("    code  = "); puthex64(vmx_get_guest_code()); newline64();
    //  putstr64("    stack = "); puthex64(vmx_get_guest_stack()); newline64();
    putstr64("Guest Activity state = "); puti64(vmx_guest_read_activity_state()); newline64();
    {
        unsigned long r = (unsigned)vmx_read_vm_exit_reason();
        putstr64("EXIT REASON = ");
        puthex64(r);
        putstr64(" [");
        putstr64(vmx_exit_reason(r));
        putstr64("]");
        newline64();
    }
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

/**
 * See Intel Manual Vol. 3
 *  [23.9 VM-EXIT INFORMATION FIELDS]
 *
 * It is foundamental to understand why exit does occur!
 */
static const char *vmx_exits[] = {
/*[ 0]*/ "Exception or non-maskable interrupt (NMI)",
/*[ 1]*/ "External interrupt",
/*[ 2]*/ "Triple fault",
/*[ 3]*/ "INIT signal",
/*[ 4]*/ "Start-up IPI (SIPI)",
/*[ 5]*/ "I/O system-management interrupt (SMI)",
/*[ 6]*/ "Other SMI",
/*[ 7]*/ "Interrupt window",
/*[ 8]*/ "NMI window",
/*[ 9]*/ "Task switch",
/*[10]*/ "CPUID",
/*[11]*/ "GETSEC",
/*[12]*/ "HLT",
/*[13]*/ "INVD",
/*[14]*/ "INVLPG",
/*[15]*/ "RDPMC",
/*[16]*/ "RDTSC",
/*[17]*/ "RSM",
/*[18]*/ "VMCALL",
/*[19]*/ "VMCLEAR",
/*[20]*/ "VMLAUNCH",
/*[21]*/ "VMPTRLD",
/*[22]*/ "VMPTRST",
/*[23]*/ "VMREAD",
/*[24]*/ "VMRESUME",
/*[25]*/ "VMWRITE",
/*[26]*/ "VMXOFF",
/*[27]*/ "VMXON",
/*[28]*/ "Control-register accesses",
/*[29]*/ "MOV DR",
/*[30]*/ "I/O instruction",
/*[31]*/ "RDMSR",
/*[32]*/ "WRMSR",
/*[33]*/ "VM-entry failure due to invalid guest state",
/*[34]*/ "VM-entry failure due to MSR loading",
/*[35]*/ "UNKNOWN",
/*[36]*/ "MWAIT",
/*[37]*/ "Monitor trap flag",
/*[38]*/ "UNKNOWN",
/*[39]*/ "MONITOR",
/*[40]*/ "PAUSE",
/*[41]*/ "VM-entry failure due to machine-check event",
/*[42]*/ "UNKNOWN",
/*[43]*/ "TPR below threshold",
/*[44]*/ "APIC access",
/*[45]*/ "Virtualized EOI",
/*[46]*/ "Access to GDTR or IDTR",
/*[47]*/ "Access to LDTR or TR",
/*[48]*/ "EPT violation",
/*[49]*/ "EPT misconfiguration",
/*[50]*/ "INVEPT",
/*[51]*/ "RDTSCP",
/*[52]*/ "VMX-preemption timer expired",
/*[53]*/ "INVVPID",
/*[54]*/ "WBINVD or WBNOINVD",
/*[55]*/ "XSETBV",
/*[56]*/ "APIC write",
/*[57]*/ "RDRAND",
/*[58]*/ "INVPCID",
/*[59]*/ "VMFUNC",
/*[60]*/ "ENCLS",
/*[61]*/ "RDSEED",
/*[62]*/ "Page-modification log full",
/*[63]*/ "XSAVES",
/*[64]*/ "XRSTORS",
/*[65]*/ "UNKNOWN",
/*[66]*/ "SPP-related event",
/*[67]*/ "UMWAIT",
/*[68]*/ "TPAUSE",
/*[69]*/ "LOADIWKEY",
};
const char *vmx_exit_reason(int number)
{
    /**
     * Only the low 16 bits are used.
     * See Intel Manual Vol. 3
     *  [APPENDIX C VMX BASIC EXIT REASONS]
     *  The low 16 bits of the exit-reason field form
     *  the basic exit reason which provides basic
     *  informa tion about the cause of the VM exit or
     *  VM-entry failure.
     */
    number &= 0xffff;
    if (number < 0 || number >= sizeof(vmx_exits)/sizeof(*vmx_exits))
    {
        return (void*)0;
    }

    return vmx_exits[number];
}

/**
 * See Intel Manual Vol. 3
 *  [22.8 RESTRICTIONS ON VMX OPERATION]
 *  VMX operation places restrictions on processor operation.
 *  These are detailed below:
 *      +In VMX operation, processors may fix certain bits in CR0
 *       and CR4 to specific values and not support other values.
 *       VMXON fails if any of these bits contains an unsupported
 *       value (see “VMXON—Enter VMX Operation” in Chapter 29).
 *       Any attempt to set one of these bits to an unsupported
 *       value while in VMX operation (including VMX root
 *       operation) using any of the CLTS, LMSW, or MOV CR
 *       instructions causes a general-protection exception. VM
 *       entry or VM exit cannot set any of these bits to an
 *       unsupported value. Software should consult the VMX
 *       capability MSRs IA32_VMX_CR0_FIXED0 and
 *       IA32_VMX_CR0_FIXED1 to determine how bits in CR0 are
 *       fixed (see Appendix A.7). For CR4, software should
 *       consult the VMX capability MSRs IA32_VMX_CR4_FIXED0 and
 *       IA32_VMX_CR4_FIXED1 (see Appendix A.8).
 *
 * See reference for details.
 */

int vmx_validate_cr0(long cr0)
{
    /**
     * See Intel Manual Vol. 3
     *  [A.7 VMX-FIXED BITS IN CR0]
     *  The IA32_VMX_CR0_FIXED0 MSR (index 486H) and
     *  IA32_VMX_CR0_FIXED1 MSR (index 487H) indicate how bits
     *  in CR0 may be set in VMX operation. They report on bits
     *  in CR0 that are allowed to be 0 and to be 1, respectively,
     *  in VMX operation. If bit X is 1 in IA32_VMX_CR0_FIXED0,
     *  then that bit of CR0 is fixed to 1 in VMX operation.
     */
    const long fixed0 = msr_read_ia32_vmx_cr0_fixed0();
    if (fixed0 != (fixed0 & cr0))
    {
        // Return missing bits
        return fixed0 ^ (fixed0 & cr0);
    }
    /**
     *  Similarly, if bit X is 0 in IA32_VMX_CR0_FIXED1, then that
     *  bit of CR0 is fixed to 0 in VMX operation. It is always
     *  the case that, if bit X is 1 in IA32_VMX_CR0_FIXED0, then
     *  that bit is also 1 in IA32_VMX_CR0_FIXED1; if bit X is 0
     *  in IA32_VMX_CR0_FIXED1, then that bit is also 0 in
     *  IA32_VMX_CR0_FIXED0. Thus, each bit in CR0 is either fixed
     *  to 0 (with value 0 in both MSRs), fixed to 1 (1 in both
     *  MSRs), or flexible (0 in IA32_VMX_CR0_FIXED0 and 1 in
     *  IA32_VMX_CR0_FIXED1).
     */
    const long fixed1 = ~msr_read_ia32_vmx_cr0_fixed1();
    if (fixed1 & cr0)
    {
        // Return nonzero bits
        return fixed1 & cr0;
    }

    return 0;
}

int vmx_validate_cr4(long cr4)
{
    /**
     * See Intel Manual Vol. 3
     *  [A.8 VMX-FIXED BITS IN CR4]
     *  The IA32_VMX_CR4_FIXED0 MSR (index 488H) and
     *  IA32_VMX_CR4_FIXED1 MSR (index 489H) indicate how bits
     *  in CR4 may be set in VMX operation. They report on bits
     *  in CR4 that are allowed to be 0 and 1, respectively,
     *  in VMX operation. If bit X is 1 in IA32_VMX_CR4_FIXED0,
     *  then that bit of CR4 is fixed to 1 in VMX operation.
     */
    const long fixed0 = msr_read_ia32_vmx_cr4_fixed0();
    if (fixed0 != (fixed0 & cr4))
    {
        return fixed0 ^ (fixed0 & cr4);
    }
    /**
     *  Similarly, if bit X is 0 in IA32_VMX_CR4_FIXED1, then that
     *  bit of CR4 is fixed to 0 in VMX operation. It is always
     *  the case that, if bit X is 1 in IA32_VMX_CR4_FIXED0, then
     *  that bit is also 1 in IA32_VMX_CR4_FIXED1; if bit X is 0
     *  in IA32_VMX_CR4_FIXED1, then that bit is also 0 in
     *  IA32_VMX_CR4_FIXED0. Thus, each bit in CR4 is either fixed
     *  to 0 (with value 0 in both MSRs), fixed to 1 (1 in both
     *  MSRs), or flexible (0 in IA32_VMX_CR4_FIXED0 and 1 in
     *  IA32_VMX_CR4_FIXED1)
     */
    const long fixed1 = ~msr_read_ia32_vmx_cr4_fixed1();
    if (fixed1 & cr4)
    {
        return fixed1 & cr4;
    }

    return 0;
}
