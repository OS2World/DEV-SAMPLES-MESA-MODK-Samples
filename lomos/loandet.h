
#include "mesamod.h"
#include "interest.h"
#include "change.h"

#define LO_REDISPLAY       WM_USER+20
#define LO_CHANGEDSIZE     WM_USER+21
#define LO_FORMATSCHANGED  WM_USER+22
#define LO_CONTENTSCHANGED WM_USER+23
#define LO_RESETVIEW       WM_USER+24

// the LOInterest class allows the Loan to know when something has changed
// during the incell editing of the sheet view.  Thus, it can update it's display.
// Each method just send one of the above messages to the window.
class LOInterest:public MInterest
{
    public:
    LOInterest(HWND hw);
    ~LOInterest();

    // this method is thread-safe
    virtual void redisplay(MChange *);
    virtual void changedSize(MChange *);
    virtual void formatsChanged(MChange *);
    virtual void contentsChanged(MChange *);
	 virtual void resetView(MChange *);

    private:
    HWND theWin;
};


// the purchase order wrapper for the model
class Loan {
public:
   Loan(HWND hwnd);
   Loan(char * filename,HWND hwnd);

   ~Loan();

char *LoanID();
char *AppDate();
char *RepID();
char *Name();
char *SSNo();
char *Type();
char *Amount();
char *Rate();
char *StDate();
char *Duration();
char *Periodicity();

void setLoanID(char * str);
void setAppDate(char *str);
void setRepID(char *str);
void setName(char *str);
void setSSNo(char *str);
void setType(char *str);
void setAmount(char *str);
void setRate(char *str);
void setStDate(char *str);
void setDuration(char *str);
void setPeriodicity(char *str);
void setPeriods();

char *fileName();
void setFileName(char * name);
void save();

void displaySheetView(HWND hw);
int isInSheetView() {return inSheetView; };

private:
    MMesaModel *theModel;
    MAddress currentEnum;
    LOInterest * loint;
    int inSheetView;
};

