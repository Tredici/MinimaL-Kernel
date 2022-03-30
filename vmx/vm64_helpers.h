
#ifndef VM64_HELPERS
#define VM64_HELPERS

/**
 * See Intel Manual Vol. 3
 *  [29.4 VM INSTRUCTION ERROR NUMBERS]
 *  For certain error conditions, the VM-instruction
 *  error field is loaded with an error number to indicate
 *  the source of the error.
 *  Table 29-1 lists VM-instruction error numbers.
 */
static const char *vmx_errors[] __attribute__((unused)) = {
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


/**
 * See Intel Manual Vol. 3
 *  [23.9 VM-EXIT INFORMATION FIELDS]
 *
 * It is foundamental to understand why exit does occur!
 */
static const char *vmx_exits[] __attribute__((unused)) = {
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

/**
 * Print General Purpose registers values
 * of the VM.
 */
void vmx_print_vm_gp_registers(struct vm64_registers* registers);

int vmx_debug_virtual_machine(struct vm64_registers* registers);

/**
 * Return a statically allocated string
 * describing the given error.
 */
const char *vmx_error_reason(int number);

/**
 * Return a statically allocated string
 * describing the reason of the VMX exit.
 */
const char *vmx_exit_reason(int number);

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
