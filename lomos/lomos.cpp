#define INCL_WIN
#define INCL_DOS
#include <os2.h>

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include "loandet.h"
#include "lomos.h"
#include "sampcont.h"

#define WM_NEW WM_USER
#define WM_OPENFILE WM_USER+1


MSampleController *MyMesa;
Loan * currloan;

// the icon stuck in the dlgs upper corner and displayed when minimized
HPOINTER prtIcon;

// this updates all of the fields in the window.  Ideally, when something
// changed, we'd just update what changed, but this is easier to deal with
void updateWindow(HWND hw,Loan * theLoan)
{
   char *str;
   int listidx;

   str=theLoan->LoanID();
   WinSetWindowText(WinWindowFromID(hw,DID_LOANID),str);
   delete str;

   str=theLoan->AppDate();
   WinSetWindowText(WinWindowFromID(hw,DID_APPDATE),str);
   delete str;

   str=theLoan->RepID();
   WinSetWindowText(WinWindowFromID(hw,DID_REP),str);
   delete str;

   str=theLoan->Name();
   WinSetWindowText(WinWindowFromID(hw,DID_APPNAME),str);
   delete str;

   str=theLoan->SSNo();
   WinSetWindowText(WinWindowFromID(hw,DID_SSNO),str);
   delete str;

   str=theLoan->Type();
   listidx = (int)WinSendDlgItemMsg(hw,DID_TYPE,
                                       LM_SEARCHSTRING,(MPARAM)NULL,str);
   WinSendDlgItemMsg(hw, DID_TYPE, 
                         LM_SETTOPINDEX, (MPARAM)listidx, (MPARAM)NULL);
   delete str;

   str=theLoan->Amount();
   WinSetWindowText(WinWindowFromID(hw,DID_AMOUNT),str);
   delete str;

   str=theLoan->Rate();
   WinSetWindowText(WinWindowFromID(hw,DID_RATE),str);
   delete str;

   str=theLoan->StDate();
   WinSetWindowText(WinWindowFromID(hw,DID_STDATE),str);
   delete str;

   str=theLoan->Duration();
   WinSetWindowText(WinWindowFromID(hw,DID_DURATION),str);
   delete str;

   str=theLoan->Periodicity();
   listidx = (int)WinSendDlgItemMsg(hw,DID_PERIODICITY,
                                       LM_SEARCHSTRING,(MPARAM)NULL,str);
   WinSendDlgItemMsg(hw, DID_PERIODICITY,
                         LM_SETTOPINDEX, (MPARAM)listidx, (MPARAM)NULL);
   delete str;

  }


