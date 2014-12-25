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
*/

#ifndef _MH_memStream

#define _MH_memStream

#include "stream.h"

class MMemoryStream : public MStream {
    public:
    MMemoryStream(); // set up to write
    MMemoryStream(char *,int); // set up to read
    virtual ~MMemoryStream();

    virtual int write(const void *,int);
    virtual int read(void *,int);
    virtual int getPos();
    virtual int getStreamLen();
    virtual int seek(int);
    virtual int isEOF();

    private:
    int pos,max,flen;
    char *cp;

};

// ifndef _MH_memStream
#endif
