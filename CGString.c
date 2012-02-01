#include<stdlib.h>
#include"CGString.h"
#include"CGAppState.h"

CGString* CGString__new(CGAppState* appState, const char* value) {
    CGString* this = malloc(sizeof(*this));
    if (this != NULL) {
        this = malloc(sizeof(char) * (strlen(value) + 1));
        if (this != NULL)
            strcpy(this, value);
        else
            CGAppState_throwException(appState, CGException__new(Severity_error, CGExceptionID_CannotAllocate, "unable to allocate CGString vector for '%s'", value));
    } else
        CGAppState_throwException(appState, CGException__new(Severity_error, CGExceptionID_CannotAllocate, "unable to allocate CGString for '%s'", value));
    return this;
}
CGString* CGString_clone(CGAppState* appState, const CGString* this) {
    return CGString__new(appState, (const char*)this);
}
void CGString_delete(CGAppState* appState, CGString* this) {
    free(this);
}
char* CGString_toVector(CGAppState* appState, const CGString* this) {
    return strdup(this);
}
int CGString__compare(CGAppState* appState, const CGString* s1, const CGString* s2) {
    return (strcmp(s1, s2));
}
void CGString_append(CGAppState* appState, CGString* this, const CGString* that) {
    this = realloc(this, sizeof(char) * (strlen(this) + strlen(that) + 1));
    strcat(this, that);
}
size_t CGString_getSize(CGAppState* appState, const CGString* this) {
    return strlen(this);
}
