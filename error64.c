#include "error64.h"
#include "video64bit.h"


void panic64(const char *msg)
{
    set_background_color(7);
    set_foreground_color(8);
    printline64(msg);
    halt();
}

