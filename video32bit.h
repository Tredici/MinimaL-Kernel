#ifndef VIDE32BIT
#define VIDE32BIT

/**
 * @brief clear console
 * 
 */
void clear_screen();

void putc(char c);
void putstr(const char *str);
void printline(const char *str);
void newline();
void disable_cursor();
void enable_cursor();
void move_cursor(int row, int col);

#endif
