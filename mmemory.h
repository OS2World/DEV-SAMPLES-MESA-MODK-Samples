/**************************************************************************
 *                                                                        *
 *                                                                        *
 *          This code is copyright (c) 1991, 1992, 1994, 1995             *
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

#ifndef _MH_memory

#define _MH_memory

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef NULL
#define NULL ( 0)
//ifndef NULL
#endif

// uncomment this define to turn on Mesa's memory debugging feature
// #define MESADEBUGMEMORYMODE

extern void MFree(void *);
extern char *MRealloc(void *,int);

extern void MFree(void *);
extern char *MRealloc(void *,int);

#ifdef MESADEBUGMEMORYMODE
#define MMalloc(a) _MMalloc(a,__FILE__,__LINE__)
#define copyOfString(a) _copyOfString(a,__FILE__,__LINE__)

extern char *_MMalloc(int,const char *,int);
extern char *_copyOfString(const char *,const char *,int);
#else
extern char *MMalloc(int);
extern char *copyOfString(const char *);
extern char *_MMalloc(int,const char *,int);
extern char *_copyOfString(const char *,const char *,int);
#endif

extern void MInitMemory();
extern void MFreeMemory();

#ifdef __cplusplus
}
#endif

#endif


