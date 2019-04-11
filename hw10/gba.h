#ifndef GBA_H
#define GBA_H

// ---------------------------------------------------------------------------
//                       USEFUL TYPEDEFS
// ---------------------------------------------------------------------------
/** An unsigned 32-bit (4-byte) type */
typedef unsigned int u32;

/** An unsigned 16-bit (2-byte) type */
typedef unsigned short u16;

/** An unsigned 8-bit (1-byte) type. Note that this type cannot be written onto RAM directly. */
typedef unsigned char u8;

// ---------------------------------------------------------------------------
//                       MODE3 MACROS
// ---------------------------------------------------------------------------
#define OFFSET(r, c, rowlen) ((c)+(rowlen)*(r))
#define ENCODE_COORDINATES(x, y) ((y)* WIDTH + (x))
#define DECODE_Y(a) ((a) / WIDTH)
#define DECODE_X(a) ((a) % WIDTH)

#define REG_DISPCNT  *(volatile unsigned short *) 0x4000000
#define MODE3 3
#define BG2_ENABLE (1<<10)
#define OBJ_ENABLE (1<<12)

typedef struct {
    u16 attr0;
    u16 attr1;
    u16 attr2;
    u16 fill;
} OamEntry;

#define SPRITEMEM ((OamEntry *)0x7000000)

typedef struct {
    u16 tileimg[8192];
} charblock;
#define CHARBLOCKBASE ((charblock *)0x6000000)

#define SPRITEDATA ((u16 *)(0x6010000))
#define SPRITEPAL ((u16 *)0x5000200)
#define MODE1D (1 << 6)

// ATTR0

// 0-7 Row position of the top of the sprite.

// 8-9 Object Mode
#define ATTR0_REG (0 << 8)
#define ATTR0_AFF (1 << 8)
#define ATTR0_HIDE (2 << 8)
#define ATTR0_AFF_DBL (3 << 8)

// 10-11 Graphics Mode for special effects
#define ATTR0_BLEND (1 << 10)  // Forbidden to use both of these
#define ATTR0_WIN (2 << 10)

// 12 Mosaic Effect
#define ATTR0_MOSAIC (1 << 12)

// 13 Color Mode
#define ATTR0_4BPP 0          // 16 colors
#define ATTR0_8BPP (1 << 13)  // 256 colors

// 14-15 Shape
#define ATTR0_SQUARE 0
#define ATTR0_WIDE (1 << 14)
#define ATTR0_TALL (2 << 14)

// ATTR1

// 0-8 Column position of left hand side of sprite

// 9-13 Valid if Affine Flag (Attribute 0 Bit 8)
// Defines which OAM_AFF_ENTY this sprite uses.

// 12-13
#define ATTR1_NOFLIP 0
#define ATTR1_HFLIP (1 << 12)
#define ATTR1_VFLIP (1 << 13)
// Used only if the Affine Flag (Attribute 0 Bit 8) is clear

// 14-15 Size...Together with the shape bits Attribute 0 Bits 14-15
// these determine the sprite's real size, see table:

//                                          col x row
/*-------------------------------------------------------------
 *
 *       Size                   00      01      10      11
 *   Shape
 *              00              8x8     16x16   32x32   64x64
 *         Wide 01              16x8    32x8    32x16   64x32
 *         Tall 10              8x16    8x32    16x32   32x64
 *------------------------------------------------------------*/
#define ATTR1_SIZE8 0
#define ATTR1_SIZE16 (1 << 14)
#define ATTR1_SIZE32 (2 << 14)
#define ATTR1_SIZE64 (3 << 14)

// ATTR2

// 0-9 Base tile-index of sprite. Note that in bitmap modes this must
// be 512 or higher.

// 10-11 Priority. Higher priorities are drawn first (and therefore
// can be covered by later sprites and backgrounds). Sprites cover
// backgrounds of the same priority, and for sprites of the same
// priority, the higher OBJ_ATTRs are drawn first.
#define ATTR2_PRI0 0
#define ATTR2_PRI1 (1 << 10)
#define ATTR2_PRI2 (2 << 10)
#define ATTR2_PRI3 (3 << 10)

