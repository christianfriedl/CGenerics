#ifndef _STRING_H
#define _STRING_H

#include<string.h>
#include"CGAppState.h"

typedef struct {
    char* vector;
} CGString;

CGString* CGString__new(CGAppState* appState, const char* value);
CGString* CGString_clone(CGAppState* appState, const CGString* this);
void CGString_delete(CGAppState* appState, CGString* this);
char* CGString_toVector(CGAppState* appState, const CGString* this);
int CGString__compare(CGAppState* appState, const CGString* i1, const CGString* i2);

#endif
