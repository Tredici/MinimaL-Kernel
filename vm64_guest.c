
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
