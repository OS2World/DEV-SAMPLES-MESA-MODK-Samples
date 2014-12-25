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

// 94-09-05 dpp
// Each element in a graph has certain attributes, i.e., color, font, etc.
// this class keeps track of these items.  There is an instance of this
// class for each element in a graph

// make sure we're only included once
#ifndef _MH_graphElement

#define _MH_graphElement

#include "color.h"
#include "font.h"

class MModel;
class MStream;

class MGraphElement
{
    public:
    // put in default values
    void init();
    
    // put in default values for the n-th element in a graph
    void init(int);
    
    void init(const MGraphElement *);
    
    // read from a stream
    void init(MStream *);
    
    // free me
    void free() {theColor.free(); borderColor.free(); font.free();};
    
    // write to a stream
    void write(MStream *) const;
    
    // get the information about the graph element
    MColor getColor() const {return theColor;};
    MColor getBorderColor() const {return borderColor;};
    const MFont *getFont() const {return &font;};
    void setFontSize(int s) {font.setSize(s);};
    int getBorderSize() const {return borderSize;};
    
    // set information
    void setColor(MColor c) {theColor = c;};
    void setColor(int c) {theColor.set(c);};
    void setBorderColor(MColor c) {borderColor = c;};
    void setFont(const MFont *fp) {font = *fp;};
    void setBorderSize(int bs) {borderSize = bs;};
    
//    MGraphElement &operator=(const MGraphElement &ge) {free(); init(&ge); return *this;};
    
    private:
    MColor theColor,borderColor;    // the color of the element and of the border
    MFont font;                        // the font that info will be displayed in
    int attributes;                    // what kind of info to display
    int pulled;                        // how far is a pie piece pulled out
    int borderSize;                    // how big is the border
    
    void operator=(const MGraphElement &);
};

// ifndef _MH_graphElement
#endif
