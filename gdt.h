

#ifndef GDT
#define GDT

/**
 * Code and definitions to initialise
 * GLOBAL DESCRIPTOR TABLE.
 * See Intel manual Vol. 3:
 *  [3.4.5 Segment Descriptors]
 */
struct segment_descriptor
{
    int limit_15_0 : 16;    /* 0 for 64 bit */
    int base_15_0 : 16;     /* 0 for 64 bit */
    int base_23_16 : 8;     /* 0 for 64 bit */
    int type : 4;           /* Depends on system flag.
            data/stack: set to 2
            code:       set to 10

            For details see Intel Manual Vol. 3
            [3.4.5.1 Code- and Data-Segment Descriptor Types]
            [Table 3-1. Code- and Data-Segment Types] */
    int system : 1;         /* system segment? If set
            contains reference to code or data segment.
            It has nothing to do with user/system context.
            MUST be 1 in this simple context! */
    int dpl : 2;            /* descriptor privilege level */
    int present : 1;        /* Is valid? */
    int limit_19_16 : 4;    /* 0 for 64 bit */
    int avl : 1;            /* Usable by system software.
            Unnecessary in this context. */
    int Long_mode_code : 1; /* IA-32e only! Only for code!
            If L-bit is set, then D-bit must be cleared.
            If not code MUST be 0! */
    int d_b : 1;            /* default operand size */
    int granularity : 1;    /* Granularity of limit field,
                             * unnecessary in 64 bit context */
    int base_31_24 : 8;
} __attribute__((packed));


#endif
