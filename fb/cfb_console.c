/*
 * (C) Copyright 2002 ELTEC Elektronik AG
 * Frank Gottschling <fgottschling@eltec.de>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * cfb_console.c
 *
 * Color Framebuffer Console driver for 8/15/16/24/32 bits per pixel.
 *
 * At the moment only the 8x16 font is tested and the font fore- and
 * background color is limited to black/white/gray colors. The Linux
 * logo can be placed in the upper left corner and additional board
 * information strings (that normaly goes to serial port) can be drawed.
 *
 * The console driver can use the standard PC keyboard interface (i8042)
 * for character input. Character output goes to a memory mapped video
 * framebuffer with little or big-endian organisation.
 * With environment setting 'console=serial' the console i/o can be
 * forced to serial port.

 The driver uses graphic specific defines/parameters/functions:

 (for SMI LynxE graphic chip)

 CONFIG_VIDEO_SMI_LYNXEM - use graphic driver for SMI 710,712,810
 VIDEO_FB_LITTLE_ENDIAN  - framebuffer organisation default: big endian
 VIDEO_HW_RECTFILL   - graphic driver supports hardware rectangle fill
 VIDEO_HW_BITBLT     - graphic driver supports hardware bit blt

 Console Parameters are set by graphic drivers global struct:

 VIDEO_VISIBLE_COLS      - x resolution
 VIDEO_VISIBLE_ROWS      - y resolution
 VIDEO_PIXEL_SIZE        - storage size in byte per pixel
 VIDEO_DATA_FORMAT       - graphical data format GDF
 VIDEO_FB_ADRS           - start of video memory

 CONFIG_I8042_KBD        - AT Keyboard driver for i8042
 VIDEO_KBD_INIT_FCT      - init function for keyboard
 VIDEO_TSTC_FCT          - keyboard_tstc function
 VIDEO_GETC_FCT          - keyboard_getc function

 CONFIG_CONSOLE_CURSOR       - on/off drawing cursor is done with delay
                   loop in VIDEO_TSTC_FCT (i8042)
 CFG_CONSOLE_BLINK_COUNT     - value for delay loop - blink rate
 CONFIG_CONSOLE_TIME         - display time/date in upper right corner,
                   needs CFG_CMD_DATE and CONFIG_CONSOLE_CURSOR
 CONFIG_VIDEO_LOGO       - display Linux Logo in upper left corner
 CONFIG_VIDEO_BMP_LOGO       - use bmp_logo instead of linux_logo
 CONFIG_CONSOLE_EXTRA_INFO   - display additional board information strings
                   that normaly goes to serial port. This define
                   requires a board specific function:
                   video_drawstring (VIDEO_INFO_X,
                         VIDEO_INFO_Y + i*VIDEO_FONT_HEIGHT,
                         info);
                   that fills a info buffer at i=row.
                   s.a: board/eltec/bab7xx.
CONFIG_VGA_AS_SINGLE_DEVICE  - If set the framebuffer device will be initialised
                   as an output only device. The Keyboard driver
                   will not be set-up. This may be used, if you
                   have none or more than one Keyboard devices
                   (USB Keyboard, AT Keyboard).

CONFIG_VIDEO_SW_CURSOR:      - Draws a cursor after the last character. No
                   blinking is provided. Uses the macros CURSOR_SET
                   and CURSOR_OFF.
CONFIG_VIDEO_HW_CURSOR:      - Uses the hardware cursor capability of the
                   graphic chip. Uses the macro CURSOR_SET.
                   ATTENTION: If booting an OS, the display driver
                   must disable the hardware register of the graphic
                   chip. Otherwise a blinking field is displayed
*/

/************************************************************************

 Copyright (C)
 File name:     cfb_console.c
 Author:  ***      Version:  ***      Date: ***
 Description:   
 Others:        
 Function List:
 
 Revision History:
 
 --------------------------------------------------------------------------
  Date                Author            Activity ID               Activity Headline
  2008-05-17    Zhouhe          PMON20080517    disableoutput() enableoutput() added,cursor bug fixed.
  2009-07-17   QianYuli          PMON20090202     Modified for implement of BIOS-LIKE function
*************************************************************************/

#define SOFTWARECURSOR	219

/******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <pmon.h>
#include <cpu.h>
#include "mod_sisfb.h"
#include <dev/pci/pcivar.h>
#include <linux/io.h>


#if defined(LOONGSON2F_ALLINONE) || defined(LOONGSON3A_3A780E)||defined(LOONGSON3A_3AITX)
#define PICBMP_START_ADDR 0xbfc70000
#else
#define PICBMP_START_ADDR 0xbfc60000
#endif

/* radeon7000 micro define */
#ifdef RADEON7000
#define CONFIG_VIDEO_SW_CURSOR
#define CONFIG_SPLASH_SCREEN
#define CONFIG_VIDEO_BMP_GZIP
#define VIDEO_HW_BITBLT
#endif

#ifdef RS780E
#define CONFIG_SPLASH_SCREEN
#define CONFIG_VIDEO_BMP_GZIP
#endif

#if !defined(LOONGSON3A_3AEV)&&!defined(LOONGSON2G_2G690E)&&!defined(LOONGSON3A_3A780E)&&!defined(LOONGSON3A_3AITX)
#ifdef VESAFB
#define CONFIG_SPLASH_SCREEN
#define CONFIG_VIDEO_BMP_GZIP
#define VIDEO_HW_BITBLT             // video hw bitblt 2d acceleration config
#endif
#ifdef NMOD_SISFB
#define CONFIG_SPLASH_SCREEN        // video splash(image) config
#define CONFIG_VIDEO_BMP_GZIP       // video bmp image (un)compression config
#define VIDEO_HW_BITBLT             // video hw bitblt 2d acceleration config
#define VIDEO_HW_RECTFILL           // video hw fillrect 2d acceleration config
#endif
#endif

#ifdef SIS315E
#endif
/* sm712 micro define */
#ifdef  SM712_GRAPHIC_CARD
#define CONFIG_SPLASH_SCREEN        // video splash(image) config
#define CONFIG_VIDEO_BMP_GZIP       // video bmp image (un)compression config
#define VIDEO_HW_BITBLT             // video hw bitblt 2d acceleration config
#define VIDEO_HW_RECTFILL           // video hw fillrect 2d acceleration config
#endif

#ifdef SMI502
#define CONFIG_SPLASH_SCREEN        // video splash(image) config
#define CONFIG_VIDEO_BMP_GZIP       // video bmp image (un)compression config
#define VIDEO_HW_BITBLT             // video hw bitblt 2d acceleration config
#define VIDEO_HW_RECTFILL           // video hw fillrect 2d acceleration config
#endif



#ifdef CONFIG_SPLASH_SCREEN
#ifdef LOONGSON2F_7INCH
#include "bmp_pic.h"
#endif
#endif

/*****************************************************************************/
/* Include video_fb.h after definitions of VIDEO_HW_RECTFILL etc         */
/*****************************************************************************/
#include "video_fb.h"

/*****************************************************************************/
/* some Macros                                   */
/*****************************************************************************/
#define VIDEO_VISIBLE_COLS  (pGD->winSizeX)
#define VIDEO_VISIBLE_ROWS  (pGD->winSizeY)
#define VIDEO_PIXEL_SIZE    (pGD->gdfBytesPP)
#define VIDEO_DATA_FORMAT   (pGD->gdfIndex)
#define VIDEO_FB_ADRS       (pGD->frameAdrs)

#define VIDEO_COLS      VIDEO_VISIBLE_COLS
#define VIDEO_ROWS      VIDEO_VISIBLE_ROWS
#define VIDEO_SIZE      (VIDEO_ROWS*VIDEO_COLS*VIDEO_PIXEL_SIZE)
#define VIDEO_PIX_BLOCKS    (VIDEO_SIZE >> 2)
#define VIDEO_LINE_LEN      (VIDEO_COLS*VIDEO_PIXEL_SIZE)
#define VIDEO_BURST_LEN     (VIDEO_COLS/8)

/*****************************************************************************/
/* Console device defines with i8042 keyboard controller             */
/* Any other keyboard controller must change this section            */
/*****************************************************************************/

#ifdef  CONFIG_I8042_KBD
#include <i8042.h>

#define VIDEO_KBD_INIT_FCT  i8042_kbd_init()
#define VIDEO_TSTC_FCT      i8042_tstc
#define VIDEO_GETC_FCT      i8042_getc
#endif

/*****************************************************************************/
/* Console device                                */
/*****************************************************************************/

#include "video_font.h"
#include "video_font_cn.h"//07-17
#ifdef CFG_CMD_DATE
#include <rtc.h>
#endif

#if (CONFIG_COMMANDS & CFG_CMD_BMP) || defined(CONFIG_SPLASH_SCREEN)
#include "bmp_layout.h"
#endif              /* (CONFIG_COMMANDS & CFG_CMD_BMP) || CONFIG_SPLASH_SCREEN */

/*****************************************************************************/
/* Cursor definition:                                */
/* CONFIG_CONSOLE_CURSOR:  Uses a timer function (see drivers/i8042.c) to    */
/*             let the cursor blink. Uses the macros CURSOR_OFF  */
/*             and CURSOR_ON.                    */
/* CONFIG_VIDEO_SW_CURSOR: Draws a cursor after the last character. No       */
/*             blinking is provided. Uses the macros CURSOR_SET  */
/*             and CURSOR_OFF.                   */
/* CONFIG_VIDEO_HW_CURSOR: Uses the hardware cursor capability of the        */
/*             graphic chip. Uses the macro CURSOR_SET.      */
/*             ATTENTION: If booting an OS, the display driver   */
/*             must disable the hardware register of the graphic */
/*             chip. Otherwise a blinking field is displayed     */
/*****************************************************************************/
#if !defined(CONFIG_CONSOLE_CURSOR) && \
    !defined(CONFIG_VIDEO_SW_CURSOR) && \
    !defined(CONFIG_VIDEO_HW_CURSOR)
/* no Cursor defined */
#define CURSOR_ON
#define CURSOR_OFF
#define CURSOR_SET
#endif

#ifdef  CONFIG_CONSOLE_CURSOR
#ifdef  CURSOR_ON
#error  only one of CONFIG_CONSOLE_CURSOR,CONFIG_VIDEO_SW_CURSOR,CONFIG_VIDEO_HW_CURSOR can be defined
#endif
void console_cursor(int state);
#define CURSOR_ON  console_cursor(1);
#define CURSOR_OFF console_cursor(0);
#define CURSOR_SET
#ifndef CONFIG_I8042_KBD
#warning Cursor drawing on/off needs timer function s.a. drivers/i8042.c
#endif
#else
#ifdef  CONFIG_CONSOLE_TIME
#error  CONFIG_CONSOLE_CURSOR must be defined for CONFIG_CONSOLE_TIME
#endif
#endif              /* CONFIG_CONSOLE_CURSOR */

#ifdef  CONFIG_VIDEO_SW_CURSOR
#ifdef  CURSOR_ON
#error  only one of CONFIG_CONSOLE_CURSOR,CONFIG_VIDEO_SW_CURSOR,CONFIG_VIDEO_HW_CURSOR can be defined
#endif
#define CURSOR_ON
#define CURSOR_OFF video_putchar(console_col * VIDEO_FONT_WIDTH,\
                 console_row * VIDEO_FONT_HEIGHT, ' ');
#define CURSOR_SET video_set_cursor();
#endif              /* CONFIG_VIDEO_SW_CURSOR */

#ifdef CONFIG_VIDEO_HW_CURSOR
#ifdef  CURSOR_ON
#error  only one of CONFIG_CONSOLE_CURSOR,CONFIG_VIDEO_SW_CURSOR,CONFIG_VIDEO_HW_CURSOR can be defined
#endif
#define CURSOR_ON
#define CURSOR_OFF
#define CURSOR_SET video_set_hw_cursor(console_col * VIDEO_FONT_WIDTH, \
          (console_row * VIDEO_FONT_HEIGHT) + VIDEO_LOGO_HEIGHT);
#endif              /* CONFIG_VIDEO_HW_CURSOR */

#ifdef  CONFIG_VIDEO_LOGO
#ifdef  CONFIG_VIDEO_BMP_LOGO
#include "bmp_logo.h"
#define VIDEO_LOGO_WIDTH    BMP_LOGO_WIDTH
#define VIDEO_LOGO_HEIGHT   BMP_LOGO_HEIGHT
#define VIDEO_LOGO_LUT_OFFSET   BMP_LOGO_OFFSET
#define VIDEO_LOGO_COLORS   BMP_LOGO_COLORS
#else   /* CONFIG_VIDEO_BMP_LOGO */
#define LINUX_LOGO_WIDTH    80
#define LINUX_LOGO_HEIGHT   80
#define LINUX_LOGO_COLORS   214
#define LINUX_LOGO_LUT_OFFSET   0x20
#define __initdata
#include "linux_logo.h"
#define VIDEO_LOGO_WIDTH    LINUX_LOGO_WIDTH
#define VIDEO_LOGO_HEIGHT   LINUX_LOGO_HEIGHT
#define VIDEO_LOGO_LUT_OFFSET   LINUX_LOGO_LUT_OFFSET
#define VIDEO_LOGO_COLORS   LINUX_LOGO_COLORS
#endif  /* CONFIG_VIDEO_BMP_LOGO */

