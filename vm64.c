
#include "vm64.h"
#include "video64bit.h"
#include "error64.h"

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
    enter_vmx();
    printline64("VMX entered!");

    return 0;
}

