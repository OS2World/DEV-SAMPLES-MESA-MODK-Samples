/*

This module is the sample controller that is a subclass of the MController...
the thing that makes Mesa tick

*/

// make sure that this file is only included once
#ifndef _MH_MSampleController

#define _MH_MSampleController

// include our superclass
#include "controlr.h"

// our controller is a subclass of Mesa's generic controller
class MSampleController : public MGController
{
	public:
	MSampleController(const char *,int &,HAB,int useRGB,int bufferRedraw);
	virtual ~MSampleController();
    virtual void displayException(const MException *);
    virtual void addToDestroyList(HWND);
    virtual int beAlive();
    virtual int getInBeAlive();
    virtual void percentComplete(int);
    virtual void setStatusMessage(const char *);
    virtual MPoint getHitPoint();
    virtual HWND getApplicationFrameWindow();
    virtual HWND getApplicationClientWindow();
    virtual int isEditing();
    virtual int isEditingFormula();
    virtual int handleKey(int,int);
    virtual void updateFormulaView();
    virtual void resizeFormulaView();
    virtual void removeEdit();
    virtual MEditView *getEditView();
    virtual void runScript(const char *,MException *);
	virtual int getMenuWindow() {return 0;};
	virtual const char * getCurrencyChars(int page,int chr);
	virtual void setHitPoint(int x,int y);
	virtual void setEndFlag(int);
	virtual int checkKBDState();
	virtual MMesaModel *findModelChar( const char *, int );
	private:
	MPoint hitPoint;
};

// ifndef _MH_MSampleController
#endif
