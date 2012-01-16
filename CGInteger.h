#ifndef _INTEGER_H
#define _INTEGER_H

#include"CGAppState.h"

typedef int CGInteger;

CGInteger* CGInteger__new(CGAppState* appState, const int value);
CGInteger* CGInteger_clone(CGAppState* appState, const CGInteger* this);
void CGInteger_delete(CGAppState* appState, CGInteger* this);
int CGInteger_toInt(CGAppState* appState, const CGInteger* this);
int CGInteger__compare(CGAppState* appState, const CGInteger* i1, const CGInteger* i2);

#endif
