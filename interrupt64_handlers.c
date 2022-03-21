
#include "interrupt64_handlers.h"
#include "video64bit.h"
#include "error64.h"
#include "string64.h"

void handle_div0()
{
    panic64("Exception DIV0!");
}

void handle_int3()
{
    panic64("Exception Breakpoint!");
}


void handle_gpe_c(long error)
{
    char buffer[80] = "General Protection Exception(";
    char *tmp;
    tmp = strcat64(buffer, ltoa64(error));
    tmp = strcat64(tmp, ")");
    panic64(buffer);
}
