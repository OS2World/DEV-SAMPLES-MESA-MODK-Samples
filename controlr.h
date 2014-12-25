/**************************************************************************
 *                                                                        *
 *                                                                        *
 *          This code is copyright (c) 1994   & 1995                      *
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
    this class is the class that handles global sheet functions for
    Mesa.  It handles:

    Keeping a list of open worksheets
        this is used for sheet linking
        Also used for opening files

    Keeps the real time feed table - String / Value
        Can be accessed by open sheets
        Updates sheets that subscribe to given feeds
        Allows multi-threaded changing of the feed table

    Keeps the list of AddIn functions

    Keeps the list of database queries
        All queries routed through this object

    Performs licensing functions

    routes messages to delegates
        - sheets opening and closing, etc.

    handles error panels
        - opens error panels

    There is only one object of this class instantiated for the
    application,  A pointer to the single object is passed to each
    model when the model is instantiated so that the model can access
    the functions of the object.

    1-17-94 dpp

    94-09-04 added getCharRes()
    94-09-19 dpp added makeBackup()
    94-12-11 dpp added support for a ping function that does not require forking a thread
	95-01-18 dpp added support for OS/2's atom table
*/

#ifndef _MH_mesa

#define _MH_mesa

#include "address.h"
#include "color.h"
#include "font.h"
#include "format.h"

#include "os2h.h"

#include "rect.h"
#include "object.h"


#if defined(M2Z) || defined(M2NT)
extern HAB TheMesaHAB;
// ifdef M2Z
#endif


class MException;
class MMesaModel;
class MValue;
class MRange;
class MEditView;
class MView;
class MPing;
class MMutex;
class MAddIn;
class MStack;
class MFunctionAddIn;
class MEditString;
class MCapture;
class MNull;

const int MAXPING = 32;
const int MAXCACHEDFONTS = 253;


#ifdef M2Z
typedef LHANDLE  HATOMTBL;
#endif

class MGController : public MObject
{
    public:
    // start a controller and pass the license string, and return the value of the enablement
    //  pass the handle to the application block, if we are in RGB mode
    // 94-09-17 dpp

    MGController(const char *,int &,
#if defined(M2Z) || defined(M2NT)
	HAB,
// ifdef M2Z
#endif
	int useRGB);

    virtual ~MGController();

    // all the methods listed below are thread-safe and may be
    // called from any thread in the application


    // these methods keep track of the worksheets that are currently open

    virtual void setUp();
	virtual void setupAddIns(); // this must be called after the application
								// has been started because many addins may need
								// application state information (like the menu bar)
    virtual void cleanUp();

    // all the methods listed below are thread-safe and may be
    // called from any thread in the application


    // these methods keep track of the worksheets that are currently open

    virtual int addModel(MMesaModel *);
        // adds a model if it is unique and has a unique pathName
        // returns 1 if successful or 0 if unsuccessful
    virtual void removeModel(MMesaModel *);
        // removes the model from the list

    // returns true if there is an unsaved model in the list
    virtual int unsavedModel();

    virtual void setAllModelsToSaved();


    // These methods return values for other worksheets
    // they manage value passing for inter-sheet recalculation

    // these methods are for the real time feeds
    // they are thread-safe
    // real time feeds are organized by feed service and by item name
    // for example feed service "Reuters" and item "IBM bid"
    virtual void setRealTimeValue(const char *,const char *,double);
    virtual int getRealTimeValue(const char *,const char *,double &);
    // polls the real time value and updates the subscribies
    // every second if the values change
    virtual void waitForData();


    virtual void recalcNeedFeeds();  // recalculate the sheets that need feeds

    // get the error string
    virtual int getMaxErrorNumber();

    virtual void displayException(const MException *) {};
    virtual void seriousError(const char *);
    virtual void postMsg(HWND,int,int,int);
	virtual int sendMsg( HWND, int, int, int );

#if defined(M2Z) || defined(M2NT)
    virtual void addToDestroyList(HWND) {}; // = 0;
#endif

