
#ifndef VM64_GUEST
#define VM64_GUEST

short vmx_guest_read_cs();
short vmx_guest_read_ds();
short vmx_guest_read_ss();
short vmx_guest_read_es();
short vmx_guest_read_fs();
short vmx_guest_read_gs();

void vmx_guest_write_cs(short val);
void vmx_guest_write_ds(short val);
void vmx_guest_write_ss(short val);
void vmx_guest_write_es(short val);
void vmx_guest_write_fs(short val);
void vmx_guestw_itrd_gs(short val);

int vmx_guest_read_cs_limit();
int vmx_guest_read_ds_limit();
int vmx_guest_read_ss_limit();
int vmx_guest_read_es_limit();
int vmx_guest_read_fs_limit();
int vmx_guest_read_gs_limit();

void vmx_guest_write_cs_limit(int ans);
void vmx_guest_write_ds_limit(int ans);
void vmx_guest_write_ss_limit(int ans);
void vmx_guest_write_es_limit(int ans);
void vmx_guest_write_fs_limit(int ans);
void vmx_guest_write_gs_limit(int ans);

int vmx_guest_read_vm_instruction_error();
int vmx_guest_read_vm_exit_reason();
int vmx_guest_read_vm_exit_interruption_information();
int vmx_guest_read_vm_exit_interruption_error_code();
int vmx_guest_read_idt_vectoring_information_field();
int vmx_guest_read_guest_idt_vectoring_error_code();
int vmx_guest_read_guest_vm_exit_instruction_length();
int vmx_guest_read_guest_vm_exit_instruction_information();

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

#endif
