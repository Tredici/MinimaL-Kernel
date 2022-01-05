#ifndef ERROR64
#define ERROR64

/**
 * @brief Panic the kernel and halt the machine
 * 
 * @param msg 
 */
void panic64(const char *msg);

/**
 * @brief Halt the machine
 * 
 */
void halt();


#endif
