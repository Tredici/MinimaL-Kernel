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
void putlu64(unsigned long n);
void puthex64(unsigned long n);
void putstr64(const char *str);
void printline64(const char *str);
void newline64();
void disable_cursor64();
void enable_cursor64();
void move_cursor64(int row, int col);
int get_foreground_color();
int set_foreground_color(int fc);
int get_background_color();
int set_background_color(int bc);

#endif
