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

//  this class holds printing information for a print job
//    94-09-27 dpp

#ifndef _MH_printHead

#define _MH_printHead

class MStream;
#include "font.h"
#include "range.h"
#include "object.h"

class MPrintHead : public MObject
{
    public:
    MPrintHead();
    virtual void loadStream(MStream *);
    virtual void copyFrom(const MPrintHead *);
    virtual ~MPrintHead();

    virtual void write(MStream *) const;
    
    virtual MPrintHead &operator=(const MPrintHead &);

    virtual void setRange(const MRange *r) {range.set(r);};
    virtual const MRange *getRange() const {return &range;};
    virtual void setLayer(int l) {layer = l;};
    virtual int getLayer() const {return layer;};
    virtual int getMargin(int i) const {return margins[i];};
    virtual void setMargin(int i,int v) {margins[i] = v;};
    virtual const char *getString(int i) const {return strings[i];};
    virtual void setString(int i,const char *);
    virtual int getGrid() const {return grids;};
    virtual void setGrid(int i) {grids = i;};
    virtual int getRCHead() const {return rcHead;};
    virtual void setRCHead(int i) {rcHead = i;};
    virtual float getScale() const {return scale;};
    virtual void setScale(float i) {scale = i;};
    virtual int getOrient() const {return orientation;};
    virtual void setOrient(int i) {orientation = i;};
    virtual int getOrder() const {return order;};
    virtual void setOrder(int i) {order = i;};
    virtual const MFont *getFont(int i) const {return &fonts[i];};
    
    
    private:
    char *name;
    char *strings[8];
    MRange range;
    int layer;
    int grids;
    int rcHead;
    int scaleToFit;
    float scale;
    int order;
    int orientation;
    int margins[4];
    MFont fonts[8];
};


// ifndef _MH_printHead
#endif

