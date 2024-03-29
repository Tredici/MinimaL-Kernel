/**
 * VM exits cause host status to be loaded from VMCS
 * Functions defined here serve to store original
 * status in reservied VMCS fields
 * 
 * See Intel Manual Vol. 3
 *  [26.5 LOADING HOST STATE]
 */

#ifndef VM64_HOST
#define VM64_HOST

/* 16-Bit Host-State Fields */
short vmx_host_read_cs();
short vmx_host_read_ds();
short vmx_host_read_ss();
short vmx_host_read_es();
short vmx_host_read_fs();
short vmx_host_read_gs();
short vmx_host_read_tr();

int vmx_host_write_cs(short val);
int vmx_host_write_ds(short val);
int vmx_host_write_ss(short val);
int vmx_host_write_es(short val);
int vmx_host_write_fs(short val);
int vmx_host_write_gs(short val);
int vmx_host_write_tr(short val);


/* Natural-Width Host-State Fields */
long vmx_host_read_cr0();
long vmx_host_read_cr3();
long vmx_host_read_cr4();
long vmx_host_read_fs_base();
long vmx_host_read_gs_base();
long vmx_host_read_tr_base();
long vmx_host_read_gdtr_base();
long vmx_host_read_idtr_base();
long vmx_host_read_ia32_sysenter_esp();
long vmx_host_read_ia32_sysenter_eip();
long vmx_host_read_rsp();
long vmx_host_read_rip();
long vmx_host_read_ia32_s_cet();
long vmx_host_read_ssp();
long vmx_host_read_ia32_interrupt_ssp_table_addr();

int vmx_host_write_cr0(long val);
int vmx_host_write_cr3(long val);
int vmx_host_write_cr4(long val);
int vmx_host_write_fs_base(long val);
int vmx_host_write_gs_base(long val);
int vmx_host_write_tr_base(long val);
int vmx_host_write_gdtr_base(long val);
int vmx_host_write_idtr_base(long val);
int vmx_host_write_ia32_sysenter_esp(long val);
int vmx_host_write_ia32_sysenter_eip(long val);
int vmx_host_write_rsp(long val);
int vmx_host_write_rip(long val);
int vmx_host_write_ia32_s_cet(long val);
int vmx_host_write_ssp(long val);
int vmx_host_write_ia32_interrupt_ssp_table_addr(long val);


/*  */
long vmx_host_read_ia32_pat();
long vmx_host_read_ia32_efer();
long vmx_host_read_ia32_perf_global_ctrl();
long vmx_host_read_ia32_pkrs();

int vmx_host_write_ia32_pat(long val);
int vmx_host_write_ia32_efer(long val);
int vmx_host_write_ia32_perf_global_ctrl(long val);
int vmx_host_write_ia32_pkrs(long val);

long vmx_host_read_ia32_sysenter_cs();

int vmx_host_write_ia32_sysenter_cs(long val);

#endif
