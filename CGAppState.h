#ifndef _APPSTATE_H
#define _APPSTATE_H

#include"CGenerics.h"
#include"CGException.h"

typedef struct {
    CGException *exception;
} CGAppState;

CGAppState* CGAppState__new();
void CGAppState_delete(CGAppState* this);
void CGAppState_throwException(CGAppState* this, CGException* exception);
bool CGAppState_catchException(CGAppState* this);
bool CGAppState_catchExceptionWithID(CGAppState* this, int exceptionID);
bool CGAppState_catchExceptionWithSeverity(CGAppState* this, Severity severity);
bool CGAppState_isExceptionRaised(CGAppState* this);
bool CGAppState_isExceptionRaisedWithID(CGAppState* this, int exceptionID);
bool CGAppState_isExceptionRaisedWithSeverity(CGAppState* this, Severity severity);
CGException* CGAppState_getException(CGAppState* this);

#endif
