/*

This module is the sample controller that is a subclass of the MController...
the thing that makes Mesa tick

*/

// make sure that this file is only included once
#ifndef _MH_MSampleController

#define _MH_MSampleController

// include our superclass
#include "controlr.h"
#include "editview.h"
// our controller is a subclass of Mesa's generic controller
class MSampleController : public MGController
{
	public:
	MSampleController(const char *,int &,HAB,int useRGB);
	virtual ~MSampleController();
    virtual int getBufferRedraw() {return 1;};
    virtual void addToDestroyList(HWND);
    virtual void getDefaultRowsAndCols(int &r,int &c) {r = 32;c = 14;};
    virtual int beAlive();
    virtual int getInBeAlive();
    virtual MPoint getHitPoint();
    virtual HWND getApplicationFrameWindow();
    virtual HWND getApplicationClientWindow();
    virtual int handleKey(int,int);
    virtual void runScript(const char *,MException *);
	virtual int getMenuWindow() {return 0;};
	virtual const char * getCurrencyChars(int page,int chr);
	virtual void setHitPoint(int x,int y);

    virtual int isEditingFormula();
    virtual int isEditing();
	virtual void invokeEdit( MEditString * );
    virtual void setFormulaView( const char * );
    virtual void removeEdit();
    virtual int getInCellEditing();
    virtual void updateFormulaView();
    virtual MEditView *getEditView();

    virtual void setHandleForEditViewOwner(HWND hwnd);

	private:
	MPoint hitPoint;
    MEditView *evptr;  // pointer to the editview that might be created
    HWND activeWnd;   // hwnd to the dialog window holding the sheetview
};

extern MSampleController *MyMesa;

// ifndef _MH_MSampleController
#endif
