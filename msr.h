
#ifndef MSR
#define MSR

long msr_read(int msr);
void msr_write(int msr, long value);

long msr_read_ia32_sysenter_cs();
long msr_read_ia32_sysenter_esp();
long msr_read_ia32_sysenter_eip();
long msr_read_ia32_debugctl();
long msr_read_ia32_vmx_basic();
long msr_read_ia32_vmx_exit_ctls();
long msr_read_ia32_vmx_entry_ctls();
long msr_read_ia32_vmx_true_exit_ctls();

#endif
