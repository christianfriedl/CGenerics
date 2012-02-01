#include<stdlib.h>
#include"CGAppState.h"

CGAppState* CGAppState__new() {
    CGAppState* this = malloc(sizeof(*this));
    if (this) {
        this->exception = NULL;
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
    CGException_log(exception);
    if (exception->severity == Severity_fatal) {
        CGAppState_delete(this); /* yeah */
        abort();
    }

    this->exception = exception;
}

bool CGAppState_catchException(CGAppState* this) {
    if (CGAppState_isExceptionRaised(this)) {
        CGException_delete(this->exception);
        this->exception = NULL;
        return true;
    } else
        return false;
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
bool CGAppState_catchExceptionWithID(CGAppState* this, int exceptionID) {
    if (this->exception != NULL && this->exception->id == exceptionID) {
        CGAppState_catchException(this);
        return true;
    }
    return false;
}

bool CGAppState_catchExceptionWithSeverity(CGAppState* this, Severity severity) {
    if (this->exception != NULL && this->exception->severity == severity) {
        CGAppState_catchException(this);
        return true;
    }
    return false;
}

CGException* CGAppState_getException(CGAppState* this) {
    return this->exception;
}
