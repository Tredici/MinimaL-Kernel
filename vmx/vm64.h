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
unsigned long read_IA32_VMX_BASIC();
unsigned int read_vmcs_revision_identifier();
int vmx_clear_vmcs(void *vmcs_region);
int vmx_enable_vmcs_region(void *vmcs_region);
int vmx_get_vmcs_region_abort_status(void *vmcs_region);
int vmx_launch_current_vmcs();
int vmx_resume_current_vmcs();
int vmx_read_vmcs_field(long *data, long field);
int vmx_write_vmcs_field(long field, long data);
void *vmx_get_guest_stack();
void *vmx_get_guest_code();

/**
 * See Intel Mnaual Vol. 3
 *  [23.11.2 VMREAD, VMWRITE, and Encodings of VMCS Fields]
 *  access_type: 1 bit
 *  index:  9 bits
 *  type:   2 bits
 *  width:  2 bits
 */
enum vmx_vmcs_field_access_type
{
    VMX_VMCS_FAT_FULL = 0,
    VMX_VMCS_FAT_HIGH = 1,
};
enum vmx_vmcs_field_type
{
    VMX_VMCS_FT_CONTROL     = 0,
    VMX_VMCS_FT_VMEXIT_INFO = 1,
    VMX_VMCS_FT_GUEST_STATE = 2,
    VMX_VMCS_FT_HOST_STATE  = 3,
};
enum vmx_vmcs_field_width
{
    VMX_VMCS_FW_16B = 0,
    VMX_VMCS_FW_64B = 1,
    VMX_VMCS_FW_32B = 2,
    VMX_VMCS_FW_NATURALW = 3,
};
int vmx_vmcs_field_encoding(enum vmx_vmcs_field_access_type access, int index, enum vmx_vmcs_field_type type, enum vmx_vmcs_field_width width);

#endif
