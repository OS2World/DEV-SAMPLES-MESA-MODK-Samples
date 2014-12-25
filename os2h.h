/**************************************************************************
 *                                                                        *
 *                                                                        *
 *          This code is copyright (c) 1994 & 1995                        *
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
    this file includes the OS/2 header files (all of them)

    2-12-94 dpp
*/

#ifndef _MH_OS2_INCLUDED

#define _MH_OS2_INCLUDED

#ifdef M2Z

// let's call HDC's OS2_HDC's because NT calls HPS's HDC's
// #define HDC OS2_HDC

#define INCL_WIN
#define INCL_WINATOM
#define INCL_GPI
#define INCL_DOS
#define INCL_ERRORS
#define INCL_DEV
#define INCL_SPL
#define INCL_RXFUNC
#define INCL_RXARI
#define INCL_SPLDOSPRINT
#define INCL_DOSPROCESS

extern "C"
{
#include <os2.h>
#include <rexxsaa.h>
}

// comment out this line for the commercial build
// Dave, could you add /DMESASEBUGMODE to the icc.exe line of your makefile instead
// of defineing it here
//#define MESADEBUGMODE

// do we want to debug locks?
#ifdef	MESADEBUGMODE
//#define DEBUGLOCKS
#endif

// do we want to debug DDE?
#ifdef MESADEBUGMODE
// #define DEBUGDDE
#endif

#ifdef MESADEBUGMODE
#define ERRORMGR
#endif

#ifdef ERRORMGR
#include <errormgr.h>
#endif

#define HANDLE void *

typedef HPS MGraphPtr;

#define MWinReleasePS(a,b)				WinReleasePS(b)
#define GetMenuItemCount(menu)			((int) WinSendMsg(menu,MM_QUERYITEMCOUNT,0,0))
#define GetMenuItemID(menu,cnt)			((int) WinSendMsg(menu,MM_ITEMIDFROMPOSITION,MPFROM2SHORT(cnt,0),0))

// defines for all the OS/2 defines into Mesa-generic ones...
#define	MESA_SCROLL_LINE_LEFT	SB_LINELEFT
#define	MESA_SCROLL_LINE_RIGHT	SB_LINERIGHT
#define	MESA_SCROLL_SLIDERTRACK	SB_SLIDERTRACK
#define	MESA_SCROLL_PAGE_LEFT	SB_PAGELEFT
#define	MESA_SCROLL_PAGE_RIGHT	SB_PAGERIGHT
#define MESA_SCROLL_SLIDERPOS	SB_SLIDERPOSITION

#define	MESA_SCROLL_LINE_UP		SB_LINEUP
#define	MESA_SCROLL_LINE_DOWN	SB_LINEDOWN
#define	MESA_SCROLL_PAGE_UP		SB_PAGEUP
#define	MESA_SCROLL_PAGE_DOWN	SB_PAGEDOWN

#define	MESA_SYSTEM_MINIMZE		SC_MINIMIZE
#define	MESA_SYSTEM_MAXIMIZE		SC_MAXIMIZE
#define	MESA_SYSTEM_RESTORE		SC_RESTORE

// system id's for the scroll-bar buttons...
#define	MSCROLL_LEFT_UP			SBMP_SBLFARROW
#define	MSCROLL_LEFT_DOWN			SBMP_SBLFARROWDEP
#define	MSCROLL_LEFT_DIS			SBMP_SBLFARROWDIS
#define	MSCROLL_RIGHT_UP			SBMP_SBRGARROW
#define	MSCROLL_RIGHT_DOWN		SBMP_SBRGARROWDEP
#define	MSCROLL_RIGHT_DIS			SBMP_SBRGARROWDIS

// window position adjustments
#define	MESA_WINDOW_MINIMIZED	0x01
#define	MESA_WINDOW_MAXIMIZED	0x02
#define	MESA_WINDOW_RESTORED	0x04
#define	MESA_WINDOW_ACTIVATE	0x08
#define	MESA_WINDOW_DEACTIVATE	0x10

// ifdef M2Z
#endif

#ifdef M2NT


#include <windows.h>
#include <windowsx.h>

// HPS's are really HDC's
#define HPS 				HDC

#define MGraphPtr 			HPS

