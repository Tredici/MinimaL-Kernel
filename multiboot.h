/**
 * Espose definition of structure passed by the
 * bootloader to the kernel.
 *
 * See:
 *  https://www.gnu.org/software/grub/manual/multiboot/multiboot.html#Boot-information-format
 */


#ifndef MULTIBOOT
#define MULTIBOOT

#include "types.h"

struct multiboot_info
{
    u32 flags;

#define MULTIBOOT_FLAG_0 (1 << 0)
    u32 mem_lower;
    u32 mem_upper;

#define MULTIBOOT_FLAG_1 (1 << 1)
    u32 boot_device;

#define MULTIBOOT_FLAG_2 (1 << 2)
    u32 cmdline;

#define MULTIBOOT_FLAG_3 (1 << 3)
    u32 mods_count;
    u32 mods_addr;

#define MULTIBOOT_FLAG_4 (1 << 4)
#define MULTIBOOT_FLAG_5 (1 << 5)
    u32 syms[4];

#define MULTIBOOT_FLAG_6 (1 << 6)
    u32 mmap_length;
    u32 mmap_addr;

#define MULTIBOOT_FLAG_7 (1 << 7)
    u32 drives_length;
    u32 drives_addr;

#define MULTIBOOT_FLAG_8 (1 << 8)
    u32 config_table;

#define MULTIBOOT_FLAG_9 (1 << 9)
    u32 boot_loader_name;

#define MULTIBOOT_FLAG_10 (1 << 10)
    u32 apm_table;

#define MULTIBOOT_FLAG_11 (1 << 11)
    u32 vbe_control_info;
    u32 vbe_mode_info;
    u32 vbe_mode;
    u32 vbe_interface_seg;
    u32 vbe_interface_off;
    u32 vbe_interface_len;

#define MULTIBOOT_FLAG_12 (1 << 12)
    u32 framebuffer_addr;
    u32 framebuffer_pitch;
    u32 framebuffer_width;
    u32 framebuffer_height;
    u32 framebuffer_bpp;
    u32 framebuffer_type;
    u32 color_info;
};



#endif