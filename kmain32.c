#include "video32bit.h"
#include "helpers_32bit.h"
#include "string32.h"

/**
 * @brief kernel 32 bit main function
 * 
 * @return int 
 */
int main32()
{
    clear_screen();
    printline("HELLO PANINARO!!!");
    printline("Uomo cactus!");
    printline(itoa32(10000));
    printline("XXXXXXXX");
    printline(itoa32(atoi32("")));
    return 0;
}
