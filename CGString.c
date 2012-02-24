#include<string.h>
#include<stdlib.h>
#include"CGString.h"
#include"CGAppState.h"

CGString* CGString__new(CGAppState* appState, const char* value) {
    CGString* this = malloc(sizeof(char) * (strlen(value) + 1));
    if (this != NULL)
        strcpy(this, value);
    else
        CGAppState_throwException(appState, CGException__new(Severity_error, CGExceptionID_CannotAllocate, "unable to allocate CGString for '%s'", value));
    return this;
}
CGString* CGString__newFromLengthAndPreset(CGAppState* appState, unsigned int length, const char preset) {
    CGString* this = malloc(sizeof(char) * (length + 1));
    if (this != NULL) {
        memset(this, preset, length);
        *(this + length) = '\0';
    } else
        CGAppState_throwException(appState, CGException__new(Severity_error, CGExceptionID_CannotAllocate, "unable to allocate CGString"));
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
CGString* CGString_createSubstring(CGAppState* appState, const CGString* this, unsigned startIndex, unsigned length) {
    if (startIndex > strlen(this)) {
        CGAppState_throwException(appState, CGException__new(Severity_notice, CGExceptionID_StringError, "startIndex %u > strlen %u in createSubstring", startIndex, strlen(this)));
        return NULL;
    }
    if (startIndex + length > strlen(this))
        length = strlen(this) - startIndex;
    CGString* newString = CGString__newFromLengthAndPreset(appState, length, '\0');
    strncpy(newString, (this + startIndex), length);
    return newString;
}
