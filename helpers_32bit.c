/**
 * This file holds some 32 bit C function
 * to be used as helper from assemly code
 */

#include "helpers_32bit.h" 

/**
 * See Intel manual 3 [4.3 32-bit Paging]
 *
 * This structure represent a Page Directory
 * Entry, an entry in the tabled pointed by
 * CR3.
 * See Figure 4-4 in the manual to understand
 * format
 */
/**
 * Trick to easily configure 4MB pages,
 * see table 4-4 for deatils.
 */
struct PDE_4MB_PAGE
{
    int present : 1;    /* Is entry present? */
    int rw : 1;         /* Are write allowed? (Remember that kernel could bypass this limitation) */
    int us : 1;         /* Is accessible by the user? */
    int pwt : 1;        /* Page-level write-through? */
    int pcd : 1;        /* Page-level cache disable? */
    int accessed : 1;   /* Has the software accessed the page? Unnecessary in this toy kernel. */
    int dirty : 1;      /* Has the software write in the page? Unnecessary in this toy kernel. */
    int ps : 1;         /* MUST BE 1! */
    /* First byte */
    int global : 1;     /* Is the translation global? Unnecessary in this context. */
    int : 3;            /* Ignored. */
    int pat : 1;        /* Page Attribute Table. Ignored, use 0. */
    int top_bits : 4;   /* To use 40 bits addresses */
    /* 2nd byte + 1 bit */
    int : 5;            /* Reserved, MUST BE 0! */
    int frame : 10;     /* Pointer to frame */
};


/**
 * Zeroes memory section
 */
void zero(void *ptr, int len)
{
    char *p = (char *)ptr;
    while (len--)
        *(p++) = 0;
}

/**
 * @brief Initialise the page directory
 * creating an identity mapping for the
 * first megabytes
 *
 * @param pd 
 */
void initialize_page_directory(void *pd)
{
    int i;
    /* Configure 4MB pages */
    struct PDE_4MB_PAGE *pde4mb = (struct PDE_4MB_PAGE *)pd;

    /* Assert size of fage entry is 4 byte */
    if (sizeof(struct PDE_4MB_PAGE) != 4)
    {
        c_abort("Invalid entry size!");
    }

    /* Use 40 MB by default, they should be enough */
    for (i = 0; i != 10; ++i)
    {
        /* Zero entry */
        (*pde4mb) = (struct PDE_4MB_PAGE){};

        pde4mb->present = 1; /* valid entry */
        pde4mb->rw = 1; /* writable */
        pde4mb->us = 1; /* system only */
        pde4mb->ps = 1; /* 4MB page entry*/
        pde4mb->pat = 0; /* unwanted */
        pde4mb->top_bits = 0; /* no 40 bit memory */
        pde4mb->frame = i; /* identity mapping */

        /* Go to next entry */
        ++pde4mb;
    }
}

