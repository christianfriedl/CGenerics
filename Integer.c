#include<stdlib.h>
#include"Integer.h"
#include"AppState.h"

Integer* Integer__new(AppState* appState, const int value) {
    Integer* this = malloc(sizeof(*this));
    if (this != NULL)
        *this = value;
    else
        AppState_throwException(appState, Exception__new(Severity_error, ExceptionID_CannotAllocate, "unable to allocate Integer for '%i'", value));
    return this;
}
void Integer_delete(AppState* appState, Integer* this) {
    free(this);
}
int Integer_toInt(AppState* appState, const Integer* this) {
    return *this;
}
Integer* Integer_clone(AppState* appState, const Integer* this) {
    return Integer__new(appState, *this);
}
