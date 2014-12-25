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

/*
    This is the header file for formats.  It defines the format of what a
    cell looks like.
    3-29-94 dpp
    
    94-09-05 dpp defined the number formating
*/

#ifndef _MH_format

#define _MH_format

#include "color.h"
#include "stream.h"

// 94-09-05 dpp
// the number format is a 16 bit number that defines the formating of the contents
// of the cell.  If bit 15 is set, the remaining number is a pointer to a "print using"
// formating table in the model (this is currently not supported).
// The formated numbers fall into four catagories: unformatted, decimal, currency, date
// bits 9 - 11 designate the type
// bits 6 - 8 designate the sub-type within a given type
// bits 4 - 5 designate a selector (this is used for currency formating)
// bits 0 - 3 is the number of decimal places

// this &'ed with the format should return 0
const unsigned int maskOldFormat = 0xf000;

// decimal place mask
const int maskDecimalFormat = 0xf;

// selector mask
const maskSelectorFormat = 0x30;
const rotateSelectorFormat = 4;

const int rotateTypeFormat = 9; // number of bits to rotate
const unsigned int maskTypeFormat = (7 << rotateTypeFormat);

const unsigned int unformattedTypeFormat = (0 << rotateTypeFormat);
const unsigned int decimalTypeFormat = (1 << rotateTypeFormat);
const unsigned int currencyTypeFormat = (2 << rotateTypeFormat);
const unsigned int dateTimeTypeFormat = (3 << rotateTypeFormat);

// within each type, there are a series of sub-types.  The sub-type is designation within
// each type of what to do

const int rotateSubtypeFormat = 6;
const unsigned int maskSubtypeFormat = (7 << rotateSubtypeFormat);

// unformattedType
const unsigned int generalSubtypeFormat = (0 << rotateSubtypeFormat);
const unsigned int textSubtypeFormat = (1 << rotateSubtypeFormat);
const unsigned int hiddenSubtypeFormat = (2 << rotateSubtypeFormat);

// decimalType
const unsigned int fixedSubtypeFormat = (0 << rotateSubtypeFormat);
const unsigned int sciSubtypeFormat = (1 << rotateSubtypeFormat);
const unsigned int percentSubtypeFormat (2 << rotateSubtypeFormat);

// currencyType
const unsigned int currencySubtypeFormat = (0 << rotateSubtypeFormat);
const unsigned int commaSubtypeFormat = (1 << rotateSubtypeFormat);

// dateTimeType
const unsigned int dateSubtypeFormat = (0 << rotateSubtypeFormat);
const unsigned int timeSubtypeFormat = (1 << rotateSubtypeFormat);

