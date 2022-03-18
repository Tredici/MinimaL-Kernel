
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
 *
 * Guest LDTR selector      000000110B  0000080CH
 * Guest TR selector        000000111B  0000080EH
 * Guest interrupt status   000001000B  00000810H
 * PML index                000001001B  00000812H
 */
#define GUEST_CS_SELECTOR 0X00000802
#define GUEST_SS_SELECTOR 0X00000804
#define GUEST_DS_SELECTOR 0X00000806
#define GUEST_ES_SELECTOR 0X00000800
#define GUEST_FS_SELECTOR 0X00000808
#define GUEST_GS_SELECTOR 0X0000080A

#define VMX_GUEST_LDTR_SELECTOR      0x0000080C
#define VMX_GUEST_TR_SELECTOR        0x0000080E
#define VMX_GUEST_INTERRUPT_STATUS   0x00000810
#define VMX_PML_INDEX                0x00000812

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

void vmx_guest_write_gs(short val)
{
    vmx_write_vmcs_field(GUEST_GS_SELECTOR, val);
}


short vmx_guest_read_ldtr_selector()
{
    long ans = 0;
    vmx_read_vmcs_field(&ans, VMX_GUEST_LDTR_SELECTOR);
    return ans;
}

void vmx_guest_write_ldtr_selector(short val)
{
    vmx_write_vmcs_field(VMX_GUEST_LDTR_SELECTOR, val);
}


short vmx_guest_read_tr_selector()
{
    long ans = 0;
    vmx_read_vmcs_field(&ans, VMX_GUEST_TR_SELECTOR);
    return ans;
}

void vmx_guest_write_tr_selector(short val)
{
    vmx_write_vmcs_field(VMX_GUEST_TR_SELECTOR, val);
}


short vmx_guest_read_interrupt_status()
{
    long ans = 0;
    vmx_read_vmcs_field(&ans, VMX_GUEST_INTERRUPT_STATUS);
    return ans;
}

void vmx_guest_write_interrupt_status(short val)
{
    vmx_write_vmcs_field(VMX_GUEST_INTERRUPT_STATUS, val);
}


short vmx_guest_read_pml_index()
{
    long ans = 0;
    vmx_read_vmcs_field(&ans, VMX_PML_INDEX);
    return ans;
}

void vmx_guest_write_pml_index(short val)
{
    vmx_write_vmcs_field(VMX_PML_INDEX, val);
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


/**
 * Following functions are used to manage control
 * and segment registers
 *
 * See Intel Manual Vol. 3
 *  [B.4.3 Natural-Width Guest-State Fields]
 *  [Table B-14. Encodings for Natural-Width Guest-State Fields (0110_10xx_xxxx_xxx0B)]
 *  Field Name          Index       Encoding
 *  Guest LDTR base     000001001B  00006812H
 *  Guest TR base       000001010B  00006814H
 *  Guest GDTR base     000001011B  00006816H
 *  Guest IDTR base     000001100B  00006818H
 *  Guest DR7           000001101B  0000681AH
 *  Guest RSP           000001110B  0000681CH
 *  Guest RIP           000001111B  0000681EH
 *  Guest RFLAGS        000010000B  00006820H
 */
#define GUEST_LDTR_BASE     0x00006812
#define GUEST_TR_BASE       0x00006814
#define GUEST_GDTR_BASE     0x00006816
#define GUEST_IDTR_BASE     0x00006818
#define GUEST_DR7           0x0000681A
#define GUEST_RSP           0x0000681C
#define GUEST_RIP           0x0000681E
#define GUEST_RFLAGS        0x00006820

long vmx_guest_read_ldtr_base()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_LDTR_BASE);
    return ans;
}

void vmx_guest_write_ldtr_base(long val)
{
    vmx_write_vmcs_field(GUEST_LDTR_BASE, val);
}


long vmx_guest_read_tr_base()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_TR_BASE);
    return ans;
}

void vmx_guest_write_tr_base(long val)
{
    vmx_write_vmcs_field(GUEST_TR_BASE, val);
}


long vmx_guest_read_gdtr_base()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_GDTR_BASE);
    return ans;
}

void vmx_guest_write_gdtr_base(long val)
{
    vmx_write_vmcs_field(GUEST_GDTR_BASE, val);
}


long vmx_guest_read_idtr_base()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_IDTR_BASE);
    return ans;
}

void vmx_guest_write_idtr_base(long val)
{
    vmx_write_vmcs_field(GUEST_IDTR_BASE, val);
}


long vmx_guest_read_dr7()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_DR7);
    return ans;
}

void vmx_guest_write_dr7(long val)
{
    vmx_write_vmcs_field(GUEST_DR7, val);
}


long vmx_guest_read_rsp()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_RSP);
    return ans;
}

void vmx_guest_write_rsp(long val)
{
    vmx_write_vmcs_field(GUEST_RSP, val);
}


long vmx_guest_read_rip()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_RIP);
    return ans;
}

void vmx_guest_write_rip(long val)
{
    vmx_write_vmcs_field(GUEST_RIP, val);
}


long vmx_guest_read_rflags()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_RFLAGS);
    return ans;
}

void vmx_guest_write_rflags(long val)
{
    vmx_write_vmcs_field(GUEST_RFLAGS, val);
}

