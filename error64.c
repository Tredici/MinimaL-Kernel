#include "error64.h"
#include "video64bit.h"


void panic64(const char *msg)
{
    clear_screen64();
    printline64(msg);
    halt();
}

