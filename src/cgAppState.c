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
#include<stdio.h>
#include"cgLogger.h"
#include"cgAppState.h"

static cgAppState *cgAppState__instance = NULL;

static cgAppState *cgAppState__new_(const char *name);

static void cgAppState_delete_(cgAppState * this);

void cgAppState__init(const char *name) {
    cgAppState__instance = cgAppState__new_(name);
}

void cgAppState__deInit() {
    if (cgAppState__instance != NULL)
        cgAppState_delete_(cgAppState__instance);
}

cgAppState *cgAppState__getInstance() {
    if (cgAppState__instance == NULL) {
        printf("cgAppState has to be initialized via cgAppState__init(). ABORTING PROGRAM DUE TO FATAL EXCEPTION.\n");
        abort();
    } else
        return cgAppState__instance;
}

static cgAppState *cgAppState__new_(const char *name) {
    cgAppState *this = malloc(sizeof(*this));

    if (this) {
        this->name = name;
        this->exception = NULL;

        cgLogger__init(name);
    } else {
        printf("Unable to initialize cgAppState. ABORTING PROGRAM DUE TO FATAL EXCEPTION.\n");
        abort();
    }
    return this;
}

static void cgAppState_delete_(cgAppState * this) {
    if (this->exception != NULL)
        cgException_delete(this->exception);
    free(this);
}

void cgAppState_throwException(cgAppState * this, cgException * exception) {
    if (cgException_getMsg(exception) != NULL)
        cgException_log(exception);
    if (exception->severity == Severity_fatal) {
        cgAppState_delete_(this);   /* yeah */
        printf("ABORTING PROGRAM DUE TO FATAL EXCEPTION.\n");
        abort();
    }

    this->exception = exception;
}

void cgAppState_assert(cgAppState * this, bool condition, cgException * exception) {
    if (!condition)
        cgAppState_throwException(this, exception);
}

bool cgAppState_catchAndDeleteException(cgAppState * this) {
    if (cgAppState_isExceptionRaised(this)) {
        cgException_delete(this->exception);
        this->exception = NULL;
        return true;
    } else
        return false;
}

bool cgAppState_catchAndDeleteExceptionWithID(cgAppState * this, int exceptionID) {
    if (cgAppState_isExceptionRaisedWithID(this, exceptionID)) {
        cgException_delete(this->exception);
        this->exception = NULL;
        return true;
    } else
        return false;
}

cgException *cgAppState_catchException(cgAppState * this) {
    if (cgAppState_isExceptionRaised(this)) {
        cgException *e = this->exception;

        this->exception = NULL;
        return e;
    } else
        return NULL;
}

bool cgAppState_isExceptionRaised(cgAppState * this) {
    return (this->exception != NULL ? true : false);
}
bool cgAppState_isExceptionRaisedWithID(cgAppState * this, int exceptionID) {
    return ((this->exception != NULL && this->exception->id == exceptionID) ? true : false);
}
bool cgAppState_isExceptionRaisedWithSeverity(cgAppState * this, Severity severity) {
    return ((this->exception != NULL && this->exception->severity == severity) ? true : false);
}
cgException *cgAppState_catchExceptionWithID(cgAppState * this, int exceptionID) {
    if (this->exception != NULL && this->exception->id == exceptionID) {
        return cgAppState_catchException(this);
    }
    return NULL;
}

cgException *cgAppState_catchExceptionWithSeverity(cgAppState * this, Severity severity) {
    if (this->exception != NULL && this->exception->severity == severity) {
        return cgAppState_catchException(this);
    }
    return NULL;
}

cgException *cgAppState_getException(cgAppState * this) {
    return this->exception;
}

void cgAppState_reset(cgAppState * this) {
    cgAppState_catchAndDeleteException(this);
}
