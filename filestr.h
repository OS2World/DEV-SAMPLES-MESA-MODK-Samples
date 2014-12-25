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
    this is a subclass of stream that handles the I/O to disk
    6-1-94 dpp
    94-09-19 dpp added makeBackup() function
*/

#ifndef _MH_fileStream

#define _MH_fileStream

#include "stream.h"

#include "os2h.h"

#ifdef M2MAC
#include <stdio.h>
#endif

class MFileStream : public MStream {
    public:
    MFileStream(int,const char *);
    virtual ~MFileStream();

    virtual int write(const void *,int);
    virtual int read(void *,int);
    virtual int getPos();
    virtual int getStreamLen();
    virtual int seek(int);
    virtual void setAttributes(const char *);
    virtual void setMesaAttributes();
    virtual int isEOF();

    private:
    char *cache;
    int blen,start,pos,rfp;

#if defined(M2Z)
    HFILE file;
#elif defined(M2NT)
    HANDLE file;
// #if defined(M2Z) || defined(M2NT)
#elif defined(M2MAC)
	FILE *file;
#endif


    void flushCache();
};

// creates a backup of the named file with the given extension
void makeBackup(const char *,const char *);


// ifndef _MH_fileStream
#endif
