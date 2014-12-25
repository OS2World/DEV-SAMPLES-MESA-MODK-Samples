/**************************************************************************
 *                                                                        *
 *                                                                        *
 *          This code is copyright (c) 1994                               *
 *                     Athena Design, Inc.                                *
 *                     and David Pollak                                   *
 *                                                                        *
 *                ALL RIGHTS RESERVED                                     *
 *                                                                        *
 *                                                                        *
 *                                                                        *
 *                                                                        *
 *                                                                        *
 **************************************************************************/


#ifndef M2_feed_h_

#define M2_feed_h_

#ifdef M2Z

#define INCL_ERRORS
#define INCL_DOS

#include <os2.h>

#ifdef __cplusplus
extern "C"
{
#endif

extern int _System getRTFValue(char *, char *,double *);
extern int _System setRTFValue(char *, char *,double);
extern int _System RTFVersion();
extern void _System getRTFTime(DATETIME *);

#ifdef __cplusplus
}
#endif

// ifdef M2Z
#elif defined(M2MAC)

#ifdef __cplusplus
extern "C"
{
#endif

extern int  getRTFValue(char *, char *,double *);
extern int  setRTFValue(char *, char *,double);
extern int  RTFVersion();
// FIXME extern void getRTFTime(DATETIME *);

#ifdef __cplusplus
}
#endif


// elif M2MAC
#endif

// ifndef M2_feed_h_

#endif

