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
#include"cgTree.h"

typedef int Int;

Int* Int__new(int value) {
    Int* this = malloc(sizeof(*this));
    /* TODO exception */
    *this = value;
    return this;
}
Int* Int_clone(Int* this) {
    return Int__new(*this);
}
void Int_delete(int* this) {
    free(this);
}

DECLARE_TREE_TYPE(Int)
DECLARE_TREE_FUNCS(Int)
DEFINE_TREE_FUNCS(Int)

cgAppState *appState;

void testNewDelete() {
    printf("%s... ", __func__);

    Int* i1 = Int__new(1);

    cgTree(Int)* tree = cgTree__new(Int, i1);
    assert(tree != NULL);
    assert(cgTree_getValue(Int, tree) == i1);
    
    Int_delete(i1);
    cgTree_delete(Int, tree);
    
    printf("ok -- ");
}

void testNewFromInitializerList() {
    printf("%s... ", __func__);

    Int* i1 = Int__new(1);
    Int* i2 = Int__new(1);
    Int* i3 = Int__new(1);

    cgTree(Int)* subLeft = cgTree__new(Int, i2);
    cgTree(Int)* subRight = cgTree__new(Int, i3);
    cgTree(Int)* root = cgTree__newFromInitializerList(Int, i1, subLeft, subRight, NULL);

    assert(cgTree_getSubTreeAt(Int, root, 0) == subLeft);
    assert(cgTree_getSubTreeAt(Int, root, 1) == subRight);
    cgArray(cgTreeOfInt)* array = cgTree_getSubTrees(Int, root);
    assert(cgArray_getSize(cgTreeOfInt, array) == 2);
    cgTree(Int)* testSubLeft = cgArray_getValueAt(cgTreeOfInt, cgTree_getSubTrees(Int, root), 0);
    cgTree(Int)* testSubRight = cgArray_getValueAt(cgTreeOfInt, cgTree_getSubTrees(Int, root), 1);
    assert(testSubLeft == subLeft);
    assert(testSubRight == subRight);
    
    Int_delete(i1);
    Int_delete(i2);
    Int_delete(i3);
    cgTree_delete(Int, root);
    
    printf("ok -- ");
}

