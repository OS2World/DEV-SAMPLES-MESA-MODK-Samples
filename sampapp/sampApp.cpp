/*
sampApp.cpp
*/

#include "sampApp.h"
#include "sampcont.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include "feed.h"
#include "mesamod.h"
#include "mesaview.h"
#include "rect.h"
#include "except.h"
#include "filestr.h"
#include "sheetv.h"

static	char *stockNames[ 5 ];
static 	float prices[ 5 ];

static	char address[ 128 ];
static	char contents[ 512 ];

MSampleController *MyMesa;
MMesaModel *theModel,*theModel2;
MMesaView *theView,*theView2;

//
// sample dialog procedure
//

static MRESULT EXPENTRY sampProc(HWND hw,ULONG msg,MPARAM mp1,MPARAM mp2)
{
	MRect tre,tre2;
	SWP swp;
	HWND hwnd;
	MAddress ad,a2;
	MException me;
	MSheetView *sv;
	static char *titles[] = {"Stock","Current Bid Price"};
	MRange ra;
	MFormat fo;
	
	switch( msg ) {
	case WM_INITDLG:
		WinSendMsg( hw, MEM_UPDATESCREEN, NULL, NULL );

		// clear the address/contents fields...
		address[ 0 ] = 0;
		contents[ 0 ] = 0;

		WinSetWindowText( WinWindowFromID( hw, SAMPAPP_ADDRESS ), address );
		WinSetWindowText( WinWindowFromID( hw, SAMPAPP_CONTENTS ), contents );
		
		// initialize the buttons...		
		WinEnableWindow( WinWindowFromID( hw, DID_RANDOM ), 1 );
		WinEnableWindow( WinWindowFromID( hw, DID_ENDWALK ), 0 );
		
		hwnd = WinWindowFromID(hw,SAMPAPP_VIEW);
		WinQueryWindowPos(hwnd,&swp);
		
		tre.setX(swp.x);
		tre.setY(swp.y);
		tre.setWid(swp.cx);
		tre.setHi(swp.cy);
		
		tre2 = tre;
		tre.setHi(tre.getHi() / 2);
		// tre.round();
		tre.offsetY(tre.getHi());
		tre2.setHi(tre.getHi());

		theModel = new MMesaModel;
		
		theModel -> setUp(MyMesa);
		
		ad.set(0,0,0);
		theModel -> setCellToString(&ad,"HOPII",0,&me,NULL);
		ad.set(1,0,0);
		theModel -> setCellToString(&ad,"STONE",0,&me,NULL);
		ad.set(2,0,0);
		theModel -> setCellToString(&ad,"MESAC",0,&me,NULL);
		ad.set(3,0,0);
		theModel -> setCellToString(&ad,"CARGZ",0,&me,NULL);
		ad.set(4,0,0);
		theModel -> setCellToString(&ad,"ARCSD",0,&me,NULL);

		ad.set(0,1,0);
		theModel -> setCellToString(&ad,"=FEED(\"Bid\",A1)",0,&me,NULL);
		ad.set(1,1,0);
		theModel -> setCellToString(&ad,"=SAME($B$1)",0,&me,NULL);
		ad.set(2,1,0);
		theModel -> setCellToString(&ad,"=SAME($B$1)",0,&me,NULL);
		ad.set(3,1,0);
		theModel -> setCellToString(&ad,"=SAME($B$1)",0,&me,NULL);
		ad.set(4,1,0);
		theModel -> setCellToString(&ad,"=SAME($B$1)",0,&me,NULL);
		
		ra.init();
		ad.set(0,1,0);
		a2.set(4,1,0);
		ra.set(&ad,&a2);
		fo.init();
		fo.setMergePrecision(1);
		fo.setMergeFormat(1);
		fo.setFormat(currencyTypeFormat |
			currencySubtypeFormat | 2);
		
		theModel -> setRangeToFormat(&ra,&fo,defaultAction,NULL,&me);
		
		fo.free();
		ra.free();
		
		theView = new MMesaView(0,theModel);
		theView -> setHWND( hw );
		theView -> setUp(&tre);
		
		sv = theView -> getSheetView();
		
		sv -> setColumnTitleHeight(36);
		sv -> setColumnTitles((const char **) titles,2);


		theModel2 = new MMesaModel;
		
		theModel2 -> setUp(MyMesa);
		
		theView2 = new MMesaView(0,theModel2);
		theView2 -> setHWND( hw );
		theView2 -> setUp(&tre2);
		theModel2 -> setPathName("examples\\portflio.m2",0);
		theModel2 -> loadFromPath(0,&me);

		
		break;
		
	case WM_COMMAND:
		{
			int control = SHORT1FROMMP( mp1 );
			int notify = SHORT2FROMMP( mp1 );
			
			switch( control ) {
			case DID_RANDOM:
				WinStartTimer( WinQueryAnchorBlock( hw ), hw, ID_TIMER, 1000 );
				// turn off the button
				WinEnableWindow( WinWindowFromID( hw, DID_RANDOM ), 0 );
				WinEnableWindow( WinWindowFromID( hw, DID_ENDWALK ), 1 );
				break;
				
			case DID_ENDWALK:
				WinStopTimer( WinQueryAnchorBlock( hw ), hw, ID_TIMER );
				// turn off the button
				WinEnableWindow( WinWindowFromID( hw, DID_RANDOM ), 1 );
				WinEnableWindow( WinWindowFromID( hw, DID_ENDWALK ), 0 );
				break;
				
			case DID_EXIT:
				WinDismissDlg( hw, 0 );
				return( ( MRESULT )1 );
				
			case DID_LOADTEXT:
				{
					MFileStream *mfs;
					
					mfs = new MFileStream(MSTREAM_READ,"sample.txt");
					if (!mfs -> getError())
					{
						MAddress ad;
						MException me;
						
						ad.set(3,3,0);
						
						theModel -> importText(mfs,&ad,0,NULL,&me);
						
						MyMesa -> displayException(&me);
						MyMesa -> displayException(mfs -> getException());
					}
					
					delete mfs;
				}
				return ((MRESULT) 1);
			
			default:
				return WinDefDlgProc( hw, msg, mp1, mp2 );
			}
		
		}	// the WM_COMMAND message
		break;
	
	case WM_CONTROL:
		{
			int control = SHORT1FROMMP( mp1 );
			int notify = SHORT2FROMMP( mp1 );
			
			switch( control ) {
				case SAMPAPP_CONTENTS:
					if( notify == EN_KILLFOCUS )
					{
						int len;
						
						hwnd = WinWindowFromID(hw, SAMPAPP_ADDRESS);
						len = WinQueryWindowTextLength(hwnd);
						WinQueryWindowText(hwnd,len + 1,(PSZ) address);
						address[len + 1] = 0;
						
						hwnd = WinWindowFromID(hw, SAMPAPP_CONTENTS);
						len = WinQueryWindowTextLength(hwnd);
						WinQueryWindowText(hwnd,len + 1,(PSZ) contents);
						contents[len + 1] = 0;
						WinSetWindowText( WinWindowFromID( hw, SAMPAPP_ADDRESS ), (PSZ) "" );
						WinSetWindowText( WinWindowFromID( hw, SAMPAPP_CONTENTS ), (PSZ) "" );
						pasteIntoMesa( address, contents );
					}
						
					break;
				
				default:
					return WinDefDlgProc( hw, msg, mp1, mp2 );		
			}	// end of control...
		
		}	// end of WM_CONTROL section;
		break;
			
	case WM_TIMER:
		walkRandom();
		stubToMesa();
		// now, refresh my display...
		WinSendMsg( hw, MEM_UPDATESCREEN, NULL, NULL );
		break;
		
	case WM_HITTEST:
		MyMesa -> setHitPoint(SHORT1FROMMP(mp1),SHORT2FROMMP(mp1));
		return WinDefDlgProc( hw, msg, mp1, mp2 );
		
		
	// sent to update the screen from the variables...
	case MEM_UPDATESCREEN:
		updateScreenVals( hw );
		break;
		
	default:
		return WinDefDlgProc( hw, msg, mp1, mp2 );
	}	// the outer-switch statement
	
	return 0;
}

