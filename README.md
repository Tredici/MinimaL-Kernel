# Disclaimer
Questa repo è brutta.
Sarà sistemata poi.
(Forse.)

# Descrizione
Progettino (si spera) molto semplice per scrivere un kernel minimale per x86_64 che sfrutti il supporto hardware per la virtualizzazione e ci lanci una "mini-VM" (1 solo "processo") che cerchi di eseguire istruzioni non implicitamente permesse, intercettate dal mini kernel hypervisor ed eseguite in modo da dare parvenza alla VM che tutto sia andato come richiesto.


# Code Flow
- header.S: kernel entry point (32 bit)
- trampoline.S: 32 bit configuration code
- trampoline64.S: 64 bit entry point
- kmain64.c: 64 bit kernel main

# Reference:
Elenco dei posti dove cercare le informazioni per capire che è stato fatto:
- make (build system): https://www.gnu.org/software/make/manual/make.html
- multiboot (specification): https://www.gnu.org/software/grub/manual/multiboot/multiboot.html
- as (assembler): https://sourceware.org/binutils/docs/as.html
- ld (linker): https://sourceware.org/binutils/docs/ld.html
- VGA text mode (memoria video mappata in RAM): https://en.wikipedia.org/wiki/VGA_text_mode
- Video BIOS (quello che permette di stampare testo su schermo dal bootloader usando l'interrrupt 0x10 predisposto dal BIOS): https://en.wikipedia.org/wiki/Video_BIOS
- Text mode cursor (how to control it): https://wiki.osdev.org/Text_Mode_Cursor
- INT 10H (l'interrupt handler che permette di scrivere a
video dal bootloader come visto in alcuni esempi con QEMU
preimpostato dal BIOS): https://en.wikipedia.org/wiki/INT_10H
- Text based console (tutorial): http://kernelx.weebly.com/text-console.html
- Manipulating the Text-mode Cursor (VGA info): http://www.osdever.net/FreeVGA/vga/textcur.htm
- CRT Controller Registers (VGA register): http://www.osdever.net/FreeVGA/vga/crtcreg.htm
    Data are sent using tho registers, the first one to specify the "control register" receiving the data and the
    second for the data itself
- Come viene realizzato il mapping: https://stackoverflow.com/questions/17367618/address-of-video-memory
- .bss (variabili non inizializzate a compile time): https://en.wikipedia.org/wiki/.bss
- Setting Up Long Mode (tutorial): https://wiki.osdev.org/Setting_Up_Long_Mode
- ELF(5) (about ELF sections): https://www.man7.org/linux/man-pages/man5/elf.5.html

Da leggere (forse) in futuro:
System address map initialization in x86/x64 architecture part 1: PCI-based systems
    https://resources.infosecinstitute.com/topic/system-address-map-initialization-in-x86x64-architecture-part-1-pci-based-systems/


