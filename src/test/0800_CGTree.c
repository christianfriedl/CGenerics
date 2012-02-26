#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include"CGAppState.h"
#include"CGTree.h"

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

CGAppState *appState;

void testNewDelete() {
    printf("%s...\n", __func__);

    Int* i1 = Int__new(1);

    CGTree(Int)* tree = CGTree__new(Int, i1);
    assert(tree != NULL);
    assert(CGTree_getValue(Int, tree) == i1);
    
    Int_delete(i1);
    CGTree_delete(Int, tree);
    
    printf("%s ok\n", __func__);
}

void testNewFromInitializerList() {
    printf("%s...\n", __func__);

    Int* i1 = Int__new(1);
    Int* i2 = Int__new(1);
    Int* i3 = Int__new(1);

    CGTree(Int)* subLeft = CGTree__new(Int, i2);
    CGTree(Int)* subRight = CGTree__new(Int, i3);
    CGTree(Int)* root = CGTree__newFromInitializerList(Int, i1, subLeft, subRight, NULL);

    assert(CGTree_getSubTreeAt(Int, root, 0) == subLeft);
    assert(CGTree_getSubTreeAt(Int, root, 1) == subRight);
    CGArray(CGTreeOfInt)* array = CGTree_getSubTrees(Int, root);
    assert(CGArray_getSize(CGTreeOfInt, array) == 2);
    CGTree(Int)* testSubLeft = CGArray_getValueAt(CGTreeOfInt, CGTree_getSubTrees(Int, root), 0);
    CGTree(Int)* testSubRight = CGArray_getValueAt(CGTreeOfInt, CGTree_getSubTrees(Int, root), 1);
    assert(testSubLeft == subLeft);
    assert(testSubRight == subRight);
    
    Int_delete(i1);
    Int_delete(i2);
    Int_delete(i3);
    CGTree_delete(Int, root);
    
    printf("%s ok\n", __func__);
}

void testSubTrees() {
    printf("%s...\n", __func__);

    Int* i1 = Int__new(1);
    Int* i2 = Int__new(2);
    Int* i3 = Int__new(3);

    CGTree(Int)* root = CGTree__new(Int, i1);
    CGTree(Int)* subLeft = CGTree__new(Int, i2);
    CGTree(Int)* subRight = CGTree__new(Int, i3);

    CGTree_addSubTree(Int, root, subLeft);
    CGTree_addSubTree(Int, root, subRight);

    assert(CGTree_getSubTreeAt(Int, root, 0) == subLeft);
    assert(CGTree_getSubTreeAt(Int, root, 1) == subRight);
    CGArray(CGTreeOfInt)* array = CGTree_getSubTrees(Int, root);
    assert(CGArray_getSize(CGTreeOfInt, array) == 2);
    assert(CGTree_getSubTreeSize(Int, root) == 2);
    CGTree(Int)* testSubLeft = CGArray_getValueAt(CGTreeOfInt, CGTree_getSubTrees(Int, root), 0);
    CGTree(Int)* testSubRight = CGArray_getValueAt(CGTreeOfInt, CGTree_getSubTrees(Int, root), 1);
    assert(testSubLeft == subLeft);
    assert(testSubRight == subRight);
    
    Int_delete(i1);
    Int_delete(i2);
    Int_delete(i3);
    CGTree_delete(Int, root);
    
    printf("%s ok\n", __func__);
}


int main() {
    printf("=== %s ===\n", __FILE__);
    CGAppState__init(__FILE__);
    appState = CGAppState__getInstance();

    testNewDelete();
    testSubTrees();
	testNewFromInitializerList(); /* this is AFTER testSubTrees because it depends on addSubTree */

    CGAppState__deInit();

    printf("=== %s ok ===\n", __FILE__);
    return 0;
}