// actual main loop
//

int main(int argc,char *argv[])
{
	HMQ	hmq;
	HAB	theHAB;
	int	ret = 0;
	int enable;
	
	theHAB = WinInitialize(0);
	hmq = WinCreateMsgQueue(theHAB,256);
	
	// initialize the function parser
	MGController :: setupFuncs();
	
	// create a Mesa Controller
	MyMesa = new MSampleController("None",enable,theHAB,1,0);
	
	// set it up
	MyMesa -> setUp();
	
	// load AddIn's
	MyMesa -> setupAddIns();

   
	loadStocks();
	WinDlgBox(HWND_DESKTOP,HWND_DESKTOP, sampProc, 0, IDD_MYAPP, 0 );
	
	theView -> cleanUp();
	delete theView;
	
	WinDestroyMsgQueue(hmq);
	releaseStocks();
    
	// clean up the controller
	MyMesa -> cleanUp();
	
	// and make it go away
	delete MyMesa;
	
	// wait for threads to end
	DosSleep(750);
	
	WinTerminate(theHAB);
	return ret;
}

void loadStocks()
{
	// build an array of 5 stock names and prices...
	int i;
	
	for( i = 0; i <5; i++ )
		stockNames[ i ] = (char *)malloc( 32 * sizeof( char ));	

	strcpy( stockNames[ 0 ], "HOPII" );
	strcpy( stockNames[ 1 ], "STONE" );
	strcpy( stockNames[ 2 ], "MESAC" );
	strcpy( stockNames[ 3 ], "CARGZ" );
	strcpy( stockNames[ 4 ], "ARCSD" );
	
	prices[ 0 ] = 20.0;
	prices[ 1 ] = 32.2;
	prices[ 2 ] = 4.5;
	prices[ 3 ] = 102.71;
	prices[ 4 ] = 43.02;
}	

