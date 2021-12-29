#ifndef VIDE32BIT
#define VIDE32BIT

/**
 * @brief clear console
 * 
 */
void clear_screen();

void putc(char c);
void printline(const char *str);
void newline();
void disable_cursor();
void enable_cursor();

#endif
