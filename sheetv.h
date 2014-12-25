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


// 94-08-23 dpp added support for UI of row and column resizing
// 94-09-10 dpp added support for punting doing a drag operation
// 94-09-11 dpp unified the selection in this class
// 94-09-14 dpp added getLayerName(), isSheetSelected(), isScriptSelected()

#ifndef _MH_sheet_View

#define _MH_sheet_View

#include "view.h"
#include "mesaview.h"
#include "select.h"
#include "rect.h"

class MMesaModel;
class MDrawImage;
class MEditString;

class MSheetView : public MView
{
    public:
    MSheetView(MView *,MMesaModel *,MMesaView *);
    virtual ~MSheetView();
    virtual int drawSelf(MDraw *,const MRect *);
    void displayFrame(const char *);
    virtual int hasDrawSelf() {return 1;};

    virtual const MAddress * getCurAdPtr();
    virtual void setCurAd(const MAddress *, int = 1);
    virtual void setAddressAndRange(const MAddress *,const MRange *,int = 1);
    // virtual void setAddressAndRange(const MAddress *,const MSelection *);
    virtual void setUp(const MRect *,int = 0);
    virtual int contextMenu( const MPoint *, int &);

    // display parts of the sheet
    virtual void displayAddress(const MAddress *);
    virtual void displayRange(const MRange *);
    virtual void displaySelectionDiff(const MSelection *,const MSelection *);
    virtual void displayRangeDiff(const MRange *,const MRange *);

    virtual void XORBaseCell(const MAddress *, int flags =0,MDraw *mdr = NULL, MRect * area =NULL);
    virtual void XORAddress(const MAddress *, int flags =0,MDraw *mdr = NULL, MRect * area =NULL);
    virtual void XORRange(const MRange *, int flags=0, MDraw *mdr = NULL, MRect * area =NULL);
    virtual void XORRangeDiff(const MRange *, const MRange *, int flags=0, MDraw *mdr = NULL, MRect * area =NULL);
    virtual void XORSelectionDiff(const MSelection *,const MSelection *, int flags=0, MDraw *mdr=NULL, MRect * area =NULL);

    virtual const MRange *getCurRngPtr();
    virtual MMesaView *getMesaView() {return theDisplay;};
    virtual void mouse1DblClick(const MPoint *,int,int &);
    virtual void transformPoint(MPoint *,MRect * = NULL);
    virtual void transformFromSheetToView(MRect *,MRect * = NULL);
    virtual void transformFromViewToSheet(MRect *,MRect * = NULL);
    virtual void mouse1Down(const MPoint *,int,int &);
    virtual void mouse1Up(const MPoint *,int,int &);
	virtual int mouseMove( const MPoint *, int, int & );
    virtual int comboButton( int & );
	
    virtual void mouse2Down(const MPoint *,int,int &);
    virtual void mouse2Up(const MPoint *,int,int &);
    virtual void mouse2MotionStart(int &);
    virtual void mouse2MotionEnd(int &);
    virtual int handleMouse2Motion( const MPoint *, int, int & );
    virtual int setCursor( const MPoint *, int, int &);
	virtual int changedSize(MChange *);

    virtual void bkgColorDroppedAt(MColor,int,int);
    virtual void colorDroppedAt(MColor,int,int);
    virtual void fontDroppedAt(const MFont *,int,int);
    virtual int bufferWindow() {return 1;};

    // set the selected range to NULL
    virtual void setToNullSelectedRange();
    virtual int isEditingFormula();
    virtual int isEditing();

    // support for the unified selection
    // get the contents of the current selection
    virtual char *getSelectionContents();

    // get the name of the current selection
    virtual char *getSelectionName();

    // get the name of the current selection (including range)
    virtual char *getSelectionRange();

    // get the font for the current selection
    virtual void getSelectionFont(MFont *);

    // get the format for the current selection
    virtual void getSelectionFormat(MFormat *);

    // set the current range
    virtual void setCurRange(const MRange *);

    // set the current selection
    virtual void select(const MSelection *);
    virtual void setSelection(const MSelection *);

    virtual void selectAll(int record=0);

    // select a named frame
    virtual void selectChar(const char *);
    virtual void deselectFrames();

    // get the current selection
    virtual const MSelection *getCurSelection();

    // move us to the correct place on the worksheet
    virtual int scrollToVisible(const MAddress *,int = 0);

    // set the layer
    virtual void setLayer(int);

    // get the layer
    virtual int getCurLayer();

    // get and set info about the upperLeft cell
    virtual const MAddress *getUpperLeft();
    virtual int getUpperLeftColumn();
    virtual int getUpperLeftRow();
    virtual void setUpperLeftRow(int);
    virtual void setUpperLeftColumn(int);

    // is a worksheet selected?
    // 94-09-14 dpp
    virtual int isSheetSelected();

    // is a script selected 94-09-14 dpp
    virtual int isScriptSelected();

    // scroll a certain number of cells 94-09-14 dpp
    virtual void scrollFrom(int,int);

    // get the name of the current layer 94-09-14 dpp
    virtual const char *getLayerName();

    // get the number of the current layer 94-09-15 dpp
    virtual int getLayerNumber();

    // can we edit the contents of the current selection? 94-09-15 dpp
    virtual int canEditContents();


#if defined(M2Z) || defined(M2NT)
    // drag & drop support
    // 94-09-21 dpp
    virtual MRESULT winDragOver(HWND,ULONG,MPARAM,MPARAM,int &);
    virtual MRESULT winDragDrop(HWND,ULONG,MPARAM,MPARAM,int &);
#endif
	
