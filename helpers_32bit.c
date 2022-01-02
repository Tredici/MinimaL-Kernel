/**
 * This file holds some 32 bit C function
 * to be used as helper from assemly code
 */

#include "helpers_32bit.h" 

#define MAX_PHYS_ADDR_BIT 46

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


/**
 * Entries of the pml4 table.
 * See Vol. 3
 *  [Table 4-15. Format of a PML4 Entry (PML4E)
 *  that References a Page-Directory-Pointer Table]
 */
struct PML4E
{
    long long int present : 1;    /* Is entry present */
    long long int rw : 1;         /* Can write? */
    long long int us : 1;         /* Accessible by user? */
    long long int pwt : 1;        /* Page-level write-through? */
    long long int pcd : 1;        /* Page-level cache disable? */
    long long int accessed : 1;   /* Page accessed? Managed by hw */
    long long int : 1;            /* Ignored */
    long long int ps : 1;         /* MUST be 0 */
    long long int : 4;            /* Ignored */
    long long int pdtp : (MAX_PHYS_ADDR_BIT - 1 - 12 + 1); /* Physical address of 4KB aligned PDP table */
    long long int : (51 - MAX_PHYS_ADDR_BIT + 1); /* MUST be 0! */
    long long int : 11;           /* Ignored */
    long long int xd : 1;         /* If IA32_EFER.NXE = 1, execute-disable or must be 0! */
};

/**
 * Entries of the pdpt table that
 * reference a Page Directory
 *
 * See Vol. 3:
 *  [Table 4-17. Format of a Page-Directory-
 *  Pointer-Table Entry (PDPTE) that
 *  References a Page Director]
 */
struct PDPTE
{
    long long int present : 1;  /* Is page present? */
    long long int rw : 1;       /* Writable? */
    long long int us : 1;       /* Accessible by user? */
    long long int pwt : 1;      /* Page-level write-through? */
    long long int pcd : 1;      /* Page-level cache disable? */
    long long int accessed : 1; /* Page accessed? Managed by hw */
    long long int : 1;          /* Ignored */
    long long int ps : 1;       /* MUST be 0 */
    long long int : 4;          /* Ignored */
    long long int pdp : (MAX_PHYS_ADDR_BIT - 1 - 12 + 1); /* Physical address of 4KB aligned PDP table */
    long long int : (51 - MAX_PHYS_ADDR_BIT + 1); /* MUST be 0! */
    long long int : 11;         /* Ignored */
    long long int xd : 1;       /* If IA32_EFER.NXE = 1, execute-disable or must be 0! */
};

/**
 * Entries of the pd table that
 * reference 2 MB pages
 *
 * See:
 *  [Table 4-18. Format of a Page-Directory
 *  Entry that Maps a 2-MByte Page]
 */
struct PDE_2MB_PAGE
{
    long long int present : 1;  /* Is page present? */
    long long int rw : 1;       /* Writable? */
    long long int us : 1;       /* Accessible by user? */
    long long int pwt : 1;      /* Page-level write-through? */
    long long int pcd : 1;      /* Page-level cache disable? */
    long long int accessed : 1; /* Page accessed? Managed by hw */
    long long int dirty : 1;    /* Page written? Managed by hw */
    long long int ps : 1;       /* MUST be 1! Page Size */
    long long int global : 1;   /* Is the translation global? Unnecessary in this context. */
    long long int : 3;          /* Ignored */
    long long int pat : 1;      /* Page Attribute Table. Ignored, use 0. */
    long long int : 8;          /* Ignored */
    long long int pta : (MAX_PHYS_ADDR_BIT - 1 - 21 + 1);
    long long int : (51 - MAX_PHYS_ADDR_BIT + 1); /* MUST be 0 */
    long long int : 7;          /* Ignored */
    long long int pk : 4;       /* protection_key. Use 0 in this context */
    long long int xd : 1;       /* If IA32_EFER.NXE = 1, execute-disable or must be 0! */
};

/**
 * See Intel Manual Vol. 3
 *  [4.5 4-LEVEL PAGING AND 5-LEVEL PAGING]
 *
 */
void initialize_64bits_page_tables(void *pml4, void *pdpt, void *pdt)
{
    struct PML4E *pml4e = (struct PML4E *)pml4;
    struct PDPTE *pdpte = (struct PDPTE *)pdpt;
    struct PDE_2MB_PAGE *pde2mb = (struct PDE_2MB_PAGE *)pdt;
    int i;

    if (sizeof(struct PML4E) != 8)
    {
        c_abort("sizeof(struct PML4E) != 8");
    }
    if (sizeof(struct PDPTE) != 8)
    {
        c_abort("sizeof(struct PDPTE) != 8");
    }
    if (sizeof(struct PDE_2MB_PAGE) != 8)
    {
        c_abort("sizeof(struct PDE_2MB_PAGE) != 8");
    }

    /**
     * May be useful: 
     *
     * See Vol. 3
     *  [Figure 4-11. Formats of CR3 and Paging-Structure
     *  Entries with 4-Level Paging and 5-Level Paging]
     */
    /**
     * Init top level page
     * Only first entry is necessary
     */
    pml4e->present = 1; /* Valid entry */
    pml4e->rw = 1;      /* writable */
    pml4e->pdtp = ((long long int)pdpte) >> 12;

    /**
     * Init 3rd level page
     * Only first entry is necessary
     */
    pdpte->present = 1; /* Valid entry */
    pdpte->rw = 1;      /* writable */
    pdpte->pdp = ((long long int)pde2mb) >> 12;;

    /**
     * Init 2rd level page
     * Map obly first 40 MB
     */
    /* Use 40 MB by default, they should be enough */
    for (i = 0; i != 20; ++i)
    {
        (*pde2mb) = (struct PDE_2MB_PAGE){};

        pde2mb->present = 1;
        pde2mb->rw = 1;
        pde2mb->ps = 1; /* 2MB page entry */
        pde2mb->pta = i;    /* Identity mapping */

        ++pde2mb;
    }

    /* No 1st level page */
}
