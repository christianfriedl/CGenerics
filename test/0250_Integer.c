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

#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include"cgAppState.h"
#include"cgInteger.h"

cgAppState* appState;

void testNewDelete() {
    printf("%s... ", __func__);
    cgInteger* i = cgInteger__new(1);
    assert(i != NULL);
    assert(*i == 1);
    cgInteger_delete(i);
    printf("ok -- ");
}
void testToInt() {
    printf("%s... ", __func__);
    cgInteger* i = cgInteger__new(1);
    assert(cgInteger_toInt(i) == 1);
    cgInteger_delete(i);
    printf("ok -- ");
}

void testClone() {
    printf("%s... ", __func__);
    cgInteger* i = cgInteger__new(1);
    cgInteger* i2 = cgInteger_clone(i);
    assert(i2 != NULL);
    assert(cgInteger_toInt(i2) == 1);
    cgInteger_delete(i);
    printf("ok -- ");
}


int main() {
    printf("=== %s ===\n", __FILE__);

    cgAppState__init(__FILE__);
    appState = cgAppState__getInstance();

    testNewDelete();
    testClone();
    testToInt();

    cgAppState__deInit();
    printf("=== %s ok ===\n", __FILE__);
    return 0;
}