void releaseStocks()
{
	int i;
	
	for( i =0; i <5; i++ )
		free( stockNames[ i ] );
	
}

void updateScreenVals( HWND hw )
{
	int	i;
	char cBuf[ 128 ];
	
	// only count 4 because I haven't re-written the UI piece...
	for( i=0; i <4; i++ )
	{
		WinSetWindowText(WinWindowFromID(hw,SAMPAPP_STOCK1 +i),stockNames[i] );
		sprintf( cBuf, "%.2f", prices[ i ] );
		WinSetWindowText(WinWindowFromID(hw,SAMPAPP_PRICE1 +i),cBuf);
	}
}

void walkRandom()
{
	int i;
	float rn;
	
	
	for( i = 0; i<5; i++ )
	{
		rn = rand();
		rn /= RAND_MAX;
		rn -= 0.5;
		prices[ i ] = prices[ i ] + ( prices[ i ]/100 * rn );
	}
}

void stubToMesa()
{
	// this is the code that would take the four new values, and send them
	// to the Mesa model.
	int i;
	
	for (i = 0; i < 5; i++)
	{
		setRTFValue("BID",stockNames[i],prices[i]);
	}
	
	return;
}

void pasteIntoMesa( char *ad, char *str )
{
	// this is the code that will take an address string and value string,
	// and pass them to the model for evaluation/storage.
	MAddress adr,base;
	MException me;
	int len;
	
	base.set(0,0,0);
	
	if (theModel -> isAddress(ad,&base,&adr,len))
	{
		theModel -> setCellToString(&adr,str,0,&me,NULL);
	}
	
	return;
}
