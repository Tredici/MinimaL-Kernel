#ifndef VIDE32BIT
#define VIDE32BIT

/**
 * @brief clear console
 * 
 */
void clear_screen32();

void putc32(char c);
void puti32(int n);
void putstr32(const char *str);
void printline32(const char *str);
void newline32();
void disable_cursor32();
void enable_cursor32();
void move_cursor32(int row, int col);

#endif
