#ifndef _CGSTRING_H
#define _CGSTRING_H

#include<string.h>
#include"CGAppState.h"

typedef char CGString;

CGString* CGString__new(CGAppState* appState, const char* value);
CGString* CGString__newFromLengthAndPreset(CGAppState* appState, unsigned int length, const char preset);
CGString* CGString__newWithSprintf(CGAppState* appState, const char* fmt, ...);
CGString* CGString_clone(CGAppState* appState, const CGString* this);
void CGString_delete(CGAppState* appState, CGString* this);
char* CGString_toVector(CGAppState* appState, const CGString* this);
int CGString__compare(CGAppState* appState, const CGString* i1, const CGString* i2);
void CGString_append(CGAppState* appState, CGString* this, const CGString* that);
size_t CGString_getSize(CGAppState* appState, const CGString* this);
CGString* CGString_createSubstring(CGAppState* appState, const CGString* this, unsigned startIndex, unsigned length);


/* TODO missing functions:
    - strchr
    - strtok
    - insertAt
    - replaceAt
    - substring
    - toUpper, toLower
*/

#endif
