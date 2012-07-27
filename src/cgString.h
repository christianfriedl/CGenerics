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

#ifndef _CGSTRING_H
#define _CGSTRING_H

#include<string.h>
#include"cgAppState.h"

typedef char cgString;

cgString *cgString__new(const char *value);

cgString *cgString__newFromLengthAndPreset(unsigned int length, const char preset);

cgString *cgString__newWithSprintf(const char *fmt, ...);

cgString *cgString_clone(const cgString * this);

void cgString_delete(cgString * this);

/* requires a sentinel NULL */
void cgString_deleteAll(cgString * item, ...);

char *cgString_toVector(const cgString * this);

int cgString__compare(const cgString * i1, const cgString * i2);

bool cgString_isEqual(const cgString * this, const cgString * that);

/*
 * append a string, returning a new string
 */
cgString *cgString_append(cgString * this, const cgString * that);

/*
 * append a string in-place
 */
cgString *cgString_append_I(cgString * this, const cgString * that);

cgString *cgString_appendWithSprintf_I(cgString * this, const cgString * fmt, ...);

cgString *cgString_appendChar_I(cgString * this, char ch);

cgString *cgString_insert_I(cgString * this, unsigned int pos, cgString * that);

cgString *cgString_insertChar_I(cgString * this, unsigned int pos, char ch);

cgString* cgString_replace_I(cgString*this, unsigned int pos, cgString* that);

size_t cgString_getSize(const cgString * this);

size_t cgString_getByteSize(const cgString * this);

cgString *cgString_createSubstring(const cgString * this, unsigned startIndex, unsigned length);

char cgString_getCharAt(const cgString * this, unsigned index);

/* TODO missing functions:
    - strchr
    - strtok
    - replaceAt
    - toUpper, toLower
*/
#endif