    virtual void ping(int,HWND,int = 0,int = 0);

    // every 10 milliseconds, come up for air and ping the application
    virtual int beAlive() {return 1;}; // = 0;
    virtual int getInBeAlive() {return 0;}; // = 0;


    // send a message to the controller that a long operation is a
    // certain percent complete
    // this is thread-safe
    virtual void percentComplete(int) {};
	virtual void boundedPercentComplete( int, int, int ) {};
#if defined(M2Z) || defined(M2NT)
    virtual HWND getApplicationFrameWindow() {return NULL;}; // = 0;
    virtual HWND getApplicationClientWindow() {return NULL;}; // = 0;
#endif

    virtual void setStatusMessage(const char *) {};

    virtual int getUseRGB() {return useRGB;};
    virtual int getBufferRedraw() {return 1;};

/*
    virtual MPoint getHitPoint() = 0;
    virtual int isEditingFormula() = 0;
    virtual int isEditing() = 0;
    virtual int handleKey(int,int) = 0;
    virtual void updateFormulaView() = 0;
	 virtual void setFormulaView( const char * ) {};
    virtual void resizeFormulaView() = 0;
    virtual void removeEdit() = 0;
    virtual MEditView *getEditView() = 0;
    virtual MMesaModel *findModel(const char *,int needsPath = 1);
*/

    virtual MPoint getHitPoint() {MPoint po; po.set(0,0); return po;}; // = 0;
    virtual int isEditingFormula() {return 0;}; // = 0;
    virtual int isEditing() {return 0;}; // = 0;
    virtual int handleKey(int,int) {return 0;}; // = 0;
    virtual void updateFormulaView() {}; // = 0;
    virtual void updateStatusView() {};
	 virtual void setFormulaView( const char * ) {};
    virtual void resizeFormulaView() {}; // = 0;
    virtual void removeEdit() {}; // = 0;
    virtual MEditView *getEditView() {return NULL;};  // = 0;
    virtual MMesaModel *findModelChar(const char *,int needsPath = 1);
	virtual void invokeEdit( MEditString * ) {};
	
    // get info about wether we're in demo mode and what our capabilities are
    virtual int getInDemoMode();

    static void setupFuncs();

    // get a string from the resource file based on in integer key
    // 94-09-04 dpp
    virtual char *getCharRes(int);
	virtual int loadResString(int,char *);
    virtual void getErrorString(int,char *);
    virtual void getShortErrorString(int,char *);

    // get the license string for display
    // 94-09-17 dpp
    virtual const char *getLicense(int);

    // should we make a backup file?
    virtual int makeBackup() {return 0;};


   // controll the keyboard state flags
   virtual void setEndFlag (int on); // set the END flag to on(on=1) or off(on=0)
   virtual int checkKBDState(); //call whenever there is a possibility that the
                        // keyboard state has changed
   // override this method to process when a state has changed
   virtual void KBDStateHasChanged(int) {};

    virtual const char *getCurrencyChars(int page,int chr);

    virtual void getDefaultUndoAndLayers(int &un,int &lay) {un = 32; lay = 1;};
    virtual void getDefaultRowsAndCols(int &r,int &c) {r = c = 32;};
    virtual void getDefaultFont(MFont &aFont) {aFont.init("12.Helvetica");};
    virtual void getDefaultScale(float &aScale) {aScale=1.0;};
    virtual int getInCellEditing() {return 1;};

    virtual int getEnterBehavior() {return 0;};
    virtual void cycleCalcIndicator() {};


    // fint the number of a model or return -1 if not found
    virtual int findModel(MMesaModel *);

    virtual MMesaModel *_findModel(const char *,int needsPath = 1);
        // finds a model with a specific path, returns NULL
        // if the path is not found
    virtual void lockModel();
    virtual void unlockModel();