#define VIDEO_INFO_X        (VIDEO_LOGO_WIDTH)
#define VIDEO_INFO_Y        (VIDEO_FONT_HEIGHT/2)
#else   /* CONFIG_VIDEO_LOGO */

#define VIDEO_LOGO_WIDTH    0
#define VIDEO_LOGO_HEIGHT   0

#endif  /* CONFIG_VIDEO_LOGO */


#ifdef  CONFIG_VIDEO_LOGO
#define CONSOLE_ROWS        ((VIDEO_ROWS - VIDEO_LOGO_HEIGHT) / VIDEO_FONT_HEIGHT)
#else
#define CONSOLE_ROWS        (VIDEO_ROWS / VIDEO_FONT_HEIGHT)
#endif

#define CONSOLE_COLS        (VIDEO_COLS / VIDEO_FONT_WIDTH)
#define CONSOLE_ROW_SIZE    (VIDEO_FONT_HEIGHT * VIDEO_LINE_LEN)
#define CONSOLE_ROW_FIRST   (video_console_address)
#define CONSOLE_ROW_SECOND  (video_console_address + CONSOLE_ROW_SIZE)
#define CONSOLE_SIZE        (CONSOLE_ROW_SIZE * CONSOLE_ROWS)
#define CONSOLE_ROW_LAST    (video_console_address + CONSOLE_SIZE - CONSOLE_ROW_SIZE)
#define CONSOLE_SCROLL_SIZE (CONSOLE_SIZE - CONSOLE_ROW_SIZE)
/*
#ifdef LOONGSON2F_7INCH
#if     1
char console_buffer[2][38][128] = { 32 };   // 128x37.5 for 1024X600@16BPP LCD
#else
char console_buffer[2][31][101] = { 32 };   // 100X30
#endif
#else
char console_buffer[2][40][101] = { 32 };   // 80X24
*/
#if defined(X640x480)
char console_buffer[2][31][81]={32};//80*30->640x480
#elif defined(X800x600)
char console_buffer[2][38][101]={32};//
#elif defined(X1024x600)
char console_buffer[2][38][128]={32};//
#elif defined(X1024x768)
char console_buffer[2][49][129]={32};//128*48->1024x768
#elif defined(X1368x768)
//char console_buffer[2][49][172]={32};//171*48->1368x768
char console_buffer[2][49][172];//171*48->1368x768
#else
char console_buffer[2][31][81]={32};//80*30->640x480
#endif



#define FB_SIZE ((pGD->winSizeX)*(pGD->winSizeY)*(pGD->gdfBytesPP))

/* Macros */
#ifdef  VIDEO_FB_LITTLE_ENDIAN
#define BYTESWAP32(x) 	(x)
#define SWAP16(x)    ((((x) & 0x00ff) << 8) | ( (x) >> 8))
#define SWAP32(x)    ((((x) & 0x000000ff) << 24) | (((x) & 0x0000ff00) << 8)|\
              (((x) & 0x00ff0000) >>  8) | (((x) & 0xff000000) >> 24) )
#define SHORTSWAP32(x)   ((((x) & 0x000000ff) <<  8) | (((x) & 0x0000ff00) >> 8)|\
              (((x) & 0x00ff0000) <<  8) | (((x) & 0xff000000) >> 8) )
#else
#define BYTESWAP32(x)    ((((x) & 0x000000ff) <<  24) | (((x) & 0x0000ff00) << 8)|\
                          (((x) & 0x00ff0000) >>  8) | (((x) & 0xff000000) >> 24) )
#define SWAP16(x)    (x)
#define SWAP32(x)    (x)
#define SHORTSWAP32(x)   (x)
#endif

#if defined(DEBUG) || defined(DEBUG_CFB_CONSOLE)
#define PRINTD(x)     printf(x)
#else
#define PRINTD(x)
#endif


#ifdef CONFIG_CONSOLE_EXTRA_INFO
extern void video_get_info_str( /* setup a board string: type, speed, etc. */
                      int line_number,  /* location to place info string beside logo */
                      char *info    /* buffer for info string */
    );

#endif

#ifdef SMI502
extern void AutodeCopyModify(int);
extern void AutodeFillRectModify(int);
extern int  deFillRectModify(unsigned long,unsigned long , unsigned long , unsigned long , unsigned long ,unsigned long);
#endif

extern int gunzip(void *, int , unsigned char *, unsigned long *);
;


/* Locals */
static GraphicDevice *pGD, GD;  /* Pointer to Graphic array */

static void *video_fb_address;  /* frame buffer address */
static void *video_console_address; /* console buffer start address */

#ifndef VIDEO_HW_BITBLT
#ifndef MEM_PRINTTO_VIDEO
#define MEM_PRINTTO_VIDEO
static char *memfb;
#endif
#endif
static int console_col = 0; /* cursor col */
static int console_row = 0; /* cursor row */

//static unsigned int eorx, fgx, bgx; /* color pats */
unsigned int eorx, fgx, bgx; /* color pats *///07-17
static const char video_font_draw_table2[] = {
            0x00, 0x03, 0x0c, 0x0f, 
	    0x30, 0x33, 0x3c, 0x3f,
	    0xc0, 0xc3, 0xcc, 0xcf,
	    0xf0, 0xf3, 0xfc, 0xff};
static const char video_font_draw_table4[] = {
            0x00, 0x0f, 0xf0, 0xff};
#if 0
static const int video_font_draw_table8[] = {
    0x00000000, 0x000000ff, 0x0000ff00, 0x0000ffff,
    0x00ff0000, 0x00ff00ff, 0x00ffff00, 0x00ffffff,
    0xff000000, 0xff0000ff, 0xff00ff00, 0xff00ffff,
    0xffff0000, 0xffff00ff, 0xffffff00, 0xffffffff
};
#else
static const int video_font_draw_table8[] = {
    0x00000000, 0xff000000, 0x00ff0000, 0xffff0000,
    0x0000ff00, 0xff00ff00, 0x00ffff00, 0xffffff00,
    0x000000ff, 0xff0000ff, 0x00ff00ff, 0xffff00ff,
    0x0000ffff, 0xff00ffff, 0x00ffffff, 0xffffffff
};
#endif

static const int video_font_draw_table15[] = {
    0x00000000, 0x00007fff, 0x7fff0000, 0x7fff7fff
};

static const int video_font_draw_table16[] = {
    0x00000000, 0xffff0000, 0x0000ffff, 0xffffffff
};

static const int video_font_draw_table24[16][3] = {
    {0x00000000, 0x00000000, 0x00000000},
    {0x00000000, 0x00000000, 0x00ffffff},
    {0x00000000, 0x0000ffff, 0xff000000},
    {0x00000000, 0x0000ffff, 0xffffffff},
    {0x000000ff, 0xffff0000, 0x00000000},
    {0x000000ff, 0xffff0000, 0x00ffffff},
    {0x000000ff, 0xffffffff, 0xff000000},
    {0x000000ff, 0xffffffff, 0xffffffff},
    {0xffffff00, 0x00000000, 0x00000000},
    {0xffffff00, 0x00000000, 0x00ffffff},
    {0xffffff00, 0x0000ffff, 0xff000000},
    {0xffffff00, 0x0000ffff, 0xffffffff},
    {0xffffffff, 0xffff0000, 0x00000000},
    {0xffffffff, 0xffff0000, 0x00ffffff},
    {0xffffffff, 0xffffffff, 0xff000000},
    {0xffffffff, 0xffffffff, 0xffffffff}
};

static const int video_font_draw_table32[16][4] = {
    {0x00000000, 0x00000000, 0x00000000, 0x00000000},
    {0x00000000, 0x00000000, 0x00000000, 0x00ffffff},
    {0x00000000, 0x00000000, 0x00ffffff, 0x00000000},
    {0x00000000, 0x00000000, 0x00ffffff, 0x00ffffff},
    {0x00000000, 0x00ffffff, 0x00000000, 0x00000000},
    {0x00000000, 0x00ffffff, 0x00000000, 0x00ffffff},
    {0x00000000, 0x00ffffff, 0x00ffffff, 0x00000000},
    {0x00000000, 0x00ffffff, 0x00ffffff, 0x00ffffff},
    {0x00ffffff, 0x00000000, 0x00000000, 0x00000000},
    {0x00ffffff, 0x00000000, 0x00000000, 0x00ffffff},
    {0x00ffffff, 0x00000000, 0x00ffffff, 0x00000000},
    {0x00ffffff, 0x00000000, 0x00ffffff, 0x00ffffff},
    {0x00ffffff, 0x00ffffff, 0x00000000, 0x00000000},
    {0x00ffffff, 0x00ffffff, 0x00000000, 0x00ffffff},
    {0x00ffffff, 0x00ffffff, 0x00ffffff, 0x00000000},
    {0x00ffffff, 0x00ffffff, 0x00ffffff, 0x00ffffff}
};

unsigned short pallete[16] = {
    SWAP16((unsigned short)(((0 >> 3) << 11) | ((0 >> 2) << 5) | (0 >> 3))),
    SWAP16((unsigned short)(((0 >> 3) << 11) | ((0 >> 2) << 5) |
                (128 >> 3))),
    SWAP16((unsigned short)(((0 >> 3) << 11) | ((128 >> 2) << 5) |
                (0 >> 3))),
    SWAP16((unsigned short)(((0 >> 3) << 11) | ((128 >> 2) << 5) |
                (128 >> 3))),
    SWAP16((unsigned short)(((128 >> 3) << 11) | ((0 >> 2) << 5) |
                (0 >> 3))),
    SWAP16((unsigned short)(((128 >> 3) << 11) | ((0 >> 2) << 5) |
                (128 >> 3))),
    SWAP16((unsigned short)(((128 >> 3) << 11) | ((128 >> 2) << 5) |
                (0 >> 3))),
    SWAP16((unsigned short)(((0xc0 >> 3) << 11) | ((0xc0 >> 2) << 5) |
                (0xc0 >> 3))),
    SWAP16((unsigned short)(((128 >> 3) << 11) | ((128 >> 2) << 5) |
                (128 >> 3))),
    SWAP16((unsigned short)(((0 >> 3) << 11) | ((0 >> 2) << 5) |
                (255 >> 3))),
    SWAP16((unsigned short)(((0 >> 3) << 11) | ((255 >> 2) << 5) |
                (0 >> 3))),
    SWAP16((unsigned short)(((0 >> 3) << 11) | ((255 >> 2) << 5) |
                (255 >> 3))),
    SWAP16((unsigned short)(((255 >> 3) << 11) | ((0 >> 2) << 5) |
                (0 >> 3))),
    SWAP16((unsigned short)(((255 >> 3) << 11) | ((0 >> 2) << 5) |
                (255 >> 3))),
    SWAP16((unsigned short)(((255 >> 3) << 11) | ((255 >> 2) << 5) |
                (0 >> 3))),
    SWAP16((unsigned short)(((255 >> 3) << 11) | ((255 >> 2) << 5) |
                (255 >> 3)))
};

unsigned long pallete_32[16] = {
    (0 << 16) | (0 << 8) | 0,
    (0 << 16) | (0 << 8) | 128,
    (0 << 16) | (128 << 8) | 0,
    (0 << 16) | (128 << 8) | 128,
    (128 << 16) | (0 << 8) | 0,
    (128 << 16) | (0 << 8) | 128,
    (128 << 16) | (128 << 8) | 0,
    (0xc0 << 16) | (0xc0 << 8) | 0xc0,
    (128 << 16) | (128 << 8) | 128,
    (0 << 16) | (0 << 8) | 255,
    (0 << 16) | (255 << 8) | 0,
    (0 << 16) | (255 << 8) | 255,
    (255 << 16) | (0 << 8) | 0,
    (255 << 16) | (0 << 8) | 255,
    (255 << 16) | (255 << 8) | 0,
    (255 << 16) | (255 << 8) | 255
};

extern int vga_available;
int *saved_frame_buffer;

// GDF_16BIT_565RGB
#define R_MASK 0xf800f800
#define G_MASK 0x07e007e0
#define B_MASK 0x001f001f
//031
#define ALPHA_VALUE 10
/*
result = A * Alpha + B * ( 1-Alpha )
->
result = ( A * Alpha + B * ( 32-Alpha ) ) / 32������Alpha < 32
->
result = ( ( A-B ) * Alpha ) >> 5 + B
*/

