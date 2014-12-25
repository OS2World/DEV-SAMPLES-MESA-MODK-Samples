/**************************************************************************
 *                                                                        *
 *                                                                        *
 *          This code is copyright (c) 1994 & 1995                        *
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

/*
    holds the font information for a given font
    5-31-94 dpp

    modify to init from OS/2 font names dpp 8/14/94
    94-09-19 dpp added operator=()
*/

#ifndef _MH_font

#define _MH_font

#include "mlib.h"

class MStream;

#define MMaxFontInfo 4

class MFont {
    public:
    void init();
    void init(MStream *);
    void init(const MFont *);
    void write(MStream *) const;

    // initialize the font from an OS/2 font name string
    // 12. Tms Roman.
    void init(const char *);

	
	void getSystemName( char * buf) const;

    void free() {};
    int operator==(const MFont &f) const
        {return (size == f.size && !MStrCmp(fontName,f.fontName));};
    MFont &operator=(const MFont &);
    MFont &operator=(const MFont *);

    const char *getName() const {return fontName;};
    void getBaseName(char *s) const;
    int getSize() const {return size;};
    void setName(const char *);
    void setSize(int);
    void makeBold(int);
    void makePlain(int);
    void makeItalic(int);

    int makeBitmap();
    int makeVector();

    int isBitmapAllowed() const { return bitmapAllowed; };

    int isBold() const;
    int isItalic() const;

    // use for internal caching stuff
    int getInfo(int n) const {return info[n];};
    void setInfo(int n,int i) {info[n] = i;};

    int getCacheNum() const { return cacheNum;};
    void setCacheNum( int i) const;

    private:
    int size;
    char fontName[60];
    int bitmapAllowed;
    int info[MMaxFontInfo];
    int cacheNum;
};

const int CACHE_NOT_CHECKED = -1;
const int NOT_IN_CACHE = -2;

//ifndef _MH_font
#endif

