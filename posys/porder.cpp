
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include "mmemory.h"
#include "range.h"
#include "mesamod.h"
#include "sheetv.h"
#include "sampcont.h"
#include "posys.h"
#include "porder.hpp"
#include "interest.h"
#include "editview.h"

extern MSampleController *MyMesa;
MMesaModel * currentModel;



// we can't send strings like "$2,150.23" into a cell so we need to
// strip out the '$' and the ',' to make it "2150.23".  this procedure
// accomplishes that
void stripDollarAndCommas(char *str)
{
   char *str2 = new char[strlen(str)+1];
   int x=0,y=0;

   for (x=0;x < strlen(str)+1 ; x++) {
      if ((str[x] != '$') && (str[x] != ',') &&(str[x] != ' ')) {
         str2[y]=str[x];
         y++;
      } /* endif */
   } /* endfor */
   strcpy(str,str2);
   delete str2;
}


// this is a major hack.  Right now, any cell that has formattings set
// when the value is queried, it comes back with an extra space at the
// end.  This function strips the space to make it work correctly.
void stripEndingSpace(char *str)
{
   if (str[MStrLen(str)-1] == ' ') {
      str[MStrLen(str)-1]='\0';
   } /* endif */
}



// as mentioned in porder.hpp, the POInterest methods mostly just post messages
// to the window so it knows what is going on in it's model
POInterest::POInterest(HWND hw) : MInterest()
{
   theWin=hw;
}

POInterest::~POInterest()
{
}

void POInterest::redisplay(MChange *mc)
{
   WinPostMsg(theWin,PO_REDISPLAY,(MPARAM)mc,0L);
}
void POInterest::changedSize(MChange *mc)
{
   WinPostMsg(theWin,PO_CHANGEDSIZE,(MPARAM)mc,0L);
}
void POInterest::formatsChanged(MChange *mc)
{
   WinPostMsg(theWin,PO_FORMATSCHANGED,(MPARAM)mc,0L);
}
void POInterest::contentsChanged(MChange *mc)
{
   WinPostMsg(theWin,PO_CONTENTSCHANGED,(MPARAM)mc,0L);
}
void POInterest::resetView(MChange *mc)
{
   WinPostMsg(theWin,PO_RESETVIEW,(MPARAM)mc,0L);
}


