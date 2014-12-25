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
    This class wraps the internal MModel class in a SOM wrapper.
    This is so that a newer version of the DLL's can be placed "under"
    an existing client application.  We would do MModel as a SOM class,
    exception for the nasty overhead problems with SOM.

    6-25-94

    added support for changing fonts in an atomic operations 8/20/94 dpp
    94-08-24 - dpp - support for column and row sizing
    94-08-28 - dpp - included "rect.h"
    94-08-31 dpp added the createGraph() method
    94-09-03 dpp added isFrameAt()
    94-09-11 dpp changed this module to support MSelection's
    94-09-17 dpp added frameAtPoint()
    94-09-18 dpp added colorDroppedOnFrameAt(), fontDroppedOnFrameAt(), and
        bkgColorDroppedOnFrameAt()
*/

#ifndef _MH_MesaModel

#define _MH_MesaModel

#include "address.h"
#include "action.h"

#include "os2h.h"

#include "color.h"
#include "object.h"

// if we're not in the "dll" we only need pointers to certain classes
#ifdef IN_DLL
#include "model.h"
#else
class MModel;
class MRect;
class MPoint;
class MEditString;
#endif

class MFormat;
class MRange;
class MInterest;
class MClipStream;
class MException;
class MGController;
class MFont;
class MSelection;
class MImage;
class MPrintHead;
class MDraw;
class MFrameXfer;
class MFrame;
class MPosition;
class MPassword;
#if defined(M2Z) //  || defined(M2NT)
class MDDEClientItem;
#endif
class MPrintInfo;

#ifndef RULERWID
// HARDWIRE - size of the rulers in a basic spreadsheet screen
#define RULERWID 36
#define RULERHI 18

// ifndef RULERWID
#endif


class MMesaModel : public MObject
{
    public:

    MMesaModel();
    virtual ~MMesaModel();

    virtual void drawInto(MDraw *,const MRect *page,const MRect *area,
	 		const MAddress *left, const MSelection *sel,int flags,
			const MSelection *key = 0, float colhi = RULERHI,
			float rowwid = RULERWID, int numTitle = -1,
			const char **titles = NULL,const MAddress *inCell = NULL,
			MEditString *es = NULL );

    void drawInCell(MDraw *md, const MAddress * left,int flags, float RulerHi, float RulerWid,
            const MAddress * inCell, MEditString *es);


    int clipGraphsFromMDraw(MDraw *md, const MRect *rct, const MAddress *left,
              int flags);
    void drawGraphsIntoMDraw(MDraw *md, const MRect *rct, const MAddress *left,
               const MSelection *theSel, int flags);


    virtual void rangeToStr(const MRange *ra,const MAddress *ad,char *&tmp,int &max);

    virtual void setCellToString(const MAddress *a1,const char *s,int action,
        MException *me,const MSelection *);

    virtual void setCellToStringOrNumber(const MAddress *a1,const char *s,int action,
        MException *me,const MSelection *);

    virtual int whichVisibleCol(int layer,int c);
    virtual int whichVisibleRow(int layer,int r);
    virtual int getNthVisibleCol(int layer,int n);
    virtual int getNthVisibleRow(int layer,int n);
    virtual int getLastVisibleCol(int layer);
    virtual int getLastVisibleRow(int layer);
    virtual void getNumVisible(int layer,int &nRows,int &nCols);

    virtual void getExtents(int layer,int &mr,int &mc);

    virtual void setExtents(int layer,int mr,int mc,int action,
        const MSelection *,MException *me);

    virtual void adToStr(const MAddress *ad,char *s,int layer);

    virtual int isAddress(const char *,const MAddress *,MAddress *,int &len);
	virtual int doesCellExist( const MAddress * );
	virtual int isCellNonBlank( const MAddress * );
	
    virtual void getRectForAd(const MAddress *left,const MAddress *ad,MRect *re);

    virtual void getRectForRangeAd(const MAddress *left,const MAddress *ul,const MAddress *lr,
        MRect *re);

    virtual void getRectForRange(const MAddress *left,const MRange *ra,MRect *re);
    virtual int getRectForFrame(const MAddress *left,const char *,MRect *re);

    virtual void setRangeToFormat(const MRange *ra,const MFormat *fo,
        int action,const MSelection *,MException *me);

    virtual void setRangeToFont(const MRange *ra,const MFont *fo,
        int action,const MSelection *,MException *me);