void alpha_blend(unsigned int *fb, unsigned int target)
{
    unsigned int fbtarget;
    unsigned int result, R1, R2, G1, G2, B1, B2;
    fbtarget =
        saved_frame_buffer[((unsigned)fb -
                (unsigned)video_fb_address) >> 2];

    //result = ((fbtarget - target) * 16) >> 5 + target;
    R1 = (fbtarget & R_MASK) >> 11, R2 = (target & R_MASK) >> 11;
    G1 = (fbtarget & G_MASK) >> 5, G2 = (target & G_MASK) >> 5;
    B1 = (fbtarget & B_MASK), B2 = (target & B_MASK);

    result = (((((R1 - R2) * 10) >> 5) + R2) << 11) & R_MASK;
    result |= (((((G1 - G2) * 10) >> 5) + G2) << 5) & G_MASK;
    result |= ((((B1 - B2) * 10) >> 5) + B2) & B_MASK;

    *fb = result;
}
void alpha_blend_fb(void)
{
    unsigned int size = FB_SIZE / 4;
    unsigned int i;
    unsigned int result, R1, R2, G1, G2, B1, B2;
    unsigned int target, fbtarget;

    for (i = 0; i < size; i++) {
        fbtarget = saved_frame_buffer[i];
        target = ((unsigned int *)video_fb_address)[i];

        //result = ((fbtarget - target) * 16) >> 5 + target;
        R1 = (fbtarget & R_MASK) >> 11, R2 = (target & R_MASK) >> 11;
        G1 = (fbtarget & G_MASK) >> 5, G2 = (target & G_MASK) >> 5;
        B1 = (fbtarget & B_MASK), B2 = (target & B_MASK);

        result = (((((R1 - R2) * 10) >> 5) + R2) << 11) & R_MASK;
        result |= (((((G1 - G2) * 10) >> 5) + G2) << 5) & G_MASK;
        result |= ((((B1 - B2) * 10) >> 5) + B2) & B_MASK;

        *(unsigned int *)video_fb_address = result;
    }
}

//2009-07-17
static int disableoutput=0;
void video_disableoutput(void)
{
    disableoutput=1;
}
void video_enableoutput(void)
{
    disableoutput=0;
}
void video_drawchars_xor (int xx, int yy, unsigned char *s, int count)
{
    unsigned char *cdat, *dest, *dest0;
    int rows, offset, c;
	int i;
    
    if(disableoutput)return;
    
    offset = yy * VIDEO_LINE_LEN + xx * VIDEO_PIXEL_SIZE;
    dest0 = video_fb_address + offset;

    switch (VIDEO_DATA_FORMAT) {
	case GDF__1BIT:
		while (count--) {
			c = *s;
			cdat = video_fontdata + c * VIDEO_FONT_HEIGHT;
			for (i=0;i<VIDEO_FONT_HEIGHT;i++)
			{
				offset = ((yy+i)*(VIDEO_VISIBLE_COLS) + xx)/8;
				*(unsigned char *)(video_fb_address + offset)=((unsigned char *)cdat)[i];
			}
			s++;
		}
		break;
    case GDF__8BIT_INDEX:
    case GDF__8BIT_332RGB:
        while (count--) {
            c = *s;
            cdat = video_fontdata + c * VIDEO_FONT_HEIGHT;
            for (rows = VIDEO_FONT_HEIGHT, dest = dest0;
                 rows--;
                 dest += VIDEO_LINE_LEN) {
                unsigned char bits = *cdat++;

				((unsigned int *) dest)[0] ^= BYTESWAP32((video_font_draw_table8[bits >> 4] & eorx) ^ bgx);
				((unsigned int *) dest)[1] ^= BYTESWAP32((video_font_draw_table8[bits & 15] & eorx) ^ bgx);
            }
            dest0 += VIDEO_FONT_WIDTH * VIDEO_PIXEL_SIZE;
            s++;
        }
        break;

    case GDF_15BIT_555RGB:
        while (count--) {
            c = *s;
            cdat = video_fontdata + c * VIDEO_FONT_HEIGHT;
            for (rows = VIDEO_FONT_HEIGHT, dest = dest0;
                 rows--;
                 dest += VIDEO_LINE_LEN){
                unsigned char bits = *cdat++;

                ((unsigned int *) dest)[0] ^= SHORTSWAP32 ((video_font_draw_table15 [bits >> 6] & eorx) ^ bgx);
                ((unsigned int *) dest)[1] ^= SHORTSWAP32 ((video_font_draw_table15 [bits >> 4 & 3] & eorx) ^ bgx);
                ((unsigned int *) dest)[2] ^= SHORTSWAP32 ((video_font_draw_table15 [bits >> 2 & 3] & eorx) ^ bgx);
                ((unsigned int *) dest)[3] ^= SHORTSWAP32 ((video_font_draw_table15 [bits & 3] & eorx) ^ bgx);
            }
            dest0 += VIDEO_FONT_WIDTH * VIDEO_PIXEL_SIZE;
            s++;
        }
        break;

    //here
    case GDF_16BIT_565RGB:
        while (count--) {
            c = *s;
            cdat = video_fontdata + c * VIDEO_FONT_HEIGHT;
            for (rows = VIDEO_FONT_HEIGHT, dest = dest0;
                 rows--;
                 dest += VIDEO_LINE_LEN) {
                unsigned char bits = *cdat++;

                ((unsigned int *) dest)[0] ^= SHORTSWAP32 ((video_font_draw_table16 [bits >> 6] & eorx) ^ bgx);
                ((unsigned int *) dest)[1] ^= SHORTSWAP32 ((video_font_draw_table16 [bits >> 4 & 3] & eorx) ^ bgx);
                ((unsigned int *) dest)[2] ^= SHORTSWAP32 ((video_font_draw_table16 [bits >> 2 & 3] & eorx) ^ bgx);
                ((unsigned int *) dest)[3] ^= SHORTSWAP32 ((video_font_draw_table16 [bits & 3] & eorx) ^ bgx);
            }
            dest0 += VIDEO_FONT_WIDTH * VIDEO_PIXEL_SIZE;
            s++;
        }
        break;

    case GDF_32BIT_X888RGB:
        while (count--) {
            c = *s;
            cdat = video_fontdata + c * VIDEO_FONT_HEIGHT;
            for (rows = VIDEO_FONT_HEIGHT, dest = dest0;
                 rows--;
                 dest += VIDEO_LINE_LEN) {
                unsigned char bits = *cdat++;

                ((unsigned int *) dest)[0] ^= SWAP32 ((video_font_draw_table32 [bits >> 4][0] & eorx) ^ bgx);
                ((unsigned int *) dest)[1] ^= SWAP32 ((video_font_draw_table32 [bits >> 4][1] & eorx) ^ bgx);
                ((unsigned int *) dest)[2] ^= SWAP32 ((video_font_draw_table32 [bits >> 4][2] & eorx) ^ bgx);
                ((unsigned int *) dest)[3] ^= SWAP32 ((video_font_draw_table32 [bits >> 4][3] & eorx) ^ bgx);
                ((unsigned int *) dest)[4] ^= SWAP32 ((video_font_draw_table32 [bits & 15][0] & eorx) ^ bgx);
                ((unsigned int *) dest)[5] ^= SWAP32 ((video_font_draw_table32 [bits & 15][1] & eorx) ^ bgx);
                ((unsigned int *) dest)[6] ^= SWAP32 ((video_font_draw_table32 [bits & 15][2] & eorx) ^ bgx);
                ((unsigned int *) dest)[7] ^= SWAP32 ((video_font_draw_table32 [bits & 15][3] & eorx) ^ bgx);
            }
            dest0 += VIDEO_FONT_WIDTH * VIDEO_PIXEL_SIZE;
            s++;
        }
        break;

    case GDF_24BIT_888RGB:
        while (count--) {
            c = *s;
            cdat = video_fontdata + c * VIDEO_FONT_HEIGHT;
            for (rows = VIDEO_FONT_HEIGHT, dest = dest0;
                 rows--;
                 dest += VIDEO_LINE_LEN) {
                unsigned char bits = *cdat++;

                ((unsigned int *) dest)[0] ^= (video_font_draw_table24[bits >> 4][0] & eorx) ^ bgx;
                ((unsigned int *) dest)[1] ^= (video_font_draw_table24[bits >> 4][1] & eorx) ^ bgx;
                ((unsigned int *) dest)[2] ^= (video_font_draw_table24[bits >> 4][2] & eorx) ^ bgx;
                ((unsigned int *) dest)[3] ^= (video_font_draw_table24[bits & 15][0] & eorx) ^ bgx;
                ((unsigned int *) dest)[4] ^= (video_font_draw_table24[bits & 15][1] & eorx) ^ bgx;
                ((unsigned int *) dest)[5] ^= (video_font_draw_table24[bits & 15][2] & eorx) ^ bgx;
            }
            dest0 += VIDEO_FONT_WIDTH * VIDEO_PIXEL_SIZE;
            s++;
        }
        break;
    }
}