// this function sets up a new PO by formatting the top layer of the
// model and inserting the appropriate titles and formulas
void SetupNewPO(MMesaModel * theModel)
{
	MRange ra;
	MFormat fo;
	MException me;
	MAddress ad,ad2;

      fo.init();
		fo.setMergePrecision(1);
		fo.setMergeFormat(1);
      fo.setFormat(generalAlignment);

      ad.set(0,0,0);
      ad2.set(31,13,0);
      ra.init();
      ra.set(&ad,&ad2);
  		theModel -> setRangeToFormat(&ra,&fo,defaultAction,NULL,&me);

		fo.setFormat(currencyTypeFormat |currencySubtypeFormat | 2);

      ad.set(1,4,0);
      ad2.set(31,4,0);
      ra.set(&ad,&ad2);
  		theModel -> setRangeToFormat(&ra,&fo,defaultAction,NULL,&me);

      ad.set(1,6,0);
      ad2.set(31,6,0);
      ra.set(&ad,&ad2);
  		theModel -> setRangeToFormat(&ra,&fo,defaultAction,NULL,&me);

      ad.set(1,7,0);
      ra.set(&ad,&ad);
  		theModel -> setRangeToFormat(&ra,&fo,defaultAction,NULL,&me);
      ad.set(1,9,0);
      ra.set(&ad,&ad);
  		theModel -> setRangeToFormat(&ra,&fo,defaultAction,NULL,&me);
      ad.set(1,10,0);
      ra.set(&ad,&ad);
  		theModel -> setRangeToFormat(&ra,&fo,defaultAction,NULL,&me);
      ad.set(1,11,0);
      ra.set(&ad,&ad);
  		theModel -> setRangeToFormat(&ra,&fo,defaultAction,NULL,&me);

      fo.setFormat(dateFormat);
      ad.set(1,1,0);
      ra.set(&ad,&ad);
  		theModel -> setRangeToFormat(&ra,&fo,defaultAction,NULL,&me);

      fo.setFormat(percentFormat);
      ad.set(1,8,0);
      ra.set(&ad,&ad);
  		theModel -> setRangeToFormat(&ra,&fo,defaultAction,NULL,&me);

		ad.set(0,0,0);
		theModel -> setCellToStringOrNumber(&ad,"PO Num",0,&me,NULL);
		ad.set(0,1,0);
		theModel -> setCellToStringOrNumber(&ad,"Date",0,&me,NULL);
		ad.set(0,2,0);
		theModel -> setCellToStringOrNumber(&ad,"Initials",0,&me,NULL);
		ad.set(0,3,0);
		theModel -> setCellToStringOrNumber(&ad,"Descriptions",0,&me,NULL);
		ad.set(0,4,0);
		theModel -> setCellToStringOrNumber(&ad,"Cost",0,&me,NULL);
		ad.set(0,5,0);
		theModel -> setCellToStringOrNumber(&ad,"Qty.",0,&me,NULL);
		ad.set(0,6,0);
		theModel -> setCellToStringOrNumber(&ad,"Total",0,&me,NULL);
		ad.set(0,7,0);
		theModel -> setCellToStringOrNumber(&ad,"Sub Total",0,&me,NULL);
		ad.set(0,12,0);
		theModel -> setCellToStringOrNumber(&ad,"Comments",0,&me,NULL);
		ad.set(0,13,0);
		theModel -> setCellToStringOrNumber(&ad,"Flags",0,&me,NULL);
		ad.set(0,8,0);
		theModel -> setCellToStringOrNumber(&ad,"Tax Rate",0,&me,NULL);
		ad.set(0,9,0);
		theModel -> setCellToStringOrNumber(&ad,"Tax",0,&me,NULL);
		ad.set(0,10,0);
		theModel -> setCellToStringOrNumber(&ad,"Shipping",0,&me,NULL);
		ad.set(0,11,0);
		theModel -> setCellToStringOrNumber(&ad,"Total",0,&me,NULL);

		ad.set(1,7,0);
		theModel -> setCellToString(&ad,"=sum(G2:G32)",0,&me,NULL);
		ad.set(1,9,0);
		theModel -> setCellToString(&ad,"=h2*i2",0,&me,NULL);
                ad.set(1,10,0);
                theModel -> setCellToStringOrNumber(&ad,"$0.00",0,&me,NULL);
		ad.set(1,11,0);
		theModel -> setCellToString(&ad,"=j2+h2+k2",0,&me,NULL);
		ad.set(1,6,0);
		theModel -> setCellToString(&ad,"=e2*f2",0,&me,NULL);
      ad2.set(21,6,0);
      ra.set(&ad,&ad2);
      theModel -> fillSmartDown(&ra,0,NULL,&me);

      fo.free();
      ra.free();
}

struct _wdata{
    MEditView *theEdit;
    MMesaView *theView;
};

// displays the internal model in sheetview format.
MRESULT EXPENTRY ViewSheetProc(HWND hw,ULONG msg,MPARAM mp1,MPARAM mp2)
{
    _wdata * wd =(_wdata*) WinQueryWindowULong(hw,QWL_USER);
    // get the pointer to the view
    switch (msg) {
    case WM_INITDLG :
    {
      MRect tre;
      SWP swp;
      wd = new _wdata;

      // query the position of where the sheet view is supposed to
      // be placed
		WinQueryWindowPos(WinWindowFromID(hw,DID_SHEETVIEW),&swp);
		tre.setX(swp.x);
		tre.setY(swp.y);
		tre.setWid(swp.cx);
		tre.setHi(swp.cy);
      // create a new sheet view and set it up
		wd->theView = new MMesaView(0,currentModel);
      wd->theView->setHWND(hw);
		wd->theView -> setUp(&tre);
      wd->theEdit=NULL;
      // save the pointer to the view in the ULong so we can delete it later
      WinSetWindowULong(hw,QWL_USER,(ULONG)wd);
      MyMesa->setHandleForEditViewOwner(hw);
      WinPostMsg(hw,WM_UPDATEFORMULA,NULL,NULL);
    }
    break;
 case WM_DESTROY:
    {
      // clean it ups and delete it
      if (wd->theEdit) {
          wd->theEdit->cleanUp();
          delete wd->theEdit;
      } // endif
      wd->theView->cleanUp();
      delete wd->theView;
      MyMesa->setHandleForEditViewOwner(0L);
    }
    break;
case WM_UPDATEFORMULA:
{
       char *tmp;
       tmp=wd->theView -> getSelectionContents();
       WinSetDlgItemText(hw,DID_FORMULA,tmp);
       MFree(tmp);
}
    break;
case WM_CREATEEDIT:
{
   if (wd->theEdit) { // get rid of old one
       wd->theEdit->cleanUp();
       delete wd->theEdit;
   } // endif

      MRect tre;
      SWP swp;

      // query the position of where the edit view is supposed to
      // be placed
		WinQueryWindowPos(WinWindowFromID(hw,DID_FORMULA),&swp);
		tre.setX(swp.x);
		tre.setY(swp.y);
		tre.setWid(swp.cx);
		tre.setHi(swp.cy);

    wd->theEdit = new MEditView(0);
    wd->theEdit->setHWND(hw);
    wd->theEdit -> setEditString( (MEditString *)mp1);
    wd->theEdit -> setUp(&tre);
}
    break;
case WM_REMOVEEDIT:
    if (wd->theEdit) {
        wd->theEdit -> cleanUp();
        WinDestroyWindow( wd->theEdit -> getView() );
        delete wd->theEdit;
        wd->theEdit=NULL;
    } // endif
    break;
case WM_INCELLEDIT:
    return (MRESULT)WinSendMsg(WinWindowFromID(hw,DID_INCELL),BM_QUERYCHECK,NULL,NULL);
    break;
case WM_SETFORMULATXT:
     WinSetDlgItemText(hw,DID_FORMULA,(PCHAR)mp1);
    break;
case WM_GETEDITVIEW:
     return (MRESULT)wd->theEdit;
    break;
 default:
    return WinDefDlgProc(hw,msg,mp1,mp2);
   break;
 } /* endswitch */
 return (MRESULT)FALSE;
}


