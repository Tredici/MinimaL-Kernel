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
    putstr32("FLAGS: "); puti32(mi->flags); newline32();
    if (mi->flags & MULTIBOOT_FLAG_0)
    {
        putstr32("MEMORY lower: "); puti32(mi->mem_lower); putc32('K'); newline32();
        putstr32("MEMORY upper: "); puti32(mi->mem_upper); putc32('K'); newline32();
    }
    else printline32("MEMORY info not availabe!");

    putstr32("CMDLINE:      ");
    if (mi->flags & MULTIBOOT_FLAG_2)   printline32((const char*)mi->cmdline);
    else    printline32("(Unspecified!)");

    if (mi->flags & MULTIBOOT_FLAG_5)
    {
        printline32("ELF Kernel!");
    }

    putstr32("BOOTLOADER:   ");
    if (mi->flags & MULTIBOOT_FLAG_9)
        printline32((const char*)mi->boot_loader_name);
    else
        printline32("(Unspecified!)");

    if (mi->flags & MULTIBOOT_FLAG_11)
        printline32("VBE info available!");
    else
        printline32("VBE info NOT available!");
}

/**
 * @brief kernel 32 bit main function
 * 
 * @return int 
 */
int main32(struct multiboot_info *mi)
{
    clear_screen32();
    putstr32("Multiboot info: "); puti32((int)mi); newline32();
    if (mi)
        print_multiboot(mi);

    printline32("HELLO PANINARO!!!");
    printline32("Uomo cactus!");
    printline32(itoa32(10000));
    printline32("XXXXXXXX");
    printline32(itoa32(atoi32("")));
    return 0;
}
