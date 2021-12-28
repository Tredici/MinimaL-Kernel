
#ifndef HELPERS_32BIT
#define HELPERS_32BIT

/**
 * @brief Noreturn function to display a message
 * and abort machine startup
 *
 * @param msg The message to be displayed
 */
void c_abort(const char* msg);

void zero(void *ptr, int len);

void initialize_page_directory(void *pd);

#endif