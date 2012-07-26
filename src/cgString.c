#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdarg.h>
#include"cgString.h"
#include"cgAppState.h"

cgString* cgString__new(const char* value) {
    cgString* this = malloc(sizeof(char) * (strlen(value) + 1));
    if (this != NULL)
        strcpy(this, value);
    else
        cgAppState_THROW(cgAppState__getInstance(), Severity_error, cgExceptionID_CannotAllocate, "unable to allocate cgString for '%s'", value);
    return this;
}
cgString* cgString__newFromLengthAndPreset(unsigned int length, const char preset) {
    cgString* this = malloc(sizeof(char) * (length + 1));
    if (this != NULL) {
        memset(this, preset, length);
        *(this + length) = '\0';
    } else
        cgAppState_THROW(cgAppState__getInstance(), Severity_error, cgExceptionID_CannotAllocate, "unable to allocate cgString");
    return this;
}
cgString* cgString__newWithSprintf(const char* fmt, ...) {
    char* mystrbuf = NULL;
    va_list args;
    va_start(args, fmt);
    int rv = vasprintf(&mystrbuf, fmt, args);
    if (rv < 0)
        cgAppState_THROW(cgAppState__getInstance(), Severity_fatal, cgExceptionID_GeneralFatalException, "unable to print via vsprintf (fmt '%s')", fmt);
    va_end(args);
    return mystrbuf;
}
cgString* cgString_clone(const cgString* this) {
    return cgString__new((const char*)this);
}
void cgString_delete(cgString* this) {
    free(this);
}
void cgString_deleteAll(cgString* item, ...) {
    va_list args;
    va_start(args, item);
    while (item != NULL) {
        cgString_delete(item);
        item = va_arg(args, cgString*);
    }
    va_end(args);
}
char* cgString_toVector(const cgString* this) {
    return strdup(this);
}
int cgString__compare(const cgString* s1, const cgString* s2) {
    return (strcmp(s1, s2));
}
bool cgString_isEqual(const cgString* this, const cgString* that) {
    return (strcmp(this, that) == 0);
}
cgString* cgString_append(cgString* this, const cgString* that) {
    cgString* newString = cgString__newFromLengthAndPreset(strlen(this) + strlen(that) + 1, '\0');
    if (newString == NULL)
        cgAppState_THROW(cgAppState__getInstance(), Severity_fatal, cgExceptionID_GeneralFatalException, "unable to allocate new string via cgString__newFromLengthAndPreset");
	strcpy(newString, this);
    strcat(newString, that);
	return newString;
}
/*
 * append a string in-place
 */
cgString* cgString_append_I(cgString* this, const cgString* that) {
    this = realloc(this, strlen(this) + strlen(that) + 1);
    if (this == NULL)
        cgAppState_THROW(cgAppState__getInstance(), Severity_fatal, cgExceptionID_GeneralFatalException, "unable to allocate new string for appending");
    strcat(this, that);
    return this;
}
cgString* cgString_appendWithSprintf_I(cgString* this, const cgString* fmt, ...) {
    cgString* newString = NULL;
    va_list args;
    va_start(args, fmt);
    int rv = vasprintf(&newString, fmt, args);
    if (rv < 0)
        cgAppState_THROW(cgAppState__getInstance(), Severity_fatal, cgExceptionID_GeneralFatalException, "unable to print via vasprintf (fmt '%s')", fmt);
    this = cgString_append_I(this, newString);
    va_end(args);
    cgString_delete(newString);
    return this;
}
size_t cgString_getSize(const cgString* this) {
    return strlen(this);
}
size_t cgString_getByteSize(const cgString* this) {
    return strlen(this);
}
cgString* cgString_createSubstring(const cgString* this, unsigned startIndex, unsigned length) {
    if (startIndex >= strlen(this)) {
        cgAppState_THROW(cgAppState__getInstance(), Severity_notice, cgExceptionID_StringError, "startIndex %u >= strlen %u in createSubstring", startIndex, strlen(this));
        return NULL;
    }
    if (startIndex + length > strlen(this))
        length = strlen(this) - startIndex;
    cgString* newString = cgString__newFromLengthAndPreset(length, '\0');
    strncpy(newString, (this + startIndex), length);
    return newString;
}

char cgString_getCharAt(const cgString* this, unsigned index) {
    if (index >= strlen(this)) {
        cgAppState_THROW(cgAppState__getInstance(), Severity_notice, cgExceptionID_StringError, "index %u >= strlen %u", index, strlen(this));
        return '\0';
    }
    return this[index];
}
