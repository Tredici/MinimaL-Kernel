#include "memory.h"

// Include submodules
#include "modules/C-page-allocator/page_allocator.h"
#include "modules/C-memory-manager/memory_manager.h"

#include "error64.h"
#include "video64bit.h"

/**
 * External variable defined in
 * the linker script likerops.ld
 */
extern void *_heap_base;

/**
 * Align a pointer to the beginning of the next empty page.
 * If the pointer refer to the beginning of a page it is
 * directly returned.
 */
static void *aling_to_page(void *ptr)
{
    const unsigned long last_12 = (1L << 12) - 1L;
    return (unsigned long)ptr & last_12
        ? (void *)((unsigned long)ptr | last_12) + 1L
        : ptr;
}

const long pages_used_for_synamic_memory = 10;
const unsigned long page_size = (1L << 12);

static struct page_allocator pa;
/**
 * Bitfield for page allocator
 */
static char page_bits[4096];

void *kalloc_page()
{
    return page_allocator_allocate(&pa);
}

int kfree_page(void *page)
{
    return page_allocator_free(&pa, page);
}

void *kalloc(unsigned long size)
{
    return mm_malloc(size);
}
/**
 * Free kernel dynamic memory.
 */
void kfree(void *ptr)
{
    mm_free(ptr);
}


void memory_init()
{
    // get beginning of page buffer base
    void *page_buffer = aling_to_page(&_heap_base);
    // init paging subsystem
    putstr64("Initializing page subsystem... ");
    if (!page_allocator_init(&pa, page_buffer, page_size, page_bits, sizeof(page_bits)*8UL))
    {
        panic64("page_allocator_init");
    }
    printline64("DONE!");
    // init kalloc/kfree subsystem
    putstr64("Initializing kalloc/kfree... ");
    void *kdyn = kalloc_page();
    if (!kdyn)
    {
        panic64("kalloc_page");
    }
    {
        unsigned long check = (unsigned long)kdyn;
        for (int i = 1; i != pages_used_for_synamic_memory; ++i)
        {
            if (check + page_size != (unsigned long)kalloc_page())
            {
                panic64("Misaligned pages!");
            }
            check += page_size;
        }
    }
    if (mm_init_memory_manager(kdyn, page_size*pages_used_for_synamic_memory))
    {
        panic64("mm_init_memory_manager");
    }
    printline64("DONE!");
}