    // script related stuff
    virtual void runScript(const char *,MException *) {}; // = 0;

    virtual void addScriptToQueue(const char *) {};
    virtual int canExecute(int,int &flags) {flags = 0; return 0;};

#if defined(M2Z) || defined(M2NT)
    // monitor the ping QUEUE and send messages at the right time
    // 94-12-11 dpp
    virtual void watchPing();
#endif
	
	virtual char *getAtom(int);
	virtual int findAtom(const char *);
	
	virtual int getAtomForMesa();
		
	virtual int isRunning() {return running;};
	virtual const char *getTimeSep() { return timeSep; }
	virtual const char *getTimeAM() { return am; }
	virtual const char *getTimePM() { return pm; }
	virtual const int getDateOrder() { return dateOrder; }
	virtual const char *getDateSep() { return dateSep; }
	virtual const unsigned int getDateFormat() { return dateFormat; }
	virtual const unsigned int getTimeFormat() { return timeFormat; }
	virtual const char *getDecSep() { return decimalSep; }
	virtual const char *getThousandsSep() { return thousandsSep; }
	virtual const int getCurrencyPrefix() { return currencyPrefix; }
	virtual const char *getCurrency() { return currencyString; }

#if defined(M2Z) || defined(M2NT)
	// returns the "HWND" for the main menu
	// used by addins
	virtual int getMenuWindow() {return 0;} // = 0;
	virtual int addInPMMessage(int,int,int,int);
	virtual HWND getApplicationWindow() {return 0;};
	virtual HWND getActiveWindow() {return 0;};
#endif
	
	virtual void registerAddIn(void *,void *,int);
	// menu command, function (0 execute, 1 can execute, 2 help)
	virtual int doAddInMenuFunction(int,int);
	
	virtual MMesaModel *getActiveModel() {return 0;};
	virtual MMesaModel *openFile(const char *) {return 0;};
	virtual void selectRange(const char *) {return;};
	virtual int getCurrentAddress(MAddress *) {return 0;};
	virtual int getCurrentRange(MRange *) {return 0;};
	virtual MMesaModel *newModel() {return 0;};
	virtual void addInDoubleClick(MMesaModel *,const MAddress *);
	virtual int addInAboutToSave(MMesaModel *);
	virtual void addInOpened(MMesaModel *);
	virtual int addInDataAboutToBeEntered(MMesaModel *,const MAddress *,const char *);
	virtual int addInAboutToClose(MMesaModel *);
	virtual int performAddInFunction(const char *,int numberOfParams,int cache,
		MStack *stack,MMesaModel *model);
	virtual void registerFunctionAddIn(const char *name,const char *fbName,
		const char *fbProto,const char *fbDesc,const char *fbExample,int *fbMembers,
		void *callBack);
	virtual int findFuncAddIns(const char *,int = -1);
	virtual int getNumFuncAddIns() {return numFuncAddIns;};
	virtual const char *getFuncAddInName(int);
	virtual const char *getFuncAddInFBName(int);
	virtual const char *getFuncAddInFBPrototype(int);
	virtual const char *getFuncAddInFBDescription(int);
	virtual const char *getFuncAddInFBExample(int);
	virtual const int *getFuncAddInFBMembers(int);
	
	
	// script history
	virtual void addStringToHistoryBuffer(const char *) {return;};
	
	
	// are we the currently active application?
	virtual int isApplicationActive() {return 1;};
	
	// get the thread ID that was executing when this instance was created (i.e., the UI Thread)
	virtual int getThreadNum() {return myThreadNum;};
	virtual void insertOperator( const char * ) {};
	virtual void insertTextAndSelectArgs( const char * ) {};
	
    virtual MGraphPtr getBufferHPS();
    virtual void releaseBufferHPS();

    virtual unsigned int getTime() { return curTime; };
    virtual void setTime(unsigned int now) { curTime = now;};