void testSubTrees() {
    printf("%s... ", __func__);

    Int* i1 = Int__new(1);
    Int* i2 = Int__new(2);
    Int* i3 = Int__new(3);

    cgTree(Int)* root = cgTree__new(Int, i1);
    cgTree(Int)* subLeft = cgTree__new(Int, i2);
    cgTree(Int)* subRight = cgTree__new(Int, i3);

    cgTree_addSubTree(Int, root, subLeft);
    cgTree_addSubTree(Int, root, subRight);

    assert(cgTree_getSubTreeAt(Int, root, 0) == subLeft);
    assert(cgTree_getSubTreeAt(Int, root, 1) == subRight);
    cgArray(cgTreeOfInt)* array = cgTree_getSubTrees(Int, root);
    assert(cgArray_getSize(cgTreeOfInt, array) == 2);
    assert(cgTree_getSubTreeSize(Int, root) == 2);
    cgTree(Int)* testSubLeft = cgArray_getValueAt(cgTreeOfInt, cgTree_getSubTrees(Int, root), 0);
    cgTree(Int)* testSubRight = cgArray_getValueAt(cgTreeOfInt, cgTree_getSubTrees(Int, root), 1);
    assert(testSubLeft == subLeft);
    assert(testSubRight == subRight);
    
    Int_delete(i1);
    Int_delete(i2);
    Int_delete(i3);
    cgTree_delete(Int, root);
    
    printf("ok -- ");
}
void testRemoveAt() {
    printf("%s... ", __func__);

    Int* i1 = Int__new(1);
    Int* i2 = Int__new(2);
    Int* i3 = Int__new(3);

    cgTree(Int)* root = cgTree__new(Int, i1);
    cgTree(Int)* subLeft = cgTree__new(Int, i2);
    cgTree(Int)* subRight = cgTree__new(Int, i3);

    cgTree_addSubTree(Int, root, subLeft);
    cgTree_addSubTree(Int, root, subRight);


    cgTree(Int)* removedTree = cgTree_removeSubTreeAt(Int, root, 0);

    assert(removedTree == subLeft);
    assert(cgTree_getSubTreeAt(Int, root, 0) == subRight);

    Int_delete(i1);
    Int_delete(i2);
    Int_delete(i3);
    cgTree_delete(Int, root);
    printf("ok -- ");
}
bool mapSumUpTo6(const Int* i, void* userData) {
    unsigned int* sum = (unsigned int*) userData;
    if (*i <= 6) {
        (*sum) += *i;
        printf("i: %i mapSumUpTo6: %u\n", *i, *sum);
        return true;
    } else
        return false;
}
void testMapConstantDepthFirst() {
    printf("%s... ", __func__);

    Int* i1 = Int__new(1);
    Int* i2 = Int__new(2);
    Int* i3 = Int__new(3);
    Int* i4 = Int__new(4);
    Int* i5 = Int__new(5);
    Int* i6 = Int__new(6);
    Int* i7 = Int__new(7);

    cgTree(Int)* root = cgTree__new(Int, i1);
    cgTree(Int)* subLeft = cgTree__new(Int, i2);
    cgTree(Int)* subRight = cgTree__new(Int, i3);
    cgTree(Int)* subLeftLeft = cgTree__new(Int, i4);
    cgTree(Int)* subLeftRight = cgTree__new(Int, i5);
    cgTree(Int)* subRightLeft = cgTree__new(Int, i6);
    cgTree(Int)* subRightRight = cgTree__new(Int, i7);

    cgTree_addSubTree(Int, root, subLeft);
    cgTree_addSubTree(Int, root, subRight);
    cgTree_addSubTree(Int, subLeft, subLeftLeft);
    cgTree_addSubTree(Int, subLeft, subLeftRight);
    cgTree_addSubTree(Int, subRight, subRightLeft);
    cgTree_addSubTree(Int, subRight, subRightRight);


    unsigned int sum = 0;
    bool rv = cgTree_mapConstant(Int, root, mapSumUpTo6, cgTreeStrategy_depthFirst, (void*)&sum);
    printf("%u\n", sum);
    assert(rv == false);
    assert(sum == 4+5+2+6);

    Int_delete(i1);
    Int_delete(i2);
    Int_delete(i3);
    Int_delete(i4);
    Int_delete(i5);
    Int_delete(i6);
    Int_delete(i7);
    cgTree_delete(Int, root);
    printf("ok -- ");
}
bool mapSum(const Int* i, void* userData) {
    unsigned int* sum = (unsigned int*) userData;
    (*sum) += *i;
    printf("i: %i mapSum: %u\n", *i, *sum);
    return true;
}
void testMapConstantBreadthFirst() {
    printf("%s... ", __func__);

    Int* i1 = Int__new(1);
    Int* i2 = Int__new(2);
    Int* i3 = Int__new(3);
    Int* i4 = Int__new(4);
    Int* i5 = Int__new(5);
    Int* i6 = Int__new(6);
    Int* i7 = Int__new(7);

    cgTree(Int)* root = cgTree__new(Int, i1);
    cgTree(Int)* subLeft = cgTree__new(Int, i2);
    cgTree(Int)* subRight = cgTree__new(Int, i3);
    cgTree(Int)* subLeftLeft = cgTree__new(Int, i4);
    cgTree(Int)* subLeftRight = cgTree__new(Int, i5);
    cgTree(Int)* subRightLeft = cgTree__new(Int, i6);
    cgTree(Int)* subRightRight = cgTree__new(Int, i7);

    cgTree_addSubTree(Int, root, subLeft);
    cgTree_addSubTree(Int, root, subRight);
    cgTree_addSubTree(Int, subLeft, subLeftLeft);
    cgTree_addSubTree(Int, subLeft, subLeftRight);
    cgTree_addSubTree(Int, subRight, subRightLeft);
    cgTree_addSubTree(Int, subRight, subRightRight);


    unsigned int sum = 0;
    bool rv = cgTree_mapConstant(Int, root, mapSum, cgTreeStrategy_breadthFirst, (void*)&sum);
    printf("%u\n", sum);
    assert(rv == true);
    assert(sum == 1+2+3+4+5+6+7);

    Int_delete(i1);
    Int_delete(i2);
    Int_delete(i3);
    Int_delete(i4);
    Int_delete(i5);
    Int_delete(i6);
    Int_delete(i7);
    cgTree_delete(Int, root);
    printf("ok -- ");
}


int main() {
    printf("=== %s ===\n", __FILE__);
    cgAppState__init(__FILE__);
    appState = cgAppState__getInstance();

    testNewDelete();
    testSubTrees();
	testNewFromInitializerList(); /* this is AFTER testSubTrees because it depends on addSubTree */
    testRemoveAt();
    testMapConstantDepthFirst();
    testMapConstantBreadthFirst();

    cgAppState__deInit();

    printf("=== %s ok ===\n", __FILE__);
    return 0;
}
