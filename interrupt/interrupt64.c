
#include "interrupt64.h"
#include "../error64.h"
#include "interrupt64_handlers.h"

#define INT_DIV0    0
#define INT_DBG     3
#define INT_UD      6
#define INT_DOUBLEF 8
#define INT_TSS     10
#define INT_SNP     11
#define INT_STACK_F 12
#define INT_GPE     13
#define INT_PFE     14

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
#define TYPE_64B_ABORT_GATE TYPE_64B_INTERRUPT_GATE
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
    idt_entry->offset_15_0 = rip_handler & 0xffff;
    idt_entry->offset_31_16 = (rip_handler >> 16) & 0xffff;
    idt_entry->offset_63_32 = (rip_handler >> 32) & 0xffffffff;
}

/**
 * @brief Initialize entry in IDT. Avoi code repetition.
 *
 * @param idt               - pointer to the IDT
 * @param exception_number  - exception number in the IDT
 * @param type              - TRAP or INTERRUPT (fault)?
 * @param rip_handler       - pointer to handler
 */
static inline void initialize_idt_entry(struct idt_gate_descriptor idt[], int exception_number, int type, u64 rip_handler)
{
    idt[exception_number] = (struct idt_gate_descriptor){};
    idt[exception_number].present = 1;
    idt[exception_number].type = type;
    idt[exception_number].segment_selector = 0x10; /* Always this for code */
    set_pointer_to_handler(&idt[exception_number], rip_handler);
}

void initialize_idt()
{
    if (sizeof(struct idt_gate_descriptor) != 16)
    {
        panic64("sizeof(struct idt_gate_descriptor) != 16");
    }

    /**
     * See Intel Manual Vol. 3
     *  [6.15 EXCEPTION AND INTERRUPT REFERENCE]
     */
    /* [Interrupt 0—Divide Error Exception (#DE)] */
    initialize_idt_entry(idt, INT_DIV0, TYPE_64B_INTERRUPT_GATE, (u64)&handle_div0);
    /* [Interrupt 3—Breakpoint Exception (#BP)] */
    initialize_idt_entry(idt, INT_DBG, TYPE_64B_TRAP_GATE, (u64)&handle_int3);
    /* [Interrupt 6—Invalid Opcode Exception (#UD)] */
    initialize_idt_entry(idt, INT_UD, TYPE_64B_TRAP_GATE, (u64)&handle_ud);
    /* [Interrupt 8—Double Fault Exception (#DF)] */
    initialize_idt_entry(idt, INT_DOUBLEF, TYPE_64B_ABORT_GATE, (u64)&handle_double_f);
    /* [Interrupt 10—Invalid TSS Exception (#TS)] */
    initialize_idt_entry(idt, INT_TSS, TYPE_64B_INTERRUPT_GATE, (u64)&handle_tss);
    /* [Interrupt 11—Segment Not Present (#NP)] */
    initialize_idt_entry(idt, INT_SNP, TYPE_64B_INTERRUPT_GATE, (u64)&handle_snp);
    /* [Interrupt 12—Stack Fault Exception (#SS)] */
    initialize_idt_entry(idt, INT_STACK_F, TYPE_64B_INTERRUPT_GATE, (u64)&handle_stack_f);
    /* [Interrupt 13—General Protection Exception (#GP)] */
    initialize_idt_entry(idt, INT_GPE, TYPE_64B_INTERRUPT_GATE, (u64)&handle_gpe);
    /* [Interrupt 14—Page-Fault Exception (#PF)] */
    initialize_idt_entry(idt, INT_PFE, TYPE_64B_INTERRUPT_GATE, (u64)&handle_pfe);

    load_idt_register(idt, IDT_LIMIT);
}

