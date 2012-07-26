#ifndef _CGAPPSTATE_H
#define _CGAPPSTATE_H

#include"cgenerics.h"
#include"cgException.h"

typedef struct {
    const char* name;
    cgException *exception;
} cgAppState;

void cgAppState__init(const char* name);
void cgAppState__deInit();
cgAppState* cgAppState__getInstance();
void cgAppState_throwException(cgAppState* this, cgException* exception);
#define cgAppState_THROW(this, severity, id, ...) cgAppState_throwException((this), cgException__newWithMetadata((severity), (id), __FILE__, __func__, __LINE__, __VA_ARGS__))
bool cgAppState_catchAndDeleteException(cgAppState* this);
bool cgAppState_catchAndDeleteExceptionWithID(cgAppState* this, int exceptionID);
cgException* cgAppState_catchException(cgAppState* this);
cgException* cgAppState_catchExceptionWithID(cgAppState* this, int exceptionID);
cgException* cgAppState_catchExceptionWithSeverity(cgAppState* this, Severity severity);
bool cgAppState_isExceptionRaised(cgAppState* this);
bool cgAppState_isExceptionRaisedWithID(cgAppState* this, int exceptionID);
bool cgAppState_isExceptionRaisedWithSeverity(cgAppState* this, Severity severity);
cgException* cgAppState_getException(cgAppState* this);
/* sometimes it's useful to reset the whole AppState, e.g. in test suites */
void cgAppState_reset(cgAppState* this);

#endif
