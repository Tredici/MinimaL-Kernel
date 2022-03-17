
#include "vm64_control.h"
#include "vm64.h"

/**
 * See Intel Manual Vol. 3
 *  [Table B-1. Encoding for 16-Bit Control Fields (0000_00xx_xxxx_xxx0B)]
 *  Field Name                              Index       Encoding
 *  Virtual-processor identifier (VPID)     000000000B  00000000H
 *  Posted-interrupt notification vector    000000001B  00000002H
 *  EPTP index                              000000010B  00000004H
 */
#define VMX_VIRTUAL_PROCESSOR_IDENTIFIER            0x00000000
#define VMX_POSTED_INTERRUPT_NOTIFICATION_VECTOR    0x00000002
#define VMX_EPTP_INDEX                              0x00000004


short vmx_read_virtual_processor_identifier()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_VIRTUAL_PROCESSOR_IDENTIFIER);
    return ans;
}

void vmx_write_virtual_processor_identifier(short val)
{
    vmx_write_vmcs_field(VMX_VIRTUAL_PROCESSOR_IDENTIFIER, (long)val);
}


short vmx_read_posted_interrupt_notification_vector()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_POSTED_INTERRUPT_NOTIFICATION_VECTOR);
    return ans;
}

void vmx_write_posted_interrupt_notification_vector(short val)
{
    vmx_write_vmcs_field(VMX_POSTED_INTERRUPT_NOTIFICATION_VECTOR, (long)val);
}


short vmx_read_eptp_index()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_EPTP_INDEX);
    return ans;
}

void vmx_write_eptp_index(short val)
{
    vmx_write_vmcs_field(VMX_EPTP_INDEX, (long)val);
}

/**
 * See Intel Manual Vol. 3
 *  [Table B-8. Encodings for 32-Bit Control Fields (0100_00xx_xxxx_xxx0B)]
 *  Field Name                                      Index       Encoding
 *  Pin-based VM-execution controls                 000000000B  00004000H
 *  Primary processor-based VM-execution controls   000000001B  00004002H
 *  Exception bitmap                                000000010B  00004004H
 *  Page-fault error-code mask                      000000011B  00004006H
 *  Page-fault error-code match                     000000100B  00004008H
 *  CR3-target count                                000000101B  0000400AH
 *  VM-exit controls                                000000110B  0000400CH
 *  VM-exit MSR-store count                         000000111B  0000400EH
 *  VM-exit MSR-load count                          000001000B  00004010H
 *  VM-entry controls                               000001001B  00004012H
 *  VM-entry MSR-load count                         000001010B  00004014H
 *  VM-entry interruption-information field         000001011B  00004016H
 *  VM-entry exception error code                   000001100B  00004018H
 *  VM-entry instruction length                     000001101B  0000401AH
 *  TPR threshold                                   000001110B  0000401CH
 *  Secondary processor-based VM-execution controls 000001111b  0000401EH
 *  PLE_Gap                                         000010000b  00004020H
 *  PLE_Window                                      000010001b  00004022H
 */

#define VMX_PIN_BASED_VM_EXECUTION_CONTROLS                 0x00004000
#define VMX_PRIMARY_PROCESSOR_BASED_VM_EXECUTION_CONTROLS   0x00004002
#define VMX_EXCEPTION_BITMAP                                0x00004004
#define VMX_PAGE_FAULT_ERROR_CODE_MASK                      0x00004006
#define VMX_PAGE_FAULT_ERROR_CODE_MATCH                     0x00004008
#define VMX_CR3_TARGET_COUNT                                0x0000400A
#define VMX_VM_EXIT_CONTROLS                                0x0000400C
#define VMX_VM_EXIT_MSR_STORE_COUNT                         0x0000400E
#define VMX_VM_EXIT_MSR_LOAD_COUNT                          0x00004010
#define VMX_VM_ENTRY_CONTROLS                               0x00004012
#define VMX_VM_ENTRY_MSR_LOAD_COUNT                         0x00004014
#define VMX_VM_ENTRY_INTERRUPTION_INFORMATION_FIELD         0x00004016
#define VMX_VM_ENTRY_EXCEPTION_ERROR_CODE                   0x00004018
#define VMX_VM_ENTRY_INSTRUCTION_LENGTH                     0x0000401A
#define VMX_TPR_THRESHOLD                                   0x0000401C
#define VMX_SECONDARY_PROCESSOR_BASED_VM_EXECUTION_CONTROLS 0x0000401E
#define VMX_PLE_GAP                                         0x00004020
#define VMX_PLE_WINDOW                                      0x00004022

