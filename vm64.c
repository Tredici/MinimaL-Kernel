
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
    if (0)
    {
        enter_vmx();
        printline64("VMX entered!");
    }
    else
    {
        // enable_vmx();
        // printline64("VMX enabled!");
        // //init_vm64_data_structures();
        // //printline64("VMX data structures initialised!");
        unsigned vmx = read_IA32_VMX_BASIC();
        putstr64("VMX = "); putl64(vmx); newline64();
    }
    

    return 0;
}

