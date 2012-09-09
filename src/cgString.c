/*
    =====================================================================
    CGenerics - Datatypes and Functions for Generic and OO Programming in C

    Copyright (C) 2012  Christian Friedl

    This file is part of CGenerics.

    CGenerics is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    CGenerics is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    =====================================================================
*/

#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdarg.h>
#include"cgString.h"
#include"cgAppState.h"

cgString *cgString__new(const char *value) {
    cgString *this = malloc(sizeof(char) * (strlen(value) + 1));

    if (this != NULL)
        strcpy(this, value);
    else
        cgAppState_THROW(cgAppState__getInstance(), Severity_error,
                         cgExceptionID_CannotAllocate, "unable to allocate cgString for '%s'", value);
    return this;
}
cgString *cgString__newFromLengthAndPreset(unsigned int length, const char preset) {
    cgString *this = malloc(sizeof(char) * (length + 1));

    if (this != NULL) {
        memset(this, preset, length);
        *(this + length) = '\0';
    } else
        cgAppState_THROW(cgAppState__getInstance(), Severity_error, cgExceptionID_CannotAllocate, "unable to allocate cgString");
    return this;
}
cgString *cgString__newWithSprintf(const char *fmt, ...) {
    char *mystrbuf = NULL;

    va_list args;

    va_start(args, fmt);
    int rv = vasprintf(&mystrbuf, fmt, args);

    if (rv < 0)
        cgAppState_THROW(cgAppState__getInstance(), Severity_fatal, cgExceptionID_GeneralFatalException,
                         "unable to print via vsprintf (fmt '%s')", fmt);
    va_end(args);
    return mystrbuf;
}
cgString *cgString_clone(const cgString * this) {
    return cgString__new((const char *)this);
}
void cgString_delete(cgString * this) {
    free(this);
}
void cgString_deleteAll(cgString * item, ...) {
    va_list args;

    va_start(args, item);
    while (item != NULL) {
        cgString_delete(item);
        item = va_arg(args, cgString *);
    }
    va_end(args);
}
char *cgString_toVector(const cgString * this) {
    return strdup(this);
}
int cgString__compare(const cgString * s1, const cgString * s2) {
    return (strcmp(s1, s2));
}
bool cgString_isEqual(const cgString * this, const cgString * that) {
    return (strcmp(this, that) == 0);
}
cgString *cgString_append(cgString * this, const cgString * that) {
    cgString *newString = cgString__newFromLengthAndPreset(strlen(this) + strlen(that) + 1, '\0');

    if (newString == NULL)
        cgAppState_THROW(cgAppState__getInstance(), Severity_fatal,
                         cgExceptionID_GeneralFatalException,
                         "unable to allocate new string via cgString__newFromLengthAndPreset");
    strcpy(newString, this);
    strcat(newString, that);
    return newString;
}

/**
 * append a string in-place
 * note: the in-place functions do return a pointer because realloc may return a pointer to a new location
 */
cgString *cgString_append_I(cgString * this, const cgString * that) {
    this = realloc(this, strlen(this) + strlen(that) + 1);
    if (this == NULL)
        cgAppState_THROW(cgAppState__getInstance(), Severity_fatal,
                         cgExceptionID_GeneralFatalException, "unable to allocate new string for appending");
    strcat(this, that);
    return this;
}

/*
 * note: the in-place functions do return a pointer because realloc may return a pointer to a new location
 */
cgString *cgString_appendWithSprintf_I(cgString * this, const cgString * fmt, ...) {
    cgString *newString = NULL;

    va_list args;

    va_start(args, fmt);
    int rv = vasprintf(&newString, fmt, args);

    if (rv < 0)
        cgAppState_THROW(cgAppState__getInstance(), Severity_fatal,
                         cgExceptionID_GeneralFatalException, "unable to print via vasprintf (fmt '%s')", fmt);
    this = cgString_append_I(this, newString);
    va_end(args);
    cgString_delete(newString);
    return this;
}

/** 
 * append a char in-place
 * note: the in-place functions do return a pointer because realloc may return a pointer to a new location
 */
