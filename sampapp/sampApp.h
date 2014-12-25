/*
Sample Mesa DOK - Mesa 2 for OS/2 application
Copyright 1995, Athena Design, Inc.

*/

#ifndef	_SAMPAPP_H
#define	_SAMPAPP_H

#define INCL_WIN
#define INCL_GPI
#define INCL_DOS
#define INCL_ERRORS
#define INCL_DEV
#define INCL_SPL
#define INCL_RXFUNC
#define INCL_RXARI
#define INCL_SPLDOSPRINT
#define INCL_DOSPROCESS

#include "os2.h"

#define IDD_MYAPP				1
#define DID_RANDOM			1000
#define DID_ENDWALK			DID_RANDOM + 1
#define DID_EXIT			DID_RANDOM + 2
#define DID_LOADTEXT		DID_RANDOM + 3
#define SAMPAPP_BASE			512
#define SAMPAPP_ADDRESS		SAMPAPP_BASE + 0
#define SAMPAPP_CONTENTS	SAMPAPP_BASE + 1
#define SAMPAPP_STOCK1		SAMPAPP_BASE +2
#define SAMPAPP_STOCK2		SAMPAPP_BASE +3
#define SAMPAPP_STOCK3		SAMPAPP_BASE +4
#define SAMPAPP_STOCK4		SAMPAPP_BASE +5
#define SAMPAPP_PRICE1		SAMPAPP_BASE +6
#define SAMPAPP_PRICE2		SAMPAPP_BASE +7
#define SAMPAPP_PRICE3		SAMPAPP_BASE +8
#define SAMPAPP_PRICE4		SAMPAPP_BASE +9
#define SAMPAPP_VIEW			SAMPAPP_BASE +10


// timer identifier
#define	ID_TIMER			1

// beginning of user-defined messages

#define	MEM_UPDATESCREEN	(WM_USER )

// function prototypes
void loadStocks();
void releaseStocks();
void updateScreenVals( HWND );
void walkRandom();
void stubToMesa();
void pasteIntoMesa( char *, char * );

#endif	// sampApp
