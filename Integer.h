#ifndef _INTEGER_H
#define _INTEGER_H

#include"CGAppState.h"

typedef int Integer;

Integer* Integer__new(CGAppState* appState, const int value);
Integer* Integer_clone(CGAppState* appState, const Integer* this);
void Integer_delete(CGAppState* appState, Integer* this);
int Integer_toInt(CGAppState* appState, const Integer* this);
int Integer__compare(CGAppState* appState, const Integer* i1, const Integer* i2);

#endif
