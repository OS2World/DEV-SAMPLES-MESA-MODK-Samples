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
    this module is the keyhandler and position-maintainer of the
	 currently edited cell...
    3-7-94 dpp
*/

#ifndef _MH_editString

#define _MH_editString

#include "clipstr.h"
#include "mesamod.h"

class MEditString {
	public:
	MEditString( const char * = 0, int = 0, int = 0, int = 1, MMesaModel *mp=NULL) ;
	virtual ~MEditString();

	virtual void setModel( MMesaModel *mp ) { model = mp; };
	virtual int handleKey(int,int);
	virtual void setString(const char *);
	virtual void selectRange(int,int,int);
	virtual char *getString() {return str;};
	virtual int getHasEdited() {return isEditing;};
	virtual void setIsEditing();
	virtual void setIsEditing(int);
	virtual void setEditRange(int,int,int = 0);
	virtual void undo();
	virtual void redo();
	virtual void insertAtStart(const char *);
	virtual void insertRefAtStart(const char *);
	virtual void removeSelection();
	virtual int getStart() const { return begin; };
	virtual int getEnd() const { return end; };
	virtual int getBlinkOn() const { return blinkOn; };
	virtual void setBlinkOn( int i ) { blinkOn = i; };
	 
	virtual int isEditingFormula();
	virtual int isCellSelectOK();
	
	virtual void selectArgs( int startPoint, int len);
	static int editGetDoSomething(int,int);
	virtual void copyToClipboard( MClipStream * );
	virtual void pasteInto( MClipStream * );
	virtual int rightOfOperator( const char *, int );
	virtual void toggleAbsolute();
	
	virtual void setCurLayer( int i ) { curLayer = i; };
	virtual int getCurLayer() const { return curLayer; };
	virtual void scrollToVisible( MDraw *, MRect * );
	virtual void setVisible( int i ) { visible = i; };
	virtual int getVisible() const { return visible; };
	virtual int getOffset() const { return offset; };
	virtual void setJustBlink( int i ) { justBlink = i; };
	virtual int getJustBlink() const { return justBlink; };
	virtual void setDownPoint( int i ) { downPoint = i; anchor = i; };
	virtual void setDownFlags( int i ) { downFlags = i; };
	virtual void beginSelect() { setEditRange( anchor, anchor ); }
	virtual void selectTo( int );
	virtual void setCanBeFormula( int i ) { canBeFormula = i; };
	virtual int getCanBeFormula() { return canBeFormula; };
	virtual void setFont( const MFont *fo ) { renderFont.init( fo ); };
	virtual int findChar( int x, float scale );
	virtual int isSelect() { return isSelecting; };
	
	private:
	char *str,*lastString;
	int max;
	int isEditing,justUndid;
	int begin,end;
	int blinkOn;
	int offset;
	int canSelRange;		// set from 1 to 0 when the user types something
							// which indicates that they are in formula-edit
							// mode rather than cell-select mode
	MMesaModel *model;
	int curLayer;
	int visible;		// char-pos to ensure visible at draw-time...
	int justBlink;		// set to 1 if just blinking the cursor, 0 otherwise...
	int anchor,isSelecting,downFlags,downPoint,lastPoint;
	int canBeFormula;		// can this do formula (ie cell selection) things
	void tone();
	MFont renderFont;
};

// ifndef _MH_editString
#endif
