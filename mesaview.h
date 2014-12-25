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
*/


#ifndef _MH_mesa_view

#define _MH_mesa_view

#include "view.h"
#include "address.h"

class MMesaModel;
class MView;
class MSheetView;
class MScrollView;
class MDisplayInterest;
class MRange;
class MEditView;
class MSelection;
class MClipStream;
class MEditString;

class MMesaView : public MView {
    public:
    MMesaView( MView *,MMesaModel *);
	// MMesaView( HWND, MMesaModel * );
    virtual ~MMesaView();
    virtual void setUp(const MRect *,int = 0);
    virtual void cleanUp();
    //virtual MRESULT winCommand(HWND,ULONG,MPARAM,MPARAM,int &);
 	virtual int command( unsigned int, int & );
	
    //virtual MRESULT winVScroll(HWND,ULONG,MPARAM,MPARAM,int &);
	 virtual int vertScroll( int, int, int, int & );
    virtual int horizScroll( int, int, int, int & );

    virtual int size( int, int, int, int, int & );
    virtual int handleChar( unsigned int, unsigned int, int & );
	 virtual int winUpdateSheet(MChange *);
	virtual int resetView(MChange *);
    virtual int canExecute(int,int &);
    virtual void arrangeViews();

    virtual MMesaModel *getModel() {return model;};
    virtual const MAddress *getCurAdPtr();

    virtual void setCurAd(const MAddress *);
    virtual int getCurLayer();
    virtual void setCurRange(const MRange *);
    virtual void setAddressAndRange(const MAddress *,const MRange *);
    virtual const MSelection *getCurSelection();

    // return the name of the current layer
    virtual const char *getLayerName();

    // get the number of the current layer 94-09-15 dpp
    virtual int getLayerNumber();

    // can we edit the contents of the current selection? 94-09-15 dpp
    virtual int canEditContents();

    // is the current layer a script?
    virtual int isScriptSelected();

    // is the current layer a spreadsheet?
    virtual int isSheetSelected();

    virtual void aboutToDestroy();


    virtual void setLayer(int);
    virtual int scrollToVisible(const MAddress *,int = 0);
    virtual void scrollFrom(int,int);

    // stuff that has changed
    virtual void formatChanged(MChange *) {};


    virtual void contentsChanged(MChange *);

    // get the path to the directory holding the current worksheet
    // remember to free what you're given
    virtual char *getDirectory();

    // about to change the layer
    // 94-09-15 dpp
    virtual void aboutToChangeToLayer(int,int);

    // change the scroll bars to reflect the current position
    // 94-09-15 dpp
    virtual void updateScrollers() {updateSpecScroller(1,1);};
    // which scroller do we have to update
    virtual void updateSpecScroller(int v,int h);

    // select a given selections
    // 94-09-23 dpp
    virtual void select(const MSelection *);
    virtual void setSelection(const MSelection *);


    virtual int changedSize(MChange *);
    virtual int isEditingFormula();
    virtual int isEditing();
    virtual MEditView *getEditView();
	 virtual MEditString *getEditString();
	virtual void terminateEditing();
	
    virtual void removeEdit();
    virtual void updateFormulaView();
    virtual void updateStatusView();
	 virtual void resizeFormulaView();
	 virtual void setFormulaView(const char *);
    virtual int handleKey(int,int);
	virtual void copyFromEditView( MClipStream * );
	virtual void cutFromEditView( MClipStream * );
	virtual void pasteIntoEditView( MClipStream * );
	
    virtual char *getSelectionName();
    virtual char *getSelectionContents();
    virtual char *getSelectionRange();
    virtual void getSelectionFont(MFont *);
    virtual void getSelectionFormat(MFormat *);


    virtual int doesFrameExist( const char * );
	virtual char *getFrameName( int num );
	
	virtual MSheetView *getSheetView() {return sheet;};
	
    // create a shape
    virtual void newShape(int type,const char *offset,int offx,int offy,
        int wid,int hi,int lWid,int arrows);

	 virtual float getViewScale();
	 virtual void setViewScale( float sc );
	 virtual void insertTextAndSelectArgs( const char * );

	 virtual void insertOperator( const char * );
	 virtual MEditString *makeEditStr();
	
    private:
    MMesaModel *model;
    MSheetView *sheet;
    MScrollView *vScroll,*hScroll;
    MDisplayInterest *di;
	
	 void scriptColorString(const char *col, int bkg= 0);
	 void scriptFormatString( const char *fmt, int prec = -1 );
};


// _MH_display_window
#endif

