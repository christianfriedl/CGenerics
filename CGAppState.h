#ifndef _CGAPPSTATE_H
#define _CGAPPSTATE_H

#include"CGenerics.h"
#include"CGException.h"

typedef struct {
    const char* name;
    CGException *exception;
} CGAppState;

CGAppState* CGAppState__new(const char* name);
void CGAppState_delete(CGAppState* this);
void CGAppState_throwException(CGAppState* this, CGException* exception);
#define CGAppState_THROW(this, severity, id, ...) CGAppState_throwException((this), CGException__new((severity), (id), __VA_ARGS__))
bool CGAppState_catchAndDeleteException(CGAppState* this);
bool CGAppState_catchAndDeleteExceptionWithID(CGAppState* this, int exceptionID);
CGException* CGAppState_catchException(CGAppState* this);
CGException* CGAppState_catchExceptionWithID(CGAppState* this, int exceptionID);
CGException* CGAppState_catchExceptionWithSeverity(CGAppState* this, Severity severity);
bool CGAppState_isExceptionRaised(CGAppState* this);
bool CGAppState_isExceptionRaisedWithID(CGAppState* this, int exceptionID);
bool CGAppState_isExceptionRaisedWithSeverity(CGAppState* this, Severity severity);
CGException* CGAppState_getException(CGAppState* this);

#endif
