/**
 * Inizio del codice con le info per multiboot.
 *
 * Doc multiboot:
 *  https://www.gnu.org/software/grub/manual/multiboot/multiboot.html
 */

/**
 * Riserva una pagina di memoria fisica all'inizio della zona bss
 *
 */
#define STACK_SIZE 0x4000

/**
 * Per i valori da usare:
 *  https://www.gnu.org/software/grub/manual/multiboot/multiboot.html
 */
#define MAGIC       0x1BADB002
/**
 *  Byte di opzioni per le configurazioni iniziali:
 *  - primi 16 (0-15) bit vanno soddisfatti per forza,
 *      altrimenti non si avvia
 *  - successivi 16 (16-31) bit sono opzionali, il bootloader
 *      non è obbligato a soddisfarli
 *
 *  Descritti in "3.1.2 The magic fields of Multiboot header"
 *
 *  Significato:
 *  - bit 0:
 *      all boot modules loaded along with the operating system
 *      must be aligned on page (4KB) boundaries. Some operating
 *      systems expect to be able to map the pages containing
 *      boot modules directly into a paged address space during
 *      startup, and thus need the boot modules to be
 *      page-aligned.
 *
 *      Nel dubbio, si allinea tutto.
 *
 *  - bit 1:
 *      information on available memory via at least the ‘mem_*’
 *      fields of the Multiboot information structure (see Boot
 *      information format) must be included. If the boot loader
 *      is capable of passing a memory map (the ‘mmap_*’ fields)
 *      and one exists, then it may be included as well.
 *
 *      Giusto per stampare queste info all'avvio del main del
 *      kernl.
 *
 *  - bit 2:
 *      information about the video mode table (see Boot
 *      information format) must be available to the kernel.
 *
 *      Assolutamente no! Non so a che serva e non voglio usarla.
 *
 *  - bit 16:
 *      fields at offsets 12-28 in the Multiboot header are
 *      valid, and the boot loader should use them instead of
 *      the fields in the actual executable header to calculate
 *      where to load the OS image.
 *
 *      Sì. Per trovare l'inizio del codice usando i riferimenti
 *      a _start e cose così.
 */
#define FLAGS 0x00010003
/**
 * The field ‘checksum’ is a 32-bit unsigned value which,
 * when added to the other magic fields (i.e. ‘magic’ and
 * ‘flags’), must have a 32-bit unsigned sum of zero.
 */
#define CHECKSUM -(MAGIC + FLAGS)

/**
 * This section will be inserted at the beginning of the text
 * segment as the standard require with a linker trick.
 *
 * It is inserted here in a different section in order to
 * avoid "section reordering" performed by the linker when
 * merging multiple assemly files.
 *
 * Section name MUST start with DOT!!!!!!!!!!!!!
 */
.section .multiboot_header
/**
 * From the doc;
 *
 * 3.1 OS image format
 * The Multiboot header [...} must be longword (32-bit) aligned.
 */
.align 4
/*
Offset	Type	    Field Name	    Note
[3.1.2 The magic fields of Multiboot header]
0	    u32	        magic   	    required
4	    u32	        flags	        required
8	    u32	        checksum    	required
[3.1.3 The address fields of Multiboot header]
12	    u32	        header_addr	    if flags[16] is set
16	    u32	        load_addr	    if flags[16] is set
20	    u32	        load_end_addr	if flags[16] is set
24	    u32	        bss_end_addr	if flags[16] is set
28	    u32	        entry_addr	    if flags[16] is set
[3.1.4 The graphics fields of Multiboot header, Ignorato]
32	    u32	        mode_type	    if flags[2] is set
36	    u32	        width	        if flags[2] is set
40	    u32	        height	        if flags[2] is set
44	    u32	        depth	        if flags[2] is set
*/
header:
    /* magic fields */
    .long MAGIC
    .long FLAGS
    .long CHECKSUM
    /* address fields, they are all PHYSICAL ADDRESSES! */
    .long header    /* header_addr */
    .long header    /* load_addr, remember that the multiboot
        standard require the multiboot header to be placed
        at the beginning of the text segment, wich is also
        the segment at lowest addresses */
    .long _end_of_data  /* load_end_addr, defined with a ld trick */
    .long _end_of_bss /* bss_end_addr, defined with a linker
        trick. Remember that all the memory in the bss segment
        is initialised to 0 so it does not need to be stored
        in the file image */
    .long _start /* entry_addr */
/**
 * The remaining part of the header is not necessary because
 * graphics options are unused
 */

/**
 * Inizia ora il codice vero e proprio che sarà invocato dal
 * bootloader seguendo le informazioni nell'header multiboot
 */
.text
/**
 * Si parte a 32 bit. Poi si andrà a 64. Poi ci pensiamo.
 *
 * Manuale as [9.16.14 Writing 16-bit Code]
 *  [...] You can switch as to writing 32-bit code with the
 *  ‘.code32’ directive or 64-bit code with the ‘.code64’
 *  directive. 
 */
.code32
.global _start /* maybe unnecessary */
_start: /* kernel entrypoint */
    /* print 7 on the screen and terminate */
    mov $'7', %al
	mov  $15, %ah
	mov  %ax,         (0xb8000)
	cli
	hlt
/* Check section [3.2 Machine state] for TODO */

.bss
/**
 * Smart trick to get a ready to use stack segment.
 * Remember that stack size in kernel mode i limited to
 * one or two pages.
 */
stack:
    nop
	;.skip STACK_SIZE 