typedef WINDOWPOS * PSWP;

#define MRESULT				LRESULT
#define MPARAM				int
#define PFNWP				WNDPROC
#define PHWND				HWND *
#define HAB					HANDLE
#define HMQ					HANDLE
#define SWP					WINDOWPOS
#define POINTL				POINT
#define PPVOID				void *
#define DATETIME			SYSTEMTIME
#define RECTL				RECT
#define BM_QUERYCHECK		BM_GETCHECK
#define QMSG				MSG
#define SWP_ZORDER			0
#define SWP_ACTIVATE		0
#define SWP_SHOW			0
#define SWP_MOVE			0
#define SWP_SIZE			0
#define	SB_SLIDERTRACK		SB_THUMBTRACK
#define SBM_QUERYPOS		SBM_GETPOS
#define SBM_QUERYRANGE		SBM_GETRANGE
#define MATRIXLF			XFORM
#define FONTMETRICS			TEXTMETRIC

// keyboard virtual key remapping
#define VK_ESC				VK_ESCAPE
#define VK_BACKTAB			VK_BACK
#define VK_ALT				VK_MENU
#define VK_CTRL				VK_CONTROL
#define VK_PAGEDOWN			VK_NEXT
#define VK_PAGEUP			VK_PRIOR
#define VK_ENTER			VK_RETURN
#define VK_NEWLINE			VK_EXECUTE

// Message mapping
#define WM_BUTTON1DOWN		WM_LBUTTONDOWN

// THESE are total Hacks
// FIXMENT
#define KC_SHIFT			MK_SHIFT
#define KC_CTRL				MK_CONTROL
#define KC_ALT				0
#define KC_CHAR				0
#define KC_KEYUP			0
#define KC_VIRTUALKEY		0
#define WM_HELP				0

// FIXMENT
#define SPBM_QUERYVALUE		10
#define SPBM_SETCURRENTVALUE		10
#define SPBQ_UPDATEIFVALID	10
#define LM_QUERYSELECTION	10
#define LIT_FIRST			10
#define LM_SELECTITEM		10
#define PP_FOREGROUNDCOLOR	1
#define PP_BACKGROUNDCOLOR	2
#define PP_FONTNAMESIZE		3

// some functions
#define WinGetPS(x) 							GetDC(x)
#define WinOpenClipbrd(x)						OpenClipboard(x)
#define WinSetFocus(x,y) 						SetFocus(y)
#define WinIsWindow(x,y) 						IsWindow(y)
#define WinSetWindowULong(x,y,z) 				SetWindowLong((x),(y),(z))
#define WinQueryWindowULong(x,y) 				GetWindowLong((x),(y))
#define DosDelete(x) 							DeleteFile(x)
#define DosMove(x,y) 							MoveFile(x,y)
#define WinPostMsg(a,b,c,d) 					PostMessage(a,b,c,d)
#define WinSendMsg(a,b,c,d) 					SendMessage(a,b,c,d)
#define WinQueryWindowPos(a,b)					GetWindowPlacement(a,b)
#define WinInvalidateRect(a,b,c)				InvalidateRect(a,b,c)
#define WinQueryWindowTextLength(a)				GetWindowTextLength(a)
#define WinQueryWindowText(a,b,c)				GetWindowText(a,c,b)
#define WinSetWindowText(a,b)					SetWindowText(a,b)
#define DosBeep(a,b)							Beep(a,b)
#define WinUpdateWindow(a)						UpdateWindow(a)
#define WinPeekMsg(a,b,c,d,e,f)					PeekMessage(b,c,d,e,f)
#define WinGetMsg(a,b,c,d,e)					GetMessage(b,c,d,e)
#define WinWindowFromID(a,b)					GetDlgItem(a,b)
#define WinDestroyWindow(a)						DestroyWindow(a)
#define WinSetCapture(a,b)						SetCapture(b)
#define MWinReleasePS(a,b)						ReleaseDC(a,b)
#define WinSetWindowPos(a,b,c,d,e,f,g)			SetWindowPos(a,b,c,d,e,f,g)
#define GpiSetModelTransformMatrix(a,b,c,d)		SetWorldTransform(a,c)
#define GpiQueryModelTransformMatrix(a,b,c)		GetWorldTransform(a,c)
#define GpiSavePS(a)							SaveDC(a)
#define GpiRestorePS(a,b)						RestoreDC(a,b)
#define WinMapWindowPoints(a,b,c,d)				MapWindowPoints(a,b,c,d)
#define WinDefWindowProc(a,b,c,d)				DefWindowProc(a,b,c,d)
#define GpiBeginPath(a,b)						BeginPath(a)
#define GpiEndPath(a)							EndPath(a)
#define GpiStrokePath(a,b,c)					StrokePath(a)
#define GpiFillPath(a,b,c)						FillPath(a)
#define GpiQueryFontMetrics(a,b,c)				GetTextMetrics(a,c)

