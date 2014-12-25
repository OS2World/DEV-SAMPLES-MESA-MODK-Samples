#define INCL_WIN
#define INCL_DOS
#include <os2.h>

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include "porder.hpp"
#include "posys.h"
#include "sampcont.h"

#define WM_NEW WM_USER
#define WM_OPENFILE WM_USER+1


MSampleController *MyMesa;
POrder * currentPo;

// the icon stuck in the dlgs upper corner and displayed when minimized
HPOINTER prtIcon;

// this procedure handles the add dialog.  When the OK button is pushed
// it queries the fields and calls the addItem method of the purchase order.
MRESULT EXPENTRY AddItemDlg(HWND hw,ULONG msg,MPARAM mp1, MPARAM mp2)
{
   char desc[200],cost[100],quant[100];

   switch (msg) {
   case WM_COMMAND:
     switch (SHORT1FROMMP(mp1)) {
     case DID_OK:
        WinQueryDlgItemText(hw,DID_DESCRIPTIONS,sizeof(desc),desc);
        WinQueryDlgItemText(hw,DID_COST,sizeof(cost),cost);
        WinQueryDlgItemText(hw,DID_QUANTITY,sizeof(quant),quant);
        currentPo->addItem(desc,cost,quant);
        WinDismissDlg(hw,DID_OK);
        break;
     case DID_CANCEL:
        WinDismissDlg(hw,DID_CANCEL);
        break;
      } /* endswitch */
      break;
   } /* endswitch */
   return WinDefDlgProc(hw,msg,mp1,mp2);
}



// this procedure queries the description of the currently selected item
// in the list box and then updates the cost, quanitity, and item total
// fields in the dialog by getting the information from the purchase order
void UpdateCosts(HWND hw, POrder *thePo, int id = 0)
{
   char buffer[300];
   char *str;
   int select;
   static int flag;

   if (flag) {
      return;
   }
   flag = 1;

   // get the id of the selected item
   select=(int)WinSendDlgItemMsg(hw,DID_DESCRIPTIONS,LM_QUERYSELECTION,(MPARAM)LIT_FIRST,0L);

   // query the text for the selected item
   WinSendDlgItemMsg(hw,DID_DESCRIPTIONS,LM_QUERYITEMTEXT,MPFROM2SHORT(select,sizeof(buffer)),buffer);

   // if there are no items in the listbox, it will return an empty string so
   // we'll disable all the appropriate entry fields and buttons and the leave
   if (strcmp(buffer,"")==0) {
      WinEnableWindow(WinWindowFromID(hw,DID_DELETEITEM),FALSE);
      WinEnableWindow(WinWindowFromID(hw,DID_COST),FALSE);
      WinEnableWindow(WinWindowFromID(hw,DID_QUANTITY),FALSE);
      return;
   } /* endif */

   // otherwise, we'll enable the windows, query the values, and then set the
   // text of each of the fields
   WinEnableWindow(WinWindowFromID(hw,DID_DELETEITEM),TRUE);
   WinEnableWindow(WinWindowFromID(hw,DID_COST),TRUE);
   WinEnableWindow(WinWindowFromID(hw,DID_QUANTITY),TRUE);

   if(id != DID_COST)
   {
     str=thePo->queryItemCost(buffer);
     WinSetWindowText(WinWindowFromID(hw,DID_COST),str);
     delete str;
   }

   if(id != DID_QUANTITY)
   {
     str=thePo->queryItemQuantity(buffer);
     WinSetWindowText(WinWindowFromID(hw,DID_QUANTITY),str);
     delete str;
   }

   str=thePo->queryItemTotal(buffer);
   WinSetWindowText(WinWindowFromID(hw,DID_ITEMTOTAL),str);
   delete str;

   str=thePo->SubTotal();
   WinSetWindowText(WinWindowFromID(hw,DID_SUBTOTAL),str);
   delete str;

   str=thePo->Total();
   WinSetWindowText(WinWindowFromID(hw,DID_TOTAL),str);
   delete str;

   flag = 0;
}

