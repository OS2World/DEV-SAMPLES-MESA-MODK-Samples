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

#include "sampcont.h"
#include <stdio.h>

MSampleController :: MSampleController(const char *lic,int &enable,HAB hab,int USERGB,int bufferRedraw)
    : MGController(lic,enable,hab,USERGB)
{
	hitPoint.set(0,0);
}

MSampleController :: ~MSampleController()
{
}

void MSampleController :: displayException(const MException *)
{
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

void MSampleController :: percentComplete(int)
{
}

void MSampleController :: setStatusMessage(const char *)
{
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

int MSampleController :: isEditingFormula()
{
    return 0;
}

int MSampleController :: isEditing()
{
    return 0;
}

int MSampleController :: handleKey(int,int)
{
    return 0;
}

void MSampleController :: updateFormulaView()
{
}

void MSampleController :: removeEdit()
{
}

MEditView *MSampleController :: getEditView()
{
    return NULL;
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

void MSampleController :: resizeFormulaView()
{
}

void MSampleController :: setEndFlag (int on)
{
}

int MSampleController :: checkKBDState()
{
return 0;
}

MMesaModel *MSampleController :: findModelChar( const char *, int )
{
	return NULL;
}

