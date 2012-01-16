#include<stdlib.h>
#include"Integer.h"
#include"CGAppState.h"

Integer* Integer__new(CGAppState* appState, const int value) {
    Integer* this = malloc(sizeof(*this));
    if (this != NULL)
        *this = value;
    else
        CGAppState_throwException(appState, Exception__new(Severity_error, ExceptionID_CannotAllocate, "unable to allocate Integer for '%i'", value));
    return this;
}
Integer* Integer_clone(CGAppState* appState, const Integer* this) {
    return Integer__new(appState, *this);
}
void Integer_delete(CGAppState* appState, Integer* this) {
    free(this);
}
int Integer_toInt(CGAppState* appState, const Integer* this) {
    return *this;
}
int Integer__compare(CGAppState* appState, const Integer* i1, const Integer* i2) {
    return ((*i1 < *i2) ? -1 : (*i1 == *i2) ? 0 : 1);
}
