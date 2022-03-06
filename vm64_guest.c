
#include "vm64_guest.h"
#include "vm64.h"

/**
 * See Intel Manual Vol. 3
 *  [Table B-2. Encodings for 16-Bit Guest-State Fields (0000_10xx_xxxx_xxx0B)]
 *  Field Name          Index       Encoding
 *  Guest ES selector   000000000B  00000800H
 *  Guest CS selector   000000001B  00000802H
 *  Guest SS selector   000000010B  00000804H
 *  Guest DS selector   000000011B  00000806H
 *  Guest FS selector   000000100B  00000808H
 *  Guest GS selector   000000101B  0000080AH
 */
#define GUEST_CS_SELECTOR 0X00000802
#define GUEST_SS_SELECTOR 0X00000804
#define GUEST_DS_SELECTOR 0X00000806
#define GUEST_ES_SELECTOR 0X00000800
#define GUEST_FS_SELECTOR 0X00000808
#define GUEST_GS_SELECTOR 0X0000080A

short vmx_guest_read_cs()
{
    long ans = 0;
    vmx_read_vmcs_field(&ans, GUEST_CS_SELECTOR);
    return ans;
}

void vmx_guest_write_cs(short val)
{
    vmx_write_vmcs_field(GUEST_CS_SELECTOR, val);
}


short vmx_guest_read_ds()
{
    long ans = 0;
    vmx_read_vmcs_field(&ans, GUEST_SS_SELECTOR);
    return ans;
}

void vmx_guest_write_ds(short val)
{
    vmx_write_vmcs_field(GUEST_SS_SELECTOR, val);
}


short vmx_guest_read_ss()
{
    long ans = 0;
    vmx_read_vmcs_field(&ans, GUEST_DS_SELECTOR);
    return ans;
}

void vmx_guest_write_ss(short val)
{
    vmx_write_vmcs_field(GUEST_DS_SELECTOR, val);
}


short vmx_guest_read_es()
{
    long ans = 0;
    vmx_read_vmcs_field(&ans, GUEST_ES_SELECTOR);
    return ans;
}

void vmx_guest_write_es(short val)
{
    vmx_write_vmcs_field(GUEST_ES_SELECTOR, val);
}


short vmx_guest_read_fs()
{
    long ans = 0;
    vmx_read_vmcs_field(&ans, GUEST_FS_SELECTOR);
    return ans;
}

void vmx_guest_write_fs(short val)
{
    vmx_write_vmcs_field(GUEST_FS_SELECTOR, val);
}


short vmx_guest_read_gs()
{
    long ans = 0;
    vmx_read_vmcs_field(&ans, GUEST_GS_SELECTOR);
    return ans;
}
void vmx_guestw_itrd_gs(short val)
{
    vmx_write_vmcs_field(GUEST_GS_SELECTOR, val);
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
#define GUEST_VM_INSTRUCTION_ERROR                0x00004400
#define GUEST_EXIT_REASON                         0x00004402
#define GUEST_VM_EXIT_INTERRUPTION_INFORMATION    0x00004404
#define GUEST_VM_EXIT_INTERRUPTION_ERROR_CODE     0x00004406
#define GUEST_IDT_VECTORING_INFORMATION_FIELD     0x00004408
#define GUEST_IDT_VECTORING_ERROR_CODE            0x0000440A
#define GUEST_VM_EXIT_INSTRUCTION_LENGTH          0x0000440C
#define GUEST_VM_EXIT_INSTRUCTION_INFORMATION     0x0000440E

int vmx_guest_read_vm_instruction_error()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_VM_INSTRUCTION_ERROR);
    return ans;
}

int vmx_guest_read_vm_exit_reason()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_EXIT_REASON);
    return ans;
}

int vmx_guest_read_vm_exit_interruption_information()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_VM_EXIT_INTERRUPTION_INFORMATION);
    return ans;
}

int vmx_guest_read_vm_exit_interruption_error_code()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_VM_EXIT_INTERRUPTION_ERROR_CODE);
    return ans;
}

int vmx_guest_read_idt_vectoring_information_field()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_IDT_VECTORING_INFORMATION_FIELD);
    return ans;
}

int vmx_guest_read_guest_idt_vectoring_error_code()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_IDT_VECTORING_ERROR_CODE);
    return ans;
}

int vmx_guest_read_guest_vm_exit_instruction_length()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_VM_EXIT_INSTRUCTION_LENGTH);
    return ans;
}

int vmx_guest_read_guest_vm_exit_instruction_information()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_VM_EXIT_INSTRUCTION_INFORMATION);
    return ans;
}