// defines for all the OS/2 defines into Mesa-generic ones...
#define	MESA_SCROLL_LINE_LEFT	SB_LINELEFT
#define	MESA_SCROLL_LINE_RIGHT	SB_LINERIGHT
#define	MESA_SCROLL_SLIDERTRACK	SB_SLIDERTRACK
#define	MESA_SCROLL_PAGE_LEFT	SB_PAGELEFT
#define	MESA_SCROLL_PAGE_RIGHT	SB_PAGERIGHT

#define	MESA_SCROLL_LINE_UP		SB_LINEUP
#define	MESA_SCROLL_LINE_DOWN	SB_LINEDOWN
#define	MESA_SCROLL_PAGE_UP		SB_PAGEUP
#define	MESA_SCROLL_PAGE_DOWN	SB_PAGEDOWN

#define	MESA_SYSTEM_MINIMZE		SC_MINIMIZE
#define	MESA_SYSTEM_MAXIMIZE		SC_MAXIMIZE
#define	MESA_SYSTEM_RESTORE		SC_RESTORE


inline PFNWP WinSubclassWindow(HWND hw,PFNWP wp)
{
	PFNWP old;
	
	old = (PFNWP) GetWindowLong(hw,GWL_WNDPROC);
	SetWindowLong(hw,GWL_WNDPROC,(int) wp);
	return old;
}

// FIXMENT - stub functions
extern HWND WinLoadMenu(HWND,int,int);

#define SHORT1FROMMP(a) 	HIWORD(a)
#define SHORT2FROMMP(a)		LOWORD(a)
#define LOUSHORT(a)			LOWORD(a)
#define MPFROM2SHORT(a,b) 	MAKELONG(a,b)
#define MPFROMLONG(a)		((int) (a))
// ifdef M2NT
#endif

// do some header file stuff to make the Mac work more like OS/2
// 95-07-10 dpp
#ifdef M2MAC
#pragma once

class LView;

#define ULONG unsigned long
typedef LView * HWND;
// #define HWND LView *
#define MGraphPtr GrafPtr

#include <LApplication.h>
#include <LWindow.h>
#include <PP_Messages.h>
#include <PP_Resources.h>
#include <URegistrar.h>
#include <PPobClasses.h>
#include <LGrowZone.h>
#include <UMemoryMgr.h>
#include <UPowerTools.h>
#include <LEditField.h>

// the scroll functionality -- FIXMEMAC
#define	MESA_SCROLL_LINE_LEFT	1
#define	MESA_SCROLL_LINE_RIGHT	2
#define	MESA_SCROLL_SLIDERTRACK	3
#define	MESA_SCROLL_PAGE_LEFT	4
#define	MESA_SCROLL_PAGE_RIGHT	5

#define	MESA_SCROLL_LINE_UP		1
#define	MESA_SCROLL_LINE_DOWN	2
#define	MESA_SCROLL_PAGE_UP		4
#define	MESA_SCROLL_PAGE_DOWN	5

#define	MESA_SYSTEM_MINIMZE		1
#define	MESA_SYSTEM_MAXIMIZE	2
#define	MESA_SYSTEM_RESTORE		3

// FIXMEMAC
#define KC_SHIFT			1
#define KC_CTRL				2
#define KC_ALT				0
#define KC_CHAR				0
#define KC_KEYUP			0
#define KC_VIRTUALKEY		0
#define WM_HELP				0

#define theHAB				0
#define TheMesaHAB			0
#define DosBeep(a,b)

//#ifdef M2MAC

#endif

// OS/2 included

#endif


