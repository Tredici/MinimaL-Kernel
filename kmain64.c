/**
 * 64 bit main
 */

#include "video64bit.h"
#include "vm64.h"

void main64()
{
    clear_screen64();
    printline64("Hello 64 bit!");
    printline64("Long Mode Activated!");
    printline64("Good Bye!");
    start_vm();
}

