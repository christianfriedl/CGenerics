#ifndef _CGSTRING_H
#define _CGSTRING_H

#include<string.h>
#include"cgAppState.h"

typedef char cgString;

cgString* cgString__new(const char* value);
cgString* cgString__newFromLengthAndPreset(unsigned int length, const char preset);
cgString* cgString__newWithSprintf(const char* fmt, ...);
cgString* cgString_clone(const cgString* this);
void cgString_delete(cgString* this);
/* requires a sentinel NULL */
void cgString_deleteAll(cgString* item, ...);
char* cgString_toVector(const cgString* this);
int cgString__compare(const cgString* i1, const cgString* i2);
bool cgString_isEqual(const cgString* this, const cgString* that);
/*
 * append a string, returning a new string
 */
cgString* cgString_append(cgString* this, const cgString* that);
/*
 * append a string in-place
 */
cgString* cgString_append_I(cgString* this, const cgString* that);
cgString* cgString_appendWithSprintf_I(cgString* this, const cgString* fmt, ...);
cgString* cgString_appendChar_I(cgString* this, char ch);
size_t cgString_getSize(const cgString* this);
size_t cgString_getByteSize(const cgString* this);
cgString* cgString_createSubstring(const cgString* this, unsigned startIndex, unsigned length);
char cgString_getCharAt(const cgString* this, unsigned index);


/* TODO missing functions:
    - strchr
    - strtok
    - insertAt
    - replaceAt
    - toUpper, toLower
*/

#endif