// the following are a series of constants for date formating
const unsigned int dateMDYFormat = 0; // MM/DD/YY 01/02/64
const unsigned int dateMMsDDsYYFormat = 0;		// same as above...
const unsigned int dateMDFormat = 1; // MM/DD 01/02
const unsigned int dateDMFormat = 2; // DD-MMM 02-Jan
const unsigned int dateDMYFormat = 3; // DD-MMM-YY 02-Jan-64
const unsigned int dateMYFormat = 4; // MMM-YY Jan-64
const unsigned int dateYMDFormat = 5; // YY/MM/DD 64/01/02
const unsigned int dateYYsMMsDDFormat = 5;	// same as above
const unsigned int dateDDMonYYFormat = 6; // DDMonYY 02Jan64
const unsigned int dateMonDDYYFormat = 7; // MonDDYY Jan0264
const unsigned int dateDDMonFormat = 8; // DDMon 02Jan
const unsigned int dateMMDDYYFormat = 9; // MMDDYY 010264
const unsigned int dateMMDDFormat = 10; // MMDD 0102
const unsigned int dateDDMMFormat = 11; // DDMM 0201
const unsigned int dateDDMMYYFormat = 12; // DDMMYY 020164
const unsigned int dateMDY2Format = 13; // Mon-DD-YY Jan-02-64
const unsigned int dateMD2Format = 14; // Mon-DD Jan-02
const unsigned int dateDATEFormat = 15; // Jan 02, 1964
const unsigned int dateDDMMYYYYFormat = 16;
const unsigned int dateMMDDYYYYFormat = 17;
const unsigned int dateMMYYYYFormat = 18;
const unsigned int dateYYMMDDFormat = 19;
const unsigned int dateDD_MON_YYYYFormat = 20;
const unsigned int dateMON_DD_YYYYFormat = 21;
const unsigned int dateMON_YYYYFormat = 22;
const unsigned int dateDD_MM_YYYYFormat = 23;
const unsigned int dateMM_DD_YYYYFormat = 24;
const unsigned int dateDD_MMFormat = 25;
const unsigned int dateMM_DDFormat = 26;
const unsigned int dateMM_YYYYFormat = 27;
const unsigned int dateDD_MM_YYFormat = 28;
const unsigned int dateMM_DD_YYFormat = 29;
const unsigned int dateDDsMMsYYYYFormat = 30;
const unsigned int dateMMsDDsYYYYFormat = 31;
const unsigned int dateDDsMMFormat = 32;
const unsigned int dateMMsYYYYFormat = 33;
const unsigned int dateDDsMMsYYFormat = 34;
const unsigned int dateDDpMMpYYYYFormat = 35;
const unsigned int dateMMpDDpYYYYFormat = 36;
const unsigned int dateDDpMMFormat = 37;
const unsigned int dateMMpDDFormat = 38;
const unsigned int dateMMpYYYYFormat = 39;
const unsigned int dateDDpMMpYYFormat = 40;
const unsigned int dateMMpDDpYYFormat = 41;	// 01x31x94, e.g.
const unsigned int dateDDxMMxYYYYFormat = 42;
const unsigned int dateMMxDDxYYYYFormat = 43;
const unsigned int dateDDxMMFormat = 44;
const unsigned int dateMMxDDFormat = 45;
const unsigned int dateMMxYYYYFormat = 46;
const unsigned int dateDDxMMxYYFormat = 47;
const unsigned int dateMMxDDxYYFormat = 48;	// 01x31x94, e.g.
const unsigned int dateDefaultFormat = 49;		// use system settings
const unsigned int dateYYxMMxDDFormat = 50;
const unsigned int dateYYpMMpDDFormat = 51;
const unsigned int dateYY_MM_DDFormat = 52;

// the following are a series of constants for time formating
const unsigned int timeHMS12Format = 0;
const unsigned int timeHM12Format = 1;
const unsigned int timeHMS24Format = 2;
const unsigned int timeHM24Format = 3;
const unsigned int timeDefaultFormat = 4;
const unsigned int timeHMS24EditFormat = 5;	// hard-coded to be colons, so 
										// we can edit it...

const int generalFormat = (unformattedTypeFormat | generalSubtypeFormat);
const int hiddenFormat = (unformattedTypeFormat | hiddenSubtypeFormat);
const int textFormat = (unformattedTypeFormat | textSubtypeFormat);
const int fixedFormat = (decimalTypeFormat | fixedSubtypeFormat | 2);
const int currencyFormat = (currencyTypeFormat | currencySubtypeFormat | 2);
const int commaFormat = (currencyTypeFormat | commaSubtypeFormat | 2);
const int percentFormat = (decimalTypeFormat | percentSubtypeFormat | 2);
const int sciFormat = (decimalTypeFormat | sciSubtypeFormat | 3);
const int timeFormat = (dateTimeTypeFormat | timeSubtypeFormat | timeDefaultFormat);
const int dateFormat = (dateTimeTypeFormat | dateSubtypeFormat | dateDefaultFormat);

class MFormat {
    public:
    void init();
    void init(const MFormat *);
    void free() {};

    // file IO stuff
    void init(MStream *);
    void write(MStream *);

    int operator==(const MFormat &mf) const {
        return (text == mf.text && bkg == mf.bkg &&
            borderCols[0] == mf.borderCols[0] &&
            borderCols[1] == mf.borderCols[1] &&
            borderCols[2] == mf.borderCols[2] &&
            borderCols[3] == mf.borderCols[3] &&
            font == mf.font && format == mf.format &&
            info == mf.info);
    };


