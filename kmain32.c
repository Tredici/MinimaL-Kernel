#include "video32bit.h"
#include "helpers_32bit.h"
#include "string32.h"
#include "multiboot.h"

/**
 * @brief Display multiboot info passed by the
 * bootloader
 *
 * @param mi struct multiboot_info
 */
void print_multiboot(struct multiboot_info *mi)
{
    putstr("FLAGS: "); puti(mi->flags); newline();
    if (mi->flags & MULTIBOOT_FLAG_0)
    {
        putstr("MEMORY lower: "); puti(mi->mem_lower); putc('K'); newline();
        putstr("MEMORY upper: "); puti(mi->mem_upper); putc('K'); newline();
    }
    else printline("MEMORY info not availabe!");

    putstr("CMDLINE:      ");
    if (mi->flags & MULTIBOOT_FLAG_2)   printline((const char*)mi->cmdline);
    else    printline("(Unspecified!)");

    if (mi->flags & MULTIBOOT_FLAG_5)
    {
        printline("ELF Kernel!");
    }

    putstr("BOOTLOADER:   ");
    if (mi->flags & MULTIBOOT_FLAG_9)
        printline((const char*)mi->boot_loader_name);
    else
        printline("(Unspecified!)");

    if (mi->flags & MULTIBOOT_FLAG_11)
        printline("VBE info available!");
    else
        printline("VBE info NOT available!");
}

/**
 * @brief kernel 32 bit main function
 * 
 * @return int 
 */
int main32(struct multiboot_info *mi)
{
    clear_screen();
    putstr("Multiboot info: "); puti((int)mi); newline();
    if (mi)
        print_multiboot(mi);

    printline("HELLO PANINARO!!!");
    printline("Uomo cactus!");
    printline(itoa32(10000));
    printline("XXXXXXXX");
    printline(itoa32(atoi32("")));
    return 0;
}