// this updates all of the fields in the window.  Ideally, when something
// changed, we'd just update what changed, but this is easier to deal with
void updateWindow(HWND hw,POrder * thePo)
{
   char *str;

   str=thePo->PONum();
   WinSetWindowText(WinWindowFromID(hw,DID_PONUM),str);
   delete str;

   str=thePo->Date();
   WinSetWindowText(WinWindowFromID(hw,DID_DATE),str);
   delete str;

   str=thePo->Initials();
   WinSetWindowText(WinWindowFromID(hw,DID_INITIALS),str);
   delete str;

   str=thePo->SubTotal();
   WinSetWindowText(WinWindowFromID(hw,DID_SUBTOTAL),str);
   delete str;

   str=thePo->Tax();
   WinSetWindowText(WinWindowFromID(hw,DID_TAX),str);
   delete str;

   str=thePo->Shipping();
   WinSetWindowText(WinWindowFromID(hw,DID_SHIPPING),str);
   delete str;

   str=thePo->Total();
   WinSetWindowText(WinWindowFromID(hw,DID_TOTAL),str);
   delete str;

   str=thePo->Comments();
   WinSetWindowText(WinWindowFromID(hw,DID_COMMENTS),str);
   delete str;

   str=thePo->Flags();
   WinSetWindowText(WinWindowFromID(hw,DID_FLAGS),str);
   delete str;

   WinSendMsg(WinWindowFromID(hw,DID_DESCRIPTIONS),LM_DELETEALL,0L,0L);
   WinEnableWindow(WinWindowFromID(hw,DID_DELETEITEM),FALSE);
   WinEnableWindow(WinWindowFromID(hw,DID_COST),FALSE);
   WinEnableWindow(WinWindowFromID(hw,DID_QUANTITY),FALSE);
   str=thePo->startEnumDescriptions();
   while (strcmp(str,"") != 0) {
         WinSendMsg(WinWindowFromID(hw,DID_DESCRIPTIONS),LM_INSERTITEM,(MPARAM)LIT_END,(MPARAM)str);
         WinEnableWindow(WinWindowFromID(hw,DID_DELETEITEM),TRUE);
         WinEnableWindow(WinWindowFromID(hw,DID_COST),TRUE);
         WinEnableWindow(WinWindowFromID(hw,DID_QUANTITY),TRUE);
         delete str;
         str=thePo->nextDescription();
   } /* end while */
   delete str;

   WinSendDlgItemMsg(hw,DID_DESCRIPTIONS,LM_SELECTITEM,(MPARAM)0,(MPARAM)TRUE);
}


// pops up the new item dialog box to allow the user to create new items
// when the item is added, it updates the entire window so that the right
// information is displayed
void NewItemProcedure(HWND hw, POrder  *thePo)
{
   currentPo=thePo;
   WinDlgBox(HWND_DESKTOP,hw,AddItemDlg,NULLHANDLE,IDD_NEWITEM,0L);
   updateWindow(hw,thePo);
}


//  This procedure pops up a message box verifing that the user really wants to
//  delete the selected item and then deletes the item if they really do
void DeleteItemProcedure(HWND hw, POrder *thePo)
{

   //query the item id
   int select=(int)WinSendDlgItemMsg(hw,DID_DESCRIPTIONS,
                           LM_QUERYSELECTION,(MPARAM)LIT_FIRST,0L);
   char desc[200];
   char buffer[400];

   // query the text of the selected item
   WinSendDlgItemMsg(hw,DID_DESCRIPTIONS,LM_QUERYITEMTEXT,
                           MPFROM2SHORT(select,sizeof(desc)),desc);

   // format the text for the message box
   sprintf(buffer,"Are you sure you want to delete item: %s",desc);

   // display the message box
   if (WinMessageBox(HWND_DESKTOP,hw,buffer,"Attention!",24,MB_YESNO | MB_ICONEXCLAMATION)==MBID_YES) {
      // if the use hit the YES button, have the PO delete the item
      thePo->deleteItem(desc);
   } /* endif */
   // nomatter what, update the window.  It really only needs to be done if something
   // was actually deleted, but it doesn't hurt
   UpdateCosts(hw,thePo);
   updateWindow(hw,thePo);
}

