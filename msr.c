#include "msr.h"

#define MSR_IA32_SYSENTER_CS    0x174
#define MSR_IA32_SYSENTER_ESP   0x175
#define MSR_IA32_SYSENTER_EIP   0x176

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
