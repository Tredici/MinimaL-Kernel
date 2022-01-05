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
#include "string32.h"

#define TEXT_ROWS 25
#define TEXT_COLS 80

#define FOREGROUND_COLOR (15 << 8)
#define BACKGROUND_COLOR (1 << 12)


/**
 * Memory location on video memory on x86 at startup.
 */
#define VIDEO_MEMORY 0xB8000
typedef short int video_array[TEXT_ROWS][TEXT_COLS];
static video_array * const video_memory = (video_array * const)VIDEO_MEMORY;

/* Current position of the cursor */
static int col, row;

static inline void next_position(int *row, int *col)
{
    if (!row || !col)
    {
        return;
    }

    if (!(0 <= *col && *col < TEXT_COLS) || !(0 <= *row && *row < TEXT_ROWS))
    {
        return;
    }

    if (++*col == TEXT_COLS)
    {
        *col = 0;
        *row = (1 + *row) % TEXT_ROWS;
    }
}

void clear_screen32()
{
    int i;
    col = 0; row = 0;
    for (i = 0; i != TEXT_ROWS * TEXT_COLS; ++i)
    {
        putc32('\0');
    }
    col = 0; row = 0;
}

void putc32(char c)
{
    (*video_memory)[row][col++] = FOREGROUND_COLOR | BACKGROUND_COLOR | c;
    if (col == TEXT_COLS)
    {
        col = 0;
        row = (row+1) % TEXT_ROWS;
    }
    move_cursor32(row, col);
}

void puti32(int n)
{
    putstr32(itoa32(n));
}

void putstr32(const char *str)
{
    if (!str)
        return;

    while (*str != 0)
        putc32(*(str++));
}

void printline32(const char *str)
{
    if (!str)
        return;

    while (*str != 0)
        putc32(*(str++));
    
    if (col != 0)
        newline32();
}

void newline32()
{
    col = 0;
    row = (row+1) % TEXT_ROWS;
}

void disable_cursor32()
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

void enable_cursor32()
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
void move_cursor32(int row, int col)
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
