
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include "mmemory.h"
#include "range.h"
#include "mesamod.h"
#include "sheetv.h"
#include "sampcont.h"
#include "lomos.h"
#include "loandet.h"
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



// as mentioned in loandet.h, the LOInterest methods mostly just post messages
// to the window so it knows what is going on in it's model
LOInterest::LOInterest(HWND hw) : MInterest()
{
   theWin=hw;
}

LOInterest::~LOInterest()
{
}

void LOInterest::redisplay(MChange *mc)
{
   WinPostMsg(theWin,LO_REDISPLAY,(MPARAM)mc,0L);
}
void LOInterest::changedSize(MChange *mc)
{
   WinPostMsg(theWin,LO_CHANGEDSIZE,(MPARAM)mc,0L);
}
void LOInterest::formatsChanged(MChange *mc)
{
   WinPostMsg(theWin,LO_FORMATSCHANGED,(MPARAM)mc,0L);
}
void LOInterest::contentsChanged(MChange *mc)
{
   WinPostMsg(theWin,LO_CONTENTSCHANGED,(MPARAM)mc,0L);
}
void LOInterest::resetView(MChange *mc)
{
   WinPostMsg(theWin,LO_RESETVIEW,(MPARAM)mc,0L);
}


// this function sets up a new Loan by formatting the top layer of the
// model and inserting the appropriate titles and formulas
void SetupNewLoan(MMesaModel * theModel)
{
	MRange ra;
	MFormat fo;
	MException me;
	MAddress ad,ad2;
   static char per[] = "=if(k2=\"Weekly\", j2*52, j2*12)";
   static char prate[] = "=if(k2=\"Weekly\", h2/52, h2/12)";
   int nper;

/* Set range formats */
      fo.init();
		fo.setMergePrecision(1);
		fo.setMergeFormat(1);
      fo.setFormat(generalAlignment);

      ad.set(0,0,0);
      ad2.set(31,12,0);
      ra.init();
      ra.set(&ad,&ad2);
  		theModel -> setRangeToFormat(&ra,&fo,defaultAction,NULL,&me);

		fo.setFormat(currencyTypeFormat |currencySubtypeFormat | 2);
      ad.set(1,6,0);
      ra.set(&ad,&ad);
  		theModel -> setRangeToFormat(&ra,&fo,defaultAction,NULL,&me);

      ad.set(4,1,0);
      ad2.set(31,4,0);
      ra.set(&ad,&ad2);
  		theModel -> setRangeToFormat(&ra,&fo,defaultAction,NULL,&me);

      ad.set(2,4,0);
      ra.set(&ad,&ad);
  		theModel -> setRangeToFormat(&ra,&fo,defaultAction,NULL,&me);

      fo.setFormat(dateFormat);
      ad.set(1,1,0);
      ra.set(&ad,&ad);
  		theModel -> setRangeToFormat(&ra,&fo,defaultAction,NULL,&me);

      ad.set(1,8,0);
      ra.set(&ad,&ad);
  		theModel -> setRangeToFormat(&ra,&fo,defaultAction,NULL,&me);

      ad.set(4,0,0);
      ad2.set(31,0,0);
      ra.set(&ad,&ad2);
  		theModel -> setRangeToFormat(&ra,&fo,defaultAction,NULL,&me);
     
      fo.setFormat(percentFormat);
      ad.set(1,7,0);
      ra.set(&ad,&ad);
  		theModel -> setRangeToFormat(&ra,&fo,defaultAction,NULL,&me);

      ad.set(1,12,0);
      ra.set(&ad,&ad);
         theModel -> setRangeToFormat(&ra,&fo,defaultAction,NULL,&me);

/* Set headings and subheadings */
		ad.set(0,0,0);
		theModel -> setCellToStringOrNumber(&ad,"Loan ID",0,&me,NULL);
		ad.set(0,1,0);
		theModel -> setCellToStringOrNumber(&ad,"App Date",0,&me,NULL);
		ad.set(0,2,0);
		theModel -> setCellToStringOrNumber(&ad,"Rep ID",0,&me,NULL);
		ad.set(0,3,0);
		theModel -> setCellToStringOrNumber(&ad,"Name",0,&me,NULL);
		ad.set(0,4,0);
		theModel -> setCellToStringOrNumber(&ad,"SS No",0,&me,NULL);
		ad.set(0,5,0);
		theModel -> setCellToStringOrNumber(&ad,"Type",0,&me,NULL);
		ad.set(0,6,0);
		theModel -> setCellToStringOrNumber(&ad,"Amount",0,&me,NULL);
		ad.set(0,7,0);
		theModel -> setCellToStringOrNumber(&ad,"Rate",0,&me,NULL);
		ad.set(0,8,0);
		theModel -> setCellToStringOrNumber(&ad,"Start Date",0,&me,NULL);
		ad.set(0,9,0);
		theModel -> setCellToStringOrNumber(&ad,"Duration",0,&me,NULL);
		ad.set(0,10,0);
		theModel -> setCellToStringOrNumber(&ad,"Periodicity",0,&me,NULL);
      ad.set(0,11,0);
      theModel -> setCellToStringOrNumber(&ad,"Periods",0,&me,NULL);
      ad.set(0,12,0);
      theModel -> setCellToStringOrNumber(&ad,"Periodic Rate",0,&me,NULL);
      ad.set(3,0,0);
      theModel -> setCellToStringOrNumber(&ad,"Month",0,&me,NULL);
      ad.set(3,1,0);
      theModel -> setCellToStringOrNumber(&ad,"Payment",0,&me,NULL);
      ad.set(3,2,0);
      theModel -> setCellToStringOrNumber(&ad,"To Interest",0,&me,NULL);
      ad.set(3,3,0);
      theModel -> setCellToStringOrNumber(&ad,"To Principal",0,&me,NULL);
      ad.set(3,4,0);
      theModel -> setCellToStringOrNumber(&ad,"Outstanding",0,&me,NULL);

/* Set the initial values or formulas */
      ad.set(1,0,0);
      theModel -> setCellToStringOrNumber(&ad,"100",0, &me, NULL);
      ad.set(1,1,0);
      theModel -> setCellToString(&ad,"=TODAY",0, &me, NULL);
      ad.set(1,5,0);
      theModel -> setCellToStringOrNumber(&ad,"Student",0, &me, NULL);
      ad.set(1,8,0);
      theModel -> setCellToString(&ad,"=DATE((YEAR(B2)+(MONTH(B2)>11)),(MOD(MONTH(B2),12)+1),DAY(2))",0, &me, NULL);
      ad.set(1,9,0);
      theModel -> setCellToStringOrNumber(&ad,"3",0, &me, NULL);
      ad.set(1,10,0);
      theModel -> setCellToStringOrNumber(&ad,"Weekly",0, &me, NULL);
      ad.set(1,11,0);
      theModel -> setCellToString(&ad,per,0, &me, NULL);
      ad.set(1,12,0);
      theModel -> setCellToString(&ad,prate,0, &me, NULL);

      ad.set(4,0,0);
      theModel -> setCellToString(&ad,"=i2",0, &me, NULL);
      ad.set(4,1,0);
      theModel -> setCellToString(&ad,"=0-pmt($m$2,$l$2,$g$2)",0, &me, NULL);
      ad.set(4,2,0);
      theModel -> setCellToString(&ad,"=$m$2*$g$2",0, &me, NULL);
      ad.set(4,3,0);
      theModel -> setCellToString(&ad,"=b5-c5",0, &me, NULL);
      ad.set(4,4,0);
      theModel -> setCellToString(&ad,"=g2-d5",0, &me, NULL);
 
      ad.set(5,0,0);
      theModel -> setCellToString(&ad,"=if(((thisrow-4)<$l$2), (DATE((YEAR(A5)+(MONTH(A5)>11)),(MOD(MONTH(A5),12)+1),DAY(2))))",0, &me, NULL);
      ad.set(5,1,0);
      theModel -> setCellToString(&ad,"=if(((thisrow-4)<$l$2), (0-pmt($m$2,$l$2,$g$2))",0, &me, NULL);
      ad.set(5,2,0);
      theModel -> setCellToString(&ad,"=if(((thisrow-4)<$l$2), ($m$2*$e5)",0, &me, NULL);
      ad.set(5,3,0);
      theModel -> setCellToString(&ad,"=if(((thisrow-4)<$l$2), (b6-c6)",0, &me, NULL);
      ad.set(5,4,0);
      theModel -> setCellToString(&ad,"=if(((thisrow-4)<$l$2), (e5-d6)",0, &me, NULL);

  // format and smartfill according to periods at [A]L2 in the model
      ad.set(5,0,0);
      ad2.set(31,0,0);
      ra.set(&ad,&ad2);
      theModel -> fillSmartDown(&ra,0,NULL,&me);

      ad.set(5,1,0);
      ad2.set(31,1,0);
      ra.set(&ad,&ad2);
      theModel -> fillSmartDown(&ra,0,NULL,&me);

      ad.set(5,2,0);
      ad2.set(31,3,0);
      ra.set(&ad,&ad2);
      theModel -> fillSmartDown(&ra,0,NULL,&me);

      ad.set(5,3,0);
      ad2.set(31,3,0);
      ra.set(&ad,&ad2);
      theModel -> fillSmartDown(&ra,0,NULL,&me);

      ad.set(5,4,0);
      ad2.set(31,4,0);
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
      // cleans it up and deletes it
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
Loan::Loan(HWND hwnd)
{
  // create a new interest object
  loint=new LOInterest(hwnd);
  // create a new MesaModel and set it up
  theModel=new MMesaModel;
  theModel->setUp(MyMesa);
  // add the formatting and titles appropriate for the purchase order
  SetupNewLoan(theModel);
  // set the pathname to nothing
  theModel->setPathName("",0);
  // register the interest in the model
  theModel->registerInterest(loint);
  // we aren't in the sheet view on startup
  inSheetView=0;
}


// this is the constructor for createing a PO from a file
Loan::Loan(char * filename,HWND hwnd)
{
  MException me;

  // create the interest object
  loint=new LOInterest(hwnd);
  // create a new mesamodel and set it up with the controller
  theModel=new MMesaModel;
  theModel->setUp(MyMesa);
  // set the path name
  theModel->setPathName(filename,0);
  // have the model load it's info from the file
  theModel->loadFromPath(0,&me);
  // register the information
  theModel->registerInterest(loint);
  // we aren't in the sheet view on startup
  inSheetView=0;
}

// the PO destructor
Loan::~Loan()
{
 // unregister the interest.  If there are no other interests (should be in our case)
 // the model will automatically delete itself so we don't have to do it here.
 // if there is another interest out there someplace, the model will be deleted
 // when that interest is done with the model
 theModel->unregisterInterest(loint);
 // delete the interest object
 delete loint;
}


// returns the Loan ID as a string
char *Loan::LoanID()
{
   char * str,*str2;
   MAddress ad;

   // get the loan ID from [A]A2 in the model
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


char *Loan::AppDate()
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

char *Loan::RepID()
{
   char * str,*str2;
   MAddress ad;

   // get the representative ID from [A]C2 in the model
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

char *Loan::Name()
{
   char * str,*str2;
   MAddress ad;

   // get the applicants name from [A]D2 in the model
   ad.set(1,3,0);
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

char *Loan::SSNo()
{
   char * str,*str2;
   MAddress ad;

   // get the applicants SS # from [A]E2 in the model
   ad.set(1,4,0);
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

char *Loan::Type()
{
   char * str,*str2;
   MAddress ad;

   // get the loan type from [A]F2 in the model
   ad.set(1,5,0);
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

char *Loan::Amount()
{
   char * str,*str2;
   MAddress ad;
   stripEndingSpace(str);

   // get the loan amount from [A]G2 in the model
   ad.set(1,6,0);
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

char *Loan::Rate()
{
   char * str,*str2;
   MAddress ad;

   // get the interest rate from [A]H2 in the model
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

char *Loan::StDate()
{
   char * str,*str2;
   MAddress ad;

   // get the start date from [A]I2 in the model
   ad.set(1,8,0);
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

char *Loan::Duration()
{
   char * str,*str2;
   MAddress ad;

   // get the duration from [A]J2 in the model
   ad.set(1,9,0);
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

char *Loan::Periodicity()
{
   char * str,*str2;
   MAddress ad;

   // get the periodicity from [A]K2 in the model
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


void Loan::setLoanID(char * str)
{
   MException me;
   MAddress ad;

   // set the Loan ID at [A]A2 in the model
   if (!inSheetView) {
      ad.set(1,0,0);
      theModel->setCellToString(&ad,str,0,&me,NULL);
   } /* endif */
}

void Loan::setAppDate(char *str)
{
   MException me;
   MAddress ad;

   // set the date at [A]B2 in the model
   if (!inSheetView) {
      ad.set(1,1,0);
      theModel->setCellToString(&ad,str,0,&me,NULL);
   }
}

void Loan::setRepID(char *str)
{
   MException me;
   MAddress ad;

   // set the representative ID at [A]C2 in the model
   if (!inSheetView) {
      ad.set(1,2,0);
      theModel->setCellToString(&ad,str,0,&me,NULL);
   }
}

void Loan::setName(char *str)
{
   MException me;
   MAddress ad;

   // set the applicants name at [A]D2 in the model
   if (!inSheetView) {
      ad.set(1,3,0);
      theModel->setCellToString(&ad,str,0,&me,NULL);
   }
}

void Loan::setSSNo(char *str)
{
   MException me;
   MAddress ad;

   // set the applicants SS # at [A]E2 in the model
   if (!inSheetView) {
      ad.set(1,4,0);
      theModel->setCellToString(&ad,str,0,&me,NULL);
   }
}

void Loan::setType(char *str)
{
   MException me;
   MAddress ad;

   // set the loan type at [A]F2 in the model
   if (!inSheetView) {
      ad.set(1,5,0);
      theModel->setCellToString(&ad,str,0,&me,NULL);
   }
}

void Loan::setAmount(char *str)
{
   MException me;
   MAddress ad;

   // set the loan amount at [A]G2 in the model
   if (!inSheetView) {
      ad.set(1,6,0);
      stripDollarAndCommas(str);
      theModel->setCellToString(&ad,str,0,&me,NULL);
   }
}

void Loan::setRate(char *str)
{
   MException me;
   MAddress ad;

   // set the interest rate at [A]H2 in the model
   if (!inSheetView) {
      ad.set(1,7,0);
      theModel->setCellToString(&ad,str,0,&me,NULL);
   }
}

void Loan::setStDate(char *str)
{
   MException me;
   MAddress ad;

   // set the start date at [A]I2 in the model
   if (!inSheetView) {
      ad.set(1,8,0);
      theModel->setCellToString(&ad,str,0,&me,NULL);
   }
}

void Loan::setDuration(char *str)
{
   MException me;
   MAddress ad;

   // set the duration at [A]J2 in the model
   if (!inSheetView) {
      ad.set(1,9,0);
      theModel->setCellToString(&ad,str,0,&me,NULL);
   }
}

void Loan::setPeriodicity(char *str)
{
   MException me;
   MAddress ad;

   // set the periodicity at [A]K2 in the model
   if (!inSheetView) {
      ad.set(1,10,0);
      theModel->setCellToString(&ad,str,0,&me,NULL);
   }
}

void Loan::setPeriods()
{
   int nper;
   MAddress ad,ad2;
   MException me;
   MRange ra;

   // format and smartfill according to periods at [A]L2 in the model
      ad.set(1,11,0);
      nper=atoi(theModel->getCellValue(&ad));
      nper+= 4;

      ad.set(4,0,0);
      ad2.set(nper,0,0);
      ra.set(&ad,&ad2);
      theModel -> fillSmartDown(&ra,0,NULL,&me);
}


// returns the filename that is stored in the model
char *Loan::fileName()
{
   char *str,*str2;

   str=theModel->getPathName();
   str2=new char[MStrLen(str)+1];
   strcpy(str2,str);
   MFree(str);
   return str;
}

// sets the filename in the model
void Loan::setFileName(char * name)
{
   theModel->setPathName(name,0);
}

// saves the model to the filename stored in the model
void Loan::save()
{
   MException me;
   theModel->saveToPath(&me);
}

// pops up the dialog with the sheet view in it
void Loan::displaySheetView(HWND hw)
{
  currentModel=theModel;
  inSheetView=1;
  WinDlgBox(HWND_DESKTOP,hw,ViewSheetProc,NULL,IDD_VIEWSHEET,0L);
  inSheetView=0;
}