// this is the constructor for creating a new purchase order.
POrder::POrder(HWND hwnd)
{
  // create a new interest object
  point=new POInterest(hwnd);
  // create a new MesaModel and set it up
  theModel=new MMesaModel;
  theModel->setUp(MyMesa);
  // add the formatting and titles appropriate for the purchase order
  SetupNewPO(theModel);
  // set the pathname to nothing
  theModel->setPathName("",0);
  // register the interest in the model
  theModel->registerInterest(point);
  // we aren't in the sheet view on startup
  inSheetView=0;
}


// this is the constructor for createing a PO from a file
POrder::POrder(char * filename,HWND hwnd)
{
  MException me;

  // create the interest object
  point=new POInterest(hwnd);
  // create a new mesamodel and set it up with the controller
  theModel=new MMesaModel;
  theModel->setUp(MyMesa);
  // set the path name
  theModel->setPathName(filename,0);
  // have the model load it's info from the file
  theModel->loadFromPath(0,&me);
  // register the information
  theModel->registerInterest(point);
  // we aren't in the sheet view on startup
  inSheetView=0;
}

// the PO destructor
POrder::~POrder()
{
 // unregister the interest.  If there are no other interests (should be in our case)
 // the model will automatically delete itself so we don't have to do it here.
 // if there is another interest out there someplace, the model will be deleted
 // when that interest is done with the model
 theModel->unregisterInterest(point);
 // delete the interest object
 delete point;
}


// returns the PO number as a string
char *POrder::PONum()
{
   char * str,*str2;
   MAddress ad;

   // get the po number from [A]A2 in the model
   ad.set(1,0,0);
   str=theModel->getCellValue(&ad);
   stripEndingSpace(str);

   // copy the resulting string to a new string that uses the
   // compiler memory management instead of Mesa's.  Thus, the returned
   // string can just be deleted with delete str instead of using MFree()
   str2=new char[MStrLen(str)+1];
   strcpy(str2,str);

   // free the memory and return the string
   MFree(str);
   return str2;
}


char *POrder::Date()
{
   char * str,*str2;
   MAddress ad;

   // get the date from [A]B2 in the model
   ad.set(1,1,0);
   str=theModel->getCellValue(&ad);
   stripEndingSpace(str);

   // copy the resulting string to a new string that uses the
   // compiler memory management instead of Mesa's.  Thus, the returned
   // string can just be deleted with delete str instead of using MFree()
   str2=new char[MStrLen(str)+1];
   strcpy(str2,str);

   // free the memory and return the string
   MFree(str);
   return str2;
}

char *POrder::Initials()
{
   char * str,*str2;
   MAddress ad;

   // get the initials from [A]C2 in the model
   ad.set(1,2,0);
   str=theModel->getCellValue(&ad);
   stripEndingSpace(str);

   // copy the resulting string to a new string that uses the
   // compiler memory management instead of Mesa's.  Thus, the returned
   // string can just be deleted with delete str instead of using MFree()
   str2=new char[MStrLen(str)+1];
   strcpy(str2,str);

   // free the memory and return the string
   MFree(str);
   return str2;
}

