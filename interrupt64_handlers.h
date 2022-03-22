#ifndef INTERRUPT64_HANDLERS
#define INTERRUPT64_HANDLERS

/**
 * IMPORTANT!
 *  The entry point of exception handler
 *  should be in assembly code to safely
 *  execute IRET.
 *  Because in this context is simply want
 *  to display diagnostic info before halting
 *  the machine this is not required.
 *
 *  Assembly code may be introduced in the
 *  future to handle these situations.
 */

/**
 * @brief Function handling DIV0 exception
 *
 */
void handle_div0();

/**
 * @brief Function handling INT3 (breakpoint) exception
 *
 */
void handle_int3();

/**
 * @brief Function handling Invalid Opcode exception!
 *
 */
void handle_ud();

/**
 * @brief Function handling Double fault abort!
 *
 */
void handle_double_f();

/**
 * @brief Function handling Invalid TSS Exception
 *
 */
void handle_tss();

/**
 * @brief Function handling Segment not present Exception
 *
 */
void handle_snp();

/**
 * @brief Function handling Stack Fault Exception
 *
 */
void handle_stack_f();

/**
 * @brief Function handling General Protection Exception
 *
 */
void handle_gpe();


/**
 * @brief Function handling General Protection Exception
 *
 */
void handle_pfe();

#endif
