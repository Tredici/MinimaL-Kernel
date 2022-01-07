/**
 * Faults and other exceptions give me too much toubles.
 * I have decided to implement a basic diagnostic
 * exception handling system to understand why errors
 * do occur.
 *
 * The current project for now is just to display
 * diagnostic info and then halt the machine.
 * HANDLERS WILL NOT RETURN!!!!
 *
 * For details see intel Manual Vol. 3
 *  [CHAPTER 6 INTERRUPT AND EXCEPTION HANDLING]
 *  [6.10 INTERRUPT DESCRIPTOR TABLE (IDT)]
 *  [6.14 EXCEPTION AND INTERRUPT HANDLING IN 64-BIT MODE]
 */
#ifndef INTERRUPT64
#define INTERRUPT64


void initialize_idt(void);
void load_idt_register(struct idt_gate_descriptor *idt, unsigned short limit);


#endif