char *POrder::SubTotal()
{
   char * str,*str2;
   MAddress ad;

   // get the subtotal from [A]H2 in the model
   ad.set(1,7,0);
   str=theModel->getCellValue(&ad);
   stripEndingSpace(str);

   // copy the resulting string to a new string that uses the
   // compiler memory management instead of Mesa's.  Thus, the returned
   // string can just be deleted with delete str instead of using MFree()
   str2=new char[MStrLen(str)+1];
   strcpy(str2,str);

   // free the memory and return the string
   MFree(str);
   return str2;
}

char *POrder::Tax()
{
   char * str,*str2;
   MAddress ad;

   // get the tax amount from [A]J2 in the model
   ad.set(1,9,0);
   str=theModel->getCellValue(&ad);
   stripEndingSpace(str);

   // copy the resulting string to a new string that uses the
   // compiler memory management instead of Mesa's.  Thus, the returned
   // string can just be deleted with delete str instead of using MFree()
   str2=new char[MStrLen(str)+1];
   strcpy(str2,str);

   // free the memory and return the string
   MFree(str);
   return str2;
}

char *POrder::TaxRate()
{
   char * str,*str2;
   MAddress ad;

   // get the tax rate from [A]I2 in the model
   ad.set(1,8,0);
   str=theModel->getCellValue(&ad);
   stripEndingSpace(str);

   // copy the resulting string to a new string that uses the
   // compiler memory management instead of Mesa's.  Thus, the returned
   // string can just be deleted with delete str instead of using MFree()
   str2=new char[MStrLen(str)+1];
   strcpy(str2,str);

   // free the memory and return the string
   MFree(str);
   return str2;
}

char *POrder::Shipping()
{
   char * str,*str2;
   MAddress ad;
   stripEndingSpace(str);

   // get the shipping charges from [A]K2 in the model
   ad.set(1,10,0);
   str=theModel->getCellValue(&ad);

   // copy the resulting string to a new string that uses the
   // compiler memory management instead of Mesa's.  Thus, the returned
   // string can just be deleted with delete str instead of using MFree()
   str2=new char[MStrLen(str)+1];
   strcpy(str2,str);

   // free the memory and return the string
   MFree(str);
   return str2;
}

char *POrder::Total()
{
   char * str,*str2;
   MAddress ad;

   // get the total from [A]L2 in the model
   ad.set(1,11,0);
   str=theModel->getCellValue(&ad);
   stripEndingSpace(str);

   // copy the resulting string to a new string that uses the
   // compiler memory management instead of Mesa's.  Thus, the returned
   // string can just be deleted with delete str instead of using MFree()
   str2=new char[MStrLen(str)+1];
   strcpy(str2,str);

   // free the memory and return the string
   MFree(str);
   return str2;
}

char *POrder::Comments()
{
   char * str,*str2;
   MAddress ad;

   // get the comments from [A]M2 in the model
   ad.set(1,12,0);
   str=theModel->getCellValue(&ad);

   // copy the resulting string to a new string that uses the
   // compiler memory management instead of Mesa's.  Thus, the returned
   // string can just be deleted with delete str instead of using MFree()
   str2=new char[MStrLen(str)+1];
   strcpy(str2,str);

   // free the memory and return the string
   MFree(str);
   return str2;
}

char *POrder::Flags()
{
   char * str,*str2;
   MAddress ad;

   // get the flags from [A]N1 in the model
   ad.set(1,13,0);
   str=theModel->getCellValue(&ad);

   // copy the resulting string to a new string that uses the
   // compiler memory management instead of Mesa's.  Thus, the returned
   // string can just be deleted with delete str instead of using MFree()
   str2=new char[MStrLen(str)+1];
   strcpy(str2,str);

   // free the memory and return the string
   MFree(str);
   return str2;
}


void POrder::setPONum(char * str)
{
   MException me;
   MAddress ad;

   // set po number the at [A]A2 in the model
   if (!inSheetView) {
      ad.set(1,0,0);
      theModel->setCellToString(&ad,str,0,&me,NULL);
   } /* endif */
}

void POrder::setDate(char *str)
{
   MException me;
   MAddress ad;

   // set the date at [A]B2 in the model
   if (!inSheetView) {
      ad.set(1,1,0);
      theModel->setCellToString(&ad,str,0,&me,NULL);
   }
}

