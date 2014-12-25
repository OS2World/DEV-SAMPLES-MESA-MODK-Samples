
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
    This header file does the right thing with the math and floating point
    stuff
    7-21-94 dpp
*/

#ifndef _MH_mesa_math

#define _MH_mesa_math

#include <math.h>

#if defined(M2Z) && !defined(__HIGHC__)
#include <builtin.h>
// #include <math.h>
#include <float.h>

#pragma map(pow,"my_masked_pow")
#pragma map(cos,"my_masked_cos")
#pragma map(acos,"my_masked_acos")
#pragma map(asin,"my_masked_asin")
#pragma map(atan,"my_masked_atan")
#pragma map(atan2,"my_masked_atan2")
#pragma map(ceil,"my_masked_ceil")
#pragma map(cosh,"my_masked_cosh")
#pragma map(exp,"my_masked_exp")
// #pragma map(fabs,"my_masked_fabs")
#pragma map(floor,"my_masked_floor")
#pragma map(log,"my_masked_log")
#pragma map(log10,"my_masked_log10")
#pragma map(sin,"my_masked_sin")
#pragma map(sinh,"my_masked_sinh")
#pragma map(sqrt,"my_masked_sqrt")
#pragma map(tan,"my_masked_tan")
#pragma map(tanh,"my_masked_tanh")


double _Optlink my_masked_pow(double,double);
double _Optlink my_masked_atan2(double,double);
double _Optlink my_masked_cos(double);
double _Optlink my_masked_acos(double);
double _Optlink my_masked_asin(double);
double _Optlink my_masked_atan(double);
double _Optlink my_masked_ceil(double);
double _Optlink my_masked_cosh(double);
double _Optlink my_masked_exp(double);
double _Optlink my_masked_floor(double);
double _Optlink my_masked_log(double);
double _Optlink my_masked_log10(double);
double _Optlink my_masked_sin(double);
double _Optlink my_masked_sinh(double);
double _Optlink my_masked_sqrt(double);
double _Optlink my_masked_tan(double);
double _Optlink my_masked_tanh(double);

/*
// (from Standard C Library, Plauger)
extern double _Stod( const char *s, char **endptr );
extern short dmul(  double *, double );
extern double _Dtento( double, short );
extern short _Dunscale( short *, double *);
extern short _Dnorm( unsigned short *ps );
extern short _Dscale( double *px, short exp );

#define _DFRAC ((1<<_DOFF)-1)
#define _DMASK (0x7fff&~_DFRAC)
#define _DMAX ((1<<(15-_DOFF))-1)
#define _DSIGN 0x8000

#define FINITE -1
#define INF		1
#define NAN		2

#if _D0==3
// little-endian
//#define _D0	3
#define _D1	2
#define _D2 1
#define _D3 0
#else
// big-endian
#define _D1 1
#define _D2 2
#define _D3 3
#endif

*/

// ifdef M2Z
#else
#include <math.h>
// ifdef M2Z
#endif

// ifndef _MH_mesa_math
#endif