/******************************************************************************/
void video_drawchars(int xx, int yy, unsigned char *s, int count)
{
    unsigned char *cdat, *dest, *dest0;
    int rows, offset, c;
	int i;

    if(disableoutput)return;
    offset = yy * VIDEO_LINE_LEN + xx * VIDEO_PIXEL_SIZE;
    dest0 = video_fb_address + offset;

    switch (VIDEO_DATA_FORMAT) {
	case GDF__1BIT:
		while (count--) {
			c = *s;
			cdat = video_fontdata + c * VIDEO_FONT_HEIGHT;

			for (i=0;i<VIDEO_FONT_HEIGHT;i++)
			{
				offset = ((yy+i)*(VIDEO_VISIBLE_COLS) + xx)/8;
				*(unsigned char *)(video_fb_address + offset)=((unsigned char *)cdat)[i];
			}
			s++;
		}
		break;

	case GDF__2BIT:
		while (count--) {
			c = *s;
			cdat = video_fontdata + c * VIDEO_FONT_HEIGHT;

			for (i=0;i<VIDEO_FONT_HEIGHT;i++)
			{
				unsigned char bits = *cdat++;
				offset = ((yy+i)*(VIDEO_VISIBLE_COLS) + xx)/4;
				dest = (unsigned char *)(video_fb_address + offset);
				dest[0] = video_font_draw_table2[bits >> 4] ;
				dest[1] = video_font_draw_table2[bits & 15] ;
			}
			s++;
		}
		break;

	case GDF__4BIT:
		while (count--) {
			c = *s;
			cdat = video_fontdata + c * VIDEO_FONT_HEIGHT;
			for (i=0;i<VIDEO_FONT_HEIGHT;i++)
			{
				unsigned char bits = *cdat++;
				offset = ((yy+i)*(VIDEO_VISIBLE_COLS) + xx)/2;
				dest = (unsigned char *)(video_fb_address + offset);
				dest[0] = video_font_draw_table4[bits >> 6] ;
				dest[1] = video_font_draw_table4[bits >> 4 & 3] ;
				dest[2] = video_font_draw_table4[bits >> 2 & 3] ;
				dest[3] = video_font_draw_table4[bits & 3] ;
			}
			s++;
		}
		break;
    case GDF__8BIT_INDEX:
    case GDF__8BIT_332RGB:
        while (count--) {
            c = *s;
            cdat = video_fontdata + c * VIDEO_FONT_HEIGHT;
            for (rows = VIDEO_FONT_HEIGHT, dest = dest0;
			     rows--;
			     dest += VIDEO_LINE_LEN) {
				unsigned char bits = *cdat++;

				((unsigned int *) dest)[0] = BYTESWAP32((video_font_draw_table8[bits >> 4] & eorx) ^ bgx);
				((unsigned int *) dest)[1] = BYTESWAP32((video_font_draw_table8[bits & 15] & eorx) ^ bgx);
            }
            dest0 += VIDEO_FONT_WIDTH * VIDEO_PIXEL_SIZE;
            s++;
        }
        break;

    case GDF_15BIT_555RGB:
        while (count--) {
            c = *s;
            cdat = video_fontdata + c * VIDEO_FONT_HEIGHT;
            for (rows = VIDEO_FONT_HEIGHT, dest = dest0;
			     rows--;
			     dest += VIDEO_LINE_LEN){
				unsigned char bits = *cdat++;

				((unsigned int *) dest)[0] = SHORTSWAP32 ((video_font_draw_table15 [bits >> 6] & eorx) ^ bgx);
				((unsigned int *) dest)[1] = SHORTSWAP32 ((video_font_draw_table15 [bits >> 4 & 3] & eorx) ^ bgx);
				((unsigned int *) dest)[2] = SHORTSWAP32 ((video_font_draw_table15 [bits >> 2 & 3] & eorx) ^ bgx);
				((unsigned int *) dest)[3] = SHORTSWAP32 ((video_font_draw_table15 [bits & 3] & eorx) ^ bgx);
            }
            dest0 += VIDEO_FONT_WIDTH * VIDEO_PIXEL_SIZE;
            s++;
        }
        break;

        //here
    case GDF_16BIT_565RGB:
        while (count--) {
            c = *s;
            cdat = video_fontdata + c * VIDEO_FONT_HEIGHT;
            for (rows = VIDEO_FONT_HEIGHT, dest = dest0;
			     rows--;
			     dest += VIDEO_LINE_LEN) {
				unsigned char bits = *cdat++;

				((unsigned int *) dest)[0] = SHORTSWAP32 ((video_font_draw_table16 [bits >> 6] & eorx) ^ bgx);
				((unsigned int *) dest)[1] = SHORTSWAP32 ((video_font_draw_table16 [bits >> 4 & 3] & eorx) ^ bgx);
				((unsigned int *) dest)[2] = SHORTSWAP32 ((video_font_draw_table16 [bits >> 2 & 3] & eorx) ^ bgx);
				((unsigned int *) dest)[3] = SHORTSWAP32 ((video_font_draw_table16 [bits & 3] & eorx) ^ bgx);
            }
            dest0 += VIDEO_FONT_WIDTH * VIDEO_PIXEL_SIZE;
            s++;
        }
        break;

    case GDF_32BIT_X888RGB:
        while (count--) {
            c = *s;
            cdat = video_fontdata + c * VIDEO_FONT_HEIGHT;
            for (rows = VIDEO_FONT_HEIGHT, dest = dest0;
			     rows--;
			     dest += VIDEO_LINE_LEN) {
				unsigned char bits = *cdat++;

				((unsigned int *) dest)[0] = SWAP32 ((video_font_draw_table32 [bits >> 4][0] & eorx) ^ bgx);
				((unsigned int *) dest)[1] = SWAP32 ((video_font_draw_table32 [bits >> 4][1] & eorx) ^ bgx);
				((unsigned int *) dest)[2] = SWAP32 ((video_font_draw_table32 [bits >> 4][2] & eorx) ^ bgx);
				((unsigned int *) dest)[3] = SWAP32 ((video_font_draw_table32 [bits >> 4][3] & eorx) ^ bgx);
				((unsigned int *) dest)[4] = SWAP32 ((video_font_draw_table32 [bits & 15][0] & eorx) ^ bgx);
				((unsigned int *) dest)[5] = SWAP32 ((video_font_draw_table32 [bits & 15][1] & eorx) ^ bgx);
				((unsigned int *) dest)[6] = SWAP32 ((video_font_draw_table32 [bits & 15][2] & eorx) ^ bgx);
				((unsigned int *) dest)[7] = SWAP32 ((video_font_draw_table32 [bits & 15][3] & eorx) ^ bgx);
            }
            dest0 += VIDEO_FONT_WIDTH * VIDEO_PIXEL_SIZE;
            s++;
        }
        break;

    case GDF_24BIT_888RGB:
        while (count--) {
            c = *s;
            cdat = video_fontdata + c * VIDEO_FONT_HEIGHT;
            for (rows = VIDEO_FONT_HEIGHT, dest = dest0;
			     rows--;
			     dest += VIDEO_LINE_LEN) {
				unsigned char bits = *cdat++;

				((unsigned int *) dest)[0] = (video_font_draw_table24[bits >> 4][0] & eorx) ^ bgx;
				((unsigned int *) dest)[1] = (video_font_draw_table24[bits >> 4][1] & eorx) ^ bgx;
				((unsigned int *) dest)[2] = (video_font_draw_table24[bits >> 4][2] & eorx) ^ bgx;
				((unsigned int *) dest)[3] = (video_font_draw_table24[bits & 15][0] & eorx) ^ bgx;
				((unsigned int *) dest)[4] = (video_font_draw_table24[bits & 15][1] & eorx) ^ bgx;
				((unsigned int *) dest)[5] = (video_font_draw_table24[bits & 15][2] & eorx) ^ bgx;
            }
            dest0 += VIDEO_FONT_WIDTH * VIDEO_PIXEL_SIZE;
            s++;
        }
        break;
    }
}

/*****************************************************************************/
int getCNcode(unsigned char *gbcode)
{
    int low = 1, high = VIDEO_FONT_CN_CHARS;
    int mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if ( gbcode[0] == gbindex[mid][0] && gbcode[1] == gbindex[mid][1])
            return mid;
        else
            if ( (gbcode[0] < gbindex[mid][0]) || ((gbcode[0] == gbindex[mid][0]) && (gbcode[1] < gbindex[mid][1])) )
                high = mid - 1;
            else
                low = mid + 1;
    }
    return 0;
}

/*****************************************************************************/

void vedio_drawCNchar(int xx, int yy, unsigned char *s)
{

    unsigned char *cdat, *dest;
    int rows, offset, c;
    
    offset = yy * VIDEO_LINE_LEN + xx * VIDEO_PIXEL_SIZE;
    dest = video_fb_address + offset;

    switch (VIDEO_DATA_FORMAT) {
    case GDF__8BIT_INDEX:
    case GDF__8BIT_332RGB:
        SBD_DISPLAY("332r",0);
        break;

    case GDF_15BIT_555RGB:
        SBD_DISPLAY("555r",0);
        break;

    //here
    case GDF_16BIT_565RGB:
            c = getCNcode(s);
            cdat = video_fontcndata + c*32;
            for (rows = VIDEO_FONT_CN_HEIGHT;
                 rows--;
                 dest += VIDEO_LINE_LEN) {
                unsigned char bits = *cdat++;
                ((unsigned int *) dest)[0] = SHORTSWAP32 ((video_font_draw_table16 [bits >> 6] & eorx) ^ bgx);
                ((unsigned int *) dest)[1] = SHORTSWAP32 ((video_font_draw_table16 [bits >> 4 & 3] & eorx) ^ bgx);
                ((unsigned int *) dest)[2] = SHORTSWAP32 ((video_font_draw_table16 [bits >> 2 & 3] & eorx) ^ bgx);
                ((unsigned int *) dest)[3] = SHORTSWAP32 ((video_font_draw_table16 [bits & 3] & eorx) ^ bgx);
                bits = *cdat++;
                ((unsigned int *) dest)[4] = SHORTSWAP32 ((video_font_draw_table16 [bits >> 6] & eorx) ^ bgx);
                ((unsigned int *) dest)[5] = SHORTSWAP32 ((video_font_draw_table16 [bits >> 4 & 3] & eorx) ^ bgx);
                ((unsigned int *) dest)[6] = SHORTSWAP32 ((video_font_draw_table16 [bits >> 2 & 3] & eorx) ^ bgx);
                ((unsigned int *) dest)[7] = SHORTSWAP32 ((video_font_draw_table16 [bits & 3] & eorx) ^ bgx);
            }
        break;

    case GDF_32BIT_X888RGB:
        SBD_DISPLAY("888r",0);
        break;

    case GDF_24BIT_888RGB:
        SBD_DISPLAY("888r",0);
        break;
    }
    
}

/*****************************************************************************/

void video_drawstring(int xx, int yy, unsigned char *s)
{
    video_drawchars(xx, yy, s, strlen((char *)s));
}

/*****************************************************************************/
//#ifndef VIDEO_HW_BITBLT
#if defined(LOONGSON3A_3AEV)||defined(LOONGSON2G_2G690E)||defined(LOONGSON3A_3A780E)||defined(LOONGSON3A_3AITX)
void video_drawsline(char *str, int rows, int cols)
{
	int xx, yy;
	int pos;

	for(yy = 1; yy < rows; yy++)
	{
		pos = yy * cols;
		for(xx = 0; xx < cols; xx++)
		{
			if(str[pos + xx] != str[pos - cols + xx])
				video_putchar(xx * VIDEO_FONT_WIDTH, (yy-1) * VIDEO_FONT_HEIGHT, str[pos + xx]);
		}
	}
	
	memcpyl (str, &str[cols], (rows - 1) *cols >> 2);
	memsetw (&str[(rows - 1) * cols], cols >> 2, CONSOLE_BG_COL);
}

#endif
void video_putchar(int xx, int yy, unsigned char c)
{
    video_drawchars(xx, yy + VIDEO_LOGO_HEIGHT, &c, 1);
}
//2009-07-17
void video_putchar_xor (int xx, int yy, unsigned char c)
{
    video_drawchars_xor (xx, yy + VIDEO_LOGO_HEIGHT, &c, 1);
}


/*****************************************************************************/
#if defined(CONFIG_CONSOLE_CURSOR) || defined(CONFIG_VIDEO_SW_CURSOR)
static void video_set_cursor(void)
{
    /* swap drawing colors */
    eorx = fgx;
    fgx = bgx;
    bgx = eorx;
    eorx = fgx ^ bgx;
    /* draw cursor */
    video_putchar(console_col * VIDEO_FONT_WIDTH,
              console_row * VIDEO_FONT_HEIGHT, ' ');
    /* restore drawing colors */
    eorx = fgx;
    fgx = bgx;
    bgx = eorx;
    eorx = fgx ^ bgx;
}
#endif
/*****************************************************************************/
#ifdef CONFIG_CONSOLE_CURSOR
void console_cursor(int state)
{
    static int last_state = 0;

#ifdef CONFIG_CONSOLE_TIME
    struct rtc_time tm;
    char info[16];

    /* time update only if cursor is on (faster scroll) */
    if (state) {
        rtc_get(&tm);

        sprintf(info, " %02d:%02d:%02d ", tm.tm_hour, tm.tm_min,
            tm.tm_sec);
        video_drawstring(VIDEO_VISIBLE_COLS - 10 * VIDEO_FONT_WIDTH,
                 VIDEO_INFO_Y, (unsigned char *)info);

        sprintf(info, "%02d.%02d.%04d", tm.tm_mday, tm.tm_mon,
            tm.tm_year);
        video_drawstring(VIDEO_VISIBLE_COLS - 10 * VIDEO_FONT_WIDTH,
				  VIDEO_INFO_Y + 1 * VIDEO_FONT_HEIGHT, (unsigned char *)info);
    }
#endif

    if (state && (last_state != state)) {
        video_set_cursor();
    }

    if (!state && (last_state != state)) {
        /* clear cursor */
        video_putchar(console_col * VIDEO_FONT_WIDTH,
                  console_row * VIDEO_FONT_HEIGHT, ' ');
    }

    last_state = state;
}
#endif

/*****************************************************************************/

static void memsetl(unsigned char *p, int c, int v)
{
    while (c--)
        *(p++) = v;
}

static void memsetw(int *p, int c, int v)
{
    while (c--)
        *(p++) = v;
}

/*****************************************************************************/

#ifndef VIDEO_HW_BITBLT
static void memcpyl(int *d, int *s, int c)
{
    while (c--)
        *(d++) = *(s++);
}
#endif

/*****************************************************************************/