long vmx_read_pin_based_vm_execution_controls()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_PIN_BASED_VM_EXECUTION_CONTROLS);
    return ans;
}

void vmx_write_pin_based_vm_execution_controls(long val)
{
    vmx_write_vmcs_field(VMX_PIN_BASED_VM_EXECUTION_CONTROLS, val);
}


long vmx_read_primary_processor_based_vm_execution_controls()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_PRIMARY_PROCESSOR_BASED_VM_EXECUTION_CONTROLS);
    return ans;
}

void vmx_write_primary_processor_based_vm_execution_controls(long val)
{
    vmx_write_vmcs_field(VMX_PRIMARY_PROCESSOR_BASED_VM_EXECUTION_CONTROLS, val);
}


long vmx_read_exception_bitmap()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_EXCEPTION_BITMAP);
    return ans;
}

void vmx_write_exception_bitmap(long val)
{
    vmx_write_vmcs_field(VMX_EXCEPTION_BITMAP, val);
}


long vmx_read_page_fault_error_code_mask()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_PAGE_FAULT_ERROR_CODE_MASK);
    return ans;
}

void vmx_write_page_fault_error_code_mask(long val)
{
    vmx_write_vmcs_field(VMX_PAGE_FAULT_ERROR_CODE_MASK, val);
}


long vmx_read_page_fault_error_code_match()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_PAGE_FAULT_ERROR_CODE_MATCH);
    return ans;
}

void vmx_write_page_fault_error_code_match(long val)
{
    vmx_write_vmcs_field(VMX_PAGE_FAULT_ERROR_CODE_MATCH, val);
}


long vmx_read_cr3_target_count()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_CR3_TARGET_COUNT);
    return ans;
}

void vmx_write_cr3_target_count(long val)
{
    vmx_write_vmcs_field(VMX_CR3_TARGET_COUNT, val);
}


long vmx_read_vm_exit_controls()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_VM_EXIT_CONTROLS);
    return ans;
}

void vmx_write_vm_exit_controls(long val)
{
    vmx_write_vmcs_field(VMX_VM_EXIT_CONTROLS, val);
}


long vmx_read_vm_exit_msr_store_count()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_VM_EXIT_MSR_STORE_COUNT);
    return ans;
}

void vmx_write_vm_exit_msr_store_count(long val)
{
    vmx_write_vmcs_field(VMX_VM_EXIT_MSR_STORE_COUNT, val);
}


long vmx_read_vm_exit_msr_load_count()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_VM_EXIT_MSR_LOAD_COUNT);
    return ans;
}

void vmx_write_vm_exit_msr_load_count(long val)
{
    vmx_write_vmcs_field(VMX_VM_EXIT_MSR_LOAD_COUNT, val);
}


long vmx_read_vm_entry_controls()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_VM_ENTRY_CONTROLS);
    return ans;
}

void vmx_write_vm_entry_controls(long val)
{
    vmx_write_vmcs_field(VMX_VM_ENTRY_CONTROLS, val);
}


long vmx_read_vm_entry_msr_load_count()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_VM_ENTRY_MSR_LOAD_COUNT);
    return ans;
}

void vmx_write_vm_entry_msr_load_count(long val)
{
    vmx_write_vmcs_field(VMX_VM_ENTRY_MSR_LOAD_COUNT, val);
}


long vmx_read_vm_entry_interruption_information_field()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_VM_ENTRY_INTERRUPTION_INFORMATION_FIELD);
    return ans;
}

void vmx_write_vm_entry_interruption_information_field(long val)
{
    vmx_write_vmcs_field(VMX_VM_ENTRY_INTERRUPTION_INFORMATION_FIELD, val);
}


long vmx_read_vm_entry_exception_error_code()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_VM_ENTRY_EXCEPTION_ERROR_CODE);
    return ans;
}

