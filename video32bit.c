/**
 * This file expose a set of function to print
 * data on the console.
 * See readme for useful reference.
 *
 * This file MUST be compiled as 32 BIT!
 */

#include "helpers_32bit.h"
#include "video32bit.h"

#define TEXT_ROWS 25
#define TEXT_COLS 80

#define FOREGROUND_COLOR (15 << 8)
#define BACKGROUND_COLOR (1 << 12)


/**
 * Memory location on video memory on x86 at startup.
 */
#define VIDEO_MEMORY 0xB8000
typedef short int video_array[TEXT_ROWS][TEXT_COLS];
video_array * const video_memory = (video_array * const)VIDEO_MEMORY;

/* Current position of the cursor */
int col, row;

void clear_screen()
{
    int i;
    col = 0; row = 0;
    for (i = 0; i != TEXT_ROWS * TEXT_COLS; ++i)
    {
        putc('\0');
    }
    col = 0; row = 0;
}

void putc(char c)
{
    (*video_memory)[row][col++] = FOREGROUND_COLOR | BACKGROUND_COLOR | c;
    if (col == TEXT_COLS)
    {
        col = 0;
        row = (row+1) % TEXT_ROWS;
    }
}

void printline(const char *str)
{
    while (*str != 0)
        putc(*(str++));
    
    if (col != 0)
        newline();
}

void newline()
{
    col = 0;
    row = (row+1) % TEXT_ROWS;
}