// this is the window procedure that handles the purchase order
MRESULT EXPENTRY POProc(HWND hw,ULONG msg,MPARAM mp1,MPARAM mp2)
{
   // the pointer to the purchase order is stored in the first window ULONG
   // so we'll query that first thing
   POrder *thePo=(POrder *) WinQueryWindowULong(hw,QWL_USER);
   char buffer[10000];
   char buffer2[1000];
   char *ptr;
   int select;

   switch (msg) {
   case WM_NEW:
      // we're creating a new PO so we'll just new it without a file name
          thePo=new POrder(hw);
      // set the first user ULONG to the po
          WinSetWindowULong(hw,QWL_USER,(ULONG)thePo);
      // update the window so it reflects the data in the sheet
          updateWindow(hw,thePo);
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
               // create a new PO and have it load it's info from the selected file
               thePo=new POrder(fdg.szFullFile,hw);
               // set the window ULONG to the PO
               WinSetWindowULong(hw,QWL_USER,(ULONG)thePo);
               // update the window to reflect the new values
               updateWindow(hw,thePo);
            } else WinDismissDlg(hw,DID_CANCEL);
          }
      break;
   case WM_CONTROL:
     switch (SHORT1FROMMP(mp1)) {
     case DID_DESCRIPTIONS:
          if (SHORT2FROMMP(mp1) == LN_SELECT) {
               UpdateCosts(hw,thePo);
          } /* endif */
        break;
     case DID_PONUM:
          if (SHORT2FROMMP(mp1) == EN_CHANGE) {
             WinQueryDlgItemText(hw,DID_PONUM,sizeof(buffer),buffer);
             thePo->setPONum(buffer);
          } /* endif */
        break;
     case DID_INITIALS:
          if (SHORT2FROMMP(mp1) == EN_CHANGE) {
             WinQueryDlgItemText(hw,DID_INITIALS,sizeof(buffer),buffer);
             thePo->setInitials(buffer);
          } /* endif */
        break;
     case DID_DATE:
          if (SHORT2FROMMP(mp1) == EN_CHANGE) {
             WinQueryDlgItemText(hw,DID_DATE,sizeof(buffer),buffer);
             thePo->setDate(buffer);
          } /* endif */
        break;
     case DID_COMMENTS:
          if (SHORT2FROMMP(mp1) == MLN_CHANGE) {
             WinQueryDlgItemText(hw,DID_COMMENTS,sizeof(buffer),buffer);
             thePo->setComments(buffer);
          } /* endif */
        break;
     case DID_SHIPPING:
          if (SHORT2FROMMP(mp1) == EN_CHANGE) {
             WinQueryDlgItemText(hw,DID_SHIPPING,sizeof(buffer),buffer);
             thePo->setShipping(buffer);
             DosSleep(100);
             WinSetWindowText(WinWindowFromID(hw,DID_TOTAL),thePo->Total());
           } /* endif */
        break;
     case DID_TAXRATE:
          if (SHORT2FROMMP(mp1) == EN_CHANGE) {
             WinQueryDlgItemText(hw,DID_TAXRATE,sizeof(buffer),buffer);
             thePo->setTaxRate(buffer);
             DosSleep(100);
             WinSetWindowText(WinWindowFromID(hw,DID_TOTAL),thePo->Total());
           } /* endif */
        break; 
     case DID_COST:
          if (SHORT2FROMMP(mp1) == EN_CHANGE) {
             WinQueryDlgItemText(hw,DID_COST,sizeof(buffer),buffer);
             select=(int)WinSendDlgItemMsg(hw,DID_DESCRIPTIONS,
                           LM_QUERYSELECTION,(MPARAM)LIT_FIRST,0L);
             WinSendDlgItemMsg(hw,DID_DESCRIPTIONS,LM_QUERYITEMTEXT,
                           MPFROM2SHORT(select,sizeof(buffer2)),buffer2);
             thePo->setItemCost(buffer2,buffer);
             UpdateCosts(hw,thePo, DID_COST);
          } /* endif */
        break;
     case DID_QUANTITY:
          if (SHORT2FROMMP(mp1) == EN_CHANGE) {
             select=(int)WinSendDlgItemMsg(hw,DID_DESCRIPTIONS,
                           LM_QUERYSELECTION,(MPARAM)LIT_FIRST,0L);
             WinSendDlgItemMsg(hw,DID_DESCRIPTIONS,LM_QUERYITEMTEXT,
                           MPFROM2SHORT(select,sizeof(buffer2)),buffer2);
             WinQueryDlgItemText(hw,DID_QUANTITY,sizeof(buffer),buffer);
             thePo->setItemQuantity(buffer2,buffer);
             UpdateCosts(hw,thePo,DID_QUANTITY);
            } /* endif */
        break;
     }
     break;
   case WM_COMMAND:
      switch (LOUSHORT(mp1)) {
      case DID_OK:
         ptr=thePo->fileName();
         if (strcmp(ptr,"")==0) {
            FILEDLG fdg;
            memset(&fdg,0,sizeof(FILEDLG));
            fdg.cbSize=sizeof(FILEDLG);
            fdg.fl=FDS_CENTER | FDS_SAVEAS_DIALOG;
            WinFileDlg(HWND_DESKTOP,hw,&fdg);
            if(fdg.lReturn == DID_OK) {
               thePo->setFileName(fdg.szFullFile);
            }
         } /* endif */
         delete ptr;
         thePo->save();
         delete thePo;
         WinDismissDlg(hw,DID_OK);
         break;
      case DID_CANCEL:
         delete thePo;
         WinDismissDlg(hw,DID_CANCEL);
         break;
      case DID_TEST:
          updateWindow(hw,thePo);
         break;
      case DID_NEWITEM:
           NewItemProcedure(hw,thePo);
         break;
      case DID_DELETEITEM:
           DeleteItemProcedure(hw,thePo);
         break;
      case DID_SHEETVIEW:
         thePo->displaySheetView(hw);
         updateWindow(hw,thePo);
         break;
      default:
        return WinDefDlgProc(hw,msg,mp1,mp2);
      } /* endswitch */
      break;
   case PO_CONTENTSCHANGED:
   case PO_RESETVIEW:
   case PO_REDISPLAY:
      if (thePo->isInSheetView()) {
         updateWindow(hw,thePo);
      } /* endif */
      break;
   default:
     return WinDefDlgProc(hw,msg,mp1,mp2);
   } /* endswitch */
   return (MRESULT)FALSE;
}


