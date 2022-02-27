#ifndef VIDE64BIT
#define VIDE64BIT

/**
 * @brief clear console
 * 
 */
void clear_screen64();

void putc64(char c);
void puti64(int n);
void putu64(unsigned n);
void putl64(long n);
void putstr64(const char *str);
void printline64(const char *str);
void newline64();
void disable_cursor64();
void enable_cursor64();
void move_cursor64(int row, int col);

#endif