cgString *cgString_appendChar_I(cgString * this, char ch) {
    cgString *s = cgString__newWithSprintf("%c", ch);

    cgString_append_I(this, s);
    cgString_delete(s);
    return this;
}

/** 
 * insert a string in-place before pos
 * note: the in-place functions do return a pointer because realloc may return a pointer to a new location
 */
cgString *cgString_insert_I(cgString * this, unsigned int pos, cgString * that) {
    if (pos > cgString_getByteSize(this)) {
        cgAppState_THROW(cgAppState__getInstance(), Severity_notice,
                         cgExceptionID_StringError, "%u > strlen (%u) ", pos, cgString_getByteSize(this));
        return this;
    } else if (pos == cgString_getByteSize(this))
        return cgString_append_I(this, that);

    this = realloc(this, cgString_getByteSize(this) + cgString_getByteSize(that) + 1);
    if (this == NULL)
        cgAppState_THROW(cgAppState__getInstance(), Severity_fatal, cgExceptionID_StringError, "unable to re-allocate string");
    memmove(this + pos + cgString_getByteSize(that), this + pos, cgString_getByteSize(this) - pos + 1); /* make room */
    memcpy(this + pos, that, cgString_getByteSize(that));   /* copy source to dest */
    return this;
}

cgString *cgString_replace_I(cgString * this, unsigned int pos, cgString * that) {
    if (pos > cgString_getByteSize(this)) {
        cgAppState_THROW(cgAppState__getInstance(), Severity_notice,
                         cgExceptionID_StringError, "%u > strlen (%u) ", pos, cgString_getByteSize(this));
        return this;
    } else if (pos == cgString_getByteSize(this))
        return cgString_append_I(this, that);

    if (pos + cgString_getByteSize(that) > cgString_getByteSize(this)) {
        this = realloc(this, cgString_getByteSize(this) + cgString_getByteSize(that) + 1);
        memcpy(this + pos, that, cgString_getByteSize(that) + 1);   /* copy source to dest */
    } else
        memcpy(this + pos, that, cgString_getByteSize(that));   /* copy source to dest */
    return this;
}

/* TODO test */
cgString *cgString_replaceN_I(cgString * this, unsigned int pos, unsigned int len, cgString * that) {
    cgString* s;
    if (len < cgString_getByteSize(that)) {
        s = cgString_clone(that);
        s[len] = '\0';
        this = cgString_replace_I(this, pos, s);
        cgString_delete(s);
    } else
        this = cgString_replace_I(this, pos, that);
    return this;
}

/* delete N chars starting at position pos
 */
cgString* cgString_removeN_I(cgString* this, unsigned int pos, unsigned int n) {
    n = min(n, cgString_getByteSize(this) - pos);
    memmove(this + pos, this + pos + n, cgString_getByteSize(this) - pos - n + 1);
    return this;
}

cgString *cgString_insertChar_I(cgString * this, unsigned int pos, char ch) {
    cgString *s = cgString__newWithSprintf("%c", ch);

    this = cgString_insert_I(this, pos, s);
    cgString_delete(s);
    return this;
}

size_t cgString_getSize(const cgString * this) {
    return strlen(this);
}
size_t cgString_getByteSize(const cgString * this) {
    return strlen(this);
}
cgString *cgString_createSubstring(const cgString * this, unsigned startIndex, unsigned length) {
    if (startIndex >= strlen(this)) {
        cgAppState_THROW(cgAppState__getInstance(), Severity_notice,
                         cgExceptionID_StringError, "startIndex %u >= strlen %u in createSubstring", startIndex, strlen(this));
        return NULL;
    }
    if (startIndex + length > strlen(this))
        length = strlen(this) - startIndex;
    cgString *newString = cgString__newFromLengthAndPreset(length, '\0');

    strncpy(newString, (this + startIndex), length);
    return newString;
}

char cgString_getCharAt(const cgString * this, unsigned index) {
    if (index >= strlen(this)) {
        cgAppState_THROW(cgAppState__getInstance(), Severity_notice,
                         cgExceptionID_StringError, "index %u >= strlen %u", index, strlen(this));
        return '\0';
    }
    return this[index];
}