// this is the window procedure that handles the loan
MRESULT EXPENTRY LoanProc(HWND hw,ULONG msg,MPARAM mp1,MPARAM mp2)
{
   // the pointer to the loan is stored in the first window ULONG
   // so we'll query that first thing
   Loan *theLoan=(Loan *) WinQueryWindowULong(hw,QWL_USER);
   char buffer[10000];
   char buffer2[1000];
   char *ptr;
   int select;

   switch (msg) {
   case WM_INITDLG:
         WinSendDlgItemMsg(hw,DID_TYPE,
                           LM_INSERTITEM,(MPARAM)LIT_END,"Student");
         WinSendDlgItemMsg(hw,DID_TYPE,
                           LM_INSERTITEM,(MPARAM)LIT_END,"Personal");
         WinSendDlgItemMsg(hw,DID_TYPE,
                           LM_INSERTITEM,(MPARAM)LIT_END,"Business");
         WinSendDlgItemMsg(hw,DID_PERIODICITY,
                           LM_INSERTITEM,(MPARAM)LIT_END,"Weekly");
         WinSendDlgItemMsg(hw,DID_PERIODICITY,
                           LM_INSERTITEM,(MPARAM)LIT_END,"Monthly");
         break;
   case WM_NEW:
      // we're creating a new Loan so we'll just new it without a file name
          theLoan=new Loan(hw);
      // set the first user ULONG to theLoan
          WinSetWindowULong(hw,QWL_USER,(ULONG)theLoan);
      // update the window to reflect the new values
          updateWindow(hw,theLoan);
          break;
   case WM_OPENFILE:
          {
         // for this, we'll pop up a standard dialog box asking for the filename
            FILEDLG fdg;
            char *types[2]={"Mesa Workbook File",NULL};
            char *type="Mesa Workbook File";

            memset(&fdg,0,sizeof(FILEDLG));
            fdg.cbSize=sizeof(FILEDLG);
            fdg.fl=FDS_CENTER | FDS_OPEN_DIALOG;
            fdg.pszIType = ( PSZ )type;
            fdg.papszITypeList = ( PAPSZ )types;
            WinFileDlg(HWND_DESKTOP,hw,&fdg);
            if(fdg.lReturn == DID_OK) {
               // create a new loan and have it load it's info from the selected file
               theLoan=new Loan(fdg.szFullFile,hw);
               // set the window ULONG to the PO
               WinSetWindowULong(hw,QWL_USER,(ULONG)theLoan);
               // update the window to reflect the new values
               updateWindow(hw,theLoan);
            } else WinDismissDlg(hw,DID_CANCEL);
          }
      break;
   
   case WM_CONTROL:
     switch (SHORT1FROMMP(mp1)) {
     case DID_LOANID:
          if (SHORT2FROMMP(mp1) == EN_KILLFOCUS) {
             WinQueryDlgItemText(hw,DID_LOANID,sizeof(buffer),buffer);
             theLoan->setLoanID(buffer);
          } /* endif */
        break;
     case DID_APPDATE:
          if (SHORT2FROMMP(mp1) == EN_KILLFOCUS) {
             WinQueryDlgItemText(hw,DID_APPDATE,sizeof(buffer),buffer);
             theLoan->setAppDate(buffer);
             ptr=theLoan->AppDate();
             WinSetWindowText(WinWindowFromID(hw,DID_APPDATE),ptr);
             delete ptr;
           } /* endif */
        break;
     case DID_REP:
          if (SHORT2FROMMP(mp1) == EN_KILLFOCUS) {
             WinQueryDlgItemText(hw,DID_REP,sizeof(buffer),buffer);
             theLoan->setRepID(buffer);
          } /* endif */
        break;
     case DID_APPNAME:
          if (SHORT2FROMMP(mp1) == EN_KILLFOCUS) {
             WinQueryDlgItemText(hw,DID_APPNAME,sizeof(buffer),buffer);
             theLoan->setName(buffer);
          } /* endif */
        break;
     case DID_SSNO:
          if (SHORT2FROMMP(mp1) == EN_KILLFOCUS) {
             WinQueryDlgItemText(hw,DID_SSNO,sizeof(buffer),buffer);
             theLoan->setSSNo(buffer);
          } /* endif */
        break;
     case DID_TYPE:
         if (SHORT2FROMMP(mp1) == LN_ENTER) {
            select=(int)WinSendDlgItemMsg(hw,DID_TYPE,LM_QUERYSELECTION,(MPARAM)NULL,0L);
            WinSendDlgItemMsg(hw,DID_TYPE,LM_QUERYITEMTEXT,MPFROM2SHORT(select,sizeof(buffer)),buffer);
            theLoan->setType(buffer);
         }
         break;
     case DID_AMOUNT:
          if (SHORT2FROMMP(mp1) == EN_KILLFOCUS) {
             WinQueryDlgItemText(hw,DID_AMOUNT,sizeof(buffer),buffer);
             theLoan->setAmount(buffer);
             ptr=theLoan->Amount();
             WinSetWindowText(WinWindowFromID(hw,DID_AMOUNT),ptr);
             delete ptr;
          } /* endif */
        break;
     case DID_RATE:
          if (SHORT2FROMMP(mp1) == EN_KILLFOCUS) {
             WinQueryDlgItemText(hw,DID_RATE,sizeof(buffer),buffer);
             theLoan->setRate(buffer);
             ptr=theLoan->Rate();
             WinSetWindowText(WinWindowFromID(hw,DID_RATE),ptr);
             delete ptr;
          } /* endif */
        break;
     case DID_STDATE:
          if (SHORT2FROMMP(mp1) == EN_KILLFOCUS) {
             WinQueryDlgItemText(hw,DID_STDATE,sizeof(buffer),buffer);
             theLoan->setStDate(buffer);
             ptr=theLoan->StDate();
             WinSetWindowText(WinWindowFromID(hw,DID_STDATE),ptr);
             delete ptr;
           } /* endif */
        break;
     case DID_DURATION:
          if (SHORT2FROMMP(mp1) == EN_KILLFOCUS) {
             WinQueryDlgItemText(hw,DID_DURATION,sizeof(buffer),buffer);
             theLoan->setDuration(buffer);
          } /* endif */
        break;
     case DID_PERIODICITY:
         if (SHORT2FROMMP(mp1) == LN_ENTER) {
            select=(int)WinSendDlgItemMsg(hw,DID_PERIODICITY,LM_QUERYSELECTION,(MPARAM)NULL,0L);
            WinSendDlgItemMsg(hw,DID_PERIODICITY,LM_QUERYITEMTEXT,MPFROM2SHORT(select,sizeof(buffer)),buffer);
            theLoan->setPeriodicity(buffer);
         }
         break;

   }
   case WM_COMMAND:
      switch (LOUSHORT(mp1)) {
      case DID_OK:
         ptr=theLoan->fileName();
         if (strcmp(ptr,"")==0) {
            FILEDLG fdg;
            memset(&fdg,0,sizeof(FILEDLG));
            fdg.cbSize=sizeof(FILEDLG);
            fdg.fl=FDS_CENTER | FDS_SAVEAS_DIALOG;
            WinFileDlg(HWND_DESKTOP,hw,&fdg);
            if(fdg.lReturn == DID_OK) {
               theLoan->setFileName(fdg.szFullFile);
            }
            else
               break;
         }
         delete ptr;
         theLoan->save();
         delete theLoan;
         WinDismissDlg(hw,DID_OK);
         break;
      case DID_CANCEL:
         delete theLoan;
         WinDismissDlg(hw,DID_CANCEL);
         break;
      case DID_SHEETVIEW:     
//         WinSetWindowPos(hw, 0, 6,35, 630, 400, SWP_SIZE);
         theLoan->displaySheetView(hw);
         updateWindow(hw,theLoan);
         break;
      default:
        return WinDefDlgProc(hw,msg,mp1,mp2);
      } 
      break;
   case LO_CONTENTSCHANGED:
   case LO_RESETVIEW:
   case LO_REDISPLAY:
      if (theLoan->isInSheetView()) {
         updateWindow(hw,theLoan);
      }
      break;
   default:
     return WinDefDlgProc(hw,msg,mp1,mp2);
   }
   return (MRESULT)FALSE;
}


