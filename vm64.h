/**
 * @file vm64.h
 * @author your name (you@domain.com)
 * @brief Exposes C functions to handle VMX extension.
 * (Putting printf in C code is easier than in assembler.)
 *
 * @version 0.1
 * @date 2022-02-25
 *
 * @copyright Copyright (c) 2022
 */

#ifndef VM64
#define VM64

int start_vm();
void enable_vmx();
int enter_vmx(void *vmx_region);
int vmxoff();
void set_cr4_vmxe();
int check_vm_support();
void *get_vmx_region();
void *get_vmcs_region();
void *get_current_vmcs();
void init_vm64_data_structures();
unsigned int read_IA32_VMX_BASIC();
unsigned int read_vmcs_revision_identifier();
int vmx_clear_vmcs(void *vmcs_region);
int vmx_enable_vmcs_region(void *vmcs_region);
int vmx_get_vmcs_region_abort_status(void *vmcs_region);

#endif