void vmx_write_vm_entry_exception_error_code(long val)
{
    vmx_write_vmcs_field(VMX_VM_ENTRY_EXCEPTION_ERROR_CODE, val);
}


long vmx_read_vm_entry_instruction_length()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_VM_ENTRY_INSTRUCTION_LENGTH);
    return ans;
}

void vmx_write_vm_entry_instruction_length(long val)
{
    vmx_write_vmcs_field(VMX_VM_ENTRY_INSTRUCTION_LENGTH, val);
}


long vmx_read_tpr_threshold()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_TPR_THRESHOLD);
    return ans;
}

void vmx_write_tpr_threshold(long val)
{
    vmx_write_vmcs_field(VMX_TPR_THRESHOLD, val);
}


long vmx_read_secondary_processor_based_vm_execution_controls()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_SECONDARY_PROCESSOR_BASED_VM_EXECUTION_CONTROLS);
    return ans;
}

void vmx_write_secondary_processor_based_vm_execution_controls(long val)
{
    vmx_write_vmcs_field(VMX_SECONDARY_PROCESSOR_BASED_VM_EXECUTION_CONTROLS, val);
}


long vmx_read_ple_gap()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_PLE_GAP);
    return ans;
}

void vmx_write_ple_gap(long val)
{
    vmx_write_vmcs_field(VMX_PLE_GAP, val);
}


long vmx_read_ple_window()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_PLE_WINDOW);
    return ans;
}

void vmx_write_ple_window(long val)
{
    vmx_write_vmcs_field(VMX_PLE_WINDOW, val);
}


/**
 * Following fields are READ ONLY!!!!
 *
 * See Intel Manual Vol. 3
 *  [Table B-9. Encodings for 32-Bit Read-Only Data Fields (0100_01xx_xxxx_xxx0B)]
 *  Field Name                          Index       Encoding
 *  VM-instruction error                000000000B  00004400H
 *  Exit reason                         000000001B  00004402H
 *  VM-exit interruption information    000000010B  00004404H
 *  VM-exit interruption error code     000000011B  00004406H
 *  IDT-vectoring information field     000000100B  00004408H
 *  IDT-vectoring error code            000000101B  0000440AH
 *  VM-exit instruction length          000000110B  0000440CH
 *  VM-exit instruction information     000000111B  0000440EH
 */
#define VMX_VM_INSTRUCTION_ERROR                0x00004400
#define VMX_EXIT_REASON                         0x00004402
#define VMX_VM_EXIT_INTERRUPTION_INFORMATION    0x00004404
#define VMX_VM_EXIT_INTERRUPTION_ERROR_CODE     0x00004406
#define VMX_IDT_VECTORING_INFORMATION_FIELD     0x00004408
#define VMX_IDT_VECTORING_ERROR_CODE            0x0000440A
#define VMX_VM_EXIT_INSTRUCTION_LENGTH          0x0000440C
#define VMX_VM_EXIT_INSTRUCTION_INFORMATION     0x0000440E

int vmx_read_vm_instruction_error()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_VM_INSTRUCTION_ERROR);
    return ans;
}

int vmx_read_vm_exit_reason()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_EXIT_REASON);
    return ans;
}

int vmx_read_vm_exit_interruption_information()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_VM_EXIT_INTERRUPTION_INFORMATION);
    return ans;
}

int vmx_read_vm_exit_interruption_error_code()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_VM_EXIT_INTERRUPTION_ERROR_CODE);
    return ans;
}

int vmx_read_idt_vectoring_information_field()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_IDT_VECTORING_INFORMATION_FIELD);
    return ans;
}

int vmx_read_idt_vectoring_error_code()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_IDT_VECTORING_ERROR_CODE);
    return ans;
}

int vmx_read_vm_exit_instruction_length()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_VM_EXIT_INSTRUCTION_LENGTH);
    return ans;
}

int vmx_read_vm_exit_instruction_information()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_VM_EXIT_INSTRUCTION_INFORMATION);
    return ans;
}