    virtual void moveCells(const MRange *rtm,const MAddress * offset,int action,
        MException *me,const MSelection *);
    virtual void copyCells(const MRange *rtm,const MAddress * offset,int action,
        MException *me,const MSelection *);

    virtual void autoRange(const MRange *ra,int type,const MSelection *,int action,MException *me);

    virtual void convertRange(const MRange *ra,int type,const MSelection *,
        int action,MException *me);

    virtual void clearSpecialRange(const MRange *ra,int type,const MSelection *,
        int action,MException *me);

    virtual void clearRange(const MRange *rp,const MSelection *,
        int action,MException *me);

    virtual void clear(const MSelection *rp,const MSelection *,
        int action,MException *me);

    virtual void fillSmartWithCell(const MAddress * cad,const MRange *cra,int action,
        const MSelection *,MException *me);

    virtual void fillWithCell(const MAddress * cad,const MRange *cra,int action,
        const MSelection *,MException *me);

    virtual void fillSmartRight(const MRange *cra,int action,
        const MSelection *,MException *me);

    virtual void fillSmartDown(const MRange *cra,int action,
        const MSelection *,MException *me);

    virtual void fillRight(const MRange *cra,int action,const MSelection *,
        MException *me);

    virtual void fillDown(const MRange *cra,int action,
        const MSelection *,MException *me);

    // set the size of all the rows or columns in the input range to the
    // size in the second parameter 94-08-24 dpp
    // if the size == -1, reset the size
    // if size == -2, hide the row or column
    // if size == -3, unhide the row or column
    // if size == -4, set the page break
    // if size == -5, clear the page break

    virtual void setColumnSize(const MRange *,int,const MSelection *,int,MException *);
    virtual void setRowSize(const MRange *,int,const MSelection *,int,MException *);
	
	virtual int getColumnSize(int layer,int column);
	virtual int getRowSize(int layer,int row);

    virtual int isRowHidden(int layer,int row);
    virtual int isColHidden(int layer,int col);


    virtual MAddress addressFromPoint(const MAddress * left,const MPoint *po,int clip = 1);

    virtual void setUp(MGController *gc);

    virtual void cleanUp(MGController *gc);

    virtual void setPathName(const char *s,int action);

    virtual void loadFromPath(int action,MException *me);
	virtual void loadFromStream(MStream *ms,int action,MException *me);

    virtual char *getPathName();

    virtual int getHasPath();

    virtual void setHasPath(int i);

    virtual void unregisterInterest(MInterest *mi);

    virtual void registerInterest(MInterest *mi);

    virtual void saveToPath(MException *me);
	
	virtual void saveToStream(MStream *ms,MException *me);

    virtual int getHasChanged();

    virtual int getInterestCount();

    virtual int isMultiRange(const char *s,const MAddress * a1,MRange *ra,int &len);

    virtual int getUndoCnt();

    virtual int getRedoCnt();

    virtual void recalc(const MAddress *,int action);
    virtual void recalcRange(const MAddress *,const MRange *,int action);
	virtual void redisplay();

    virtual int undoLastCommand(const MSelection *,
        int action,MSelection *);

    virtual int redoLastCommand(const MSelection *,
        int action,MSelection *);

    virtual void copy(const MSelection *,int type,MClipStream *mcs);

    virtual void cut(const MSelection *,int type,MClipStream *mcs,
        const MSelection *,int action,MException *me);

    virtual void paste(const MSelection *,int type,MClipStream *mcs,
        const MSelection *,int action,MException *me);

    virtual char *getCellString(const MAddress * ad);
    virtual char *getCellValue(const MAddress * ad);
    virtual char **getLayerNames(int &);
    virtual int getNumLayers();
    virtual char *getLayerName(int);
    virtual void newLayer(int,MException *,const MSelection *);
    virtual void deleteLayer(int layer,int action,MException *,const MSelection *);
    virtual void setLayerName(int lay,const char *newName,int action,const MSelection *);

    virtual void doGridBorder(const MSelection *,int type,int action,
        const MSelection *,MException *);

    virtual int getHasFeed();

    virtual void setHasChanged(int i);

    virtual int getRulerWid();
    virtual int getRulerHi();

    virtual char *getScript(const char *);
    virtual int hasCloseScripts();
    virtual void executeCloseScripts();
    virtual void executeOpenScripts();
    virtual int getScriptInfo(const char *);
    virtual void setScriptInfo(const char *,int,int action,const MSelection *);