    virtual void checkFontCache(const MFont *);

#ifdef M2MAC
	virtual void idleEvent();
	virtual void setCapture(MView *);
#endif

    private:
	// load any controller-wide defaults from ini files...
	void loadDefaults();
	void loadLicenseString( char *&license, char *&encrypted, HAB hab );
	void  processLicenseResults( int gotTheLicence, int enable, const char *lic, HAB hab );
    // the double-buffering facilities
#ifdef M2Z
    HDC dbHdc;
    HPS dbHps;
    HBITMAP dbHbm;
    MMutex *dbMutex;

    DATETIME lastFeedTime;
	HATOMTBL atoms;
#endif

#ifdef M2MAC
	MCapture *capture; // the instance of the view that we are using to capture mouse movement events
	MNull *myNull;
	MMutex *msgMut;
	int msgSendCnt;
	HWND msgWin[100];
	int msgNum[100];
	int msgParam1[100];
	int msgParam2[100];
#endif

    // font caching information
    MFont fonts[MAXCACHEDFONTS + 1];  // the fonts;
    int numFonts;      // the number of fonts in the array
    MMutex *fntMut;    // mutex for writing dealing with the fonts

    unsigned int curTime;

    int numModel,maxModel;
    MMesaModel **models;
    MMutex *pmodelMut;


    // int feedChanged;
    int waitForFeedNum;

    int useRGB;
    int inDemoMode;
    char *theLicense;

    // list of pingHolders
    MPing *thePings[MAXPING];
    MMutex *pingMut;
    int pingThreadNum;
	int running;

	// internationalization entries...
	char *timeSep;		// between hours, minutes and seconds
	char *dateSep;
	char *am, *pm;	// string used for AM/PM...
	int dateOrder, timeOrder;		// values stored in INI file...
	unsigned int dateFormat;		// mdy, dmy, or ymd
	unsigned int timeFormat;		// 12 hours vs 24 hours
	char *decimalSep;					// currency decimal separator
	char *thousandsSep;				// thousands separator
	int	fixedDec;					// number of digits to show for fixed decimal
	int	measurement;	// english, metric, picas, points.
	char currency[ 4 ][ 4 ];		// a 4x4 grid of currency characters...
	int	currencyPrefix;			// 1 if a prefix, 0 if a suffix
	char *currencyString;		// currency string
	
	int numAddIns,maxAddIns;
	MAddIn **addIns;
	
	int maxFuncAddIns,numFuncAddIns;
	MFunctionAddIn **funcAddIn;
	void sortFuncAddIns();

    MMutex *errorMut;

    char **errors;
    char **shortErrors;
    int numError;
	
	int myThreadNum;

   // Keyboard state flags
   int keystateflags;
};

// if this bit it set, we have a full size mesa worksheet
const int FULLSIZELIC = 0x8000;
const int NOTVALID_LICENSE = 2; // the license string was not valid
const int EXPIRED_LICENSE = 1; // the license has expired


//flag values for the keyboard state methods
const int KEYMASK_END         = 0x0001;
const int KEYMASK_CAPSLOCK    = 0x0002;
const int KEYMASK_NUMLOCK     = 0x0004;
const int KEYMASK_INSERTMODE  = 0x0008;
const int KEYMASK_SCROLLLOCK  = 0x0010;


#ifdef M2Z
// this is support for the entry point for background printing from WPS
#ifdef __cplusplus
extern "C"
{
#endif

void doBkgPrint(void *,char *);
#ifdef __cplusplus
}
#endif

// ifdef M2Z
#endif

#ifdef IN_DLL
extern MGController *TheMesa;
#endif

// IBMCHANGE
// the name of the application for defaults lookup
#if defined(M2Z)
#define ApplicationName "Mesa2"
#else
#define ApplicationName "Mesa"
#endif

// #ifndef _MH_mesa

#endif

