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

#ifndef _MH_exception_num

#define _MH_exception_num

#define noError 0

// these are the various parse errors
#define parseType1Error 1
#define parseType2Error 2
#define parseNotAFormulaError 3
#define parseNoMatchingParenError 4
#define parseNoMatchingSqBraceError 5
#define parseNoMatchingCurleBraceError 6
#define parseBadCommaError 7
#define parseNoMatchingCurBraceError 8
#define parseBadSemiError 9
#define parseUnknownError 10
#define parseBadElementInArrayError 11

// and some execution errors
#define stackUnderflowError 12
#define feedNotFoundError 13
#define divideByZeroError 14
#define rateNotCalcError 15
#define irrNotCalcError 16
#define notAddressError 17
#define NAError 18
#define needCellRefError 19
#define sameError 20

// another parse error
#define wrongNumParamsError 21

// function error
#define notFoundError 22
#define matrixSizeError 23
#define singularMatrixError 24
#define depreciationError 25
#define chooseError 26
#define indexError 27
#define elementError 28
#define lookupError 29
#define generalError 30

// if the operation cannot be performed because the layer is protected
#define protectedError 31
#define readOnlyLayerError 32
#define readOnlyModelError 33
#define circularRefError 34

// pasteboard errors
#define incompatablePasteBoardError 35
#define needsMesaDataPasteBoardError 36
#define badDataShapePasteBoardError 37
#define badDataTypePasteBoardError 38
#define moveOnlyOnSameSheetPasteBoardError 39
#define numberTooLargeError 40

// addin and label errors
// 94-09-24 dpp
#define labelNotFoundError 41
#define addInNotFoundError 42

// bad input type error
#define badInputTypeError 43

// can't do this to a non-sheet layer
#define nonSheetTypeError 44

// a date or time format string is expected
#define notDateTimeError 45

// the shape cannot be done by the operation - ie sorting a discontiguous range
#define badShapeError 46

// the file is not a bitmap
#define notBitmapError 47

// the label was truncated due to restrictions on the output file format
#define	labelTruncatedError					48

// a multiple-range entry was saved as a single range due to output format
#define	rangeMultipleSavedAsSingleError		49

// cell reference out of the boundaries supported by output format
#define	cellBeyondSheetLimitsError			50

// the storage procedure was interupted by an AddIn
#define saveBlockedByAddInError				51

// the storage procedure was interupted by an AddIn
#define entryBlockedByAddInError			52

// find-and-replace showed a find that returned the same cell that
// it was just replaced in
#define findAndReplaceWraparoundError		53

// tried to goto a hidden cell
#define gotoAHiddenCellError                54

// create a dde link with an invalid-cell as target
#define	invalidTargetError					55

// tried to open too many windows
#define openedTooManyWindowsError           56

#define	findStringNotFoundError				57
#define	dontSupportExcel5Error				58

#define noPrintersInstalledError			59

// must be updated to reflect the total number of errors supported by
// the system
#define MAXERRORNUMBER 59

// file system errors
#define fileNotFoundError 200
#define pathNotFoundError 201
#define tooManyOpenFilesError 202
#define fileAccessDeniedError 203
#define invalidFileAccessError 204
#define notDosDiskError 205
#define fileSharingViolationError 206
#define fileSharingBufferError 207
#define cannotMakeFileError 208
#define fileInvalidParameterError 209
#define deviceInUseFileError 210
#define driveLockedError 211
#define openFailedError 212
#define diskFullError 213
#define filenameExceededRangeError 214
#define pipeBusyError 215
#define invalidFileHandleError 216
#define writeProtectError 217
#define writeFaultError 218
#define lockViolationFileError 219
#define brokenPipeError 220
#define moreDataFileError 221
#define unknownFileTypeError 222
#define unsupportedFileTypeError 223
#define invalidPasswordError	224
#define mismatchChangePasswordError 225
#define undefinedError 226
#define noFM3File		227		// no .FM3 file found for importing
#define ddeOpenFailedError 228	// dde tried to open a file which Mesa couldn't find
// a series of REXX errors
#define progUnreadableRexxError         403
#define progInteruptedRexxError         404
#define machineResExhaustedRexxError     405
#define unmatchedQuoteRexxError            406
#define whenExpectedRexxError            407
#define unexpectedThenRexxError            408
#define unexpectedWhenRexxError            409
#define unexpectedEndRexxError            410
#define controlStackFullRexxError        411
#define invalidCharRexxError            413
#define incompleteDoRexxError            414
#define invalidHexxRexxError            415
#define labelNotFoundRexxError            416
#define unexpectedProcRexxError            417
#define thenExpectedRexxError            418
#define stringExpectedRexxError            419
#define symbolExpectedRexxError            420
#define invalidDataRexxError            421
#define invalidCharStrRexxError            423
#define invalidTraceRexxError            424
#define invalidSubkeyRexxError            425
#define invalidNumberRexxError            426
#define invalidDoRexxError                427
#define invalidLeaveRexxError            428
#define envNameTooLongRexxError            429
#define nameTooLongRexxError            430
#define badNameRexxError                431
#define invalidResultRexxError            433
#define badLogicalValRexxError            434
#define invalidExpRexxError                435
#define unmatchedParenRexxError            436
#define unexpectedParenRexxError        437
#define invalidTemplateRexxError        438
#define stackOverflowRexxError            439
#define incorrectCallRexxError            440
#define badArithmaticRexxError            441
#define overflowRexxError                442
#define routineNotFoundRexxError        443
#define noReturnRexxError                444
#define noDataSpecRexxError                445
#define invalidVarRexxError                446
#define unexpectedLabelRexxError        447
#define systemServFailureRexxError        448
#define interpretRexxError                449


// ifndef _MH_exception_num
#endif
