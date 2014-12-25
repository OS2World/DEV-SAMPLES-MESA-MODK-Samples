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
        the header file for the platform independant streaming protocal
        3-9-94 dpp
        
        94-08-30 dpp added support for MFILE_FRAME and changed the defines to const's
*/

#ifndef _MH_stream

#define _MH_stream

#include "except.h"
#include "object.h"

class MStream : public MObject
{
    public:

    MStream(); // initialize as a memory stream

    // MStream(MException *,void *,int);
    // MStream(MException *,int,const char *); // initialize to a file
    virtual ~MStream();


    // in order to get this class to read from your stream of choice
    // implement the following 5 methods and you're all set
    virtual int getPos() = 0; // get the position within the stream
    virtual int getStreamLen() = 0; // gets the total size of the stream
    virtual int seek(int) = 0; // goes to a position within the stream
    virtual int write(const void *,int) = 0; // write a bunch of bytes to the stream
    virtual int read(void *,int) = 0; // read a bunch of bytes from the stream
    virtual int isEOF() = 0; // are we at the end of the file?
    
    virtual void setMesaAttributes() {};
    virtual void setAttributes(const char *) {};

    // write an integer to the stream
    void writeInt(int i) {write(&i,sizeof(i));};
	
    // read an integer from the stream
    int readInt() {read(&tmpInt,sizeof(tmpInt)); return tmpInt;};
    long readLong() {read(&tmpLong,sizeof(tmpLong)); return tmpLong;};
    unsigned long readULong() {unsigned long i = 0; read(&i,sizeof(i)); return i;};
    // read a short from the stream
    short readShort() {read(&tmpShort,sizeof(tmpShort)); return tmpShort;};
    // read an unsigned short from the stream
    unsigned short readUShort() {read(&tmpUShort,sizeof(tmpUShort)); return tmpUShort;};
    // read an unsigned character
    int readUChar() {read(&tmpUChar,1); return tmpUChar;};
    // read a character
    int readChar() {read(&tmpChar,1); return tmpChar;};
    long double readLongDouble() { read(&tmpLDouble,sizeof(tmpLDouble)); return tmpLDouble;};
    // reads a double
    double readNumber() {read(&tmpDouble,sizeof(tmpDouble)); return tmpDouble;};

    // write a short to the stream
    void writeShort(short s) {write(&s,sizeof(s));};
    void writeUChar(unsigned char c) {write(&c,1);};

    // writes a double
    void writeNumber(double n) {write(&n,sizeof(n));};

    // read or write a pointer.  This is good only for
    // pointers that will be IN THE SAME PLACE when the
    // stream is read back!!!
    void writePointer(void *vp) {write(&vp,sizeof(void *));};
    const MException *getException() {return &exp;};
    // file version info
    int getVersion() {return version;};
    void setVersion(int i) {version = i;};

    
    // reading Excel data types
    int readXLInt();
    double readXLDouble();
    double readXLRK();
    void readXLString(char *);
    

    
    
    void writeLongDouble( long double d ) {write(&d,10);};

    // read a character string from the stream
    // returns a pointer to a null-terminated string that
    // must be MFree'd
    void *readPtr();

    // used to write a string pointer to the stream
    void writePtr(const void *,int);
    void writeString(const char *);

	// write a null terminated string to the stream
	void writes(const char *);
	// write an rtf string
	void writeRTF(const char *);

    void writeStr(const char *s) {writeString(s);};
    char *readString() {return (char *) readPtr();};
    char *readStr() {return readString();};
	void readString(char *);

    void *readPointer();

    int isError();
    int getError();

    void setupWrite(int);
    void endWrite();

	void setupXLWrite( int );
	void endXLWrite();
	
	void setupWK3Write( int );
	void endWK3Write();

    int setupRead();
    void unsetRead();
    void endRead();

        

    protected:
    int type;
    MException exp;
    int nextPos,lastPos;
    int version;
	
	// some temporary workspaces so we don't clog the stack with
	// infrequently used temporary variables
	int tmpInt;
	long tmpLong;
	short tmpShort;
	unsigned short tmpUShort;
	unsigned char tmpUChar;
	char tmpChar;
	long double tmpLDouble;
	double tmpDouble; 
};


const int MSTREAM_READ = 1;
const int MSTREAM_WRITE = 2;

const int ORG_VERSION = 0;

const int CURRENT_VERSION = 1;

/*
    records in the file format
*/

const int MFILE_BOF = 1;  // marks the begining of a Mesa file
const int MFILE_EOF = 2; // the last record in a Mesa file
const int MFILE_CELL = 3; // the contents of a cell in a Mesa file
const int MFILE_FORMAT = 4; // a format record
const int MFILE_OLDLAYER = 5; // layer information including runs
const int MFILE_COPY = 6; // the begining of a clipboard copy area
const int MFILE_FONT = 7; // a font record
const int MFILE_SCRIPT = 8; // a script record
const int MFILE_FRAME = 9; // a graphics frame record
const int MFILE_NUMFORMAT = 10; // info on number formats
const int MFILE_LABELS = 11; // the named ranges
const int MFILE_LAYER = 12; // the named ranges
const int MFILE_RECALC = 13; // stuff relating to recalculation
const int MFILE_DEFPRINTHEAD = 14; // the default print header info
const int MFILE_POSITION = 15; // where are the windows?
const int MFILE_NEWSCRIPT = 16; // a new script record
const int MFILE_DDEITEM = 17; // a new script record
const int MFILE_PASSWORD = 18;	// password information
const int MFILE_ZOOM = 19;		// zoom/scale
const int MFILE_BLOB = 20;		// blob storage
const int MFILE_SIZE = 21;		// the number of cells in the array
const int MFILE_TEXTSQUARE = 22;	// hack for 2.0.2/2.0.3 file compatibility
const int MFILE_TABSET = 23;		// hack for 2.0.2/2.0.3 file compat.
// ifndef _MH_stream
#endif