/**
 * See Intel Manual Vol. 3
 *  [Table B-12. Encodings for Natural-Width Control Fields (0110_00xx_xxxx_xxx0B)]
 *  Field Name          Index       Encoding
 *  CR0 guest/host mask 000000000B  00006000H
 *  CR4 guest/host mask 000000001B  00006002H
 *  CR0 read shadow     000000010B  00006004H
 *  CR4 read shadow     000000011B  00006006H
 *  CR3-target value 0  000000100B  00006008H
 *  CR3-target value 1  000000101B  0000600AH
 *  CR3-target value 2  000000110B  0000600CH
 *  CR3-target value 3  000000111B  0000600EH
 */

#define VMX_CR0_GUEST_HOST_MASK 0x00006000
#define VMX_CR4_GUEST_HOST_MASK 0x00006002
#define VMX_CR0_READ_SHADOW     0x00006004
#define VMX_CR4_READ_SHADOW     0x00006006
#define VMX_CR3_TARGET_VALUE_0  0x00006008
#define VMX_CR3_TARGET_VALUE_1  0x0000600A
#define VMX_CR3_TARGET_VALUE_2  0x0000600C
#define VMX_CR3_TARGET_VALUE_3  0x0000600E

long vmx_read_cr0_guest_host_mask()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_CR0_GUEST_HOST_MASK);
    return ans;
}

void vmx_write_cr0_guest_host_mask(long val)
{
    vmx_write_vmcs_field(VMX_CR0_GUEST_HOST_MASK, val);
}


long vmx_read_cr4_guest_host_mask()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_CR4_GUEST_HOST_MASK);
    return ans;
}

void vmx_write_cr4_guest_host_mask(long val)
{
    vmx_write_vmcs_field(VMX_CR4_GUEST_HOST_MASK, val);
}


long vmx_read_cr0_read_shadow()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_CR0_READ_SHADOW);
    return ans;
}

void vmx_write_cr0_read_shadow(long val)
{
    vmx_write_vmcs_field(VMX_CR0_READ_SHADOW, val);
}


long vmx_read_cr4_read_shadow()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_CR4_READ_SHADOW);
    return ans;
}

void vmx_write_cr4_read_shadow(long val)
{
    vmx_write_vmcs_field(VMX_CR4_READ_SHADOW, val);
}


long vmx_read_cr3_target_value_0()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_CR3_TARGET_VALUE_0);
    return ans;
}

void vmx_write_cr3_target_value_0(long val)
{
    vmx_write_vmcs_field(VMX_CR3_TARGET_VALUE_0, val);
}


long vmx_read_cr3_target_value_1()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_CR3_TARGET_VALUE_1);
    return ans;
}

void vmx_write_cr3_target_value_1(long val)
{
    vmx_write_vmcs_field(VMX_CR3_TARGET_VALUE_1, val);
}


long vmx_read_cr3_target_value_2()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_CR3_TARGET_VALUE_2);
    return ans;
}

void vmx_write_cr3_target_value_2(long val)
{
    vmx_write_vmcs_field(VMX_CR3_TARGET_VALUE_2, val);
}


long vmx_read_cr3_target_value_3()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_CR3_TARGET_VALUE_3);
    return ans;
}

void vmx_write_cr3_target_value_3(long val)
{
    vmx_write_vmcs_field(VMX_CR3_TARGET_VALUE_3, val);
}

/**
 * See Intel Manual Vol. 3
 *  [Table B-13. Encodings for Natural-Width Read-Only Data Fields (0110_01xx_xxxx_xxx0B)]
 *  Field Name              Index       Encoding
 *  Exit qualification      000000000B  00006400H
 *  I/O RCX                 000000001B  00006402H
 *  I/O RSI                 000000010B  00006404H
 *  I/O RDI                 000000011B  00006406H
 *  I/O RIP                 000000100B  00006408H
 *  Guest-linear address    000000101B  0000640AH
 */
#define VMX_EXIT_QUALIFICATION      0x00006400
#define VMX_IO_RCX                  0x00006402
#define VMX_IO_RSI                  0x00006404
#define VMX_IO_RDI                  0x00006406
#define VMX_IO_RIP                  0x00006408
#define VMX_GUEST_LINEAR_ADDRESS    0x0000640A

long vmx_read_exit_qualification()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_EXIT_QUALIFICATION);
    return ans;
}


long vmx_read_io_rcx()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_IO_RCX);
    return ans;
}


long vmx_read_io_rsi()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_IO_RSI);
    return ans;
}