// this procedure processes the messages sent to the main application window
// this includes menu items (which are usually just forwarded to the appropriate
// purchase order) and painting.
MRESULT EXPENTRY PurchaseOrderSysProc(HWND hw,ULONG msg,MPARAM mp1,MPARAM mp2)
{
   HWND hwnddlg;
	
   switch( msg ) {
   case WM_COMMAND:
     {
     switch( SHORT1FROMMP( mp1 ) ) {
     // the File->New PO  menu item.  It loads the dialog from the resources
     // and sends it the NEW po message to tell it to create a new PO
     case MID_FILE_NEW:
          hwnddlg=WinLoadDlg(hw,hw,&POProc,NULL,IDD_PURCHASE_ORDER,0L);
          // set the icon
          WinSendMsg(hwnddlg,WM_SETICON,(MPARAM)prtIcon,0L);
          // send it the new message
          WinSendMsg(hwnddlg,WM_NEW,0L,0L);
          // show the window
          WinShowWindow(hwnddlg,TRUE);
        break;

     // the File->Open menu item.  It loads the dialog from the resources and
     // sends it the Open message to have it open an existing PO.
     case MID_FILE_OPEN:
          hwnddlg=WinLoadDlg(hw,hw,&POProc,NULL,IDD_PURCHASE_ORDER,0L);
          // set the icon
          WinSendMsg(hwnddlg,WM_SETICON,(MPARAM)prtIcon,0L);
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


   ULONG frameFlags = FCF_TITLEBAR | FCF_SYSMENU | FCF_SIZEBORDER | FCF_ICON |
                      FCF_MINMAX | FCF_MENU | FCF_SHELLPOSITION | FCF_TASKLIST;
	
	theHAB = WinInitialize(0);
	hmq = WinCreateMsgQueue(theHAB,256);
   rc=WinRegisterClass(theHAB,"CLIENT",PurchaseOrderSysProc,0,0);
	
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
                     "Purchase Ordering System",0,0,ID_APPNAME,
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
	delete MyMesa;
	
	// wait for threads to end
	DosSleep(750);
	
   // outa here!
	WinTerminate(theHAB);
}
