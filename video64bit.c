/**
 * This file expose a set of function to print
 * data on the console.
 * See readme for useful reference.
 *
 * This file MUST be compiled as 64 BIT!
 */

#include "video64bit.h"
#include "io64.h"
#include "string64.h"

#define TEXT_ROWS 25
#define TEXT_COLS 80

static int FOREGROUND_COLOR = (15 << 8);
static int BACKGROUND_COLOR = (1 << 12);


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

void clear_screen64()
{
    int i;
    col = 0; row = 0;
    for (i = 0; i != TEXT_ROWS * TEXT_COLS; ++i)
    {
        putc64('\0');
    }
    col = 0; row = 0;
}

void putc64(char c)
{
    (*video_memory)[row][col++] = FOREGROUND_COLOR | BACKGROUND_COLOR | c;
    if (col == TEXT_COLS)
    {
        col = 0;
        row = (row+1) % TEXT_ROWS;
    }
    move_cursor64(row, col);
}

void puti64(int n)
{
    putstr64(itoa64(n));
}

void putu64(unsigned n)
{
    putstr64(ltoa64((long)n));
}

void putl64(long n)
{
    putstr64(ltoa64(n));
}

void putlu64(unsigned long n)
{
    putstr64(ultoa64(n));
}

void puthex64(unsigned long n)
{
    putstr64(hex64(n));
}

void putstr64(const char *str)
{
    if (!str)
        return;

    while (*str != 0)
        putc64(*(str++));
}

void printline64(const char *str)
{
    if (!str)
        return;

    while (*str != 0)
        putc64(*(str++));
    
    if (col != 0)
        newline64();
}

void newline64()
{
    col = 0;
    row = (row+1) % TEXT_ROWS;
}

void disable_cursor64()
{
    /**
     * The first command select the
     * "Cursor Start Register (Index 0Ah)"
     * and the second one disable the cursor
     *  http://www.osdever.net/FreeVGA/vga/crtcreg.htm#0A
     */
    outputb64(0x3D4, 0x0A);
	outputb64(0x3D5, 0x20);
}

void enable_cursor64()
{
    /**
     * The first command select the
     * "Cursor Start Register (Index 0Ah)"
     * and the second one disable the cursor
     *  http://www.osdever.net/FreeVGA/vga/crtcreg.htm#0A
     */
    outputb64(0x3D4, 0x0A);
	outputb64(0x3D5, ((~0x20) & 0xe0 & inputb64(0x3D5)) | 12);

    outputb64(0x3D4, 0x0B);
	outputb64(0x3D5, (0xe0 & inputb64(0x3D5)) | 15);
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
void move_cursor64(int row, int col)
{
    unsigned short position = (unsigned short) row*TEXT_COLS + col;

    /* Check console boundaries */
    if (!(0 <= col && col < TEXT_COLS) || !(0 <= row && row < TEXT_ROWS))
    {
        return;
    }

	outputb64(0x3D4, 0x0f);
	outputb64(0x3D5, (unsigned char)position & 0xff);
 
	outputb64(0x3D4, 0x0e);
	outputb64(0x3D5, (unsigned char)(position >> 8) & 0xff);
}

int get_foreground_color()
{
    return FOREGROUND_COLOR >> 8;
}

int set_foreground_color(int fc)
{
    int old = get_foreground_color();
    FOREGROUND_COLOR = (fc & 15) << 8;
    return old;
}

int get_background_color(void)
{
    return BACKGROUND_COLOR >> 12;
}

int set_background_color(int bc)
{
    int old = get_background_color();
    BACKGROUND_COLOR = (bc & 7) << 8;
    return old;
}
