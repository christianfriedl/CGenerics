#ifndef _APPSTATE_H
#define _APPSTATE_H

#include"CGenerics.h"
#include"Exception.h"

typedef struct {
    Exception *exception;
} CGAppState;

CGAppState* CGAppState__new();
void CGAppState_delete(CGAppState* this);
void CGAppState_throwException(CGAppState* this, Exception* exception);
bool CGAppState_catchException(CGAppState* this);
bool CGAppState_catchExceptionWithID(CGAppState* this, int exceptionID);
bool CGAppState_catchExceptionWithSeverity(CGAppState* this, Severity severity);
bool CGAppState_isExceptionRaised(CGAppState* this);
bool CGAppState_isExceptionRaisedWithID(CGAppState* this, int exceptionID);
bool CGAppState_isExceptionRaisedWithSeverity(CGAppState* this, Severity severity);
Exception* CGAppState_getException(CGAppState* this);

#endif
