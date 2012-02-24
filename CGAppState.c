#include<stdlib.h>
#include<stdio.h>
#include"CGLogger.h"
#include"CGAppState.h"

CGAppState* CGAppState__new(const char* name) {
    CGAppState* this = malloc(sizeof(*this));
    if (this) {
        this->name = name;
        this->exception = NULL;

        CGLogger__init(name);
    } else
        CGAppState_throwException(this, &CGGeneralFatalException);
    return this;
}

void CGAppState_delete(CGAppState* this) {
    if (this->exception != NULL)
        CGException_delete(this->exception);
    free(this);
}

void CGAppState_throwException(CGAppState* this, CGException* exception) {
    if (CGException_getMsg(exception) != NULL)
        CGException_log(exception);
    if (exception->severity == Severity_fatal) {
        CGAppState_delete(this); /* yeah */
        printf("ABORTING PROGRAM DUE TO FATAL EXCEPTION.\n");
        abort();
    }

    this->exception = exception;
}

bool CGAppState_catchAndDeleteException(CGAppState* this) {
    if (CGAppState_isExceptionRaised(this)) {
        CGException_delete(this->exception);
        this->exception = NULL;
        return true;
    } else
        return false;
}

bool CGAppState_catchAndDeleteExceptionWithID(CGAppState* this, int exceptionID) {
    if (CGAppState_isExceptionRaisedWithID(this, exceptionID)) {
        CGException_delete(this->exception);
        this->exception = NULL;
        return true;
    } else
        return false;
}

CGException* CGAppState_catchException(CGAppState* this) {
    if (CGAppState_isExceptionRaised(this)) {
        CGException* e = this->exception;
        this->exception = NULL;
        return e;
    } else
        return NULL;
}

bool CGAppState_isExceptionRaised(CGAppState* this) {
    return (this->exception != NULL ? true: false);
}
bool CGAppState_isExceptionRaisedWithID(CGAppState* this, int exceptionID) {
    return ((this->exception != NULL && this->exception->id == exceptionID) ? true : false);
}
bool CGAppState_isExceptionRaisedWithSeverity(CGAppState* this, Severity severity) {
    return ((this->exception != NULL && this->exception->severity == severity) ? true : false);
}
CGException* CGAppState_catchExceptionWithID(CGAppState* this, int exceptionID) {
    if (this->exception != NULL && this->exception->id == exceptionID) {
        return CGAppState_catchException(this);
    }
    return NULL;
}

CGException* CGAppState_catchExceptionWithSeverity(CGAppState* this, Severity severity) {
    if (this->exception != NULL && this->exception->severity == severity) {
        return CGAppState_catchException(this);
    }
    return NULL;
}

CGException* CGAppState_getException(CGAppState* this) {
    return this->exception;
}
