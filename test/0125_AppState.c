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

#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include"cgAppState.h"

cgAppState* appState = NULL;

void testNewDelete() {
    printf("%s... ", __func__);
    cgAppState__init(__FILE__);
    appState = cgAppState__getInstance();
    assert(appState != NULL);
    printf("ok -- ");
}

void testExceptionNewDelete() {
    printf("%s... ", __func__);

    cgException* e = cgException__new(Severity_error, cgExceptionID_GeneralFatalException, "testing");
    assert(e != NULL);
    assert(cgException_getId(e) == cgExceptionID_GeneralFatalException);
    assert(cgException_getSeverity(e) == Severity_error);
    char *msg = cgException_getMsg(e);
    assert(!strcmp(msg, "testing"));
    free(msg);
    cgException_delete(e);

    e = cgException__new(Severity_error, cgExceptionID_GeneralFatalException, NULL);
    assert(cgException_getMsg(e) == NULL);
    cgException_delete(e);

    printf("ok -- ");
}
void testThrowCatch() {
    printf("%s... ", __func__);
    assert(cgAppState_isExceptionRaised(appState) == false);
    cgException* e = cgException__new(Severity_error, cgExceptionID_GeneralFatalException, "testing");
    cgAppState_throwException(appState, e);
    assert(cgAppState_isExceptionRaised(appState) == true);
    assert(cgAppState_isExceptionRaisedWithID(appState, cgExceptionID_CannotAllocate) == false);
    assert(cgAppState_isExceptionRaisedWithID(appState, cgExceptionID_GeneralFatalException) == true);
    assert(cgAppState_getException(appState) == e);
    assert(cgAppState_catchExceptionWithID(appState, cgExceptionID_CannotAllocate) == NULL);
    assert(cgAppState_isExceptionRaisedWithID(appState, cgExceptionID_GeneralFatalException) == true);
    assert(cgAppState_catchExceptionWithID(appState, cgExceptionID_GeneralFatalException) == e);
    assert(cgAppState_catchExceptionWithID(appState, cgExceptionID_GeneralFatalException) == NULL);
    e = cgException__new(Severity_error, cgExceptionID_GeneralFatalException, "testing");
    cgAppState_throwException(appState, e);
    assert(cgAppState_catchException(appState) == e);
    assert(cgAppState_catchException(appState) == NULL);
    cgException_delete(e);
    e = cgException__new(Severity_error, cgExceptionID_GeneralFatalException, "testing");
    cgAppState_throwException(appState, e);
    assert(cgAppState_isExceptionRaisedWithSeverity(appState, Severity_none) == false);
    assert(cgAppState_isExceptionRaisedWithSeverity(appState, Severity_error) == true);
    assert(cgAppState_catchExceptionWithSeverity(appState, Severity_none) == NULL);
    assert(cgAppState_catchExceptionWithSeverity(appState, Severity_error) == e);
    printf("ok -- ");
}

void testAssert() {
    printf("%s... ", __func__);
    assert(cgAppState_isExceptionRaised(appState) == false);
    cgException* e = cgException__new(Severity_error, cgExceptionID_GeneralFatalException, "testing");
    cgAppState_assert(appState, (1 == 0), e);
    assert(cgAppState_isExceptionRaised(appState) == true);
    assert(cgAppState_isExceptionRaisedWithID(appState, cgExceptionID_CannotAllocate) == false);
    assert(cgAppState_isExceptionRaisedWithID(appState, cgExceptionID_GeneralFatalException) == true);
    assert(cgAppState_getException(appState) == e);
    assert(cgAppState_catchExceptionWithID(appState, cgExceptionID_CannotAllocate) == NULL);
    assert(cgAppState_isExceptionRaisedWithID(appState, cgExceptionID_GeneralFatalException) == true);
    assert(cgAppState_catchExceptionWithID(appState, cgExceptionID_GeneralFatalException) == e);
    assert(cgAppState_catchExceptionWithID(appState, cgExceptionID_GeneralFatalException) == NULL);

    cgAppState_assert(appState, (1 == 1), e);
    assert(cgAppState_isExceptionRaised(appState) == false);

    cgException_delete(e);
    printf("ok -- ");
}

void testThrowCatchNoMsg() {
    printf("%s... ", __func__);

    assert(cgAppState_isExceptionRaised(appState) == false);
    cgException* e = cgException__new(Severity_error, cgExceptionID_GeneralFatalException, NULL);
    cgAppState_throwException(appState, e);
    assert(cgAppState_isExceptionRaised(appState) == true);
    assert(cgAppState_isExceptionRaisedWithID(appState, cgExceptionID_CannotAllocate) == false);
    assert(cgAppState_isExceptionRaisedWithID(appState, cgExceptionID_GeneralFatalException) == true);
    assert(cgAppState_getException(appState) == e);
    assert(cgAppState_catchExceptionWithID(appState, cgExceptionID_CannotAllocate) == NULL);
    assert(cgAppState_isExceptionRaisedWithID(appState, cgExceptionID_GeneralFatalException) == true);
    assert(cgAppState_catchExceptionWithID(appState, cgExceptionID_GeneralFatalException) == e);
    assert(cgAppState_catchExceptionWithID(appState, cgExceptionID_GeneralFatalException) == NULL);
    cgException_delete(e);

    printf("ok -- ");
}

void testReset() {
    printf("%s... ", __func__);

    assert(cgAppState_isExceptionRaised(appState) == false);
    cgException* e = cgException__new(Severity_error, cgExceptionID_GeneralFatalException, NULL);
    cgAppState_throwException(appState, e);
    assert(cgAppState_isExceptionRaised(appState) == true);

    cgAppState_reset(appState);
    assert(cgAppState_isExceptionRaised(appState) == false);

    printf("ok -- ");
}


int main() {
    printf("=== %s ===\n", __FILE__);

    testNewDelete();
    testExceptionNewDelete();
    testThrowCatch();
    testThrowCatchNoMsg();
    testAssert();
    testReset();

    printf("=== %s ok ===\n", __FILE__);
    return 0;
}