long vmx_read_io_rdi()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_IO_RDI);
    return ans;
}


long vmx_read_io_rip()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_IO_RIP);
    return ans;
}


long vmx_read_guest_linear_address()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_GUEST_LINEAR_ADDRESS);
    return ans;
}


/**
 * See Intel Manual Vol. 3
 *  [Table B-4. Encodings for 64-Bit Control Fields (0010_00xx_xxxx_xxxAb)]
 *  Field Name                                      Encoding
 *  Address of I/O bitmap A                         00002000H
 *  Address of I/O bitmap B                         00002002H
 *  Address of MSR bitmaps                          00002004H
 *  VM-exit MSR-store address                       00002006H
 *
 *  VM-exit MSR-load address                        00002008H
 *  VM-entry MSR-load address                       0000200AH
 *  Executive-VMCS pointer                          0000200CH
 *  PML address                                     0000200EH
 *  TSC offset                                      00002010H
 *  Virtual-APIC address                            00002012H
 *  APIC-access address                             00002014H
 *  Posted-interrupt descriptor address             00002016H
 *  VM-function controls                            00002018H
 *  EPT pointer (EPTP)                              0000201AH
 *  EOI-exit bitmap 0 (EOI_EXIT0)                   0000201CH
 *  EOI-exit bitmap 1 (EOI_EXIT1)                   0000201EH
 *  EOI-exit bitmap 2 (EOI_EXIT2)                   00002020H
 *  EOI-exit bitmap 3 (EOI_EXIT3)                   00002022H
 *  EPTP-list address                               00002024H
 *  VMREAD-bitmap address                           00002026H
 *  VMWRITE-bitmap address                          00002028H
 *  Virtualization-exception information address    0000202AH
 *  XSS-exiting bitmap                              0000202CH
 *
 *  ENCLS-exiting bitmap                            0000202EH
 *  Sub-page-permission-table pointer               00002030H
 *  TSC multiplier                                  00002032H
 *  Tertiary processor-based VM-execution controls  00002034H
 *  ENCLV-exiting bitmap                            00002036H
 */
/* 1st block */
#define VMX_ADDRESS_OF_IO_BITMAP_A      0x00002000
#define VMX_ADDRESS_OF_IO_BITMAP_B      0x00002002
#define VMX_ADDRESS_OF_MSR_BITMAPS      0x00002004
#define VMX_VM_EXIT_MSR_STORE_ADDRESS   0x00002006

long vmx_read_address_of_io_bitmap_a()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_ADDRESS_OF_IO_BITMAP_A);
    return ans;
}

void vmx_write_address_of_io_bitmap_a(long val)
{
    vmx_write_vmcs_field(VMX_ADDRESS_OF_IO_BITMAP_A, val);
}


long vmx_read_address_of_io_bitmap_b()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_ADDRESS_OF_IO_BITMAP_B);
    return ans;
}

void vmx_write_address_of_io_bitmap_b(long val)
{
    vmx_write_vmcs_field(VMX_ADDRESS_OF_IO_BITMAP_B, val);
}


long vmx_read_address_of_msr_bitmaps()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_ADDRESS_OF_MSR_BITMAPS);
    return ans;
}

void vmx_write_address_of_msr_bitmaps(long val)
{
    vmx_write_vmcs_field(VMX_ADDRESS_OF_MSR_BITMAPS, val);
}


long vmx_read_vm_exit_msr_store_address()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_VM_EXIT_MSR_STORE_ADDRESS);
    return ans;
}

void vmx_write_vm_exit_msr_store_address(long val)
{
    vmx_write_vmcs_field(VMX_VM_EXIT_MSR_STORE_ADDRESS, val);
}

