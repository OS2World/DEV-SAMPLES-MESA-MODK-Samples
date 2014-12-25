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
    this is the abstract class that handles the window functions

    To change default behavior, over-ride any of the methods listed below

    1-24-94 dpp

    94-09-03 dpp added support for getting MRect's
    94-09-15 dpp changed #define statements to consts and updateLayerNumber()
    94-09-21 dpp added Drag & Drop support
*/

#ifndef _MH_window

#define _MH_window


#include "os2h.h"

#include "view.h"

class MChange;
class MRect;
class MPoint;
class MDraw;
// class MView;

#if defined(M2Z) || defined(M2NT)
// class MWindow : public MObject
class MWindow : public MView
#elif defined(M2MAC)
#include "bwindow.h"

class MWindow : public MBWindow
#endif
{
    public:
    MWindow();
    virtual ~MWindow();

    virtual void setUp(const MRect *,int = 0);
    virtual void cleanUp();

    //virtual HWND getFrameWindow() {return frame;};
    //virtual HWND getClientWindow() {return getView();};
    //virtual void getFrameRect(MRect *);
    //virtual void getRect(MRect *re) {getClientWindowViewRect(re);};
    //virtual void getViewRect(MRect *re) {getClientWindowViewRect(re);};


    //virtual int changedSize(MChange *) {return 0;};
	//virtual int resetView(MChange *) {return 0;};
    //virtual int hasDrawSelf() {return 0;};

    //virtual int canExecute(int,int &flags) {flags = 0; return 0;};
	//virtual int handleChar( unsigned int, unsigned int, int & ) { return 0; };


    // force a window re-draw
    virtual void update();

    virtual int drawSelf(MDraw *,const MRect *);

    //virtual void cycleCalcIndicator() {};

    // perform a REXX function
    // virtual void threadRexxFuncs() {};


    // virtual void setFocus() { WinSetFocus( HWND_DESKTOP, client ); };
    virtual void setFocus();

    virtual void makeActive();
	
    // prepare the window to be closed
    // virtual void aboutToDestroy();


    // data member access

	
	virtual void invalidateRect(const MRect *);
	virtual void updateWindow();
	
// Mesa-unpacked, not system dependent, windowing Messages

//	virtual int vertScroll( int, int, int, int & ) { return 0; };
//	virtual int horizScroll( int, int, int, int & ) { return 0; };

	// MsetFocus takes the current window, the focus-window, a state
	// (1 = getting focus, 0 = losing focus)
	// virtual int MsetFocus( unsigned long, unsigned long, int, int & ) { return 0; };
	
	// size takes old x, old y, new x, new y
	virtual int size( int, int, int, int, int & ) { return 0; };
	// sysCommand takes a command, a source, and a mouse-or-keyboard flag
	// virtual int sysCommand( unsigned int, int, int, int & ) { return 0; };
	// mouseMove takes a new point, and keyboard flags
	//virtual int mouseMove( const MPoint *, int, int &) {return 0;};
	// close
	// virtual int Mclose( unsigned long, int & ) {return 0;};
	// activate
	virtual int activate( unsigned long, int, int &) {return 0;};
	virtual int Mhelp( unsigned int, int & ) { return 0; };
	virtual int command( unsigned int, int & ) { return 0; };
	virtual int comboButton( int & ) { return 0; };
	// virtual int contextMenu( const MPoint *, int & ) { return 0; };
	virtual int control( unsigned int, unsigned int, int & ) { return 0; };
	

#if defined(M2Z) || defined(M2NT)
    //virtual void setFrameWindow(HWND);
    //virtual void setClientWindow(HWND);
	//virtual MRESULT winDestroy(HWND hw,ULONG,MPARAM,MPARAM,int &handled);
    // virtual void getFrameRectL(RECTL *);

    static int isWindowMaximized(HWND);
    static int isWindowMinimized(HWND);
    static int isMesaWindow(HWND);

    virtual HWND createStdWindow(HWND,ULONG,PULONG,PSZ,
                ULONG,HMODULE,ULONG,PHWND);
/*
    virtual HWND createWindow (HWND,PSZ,ULONG,LONG,LONG,LONG,LONG,
                HWND ,HWND);
*/
#endif

#ifdef M2MAC

    virtual void getClientWindowViewRect(MRect *);
    virtual  HWND getView();
    virtual HWND getFrameWindow() {return getView();};
	virtual void aboutToDestroy();

	virtual int Mclose(HWND, int & ) {return 0;};
    virtual int winUpdateSheet(MChange *) {return 0;};
    virtual int winPing(int,int) {return 0;};
    virtual int changedSize(MChange *) {return 0;};
	virtual int resetView(MChange *) {return 0;};
    // sent to a window when a display format has changed
    virtual void formatChanged(MChange *) {};

    // sent to a window when the data in the worksheet has changed
    virtual void contentsChanged(MChange *) {};

    virtual void percentChanged(int) {};
    virtual void updateLayerNumber(int) {};
	//dpr added
	 virtual void memOpenRevert(int &) {};
    virtual void cycleCalcIndicator() {};

// ifdef M2MAC
#endif

    private:
#if defined(M2Z) || defined(M2NT)
    // HWND frame;
#endif
	int ___notUsed;
	
};

#if defined(M2Z) || defined(M2NT)
extern MRESULT EXPENTRY handleWindowProc(HWND , ULONG , MPARAM ,MPARAM );

extern MRESULT EXPENTRY appHandleWindowProc(HWND , ULONG , MPARAM ,MPARAM );
#endif


// user level messages that get sent to the system and dispatched to windows


// #ifndef _MH_window

#endif

