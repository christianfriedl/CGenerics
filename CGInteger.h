#ifndef _CGINTEGER_H
#define _CGINTEGER_H

#include"CGAppState.h"

typedef int CGInteger;

CGInteger* CGInteger__new(const int value);
CGInteger* CGInteger_clone(const CGInteger* this);
void CGInteger_delete(CGInteger* this);
int CGInteger_toInt(const CGInteger* this);
int CGInteger__compare(const CGInteger* i1, const CGInteger* i2);

#endif
