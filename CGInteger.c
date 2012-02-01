#include<stdlib.h>
#include"CGInteger.h"
#include"CGAppState.h"

CGInteger* CGInteger__new(CGAppState* appState, const int value) {
    CGInteger* this = malloc(sizeof(*this));
    if (this != NULL)
        *this = value;
    else
        CGAppState_throwException(appState, CGException__new(Severity_error, CGExceptionID_CannotAllocate, "unable to allocate CGInteger for '%i'", value));
    return this;
}
CGInteger* CGInteger_clone(CGAppState* appState, const CGInteger* this) {
    return CGInteger__new(appState, *this);
}
void CGInteger_delete(CGAppState* appState, CGInteger* this) {
    free(this);
}
int CGInteger_toInt(CGAppState* appState, const CGInteger* this) {
    return *this;
}
int CGInteger__compare(CGAppState* appState, const CGInteger* i1, const CGInteger* i2) {
    return ((*i1 < *i2) ? -1 : (*i1 == *i2) ? 0 : 1);
}
