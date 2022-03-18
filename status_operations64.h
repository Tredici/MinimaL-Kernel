
#ifndef STATUS_OPERATIONS
#define STATUS_OPERATIONS

/**
 * Functions to read Control Registers
 */
long so_read_cr0();
long so_read_cr1();
long so_read_cr2();
long so_read_cr3();
long so_read_cr4();
long so_read_cr5();
long so_read_cr6();
long so_read_cr7();
long so_read_cr8();

/**
 * Functions to read segment registers
 */
short so_read_cs();
short so_read_ds();
short so_read_ss();
short so_read_es();
short so_read_fs();
short so_read_gs();

/**
 * Read RFLAGS register
 */
long so_read_rflags();

/**
 * Read Global descriptor table register. 
 */
int so_read_gdtr(void *gdt, unsigned short *limit);

#endif
