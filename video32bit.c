/**
 * This file expose a set of function to print
 * data on the console.
 * See readme for useful reference.
 *
 * This file MUST be compiled as 32 BIT!
 */

#include "helpers_32bit.h"
#include "video32bit.h"
#include "io32.h"

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
    if (!str)
        return;

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

void disable_cursor()
{
    /**
     * The first command select the
     * "Cursor Start Register (Index 0Ah)"
     * and the second one disable the cursor
     *  http://www.osdever.net/FreeVGA/vga/crtcreg.htm#0A
     */
    outputb32(0x3D4, 0x0A);
	outputb32(0x3D5, 0x20);
}

void enable_cursor()
{
    /**
     * The first command select the
     * "Cursor Start Register (Index 0Ah)"
     * and the second one disable the cursor
     *  http://www.osdever.net/FreeVGA/vga/crtcreg.htm#0A
     */
    outputb32(0x3D4, 0x0A);
	outputb32(0x3D5, ((~0x20) & 0xe0 & inputb32(0x3D5)) | 12);

    outputb32(0x3D4, 0x0B);
	outputb32(0x3D5, (0xe0 & inputb32(0x3D5)) | 15);
}

/**
 * @brief Move the cursor to the given position.
 * Note: cursor will not be automatically enabled!
 *
 * An example of this function can be foundgere:
 *  http://kernelx.weebly.com/text-console.html
 * @param row 
 * @param col 
 */
void move_cursor(int row, int col)
{
    unsigned short position = (unsigned short) row*TEXT_COLS + col;

    /* Check console boundaries */
    if (!(0 <= col && col < TEXT_COLS) || !(0 <= row && row < TEXT_ROWS))
    {
        return;
    }

	outputb32(0x3D4, 0x0f);
	outputb32(0x3D5, (unsigned char)position & 0xff);
 
	outputb32(0x3D4, 0x0e);
	outputb32(0x3D5, (unsigned char)(position >> 8) & 0xff);
}
