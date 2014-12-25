/**************************************************************************
 *                                                                        *
 *                                                                        *
 *          This code is copyright (c) 1994                               *
 *                     Athena Design, Inc.                                *
 *                     and David Pollak                                   *
 *                                                                        *
 *                ALL RIGHTS RESERVED                                     *
 *                                                                        *
 *                                                                        *
 *                                                                        *
 *                                                                        *
 *                                                                        *
 **************************************************************************/

#include "lomos.h"
#include "sampcont.h"
#include "editstr.h"
#include "rect.h"
#include "mesaview.h"
#include <stdio.h>

MSampleController :: MSampleController(const char *lic,int &enable,HAB hab,int USERGB)
    : MGController(lic,enable,hab,USERGB)
{
	hitPoint.set(0,0);
    evptr=NULL;
    activeWnd=NULL;
}

MSampleController :: ~MSampleController()
{
    if (evptr) {
       evptr->cleanUp();
       delete evptr;
    } // endif
}

void MSampleController :: addToDestroyList(HWND)
{
}

int MSampleController :: beAlive()
{
    return 1;
}

int MSampleController :: getInBeAlive()
{
    return 0;
}

MPoint MSampleController :: getHitPoint()
{
	return hitPoint;
}

void MSampleController :: setHitPoint(int x,int y)
{
	hitPoint.set(x,y);
}


HWND MSampleController :: getApplicationFrameWindow()
{
    return 0;
}

HWND MSampleController :: getApplicationClientWindow()
{
    return 0;
}


int MSampleController :: handleKey(int,int)
{
    return 0;
}

void MSampleController :: runScript(const char *,MException *)
{
}

const char * MSampleController :: getCurrencyChars(int page,int chr)
{
    static char *cur[] = {
        // dollars
        ".",",","$","",
        // yen
        ".",",","\xBE","",
        // pounds
        ".",",","\x9C","",
        // ??
        ",",".","",""};

    return cur[page * 4 + chr];
}

// invokes an edit view
void MSampleController :: invokeEdit( MEditString * edstr)
{
    if (activeWnd) {
        WinSendMsg(activeWnd,WM_CREATEEDIT,(MPARAM)edstr,NULL);
    } // endif
}

// set the formula in the formula bar
void MSampleController :: setFormulaView( const char * txt)
{
    if (activeWnd) {
        WinSendMsg(activeWnd,WM_SETFORMULATXT,(MPARAM)txt,NULL);
    } // endif
}

void MSampleController :: removeEdit()
{
    if (activeWnd) {
        WinSendMsg(activeWnd,WM_REMOVEEDIT,NULL,NULL);
    } // endif
}

int MSampleController :: getInCellEditing()
{
    if (activeWnd) {
        return (int)WinSendMsg(activeWnd,WM_INCELLEDIT,NULL,NULL);
    } // endif
    return 0;
}

void MSampleController :: updateFormulaView()
{
    if (activeWnd) {
        WinSendMsg(activeWnd,WM_UPDATEFORMULA,NULL,NULL);
    } // endif
}

MEditView *MSampleController :: getEditView()
{
    if (activeWnd) {
        return (MEditView *)WinSendMsg(activeWnd,WM_GETEDITVIEW,NULL,NULL);
    } // endif
    return NULL;
}

// these two methods are here for the moment.  In future versions these methods
// might be eliminated because they aren't needed.
int MSampleController :: isEditingFormula()
{
 return 0;
}

int MSampleController :: isEditing()
{
 return 0;
}

void MSampleController :: setHandleForEditViewOwner(HWND hwnd)
{
    if (evptr) {
       evptr->cleanUp();
       delete evptr;
       evptr=NULL;
    } // endif
    activeWnd=hwnd;
}
