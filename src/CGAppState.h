#ifndef _CGAPPSTATE_H
#define _CGAPPSTATE_H

#include"CGenerics.h"
#include"CGException.h"

typedef struct {
    const char* name;
    CGException *exception;
} CGAppState;

void CGAppState__init(const char* name);
void CGAppState__deInit();
CGAppState* CGAppState__getInstance();
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
/* sometimes it's useful to reset the whole AppState, e.g. in test suites */
void CGAppState_reset(CGAppState* this);

#endif
