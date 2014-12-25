/**************************************************************************
 *                                                                        *
 *                                                                        *
 *          This code is copyright (c)  1994  & 1995                      *
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
#ifndef _mh_TAG_MLIB__

#define _mh_TAG_MLIB__

#include "base.h"

#include "mmath.h"
#include "mversion.h"

extern "C"
{
extern int MStrLen(const char *);
extern int MByteLen(const char *s);

extern char *MStrNCpy(char *,const char *,int);
//extern void BCopy(const void *,void *,int);
extern void MMemSet(void *,int,int);
extern int MStrCmp(const char *,const char *);
extern void MStrUpr(char *);
extern int MStrNCmp(const char *,const char *,int);
extern int MStrCmpCI(const char *,const char *);
extern int MStrNCmpCI(const char *,const char *,int);
extern char *MStrCat(char *,const char *);
extern char *MStrChr(char *,char);
extern const char *MStrConstChr(const char *,char);
extern int MStrCspn(const char *,const char *);
extern int MStrCspnCI(const char *,const char *);
extern int matchStrings(const char *isIn,const char *string,int exact,int caseSensitive);
extern const char *passWhiteSpace(const char *);
inline const char *passW(const char *s) {return passWhiteSpace(s);}

/*
#if !defined(__HIGHC__) && !defined(M2MAC)
inline void memset(void *vp,int v,int cnt)
{
	char *cp = (char *) vp;
	
	while (cnt--) *(cp++) = v;
}
#endif
*/

extern int MAtoI(const char *);
extern float MAtoF(const char *);
extern  char *MStrSubstitute( const char *target, const char *find, const char *replace, int caseSens = 0);

// sorts two integers
extern void sort(int &,int &);

// these will have to be changed for non-byte-sized char sets


#ifdef M2ASCII
inline int isChar(char c) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) return 1; else return 0;}
inline int isNumberChar(char c) {if (c >= '0' && c <= '9') return 1; return 0;}
inline const char *nextConstChar(const char *t) {return t + 1;}
inline char *nextChar(char *t) {return t + 1;}

// return the position in the string of the nth character
inline int charPos(const char *,int t) {return t;}

inline int MToUpper(int i) {if (i >= 'a' && i <= 'z') return i - 32; return i;}

inline void copyChar(const char *s,char *&t) {*(t++) = *s;}
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

inline int MWordAlign(int i) {return i + ((i & 1)|((i&2)^((i&1)<<1)));}
inline double radtodeg(double d) {return (d / M_PI) * 180.0;}
inline double degtorad(double d) {return (d / 180.0) * M_PI;}

// round a number to n digits.  n can be negative
double MRound(double,int);
double MRoundInt(double);

// does a bounds check for an input string and its maximum size
// it reallocates the string if it needs more space
void checkSizeChar(char *&,const char *,int &);
void checkSize(char *&,int,int &);

#ifdef M2Z
#define DEFAULTAPPNAME "Mesa2"
#else
#define DEFAULTAPPNAME "Mesa"
#endif

int getIntDefault(const char *thing, int def,const char *  = DEFAULTAPPNAME);
char *getDefault(const char *thing, const char *def ,const char * = DEFAULTAPPNAME );
char *getBasicDefault(const char *thing);
void *getDefaultData(const char *,int *,const char * = DEFAULTAPPNAME);

void setIntDefault( const char *thing, int def,const char *  = DEFAULTAPPNAME);
void setDefault( const char *thing, const char *def,const char * = DEFAULTAPPNAME );
void setDefaultData(const char *,const void *,int ,const char * = DEFAULTAPPNAME);

double MStrtod( const char *, char ** );

inline void MStrCpy(char *d,const char *s)
{
	while (*s)
		*(d++) = *(s++);
	
	*d = 0;
}

inline void BCopy(const void *sv, void *sd,int n)
{
	const char *s = (const char *) sv;
	char *d = (char *) sd;
	
	while (n--)
		*(d++) = *(s++);
}


const char *getMesaVersion();
int getMesaRevision();

}

#endif
