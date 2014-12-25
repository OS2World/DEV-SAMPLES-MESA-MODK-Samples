
#include "mesamod.h"
#include "interest.h"
#include "change.h"

#define PO_REDISPLAY       WM_USER+20
#define PO_CHANGEDSIZE     WM_USER+21
#define PO_FORMATSCHANGED  WM_USER+22
#define PO_CONTENTSCHANGED WM_USER+23
#define PO_RESETVIEW       WM_USER+24

// the POInterest class allows the PO to know when something has changed
// during the incell editing of the sheet view.  Thus, it can update it's display.
// Each method just send one of the above messages to the window.
class POInterest:public MInterest
{
    public:
    POInterest(HWND hw);
    ~POInterest();

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
class POrder {
public:
   POrder(HWND hwnd);
   POrder(char * filename,HWND hwnd);

   ~POrder();

char *PONum();
char *Date();
char *Initials();
char *SubTotal();
char *Tax();
char *TaxRate();
char *Shipping();
char *Total();
char *Comments();
char *Flags();

void setPONum(char * str);
void setDate(char *str);
void setInitials(char *str);
void setTaxRate(char *str);
void setShipping(char *str);
void setComments(char *str);
void setFlags(char *str);

void addItem(char *desc, char *cost ,char *quantity);
void deleteItem(char *desc);
void setItemCost(char *desc, char *cost);
void setItemQuantity(char *desc, char *quan);
char *queryItemCost(char *desc);
char *queryItemQuantity(char *desc);
char *queryItemTotal(char *desc);

char *startEnumDescriptions();
void endEnumDescriptions();
char *nextDescription();

char *fileName();
void setFileName(char * name);
void save();

void displaySheetView(HWND hw);
int isInSheetView() {return inSheetView; };

private:
    MMesaModel *theModel;
    MAddress currentEnum;
    POInterest * point;
    int inSheetView;
};

