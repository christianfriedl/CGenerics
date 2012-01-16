#include<stdlib.h>
#include"CGAppState.h"

CGAppState* CGAppState__new() {
    CGAppState* this = malloc(sizeof(*this));
    if (this) {
        this->exception = NULL;
    } else
        CGAppState_throwCGException(this, &GeneralFatalCGException);
    return this;
}

void CGAppState_delete(CGAppState* this) {
    if (this->exception != NULL)
        CGException_delete(this->exception);
    free(this);
}

void CGAppState_throwCGException(CGAppState* this, CGException* exception) {
    CGException_log(exception);
    if (exception->severity == Severity_fatal) {
        CGAppState_delete(this); /* yeah */
        abort();
    }

    this->exception = exception;
}

bool CGAppState_catchCGException(CGAppState* this) {
    if (CGAppState_isCGExceptionRaised(this)) {
        CGException_delete(this->exception);
        this->exception = NULL;
        return true;
    } else
        return false;
}

bool CGAppState_isCGExceptionRaised(CGAppState* this) {
    return (this->exception != NULL ? true: false);
}
bool CGAppState_isCGExceptionRaisedWithID(CGAppState* this, int exceptionID) {
    return ((this->exception != NULL && this->exception->id == exceptionID) ? true : false);
}
bool CGAppState_isCGExceptionRaisedWithSeverity(CGAppState* this, Severity severity) {
    return ((this->exception != NULL && this->exception->severity == severity) ? true : false);
}
bool CGAppState_catchCGExceptionWithID(CGAppState* this, int exceptionID) {
    if (this->exception != NULL && this->exception->id == exceptionID) {
        CGAppState_catchCGException(this);
        return true;
    }
    return false;
}

bool CGAppState_catchCGExceptionWithSeverity(CGAppState* this, Severity severity) {
    if (this->exception != NULL && this->exception->severity == severity) {
        CGAppState_catchCGException(this);
        return true;
    }
    return false;
}

CGException* CGAppState_getCGException(CGAppState* this) {
    return this->exception;
}