    // get the text of a script for a given layer number
    virtual char *getScriptNum(int);
    virtual void setScript(const char *name,const char *script,int info,int action,
        const MSelection *);
    virtual void deleteScript(const char *,int action,const MSelection *);
    virtual char **getScriptNames(int &);
    virtual char *getNextScriptName();
    virtual int getNumScripts();
    virtual char *getScriptName(int);
    virtual void setScriptName(int,const char *,int action,const MSelection *);

    virtual char **getCurSymbols();
    virtual void setCurSymbols(char **,int action,const MSelection *);

    // get the number of the font from the model
    // add the font if it's not already in the list
    virtual int getFontNum(const MFont *);

    // create a graph and return the name of the graph (which must be free'd)
    // the rect is the offset from the "anchor" cell.
    // The type is the graph type (see MFrame for a list)
    // data is the range where the graph draws its data, action is the action to take
    // and MAddress and MRange are the current selection
    // 94-08-31 dpp
    virtual char *createGraph(MRect *,const MAddress *anchor,int type,
        const MRange *data,int action,const MSelection *);

    virtual MFrameXfer *getFrameInfo(const char *);
    virtual void setFrameInfo(const char *,const MFrameXfer *,int action,const MSelection *);
    virtual void setFrameToType(const char *,int type,int action,const MSelection *);
    virtual int getCornerForFrame(const char *,const MAddress *,const MPoint *);
    virtual void setFrameOrder(const char *frame,int order,int action,const MSelection *);
    virtual char **getFrameNames(int &);


    // add an image in a frame
    // 94-09-22 dpp
    virtual char *addImage(const MPoint *,const MAddress *anchor,MImage *,
        int action,const MSelection *);

    virtual char *addFrame(const MPoint *,const MAddress *anchor,MFrame *,
        int action,const MSelection *);

    virtual void newShape(int type,const MAddress *offset,const MRect *re,
        int lWid,int arrow,int action,const MSelection *sel);

    // check to see if there is a graph in a certain rectangle (offset from cell A1)
    // on a given layer.  This routine is used to check to see if it's okay to put a
    // graph at a given rectangle
    // 94-09-03 dpp
    virtual int isFrameAt(int layer,const MRect *);

    // tries to find a graph at the given point.  If one is found, set the graph name
    // in the char ** (this must be MFree'd) and return 1.  If 0 is returned, no matching
    // graph was found and no freeing is necessary
    // 94-09-17 dpp
    virtual int frameAtPoint(const MAddress *,const MPoint *,char **);

    // drop stuff on a frame
    // 94-09-18 dpp
    virtual void colorDroppedOnFrameAt(MColor,const char *,const MAddress *,
        const MPoint *,const MSelection *,int);
    virtual void bkgColorDroppedOnFrameAt(MColor,const char *,const MAddress *,
        const MPoint *,const MSelection *,int);
    virtual void fontDroppedOnFrameAt(const MFont *,const char *,const MAddress *,
        const MPoint *,const MSelection *,int);

    virtual char *getLabel(int,MRange *);
    virtual int numberOfLabels();
    virtual char **getLabelNames(int &);
    virtual void setLabel(const char *,const MRange *,int action,const MSelection *);
    virtual void deleteLabel(const char *,int action,const MSelection *);
    virtual int findLabel(const char *,MRange *);

    virtual void setLayerColor(int layer,MColor,int type,int action,const MSelection *,
        MException *me);

    virtual void setUndoMax(int);
    virtual int getUndoMax();

    virtual int getLayerProtection(int);
    virtual void setLayerProtection(int,int,int action,const MSelection *);

    virtual int getLayerGrid(int);
    virtual void setLayerGrid(int,int,int action,const MSelection *);

    virtual void getDefaultCellSize(int,int &,int &);
    virtual void setDefaultCellSize(int layer,int wid,int hi,int action,const MSelection *);

    virtual int getAutoRecalc();
    virtual void setAutoRecalc(int,int action,const MSelection *);
    virtual int getRecalcType();
    virtual void setRecalcType(int,int action,const MSelection *);
    virtual int getRecalcIterations();
    virtual void setRecalcIterations(int,int action,const MSelection *);

    virtual int getFormatAndFontForCell(const MAddress *,MFormat *,MFont *);

    virtual void print(MDraw *,const MRect *,const MPrintHead *,int start,int end,MException *);

    virtual void print_nonThreaded(MDraw *,const MRect *,const MPrintHead *,
        int start,int end,MException *);

