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

    This is an OS/2 class that handles abstract views.  A view is a
    display region that can be placed inside a window.  It is implemented
    as an OS/2 window and is a sub-class of the OS/2 Window class

*/

#ifndef _MH_view

#define _MH_view


#include "os2h.h"
#include "object.h"
#include "color.h"
#include "format.h"
#include "font.h"

class MFont;
class MChange;
class MRect;
class MPoint;
class MDraw;

#if defined(M2Z) || defined(M2NT)
//class MView : public MWindow
class MView : public MObject
#elif defined(M2MAC)
#include "bview.h"

class MView : public MBView
#endif
{
    public:
    MView( MView *,int, HWND = 0);
	virtual void setView(HWND h);
	virtual void setHWND(HWND);
    virtual ~MView();
    virtual void setUp(const MRect *,int = 0);
    virtual void cleanUp();
    virtual int drawSelf(MDraw *,const MRect *);
    virtual void setViewPos(const MRect *);

    // if you subclass and still want d&d font and color support,
    // make sure you call this method
    // virtual MRESULT winHitTest(HWND,ULONG,MPARAM,MPARAM,int &);

    virtual void setSuperview( MView *h ) { superview = h; superHWND = h -> getView(); };
    virtual void setSuperSuperHWND( HWND h ) { supersuperHWND = h; };
    virtual void setFocus();

#if defined(M2Z) || defined(M2NT)
    virtual MRESULT winPresParamChanged(HWND,ULONG,MPARAM,MPARAM,int &);
#endif

    virtual void colorDroppedAt(MColor,int,int) {};
    virtual void bkgColorDroppedAt(MColor,int,int) {};
    virtual void fontDroppedAt(const MFont *,int,int) {};

//#ifdef M2MAC
    virtual MView *getSuperview() {return superview;};
//#else
	// FIXMENT
	// FIXMEOS - revise the view hierarchy to make MView the superclass of MWindow
//	virtual MWindow *getSuperview() {return superview;};
//#endif


	 virtual HWND getSuperHWND() { return superHWND; };

    //virtual HWND getSuperview() {return superview;};
    //virtual void setSuperview(HWND h) {superview = h;};
    virtual void setSuperHWND( HWND h ) { superHWND = h;};

	 //virtual MRESULT winHelp(HWND,ULONG,MPARAM,MPARAM,int &);
	
    // virtual int contextMenu( const MPoint *,int &);
    virtual int getObjectMenu();

	 virtual const MFont *getFont() { return &viewFont; };
	 virtual const MFormat *getFormat() { return &viewFormat; };
	 virtual void setFont( const MFont *newFont )
	 	{ viewFont.init( newFont ); };
	 virtual void setFormat( const MFormat *newFormat )
	 	{ viewFormat.init( newFormat ); };
	 	
	 	
    virtual void invalidateRect(const MRect *);
    virtual void validateRect(const MRect *);
    virtual void getInvalidRect(MRect *);

	virtual HWND getView();

	virtual void aboutToDestroy();
	virtual int size(int,int,int,int,int &) {return 0;};
	virtual void getViewRect(MRect *);
    virtual void getClientWindowViewRect(MRect *);

	virtual int activate( unsigned long, int, int &) {return 0;};
	virtual int Mhelp( unsigned int, int & );
	virtual int command( unsigned int, int & ) { return 0; };
	virtual int comboButton( int & ) { return 0; };
	virtual int contextMenu( const MPoint *, int & );
	virtual int control( unsigned int, unsigned int, int & ) { return 0; };
	// mouseMove takes a new point, and keyboard flags
	virtual int mouseMove( const MPoint *, int, int &) {return 0;};
	// MsetFocus takes the current window, the focus-window, a state
	// (1 = getting focus, 0 = losing focus)
	virtual int MsetFocus( unsigned long, unsigned long, int, int & ) { return 0; };
	// sysCommand takes a command, a source, and a mouse-or-keyboard flag
	virtual int sysCommand( unsigned int, int, int, int & ) { return 0; };
	// close
	virtual int Mclose(HWND, int & ) {return 0;};

    virtual int hasDrawSelf() {return 0;};
	virtual float getDrawScale() {return 1.0;};

    virtual void mouse1Down(const MPoint *,int,int &) {};
    virtual void mouse2Down(const MPoint *,int,int &) {};
    virtual void mouse3Down(const MPoint *,int,int &) {};
    virtual void mouse1Up(const MPoint *,int,int &) {};
    virtual void mouse2Up(const MPoint *,int,int &) {};
    virtual void mouse3Up(const MPoint *,int,int &) {};
    virtual void mouse1Click(const MPoint *,int,int &) {};
    virtual void mouse2Click(const MPoint *,int,int &) {};
    virtual void mouse3Click(const MPoint *,int,int &) {};
    virtual void mouse1DblClick(const MPoint *,int,int &) {};
    virtual void mouse2DblClick(const MPoint *,int,int &) {};
    virtual void mouse3DblClick(const MPoint *,int,int &) {};
    virtual void mouse1MotionStart(int &) {};
    virtual void mouse1MotionEnd(int &) {};
    virtual void mouse2MotionStart(int &) {};
    virtual void mouse2MotionEnd(int &) {};
    virtual void mouse3MotionStart(int &) {};
    virtual void mouse3MotionEnd(int &) {};

	virtual int vertScroll( int, int, int, int & ) { return 0; };
	virtual int horizScroll( int, int, int, int & ) { return 0; };

	virtual int positionChanged( int, int & ) { return 0; };
    virtual int winPing(int,int) {return 0;};

    virtual int changedSize(MChange *) {return 0;};
	virtual int resetView(MChange *) {return 0;};

    virtual void percentChanged(int) {};
    virtual int bufferWindow() {return 0;};
    virtual void updateLayerNumber(int,int) {};
	//dpr added
	 virtual void memOpenRevert(int &) {};

    // sent to a window when a display format has changed
    virtual void formatChanged(MChange *) {};

    // sent to a window when the data in the worksheet has changed
    virtual void contentsChanged(MChange *) {};

    // force a window re-draw
    virtual void update();

    virtual int canExecute(int,int &flags) {flags = 0; return 0;};
	virtual int handleChar( unsigned int, unsigned int, int & ) { return 0; };

    virtual void cycleCalcIndicator() {};
    virtual int winUpdateSheet(MChange *) {return 0;};

    // perform a REXX function
    virtual void threadRexxFuncs() {};

    virtual void enableDialogWindow( unsigned int, unsigned int, int );

#if defined(M2Z) || defined(M2NT)
    virtual HWND getFrameWindow() {return frame;};
    virtual HWND getClientWindow() {return view;};

    virtual void getFrameRect(MRect *);
    // virtual void getClientWindowViewRect(MRect *);
    virtual void getRect(MRect *re) {getClientWindowViewRect(re);};
    // virtual void getViewRect(MRect *re) {getClientWindowViewRect(re);};

    virtual void setFrameWindow(HWND h) {frame = h;};
    virtual void setClientWindow(HWND h) {view = h;};

    virtual void getFrameRectL(RECTL *);
	
// #if defined(M2Z) || defined(M2NT)
#endif

	virtual void setCaptureOn(int);

/*
#ifdef M2MAC
	// virtual void setUp(const MRect *);
#else
	 virtual void setCapture(HWND h) {WinSetCapture(HWND_DESKTOP,h);};
#endif
*/

#if defined(M2Z) || defined(M2NT)
    // these methods handle various different workspace manager
    // messages
    virtual MRESULT winAdjustWindowPos(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winCalcFrameRect(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winCalcValidRects(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winCreate(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winDestroy(HWND,ULONG,MPARAM,MPARAM,int &);
    virtual MRESULT winEnable(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winMove(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winPaint(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winQueryWindowParams(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winSetWindowParams(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winShow(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winPositionChanged(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winEraseBackground(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winMenuSelect(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winInitMenu(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winControlPointer(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winDrawItem(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winFocusChanged(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    //virtual MRESULT winHelp(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winMeasureItem(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winMenuEnd(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winNextMenu(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winQueryFocusPos(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winQueryConvertPos(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winNull(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winHitTest(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winSetSelection(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winPPaint(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winPSetFocus(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winPSysColorChange(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winPSize(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winPActivate(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winPControl(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winTimer(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winSem1(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winSem2(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winSem3(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winSem4(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winQuit(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winSysColorChange(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winSysValueChanged(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winAppTerminateNotify(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
//    virtual MRESULT winPresParamChanged(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winQueryDlgCode(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winInitDlg(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winSubstituteString(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winMatchMnemonic(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winSaveApplication(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winMouseLasr(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winExtMouseFirst(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winExtMouseLast(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winMouseTranslateFirst(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winMouseTranslateLast(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winSingleSelect(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winOpen(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winTextEdit(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winBeginSelect(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winMouseLast(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winContextHelp(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winChar(HWND,ULONG,MPARAM,MPARAM,int &);
    virtual MRESULT winVioChar(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winBeginDrag(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winDDEAck(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winDDEAdvise(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winDDEData(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winDDEExecute(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winDDEInitiate(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winDDEInitiateAck(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winDDEPoke(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winDDERequest(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winDDETerminate(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winDDEUnadvise(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winDestroyClipboard(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winDrawClipboard(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winFlashWindow(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winFormatFrame(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winHScrollClipboard(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winJournalNotify(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winMinMaxFrame(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winPaintClipboard(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winQueryAccelTable(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winQueryFocusChain(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winQueryFrameCount(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winQueryFrameInfo(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winQueryIcon(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winQueryTrackInfo(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winRenderAllFmts(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winRenderFmt(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winSetAccelTable(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winSetBorderSize(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winSetIcon(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winSizeClipboard(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winTrackFrame(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winTranslateAccel(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winUpdateFrame(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winVScrollClipboard(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winDefault(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winEndSelect(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winEndDrag(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual void getClientWindowViewRectL(RECTL *);
    virtual void getRectL(RECTL *re) {getClientWindowViewRectL(re);};
/*
    virtual HWND createStdWindow(HWND,ULONG,PULONG,PSZ,
                ULONG,HMODULE,ULONG,PHWND);
*/

    virtual HWND createWindow (HWND,PSZ,ULONG,LONG,LONG,LONG,LONG,
                HWND ,HWND);
    virtual PFNWP getWinProc() {return frameWindowProc;};

    virtual void setWinProc(PFNWP);


    // stuff that OS/2 SHOULD provide
    virtual void getItemText(int id,char *text);
    virtual void setItemText(int id,const char *text);
    virtual double getItemValue(int id);
    virtual void setItemValue(int,double);
    virtual int getButtonValue(int);
    virtual void setButtonValue(int,int);
    virtual int getSpinValue(int);
    virtual void setSpinValue(int,int);
    virtual int getSelectValue(int);
    virtual void setSelectValue(int,int);
    virtual int getRadioValue(int numItems,const int *itemList);
    virtual void setRadioValue(int val,int numItems,const int *itemList);
    virtual int itemNumFromList(int item,int num,const int *itemList);
	virtual HWND getWindowFromControl( HWND, int );
	virtual int getListItem( HWND );
	virtual void setListItem( HWND, int );
	virtual void getListItemText( HWND, char *cBuf );


#endif

#if defined(M2Z)
	// OS/2-specific method functions -- if an application needs to,
	// it can override any of these methods for direct access.  All
	// are provided in a generic, unpacked form, tho, for cross-platform
	// access
	
    virtual MRESULT winVScroll(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winHScroll(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winSize(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winSetFocus(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winSysCommand(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winMouseMove(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winClose(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winActivate(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winHelp(HWND,ULONG,MPARAM,MPARAM,int &);
    virtual MRESULT winCommand(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winChord(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winContextMenu(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winControl(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};


// mouse messages that should be unnecessary/unused?
    virtual MRESULT winButton1(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winButton2(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winButton3(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winButton1Up(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winButton1Click(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winButton3DoubleClick(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winButton2Up(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winButton2DoubleClick(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winButton3Up(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winButton1MotionStart(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winButton1MotionEnd(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winButton1DoubleClick(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winButton3Click(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winButton2MotionStart(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winButton2MotionEnd(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winButton2Click(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winButton3MotionStart(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winButton3MotionEnd(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};

    // drag & drop support
    // 94-09-21 dpp
    virtual MRESULT winDragRenderPrepare(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winDragDiscardObject(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winDragError(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winDragFileComplete(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winDragLeave(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winDragOver(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winDragOverNotify(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winDragDrop(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winDragDropHelp(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winDragEmphasizeTarget(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winDragEndConversation(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winDragFileRendered(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winDragPrintObject(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winDragRender(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winDragRenderComplete(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};
    virtual MRESULT winDragRenderFile(HWND,ULONG,MPARAM,MPARAM,int &) {return 0;};

    static MView *windowInProcess;
#endif

    protected:
    HWND menu;

    private:
    MView *superview;
	HWND superHWND;
	HWND supersuperHWND;		// used to pass messages up to the super-parent
    //int doneInit;
	MFormat viewFormat;
	MFont viewFont;

#if defined(M2Z) || defined(M2NT)
	HWND view;
	HWND frame;
    PFNWP frameWindowProc;
#endif
};

#ifdef M2MAC
#define WM_USER 1000

// some command numbers that we have to implement in Mesa to get the message posting stuff
// to work correctly
// 95-08-07 dpp

#define WM_CLOSE 			(WM_USER - 1)
#define WM_COMMAND 			(WM_USER - 2)

// here are some constant window numbers for window message posting
// 95-08-07 dpp
#define MApplicationFrameWindowNum		-1

#endif

// update all windows belonging to a sheet mp1 - the sheet, mp2 - null
const int MEM_UPDATE = (WM_USER + 1);
const int MEM_PING = (WM_USER + 2);
const int MEM_CHANGEDSIZE = (WM_USER + 3);
const int MEM_PERCENT = (WM_USER + 4);
const int MEM_FMT_CHANGED = (WM_USER + 5);
const int MEM_CONTENTS_CHANGED = (WM_USER + 6);
const int MEM_ADJUST_MAX = (WM_USER + 7);
const int MEM_SET_LAYER = (WM_USER + 8); // sent to a window when the layer is changed
const int MEM_REXX = (WM_USER + 9); // do a REXX thing
const int MEM_CALC = (WM_USER + 13); // calc indicator
const int MEM_RESET_VIEW = (WM_USER + 11); // reset the view
const int MEM_OPEN_REVERT = (WM_USER + 12 ); // file revert to saved...

// Mesa-specific key masks, rather than OS/2 specific ones...
const int MESA_SHIFT 			= 0x0001;
const int MESA_ALT				= 0x0002;
const int MESA_CTRL				= 0x0004;
const int MESA_NUMERICKEYPAD	= 0x0008;
const int MESA_NUMLOCK			= 0x0010;
const int MESA_SCROLLLOCK     = 0x0020;

const int LEFTARROW = 0x4be0;
const int CLEFTARROW = 0x73e0;
const int RIGHTARROW = 0x4de0;
const int CRIGHTARROW = 0x74e0;
const int ESCCHAR = 0x11b;
const int UPARROW = 0x48e0;
const int DOWNARROW = 0x50e0;

const int DELKEY		= 0x53e0;
const int KPDELKEY	= 0x5300;
const int INSERTKEY	= 0x52e0;
const int KPINSERTKEY = 0x5200;
const int HOMEKEY		= 0x47e0;
const int KPHOMEKEY	= 0x4700;
const int ENDKEY		= 0x4fe0;
const int KPENDKEY	= 0x4f00;
const int PGUPKEY		= 0x49e0;
const int KPPGUPKEY	= 0x4900;
const int PGDWNKEY	= 0x51e0;
const int KPPGDWNKEY	= 0x5100;
const int PGLEFTKEY	= 0x84e0;
const int PGRIGHTKEY	= 0x76e0;

const int F1KEY = 0x3b0000;
const int F2KEY = 0x3c0000;
const int F3KEY = 0x3d0000;
const int F4KEY = 0x3e0000;
const int F5KEY = 0x3f0000;
const int F6KEY = 0x400000;
const int F7KEY = 0x410000;
const int F8KEY = 0x420000;
const int F9KEY = 0x430000;

const int RETURNKEY = 13;
const int ENTERKEY = 10;
const int TABKEY = 9;
const int BKTABKEY = 7;

const int NUMLOCKKEY = 0x001D0000;

// the following are the names of window classes that will be pre-registered


#define M_APP_WINDOW "MesaAW"

// ifndef _MH_view
#endif