static void console_scrollup(void)
{
    /* copy up rows ignoring the first one */
    if(disableoutput)return;
 #if defined(LOONGSON3A_3AEV)||defined(LOONGSON2G_2G690E)||defined(LOONGSON3A_3A780E)||defined(LOONGSON3A_3AITX)
	video_drawsline(memfb, CONSOLE_ROWS, CONSOLE_COLS);

    memsetl(CONSOLE_ROW_LAST, CONSOLE_ROW_SIZE, CONSOLE_BG_COL);
	//memsetl (CONSOLE_ROW_LAST-CONSOLE_ROW_SIZE/2, CONSOLE_ROW_SIZE >> 2, CONSOLE_BG_COL);
#else    
#ifdef VIDEO_HW_BITBLT
    #ifdef LOONGSON2F_7INCH
    video_hw_bitblt(VIDEO_PIXEL_SIZE,   /* bytes per pixel */
            0,  /* source pos x */
            VIDEO_LOGO_HEIGHT + VIDEO_FONT_HEIGHT,  /* source pos y */
            0,  /* dest pos x */
            VIDEO_LOGO_HEIGHT,  /* dest pos y */
            VIDEO_VISIBLE_COLS, /* frame width */
            VIDEO_VISIBLE_ROWS - VIDEO_LOGO_HEIGHT - VIDEO_FONT_HEIGHT  /* frame height */
        );
    #endif
    #if defined( LOONGSON2F_ALLINONE) 
        #if(NMOD_SISFB)
        {
            void sisfb_copyarea(int sx,int sy,int dx,int dy,int width,int height);
                sisfb_copyarea(0,VIDEO_LOGO_HEIGHT + VIDEO_FONT_HEIGHT,0,VIDEO_LOGO_HEIGHT,1360,768 - VIDEO_LOGO_HEIGHT - 16);
        }
        #endif
    #endif
    #ifdef LOONGSON2F_FULOONG
    video_hw_bitblt(VIDEO_PIXEL_SIZE,   /* bytes per pixel */
            0,  /* source pos x */
            VIDEO_LOGO_HEIGHT + VIDEO_FONT_HEIGHT,  /* source pos y */
            0,  /* dest pos x */
            VIDEO_LOGO_HEIGHT,  /* dest pos y */
            VIDEO_VISIBLE_COLS, /* frame width */
            VIDEO_VISIBLE_ROWS - VIDEO_LOGO_HEIGHT /* frame height */
        );
    #endif

    #if (defined(SMI502))
    AutodeCopyModify((pGD->gdfBytesPP * 8));
    #endif
#else

	    memcpyl (CONSOLE_ROW_FIRST, CONSOLE_ROW_SECOND,
		    CONSOLE_SCROLL_SIZE >> 2);
/*

    memcpyl (CONSOLE_ROW_FIRST, CONSOLE_ROW_SECOND,
         CONSOLE_SCROLL_SIZE >> 2);
*/         
#endif

    /* clear the last one */
#ifdef VIDEO_HW_RECTFILL
#ifdef SM712_GRAPHIC_CARD
    video_hw_rectfill(VIDEO_PIXEL_SIZE, /* bytes per pixel */
              0,    /* dest pos x */
              (VIDEO_VISIBLE_ROWS - VIDEO_FONT_HEIGHT), /* dest pos y */
              VIDEO_VISIBLE_COLS,   /* frame width */
              VIDEO_FONT_HEIGHT,    /* frame height */
              CONSOLE_BG_COL    /* fill color */
        );
#endif
#if (defined(SMI502))
    AutodeFillRectModify(CONSOLE_BG_COL);
#endif

#ifdef NMOD_SISFB
#if 0
{
    void sisfb_rectfill(unsigned int bpp, unsigned int dst_x, unsigned int dst_y, 
                unsigned int dim_x, unsigned int dim_y, unsigned int color);
    sisfb_rectfill(         
            VIDEO_PIXEL_SIZE,   /* bytes per pixel */
            0,  /* dest pos x */
            VIDEO_VISIBLE_ROWS-VIDEO_FONT_HEIGHT,
            VIDEO_VISIBLE_COLS, /* frame width */
            VIDEO_FONT_HEIGHT, /* frame height */
            CONSOLE_BG_COL);            
}
#endif
    memsetl(CONSOLE_ROW_LAST, CONSOLE_ROW_SIZE, CONSOLE_BG_COL);
#endif

#else
    memsetl(CONSOLE_ROW_LAST, CONSOLE_ROW_SIZE, CONSOLE_BG_COL);
#endif

#endif
}

/*****************************************************************************/

static void console_back(void)
{
    CURSOR_OFF console_col--;

    if (console_col < 0) {
        console_col = CONSOLE_COLS - 1;
        console_row--;
        if (console_row < 0)
            console_row = 0;
    }
    video_putchar(console_col * VIDEO_FONT_WIDTH,
              console_row * VIDEO_FONT_HEIGHT, ' ');
}

/*****************************************************************************/

static void console_newline(void)
{
    CURSOR_OFF console_row++;
    console_col = 0;

    /* Check if we need to scroll the terminal */
    if (console_row >= CONSOLE_ROWS) {
        /* Scroll everything up */
        console_scrollup();

        /* Decrement row number */
        console_row--;
    }
}

/*****************************************************************************/

void video_putc(const char c)
{
    switch (c) {
    case 13:        /* ignore */
        break;

    case '\n':      /* next line */
        console_newline();
        break;

    case 9:     /* tab 8 */
        CURSOR_OFF console_col |= 0x0008;
        console_col &= ~0x0007;

        if (console_col >= CONSOLE_COLS)
            console_newline();
        break;

    case 8:     /* backspace */
        console_back();
        break;

    default:        /* draw the char */
        video_putchar(console_col * VIDEO_FONT_WIDTH,
                  console_row * VIDEO_FONT_HEIGHT, c);

#if defined(LOONGSON3A_3AEV) || defined(LOONGSON2G_2G690E)||defined(LOONGSON3A_3A780E)||defined(LOONGSON3A_3AITX)
		memfb[console_row * CONSOLE_COLS + console_col] = c;
#endif 

    console_col++;

        /* check for newline */
        if (console_col >= CONSOLE_COLS)
            console_newline();
    }
CURSOR_SET}

/*****************************************************************************/

void video_puts(const char *s)
{
    int count = strlen(s);

    while (count--)
        video_putc(*s++);
}

/*****************************************************************************/

#if (CONFIG_COMMANDS & CFG_CMD_BMP) || defined(CONFIG_SPLASH_SCREEN)

#define FILL_8BIT_332RGB(r,g,b) {           \
    *fb = ((r>>5)<<5) | ((g>>5)<<2) | (b>>6);   \
    fb ++;                      \
}

#define FILL_15BIT_555RGB(r,g,b) {          \
    *(unsigned short *)fb = SWAP16((unsigned short)(((r>>3)<<10) | ((g>>3)<<5) | (b>>3))); \
    fb += 2;                    \
}

#define FILL_16BIT_565RGB(r,g,b) {          \
    *(unsigned short *)fb = SWAP16((unsigned short)((((r)>>3)<<11) | (((g)>>2)<<5) | ((b)>>3))); \
    fb += 2;                    \
}

#define FILL_32BIT_X888RGB(r,g,b) {         \
    *(unsigned long *)fb = SWAP32((unsigned long)(((r<<16) | (g<<8) | b))); \
    fb += 4;                    \
}

#ifdef VIDEO_FB_LITTLE_ENDIAN
#define FILL_24BIT_888RGB(r,g,b) {          \
    fb[0] = b;                  \
    fb[1] = g;                  \
    fb[2] = r;                  \
    fb += 3;                    \
}
#else
#define FILL_24BIT_888RGB(r,g,b) {          \
    fb[0] = r;                  \
    fb[1] = g;                  \
    fb[2] = b;                  \
    fb += 3;                    \
}
#endif

#define le32_to_cpu(x) (x)
#define le16_to_cpu(x) (x)

#define CFG_VIDEO_LOGO_MAX_SIZE 0x200000
#define GZIP_BMP_FILE_MAX_SIZE 0x20000
/*
 * Display the BMP file located at address bmp_image.
 * Only uncompressed
 */
int video_display_bitmap(ulong bmp_image, int x, int y)
{
    ushort xcount, ycount;
    unsigned char *fb;
    bmp_image_t *bmp = (bmp_image_t *) bmp_image;
    unsigned char *bmap;
    ushort padded_line;
    unsigned long width, height, bpp;
    unsigned colors;
    unsigned long compression;
    bmp_color_table_entry_t cte;
#ifdef CONFIG_VIDEO_BMP_GZIP
    unsigned char *dst = NULL;
    unsigned char *bg_img_src = NULL;
    ulong len;
#ifdef  LOONGSON2F_7INCH
    unsigned char is_bigbmp = 0;
    unsigned long dst_size = 0;
#endif
#endif

    if (!((bmp->header.signature[0] == 'B') &&
          (bmp->header.signature[1] == 'M'))) {

#ifdef CONFIG_VIDEO_BMP_GZIP
#ifdef  LOONGSON2F_7INCH
        /*
         * Could be a gzipped bmp image, try to decrompress...
         */
        if( (x == BIGBMP_X) && (y == BIGBMP_Y) ){
            is_bigbmp = 1;
        }else{
            is_bigbmp = 0;
        }

        if(is_bigbmp){
                dst_size = 0x80000;
                len = 0xd000;
        }else{
                dst_size = 0x8000;
                len = 0x300;
        }
        bg_img_src = malloc(len);
        if (bg_img_src == NULL) {
            printf("Error: malloc in gunzip failed!\n");
            return (1);
        }

        dst = malloc(dst_size);
        if (dst == NULL) {
            printf("Error: malloc in gunzip failed!\n");
            return (1);
        }

        memcpy(bg_img_src, bmp_image, len);

        if( gunzip(dst, dst_size, (unsigned char *)bg_img_src, &len) != 0 ){
            printf("Error: no valid bmp or bmp.gz image at %lx\n", bmp_image);
            free(dst);
            free(bg_img_src);
            return 1;
        }
        if (len >= dst_size) {
            printf("Image could be truncated (increase CFG_VIDEO_LOGO_MAX_SIZE)!\n");
        }
#else
        len = GZIP_BMP_FILE_MAX_SIZE;
        bg_img_src = malloc(len);
        if (bg_img_src == NULL) {
            printf("Error: malloc in gunzip failed!\n");
            return (1);
        }

        dst = malloc(CFG_VIDEO_LOGO_MAX_SIZE);
        if (dst == NULL) {
            printf("Error: malloc in gunzip failed!\n");
            return (1);
        }

        memcpy(bg_img_src,(const void *) bmp_image, len);
        if (gunzip(dst, CFG_VIDEO_LOGO_MAX_SIZE, 
                (unsigned char *)bg_img_src, &len) != 0) {
            printf("Error: no valid bmp or bmp.gz image at %lx\n",
                   bmp_image);
            free(dst);
            free(bg_img_src);
            return 1;
        }
        if (len == CFG_VIDEO_LOGO_MAX_SIZE) {
            printf
                ("Image could be truncated (increase CFG_VIDEO_LOGO_MAX_SIZE)!\n");
        }

#endif

        /*
         * Set addr to decompressed image
         */
        bmp = (bmp_image_t *) dst;

        if (!((bmp->header.signature[0] == 'B') &&
              (bmp->header.signature[1] == 'M'))) {
            printf("Error: no valid bmp.gz image at %lx\n",
                   bmp_image);
            return 1;
        }
#endif              /* CONFIG_VIDEO_BMP_GZIP */
    }

    width = le32_to_cpu(bmp->header.width);
    height = le32_to_cpu(bmp->header.height);
    bpp = le16_to_cpu(bmp->header.bit_count);
    colors = le32_to_cpu(bmp->header.colors_used);
    compression = le32_to_cpu(bmp->header.compression);

    //printf("Display-bmp: %d x %d  with %d colors\n", width, height, colors);

    if (compression != BMP_BI_RGB) {
        printf("Error: compression type %ld not supported\n",
               compression);
        return 1;
    }

    padded_line = (((width * bpp + 7) / 8) + 3) & ~0x3;

    if ((x + width) > VIDEO_VISIBLE_COLS)
        width = VIDEO_VISIBLE_COLS - x;
    if ((y + height) > VIDEO_VISIBLE_ROWS)
        height = VIDEO_VISIBLE_ROWS - y;

    bmap = (unsigned char *)bmp + le32_to_cpu(bmp->header.data_offset);
    fb = (unsigned char *)(video_fb_address +
                   ((y + height -
                 1) * VIDEO_COLS * VIDEO_PIXEL_SIZE) +
                   x * VIDEO_PIXEL_SIZE);

    /* We handle only 8bpp or 24 bpp bitmap */
    switch (le16_to_cpu(bmp->header.bit_count)) {
    case 8:
        padded_line -= width;
        if (VIDEO_DATA_FORMAT == GDF__8BIT_INDEX) {
#if 1
            /* Copy colormap                                             */
            for (xcount = 0; xcount < colors; ++xcount) {
                cte = bmp->color_table[xcount];
                video_set_lut(xcount, cte.red, cte.green,
                          cte.blue);
            }
#endif
        }
        ycount = height;
        switch (VIDEO_DATA_FORMAT) {
        case GDF__8BIT_INDEX:
            while (ycount--) {

                xcount = width;
                while (xcount--) {
                    *fb++ = *bmap++;
                }
                bmap += padded_line;
                fb -=
                    (VIDEO_VISIBLE_COLS +
                     width) * VIDEO_PIXEL_SIZE;
            }
            break;
        case GDF__8BIT_332RGB:
            while (ycount--) {

                xcount = width;
                while (xcount--) {
                    cte = bmp->color_table[*bmap++];
                    FILL_8BIT_332RGB(cte.red, cte.green,
                             cte.blue);
                }
                bmap += padded_line;
                fb -=
                    (VIDEO_VISIBLE_COLS +
                     width) * VIDEO_PIXEL_SIZE;
            }
            break;
        case GDF_15BIT_555RGB:
            while (ycount--) {

                xcount = width;
                while (xcount--) {
                    cte = bmp->color_table[*bmap++];
                    FILL_15BIT_555RGB(cte.red, cte.green,
                              cte.blue);
                }
                bmap += padded_line;
                fb -=
                    (VIDEO_VISIBLE_COLS +
                     width) * VIDEO_PIXEL_SIZE;
            }
            break;
        case GDF_16BIT_565RGB:
            while (ycount--) {

                xcount = width;
                while (xcount--) {
                    cte = bmp->color_table[*bmap++];
                    FILL_16BIT_565RGB(cte.red, cte.green,
                              cte.blue);
                }
                bmap += padded_line;
                fb -=
                    (VIDEO_VISIBLE_COLS +
                     width) * VIDEO_PIXEL_SIZE;
            }
            break;
        case GDF_32BIT_X888RGB:
            while (ycount--) {

                xcount = width;
                while (xcount--) {
                    cte = bmp->color_table[*bmap++];
                    FILL_32BIT_X888RGB(cte.red, cte.green,
                               cte.blue);
                }
                bmap += padded_line;
                fb -=
                    (VIDEO_VISIBLE_COLS +
                     width) * VIDEO_PIXEL_SIZE;
            }
            break;
        case GDF_24BIT_888RGB:
            while (ycount--) {

                xcount = width;
                while (xcount--) {
                    cte = bmp->color_table[*bmap++];
                    FILL_24BIT_888RGB(cte.red, cte.green,
                              cte.blue);
                }
                bmap += padded_line;
                fb -=
                    (VIDEO_VISIBLE_COLS +
                     width) * VIDEO_PIXEL_SIZE;
            }
            break;
        }
        break;
    case 24:
        padded_line -= 3 * width;
        ycount = height;
        switch (VIDEO_DATA_FORMAT) {
        case GDF__8BIT_332RGB:
            while (ycount--) {

                xcount = width;
                while (xcount--) {
                    FILL_8BIT_332RGB(bmap[2], bmap[1],
                             bmap[0]);
                    bmap += 3;
                }
                bmap += padded_line;
                fb -=
                    (VIDEO_VISIBLE_COLS +
                     width) * VIDEO_PIXEL_SIZE;
            }
            break;
        case GDF_15BIT_555RGB:
            while (ycount--) {

                xcount = width;
                while (xcount--) {
                    FILL_15BIT_555RGB(bmap[2], bmap[1],
                              bmap[0]);
                    bmap += 3;
                }
                bmap += padded_line;
                fb -=
                    (VIDEO_VISIBLE_COLS +
                     width) * VIDEO_PIXEL_SIZE;
            }
            break;
        case GDF_16BIT_565RGB:
            while (ycount--) {

                xcount = width;
                while (xcount--) {
                    FILL_16BIT_565RGB(bmap[2], bmap[1],
                              bmap[0]);
                    bmap += 3;
                }
                bmap += padded_line;
                fb -=
                    (VIDEO_VISIBLE_COLS +
                     width) * VIDEO_PIXEL_SIZE;
            }
            break;
        case GDF_32BIT_X888RGB:
            while (ycount--) {

                xcount = width;
                while (xcount--) {
                    FILL_32BIT_X888RGB(bmap[2], bmap[1],
                               bmap[0]);
                    bmap += 3;
                }
                bmap += padded_line;
                fb -=
                    (VIDEO_VISIBLE_COLS +
                     width) * VIDEO_PIXEL_SIZE;
            }
            break;
        case GDF_24BIT_888RGB:
            while (ycount--) {

                xcount = width;
                while (xcount--) {
                    FILL_24BIT_888RGB(bmap[2], bmap[1],
                              bmap[0]);
                    bmap += 3;
                }
                bmap += padded_line;
                fb -=
                    (VIDEO_VISIBLE_COLS +
                     width) * VIDEO_PIXEL_SIZE;
            }
            break;
        default:
            printf
                ("Error: 24 bits/pixel bitmap incompatible with current video mode\n");
            break;
        }
        break;
    default:
        printf("Error: %d bit/pixel bitmaps not supported by U-Boot\n",
               le16_to_cpu(bmp->header.bit_count));
        break;
    }

#ifdef CONFIG_VIDEO_BMP_GZIP
    if (dst) {
        free(dst);
    }
    if (bg_img_src)
        free(bg_img_src);
#endif

    return (0);
}
#endif              /* (CONFIG_COMMANDS & CFG_CMD_BMP) || CONFIG_SPLASH_SCREEN */

