
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
    putstr64("vmx_region = "); puthex64(vmx_region); newline64();
    putstr64("vmx_region = "); puti64(vmx_region); newline64();
    putstr64("*vmx_region = "); puthex64(*(unsigned long*)vmx_region); newline64();

    int status = enter_vmx(vmx_region);
    if (vmx_success(status))
    {
        printline64("enter_vmx success");
    }
    else
    {
        printline64("enter_vmx failed!");
        if (vmx_fail_invalid(status))
        {
            panic64("vmx_fail_invalid");
        }
    }
    printline64("VMX entered!");
    init_vm64_data_structures();
    printline64("Paninooo");

    return 0;
}

