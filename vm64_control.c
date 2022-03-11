
#include "vm64_control.h"
#include "vm64.h"


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



