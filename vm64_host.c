#include "vm64_host.h"
#include "vm64.h"

/**
 * See Intel Manual Vol. 3
 *  [Table B-3. Encodings for 16-Bit Host-State Fields (0000_11xx_xxxx_xxx0B)]
 *  Field Name          Index       Encoding
 *  Host ES selector    000000000B  00000C00H
 *  Host CS selector    000000001B  00000C02H
 *  Host SS selector    000000010B  00000C04H
 *  Host DS selector    000000011B  00000C06H
 *  Host FS selector    000000100B  00000C08H
 *  Host GS selector    000000101B  00000C0AH
 *  Host TR selector    000000110B  00000C0CH
 */
#define HOST_ES_SELECTOR 0x00000C00
#define HOST_CS_SELECTOR 0x00000C02
#define HOST_SS_SELECTOR 0x00000C04
#define HOST_DS_SELECTOR 0x00000C06
#define HOST_FS_SELECTOR 0x00000C08
#define HOST_GS_SELECTOR 0x00000C0A
#define HOST_TR_SELECTOR 0x00000C0C


short vmx_host_read_cs()
{
    long ans = 0;
    vmx_read_vmcs_field(&ans, HOST_CS_SELECTOR);
    return ans;
}

int vmx_host_write_cs(short val)
{
    return vmx_write_vmcs_field(HOST_CS_SELECTOR, val);
}


short vmx_host_read_ds()
{
    long ans = 0;
    vmx_read_vmcs_field(&ans, HOST_SS_SELECTOR);
    return ans;
}

int vmx_host_write_ds(short val)
{
    return vmx_write_vmcs_field(HOST_SS_SELECTOR, val);
}


short vmx_host_read_ss()
{
    long ans = 0;
    vmx_read_vmcs_field(&ans, HOST_DS_SELECTOR);
    return ans;
}

int vmx_host_write_ss(short val)
{
    return vmx_write_vmcs_field(HOST_DS_SELECTOR, val);
}


short vmx_host_read_es()
{
    long ans = 0;
    vmx_read_vmcs_field(&ans, HOST_ES_SELECTOR);
    return ans;
}

int vmx_host_write_es(short val)
{
    return vmx_write_vmcs_field(HOST_ES_SELECTOR, val);
}


short vmx_host_read_fs()
{
    long ans = 0;
    vmx_read_vmcs_field(&ans, HOST_FS_SELECTOR);
    return ans;
}

int vmx_host_write_fs(short val)
{
    return vmx_write_vmcs_field(HOST_FS_SELECTOR, val);
}


short vmx_host_read_gs()
{
    long ans = 0;
    vmx_read_vmcs_field(&ans, HOST_GS_SELECTOR);
    return ans;
}

int vmx_host_write_gs(short val)
{
    return vmx_write_vmcs_field(HOST_GS_SELECTOR, val);
}


short vmx_host_read_tr()
{
    long ans = 0;
    vmx_read_vmcs_field(&ans, HOST_TR_SELECTOR);
    return ans;
}

int vmx_host_write_tr(short val)
{
    return vmx_write_vmcs_field(HOST_TR_SELECTOR, val);
}

/**
 * See Intel Manual Vol. 3
 *  [Table B-15. Encodings for Natural-Width Host-State Fields (0110_11xx_xxxx_xxx0B)]
 *  Field Name              Index       Encoding
 *  Host CR0                000000000B  00006C00H
 *  Host CR3                000000001B  00006C02H
 *  Host CR4                000000010B  00006C04H
 *  Host FS base            000000011B  00006C06H
 *  Host GS base            000000100B  00006C08H
 *  Host TR base            000000101B  00006C0AH
 *  Host GDTR base          000000110B  00006C0CH
 *  Host IDTR base          000000111B  00006C0EH
 *  Host IA32_SYSENTER_ESP  000001000B  00006C10H
 *  Host IA32_SYSENTER_EIP  000001001B  00006C12H
 *  Host RSP                000001010B  00006C14H
 *  Host RIP                000001011B  00006C16H
 *  Host IA32_S_CET         000001100B  00006C18H
 *
 *  Host SSP                            000001101B 00006C1AH
 *  Host IA32_INTERRUPT_SSP_TABLE_ADDR  000001110B 00006C1CH
 */
