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
    This is an abstract class that allows an object to register
    "interest" in another object.
    4-7-94 dpp
*/


#ifndef _MH_interest

#define _MH_interest

class MChange;

#include "object.h"

class MInterest : public MObject
{
    public:
    MInterest();
    virtual ~MInterest();

    // this method is thread-safe
    virtual void redisplay(MChange *) {}; // = 0;
    virtual void changedSize(MChange *) {}; // = 0;
    virtual void formatsChanged(MChange *) {}; // = 0;
    virtual void contentsChanged(MChange *) {}; // = 0;
	virtual void resetView(MChange *) {}; // = 0;

    private:
    int n;
};


// ifndef _MH_interest
#endif
