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
    This class abstracts the OS/2 clipboard and either serves up data
    or archives data for clipboard operations
    6-15-94 dpp
*/

#ifndef _MH_clip_stream

#define _MH_clip_stream

#include "os2h.h"

#include "stream.h"


class MClipStream : public MStream
{
    public:

#if defined(M2Z)
    MClipStream(HAB);
#elif defined(M2NT)
    MClipStream(HWND);
#elif defined(M2MAC)
	MClipStream(int);
#endif
    virtual ~MClipStream();
    virtual void beginWrite();
    virtual void endWriteText();
    virtual void endWriteBitmap();
    virtual void endWritePict();
    virtual void endWriteMesa();
	virtual void endWriteLink();
	virtual void endWriteRTF();
    virtual int hasText();
    virtual int hasBitmap();
    virtual int hasPict();
    virtual int hasMesa();
    virtual int hasRTF();
	virtual int hasLink();
    virtual int isEOF();


    virtual void resetClipboard();  // clear all the data on the clipboard

    virtual void beginReadText();
    virtual const char *getTextPtr() {return textBuf;};
    virtual const char *getRTFPtr() {return rtfBuf;};
	virtual const char *getLinkPtr() {return linkBuf;};
    virtual const char *getMesaPtr(int &l) {l = mesaLen; return mesaBuf;};
    virtual void beginReadBitmap();
    virtual void beginReadPict();
    virtual void beginReadMesa();
    virtual void beginReadRTF();
	virtual void beginReadLink();
    virtual void endClipRead();
    virtual int read(void *,int);
    virtual int write(const void *,int);
    virtual int getPos();
    virtual int getStreamLen();
    virtual int seek(int);
	virtual void setDontStuff(int);

    private:
    int pos,len;
    int size;
    char *mBuf;
#if defined(M2Z)
    HAB hab; // need this to pass to the engine side which cannot ask for it
#elif defined(M2NT)
    HWND hab; // need this to pass to the engine side which cannot ask for it
#endif
    char *textBuf,*bitMapBuf,*pictBuf,*mesaBuf,*linkBuf,*rtfBuf;
	int mesaLen;
    int resetAndStuff;
	int dontStuff;

    void doubleSize();
};

// ifndef _MH_clip_stream
#endif