void POrder::setInitials(char *str)
{
   MException me;
   MAddress ad;

   // set the initials at [A]C2 in the model
   if (!inSheetView) {
      ad.set(1,2,0);
      theModel->setCellToString(&ad,str,0,&me,NULL);
   }
}

void POrder::setTaxRate(char *str)
{
   MException me;
   MAddress ad;

   // set the taxrate at [A]I2 in the model
   if (!inSheetView) {
      ad.set(1,8,0);
      theModel->setCellToString(&ad,str,0,&me,NULL);
   }
}

void POrder::setShipping(char *str)
{
   MException me;
   MAddress ad;

   // set the shipping charges at [A]K2 in the model
   if (!inSheetView) {
      ad.set(1,10,0);
      stripDollarAndCommas(str);
      theModel->setCellToString(&ad,str,0,&me,NULL);
   }
}

void POrder::setComments(char *str)
{
   MException me;
   MAddress ad;

   // set the at [A]M2 in the model
   if (!inSheetView) {
      ad.set(1,12,0);
      theModel->setCellToString(&ad,str,0,&me,NULL);
   }
}

void POrder::setFlags(char *str)
{
   MException me;
   MAddress ad;

   // set the at [A]N2 in the model
   if (!inSheetView) {
      ad.set(1,13,0);
      theModel->setCellToString(&ad,str,0,&me,NULL);
   }
}

void POrder::setItemCost(char *desc, char *cost)
{
   MAddress ad,ad2;
   MException me;
   MRange ra;

   // set the range in which to find the description
   if (!inSheetView) {
      ad.set(0,3,0);
      ad2.set(31,3,0);
      ra.init();
      ra.set(&ad,&ad2);
      ad2=theModel->find(desc,stringFindFlag,0,&ra,&ad);

      // once the cell for the description is found, advance 1 column
      // to get the cost and set it to the new value.
      ad2.setCol(ad2.getCol()+1);
      stripDollarAndCommas(cost);
      theModel->setCellToString(&ad2,cost,0,&me,NULL);
   }
}

void POrder::setItemQuantity(char *desc, char *quan)
{
   MAddress ad,ad2;
   MException me;
   MRange ra;

   // set the range in which to find the description
   if (!inSheetView) {
      ad.set(0,3,0);
      ad2.set(31,3,0);
      ra.init();
      ra.set(&ad,&ad2);
      ad2=theModel->find(desc,stringFindFlag,0,&ra,&ad);

      // once the cell for the description is found, advance 2 columns
      // to get the quanitity and set it to the new value.
      ad2.setCol(ad2.getCol()+2);
      stripEndingSpace(quan);
      theModel->setCellToString(&ad2,quan,0,&me,NULL);
   }
}

char *POrder::queryItemCost(char *desc)
{
   MAddress ad,ad2;
   MRange ra;
   char *str,*str2;

   // set the range in which to find the description
   ad.set(0,3,0);
   ad2.set(31,3,0);
   ra.init();
   ra.set(&ad,&ad2);
   ad2=theModel->find(desc,stringFindFlag,0,&ra,&ad);

   // once the cell for the description is found, advance to next column
   // to get the cost and get it.
   ad2.setCol(ad2.getCol()+1);
   str=theModel->getCellValue(&ad2);
   // copy the resulting string to a new string that uses the
   // compiler memory management instead of Mesa's.  Thus, the returned
   // string can just be deleted with delete str instead of using MFree()
   str2=new char[MStrLen(str)+1];
   strcpy(str2,str);

   // free the memory and return the string
   MFree(str);
   return str2;
}

char *POrder::queryItemQuantity(char *desc)
{
   MAddress ad,ad2;
   MRange ra;
   char *str,*str2;

   // set the range in which to find the description
   ad.set(0,3,0);
   ad2.set(31,3,0);
   ra.init();
   ra.set(&ad,&ad2);
   ad2=theModel->find(desc,stringFindFlag,0,&ra,&ad);

   // once the cell for the description is found, advance 2 columns
   // to get the quanitity and get it.
   ad2.setCol(ad2.getCol()+2);
   str=theModel->getCellValue(&ad2);
   // copy the resulting string to a new string that uses the
   // compiler memory management instead of Mesa's.  Thus, the returned
   // string can just be deleted with delete str instead of using MFree()
   str2=new char[MStrLen(str)+1];
   strcpy(str2,str);

   // free the memory and return the string
   MFree(str);
   return str2;
}

