
#include "interrupt64.h"
#include "error64.h"
#include "interrupt64_handlers.h"


#define IDT_ENTRYES 256
#define IDT_LIMIT (256*16 - 1)

/**
 * See Intel Manual Vol. 3
 *  [Table 3-2. System-Segment and Gate-Descriptor Types]
 *
 * To understand which is to be used in the type field
 * of the following struct see:
 *  [6.15 EXCEPTION AND INTERRUPT REFERENCE]
 */
#define TYPE_64B_INTERRUPT_GATE 14
#define TYPE_64B_TRAP_GATE 15

typedef unsigned long long int u64;

/**
 * See Intel Manual Vol. 3
 *  [Figure 6-8. 64-Bit IDT Gate Descriptors]
 */
struct idt_gate_descriptor
{
    u64 offset_15_0 : 16;
    u64 segment_selector : 16;
    u64 ist : 3; /* Interrupt table stack
            See Intel Manual Vol. 3
            [6.14.5 Interrupt Stack Table]
            for details. Unused if 0.

            NOT USED IN THIS CONTEXT!
            */
    u64 : 5; /* MUST BE 0! */
    u64 type : 4; /* Described in Table 3-2 */
    u64 : 1; /* MUST BE 0! */
    u64 dpl : 2; /* Descriptor privilege level */
    u64 present : 1; /* Is gate present? */
    u64 offset_31_16 : 16;
    u64 offset_63_32 : 32;
    u64 : 32; /* Reserved */
} __attribute__((packed));

/**
 * Page aligned is always good.
 * For details about __attribute__ ((aligned (n))), see:
 *  https://gcc.gnu.org/onlinedocs/gcc-3.3/gcc/Type-Attributes.html
 */
struct idt_gate_descriptor idt[IDT_ENTRYES]  __attribute__ ((aligned (4096)));


static void set_pointer_to_handler(struct idt_gate_descriptor *idt_entry, u64 rip_handler)
{
    // Pointer to handler
    idt_entry->offset_15_0 = rip_handler & ((1 << 16) - 1);
    idt_entry->offset_31_16 = (rip_handler >> 16) & ((1 << 16) - 1);
    idt_entry->offset_63_32 = (rip_handler >> 32) & ((1 << 32) - 1);
}

/**
 * @brief Initialize DIV BY 0 handler
 *
 * @param idt
 *
 * See Intel Manual Vol. 3
 *  [6.15 EXCEPTION AND INTERRUPT REFERENCE]
 *  [Interrupt 0—Divide Error Exception (#DE)]
 */
void initialize_DIV0(struct idt_gate_descriptor idt[])
{
    u64 rip_handler = (u64)&handle_div0;

    idt[0] = (struct idt_gate_descriptor){};
    idt[0].present = 1;
    idt[0].type = TYPE_64B_INTERRUPT_GATE;
    idt[0].segment_selector = 0x08; /* Always this for code */
    set_pointer_to_handler(&idt[0], rip_handler);
}


/**
 * @brief Initialize INT3 (debug) handler
 *
 * @param idt
 *
 * See Intel Manual Vol. 3
 *  [6.15 EXCEPTION AND INTERRUPT REFERENCE]
 *  [Interrupt 3—Breakpoint Exception (#BP)]
 */
void initialize_INT3(struct idt_gate_descriptor idt[])
{
    const int int_number = 3;
    u64 rip_handler = (u64)&handle_int3;

    idt[int_number] = (struct idt_gate_descriptor){};
    idt[int_number].present = 1;
    idt[int_number].type = TYPE_64B_TRAP_GATE;
    idt[int_number].segment_selector = 0x08; /* Always this for code */
    set_pointer_to_handler(&idt[int_number], rip_handler);
}

void initialize_idt()
{
    if (sizeof(struct idt_gate_descriptor) != 16)
    {
        panic64("sizeof(struct idt_gate_descriptor) != 16");
    }

    initialize_DIV0(idt);
    initialize_INT3(idt);

    load_idt_register(idt, IDT_LIMIT);
}

