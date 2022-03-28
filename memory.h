/**
 * This file expose functions
 * to manage dynamic memory and
 * page allocation.
 */
#ifndef MEMORY
#define MEMORY

/**
 * Initialize memory subsystem
 */
void memory_init();

/**
 * Allocate page.
 */
void *kalloc_page();

/**
 * Deallocate page.
 */
int kfree_page(void *page);

/**
 * Allocate kernel dynamic memory.
 */
void *kalloc(unsigned long size);

/**
 * Free kernel dynamic memory.
 */
void kfree(void *ptr);

#endif
