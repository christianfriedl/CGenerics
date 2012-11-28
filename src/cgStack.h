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

#ifndef _CGSTACK_H
#define _CGSTACK_H

/* NOMAKEMAN */

#include"cgArray.h"

/* callers */

#define cgStack__new(TYPENAME, initialCapacity) cgArrayOf##TYPENAME##__new((initialCapacity))
#define cgStack__newFromInitializerList(TYPENAME, ...) cgArrayOf##TYPENAME##__newFromInitializerList(__VA_ARGS__)
/**
 * cgStack_clone: returns a deep copy of the stack
 */
#define cgStack_clone(TYPENAME, stack) cgArrayOf##TYPENAME##_clone((stack))
#define cgStack_delete(TYPENAME, stack) cgArrayOf##TYPENAME##_delete((stack))
#define cgStack_deleteValues(TYPENAME, stack) cgArrayOf##TYPENAME##_deleteValues((stack))
#define cgStack_push(TYPENAME, stack, value) cgArrayOf##TYPENAME##_push((stack), (value))
#define cgStack_pop(TYPENAME, stack) cgArrayOf##TYPENAME##_pop((stack))
#define cgStack_getCapacity(TYPENAME, stack) cgArrayOf##TYPENAME##_getCapacity((stack))
#define cgStack_getSize(TYPENAME, stack) cgArrayOf##TYPENAME##_getSize((stack))

#endif
