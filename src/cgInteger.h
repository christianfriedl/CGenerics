#ifndef _CGINTEGER_H
#define _CGINTEGER_H

#include"cgAppState.h"

typedef int cgInteger;

cgInteger* cgInteger__new(const int value);
cgInteger* cgInteger_clone(const cgInteger* this);
void cgInteger_delete(cgInteger* this);
int cgInteger_toInt(const cgInteger* this);
int cgInteger__compare(const cgInteger* i1, const cgInteger* i2);

#endif
