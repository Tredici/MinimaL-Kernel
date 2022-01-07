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


#endif