// 12-15 Palette-bank to use when in 16-color mode. Has no effect if
// the color mode flag Attribute 0 Bit 12 is set.
#define ATTR2_PALETTE_BANK(pbn) ((pbn) << 12)

#define COLOR(r, g, b) ((r) | (g)<<5 | (b)<<10)
#define WHITE COLOR(31,31,31)
#define RED COLOR(31,0,0)
#define GREEN COLOR(0,31,0)
#define BLUE COLOR(0,0,31)
#define MAGENTA COLOR(31, 0, 31)
#define CYAN COLOR(0, 31, 31)
#define YELLOW COLOR(31, 31, 0)
#define BLACK 0
#define GRAY COLOR(5, 5, 5)

// The size of the GBA Screen
#define WIDTH 240
#define HEIGHT 160

// This is initialized in gba.c
extern volatile unsigned short *videoBuffer;

// ---------------------------------------------------------------------------
//                       BUTTON INPUT
// ---------------------------------------------------------------------------
#define BUTTON_A		(1<<0)
#define BUTTON_B		(1<<1)
#define BUTTON_SELECT	(1<<2)
#define BUTTON_START	(1<<3)
#define BUTTON_RIGHT	(1<<4)
#define BUTTON_LEFT		(1<<5)
#define BUTTON_UP		(1<<6)
#define BUTTON_DOWN		(1<<7)
#define BUTTON_R		(1<<8)
#define BUTTON_L		(1<<9)

#define BUTTONS *(volatile u32 *) 0x4000130
#define KEYS_DOWN(keys, buttons) ((~(buttons) & (keys)) > 0)

// TA-TODO: COMPLETE THIS MACRO.
// Remember that a button is recently pressed if it wasn't pressed in the last
// input (oldButtons) but is pressed in the current input. Use the KEY_DOWN
// macro to check if the button was pressed in the inputs.
#define KEY_JUST_PRESSED(key, buttons, oldbuttons) \
    ((KEYS_DOWN((key), (buttons))) && !(KEYS_DOWN((key), (oldbuttons))))

// ---------------------------------------------------------------------------
//                       DMA
// ---------------------------------------------------------------------------
typedef struct
{
	const volatile void *src;
	const volatile void *dst;
	u32                  cnt;
} DMA_CONTROLLER;

#define DMA ((volatile DMA_CONTROLLER *) 0x040000B0)

// Defines
#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_DESTINATION_RESET (3 << 21)

#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_REPEAT (1 << 25)

#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)

#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)

// ---------------------------------------------------------------------------
//                       VBLANK
// ---------------------------------------------------------------------------
#define SCANLINECOUNTER *(volatile unsigned short *)0x4000006

// Use this variable to count vBlanks. Initialized in gba.c and to be
// manipulated by waitForVBlank()
extern u32 vBlankCounter;

/**
 * Runs a blocking loop until the start of next VBlank.
 */
void waitForVBlank(void);

// ---------------------------------------------------------------------------
//                       MISC
// ---------------------------------------------------------------------------
#define UNUSED(param) ((void)((param)))

/**
 * Generates a pseudo-random number between min and max, inclusive.
 *
 * @param  min bottom end of range.
 * @param  max top end of range.
 * @return random number in the given range.
 */
int randint(int min, int max);

// ---------------------------------------------------------------------------
//                       DRAWING
// ---------------------------------------------------------------------------
void setPixel(int x, int y, u16 color);
void drawRectDMA(int x, int y, int width, int height, volatile u16 color);
void drawFullScreenImageDMA(const u16 *image);
void drawImageDMA(int x, int y, int width, int height, const u16 *image);
void drawPartBackground(int x, int y, int width, int height, const u16 *image);
void fillScreenDMA(volatile u16 color);
void drawChar(int col, int row, char ch, u16 color);
void drawString(int col, int row, char *str, u16 color);
void drawCenteredString(int col, int row, int width, int height, char *str, u16 color);

/** Contains the pixels of each character from a 6x8 font */
// This is in the font.c file. You can replace the font if you want.
extern const unsigned char fontdata_6x8[12288];

#endif
