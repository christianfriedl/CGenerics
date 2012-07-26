#include<stdlib.h>
#include"cgInteger.h"
#include"cgAppState.h"

cgInteger* cgInteger__new(const int value) {
    cgInteger* this = malloc(sizeof(*this));
    if (this != NULL)
        *this = value;
    else
        cgAppState_throwException(cgAppState__getInstance(), cgException__new(Severity_error, cgExceptionID_CannotAllocate, "unable to allocate cgInteger for '%i'", value));
    return this;
}
cgInteger* cgInteger_clone(const cgInteger* this) {
    return cgInteger__new(*this);
}
void cgInteger_delete(cgInteger* this) {
    free(this);
}
int cgInteger_toInt(const cgInteger* this) {
    return *this;
}
int cgInteger__compare(const cgInteger* i1, const cgInteger* i2) {
    return ((*i1 < *i2) ? -1 : (*i1 == *i2) ? 0 : 1);
}
