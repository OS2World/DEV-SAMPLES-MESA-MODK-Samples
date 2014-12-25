/**************************************************************************
 *                                                                        *
 *                                                                        *
 *          This code is copyright (c)        1994                        *
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

#ifndef _mh_TAG_ADDRESS__

#define _mh_TAG_ADDRESS__

/*
    the address is a three dimensional coordinate
    the theCol and theRow fields are the number of the row or column
    the first 12 bits of theLayer contain the layer number
    Bits in layer:
    12 - relative row
    13 - relative col
    14 - relative layer
    15 - null if set
*/

#define NULLADDRESS (1 << 15)
#define ABSROW (1 << 12)
#define ABSCOL (1 << 13)
#define ABSLAYER (1 << 14)
#define LAYERMASK (4095)
#define LAYERBITMASK (0x7000)
//#define MAXCOL (18277)
//#define MAXROW (999999)
//#define MAXROW (32766)
//#define MAXLAYER (701)
#define ROWMASK (0xffffff)
#define COLMASK (0xffff)

extern int theMAXCOL,theMAXROW,theMAXLAYER;

#define MAXCOL (theMAXCOL)
#define MAXROW (theMAXROW)
#define MAXLAYER (theMAXLAYER)

class MStream;

class MAddress {
    public:
    // create a null value, initialize
    void init() {theRow = 0; theCol = 0; theLayer = 0 | NULLADDRESS;};
    void init(int r,int c,int l) {theRow = r & ROWMASK; theCol = c & COLMASK;
				  theLayer = (l & LAYERMASK);};
    void init(const MAddress *a) {*this = *a;};
    void init(MStream *sp) {read(sp);};

    // set to null, cleanup
    void free() {init();};
    void zap() {theRow = 0; theCol = 0; theLayer = NULLADDRESS;};
    void makeNull() {zap();};

    // get the column, row or layer
    int getCol() const {return theCol;};
    int getRow() const {return theRow;};
    int getLayer() const {return theLayer & LAYERMASK;};

    // set address
    void set(const MAddress *a1) {*this = *a1;};
    void set(int r,int c,int l) {theRow = r & ROWMASK; theCol = c & COLMASK;
				 theLayer = (l & LAYERMASK);};

    // set the row, col, or layer and make them relative
    void setRow(int r) {theLayer &= ~ABSROW; theRow = r & ROWMASK;};
    void setCol(int c) {theLayer &= ~ABSCOL; theCol = c & COLMASK;};
    void setLayer(int l) {theLayer = (l & LAYERMASK) |
			  (theLayer & ~LAYERMASK & ~ABSLAYER);};

    // set the attributes without affecting the ABS values
    void setRawRow(int r) {theRow = r & ROWMASK;};
    void setRawCol(int c) {theCol = c & COLMASK;};
    void setRawLayer(int l) {theLayer = (theLayer & ~LAYERMASK) | (l & LAYERMASK);};

    // get and set absolute values
    void setAbsRow(int i) {if (i) theLayer |= ABSROW; else theLayer &= ~ABSROW;};
    void setAbsCol(int i) {if (i) theLayer |= ABSCOL; else theLayer &= ~ABSCOL;};
    void setAbsLayer(int i) {if (i) theLayer |= ABSLAYER; else theLayer &= ~ABSLAYER;};
    void makeAbs() {theLayer |= ABSLAYER | ABSROW | ABSCOL;};

    int getAbsRow() const {return theLayer & ABSROW;};
    int getAbsCol() const {return theLayer & ABSCOL;};
    int getAbsLayer() const {return theLayer & ABSLAYER;};

    // swap values
    void swapRowInfo(MAddress &);
    void swapColInfo(MAddress &);
    void swapLayerInfo(MAddress &);

    // offset values
    void offset(int,int,int);
    void offsetRel(int,int,int);
    void offsetAbs(int,int,int);

    // operator overloading
    int operator== (const MAddress &a1) const {
        if (isNull() || a1.isNull()) return 0;
        return (getRow() == a1.getRow() && getCol() == a1.getCol()
		&& getLayer() == a1.getLayer());
        };
            
    int operator<= (const MAddress &a1) const;
    

    /*
        to preserve the correct ordering in the array, layer is the most
        significant item, then row, and column is the least significant item.

        This allows keeping a pointer to a cell and incrementing the pointer
        through the array and catching each cell in a given row.

        1/20/94 dpp
    */

    int operator> (const MAddress &a1) const {
        if (getLayer() < a1.getLayer()) return 0;
        if (getLayer() > a1.getLayer()) return 1;
        if (getRow() < a1.getRow()) return 0;
        if (getRow() > a1.getRow()) return 1;
        return getCol() > a1.getCol();
        };

    int operator>=(const MAddress &a1) const {
        if (a1 == *this) return 1;
        if (getLayer() < a1.getLayer()) return 0;
        if (getLayer() > a1.getLayer()) return 1;
        if (getRow() < a1.getRow()) return 0;
        if (getRow() > a1.getRow()) return 1;
        return getCol() > a1.getCol();
        };

    int operator< (const MAddress &a1) const {
        if (getLayer() < a1.getLayer()) return 1;
        if (getLayer() > a1.getLayer()) return 0;
        if (getRow() < a1.getRow()) return 1;
        if (getRow() > a1.getRow()) return 0;
        return getCol() < a1.getCol();
        };

    int operator!= (const MAddress &a1) const {
        return (getRow() != a1.getRow() || getCol() != a1.getCol() || 
		getLayer() != a1.getLayer());
        };

    // utility and misc methods
    int isNull() const {return theLayer & NULLADDRESS;};
    int inRange(const MAddress *,const MAddress *) const;
    void toStr(char *,int = -1) const;
    void read(MStream *);
    void write(MStream *) const;
    void doMerge(const MAddress *);

    private:
    unsigned short theLayer,theCol;
    int theRow;
    };

extern void sortAddresses(MAddress &,MAddress &);

#endif