// this procedure processes the messages sent to the main application window
// this includes menu items (which are usually just forwarded to the appropriate
// loan) and painting.
MRESULT EXPENTRY LoanAmortizationSysProc(HWND hw,ULONG msg,MPARAM mp1,MPARAM mp2)
{
   HWND hwnddlg;
	
   switch( msg ) {
   case WM_COMMAND:
     {
     switch( SHORT1FROMMP( mp1 ) ) {
     // the File->New PO  menu item.  It loads the dialog from the resources
     // and sends it the NEW po message to tell it to create a new PO
     case MID_FILE_NEW:
          hwnddlg=WinLoadDlg(hw,hw,LoanProc,NULL,IDD_LOAN_AMORTIZATION,0L);
           // send it the new message
          WinSendMsg(hwnddlg,WM_NEW,0L,0L);
          // show the window
          WinShowWindow(hwnddlg,TRUE);
        break;

     // the File->Open menu item.  It loads the dialog from the resources and
     // sends it the Open message to have it open an existing PO.
     case MID_FILE_OPEN:
          hwnddlg=WinLoadDlg(hw,hw,LoanProc,NULL,IDD_LOAN_AMORTIZATION,0L);
           // tell it to open a file
          WinSendMsg(hwnddlg,WM_OPENFILE,0L,0L);
          // show it
          WinShowWindow(hwnddlg,TRUE);
        break;

     case MID_FILE_SAVE:
        break;
     case MID_FILE_SAVEAS:
        break;
     case MID_FILE_PRINT:
        break;

      // close the window if the exit menu option is selected
     case MID_FILE_EXIT:
        WinPostMsg(hw,WM_CLOSE,0L,0L);
        break;
     default:
        return WinDefWindowProc( hw, msg, mp1, mp2 );
     }
		
   }  // the WM_COMMAND message
      break;


   // general window stuff
   case WM_ERASEBACKGROUND:
       return (MRESULT)TRUE;

    case WM_PAINT:
       {
          HPS hps=WinBeginPaint(hw,0,0);
          RECTL re;
          WinQueryWindowRect(hw,&re);
          WinFillRect(hps,&re,CLR_WHITE);
          WinEndPaint(hps);
          return 0L;
       }

	default:
		return WinDefWindowProc( hw, msg, mp1, mp2 );
	}	// the outer-switch statement
	
	return 0;
}



int main(int argc,char *argv[])
{
	HMQ	hmq;
   QMSG  qmsg;
	HAB	theHAB;
	int enable;
   HWND frame,client=NULLHANDLE;
   int rc=0;

   ULONG frameFlags = FCF_TITLEBAR | FCF_MENU | FCF_SYSMENU | FCF_SIZEBORDER |
                      FCF_MINMAX  | FCF_SHELLPOSITION | FCF_TASKLIST;
	
	theHAB = WinInitialize(0);
	hmq = WinCreateMsgQueue(theHAB,256);
   rc=WinRegisterClass(theHAB,"CLIENT",LoanAmortizationSysProc,0,0);
	
	// initialize the function parser
	MGController :: setupFuncs();
	
	// create a Mesa Controller
	MyMesa = new MSampleController("None",enable,theHAB,1);
	
	// set it up
	MyMesa -> setUp();
	
	// load AddIn's
	MyMesa -> setupAddIns();

   // create the frame window
   frame=WinCreateStdWindow(HWND_DESKTOP,WS_VISIBLE,&frameFlags,"CLIENT",
                     "Loan Amortization System",0,0,ID_APPNAME,
                     &client);

   // load the pointer used by the client windows
   prtIcon=WinLoadPointer(HWND_DESKTOP,NULL,1);

   // run the application
   while (WinGetMsg(theHAB,&qmsg,0,0,0)) {
         WinDispatchMsg(theHAB,&qmsg);
   } /* endwhile */

   //destroy the message queue when done
	WinDestroyMsgQueue(hmq);

	// clean up the controller
	MyMesa -> cleanUp();
	
	// and make it go away
//	delete MyMesa;
	
	// wait for threads to end
	DosSleep(750);
	
   // outa here!
	WinTerminate(theHAB);
}