#define HOST_CR0                0x00006C00
#define HOST_CR3                0x00006C02
#define HOST_CR4                0x00006C04
#define HOST_FS_BASE            0x00006C06
#define HOST_GS_BASE            0x00006C08
#define HOST_TR_BASE            0x00006C0A
#define HOST_GDTR_BASE          0x00006C0C
#define HOST_IDTR_BASE          0x00006C0E
#define HOST_IA32_SYSENTER_ESP  0x00006C10
#define HOST_IA32_SYSENTER_EIP  0x00006C12
#define HOST_RSP                0x00006C14
#define HOST_RIP                0x00006C16
#define HOST_IA32_S_CET         0x00006C18

#define VMX_HOST_SSP                            0x00006C1A
#define VMX_HOST_IA32_INTERRUPT_SSP_TABLE_ADDR  0x00006C1C

long vmx_host_read_cr0()
{
    long ans;
    vmx_read_vmcs_field(&ans, HOST_CR0);
    return ans;
}

int vmx_host_write_cr0(long val)
{
    return vmx_write_vmcs_field(HOST_CR0, val);
}


long vmx_host_read_cr3()
{
    long ans;
    vmx_read_vmcs_field(&ans, HOST_CR3);
    return ans;
}

int vmx_host_write_cr3(long val)
{
    return vmx_write_vmcs_field(HOST_CR3, val);
}


long vmx_host_read_cr4()
{
    long ans;
    vmx_read_vmcs_field(&ans, HOST_CR4);
    return ans;
}

int vmx_host_write_cr4(long val)
{
    return vmx_write_vmcs_field(HOST_CR4, val);
}


long vmx_host_read_fs_base()
{
    long ans;
    vmx_read_vmcs_field(&ans, HOST_FS_BASE);
    return ans;
}

int vmx_host_write_fs_base(long val)
{
    return vmx_write_vmcs_field(HOST_FS_BASE, val);
}


long vmx_host_read_gs_base()
{
    long ans;
    vmx_read_vmcs_field(&ans, HOST_GS_BASE);
    return ans;
}

int vmx_host_write_gs_base(long val)
{
    return vmx_write_vmcs_field(HOST_GS_BASE, val);
}


long vmx_host_read_tr_base()
{
    long ans;
    vmx_read_vmcs_field(&ans, HOST_TR_BASE);
    return ans;
}

int vmx_host_write_tr_base(long val)
{
    return vmx_write_vmcs_field(HOST_TR_BASE, val);
}


long vmx_host_read_gdtr_base()
{
    long ans;
    vmx_read_vmcs_field(&ans, HOST_GDTR_BASE);
    return ans;
}

int vmx_host_write_gdtr_base(long val)
{
    return vmx_write_vmcs_field(HOST_GDTR_BASE, val);
}


long vmx_host_read_idtr_base()
{
    long ans;
    vmx_read_vmcs_field(&ans, HOST_IDTR_BASE);
    return ans;
}

int vmx_host_write_idtr_base(long val)
{
    return vmx_write_vmcs_field(HOST_IDTR_BASE, val);
}


long vmx_host_read_ia32_sysenter_esp()
{
    long ans;
    vmx_read_vmcs_field(&ans, HOST_IA32_SYSENTER_ESP);
    return ans;
}

int vmx_host_write_ia32_sysenter_esp(long val)
{
    return vmx_write_vmcs_field(HOST_IA32_SYSENTER_ESP, val);
}


long vmx_host_read_ia32_sysenter_eip()
{
    long ans;
    vmx_read_vmcs_field(&ans, HOST_IA32_SYSENTER_EIP);
    return ans;
}

int vmx_host_write_ia32_sysenter_eip(long val)
{
    return vmx_write_vmcs_field(HOST_IA32_SYSENTER_EIP, val);
}


long vmx_host_read_rsp()
{
    long ans;
    vmx_read_vmcs_field(&ans, HOST_RSP);
    return ans;
}

