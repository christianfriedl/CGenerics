#ifndef _APPSTATE_H
#define _APPSTATE_H

#include"CGenerics.h"
#include"CGException.h"

typedef struct {
    CGException *exception;
} CGAppState;

CGAppState* CGAppState__new();
void CGAppState_delete(CGAppState* this);
void CGAppState_throwCGException(CGAppState* this, CGException* exception);
bool CGAppState_catchCGException(CGAppState* this);
bool CGAppState_catchCGExceptionWithID(CGAppState* this, int exceptionID);
bool CGAppState_catchCGExceptionWithSeverity(CGAppState* this, Severity severity);
bool CGAppState_isCGExceptionRaised(CGAppState* this);
bool CGAppState_isCGExceptionRaisedWithID(CGAppState* this, int exceptionID);
bool CGAppState_isCGExceptionRaisedWithSeverity(CGAppState* this, Severity severity);
CGException* CGAppState_getCGException(CGAppState* this);

#endif
