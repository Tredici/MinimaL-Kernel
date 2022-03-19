
#ifndef VM64_GUEST
#define VM64_GUEST

short vmx_guest_read_cs();
short vmx_guest_read_ds();
short vmx_guest_read_ss();
short vmx_guest_read_es();
short vmx_guest_read_fs();
short vmx_guest_read_gs();
short vmx_guest_read_ldtr_selector();
short vmx_guest_read_tr_selector();
short vmx_guest_read_interrupt_status();
short vmx_guest_read_pml_index();

void vmx_guest_write_cs(short val);
void vmx_guest_write_ds(short val);
void vmx_guest_write_ss(short val);
void vmx_guest_write_es(short val);
void vmx_guest_write_fs(short val);
void vmx_guest_write_gs(short val);
void vmx_guest_write_ldtr_selector(short val);
void vmx_guest_write_tr_selector(short val);
void vmx_guest_write_interrupt_status(short val);
void vmx_guest_write_pml_index(short val);

int vmx_guest_read_cs_limit();
int vmx_guest_read_ds_limit();
int vmx_guest_read_ss_limit();
int vmx_guest_read_es_limit();
int vmx_guest_read_fs_limit();
int vmx_guest_read_gs_limit();
int vmx_guest_read_ldtr_limit();
int vmx_guest_read_tr_limit();

void vmx_guest_write_cs_limit(int ans);
void vmx_guest_write_ds_limit(int ans);
void vmx_guest_write_ss_limit(int ans);
void vmx_guest_write_es_limit(int ans);
void vmx_guest_write_fs_limit(int ans);
void vmx_guest_write_gs_limit(int ans);
void vmx_guest_write_ldtr_limit(int ans);
void vmx_guest_write_tr_limit(int ans);


long vmx_guest_read_cr0();
long vmx_guest_read_cr3();
long vmx_guest_read_cr4();
long vmx_guest_read_es_base();
long vmx_guest_read_cs_base();
long vmx_guest_read_ss_base();
long vmx_guest_read_ds_base();
long vmx_guest_read_fs_base();
long vmx_guest_read_gs_base();

void vmx_guest_write_cr0(long val);
void vmx_guest_write_cr3(long val);
void vmx_guest_write_cr4(long val);
void vmx_guest_write_es_base(long val);
void vmx_guest_write_cs_base(long val);
void vmx_guest_write_ss_base(long val);
void vmx_guest_write_ds_base(long val);
void vmx_guest_write_fs_base(long val);
void vmx_guest_write_gs_base(long val);

long vmx_guest_read_ldtr_base();
long vmx_guest_read_tr_base();
long vmx_guest_read_gdtr_base();
long vmx_guest_read_idtr_base();
long vmx_guest_read_dr7();
long vmx_guest_read_rsp();
long vmx_guest_read_rip();
long vmx_guest_read_rflags();

void vmx_guest_write_ldtr_base(long val);
void vmx_guest_write_tr_base(long val);
void vmx_guest_write_gdtr_base(long val);
void vmx_guest_write_idtr_base(long val);
void vmx_guest_write_dr7(long val);
void vmx_guest_write_rsp(long val);
void vmx_guest_write_rip(long val);
void vmx_guest_write_rflags(long val);

long vmx_guest_read_pending_debug_exceptions();
long vmx_guest_read_ia32_sysenter_esp();
long vmx_guest_read_ia32_sysenter_eip();
long vmx_guest_read_ia32_s_cet();
long vmx_guest_read_ssp();
long vmx_guest_read_ia32_interrupt_ssp_table_addr();

void vmx_guest_write_pending_debug_exceptions(long val);
void vmx_guest_write_ia32_sysenter_esp(long val);
void vmx_guest_write_ia32_sysenter_eip(long val);
void vmx_guest_write_ia32_s_cet(long val);
void vmx_guest_write_ssp(long val);
void vmx_guest_write_ia32_interrupt_ssp_table_addr(long val);


long vmx_guest_read_vmcs_link_pointer();
long vmx_guest_read_ia32_debugctl();
long vmx_guest_read_ia32_pat();
long vmx_guest_read_ia32_efer();
long vmx_guest_read_ia32_perf_global_ctrl();
long vmx_guest_read_pdpte0();
long vmx_guest_read_pdpte1();
long vmx_guest_read_pdpte2();
long vmx_guest_read_pdpte3();
long vmx_guest_read_ia32_bndcfgs();
long vmx_guest_read_ia32_rtit_ctl();
long vmx_guest_read_ia32_pkrs();

void vmx_guest_write_vmcs_link_pointer(long val);
void vmx_guest_write_ia32_debugctl(long val);
void vmx_guest_write_ia32_pat(long val);
void vmx_guest_write_ia32_efer(long val);
void vmx_guest_write_ia32_perf_global_ctrl(long val);
void vmx_guest_write_pdpte0(long val);
void vmx_guest_write_pdpte1(long val);
void vmx_guest_write_pdpte2(long val);
void vmx_guest_write_pdpte3(long val);
void vmx_guest_write_ia32_bndcfgs(long val);
void vmx_guest_write_ia32_rtit_ctl(long val);
void vmx_guest_write_ia32_pkrs(long val);


#endif
