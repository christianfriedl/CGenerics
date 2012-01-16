#include<stdlib.h>
#include"CGString.h"
#include"CGAppState.h"

CGString* CGString__new(CGAppState* appState, const char* value) {
    CGString* this = malloc(sizeof(*this));
    if (this != NULL) {
        this->vector = malloc(sizeof(char) * (strlen(value) + 1));
        if (this->vector != NULL)
            strcpy(this->vector, value);
        else
            CGAppState_throwException(appState, Exception__new(Severity_error, ExceptionID_CannotAllocate, "unable to allocate CGString vector for '%s'", value));
    } else
        CGAppState_throwException(appState, Exception__new(Severity_error, ExceptionID_CannotAllocate, "unable to allocate CGString for '%s'", value));
    return this;
}
CGString* CGString_clone(CGAppState* appState, const CGString* this) {
    return CGString__new(appState, (const char*)this->vector);
}
void CGString_delete(CGAppState* appState, CGString* this) {
    free(this->vector);
    free(this);
}
char* CGString_toVector(CGAppState* appState, const CGString* this) {
    return strdup(this->vector);
}
int CGString__compare(CGAppState* appState, const CGString* s1, const CGString* s2) {
    return (strcmp(s1->vector, s2->vector));
}