int vmx_host_write_rsp(long val)
{
    return vmx_write_vmcs_field(HOST_RSP, val);
}



long vmx_host_read_rip()
{
    long ans;
    vmx_read_vmcs_field(&ans, HOST_RIP);
    return ans;
}

int vmx_host_write_rip(long val)
{
    return vmx_write_vmcs_field(HOST_RIP, val);
}


long vmx_host_read_ia32_s_cet()
{
    long ans;
    vmx_read_vmcs_field(&ans, HOST_IA32_S_CET);
    return ans;
}

int vmx_host_write_ia32_s_cet(long val)
{
    return vmx_write_vmcs_field(HOST_IA32_S_CET, val);
}


long vmx_host_read_ssp()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_HOST_SSP);
    return ans;
}

int vmx_host_write_ssp(long val)
{
    return vmx_write_vmcs_field(VMX_HOST_SSP, val);
}


long vmx_host_read_ia32_interrupt_ssp_table_addr()
{
    long ans;
    vmx_read_vmcs_field(&ans, VMX_HOST_IA32_INTERRUPT_SSP_TABLE_ADDR);
    return ans;
}

int vmx_host_write_ia32_interrupt_ssp_table_addr(long val)
{
    return vmx_write_vmcs_field(VMX_HOST_IA32_INTERRUPT_SSP_TABLE_ADDR, val);
}


/**
 * See Intel Manual Vol. 3
 *  [Table B-7. Encodings for 64-Bit Host-State Fields (0010_11xx_xxxx_xxxAb)]
 *  Field Name                  Encoding
 *  Host IA32_PAT               00002C00H
 *  Host IA32_EFER              00002C02H
 *  Host IA32_PERF_GLOBAL_CTRL  00002C04H
 *  Host IA32_PKRS              00002C06H
 */
#define HOST_IA32_PAT               0x00002C00
#define HOST_IA32_EFER              0x00002C02
#define HOST_IA32_PERF_GLOBAL_CTRL  0x00002C04
#define HOST_IA32_PKRS              0x00002C06

long vmx_host_read_ia32_pat()
{
    long ans;
    vmx_read_vmcs_field(&ans, HOST_IA32_PAT);
    return ans;
}

int vmx_host_write_ia32_pat(long val)
{
    return vmx_write_vmcs_field(HOST_IA32_PAT, val);
}


long vmx_host_read_ia32_efer()
{
    long ans;
    vmx_read_vmcs_field(&ans, HOST_IA32_EFER);
    return ans;
}

int vmx_host_write_ia32_efer(long val)
{
    return vmx_write_vmcs_field(HOST_IA32_EFER, val);
}


long vmx_host_read_ia32_perf_global_ctrl()
{
    long ans;
    vmx_read_vmcs_field(&ans, HOST_IA32_PERF_GLOBAL_CTRL);
    return ans;
}

int vmx_host_write_ia32_perf_global_ctrl(long val)
{
    return vmx_write_vmcs_field(HOST_IA32_PERF_GLOBAL_CTRL, val);
}


long vmx_host_read_ia32_pkrs()
{
    long ans;
    vmx_read_vmcs_field(&ans, HOST_IA32_PKRS);
    return ans;
}

int vmx_host_write_ia32_pkrs(long val)
{
    return vmx_write_vmcs_field(HOST_IA32_PKRS, val);
}


/**
 * See Intel Manual Vol. 3
 *  [Table B-11. Encoding for 32-Bit Host-State Field (0100_11xx_xxxx_xxx0B)]
 *  Field Name              Index       Encoding
 *  Host IA32_SYSENTER_CS   000000000B  00004C00H
 */
#define HOST_IA32_SYSENTER_CS   0x00004C00

long vmx_host_read_ia32_sysenter_cs()
{
    long ans;
    vmx_read_vmcs_field(&ans, HOST_IA32_SYSENTER_CS);
    return ans;
}

int vmx_host_write_ia32_sysenter_cs(long val)
{
    return vmx_write_vmcs_field(HOST_IA32_SYSENTER_CS, val);
}



