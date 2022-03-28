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
extern void *_end_of_bss;

void memory_init()
{
    putstr64("_heap_base = "); puthex64(&_heap_base); newline64();
    putstr64("_heap_base = "); putlu64((unsigned long)&_heap_base); newline64();
    panic64(".");
}