/* 2nd block */
#define VMX_VM_EXIT_MSR_LOAD_ADDRESS                        0x00002008
#define VMX_VM_ENTRY_MSR_LOAD_ADDRESS                       0x0000200A
#define VMX_EXECUTIVE_VMCS_POINTER                          0x0000200C
#define VMX_PML_ADDRESS                                     0x0000200E
#define VMX_TSC_OFFSET                                      0x00002010
#define VMX_VIRTUAL_APIC_ADDRESS                            0x00002012
#define VMX_APIC_ACCESS_ADDRESS                             0x00002014
#define VMX_POSTED_INTERRUPT_DESCRIPTOR_ADDRESS             0x00002016
#define VMX_VM_FUNCTION_CONTROLS                            0x00002018
#define VMX_EPT_POINTER                                     0x0000201A
#define VMX_EOI_EXIT_BITMAP_0                               0x0000201C
#define VMX_EOI_EXIT_BITMAP_1                               0x0000201E
#define VMX_EOI_EXIT_BITMAP_2                               0x00002020
#define VMX_EOI_EXIT_BITMAP_3                               0x00002022
#define VMX_EPTP_LIST_ADDRESS                               0x00002024
#define VMX_VMREAD_BITMAP_ADDRESS                           0x00002026
#define VMX_VMWRITE_BITMAP_ADDRESS                          0x00002028
#define VMX_VIRTUALIZATION_EXCEPTION_INFORMATION_ADDRESS    0x0000202A
#define VMX_XSS_EXITING_BITMAP                              0x0000202C

long vmx_read_vm_exit_msr_load_address()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_VM_EXIT_MSR_LOAD_ADDRESS);
    return ans;
}

void vmx_write_vm_exit_msr_load_address(long val)
{
    vmx_write_vmcs_field(VMX_VM_EXIT_MSR_LOAD_ADDRESS, val);
}


long vmx_read_vm_entry_msr_load_address()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_VM_ENTRY_MSR_LOAD_ADDRESS);
    return ans;
}

void vmx_write_vm_entry_msr_load_address(long val)
{
    vmx_write_vmcs_field(VMX_VM_ENTRY_MSR_LOAD_ADDRESS, val);
}


long vmx_read_executive_vmcs_pointer()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_EXECUTIVE_VMCS_POINTER);
    return ans;
}

void vmx_write_executive_vmcs_pointer(long val)
{
    vmx_write_vmcs_field(VMX_EXECUTIVE_VMCS_POINTER, val);
}


long vmx_read_pml_address()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_PML_ADDRESS);
    return ans;
}

void vmx_write_pml_address(long val)
{
    vmx_write_vmcs_field(VMX_PML_ADDRESS, val);
}


long vmx_read_tsc_offset()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_TSC_OFFSET);
    return ans;
}

void vmx_write_tsc_offset(long val)
{
    vmx_write_vmcs_field(VMX_TSC_OFFSET, val);
}


long vmx_read_virtual_apic_address()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_VIRTUAL_APIC_ADDRESS);
    return ans;
}

void vmx_write_virtual_apic_address(long val)
{
    vmx_write_vmcs_field(VMX_VIRTUAL_APIC_ADDRESS, val);
}


long vmx_read_apic_access_address()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_APIC_ACCESS_ADDRESS);
    return ans;
}

void vmx_write_apic_access_address(long val)
{
    vmx_write_vmcs_field(VMX_APIC_ACCESS_ADDRESS, val);
}


long vmx_read_posted_interrupt_descriptor_address()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_POSTED_INTERRUPT_DESCRIPTOR_ADDRESS);
    return ans;
}

void vmx_write_posted_interrupt_descriptor_address(long val)
{
    vmx_write_vmcs_field(VMX_POSTED_INTERRUPT_DESCRIPTOR_ADDRESS, val);
}


long vmx_read_vm_function_controls()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_VM_FUNCTION_CONTROLS);
    return ans;
}

void vmx_write_vm_function_controls(long val)
{
    vmx_write_vmcs_field(VMX_VM_FUNCTION_CONTROLS, val);
}


long vmx_read_ept_pointer()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_EPT_POINTER);
    return ans;
}

void vmx_write_ept_pointer(long val)
{
    vmx_write_vmcs_field(VMX_EPT_POINTER, val);
}


long vmx_read_eoi_exit_bitmap_0()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_EOI_EXIT_BITMAP_0);
    return ans;
}

void vmx_write_eoi_exit_bitmap_0(long val)
{
    vmx_write_vmcs_field(VMX_EOI_EXIT_BITMAP_0, val);
}


long vmx_read_eoi_exit_bitmap_1()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_EOI_EXIT_BITMAP_1);
    return ans;
}