/*****************************************************************************/

#ifdef CONFIG_VIDEO_LOGO
void logo_plot(void *screen, int width, int x, int y)
{

    int xcount, i;
    int skip = (width - VIDEO_LOGO_WIDTH) * VIDEO_PIXEL_SIZE;
    int ycount = VIDEO_LOGO_HEIGHT;
    unsigned char r, g, b, *logo_red, *logo_blue, *logo_green;
    unsigned char *source;
    unsigned char *dest =
        (unsigned char *)screen + ((y * width * VIDEO_PIXEL_SIZE) + x);

#ifdef CONFIG_VIDEO_BMP_LOGO
    source = bmp_logo_bitmap;

    /* Allocate temporary space for computing colormap                       */
    logo_red = malloc(BMP_LOGO_COLORS);
    logo_green = malloc(BMP_LOGO_COLORS);
    logo_blue = malloc(BMP_LOGO_COLORS);
    /* Compute color map                                                     */
    for (i = 0; i < VIDEO_LOGO_COLORS; i++) {
        logo_red[i] = (bmp_logo_palette[i] & 0x0f00) >> 4;
        logo_green[i] = (bmp_logo_palette[i] & 0x00f0);
        logo_blue[i] = (bmp_logo_palette[i] & 0x000f) << 4;
    }
#else
    source = linux_logo;
    logo_red = linux_logo_red;
    logo_green = linux_logo_green;
    logo_blue = linux_logo_blue;
#endif

    if (VIDEO_DATA_FORMAT == GDF__8BIT_INDEX) {
#if 1
        for (i = 0; i < VIDEO_LOGO_COLORS; i++) {
            video_set_lut(i + VIDEO_LOGO_LUT_OFFSET,
                      logo_red[i], logo_green[i], logo_blue[i]);
        }
#endif
    }

    while (ycount--) {
        xcount = VIDEO_LOGO_WIDTH;
        while (xcount--) {
            r = logo_red[*source - VIDEO_LOGO_LUT_OFFSET];
            g = logo_green[*source - VIDEO_LOGO_LUT_OFFSET];
            b = logo_blue[*source - VIDEO_LOGO_LUT_OFFSET];

            switch (VIDEO_DATA_FORMAT) {
            case GDF__8BIT_INDEX:
                *dest = *source;
                break;
            case GDF__8BIT_332RGB:
                *dest =
                    ((r >> 5) << 5) | ((g >> 5) << 2) | (b >>
                                     6);
                break;
            case GDF_15BIT_555RGB:
                *(unsigned short *)dest =
                    SWAP16((unsigned short)(((r >> 3) << 10) |
                                ((g >> 3) << 5) | (b
                                           >>
                                           3)));
                break;
            case GDF_16BIT_565RGB:
                *(unsigned short *)dest =
                    SWAP16((unsigned short)(((r >> 3) << 11) |
                                ((g >> 2) << 5) | (b
                                           >>
                                           3)));
                break;
            case GDF_32BIT_X888RGB:
                *(unsigned long *)dest =
                    SWAP32((unsigned long)((r << 16) | (g << 8)
                               | b));
                break;
            case GDF_24BIT_888RGB:
#ifdef VIDEO_FB_LITTLE_ENDIAN
                dest[0] = b;
                dest[1] = g;
                dest[2] = r;
#else
                dest[0] = r;
                dest[1] = g;
                dest[2] = b;
#endif
                break;
            }
            source++;
            dest += VIDEO_PIXEL_SIZE;
        }
        dest += skip;
    }
#ifdef CONFIG_VIDEO_BMP_LOGO
    free(logo_red);
    free(logo_green);
    free(logo_blue);
#endif
}

/*****************************************************************************/
static void *video_logo(void)
{
    char info[128] = " PMON on Godson-LM2E,build r31,2006.10.21.";

#ifdef CONFIG_VIDEO_BMP_LOGO
    logo_plot(video_fb_address, VIDEO_COLS,
          (VIDEO_COLS - VIDEO_LOGO_WIDTH) * VIDEO_PIXEL_SIZE, 0);
#endif
    //video_drawstring (VIDEO_INFO_X, VIDEO_INFO_Y, (unsigned char *)info);

#ifdef CONFIG_CONSOLE_EXTRA_INFO
    {
        int i, n =
            ((VIDEO_LOGO_HEIGHT -
              VIDEO_FONT_HEIGHT) / VIDEO_FONT_HEIGHT);

        for (i = 1; i < n; i++) {
            video_get_info_str(i, info);
            if (*info)
                video_drawstring(VIDEO_INFO_X,
                         VIDEO_INFO_Y +
                         i * VIDEO_FONT_HEIGHT,
                         (unsigned char *)info);
        }
    }
#endif

    return (video_fb_address + VIDEO_LOGO_HEIGHT * VIDEO_LINE_LEN);
}
#endif
void _set_font_color(void)
{
    unsigned char color8;
    unsigned int i, cnt;
    /* Init drawing pats */
    switch (VIDEO_DATA_FORMAT) {
    case GDF__8BIT_INDEX:
        cnt = sizeof(pallete_32) / sizeof(unsigned long);
        for (i = 0; i < cnt; i++) {            
        #if defined(SM712_GRAPHIC_CARD)|| defined(VESAFB)||defined(RADEON7000)  
            video_set_lut2(i, pallete_32[i]);
        #endif
        }
        fgx = 0x07070707;
        bgx = 0x00000000;
        break;
    case GDF__8BIT_332RGB:
        color8 = ((CONSOLE_FG_COL & 0xe0) |
              ((CONSOLE_FG_COL >> 3) & 0x1c) | CONSOLE_FG_COL >> 6);
        fgx = (color8 << 24) | (color8 << 16) | (color8 << 8) | color8;
        color8 = ((CONSOLE_BG_COL & 0xe0) |
              ((CONSOLE_BG_COL >> 3) & 0x1c) | CONSOLE_BG_COL >> 6);
        bgx = (color8 << 24) | (color8 << 16) | (color8 << 8) | color8;
        break;
    case GDF_15BIT_555RGB:
        fgx = (((CONSOLE_FG_COL >> 3) << 26) |
               ((CONSOLE_FG_COL >> 3) << 21) | ((CONSOLE_FG_COL >> 3) <<
                            16) | ((CONSOLE_FG_COL
                                >> 3) << 10) |
               ((CONSOLE_FG_COL >> 3) << 5) | (CONSOLE_FG_COL >> 3));
        bgx =
            (((CONSOLE_BG_COL >> 3) << 26) |
             ((CONSOLE_BG_COL >> 3) << 21) | ((CONSOLE_BG_COL >> 3) <<
                              16) | ((CONSOLE_BG_COL >>
                                  3) << 10) |
             ((CONSOLE_BG_COL >> 3) << 5) | (CONSOLE_BG_COL >> 3));
        break;
    case GDF_16BIT_565RGB:
        fgx = (((CONSOLE_FG_COL >> 3) << 27) |
               ((CONSOLE_FG_COL >> 2) << 21) | ((CONSOLE_FG_COL >> 3) <<
                            16) | ((CONSOLE_FG_COL
                                >> 3) << 11) |
               ((CONSOLE_FG_COL >> 2) << 5) | (CONSOLE_FG_COL >> 3));
        bgx =
            (((CONSOLE_BG_COL >> 3) << 27) |
             ((CONSOLE_BG_COL >> 2) << 21) | ((CONSOLE_BG_COL >> 3) <<
                              16) | ((CONSOLE_BG_COL >>
                                  3) << 11) |
             ((CONSOLE_BG_COL >> 2) << 5) | (CONSOLE_BG_COL >> 3));
        break;
    case GDF_32BIT_X888RGB:
        fgx =
            (CONSOLE_FG_COL << 16) | (CONSOLE_FG_COL << 8) |
            CONSOLE_FG_COL;
        bgx =
            (CONSOLE_BG_COL << 16) | (CONSOLE_BG_COL << 8) |
            CONSOLE_BG_COL;
        break;
    case GDF_24BIT_888RGB:
        fgx = (CONSOLE_FG_COL << 24) | (CONSOLE_FG_COL << 16) |
            (CONSOLE_FG_COL << 8) | CONSOLE_FG_COL;
        bgx = (CONSOLE_BG_COL << 24) | (CONSOLE_BG_COL << 16) |
            (CONSOLE_BG_COL << 8) | CONSOLE_BG_COL;
        break;
    }
    eorx = fgx ^ bgx;

}

