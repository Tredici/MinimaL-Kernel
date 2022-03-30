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
#define VMX_EXIT_NMI 0
/*[ 0]*/ "Exception or non-maskable interrupt (NMI)",
#define VMX_EXIT_EXTERNAL_INTERRUPT 1
/*[ 1]*/ "External interrupt",
#define VMX_EXIT_TRIPLE_FAULT 2
/*[ 2]*/ "Triple fault",
#define VMX_EXIT_INIT_SIGNAL 3
/*[ 3]*/ "INIT signal",
#define VMX_EXIT_SIPI 4
/*[ 4]*/ "Start-up IPI (SIPI)",
#define VMX_EXIT_IO_SMI 5
/*[ 5]*/ "I/O system-management interrupt (SMI)",
#define VMX_EXIT_OTHER_SMI 6
/*[ 6]*/ "Other SMI",
#define VMX_EXIT_INTERRUPTWINDOW 7
/*[ 7]*/ "Interrupt window",
#define VMX_EXIT_NMI_WINDOW 8
/*[ 8]*/ "NMI window",
#define VMX_EXIT_TASK_SWITCH 9
/*[ 9]*/ "Task switch",
#define VMX_EXIT_CPUID 10
/*[10]*/ "CPUID",
#define VMX_EXIT_GETSEC 11
/*[11]*/ "GETSEC",
#define VMX_EXIT_HLT 12
/*[12]*/ "HLT",
#define VMX_EXIT_INVD 13
/*[13]*/ "INVD",
#define VMX_EXIT_INVLPG 14
/*[14]*/ "INVLPG",
#define VMX_EXIT_RDPMC 15
/*[15]*/ "RDPMC",
#define VMX_EXIT_RDTSC 16
/*[16]*/ "RDTSC",
#define VMX_EXIT_RSM 17
/*[17]*/ "RSM",
#define VMX_EXIT_VMCALL 18
/*[18]*/ "VMCALL",
#define VMX_EXIT_VMCLEAR 19
/*[19]*/ "VMCLEAR",
#define VMX_EXIT_VMLAUNCH 20
/*[20]*/ "VMLAUNCH",
#define VMX_EXIT_VMPTRLD 21
/*[21]*/ "VMPTRLD",
#define VMX_EXIT_VMPTRST 22
/*[22]*/ "VMPTRST",
#define VMX_EXIT_VMREAD 23
/*[23]*/ "VMREAD",
#define VMX_EXIT_VMRESUME 24
/*[24]*/ "VMRESUME",
#define VMX_EXIT_VMWRITE 25
/*[25]*/ "VMWRITE",
#define VMX_EXIT_VMXOFF 26
/*[26]*/ "VMXOFF",
#define VMX_EXIT_VMXON 27
/*[27]*/ "VMXON",
#define VMX_EXIT_CONTROL_REGISTER_ACCESSES 28
/*[28]*/ "Control-register accesses",
#define VMX_EXIT_MOV_DR 29
/*[29]*/ "MOV DR",
#define VMX_EXIT_IO 30
/*[30]*/ "I/O instruction",
#define VMX_EXIT_RDMSR 31
/*[31]*/ "RDMSR",
#define VMX_EXIT_WRMSR 32
/*[32]*/ "WRMSR",
#define VMX_EXIT_VM_ENTRY_FAILURE_DUE_TO_INVALID_GUEST_STATE 33
/*[33]*/ "VM-entry failure due to invalid guest state",
#define VMX_EXIT_VM_ENTRY_FAILURE_DUE_TO_MSR_LOADING 34
/*[34]*/ "VM-entry failure due to MSR loading",
#define VMX_EXIT_UNKNOWN 35
/*[35]*/ "UNKNOWN",
#define VMX_EXIT_MWAIT 36
/*[36]*/ "MWAIT",
#define VMX_EXIT_MONITOR_TRAP_FLAG 37
/*[37]*/ "Monitor trap flag",
//#define VMX_EXIT_UNKNOWN 38
/*[38]*/ "UNKNOWN",
#define VMX_EXIT_MONITOR 39
/*[39]*/ "MONITOR",
#define VMX_EXIT_PAUSE 40
/*[40]*/ "PAUSE",
#define VMX_EXIT_VM_ENTRY_FAILURE_DUE_TO_MACHINE_CHECK_EVENT 41
/*[41]*/ "VM-entry failure due to machine-check event",
//#define VMX_EXIT_UNKNOWN 42
/*[42]*/ "UNKNOWN",
#define VMX_EXIT_TPR_BELOW_THRESHOLD 43
/*[43]*/ "TPR below threshold",
#define VMX_EXIT_APIC_ACCESS 44
/*[44]*/ "APIC access",
#define VMX_EXIT_VIRTUALIZED_EOI 45
/*[45]*/ "Virtualized EOI",
#define VMX_EXIT_ACCESS_TO_GDTR_OR_IDTR 46
/*[46]*/ "Access to GDTR or IDTR",
#define VMX_EXIT_ACCESS_TO_LDTR_OR_TR 47
/*[47]*/ "Access to LDTR or TR",
#define VMX_EXIT_EPT_VIOLATION 48
/*[48]*/ "EPT violation",
#define VMX_EXIT_EPT_MISCONFIGURATION 49
/*[49]*/ "EPT misconfiguration",
#define VMX_EXIT_INVEPT 50
/*[50]*/ "INVEPT",
#define VMX_EXIT_RDTSCP 51
/*[51]*/ "RDTSCP",
#define VMX_EXIT_VMX_PREEMPTION_TIMER_EXPIRED 52
/*[52]*/ "VMX-preemption timer expired",
#define VMX_EXIT_INVVPID 53
/*[53]*/ "INVVPID",
#define VMX_EXIT_WBINVD_OR_WBNOINVD 54
/*[54]*/ "WBINVD or WBNOINVD",
#define VMX_EXIT_XSETBV 55
/*[55]*/ "XSETBV",
#define VMX_EXIT_APIC_WRITE 56
/*[56]*/ "APIC write",
#define VMX_EXIT_RDRAND 57
/*[57]*/ "RDRAND",
#define VMX_EXIT_INVPCID 58
/*[58]*/ "INVPCID",
#define VMX_EXIT_VMFUNC 59
/*[59]*/ "VMFUNC",
#define VMX_EXIT_ENCLS 60
/*[60]*/ "ENCLS",
#define VMX_EXIT_RDSEED 61
/*[61]*/ "RDSEED",
#define VMX_EXIT_PAGE_MODIFICATION_LOG_FULL 62
/*[62]*/ "Page-modification log full",
#define VMX_EXIT_XSAVES 63
/*[63]*/ "XSAVES",
#define VMX_EXIT_XRSTORS 64
/*[64]*/ "XRSTORS",
//#define VMX_EXIT_UNKNOWN 65
/*[65]*/ "UNKNOWN",
#define VMX_EXIT_SPP_RELATED_EVENT 66
/*[66]*/ "SPP-related event",
#define VMX_EXIT_UMWAIT 67
/*[67]*/ "UMWAIT",
#define VMX_EXIT_TPAUSE 68
/*[68]*/ "TPAUSE",
#define VMX_EXIT_LOADIWKEY 69
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
