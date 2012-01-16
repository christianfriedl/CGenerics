#include<stdlib.h>
#include"AppState.h"

AppState* AppState__new() {
    AppState* this = malloc(sizeof(*this));
    if (this) {
        this->exception = NULL;
    } else
        AppState_throwException(this, &GeneralFatalException);
    return this;
}

void AppState_delete(AppState* this) {
    if (this->exception != NULL)
        Exception_delete(this->exception);
    free(this);
}

void AppState_throwException(AppState* this, Exception* exception) {
    Exception_log(exception);
    if (exception->severity == Severity_fatal) {
        AppState_delete(this); /* yeah */
        abort();
    }

    this->exception = exception;
}

bool AppState_catchException(AppState* this) {
    if (AppState_isExceptionRaised(this)) {
        Exception_delete(this->exception);
        this->exception = NULL;
        return true;
    } else
        return false;
}

bool AppState_isExceptionRaised(AppState* this) {
    return (this->exception != NULL ? true: false);
}
bool AppState_isExceptionRaisedWithID(AppState* this, int exceptionID) {
    return ((this->exception != NULL && this->exception->id == exceptionID) ? true : false);
}
bool AppState_catchExceptionWithID(AppState* this, int exceptionID) {
    if (this->exception != NULL && this->exception->id == exceptionID) {
        AppState_catchException(this);
        return true;
    }
    return false;
}

Exception* AppState_getException(AppState* this) {
    return this->exception;
}
