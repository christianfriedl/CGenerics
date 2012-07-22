#ifndef _CGSTRING_H
#define _CGSTRING_H

#include<string.h>
#include"CGAppState.h"

typedef char CGString;

CGString* CGString__new(const char* value);
CGString* CGString__newFromLengthAndPreset(unsigned int length, const char preset);
CGString* CGString__newWithSprintf(const char* fmt, ...);
CGString* CGString_clone(const CGString* this);
void CGString_delete(CGString* this);
/* requires a sentinel NULL */
void CGString_deleteAll(CGString* item, ...);
char* CGString_toVector(const CGString* this);
int CGString__compare(const CGString* i1, const CGString* i2);
/*
 * append a string, returning a new string
 */
CGString* CGString_append(CGString* this, const CGString* that);
/*
 * append a string in-place
 */
CGString* CGString_append_I(CGString* this, const CGString* that);
CGString* CGString_appendWithSprintf_I(CGString* this, const CGString* fmt, ...);
size_t CGString_getSize(const CGString* this);
CGString* CGString_createSubstring(const CGString* this, unsigned startIndex, unsigned length);
char CGString_getCharAt(const CGString* this, unsigned index);


/* TODO missing functions:
    - strchr
    - strtok
    - insertAt
    - replaceAt
    - toUpper, toLower
*/

#endif
