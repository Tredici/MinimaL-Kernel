
#ifndef MSR
#define MSR

long msr_read(int msr);
void msr_write(int msr, long value);

long msr_read_ia32_sysenter_cs();
long msr_read_ia32_sysenter_esp();
long msr_read_ia32_sysenter_eip();
long msr_read_ia32_debugctl();

long msr_read_ia32_pat();

long msr_read_ia32_ia32_perf_global_ctrl();

long msr_read_ia32_vmx_basic();
long msr_read_ia32_vmx_pinbased_ctls();
long msr_read_ia32_vmx_procbased_ctls();
long msr_read_ia32_vmx_exit_ctls();
long msr_read_ia32_vmx_entry_ctls();

long msr_read_ia32_vmx_cr0_fixed0();
long msr_read_ia32_vmx_cr0_fixed1();
long msr_read_ia32_vmx_cr4_fixed0();
long msr_read_ia32_vmx_cr4_fixed1();

long msr_read_ia32_vmx_true_exit_ctls();

long msr_read_ia32_pkrs();

long msr_read_ia32_fs_base();
long msr_read_ia32_gs_base();

long msr_read_ia32_efer();

#endif
