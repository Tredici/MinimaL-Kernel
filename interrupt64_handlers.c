
#include "interrupt64_handlers.h"
#include "video64bit.h"
#include "error64.h"

void handle_div0()
{
    panic64("Exception DIV0!");
}

void handle_int3()
{
    panic64("Exception Breakpoint!");
}
