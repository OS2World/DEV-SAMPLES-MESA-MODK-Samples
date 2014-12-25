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
    this header file contains the code for the MRect rectangle object
    2-20-94 dpp

    94-08-30 dpp added support for offseting the X and Y values
    94-08-31 dpp allow a rectangle to archive itself out
    94-09-03 dpp added operator==() and setNull() and isNull()
    94-09-04 dpp added doesIntersect()
    94-09-17 dpp added the MPoint class
*/

#ifndef _MH_mrect

#define _MH_mrect

class MStream; // we have to know what a stream is to archive ourselves

// the MPoint class is very simply a single point in an xy coordinate space
// 94-09-17 dpp
class MPoint
{
    public:
    void init() {x = 0; y = 0;};
    void init(const MPoint *mp) {x = mp -> x; y = mp -> y;};
    void init(int x1,int y1) {x = (float) x1; y = (float) y1;};
    void free() {};
    void write(MStream *) const;
    void init(MStream *);
    void scaleUp(float);
    void scaleDown(float);
	
    void set(float x1,float y1) {x = x1; y = y1;};

    void copyFromPOINTL(const void *);
    void copyToPOINTL(void *) const;

    float getX() const {return x;};
    float getY() const {return y;};
    void setX(float i) {x = i;};
    void setY(float i) {y = i;};
    void offsetX(float i) {x += i;};
    void offsetY(float i) {y += i;};

    // int operator==(const MPoint &mp) const {return (x == mp.x && y == mp.y);};
	// MPoint &operator=(const MPoint &mp) {x = mp.x; y = mp.y; return *this;};
    void translate(float xt,float yt) {x -= xt; y -= yt;};
    void rotate( float );
	
    private:
    float x,y;  // the x and y coordinates
};

class MRect {
    public:
    MRect() {x = y = wid = hi = 0.0;};
    void init() {x = y = wid = hi = 0.0;};
    void init(float tx,float ty,float twid,float thi) {x = tx;
        y = ty; wid = twid; hi = thi;};

    void init(const MRect *re) {*this = *re;};

    // because this class takes up no allocated storage, do nothing on a free
    // 94-08-31 dpp
    void free() {};
	
	void scaleUp(float);
	void scaleDown(float);

    void set(float tx,float ty,float twid,float thi) {x = tx;
        y = ty; wid = twid; hi = thi;};
    void copyFromRECTLNorm(const void *);
    void copyToRECTLNorm(void *) const;

    void copyFromRECTLInc(const void *);
    void copyToRECTLInc(void *) const;

    float getX() const {return x;};
    float getY() const {return y;};
    float getWid() const {return wid;};
    float getHi() const {return hi;};
    void setX(float i) {x = i;};
    void setY(float i) {y = i;};
    void setWid(float i) {wid = i;};
    void setHi(float i) {hi = i;};
    float getCX() const {return x + wid;};
    float getCY() const {return y + hi;};
    void setCX(float tx) {wid = tx - x;};
    void setCY(float ty) {hi = ty - y;};

    // offset the values
    void offset(float v1, float v2) { x+=v1 ; y += v2;};
    void offsetX(float v) {x += v;};
    void offsetY(float v) {y += v;};
    void offsetWid(float v) {wid += v;};
    void offsetHi(float v) {hi += v;};

    MRect *insetRect(float,float);
    MRect *inset(float x,float y) {return insetRect(x,y);};
    int intersectRect(const MRect *);
    int pointIn(const void *) const;
    int pointIn(const MPoint *) const;
    int inSide(const MRect *) const;
    int clipRect( const MRect * );
	int sloppyClipRect( const MRect * );	// FIXME

    void unionRect( const MRect *);
    void clipTo(const MRect *);	


    // Write or initialize yourself from a stream
    // 94-08-31 dpp
    void write(MStream *) const;
    void init(MStream *);

    // compare two rectangles.  Return 1 if they are the same
    // 94-09-03 dpp
    int operator==(const MRect &) const;

    // this method makes a rectangle NULL
    // 94-09-03 dpp
    void setNull() {x = y = wid = hi = -1.0;};

    // returns 1 if the rectangle is NULL
    // 94-09-03 dpp
    int isNull() const {if (x == -1 && y == -1 && wid == -1 && hi == -1) return 1; return 0;};

    // returns 1 if the two rectangles intersect
    // 94-09-04 dpp
    int doesIntersect(const MRect *) const;

    void sizeByCorner(int corner,float dx,float dy);
	
	// round the rectangle to integer coordinates
	// 95-04-18 dpp
	void round();

    private:
    float x,y,wid,hi;
};

const int MUpperLeftCorner = 1;
const int MUpperRightCorner = 2;
const int MUpperMidCorner = 3;
const int MLowerLeftCorner = 4;
const int MLowerRightCorner = 5;
const int MLowerMidCorner = 6;
const int MMidLeftCorner = 7;
const int MMidRightCorner = 8;



#endif