/**
 * See Intel Manual Vol. 3
 *  [Table B-6. Encodings for 64-Bit Guest-State Fields (0010_10xx_xxxx_xxxAb)]
 *  Field Name                  Encoding
 *  VMCS link pointer           00002800H
 *  Guest IA32_DEBUGCTL         00002802H
 *  Guest IA32_PAT              00002804H
 *  Guest IA32_EFER             00002806H
 *  Guest IA32_PERF_GLOBAL_CTRL 00002808H
 *  Guest PDPTE0                0000280AH
 *  Guest PDPTE1                0000280CH
 *  Guest PDPTE2                0000280EH
 *  Guest PDPTE3                00002810H
 *  Guest IA32_BNDCFGS          00002812H
 *  Guest IA32_RTIT_CTL         00002814H
 *  Guest IA32_PKRS             00002818H
 */
/**
 * See Intel Manual Vol. 3
 *  [23.1 OVERVIEW]
 *  The VMCS link pointer field in the current
 *  VMCS (see Section 23.4.2) is itself the
 *  address of a VMCS. If VM entry is performed
 *  successfully with the 1-setting of the “VMCS
 *  shadowing” VM-execution control, the VMCS
 *  referenced by the VMCS link pointer field
 *  becomes active on the logical processor.
 *  The identity of the current VMCS does not
 *  change.
 *
 * See Intel Manual Vol. 3
 *  [23.4.2 Guest Non-Register State]
 *  VMCS link pointer (64 bits). If the “VMCS
 *  shadowing” VM-execution control is 1, the
 *  VMREAD and VMWRITE instructions access the
 *  VMCS referenced by this pointer (see Section
 *  23.10). Otherwise, software should set this
 *  field to FFFFFFFF_FFFFFFFFH to avoid VM-entry
 *  failures (see Section 25.3.1.5).
 */
#define VMCS_LINK_POINTER           0x00002800
#define GUEST_IA32_DEBUGCTL         0x00002802
#define GUEST_IA32_PAT              0x00002804
#define GUEST_IA32_EFER             0x00002806
#define GUEST_IA32_PERF_GLOBAL_CTRL 0x00002808
#define GUEST_PDPTE0                0x0000280A
#define GUEST_PDPTE1                0x0000280C
#define GUEST_PDPTE2                0x0000280E
#define GUEST_PDPTE3                0x00002810
#define GUEST_IA32_BNDCFGS          0x00002812
#define GUEST_IA32_RTIT_CTL         0x00002814
#define GUEST_IA32_PKRS             0x00002818

long vmx_guest_read_vmcs_link_pointer()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMCS_LINK_POINTER);
    return ans;
}

void vmx_guest_write_vmcs_link_pointer(long val)
{
    vmx_write_vmcs_field(VMCS_LINK_POINTER, val);
}


long vmx_guest_read_ia32_debugctl()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_IA32_DEBUGCTL);
    return ans;
}

void vmx_guest_write_ia32_debugctl(long val)
{
    vmx_write_vmcs_field(GUEST_IA32_DEBUGCTL, val);
}


long vmx_guest_read_ia32_pat()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_IA32_PAT);
    return ans;
}

void vmx_guest_write_ia32_pat(long val)
{
    vmx_write_vmcs_field(GUEST_IA32_PAT, val);
}


long vmx_guest_read_ia32_efer()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_IA32_EFER);
    return ans;
}

void vmx_guest_write_ia32_efer(long val)
{
    vmx_write_vmcs_field(GUEST_IA32_EFER, val);
}


long vmx_guest_read_ia32_perf_global_ctrl()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_IA32_PERF_GLOBAL_CTRL);
    return ans;
}

void vmx_guest_write_ia32_perf_global_ctrl(long val)
{
    vmx_write_vmcs_field(GUEST_IA32_PERF_GLOBAL_CTRL, val);
}


long vmx_guest_read_pdpte0()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_PDPTE0);
    return ans;
}

void vmx_guest_write_pdpte0(long val)
{
    vmx_write_vmcs_field(GUEST_PDPTE0, val);
}


long vmx_guest_read_pdpte1()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_PDPTE1);
    return ans;
}

void vmx_guest_write_pdpte1(long val)
{
    vmx_write_vmcs_field(GUEST_PDPTE1, val);
}


long vmx_guest_read_pdpte2()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_PDPTE2);
    return ans;
}

void vmx_guest_write_pdpte2(long val)
{
    vmx_write_vmcs_field(GUEST_PDPTE2, val);
}


long vmx_guest_read_pdpte3()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_PDPTE3);
    return ans;
}

void vmx_guest_write_pdpte3(long val)
{
    vmx_write_vmcs_field(GUEST_PDPTE3, val);
}


long vmx_guest_read_ia32_bndcfgs()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_IA32_BNDCFGS);
    return ans;
}

void vmx_guest_write_ia32_bndcfgs(long val)
{
    vmx_write_vmcs_field(GUEST_IA32_BNDCFGS, val);
}


long vmx_guest_read_ia32_rtit_ctl()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_IA32_RTIT_CTL);
    return ans;
}

void vmx_guest_write_ia32_rtit_ctl(long val)
{
    vmx_write_vmcs_field(GUEST_IA32_RTIT_CTL, val);
}


long vmx_guest_read_ia32_pkrs()
{
    long ans;
    vmx_read_vmcs_field(&ans, GUEST_IA32_PKRS);
    return ans;
}

void vmx_guest_write_ia32_pkrs(long val)
{
    vmx_write_vmcs_field(GUEST_IA32_PKRS, val);
}

