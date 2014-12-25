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

// 94-09-11 dpp
// this class handles the "current selection" of the worksheet.  This allows
// the expansion of ranges and cells to graphics to anything else
// 94-09-17 dpp added isFrameSelected()

#ifndef _MH_selection

#define _MH_selection

class MStream;
class MMesaModel;
class MFont;
class MFormat;

#include "address.h"
#include "range.h"

// masks for some layer types

const int ASHEETLAYER = 0;
const int ASCRIPTLAYER = 0x10000;
const int ADISPLAYLAYER = 0x20000;
const int AQUERYLAYER = 0x40000;
const int ALAYERMASK = 0xffff;

class MSelection
{

    public:	
	
    void init();                                // initialize
    void init(MStream *);						// initialize from a stream
    void init(const MSelection *,int = 1);		// initialize from a copy
	void initToA1() {init();};					// initialize to cell [A]A1
    void free();                                // release storage
    void zap() {free(); init(); ad.zap();};		// reset to a known state
    void zapToLayer();							// reset to a known state on the current layer
    void zapRange() {range.zap();};				// zap the range
    void write(MStream *) const;                // archive

    MSelection &operator=(const MSelection &);
    MSelection &operator=(const MSelection *);
    MSelection &operator=(const MAddress &);
    MSelection &operator=(const MRange &);

    // setting the selection
    void setAddressAndRange(const MAddress *,const MRange *);


    // setting the layer
    void setLayer(int, MMesaModel *);

    // sets the default range for the given layer number
    void setDefaultForLayer(int,const MSelection *);
    void setDefaultForLayer(int,const MAddress *,const MRange *);

    // prime a series of selections for the correct stuff
    void prime(int layer,const MAddress *);
    void prime(int layer,const MAddress *,const MRange *);
    void prime(int layer,const MSelection *);


    // deal if we are selecting a script layer
    int isAScript() const;		// dpr - this doesn't exist?
    // const char *getScriptLayerName() const;

    // deal if we are selecting something on a spreadsheet layer
    int isASpreadsheet() const;
    const MAddress *getAdPtr() const {return &ad;};
    const MRange *getRangePtr() const {return &range;};
	
    const MAddress *getUpperLeftPtr() const {return &upperLeft;};
	MRange *getUnconstRangePtr() {return &range;};
    int getUpperLeftRow() const {return upperLeft.getRow();};
    int getUpperLeftColumn() const {return upperLeft.getCol();};
    int getUpperLeftLayer() const {return upperLeft.getLayer();};
    int getLayer() const {return layer;};
    void setUpperLeft(const MAddress *ap) {upperLeft = *ap;};
    void setUpperLeftRow(int i) {upperLeft.setRow(i);};
    void setUpperLeftColumn(int i) {upperLeft.setCol(i);};
    void setFrameSelection(const char *);

    // get the nth item in the range
    void getItem(int n,MAddress &a1,MAddress &a2) const {range.getItem(n,a1,a2);};

    // is a cell in the range?
    int inRange(const MAddress *ad) const {return range.inRange(ad);};

    // and what range is it in?
    int inWhichRange(const MAddress *ad,
        MAddress &a1,MAddress &a2) const {return range.inWhichRange(ad,a1,a2);};

    // some more range mechanics
    int isRowInRange(int i1,int i2) const {return range.isRowInRange(i1,i2);};
    int isColInRange(int i1,int i2) const {return range.isColInRange(i1,i2);};

    // how many elements in the range?
    int getRangeCount() const {return range.getCount();};

    // some things that a selection can do
    // return the contents of the current selection
    // and remember to free the returned string
    char *getSelectionContents(MMesaModel *) const;
    char *getSelectionName(MMesaModel *) const;
    void getSelectionFont(MMesaModel *,MFont *) const;
    void getSelectionFormat(MMesaModel *,MFormat *) const;
    const char *getFrameName(int n) const
        {if (graphs && n < numGraphs) return graphs[n]; return 0;};

	 // return a string representation of the range, if one is selected, or
	 // the address if not
	 char *getSelectionRange( MMesaModel *, int &);

//	 void setSelectionContents( MMesaModel *, char * );
    // set the address, but don't disturb the range
    void setAdButNotRange(const MAddress *);

    // set a range and sort the range items
    void setAndSort(const MAddress *,const MAddress *);
	 void setAndSortItem( int item, const MAddress *, const MAddress * );
    void set(const MAddress *);

    // does the selection have any contents?
    int hasSelection() const;

    // is the selection zapped?
    int isZapped() const;

    // set the selection type
    void makeARange();     // force the selection to be an address or a range
    void makeNoGraph();    // make sure that no graphs are selected
    void makeGraphs();     // force the selection to be graphs plus the underlying range selection
    void makeScript();     // make the current selection a script

    // get the selection type
    int isScriptLayer() const; // is the layer a script
    int isSheetLayer() const; // is a worksheet layer selected?

    // is the difference between the two selections only the range
    // or is there more
    int deltaOnlyRange(const MSelection *) const;

    // get the name of the script if it's a script layer, otherwise, return a blank string
    // 94-09-14 dpp
    const char *getLayerName(MMesaModel *);

    // can we edit the contents of the current selection (i.e., does it have a
    // text representation?
    int canEditContents(MMesaModel *) const;

    // returns a pointer to a layer if that layer exists so that we
    // can retrieve the former position on a layer
    const MSelection *findSelection(int) const;

    // is a named frame one of the selected items?
    int isFrameSelected(const char *) const;
    int isFrameSelected() const;


    // from the layer number, figure out the type of selections it is
    static int testForSheetLayer(int i)
        {if ((i & ~ALAYERMASK) == 0) return 1; return 0;};
    static int testForScriptLayer(int i)
        {if ((i & ASCRIPTLAYER) == ASCRIPTLAYER) return 1; return 0;};

    // put the current cell or range into the given range
    // 94-09-24 dpp
    void fillRange(MRange *) const;
	// returns 0 if the two selections are identical in content, 1 otherwise
	int areDifferent( const MSelection * ) const;
	int getNumGraphs() const { return numGraphs; };
	
    private:
    // int type;                // the type of selection
    int layer;                // the number of the currently displaying layer
    MAddress ad;            // the current address
    MAddress upperLeft;        // the upperleft of the display area
    MRange range;            // the current range
    int numGraphs;            // the number of graphs
    char **graphs;            // a list of the graphs
    char *scriptName;        // the name of the current script
    int numSelections;        // get the number of selections that we have chained
    MSelection *selections;    // selections for each layer
	

    // copy the selections except don't mess with the other selections
    void copyExceptOtherSelections(const MSelection *);
};


// ifndef _MH_selection
#endif