//special for sm502's clear srceen
#if (defined(SMI502))
void sm502_video_cls(void)
{
#if (defined(X1368x768))
	/*20100119,Teddy:It seems that SM502's fillrect function has bug that it can't draw a large width rect.We draw it three times.*/
    deFillRectModify(0,0,0,500,768,CONSOLE_BG_COL); 
    deFillRectModify(0,500,0,1000,768,CONSOLE_BG_COL);
    deFillRectModify(0,1000,0,1368,768,CONSOLE_BG_COL);
#endif
#if defined(X1024x768)
	deFillRectModify(0,0,0,1024,768,CONSOLE_BG_COL);
#endif
	
#if defined(X800x600)	
	deFillRectModify(0,0,0,800,600,CONSOLE_BG_COL);
#endif
	
#if defined(X640x480)
	deFillRectModify(0,0,0,640,480,CONSOLE_BG_COL);
#endif

#if defined(X1024x600)
	deFillRectModify(0,0,0,400,600,CONSOLE_BG_COL);
    deFillRectModify(0,400,0,800,600,CONSOLE_BG_COL);
    deFillRectModify(0,800,0,1024,600,CONSOLE_BG_COL);
#endif
}
#endif

void video_cls(void)
{
#if  (defined(VIDEO_HW_RECTFILL))
#if (defined(SMI502))
    sm502_video_cls();
#endif
#if (defined(SM712_GRAPHIC_CARD))
    video_hw_rectfill(
            VIDEO_PIXEL_SIZE,   /* bytes per pixel */
            0,  /* dest pos x */
            VIDEO_LOGO_HEIGHT,
            VIDEO_VISIBLE_COLS, /* frame width */
#ifdef LOONGSON2F_7INCH
            /*fixup vga display problem*/
            VIDEO_VISIBLE_ROWS + 140, /*LCD 800x480, VGA 800x600*/
#else
            VIDEO_VISIBLE_ROWS, /* frame height */
#endif
            CONSOLE_BG_COL  /* fill color */
        );
#endif
//5-8
#if NMOD_SISFB
{
    void sisfb_rectfill(unsigned int bpp, unsigned int dst_x, unsigned int dst_y, 
                unsigned int dim_x, unsigned int dim_y, unsigned int color);
    sisfb_rectfill(         
            VIDEO_PIXEL_SIZE,   /* bytes per pixel */
            0,  /* dest pos x */
            VIDEO_LOGO_HEIGHT,
            VIDEO_VISIBLE_COLS, /* frame width */
            VIDEO_VISIBLE_ROWS, /* frame height */
            CONSOLE_BG_COL);            
}
#endif
#else
    memsetl(video_fb_address + VIDEO_LOGO_HEIGHT * VIDEO_LINE_LEN,
        CONSOLE_SIZE - VIDEO_LOGO_HEIGHT * VIDEO_LINE_LEN,
        CONSOLE_BG_COL);
#endif

    _set_font_color();
/*
    memcpy(video_fb_address, saved_frame_buffer, FB_SIZE);

*/
}

void video_set_background(unsigned char r, unsigned char g, unsigned char b)
{
    int cnt = CONSOLE_SIZE - VIDEO_LOGO_HEIGHT * VIDEO_LINE_LEN;

    switch (VIDEO_DATA_FORMAT) {
    case GDF_16BIT_565RGB:
        {
            unsigned short *p =
                video_fb_address +
                VIDEO_LOGO_HEIGHT * VIDEO_LINE_LEN;
            unsigned short color =
                SWAP16((unsigned short)(((r >> 3) << 11) |
                            ((g >> 2) << 5) | (b >>
                                       3)));

            while (cnt > 0) {
                *(p++) = color;
                cnt -= 2;
            }
        }
        break;

    case GDF_32BIT_X888RGB:
        {
            unsigned int *p =
                video_fb_address +
                VIDEO_LOGO_HEIGHT * VIDEO_LINE_LEN;
            unsigned int color = r << 16 | g << 8 | b;

            while (cnt > 0) {
                *(p++) = color;
                cnt -= 4;
            }
        }
        break;
    }
    return;

#if 0
    int cnt = CONSOLE_SIZE;
    unsigned int *p = video_fb_address + VIDEO_LOGO_HEIGHT * VIDEO_LINE_LEN;
    unsigned int color =
        SWAP16((unsigned short)(((r >> 3) << 11) | ((g >> 2) << 5) |
                    (b >> 3)));
    color |= (color << 16);

    while (cnt > 0) {
        alpha_blend(p++, color);
        cnt -= 2;
    }

#endif
}
static int record = 1;
void video_console_print(int console_col, int console_row, unsigned char *s)
{
    int count = strlen(s);

    while (count--) {
        video_putchar(console_col * VIDEO_FONT_WIDTH,
                  console_row * VIDEO_FONT_HEIGHT, *s);
        if (record) {
            console_buffer[0][console_row][console_col] = *s;
            console_buffer[1][console_row][console_col] = (char)bgx;
        }
        console_col++;
        s++;
    }
}
void begin_record(void)
{
    record = 1;
}

void stop_record(void)
{
    record = 0;
}

char video_get_console_char(int console_col, int console_row)
{
    return console_buffer[0][console_row][console_col];
}

char video_get_console_bgcolor(int console_col, int console_row)
{
    return console_buffer[1][console_row][console_col];
}

void video_set_bg(unsigned char r, unsigned char g, unsigned char b)
{
    switch (VIDEO_DATA_FORMAT) {
    case GDF_16BIT_565RGB:
        bgx =
            SWAP16((unsigned short)(((r >> 3) << 11) | ((g >> 2) << 5) |
                        (b >> 3)));
        bgx |= (bgx << 16);
        fgx =
            SWAP16((unsigned short)(((128 >> 3) << 11) |
                        ((128 >> 2) << 5) | (128 >> 3)));
        fgx |= (fgx << 16);
        eorx = fgx ^ bgx;
        break;

    case GDF_32BIT_X888RGB:
        bgx = (r << 16) | (g << 8) | b;
        fgx = (128 << 16) | (128 << 8) | 128;
        eorx = fgx ^ bgx;
        break;
    }
    return;

}

void set_vga_color(int fg, int bg)
{
    switch (VIDEO_DATA_FORMAT) {
    case GDF_16BIT_565RGB:
        bgx = pallete[bg];
        bgx |= (bgx << 16);
        fgx = pallete[fg];
        fgx |= (fgx << 16);
        eorx = fgx ^ bgx;
        break;

    case GDF_32BIT_X888RGB:
        bgx = pallete_32[bg];
        fgx = pallete_32[fg];
        eorx = fgx ^ bgx;
        break;
    case GDF__8BIT_INDEX:
        fgx = fg | fg << 8, bgx = bg | bg << 8;
        fgx |= fgx << 16, bgx |= bgx << 16;
        eorx = fgx ^ bgx;
        break;
    }
    return;
}

void __cprint(int y, int x, int width, char color, const char *buf)
{
    set_vga_color(color & 0xf, ((unsigned char)color) >> 4);
    video_console_print(x, y, (unsigned char *)buf);
    set_vga_color(8, 0);
}
static char buf[0x100];
void cprintf(int y, int x, int width, char color, const char *fmt, ...)
{
    int len;
    va_list ap;
    va_start(ap, fmt);
    len = vsprintf(buf, fmt, ap);
    va_end(ap);
    __cprint(y, x, width, color, buf);
}

void gui_print(int row, int col, int width, int forecolor, int bgcolor,
           const char *str)
{
    set_vga_color(forecolor, bgcolor);
    video_console_print(col, row, (unsigned char *)str);
}

/*****************************************************************************/
int GetGDFIndex(int BytesPP)
{
    switch (BytesPP) {
    case 1:
        return GDF__8BIT_INDEX;
    case 2:
        return GDF_16BIT_565RGB;
    case 4:
        return GDF_32BIT_X888RGB;
    default:
        return GDF_16BIT_565RGB;
    }
}

//2009-07-17
void set_cursor_fb(unsigned char x,unsigned char y)
{
    console_col=x;
    console_row=y;
}

