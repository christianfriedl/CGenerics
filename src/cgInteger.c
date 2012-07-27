/*
    =====================================================================
    CGenerics - Datatypes and Functions for Generic and OO Programming in C

    Copyright (C) 2012  Christian Friedl

    This file is part of CGenerics.

    CGenerics is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    CGenerics is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    =====================================================================
*/

#include<stdlib.h>
#include"cgInteger.h"
#include"cgAppState.h"

cgInteger *cgInteger__new(const int value) {
    cgInteger *this = malloc(sizeof(*this));

    if (this != NULL)
        *this = value;
    else
        cgAppState_throwException(cgAppState__getInstance(),
                                  cgException__new(Severity_error, cgExceptionID_CannotAllocate,
                                                   "unable to allocate cgInteger for '%i'", value));
    return this;
}
cgInteger *cgInteger_clone(const cgInteger * this) {
    return cgInteger__new(*this);
}
void cgInteger_delete(cgInteger * this) {
    free(this);
}
int cgInteger_toInt(const cgInteger * this) {
    return *this;
}
int cgInteger__compare(const cgInteger * i1, const cgInteger * i2) {
    return ((*i1 < *i2) ? -1 : (*i1 == *i2) ? 0 : 1);
}
