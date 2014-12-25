/**************************************************************************
 *                                                                        *
 *                                                                        *
 *          This code is copyright (c)              1994                  *
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

#ifndef _mh_TAG_RANGE__

#define _mh_TAG_RANGE__

#include "address.h"

// 94-08-23 dpp added methods to check whether a row or column on a give layer intersects the range
// 94-09-19 dpp added methods to copy a set of ranges

class MSheet;
class MStream;

const int COUNTMASK = 0xffff;        // the max number od discontiguous ranges
const int AUTOGROWBIT = 0x10000;    // the bit that determines if we're autogrow


class MRange {

    public:
    void init() { r2.ads = 0 ; count = 0;};
    void init(const MRange *mr) {init(); if (mr) *this = *mr;};
    void zap() {if ((count & COUNTMASK) > 1) _free(); init();};
    void free() {if ((count & COUNTMASK) > 1) _free(); count = 0;};
    int getCount() const {return count & COUNTMASK;};
	
    void init(const MAddress *,const MAddress *);
    void init(const MAddress *);
    void init(MStream *);
    void write(MStream *) const;
    void addRange(const MAddress *,const MAddress *);
    void addAndSortRange(const MAddress *,const MAddress *);
    void addRange(const MAddress *);
    void addRange(const MRange *);
    void sortRange();

    int inRange(const MAddress *) const;
    int inRange(const MRange *) const;

    // do the two ranges overlap or intersect?
    // 94-09-16 dpp
    int overlapRange(const MRange *) const;

    int inWhichRange(const MAddress *,MAddress &,MAddress &) const;
    void set(const MAddress *);
    void set(const MRange *ra) {free(); init(ra);};
    void set(const MAddress *,const MAddress *);
    void getItem(int,MAddress &,MAddress &) const;
    void setItem(int,const MAddress *,const MAddress *);
    void doMerge(const MAddress *);
    // void offset(int,int,int);
    MRange &operator=(const MRange &);
    int operator==(const MRange &) const;
    int getTotalCells() const;
    void setAndSort(const MAddress *,const MAddress *);
    void offset(int,int,int);
    void offsetBy(const MAddress *);
    void makeAbs();
	 void setAbs( int );
	 int getAbs();

    int isRowInRange(int,int) const;
        // pass a row and a layer, returns 1 if that row intersects the rng
    int isColInRange(int,int) const;
        // pass a col and a layer, returns 1 if that col intersects the rng

    // copy a set of range pairs from the source to *this
    // 94-09-19 dpp
    void copySelectedRanges(const MRange *,int,int);

    // get and set the autogrow bit
    int isAutoGrow() const {return (count & AUTOGROWBIT) ? 1 : 0;};
	int isAtLowerEdge(const MAddress *) const;
	int growFrom(const MAddress *);
    void setAutoGrow(int i) {if (i) count |= AUTOGROWBIT; else count &= ~AUTOGROWBIT;};
    void setCount(int i) {count = (count & ~COUNTMASK) | i;};


    private:

    void _free();

    int count;
    union {
        MAddress ul;
        int max;
        } r1;
    union {
        MAddress lr;
        MAddress *ads;
        } r2;
    };

#endif

