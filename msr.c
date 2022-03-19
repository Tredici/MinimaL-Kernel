#include "msr.h"

#define MSR_IA32_SYSENTER_CS    0x174
#define MSR_IA32_SYSENTER_ESP   0x175
#define MSR_IA32_SYSENTER_EIP   0x176
#define MSR_IA32_DEBUGCTL       0x1D9

#define MSR_IA32_VMX_BASIC          0x480
#define MSR_IA32_VMX_EXIT_CTLS      0x483      
#define MSR_IA32_VMX_ENTRY_CTLS     0x484
#define MSR_IA32_VMX_TRUE_EXIT_CTLS 0x48F

long msr_read_ia32_sysenter_cs()
{
    return msr_read(MSR_IA32_SYSENTER_CS);
}

long msr_read_ia32_sysenter_esp()
{
    return msr_read(MSR_IA32_SYSENTER_ESP);
}

long msr_read_ia32_sysenter_eip()
{
    return msr_read(MSR_IA32_SYSENTER_EIP);
}

long msr_read_ia32_debugctl()
{
    return msr_read(MSR_IA32_DEBUGCTL);
}

long msr_read_ia32_vmx_basic()
{
    return msr_read(MSR_IA32_VMX_BASIC);
}

long msr_read_ia32_vmx_exit_ctls()
{
    return msr_read(MSR_IA32_VMX_EXIT_CTLS);
}

long msr_read_ia32_vmx_entry_ctls()
{
    return msr_read(MSR_IA32_VMX_ENTRY_CTLS);
}

long msr_read_ia32_vmx_true_exit_ctls()
{
    return msr_read(MSR_IA32_VMX_TRUE_EXIT_CTLS);
}