void vmx_write_eoi_exit_bitmap_1(long val)
{
    vmx_write_vmcs_field(VMX_EOI_EXIT_BITMAP_1, val);
}


long vmx_read_eoi_exit_bitmap_2()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_EOI_EXIT_BITMAP_2);
    return ans;
}

void vmx_write_eoi_exit_bitmap_2(long val)
{
    vmx_write_vmcs_field(VMX_EOI_EXIT_BITMAP_2, val);
}


long vmx_read_eoi_exit_bitmap_3()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_EOI_EXIT_BITMAP_3);
    return ans;
}

void vmx_write_eoi_exit_bitmap_3(long val)
{
    vmx_write_vmcs_field(VMX_EOI_EXIT_BITMAP_3, val);
}


long vmx_read_eptp_list_address()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_EPTP_LIST_ADDRESS);
    return ans;
}

void vmx_write_eptp_list_address(long val)
{
    vmx_write_vmcs_field(VMX_EPTP_LIST_ADDRESS, val);
}


long vmx_read_vmread_bitmap_address()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_VMREAD_BITMAP_ADDRESS);
    return ans;
}

void vmx_write_vmread_bitmap_address(long val)
{
    vmx_write_vmcs_field(VMX_VMREAD_BITMAP_ADDRESS, val);
}


long vmx_read_vmwrite_bitmap_address()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_VMWRITE_BITMAP_ADDRESS);
    return ans;
}

void vmx_write_vmwrite_bitmap_address(long val)
{
    vmx_write_vmcs_field(VMX_VMWRITE_BITMAP_ADDRESS, val);
}


long vmx_read_virtualization_exception_information_address()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_VIRTUALIZATION_EXCEPTION_INFORMATION_ADDRESS);
    return ans;
}

void vmx_write_virtualization_exception_information_address(long val)
{
    vmx_write_vmcs_field(VMX_VIRTUALIZATION_EXCEPTION_INFORMATION_ADDRESS, val);
}


long vmx_read_xss_exiting_bitmap()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_XSS_EXITING_BITMAP);
    return ans;
}

void vmx_write_xss_exiting_bitmap(long val)
{
    vmx_write_vmcs_field(VMX_XSS_EXITING_BITMAP, val);
}

/*************** 3rd block ***********/
#define VMX_ENCLS_EXITING_BITMAP                            0x0000202E
#define VMX_SUB_PAGE_PERMISSION_TABLE_POINTER               0x00002030
#define VMX_TSC_MULTIPLIER                                  0x00002032
#define VMX_TERTIARY_PROCESSOR_BASED_VM_EXECUTION_CONTROLS  0x00002034
#define VMX_ENCLV_EXITING_BITMAP                            0x00002036

long vmx_read_encls_exiting_bitmap()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_ENCLS_EXITING_BITMAP);
    return ans;
}

void vmx_write_encls_exiting_bitmap(long val)
{
    vmx_write_vmcs_field(VMX_ENCLS_EXITING_BITMAP, val);
}


long vmx_read_sub_page_permission_table_pointer()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_SUB_PAGE_PERMISSION_TABLE_POINTER);
    return ans;
}

void vmx_write_sub_page_permission_table_pointer(long val)
{
    vmx_write_vmcs_field(VMX_SUB_PAGE_PERMISSION_TABLE_POINTER, val);
}


long vmx_read_tsc_multiplier()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_TSC_MULTIPLIER);
    return ans;
}

void vmx_write_tsc_multiplier(long val)
{
    vmx_write_vmcs_field(VMX_TSC_MULTIPLIER, val);
}


long vmx_read_tertiary_processor_based_vm_execution_controls()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_TERTIARY_PROCESSOR_BASED_VM_EXECUTION_CONTROLS);
    return ans;
}

void vmx_write_tertiary_processor_based_vm_execution_controls(long val)
{
    vmx_write_vmcs_field(VMX_TERTIARY_PROCESSOR_BASED_VM_EXECUTION_CONTROLS, val);
}


long vmx_read_enclv_exiting_bitmap()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_ENCLV_EXITING_BITMAP);
    return ans;
}

void vmx_write_enclv_exiting_bitmap(long val)
{
    vmx_write_vmcs_field(VMX_ENCLV_EXITING_BITMAP, val);
}
