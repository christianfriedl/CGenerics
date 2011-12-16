#ifndef _APPSTATE_H
#define _APPSTATE_H

#include"CGenerics.h"
#include"Exception.h"

typedef struct {
    Exception *exception;
} AppState;

AppState* AppState__new();
void AppState_delete(AppState* this);
void AppState_throwException(AppState* this, Exception* exception);
void AppState_catchException(AppState* this);
bool AppState_catchExceptionWithID(AppState* this, int exceptionID);
bool AppState_isExceptionRaised(AppState* this);
bool AppState_isExceptionRaisedWithID(AppState* this, int exceptionID);
Exception* AppState_getException(AppState* this);

#endif