char *POrder::queryItemTotal(char *desc)
{
   MAddress ad,ad2;
   MRange ra;
   char *str,*str2;

   // set the range in which to find the description
   ad.set(0,3,0);
   ad2.set(31,3,0);
   ra.init();
   ra.set(&ad,&ad2);
   ad2=theModel->find(desc,stringFindFlag,0,&ra,&ad);

   // once the cell for the description is found, advance 3 columns
   // to get the items total and get it.
   ad2.setCol(ad2.getCol()+3);
   str=theModel->getCellValue(&ad2);
   // copy the resulting string to a new string that uses the
   // compiler memory management instead of Mesa's.  Thus, the returned
   // string can just be deleted with delete str instead of using MFree()
   str2=new char[MStrLen(str)+1];
   strcpy(str2,str);

   // free the memory and return the string
   MFree(str);
   return str2;
}

char *POrder::startEnumDescriptions()
{
   char *str,*str2;

   currentEnum.set(1,3,0);
   str=theModel->getCellValue(&currentEnum);
   // copy the resulting string to a new string that uses the
   // compiler memory management instead of Mesa's.  Thus, the returned
   // string can just be deleted with delete str instead of using MFree()
   str2=new char[MStrLen(str)+1];
   strcpy(str2,str);

   // free the memory and return the string
   MFree(str);
   return str2;
}

void POrder::endEnumDescriptions()
{
   currentEnum.set(0,3,0);
}

char *POrder::nextDescription()
{
   char *str,*str2;

   currentEnum.setRow(currentEnum.getRow()+1);
   str=theModel->getCellValue(&currentEnum);
   // copy the resulting string to a new string that uses the
   // compiler memory management instead of Mesa's.  Thus, the returned
   // string can just be deleted with delete str instead of using MFree()
   str2=new char[MStrLen(str)+1];
   strcpy(str2,str);

   // free the memory and return the string
   MFree(str);
   return str2;
}


// returns the filename that is stored in the model
char *POrder::fileName()
{
   char *str,*str2;

   str=theModel->getPathName();
   str2=new char[MStrLen(str)+1];
   strcpy(str2,str);
   MFree(str);
   return str;
}

// sets the filename in the model
void POrder::setFileName(char * name)
{
   theModel->setPathName(name,0);
}

// saves the model to the filename stored in the model
void POrder::save()
{
   MException me;
   theModel->saveToPath(&me);
}

// pops up the dialog whith the sheet view in it
void POrder::displaySheetView(HWND hw)
{
  currentModel=theModel;
  inSheetView=1;
  WinDlgBox(HWND_DESKTOP,hw,ViewSheetProc,NULL,IDD_VIEWSHEET,0L);
  inSheetView=0;
}

// adds an item to the PO
void POrder::addItem(char *desc, char *cost ,char *quantity)
{
   MAddress ad,ad2;
   MException me;

   // strip the extra formatting of the cost
   stripDollarAndCommas(cost);

   // start at the bottom of the description column ([A]D32)
   ad.set(31,3,0);
   // find the first cell from the bottom that contains text
   // equivilent to hitting <end><up> in Mesa 2
   theModel->findPriorCellInCol(1,&ad,&ad2);
   // we want the empty cell below it
   ad2.setRow(ad2.getRow()+1);
   // set the cell to the description
   theModel->setCellToString(&ad2,desc,0,&me,NULL);
   //set the cost and quantity
   setItemCost(desc,cost);
   setItemQuantity(desc,quantity);
}

// deletes an item from the PO and shifts the items up to remove
// any white space
void POrder::deleteItem(char *desc)
{
   MAddress ad,ad2;
   MRange ra;
   MException me;
   MFormat fo;
   char *str,*str2;

   // set the range in which to find the description
   ad.set(0,3,0);
   ad2.set(31,3,0);
   ra.init();
   ra.set(&ad,&ad2);
   ad2=theModel->find(desc,stringFindFlag,0,&ra,&ad);

   // once the description is found, we'll move everything
   // bellow it up

   ad.set(31,5,0);
   ad2.setRow(ad2.getRow()+1);
   ra.set(&ad2,&ad);
   ad.set(-1,0,0);
   theModel->moveCells(&ra,&ad,0,&me,NULL);

   // reforma the bottom row
   ad.set(31,4,0);
   fo.init();
   fo.setMergePrecision(1);
   fo.setMergeFormat(1);
   ra.set(&ad,&ad);
   fo.setFormat(currencyTypeFormat |currencySubtypeFormat | 2);
   theModel -> setRangeToFormat(&ra,&fo,defaultAction,NULL,&me);
}
