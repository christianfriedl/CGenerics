#ifndef _INTEGER_H
#define _INTEGER_H

#include"AppState.h"

typedef int Integer;

Integer* Integer__new(AppState* appState, const int value);
void Integer_delete(AppState* appState, Integer* this);
int Integer_toInt(AppState* appState, const Integer* this);
Integer* Integer_clone(AppState* appState, const Integer* this);

#endif