    virtual void getDefaultPrintHead(MPrintHead *);

    virtual void setDefaultPrintHead(const MPrintHead *,int action,const MSelection *);

    virtual void setFontAttribute(int attrib,const MRange *,int action,const MSelection *,
        MException *);
    virtual void setFont(const char *,int size,const MRange *,int action,const MSelection *,
        MException *);

        // changes the row/column header fonts
        virtual void setFontForLayer( int layer, const MFont *, int action, const MSelection *,
                MException * );

	virtual void importText(MStream *,const MAddress *,int,const MSelection *,MException *);
	virtual void importDelimitedText(MStream *ms,const MAddress *ad,int action,const MSelection *sel,MException *me,int);

	virtual void setPosition(const MPosition *);
	virtual MPosition *getPosition();

	virtual MAddress find(const char *string,int flags,int order,const MRange *range,
	    const MAddress *start);
	virtual void replace( const char *find, const char *repl, int flags, int, const MAddress *, MException *, const MSelection * );
	virtual void replaceAll( const char *find, const char *repl, int flags, int, const MRange *, MException *, const MSelection * );

	virtual void sort(const MRange *ra,int hasTitles,int byCol,int numKey,int *keys,int *order,
	    int action,const MSelection *sel,MException *);

	virtual int getFileType();
	virtual void setFileType( int );
	
	virtual MPassword *getPassword();

#if defined(M2Z) // || defined(M2NT)
	virtual int getNumDDEItems();
	virtual MDDEClientItem *getDDEItem( int i );
	
	virtual void addDDEItem( const char *, const char *, const char *, const char *, const char *, int action, const MSelection *, MException * );
	virtual void deleteDDEItem( int, int action, const MSelection *, MException * );
	
	virtual MDDEClientItem *getNewDDEClientItem();
// #if defined(M2Z) || defined(M2NT)
#endif
	virtual void getScale( float *scArray );
	virtual void setScale( float *scArray );

	virtual void duplicateFrame( const char *, const MPoint *, const char *, int,
		const MSelection * );

	virtual int frameHasText( const char *frame );
	virtual char *getFrameText( const char *frame );
	virtual void setFrameText( const char *frame, char *text, int action, const MSelection *sel );

	virtual void setBlobValue(const char *name,int len,const void *blob);
	virtual int getBlobValue(const char *name,int &len, void *&blob);
	
	virtual int setCellToAddInValue(void *,int action);
	virtual void getCellValueToAddInValue(void *);
	
	virtual int shouldAutoGrow(const MAddress *,const MRange *);
	virtual void autoGrow(const MAddress *,const MRange *,int action,const MSelection *,
		MException *);
	virtual MPrintInfo *createPrintInfo(const MRect *ire,const MPrintHead *ph);
	virtual void doPage(MDraw *,const MRect *,const MAddress *,const MAddress *,const MPrintHead *,
		int thisPage,int totPage,double time, int precise=1);

	virtual void findPriorCellInRow( int, const MAddress *, MAddress * );
	virtual void findNextCellInRow( int, const MAddress *, MAddress * );
	virtual void findPriorCellInCol( int, const MAddress *, MAddress * );
	virtual void findNextCellInCol( int, const MAddress *, MAddress * );
	virtual void findLowerRightCell( MAddress * );

	virtual void smartSizeRows( const MRange *, int, const MSelection *, MException * );
	virtual void smartSizeColumns( const MRange *, int, const MSelection *, MException * );

    private:
    MModel *theModel;
};

// flags for drawing the worksheet
const int hideRowsDrawFlag = 1;
const int hideColsDrawFlag = 2;
const int noCurCellDrawFlag = 4;
const int noSelRangeDrawFlag = 8;
const int noGraphsDrawFlag = 16;
const int printingDrawFlag = 32;
const int preciseDrawFlag = 64;
const int showGridDrawFlag = 128;
const int dontLockDrawFlag = 256;
const int onlyFramesDrawFlag = 512;
const int drawPreciseGraphs = 1024;
const int drawOnlyNonSolidGraphs = 2048;
const int dontClipGraphsFlag     = 4096;

// variables for layer color settings
const int bkgColorLayer = 0;
const int rulerColorLayer = 1;
const int gridColorLayer = 2;
const int tabColorLayer = 3;


// used to store the maximum row height/column width values...
#define MAXROWSIZE	400
#define MAXCOLSIZE	600

// ifndef _MH_MesaModel
#endif
