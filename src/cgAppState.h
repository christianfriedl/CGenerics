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

#ifndef _CGAPPSTATE_H
#define _CGAPPSTATE_H

#include"cgenerics.h"
#include"cgException.h"

typedef struct {
    const char *name;
    cgException *exception;
} cgAppState;

void cgAppState__init(const char *name);

void cgAppState__deInit();

cgAppState *cgAppState__getInstance();

void cgAppState_throwException(cgAppState * this, cgException * exception);

#define cgAppState_THROW(this, severity, id, ...) cgAppState_throwException((this), cgException__newWithMetadata((severity), (id), __FILE__, __func__, __LINE__, __VA_ARGS__))
bool cgAppState_catchAndDeleteException(cgAppState * this);

bool cgAppState_catchAndDeleteExceptionWithID(cgAppState * this, int exceptionID);

cgException *cgAppState_catchException(cgAppState * this);

cgException *cgAppState_catchExceptionWithID(cgAppState * this, int exceptionID);

cgException *cgAppState_catchExceptionWithSeverity(cgAppState * this, Severity severity);

bool cgAppState_isExceptionRaised(cgAppState * this);

bool cgAppState_isExceptionRaisedWithID(cgAppState * this, int exceptionID);

bool cgAppState_isExceptionRaisedWithSeverity(cgAppState * this, Severity severity);

cgException *cgAppState_getException(cgAppState * this);

/* sometimes it's useful to reset the whole AppState, e.g. in test suites */
void cgAppState_reset(cgAppState * this);
#endif
