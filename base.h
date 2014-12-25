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

/*
    this module is the base header file for the Mesa project.

    It contains a series of assumptions about the project.

    1-24-94 dpp

    items that vary:

    endianness
        M2BIGENDIAN        -    for 68K, HA-PA, SPARC
        M2LITTLEENDIAN    -    for Intel, PowerPC

    Unicode support
        M2UNICODE    -    if UNICODE is supported by the underlying OS
        M2ASCII        -    if ASCII only is supported

    About the filesystem
        M2FSSENSITIVE     -    if the file system is case sensitive - UNIX
        M2FSINSENSITIVE    -    if the file system is case insensitive - OS/2, WP/OS

    Text that is hard coded is IFDEF'd with M2HARDTEXT


*/

#ifndef _MH_base

#define _MH_base

#if defined(M2Z) || defined(M2NT)

#define M2LITTLEENDIAN
#define M2ASCII
#define M2FSINSENSITIVE
// #define M2HARDTEXT

// what is the longest path name?
#define PATHLEN 2048

// what is the path separator char
#define PATHSEP '\\'
#define MAXTITLELEN 58

/*
#define IN_DLL
#define NOT_IN_DLL

#ifndef IN_DLL
#define NOT_IN_DLL
#endif
*/

#elif defined(M2MAC)

#define M2BIGENDIAN
#define M2ASCII
#define M2FSINSENSITIVE
// #define M2HARDTEXT

// what is the longest path name?
#define PATHLEN 2048

// what is the path separator char
#define PATHSEP ':'

#else
this is an error, no target OS defined
#endif

#endif