int fb_init(unsigned long fbbase, unsigned long iobase)
{

#if !defined(SMI502) && !defined(LOONGSON3A_3AEV) && !defined(LOONGSON2G_2G690E)&& !defined(LOONGSON3A_3A780E)&&!defined(LOONGSON3A_3AITX)
    pGD = &GD;
    #if NMOD_SISFB
        pGD->winSizeX = Sis_GetXRes();
        pGD->winSizeY = Sis_GetYRes();

        pGD->gdfBytesPP = Sis_GetBytesPP();
        pGD->gdfIndex = GetGDFIndex(pGD->gdfBytesPP);
    #else
        pGD->winSizeX = GetXRes();
        pGD->winSizeY = GetYRes();

        pGD->gdfBytesPP = GetBytesPP();
        pGD->gdfIndex = GetGDFIndex(GetBytesPP());
    #endif
    //pGD->frameAdrs = 0xb0000000 | fbbase;
    printf("fb_init fbbase:%x\n",fbbase);

    #ifdef LOONGSON2F_7INCH
    pGD->frameAdrs = PTR_PAD(0xb0000000) | fbbase;
    #else
        #ifdef USETLB
        pGD->frameAdrs = PTR_PAD(0xe0000000);
        #else
        pGD->frameAdrs = PTR_PAD(0xb0000000) | ((fbbase & 0xf0000000) ? 0 : fbbase);
        #endif
    #endif  

    
    #if 0
    printf("x %d, y %d, bpp %d, index %d\n", pGD->winSizeX, pGD->winSizeY, pGD->gdfBytesPP, pGD->gdfIndex);
    printf("cfb_console init,fb=%x\n", pGD->frameAdrs);
    #endif

    _set_font_color();

    video_fb_address = (void *)VIDEO_FB_ADRS;
    #ifdef CONFIG_VIDEO_HW_CURSOR
    video_init_hw_cursor(VIDEO_FONT_WIDTH, VIDEO_FONT_HEIGHT);
    #endif

    #if 1
    video_cls ();
    #else
    memsetl(video_fb_address, CONSOLE_SIZE,  CONSOLE_BG_COL);
    #endif

    #ifdef CONFIG_VIDEO_LOGO
    /* Plot the logo and get start point of console */
    printf("Video: Drawing the logo ...\n");
    video_console_address = video_logo();
    #else
        #ifdef CONFIG_SPLASH_SCREEN
            #ifdef  LOONGSON2F_7INCH
            video_display_bitmap(BIGBMP_START_ADDR, BIGBMP_X, BIGBMP_Y);
            #else
            video_display_bitmap(PTR_PAD(PICBMP_START_ADDR), 0, 0);
            #endif
        #endif
    video_console_address = video_fb_address;
    #endif
    printf("CONSOLE_SIZE %d, CONSOLE_ROW_SIZE %d\n", CONSOLE_SIZE, CONSOLE_ROW_SIZE);
    //saved_frame_buffer = malloc(FB_SIZE);
    //memcpy(saved_frame_buffer, video_fb_address, FB_SIZE);

    /* Initialize the console */
    console_col = 0;
    console_row = 0;

    memset(console_buffer, ' ', sizeof console_buffer);

    #ifdef  LOONGSON2F_7INCH
    video_display_bitmap(SMALLBMP0_START_ADDR, SMALLBMP0_X, SMALLBMP0_Y);
    video_display_bitmap(SMALLBMP_START_ADDR_EN_01, SMALLBMP01_EN_X, SMALLBMP01_EN_Y);
    #endif
    return 0;

#endif
#ifdef SMI502 

    unsigned char color8;

    pGD = &GD;
    #if defined(VGA_NOTEBOOK_V1)
    pGD->winSizeX  = 1280;
    pGD->winSizeY  = 800;
    #elif defined(VGA_NOTEBOOK_V2)
    pGD->winSizeX  = 1024;
    pGD->winSizeY  = 768;
    #else
    pGD->winSizeX  = 640;
    pGD->winSizeY  = 480;
    #endif
    
    #if defined(X800x600)
    pGD->winSizeX  = 800;
    pGD->winSizeY  = 600;
    #elif defined(X1024x768)
    pGD->winSizeX  = 1024;
    pGD->winSizeY  = 768;
    #elif defined(X1024x600)
    pGD->winSizeX  = 1024;
    pGD->winSizeY  = 600;
    #elif defined(X1368x768)   
    pGD->winSizeX  = 1368;
    pGD->winSizeY  = 768;
    #else
    pGD->winSizeX  = 640;
    pGD->winSizeY  = 480;
    #endif          
    
    #if defined(CONFIG_VIDEO_8BPP)
    pGD->gdfBytesPP= 1;
//  pGD->gdfIndex  = GDF__8BIT_INDEX;
    pGD->gdfIndex  = GDF__8BIT_332RGB;
    #elif defined(CONFIG_VIDEO_16BPP)
    pGD->gdfBytesPP= 2;
    pGD->gdfIndex  = GDF_16BIT_565RGB;
    #elif defined(CONFIG_VIDEO_32BPP)
    pGD->gdfBytesPP= 4;
    pGD->gdfIndex  = GDF_32BIT_X888RGB;
    #else
    pGD->gdfBytesPP= 2;
    pGD->gdfIndex  = GDF_16BIT_565RGB;
    #endif

    pGD->frameAdrs = PTR_PAD(0xb0000000) | fbbase;

    video_fb_address = (void *) VIDEO_FB_ADRS;
    #ifdef CONFIG_VIDEO_HW_CURSOR
    video_init_hw_cursor (VIDEO_FONT_WIDTH, VIDEO_FONT_HEIGHT);
    #endif
    /* Init drawing pats */
    switch (VIDEO_DATA_FORMAT) {
    #if 0
        case GDF__8BIT_INDEX:
            video_set_lut (0x01, CONSOLE_FG_COL, CONSOLE_FG_COL, CONSOLE_FG_COL);
            video_set_lut (0x00, CONSOLE_BG_COL, CONSOLE_BG_COL, CONSOLE_BG_COL);
            fgx = 0x01010101;
            bgx = 0x00000000;
            break;
    #endif
        case GDF__8BIT_332RGB:
            color8 = ((CONSOLE_FG_COL & 0xe0) |
                    ((CONSOLE_FG_COL >> 3) & 0x1c) | CONSOLE_FG_COL >> 6);
            fgx = (color8 << 24) | (color8 << 16) | (color8 << 8) | color8;
            color8 = ((CONSOLE_BG_COL & 0xe0) |
                    ((CONSOLE_BG_COL >> 3) & 0x1c) | CONSOLE_BG_COL >> 6);
            bgx = (color8 << 24) | (color8 << 16) | (color8 << 8) | color8;
            break;
        case GDF_15BIT_555RGB:
            fgx = (((CONSOLE_FG_COL >> 3) << 26) |
                    ((CONSOLE_FG_COL >> 3) << 21) | ((CONSOLE_FG_COL >> 3) << 16) |
                    ((CONSOLE_FG_COL >> 3) << 10) | ((CONSOLE_FG_COL >> 3) << 5) |
                    (CONSOLE_FG_COL >> 3));
            bgx = (((CONSOLE_BG_COL >> 3) << 26) |
                    ((CONSOLE_BG_COL >> 3) << 21) | ((CONSOLE_BG_COL >> 3) << 16) |
                    ((CONSOLE_BG_COL >> 3) << 10) | ((CONSOLE_BG_COL >> 3) << 5) |
                    (CONSOLE_BG_COL >> 3));
            break;
        case GDF_16BIT_565RGB:
            fgx = (((CONSOLE_FG_COL >> 3) << 27) |
                    ((CONSOLE_FG_COL >> 2) << 21) | ((CONSOLE_FG_COL >> 3) << 16) |
                    ((CONSOLE_FG_COL >> 3) << 11) | ((CONSOLE_FG_COL >> 2) << 5) |
                    (CONSOLE_FG_COL >> 3));
            bgx = (((CONSOLE_BG_COL >> 3) << 27) |
                    ((CONSOLE_BG_COL >> 2) << 21) | ((CONSOLE_BG_COL >> 3) << 16) |
                    ((CONSOLE_BG_COL >> 3) << 11) | ((CONSOLE_BG_COL >> 2) << 5) |
                    (CONSOLE_BG_COL >> 3));
            break;
        case GDF_32BIT_X888RGB:
            fgx = (CONSOLE_FG_COL << 16) | (CONSOLE_FG_COL << 8) | CONSOLE_FG_COL;
            bgx = (CONSOLE_BG_COL << 16) | (CONSOLE_BG_COL << 8) | CONSOLE_BG_COL;
            break;
        case GDF_24BIT_888RGB:
            fgx = (CONSOLE_FG_COL << 24) | (CONSOLE_FG_COL << 16) |
                (CONSOLE_FG_COL << 8) | CONSOLE_FG_COL;
            bgx = (CONSOLE_BG_COL << 24) | (CONSOLE_BG_COL << 16) |
                (CONSOLE_BG_COL << 8) | CONSOLE_BG_COL;
            break;
    }
    eorx = fgx ^ bgx;

    memsetl (video_fb_address, CONSOLE_SIZE, CONSOLE_BG_COL);
    #if 0
        #ifdef CONFIG_VIDEO_LOGO
        /* Plot the logo and get start point of console */
        printf("Video: Drawing the logo ...\n");
        video_console_address = video_logo ();
        #else
        video_console_address = video_fb_address;
        #endif
    #endif

    #ifdef CONFIG_VIDEO_LOGO
    /* Plot the logo and get start point of console */
    printf("Video: Drawing the logo ...\n");
    video_console_address = video_logo();
    #else
        #ifdef CONFIG_SPLASH_SCREEN
            #ifdef  LOONGSON2F_7INCH
            video_display_bitmap(BIGBMP_START_ADDR, BIGBMP_X, BIGBMP_Y);
            #else
            video_display_bitmap(PTR_PAD(PICBMP_START_ADDR), 0, 0);
            #endif
        #endif
    video_console_address = video_fb_address;
    #endif

    printf("CONSOLE_SIZE %d\n", CONSOLE_SIZE);

    /* Initialize the console */
    console_col = 0;
    console_row = 0;

    memset (console_buffer, ' ', sizeof console_buffer);

    return 0;

#endif 


#if defined(LOONGSON3A_3AEV) || defined(LOONGSON2G_2G690E)||defined(LOONGSON3A_3A780E)||defined(LOONGSON3A_3AITX)
	unsigned char color8;

    int i,j;
	pGD = &GD;

    //pGD->winSizeX  =  800;
    //pGD->winSizeY  =  600;	
    pGD->winSizeX = GetXRes();
    pGD->winSizeY = GetYRes();
    
#if   defined(CONFIG_VIDEO_1BPP)
        pGD->gdfIndex  = GDF__1BIT;
	pGD->gdfBytesPP= 1;
#elif defined(CONFIG_VIDEO_2BPP)
        pGD->gdfIndex  = GDF__2BIT;
	pGD->gdfBytesPP= 1;
#elif defined(CONFIG_VIDEO_4BPP)
        pGD->gdfIndex  = GDF__4BIT;
	pGD->gdfBytesPP= 1;
#elif defined(CONFIG_VIDEO_8BPP_INDEX)
        pGD->gdfBytesPP= 1;
        pGD->gdfIndex  = GDF__8BIT_INDEX;
#elif defined(CONFIG_VIDEO_8BPP)
	pGD->gdfBytesPP= 1;
	pGD->gdfIndex  = GDF__8BIT_332RGB;
#elif defined(CONFIG_VIDEO_16BPP)
        pGD->gdfBytesPP= 2;
        pGD->gdfIndex  = GDF_16BIT_565RGB;
#elif defined(CONFIG_VIDE0_24BPP)
        pGD->gdfBytesPP= 3;
		pGD->gdfIndex=GDF_24BIT_888RGB;
#elif defined(CONFIG_VIDEO_32BPP)
        pGD->gdfBytesPP= 4;
        pGD->gdfIndex  = GDF_32BIT_X888RGB;
#else
        pGD->gdfBytesPP= 2;
        pGD->gdfIndex  = GDF_16BIT_565RGB;
#endif
	if(fbbase<0x20000000) pGD->frameAdrs = 0xb0000000 | fbbase;
	else pGD->frameAdrs = fbbase;

	printf("cfb_console init,fb=%x\n",pGD->frameAdrs);

	video_fb_address = (void *) VIDEO_FB_ADRS;
#ifdef CONFIG_VIDEO_HW_CURSOR
	video_init_hw_cursor (VIDEO_FONT_WIDTH, VIDEO_FONT_HEIGHT);
#endif

	/* Init drawing pats */
	switch (VIDEO_DATA_FORMAT) {
#if 1
		case GDF__8BIT_INDEX:
			video_set_lut (0x01, CONSOLE_FG_COL, CONSOLE_FG_COL, CONSOLE_FG_COL);
			video_set_lut (0x00, CONSOLE_BG_COL, CONSOLE_BG_COL, CONSOLE_BG_COL);
			fgx = 0x01010101;
			bgx = 0x00000000;
			break;
#endif
		case GDF__1BIT:
			fgx=1;
			bgx=0;
			break;
		case GDF__2BIT:
			fgx=3;
			bgx=0;
			break;
		case GDF__4BIT:
			fgx=0xf;
			bgx=0;
			break;
		case GDF__8BIT_332RGB:
			color8 = ((CONSOLE_FG_COL & 0xe0) |
					((CONSOLE_FG_COL >> 3) & 0x1c) | CONSOLE_FG_COL >> 6);
			fgx = (color8 << 24) | (color8 << 16) | (color8 << 8) | color8;
			color8 = ((CONSOLE_BG_COL & 0xe0) |
					((CONSOLE_BG_COL >> 3) & 0x1c) | CONSOLE_BG_COL >> 6);
			bgx = (color8 << 24) | (color8 << 16) | (color8 << 8) | color8;
			break;
		case GDF_15BIT_555RGB:
			fgx = (((CONSOLE_FG_COL >> 3) << 26) |
					((CONSOLE_FG_COL >> 3) << 21) | ((CONSOLE_FG_COL >> 3) << 16) |
					((CONSOLE_FG_COL >> 3) << 10) | ((CONSOLE_FG_COL >> 3) << 5) |
					(CONSOLE_FG_COL >> 3));
			bgx = (((CONSOLE_BG_COL >> 3) << 26) |
					((CONSOLE_BG_COL >> 3) << 21) | ((CONSOLE_BG_COL >> 3) << 16) |
					((CONSOLE_BG_COL >> 3) << 10) | ((CONSOLE_BG_COL >> 3) << 5) |
					(CONSOLE_BG_COL >> 3));
			break;
		case GDF_16BIT_565RGB:
			fgx = (((CONSOLE_FG_COL >> 3) << 27) |
					((CONSOLE_FG_COL >> 2) << 21) | ((CONSOLE_FG_COL >> 3) << 16) |
					((CONSOLE_FG_COL >> 3) << 11) | ((CONSOLE_FG_COL >> 2) << 5) |
					(CONSOLE_FG_COL >> 3));
			bgx = (((CONSOLE_BG_COL >> 3) << 27) |
					((CONSOLE_BG_COL >> 2) << 21) | ((CONSOLE_BG_COL >> 3) << 16) |
					((CONSOLE_BG_COL >> 3) << 11) | ((CONSOLE_BG_COL >> 2) << 5) |
					(CONSOLE_BG_COL >> 3));
			break;
		case GDF_32BIT_X888RGB:
			fgx = (CONSOLE_FG_COL << 16) | (CONSOLE_FG_COL << 8) | CONSOLE_FG_COL;
			bgx = (CONSOLE_BG_COL << 16) | (CONSOLE_BG_COL << 8) | CONSOLE_BG_COL;
			break;
		case GDF_24BIT_888RGB:
			fgx = (CONSOLE_FG_COL << 24) | (CONSOLE_FG_COL << 16) |
				(CONSOLE_FG_COL << 8) | CONSOLE_FG_COL;
			bgx = (CONSOLE_BG_COL << 24) | (CONSOLE_BG_COL << 16) |
				(CONSOLE_BG_COL << 8) | CONSOLE_BG_COL;
			break;
	}
	eorx = fgx ^ bgx;

	memsetl (video_fb_address, VIDEO_COLS * VIDEO_ROWS * VIDEO_PIXEL_SIZE / 4, CONSOLE_BG_COL);
#ifdef CONFIG_VIDEO_LOGO
	/* Plot the logo and get start point of console */
	printf("Video: Drawing the logo ...\n");
	video_console_address = video_logo ();
#else
    #ifdef CONFIG_SPLASH_SCREEN
    video_display_bitmap(PTR_PAD(PICBMP_START_ADDR), 0, 0);
    #endif
	video_console_address = video_fb_address;
#endif
	printf("CONSOLE_SIZE %d\n", CONSOLE_SIZE);

	/* Initialize the console */
	console_col = 0;
	console_row = 0;

	memset (console_buffer, ' ', sizeof console_buffer);
//#if defined(MEM_PRINTTO_VIDEO)
	memfb = malloc(CONSOLE_ROWS * CONSOLE_COLS);
	memset (memfb, 0, CONSOLE_ROWS * CONSOLE_COLS);
//#endif
return 0;
#endif
}

int getX(void)
{
    return console_col;
}

int getY(void)
{
    return console_row;
}

void setX(int x)
{
    if(x > CONSOLE_COLS)
        x = CONSOLE_COLS;
    console_col = x;
}

void setY(int y)
{
    if(y > CONSOLE_ROWS )   
        y = CONSOLE_ROWS;
    console_row = y;
}

//get the width of screen(units:font)
int get_scr_width(void)
{
    return GD.winSizeX/VIDEO_FONT_WIDTH;
}

int get_scr_height(void)
{
    return GD.winSizeY/VIDEO_FONT_HEIGHT;
}
