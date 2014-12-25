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


// 94-08-24 dpp changed action values from #define's to const's
// per IBM style guidelines

#ifndef _MH_actions

#define _MH_actions

// here are a bunch of actions
const int defaultAction = 0;
const int noAction = 0xffffffff;

const int recalcDoAction = 1;
const int redisplayDoAction = 0x10;
const int changedSizeDoAction = 0x100;
const int contentsChangedDoAction = 0x1000;
const int formatChangedDoAction = 0x10000;
const int resetViewDoAction = 0x100000;
const int allDoAction = (contentsChangedDoAction | formatChangedDoAction |
    recalcDoAction | redisplayDoAction | changedSizeDoAction);
const int normalDoAction = (contentsChangedDoAction | recalcDoAction | redisplayDoAction);
const int normFormDoAction = (normalDoAction | formatChangedDoAction);


// some constants for various functions

const int clearFormatModelFunc = 0;
const int clearValuesModelFunc = 1;
const int clearFormulasModelFunc = 2;
const int clearStringsModelFunc = 3;
const int clearNumbersModelFunc = 4;

const int convertFormToValueModelFunc = 0;
const int convertStringsToNumbersModelFunc = 1;
const int convertNumbersToStringsModelFunc = 2;
const int convertToUpperModelFunc = 3;
const int convertToLowerModelFunc = 4;
const int convertToProperModelFunc = 5;

const int autoSumModelFunc = 0;
const int autoAveModelFunc = 1;
const int autoStdDevModelFunc = 2;
const int autoVarModelFunc = 3;
const int autoMinModelFunc = 4;
const int autoMaxModelFunc = 5;
const int autoProdModelFunc = 6;
const int autoSumSqModelFunc = 7;

const int noLock = 0;
const int readOnlyLock = 1;
const int noReadLock = 2;

const int noProtection = 0;
const int normalProtection = 1;

// recalculation order

const int rowRecalcOrder = 0;
const int columnRecalcOrder = 1;
const int naturalRecalcOrder = 2;
const int allowCircRecalcOrder = 3;

// the types of things to copy into the pasteboard
const int textPBOp = 1;
const int mesaPBOp = 2;
const int pictPBOp = 4;
const int allPBOp = (textPBOp | mesaPBOp | pictPBOp);

// the following are valid paste types
const int normalPaste = 0;
const int valuesPaste = 1;
const int formatPaste = 2;
const int transposePaste = 3;
const int insertDownPaste = 4;
const int insertRightPaste = 5;
const int movePaste = 6;
const int linkPaste = 7;

const int contentsFindFlag = 1;
const int valueFindFlag = 2;
const int numberFindFlag = 4;
const int stringFindFlag = 8;
const int exactFindFlag = 16;
const int caseFindFlag = 32;



// ifndef _MH_actions
#endif
