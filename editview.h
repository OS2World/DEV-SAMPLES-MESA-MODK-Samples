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
    this module is the subclass of an MView that does text editing
    3-7-94 dpp
*/

#ifndef _MH_editView

#define _MH_editView

#include "view.h"
#include "rect.h"
#include "font.h"

class MEditString;

class MEditView : public MView {
	public:
    MEditView( MView *, int = 0, HWND super=0);
	virtual ~MEditView();

	virtual int drawSelf(MDraw *,const MRect *);
	virtual int hasDrawSelf() {return 1;};
	virtual void cleanUp();
	virtual void setUp(const MRect *,int = 0);
	virtual void setEditString( MEditString * );
	virtual void scrollToVisible(int);
	virtual int winPing( int, int );
	virtual int bufferWindow() {return 1;};

    // handle the mouse events
	virtual void mouse1Down(const MPoint *,int,int &);
	virtual void mouse1Up(const MPoint *,int,int &);
	virtual void mouse1MotionStart(int &);
	virtual void mouse1MotionEnd(int &);
#if defined(M2Z)
    virtual MRESULT winButton1DoubleClick(HWND,ULONG,MPARAM,MPARAM,int &);
#endif
	virtual int comboButton( int & );
	virtual int mouseMove( const MPoint *, int, int & );

	
    // find a character based on an x position in the edit field
    virtual int findChar(int);
	virtual void setFont(const MFont *);
	
	private:
	MEditString *es;	
	int blinkOn;
	MPoint thePoint;
	MFont editFont;
	int isSelecting;
	int downFlags, downPoint, lastPoint;
};

// ifndef _MH_editView
#endif


