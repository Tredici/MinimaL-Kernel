
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


/*
 * See Intel Manual Vol. 3
 *  [Table B-10. Encodings for 32-Bit Guest-State Fields (0100_10xx_xxxx_xxx0B)]
 *  Field Name          Index       Encoding
 *  Guest ES limit      000000000B  00004800H
 *  Guest CS limit      000000001B  00004802H
 *  Guest SS limit      000000010B  00004804H
 *  Guest DS limit      000000011B  00004806H
 *  Guest FS limit      000000100B  00004808H
 *  Guest GS limit      000000101B  0000480AH
 *  Guest LDTR limit    000000110B  0000480CH
 *  Guest TR limit      000000111B  0000480EH
 */
#define GUEST_ES_LIMIT      0x00004800
#define GUEST_CS_LIMIT      0x00004802
#define GUEST_SS_LIMIT      0x00004804
#define GUEST_DS_LIMIT      0x00004806
#define GUEST_FS_LIMIT      0x00004808
#define GUEST_GS_LIMIT      0x0000480A
#define GUEST_LDTR_LIMIT    0x0000480C
#define GUEST_TR_LIMIT      0x0000480E

int vmx_guest_read_cs_limit()
{
    long ans = 0;
    vmx_read_vmcs_field(&ans, GUEST_CS_LIMIT);
    return ans;
}

void vmx_guest_write_cs_limit(int ans)
{
    vmx_write_vmcs_field(GUEST_CS_LIMIT, ans);
}


int vmx_guest_read_ds_limit()
{
    long ans = 0;
    vmx_read_vmcs_field(&ans, GUEST_DS_LIMIT);
    return ans;
}

void vmx_guest_write_ds_limit(int ans)
{
    vmx_write_vmcs_field(GUEST_DS_LIMIT, ans);
}


int vmx_guest_read_ss_limit()
{
    long ans = 0;
    vmx_read_vmcs_field(&ans, GUEST_SS_LIMIT);
    return ans;
}

void vmx_guest_write_ss_limit(int ans)
{
    vmx_write_vmcs_field(GUEST_SS_LIMIT, ans);
}


int vmx_guest_read_es_limit()
{
    long ans = 0;
    vmx_read_vmcs_field(&ans, GUEST_ES_LIMIT);
    return ans;
}

void vmx_guest_write_es_limit(int ans)
{
    vmx_write_vmcs_field(GUEST_ES_LIMIT, ans);
}


int vmx_guest_read_fs_limit()
{
    long ans = 0;
    vmx_read_vmcs_field(&ans, GUEST_FS_LIMIT);
    return ans;
}

void vmx_guest_write_fs_limit(int ans)
{
    vmx_write_vmcs_field(GUEST_FS_LIMIT, ans);
}


int vmx_guest_read_gs_limit()
{
    long ans = 0;
    vmx_read_vmcs_field(&ans, GUEST_GS_LIMIT);
    return ans;
}

void vmx_guest_write_gs_limit(int ans)
{
    vmx_write_vmcs_field(GUEST_GS_LIMIT, ans);
}


/**
 * Following functions are used to manage control
 * and segment registers
 *
 * See Intel Manual Vol. 3
 *  [B.4.3 Natural-Width Guest-State Fields]
 *  [Table B-14. Encodings for Natural-Width Guest-State Fields (0110_10xx_xxxx_xxx0B)]
 *  Field Name          Index       Encoding
 *  Guest CR0           000000000B  00006800H
 *  Guest CR3           000000001B  00006802H
 *  Guest CR4           000000010B  00006804H
 *  Guest ES base       000000011B  00006806H
 *  Guest CS base       000000100B  00006808H
 *  Guest SS base       000000101B  0000680AH
 *  Guest DS base       000000110B  0000680CH
 *  Guest FS base       000000111B  0000680EH
 *  Guest GS base       000001000B  00006810H
 */
#define GUEST_CR0           0x00006800
#define GUEST_CR3           0x00006802
#define GUEST_CR4           0x00006804
#define GUEST_ES_BASE       0x00006806
#define GUEST_CS_BASE       0x00006808
#define GUEST_SS_BASE       0x0000680A
#define GUEST_DS_BASE       0x0000680C
#define GUEST_FS_BASE       0x0000680E
#define GUEST_GS_BASE       0x00006810

long vmx_guest_read_cr0()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_CR0);
    return ans;
}

void vmx_guest_write_cr0(long val)
{
    vmx_write_vmcs_field(GUEST_CR0, val);
}


long vmx_guest_read_cr3()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_CR3);
    return ans;
}

void vmx_guest_write_cr3(long val)
{
    vmx_write_vmcs_field(GUEST_CR3, val);
}


long vmx_guest_read_cr4()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_CR4);
    return ans;
}

void vmx_guest_write_cr4(long val)
{
    vmx_write_vmcs_field(GUEST_CR4, val);
}


long vmx_guest_read_es_base()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_ES_BASE);
    return ans;
}

void vmx_guest_write_es_base(long val)
{
    vmx_write_vmcs_field(GUEST_ES_BASE, val);
}


long vmx_guest_read_cs_base()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_CS_BASE);
    return ans;
}

void vmx_guest_write_cs_base(long val)
{
    vmx_write_vmcs_field(GUEST_CS_BASE, val);
}


long vmx_guest_read_ss_base()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_SS_BASE);
    return ans;
}

void vmx_guest_write_ss_base(long val)
{
    vmx_write_vmcs_field(GUEST_SS_BASE, val);
}


long vmx_guest_read_ds_base()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_DS_BASE);
    return ans;
}

void vmx_guest_write_ds_base(long val)
{
    vmx_write_vmcs_field(GUEST_DS_BASE, val);
}


long vmx_guest_read_fs_base()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_FS_BASE);
    return ans;
}

void vmx_guest_write_fs_base(long val)
{
    vmx_write_vmcs_field(GUEST_FS_BASE, val);
}


long vmx_guest_read_gs_base()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_GS_BASE);
    return ans;
}

void vmx_guest_write_gs_base(long val)
{
    vmx_write_vmcs_field(GUEST_GS_BASE, val);
}
