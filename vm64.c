
#include "vm64.h"
#include "video64bit.h"
#include "error64.h"

#define VMsucceed (1<<0 | 1<<2 | 1<<4 | 1<<6 | 1<<7 | 1<<11)
#define VMfailinvalid (1<<2 | 1<<4 | 1<<6 | 1<<7 | 1<<11)

static int vmx_success(int status)
{
    return !status;
}

static int vmx_fail_invalid(int status)
{
    // CF == 1, other are 0
    return status == 1;
}

int start_vm()
{
    int status;

    if (check_vm_support())
    {
        printline64("VMX supported!");
    }
    else
    {
        panic64("VMX not supported!");
    }
    printline64("Ciaooooooooooooo");
    putstr64("Rev Id = "); putu64(read_vmcs_revision_identifier()); newline64();
    putstr64("VMX    = "); putl64(read_IA32_VMX_BASIC()); newline64();
    set_cr4_vmxe();
    printline64("CR4.VMXE set!");
    void *vmx_region = get_vmx_region();
    putstr64("vmx_region = "); puthex64((unsigned long)vmx_region); newline64();
    putstr64("vmx_region = "); puti64((unsigned long)vmx_region); newline64();
    putstr64("*vmx_region = "); puthex64(*(unsigned long*)vmx_region); newline64();

    status = enter_vmx(vmx_region);
    if (!vmx_success(status))
    {
        printline64("enter_vmx failed!");
        if (vmx_fail_invalid(status))
        {
            panic64("vmx_fail_invalid");
        }
    }

    printline64("enter_vmx success");
    void *vmcs_region = get_vmcs_region();
    status = vmx_enable_vmcs_region(vmcs_region);
    if (!vmx_success(status))
    {
        panic64("Disaster VMPTRLD");
    }
    printline64("VMCS region enabled!");

    status = vmx_clear_vmcs(vmcs_region);
    if (!vmx_success(status))
    {
        panic64("Disaster VMCLEAR");
    }
    printline64("VMCS successfully cleared!");

    printline64("Paninooo");

    return 0;
}

/**
 * See Intel manual Vol. 3
 *  [23.2 FORMAT OF THE VMCS REGION]
 */
int vmx_get_vmcs_region_abort_status(void *vmcs_region)
{
    return !vmcs_region ? -1 : *(1 + (int *)vmcs_region);
}

int vmx_vmcs_field_encoding(enum vmx_vmcs_field_access_type access, int index, enum vmx_vmcs_field_type type, enum vmx_vmcs_field_width width)
{
    if (! ((access & 1) == access && (index & 0x1ff) == index
        && (type & 3) == type && (width & 3) == width) )
    {
        return -1;
    }
    return access | index << 1 | type << 10 | width << 13;
}
