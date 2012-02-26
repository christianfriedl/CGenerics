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
char* CGString_toVector(const CGString* this);
int CGString__compare(const CGString* i1, const CGString* i2);
CGString* CGString_append(CGString* this, const CGString* that);
size_t CGString_getSize(const CGString* this);
CGString* CGString_createSubstring(const CGString* this, unsigned startIndex, unsigned length);


/* TODO missing functions:
    - strchr
    - strtok
    - insertAt
    - replaceAt
    - substring
    - toUpper, toLower
*/

#endif
