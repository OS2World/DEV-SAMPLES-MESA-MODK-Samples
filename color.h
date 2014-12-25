/**************************************************************************
 *                                                                        *
 *                                                                        *
 *          This code is copyright (c) 1994                               *
 *                     Athena Design, Inc.                                *
 *                                                                        *
 *                                                                        *
 *                ALL RIGHTS RESERVED                                     *
 *                                                                        *
 *                                                                        *
 *                                                                        *
 *                                                                        *
 *                                                                        *
 **************************************************************************/

// dpr was here
/*
    this is the header file for the color model on Mesa.
    Each color consists of two integers.  The first is of the format:
    (16777216 * pat) + (r * 65536) + (g * 256) + b
    if pat != 0, then pat specifies the pattern that is overlayed on the
    color represented in the second it.  If that color has a pattern of
    255, then it is assumed to be clear.

    2-27-94 dpp

    94-09-04 dpp changed MColor so that it does not have a constructor, but has
        init() and free() methods
*/

#ifndef _MH_color

#define _MH_color

class MStream;

class MColor {
    public:
    void init(int t) {pCol = t; bkgCol = 0;};
    void init(const MColor *cp) {pCol = cp -> pCol; bkgCol = cp -> bkgCol;};
    void free() {};
    void init() {};
    void set(int t) {pCol = t; bkgCol = 0;};
    void set(MColor c) {*this = c;};
    void set(const MColor *cp) {*this = *cp;};
    void set(int r,int g,int b) {pCol = r * 65536 + g * 256 + b; bkgCol = 0;};
	unsigned int getRed() { return ( ( pCol & 0xFF0000 )/65536 ); }
	unsigned int getGreen()	{ return ( ( pCol & 0x00FF00 )/256 ); }
	unsigned int getBlue()	{ return ( pCol & 0x0000FF ); }

	unsigned int getBkgRed() { return ( ( bkgCol & 0xFF0000 )/65536 ); }
	unsigned int getBkgGreen()	{ return ( ( bkgCol & 0x00FF00 )/256 ); }
	unsigned int getBkgBlue()	{ return ( bkgCol & 0x0000FF ); }
    // set a color to a named color string
    int set(const char *);

    int getRGB() {return pCol & 0xffffff;};
    int getColor() {return pCol;};
    int getPattern() {return pCol >> 24;};
    int getBkgRGB() {return bkgCol & 0xffffff;};
    int getBkgPattern() {return bkgCol >> 24;};
    int operator==(const MColor &c) const
        {if (pCol == c.pCol && bkgCol == c.bkgCol) return 1; else return 0;};
    int operator!=(const MColor &c) const
        {if (pCol != c.pCol || bkgCol != c.bkgCol) return 1; else return 0;};

    int operator>(const MColor &c) const
        {if (pCol > c.pCol || (pCol == c.pCol && bkgCol > c.bkgCol)) return 1; else return 0;};
    int operator>=(const MColor &c) const
        {if (pCol > c.pCol || (pCol == c.pCol && bkgCol >= c.bkgCol)) return 1; else return 0;};
    int operator<(const MColor &c) const
        {if (pCol < c.pCol || (pCol == c.pCol && bkgCol < c.bkgCol)) return 1; else return 0;};
    int operator<=(const MColor &c) const
        {if (pCol < c.pCol || (pCol == c.pCol && bkgCol <= c.bkgCol)) return 1; else return 0;};

    void read(MStream *);
    void write(MStream *) const;

    // average between the solid portion of the two colors
    void average(MColor);

    void init(MStream *sp) {read(sp);};

	// locate an index into a palette, or return the closest match...
	int getColorFromPalette( MColor *palette, int numInPalette );
	
    private:
    unsigned int pCol,bkgCol;
};

const int MCOL_LTGRAY = 0x00cccccc;
const int MCOL_DKGRAY = 0x00555555;
const int MCOL_GRAY   = 0x00808080;
const int MCOL_BLACK = 0;
const int MCOL_WHITE = 0xffffff;
const int MCOL_RED = 0x00ff0000;
const int MCOL_GREEN = 0x0000ff00;
const int MCOL_BLUE = 0xff;
const int MCOL_CYAN = (MCOL_GREEN | MCOL_BLUE);
const int MCOL_YELLOW = (MCOL_RED | MCOL_GREEN);
const int MCOL_MAGENTA = (MCOL_RED | MCOL_BLUE);

#ifdef M2Z
#define MCOL_3D_LIGHT  WinQuerySysColor(HWND_DESKTOP,SYSCLR_BUTTONLIGHT,0)
#define MCOL_3D_DARK  WinQuerySysColor(HWND_DESKTOP,SYSCLR_BUTTONDARK,0)
#define MCOL_BUTTONFACE WinQuerySysColor(HWND_DESKTOP,SYSCLR_BUTTONMIDDLE,0)
#define MCOL_DIALOGBACK WinQuerySysColor(HWND_DESKTOP,SYSCLR_DIALOGBACKGROUND,0)
#define MCOL_BUTTONTEXT WinQuerySysColor(HWND_DESKTOP,SYSCLR_MENUTEXT,0)

#else
//FIXMEMAC
//FIXMENT
#define MCOL_3D_LIGHT MCOL_WHITE
#define MCOL_3D_DARK  MCOL_DKGRAY
#define MCOL_BUTTONFACE MCOL_LTGRAY
#define MCOL_DIALOGBACK MCOL_LTGRAY
#define MCOL_BUTTONTEXT MCOL_BLACK
#endif

// ifndef _MH_color
#endif
