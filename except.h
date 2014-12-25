/**************************************************************************
 *                                                                        *
 *                                                                        *
 *          This code is copyright (c) 1994                               *
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
    Errors, warnings, and notes are tricky little beasts.

    At the user interface level of an

    */

#ifndef _MH_exception

#define _MH_exception

#include "exc_num.h"

#ifdef BORLAND
#ifndef NULL
#define NULL ((void *) 0)
//ifndef NULL
#endif

// ifdef BORLAND
#else
#ifndef NULL
#define NULL ( 0)
//ifndef NULL
#endif
// ifdef BORLAND
#endif


class MGController;

class MException {
    public:
    void setErrorPlaces(int n,int i) {if (this) errorPlaces[n] = i;};
    int getErrorPlaces(int n) const {return errorPlaces[n];};
    int isError() const {if (this) return err; else return noError;};
    int getError() const {if (this) return err; else return noError;};
    MException() {_init();};
    ~MException() {_destroy();};

    void setError(int,const char * = (const char *) NULL);
    void addWarning(int,const char * = (const char *) NULL);
    int getWarningCnt() const;
    int getWarning(int) const;

    char *getErrorText() const;
    char *getWarningText(int) const;

    void setOSError(int);
    void setErrnoError(int);
    

#ifdef M2Z
    void setRexxError(int);
#endif

    void _init();
    void _destroy();

    private:
    

    int warnCnt,maxWarn;
    int *warnings;
    char **warnStrs;
    int err;
    char *errStr;
    int errorPlaces[10];
    };


#endif