    MColor getTextColor() const {return text;};
    MColor getBkgColor() const {return bkg;};
    MColor getBorderColor(int n) const {return borderCols[n];};
    void setTextColor(MColor c) {text = c;};
    void setTextColor(int c) {text.set(c);};
    void setBkgColor(MColor c) {bkg = c;};
    void setBkgColor(int c) {bkg.set(c);};
    void setBorderColor(int n,MColor c) {borderCols[n] = c;};

    int getFont() const {return font;};
    void setFont(int i) {font = i;};

    int getFormat() const {return format;};
    int getFormatSansPrec() const
    {
        if ((format & maskTypeFormat) == decimalTypeFormat ||
            (format & maskTypeFormat) == currencyTypeFormat)
            return (format & ~maskDecimalFormat);
            
        return format;
    };
    void setFormat(int i) {format = i;};
    // set the format to a named format type with a given precision
    int setFormat(const char *,int);
    int getPrecision() const {return format & maskDecimalFormat;};
    void setPrecision(int i) {if ((format & maskTypeFormat) == decimalTypeFormat ||
        (format & maskTypeFormat) == currencyTypeFormat)
            format = (format & ~maskDecimalFormat) | (i & maskDecimalFormat);
        };

    int hasBorders() const {return (info & 0xff);};
    int getBorder(int i) const {return 0x3 & (info >> (i * 2));};
    void setBorder(int i,int n) {info = (~(0x3 << (i * 2)) & info) | ((n & 0x3) << (i * 2));};

    int getAlignment() const {return (info & 0x700) >> 8;};
    void setAlignment(int i) {info = (info & ~0x700) | (0x700 & (i << 8));};
    int getProtected() const {return (info & 0x800) >> 11;};
    void setProtected(int i) {info = (info & ~0x800) | (0x800 & (i << 11));};
    int getInputType() const {return (info & 0x7000) >> 12;};
    void setInputType(int i) {info = (info & ~0x7000) | (0x7000 & (i << 12));};
    int getScriptOnInput() const {return ((info & 0x8000) >> 15);};
    void setScriptOnInput(int i) {info = (info & ~0x8000) | (0x8000 & (i << 15));};
    int getUnderline() const {return (info & 0x30000) >> 16;};
    void setUnderline(int i) {info = (info & ~0x30000) | (0x30000 & (i << 16));};
    int getWrap() const {return (info & 0x40000) >> 18;};
    void setWrap(int i) {info = (info & ~0x40000) | (0x40000 & (i << 18));};
    int getHidden() const {return (info & 0x80000) >> 19;};
    void setHidden(int i) {info = (info & ~0x80000) | (0x80000 & (i << 19));};
    int getVertAlign() const {return (info & 0x300000) >> 20;};
    void setVertAlign(int i) {info = (info & ~0x300000) | (0x300000 & (i << 20));};
    int getClearBkg() const {return (info & 0x400000) >> 22;};
    void setClearBkg(int i) {info = (info & ~0x400000) | (0x400000 & (i << 22));};

    void setMergeTextColor(int i) {merge = (merge & ~0x1) | (1 & i);};
    void setMergeBorderColor1(int i) {merge = (merge & ~0x2) | (0x2 & (i << 1));};
    void setMergeBorderColor2(int i) {merge = (merge & ~0x4) | (0x4 & (i << 2));};
    void setMergeBorderColor3(int i) {merge = (merge & ~0x8) | (0x8 & (i << 3));};
    void setMergeBorderColor4(int i) {merge = (merge & ~0x10) | (0x10 & (i << 4));};
    void setMergeBorder1(int i) {merge = (merge & ~0x20) | (0x20 & (i << 5));};
    void setMergeBorder2(int i) {merge = (merge & ~0x40) | (0x40 & (i << 6));};
    void setMergeBorder3(int i) {merge = (merge & ~0x80) | (0x80 & (i << 7));};
    void setMergeBorder4(int i) {merge = (merge & ~0x100) | (0x100 & (i << 8));};
    void setMergeAlignment(int i) {merge = (merge & ~0x200) | (0x200 & (i << 9));};
    void setMergeProtected(int i) {merge = (merge & ~0x400) | (0x400 & (i << 10));};
    void setMergeInputType(int i) {merge = (merge & ~0x800) | (0x800 & (i << 11));};
    void setMergeScriptOnInput(int i) {merge = (merge & ~0x1000) | (0x1000 & (i << 12));};
    void setMergeUnderline(int i) {merge = (merge & ~0x2000) | (0x2000 & (i << 13));};
    void setMergeWrap(int i) {merge = (merge & ~0x4000) | (0x4000 & (i << 14));};
    void setMergeHidden(int i) {merge = (merge & ~0x8000) | (0x8000 & (i << 15));};
    void setMergeVertAlign(int i) {merge = (merge & ~0x10000) | (0x10000 & (i << 16));};
    void setMergeBkgColor(int i) {merge = (merge & ~0x20000) | (0x20000 & (i << 17));};
    void setMergeFont(int i) {merge = (merge & ~0x40000) | (0x40000 & (i << 18));};
    void setMergePrecision(int i) {merge = (merge & ~0x80000) | (0x80000 & (i << 19));};
    void setMergeFormat(int i) {merge = (merge & ~0x100000) | (0x100000 & (i << 20));};