    // create a shape
    virtual void newShape(int type,const char *offset,int offx,int offy,
        int wid,int hi,int lWid,int arrows);
		
	virtual float getViewScale() {return scale;};
	virtual void setViewScale( float s ) { scale = s; };
	virtual float getDrawScale() {return scale == 1.0 ? 1 : 32;};
	
	virtual int handleChar( unsigned int, unsigned int, int & );
	virtual void extendSelection( MAddress *tmp );
	
	virtual void setColumnTitles(const char **title,int numTitle);
	virtual void setColumnTitleHeight(int);
	virtual void setRowTitleWidth(int);
	
	virtual void updateInCell();
	virtual int winPing(int,int );
	virtual void insertTextAndSelectArgs( const char * );
	virtual void insertOperator( const char * );
	virtual MEditString *getEditString() { return editStr; };
	virtual void invokeEdit( int = 0 );
	virtual void terminateEditing();
	virtual MEditString *makeEditStr();
	virtual void copyFromEditView( MClipStream * );
	virtual void cutFromEditView( MClipStream * );
	virtual void pasteIntoEditView( MClipStream * );
	
	
    private:
    MEditString *editStr;		// holds the currently editable string
    MMesaModel *model;
    float scale;
    MMesaView *theDisplay;
    MSelection selection;		// current selection
    MSelection showSel;			// selection (used during selecting a cell/range
	 									// as part of a formula edit)
	MSelection keySel;			// stores the key-cell/range during formula-edit
											
    MAddress tmpAd;
    int isSelectingCells;				// are we selecting cells w/in the sheet
    char *frameSelected;
    MPoint downPoint;    // the place where the mouse was clicked down
    MPoint lastPoint;    // the last point where the mouse moved
    MAddress downUL;    // the upperLeft when the mouse was clicked down
    int downFlags;        // the KBD flags when the mouse was clicked down
    MAddress anchor;
    int resizeCorner;
    MRect resizeRect;

    int b1SelType;

    int mouseN;			// number of the mouse button currently depressed...
    int puntDrag;
    MDrawImage *drawCache;
    MDrawImage *oldBits;
    MRect drawCacheRect,bitsRect;
    MRange rangeToMove;

    // these variables are used for row and column resizing
    int sizePlace,startPlace; // the x or y location of the mouse during a resizing operation
    MAddress adOfRowOrCol; // address of the row or column that is being resized

	char **titles;
	int numTitles;
	float colHi,rowWid;
	
    HWND menus[10];
	
	 int endPressed;
	 int	settingRef;		// 0 if not currently setting a cell/range reference
	 int lastStart, lastLen;	// location within EditView of the last-inserted
	 							// cell/range reference
								
	int isSelectingText;		// are we using mouse to edit incell entry?
	
	 void selectOrSizeRow( MPoint );
	 void selectOrSizeCol( MPoint );
	 void doSizeFrame( void );
	 void doSelectFrame( MAddress *, MPoint * );
	 void doSizeRow( void );
	 void doSizeCol( void );
	 void doMoveFrame( MPoint * );

	 void doFrameDelDeselect( int, int & );
	 int setContents( MEditString * );


	 void doGoHome( MAddress *, int );
	 void doGoPage( MAddress *, int, int );
	 void doGoUp( MAddress *, int );
	 void doGoDown( MAddress *, int );
	 void doGoLeft( MAddress *, int );
	 void doGoRight( MAddress *, int );

	 void processEndKey( MAddress *, int );
	 virtual int isMovement( int );		// returns 1 if char is a mvmnt char
	 virtual void handleDirectionKey( MAddress *, int, int );
	 int sizeRorC;
	 int incellEdit, incellStart, incellEnd;
	 MAddress incellAd;
	 int blinkOn;

	 int blinkRate;
	 int dontProcessUp;     // in some cases, we don't want to process the button1up
	 int incellOffset;		// how much to subtract on incell-hit-detection
	 								// for selection of text
};


// these are the selection types for button 1 selections
const int b1SelNothing=0; // select nothing
const int b1SelRow = 1; // select a set of rows
const int b1SelCol = 2; // select a set of columns
const int b1SelAll = 3; // select the whole layer
const int b1SizeRow = 4; // change the size of the row
const int b1SizeCol = 5; // change the size of the column
const int b1SelectFrame = 6; // change the size of the column
const int b1MoveFrame = 7; // move a graph/frame
const int b1SizeFrame = 8; // sizing a frame
const int b1Select1Cell =9; // alecting only one cell
const int b1SelCells = 10; // select a range of cells
const int b1InCellText = 11; // selecting text in cell

/*
    This is the trace of events that happen when a layer is changed
    94-09-15 dpp

    The MDisplayWindow receives a change layer event (script, user input, etc.) and
        sends a setLayer() message to the MMesaView that it owns

    The MMesaView sends the setLayer() message to the MSheetView

    The MSheetView sends an "about to change layers message" to the MMesaView

    The MMesaView sends a message (via WinSendMsg()) to the MDisplayWindow

    The MDisplayWindow swallows the script (if one is being edited) and rearranges the
        views (ie script or sheet)

    The MDisplayWindow updates the MTabView

    The MSheetView changes the selection

    The MSheetView updates

    The MMesaView updates the size of the scroll bars if the layer is a sheet layer

*/


// #ifndef _MH_sheet_View
#endif

