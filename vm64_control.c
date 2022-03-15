
#include "vm64_control.h"
#include "vm64.h"

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


