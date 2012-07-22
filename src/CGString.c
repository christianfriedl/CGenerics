#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdarg.h>
#include"CGString.h"
#include"CGAppState.h"

CGString* CGString__new(const char* value) {
    CGString* this = malloc(sizeof(char) * (strlen(value) + 1));
    if (this != NULL)
        strcpy(this, value);
    else
        CGAppState_THROW(CGAppState__getInstance(), Severity_error, CGExceptionID_CannotAllocate, "unable to allocate CGString for '%s'", value);
    return this;
}
CGString* CGString__newFromLengthAndPreset(unsigned int length, const char preset) {
    CGString* this = malloc(sizeof(char) * (length + 1));
    if (this != NULL) {
        memset(this, preset, length);
        *(this + length) = '\0';
    } else
        CGAppState_THROW(CGAppState__getInstance(), Severity_error, CGExceptionID_CannotAllocate, "unable to allocate CGString");
    return this;
}
CGString* CGString__newWithSprintf(const char* fmt, ...) {
    char* mystrbuf = NULL;
    va_list args;
    va_start(args, fmt);
    int rv = vasprintf(&mystrbuf, fmt, args);
    if (rv < 0)
        CGAppState_THROW(CGAppState__getInstance(), Severity_fatal, CGExceptionID_GeneralFatalException, "unable to print via vsprintf (fmt '%s')", fmt);
    va_end(args);
    return mystrbuf;
}
CGString* CGString_clone(const CGString* this) {
    return CGString__new((const char*)this);
}
void CGString_delete(CGString* this) {
    free(this);
}
void CGString_deleteAll(CGString* item, ...) {
    va_list args;
    va_start(args, item);
    while (item != NULL) {
        CGString_delete(item);
        item = va_arg(args, CGString*);
    }
    va_end(args);
}
char* CGString_toVector(const CGString* this) {
    return strdup(this);
}
int CGString__compare(const CGString* s1, const CGString* s2) {
    return (strcmp(s1, s2));
}
CGString* CGString_append(CGString* this, const CGString* that) {
    CGString* newString = CGString__newFromLengthAndPreset(strlen(this) + strlen(that) + 1, '\0');
    if (newString == NULL)
        CGAppState_THROW(CGAppState__getInstance(), Severity_fatal, CGExceptionID_GeneralFatalException, "unable to allocate new string via CGString__newFromLengthAndPreset");
	strcpy(newString, this);
    strcat(newString, that);
	return newString;
}
/*
 * append a string in-place
 */
CGString* CGString_append_I(CGString* this, const CGString* that) {
    this = realloc(this, strlen(this) + strlen(that) + 1);
    if (this == NULL)
        CGAppState_THROW(CGAppState__getInstance(), Severity_fatal, CGExceptionID_GeneralFatalException, "unable to allocate new string for appending");
    strcat(this, that);
    return this;
}
CGString* CGString_appendWithSprintf_I(CGString* this, const CGString* fmt, ...) {
    CGString* newString = NULL;
    va_list args;
    va_start(args, fmt);
    int rv = vasprintf(&newString, fmt, args);
    if (rv < 0)
        CGAppState_THROW(CGAppState__getInstance(), Severity_fatal, CGExceptionID_GeneralFatalException, "unable to print via vasprintf (fmt '%s')", fmt);
    this = CGString_append_I(this, newString);
    va_end(args);
    CGString_delete(newString);
    return this;
}
size_t CGString_getSize(const CGString* this) {
    return strlen(this);
}
CGString* CGString_createSubstring(const CGString* this, unsigned startIndex, unsigned length) {
    if (startIndex >= strlen(this)) {
        CGAppState_THROW(CGAppState__getInstance(), Severity_notice, CGExceptionID_StringError, "startIndex %u >= strlen %u in createSubstring", startIndex, strlen(this));
        return NULL;
    }
    if (startIndex + length > strlen(this))
        length = strlen(this) - startIndex;
    CGString* newString = CGString__newFromLengthAndPreset(length, '\0');
    strncpy(newString, (this + startIndex), length);
    return newString;
}

char CGString_getCharAt(const CGString* this, unsigned index) {
    if (index >= strlen(this)) {
        CGAppState_THROW(CGAppState__getInstance(), Severity_notice, CGExceptionID_StringError, "index %u >= strlen %u", index, strlen(this));
        return '\0';
    }
    return this[index];
}