    int getMergeTextColor() const {return merge & 0x1;};
    int getMergeBorderColor1() const {return (merge & 0x2) >> 1;};
    int getMergeBorderColor2() const {return (merge & 0x4) >> 2;};
    int getMergeBorderColor3() const {return (merge & 0x8) >> 3;};
    int getMergeBorderColor4() const {return (merge & 0x10) >> 4;};
    int getMergeBorder1() const {return (merge & 0x20) >> 5;};
    int getMergeBorder2() const {return (merge & 0x40) >> 6;};
    int getMergeBorder3() const {return (merge & 0x80) >> 7;};
    int getMergeBorder4() const {return (merge & 0x100) >> 8;};
    int getMergeAlignment() const {return (merge & 0x200) >> 9;};
    int getMergeProtected() const {return (merge & 0x400) >> 10;};
    int getMergeInputType() const {return (merge & 0x800) >> 11;};
    int getMergeScriptOnInput() const {return (merge & 0x1000) >> 12;};
    int getMergeUnderline() const {return (merge & 0x2000) >> 13;};
    int getMergeWrap() const {return (merge & 0x4000) >> 14;};
    int getMergeHidden() const {return (merge & 0x8000) >> 15;};
    int getMergeVertAlign() const {return (merge & 0x10000) >> 16;};
    int getMergeBkgColor() const {return (merge & 0x20000) >> 17;};
    int getMergeFont() const {return (merge & 0x40000) >> 18;};
    int getMergePrecision() const {return (merge & 0x80000) >> 19;};
    int getMergeFormat() const {return (merge & 0x100000) >> 20;};

    void mergeFormat(const MFormat &);

    private:
    MColor text,bkg;
    MColor borderCols[4];
    unsigned short font;
    unsigned short format;
    unsigned int info;
    unsigned int merge;

    /*
    unsigned int borders; // 8 bits
    int alignment; // 3 bits
    int protection; // 1 bit
    int inputType; // 3 bits
    int scriptOnInput; // 1 bit
    int underline; // 2 bits
    int wrap; // 1 bit
    int hidden; // 1 bit
    int vert align // 2 bits
    */

    /*
    0 text color
    1 bkg color
    2 border color 1
    3 border color 2
    4 border color 3
    5 border color 4
    6 border 1
    7 border 2
    8 border 3
    9 border 4
    10 alignment
    11 protection
    12 input type
    13 scriptOnInput
    14 underline
    15 wrap
    16 hidden
    17 vert alignment
    */
};


const int generalAlignment = 0;
const int leftAlignment = 1;
const int rightAlignment = 2;
const int centerAlignment = 3;

const int vertBottomAlignment = 0;
const int vertTopAlignment = 1;
const int vertCenterAlignment = 2;

const int allInputType = 0;
const int numbersInputType = 1;
const int stringsInputType = 2;
const int datesInputType = 3;
const int formulasInputType = 4;

const int topBorder = 2;
const int bottomBorder = 3;
const int leftBorder = 0;
const int rightBorder = 1;

// ifdef _MH_format
#endif

