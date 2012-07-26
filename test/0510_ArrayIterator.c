#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include"cgAppState.h"
#include"cgArray.h"
#include"cgArrayIterator.h"
#include"cgInteger.h"

INIT_ARRAY(cgInteger)
INIT_ARRAY_ITERATOR(cgInteger)

cgAppState *appState;

void testNewDelete() {
    printf("%s... ", __func__);

    cgInteger* i1 = cgInteger__new(1);
    cgArray(cgInteger)* array = cgArray__newFromInitializerList(cgInteger, i1, NULL);
    cgArrayIterator(cgInteger)* iter = cgArrayIterator__new(cgInteger, array);
    cgArrayIterator_delete(cgInteger, iter);

    cgArray_deleteValues(cgInteger, array);
    cgArray_delete(cgInteger, array);
    
    printf("ok -- ");
}
void testIterate() {
    printf("%s... ", __func__);

    cgInteger* i1 = cgInteger__new(1);
    cgInteger* i2 = cgInteger__new(2);
    cgArray(cgInteger)* array = cgArray__newFromInitializerList(cgInteger, i1, i2, NULL);
    cgArrayIterator(cgInteger)* iter = cgArrayIterator__new(cgInteger, array);

    assert(cgArrayIterator_isInsideBounds(cgInteger, iter) == true);
    assert(cgArrayIterator_getCurrentIndex(cgInteger, iter) == 0);
    assert(cgArrayIterator_getCurrentElement(cgInteger, iter) == i1);

    assert(cgArrayIterator_moveToNextElement(cgInteger, iter) == true);
    assert(cgArrayIterator_isInsideBounds(cgInteger, iter) == true);
    assert(cgArrayIterator_getCurrentIndex(cgInteger, iter) == 1);
    assert(cgArrayIterator_getCurrentElement(cgInteger, iter) == i2);

    assert(cgArrayIterator_moveToNextElement(cgInteger, iter) == false);
    assert(cgArrayIterator_isInsideBounds(cgInteger, iter) == false);
    assert(cgArrayIterator_getCurrentElement(cgInteger, iter) == NULL);

    cgArrayIterator_reset(cgInteger, iter);
    assert(cgArrayIterator_isInsideBounds(cgInteger, iter) == true);
    assert(cgArrayIterator_getCurrentIndex(cgInteger, iter) == 0);
    assert(cgArrayIterator_getCurrentElement(cgInteger, iter) == i1);

    cgArrayIterator_delete(cgInteger, iter);

    cgArray_deleteValues(cgInteger, array);
    cgArray_delete(cgInteger, array);
    
    printf("ok -- ");
}
void testFetch() {
    printf("%s... ", __func__);

    cgInteger* i1 = cgInteger__new(1);
    cgInteger* i2 = cgInteger__new(2);
    cgArray(cgInteger)* array = cgArray__newFromInitializerList(cgInteger, i1, i2, NULL);
    cgArrayIterator(cgInteger)* iter = cgArrayIterator__new(cgInteger, array);

    int i = 0;
    cgInteger* iVector[2] = { i1, i2 };
    cgInteger* iFetch;
    while ((iFetch = cgArrayIterator_fetch(cgInteger, iter)) != NULL) {
        assert(iVector[i] == iFetch);
        i++;
    }
    assert(i==2);

    cgArrayIterator_delete(cgInteger, iter);

    cgArray_deleteValues(cgInteger, array);
    cgArray_delete(cgInteger, array);
    
    printf("ok -- ");
}
void testFetchEmptyArray() {
    printf("%s... ", __func__);

    cgArray(cgInteger)* array = cgArray__new(cgInteger, 1);
    cgArrayIterator(cgInteger)* iter = cgArrayIterator__new(cgInteger, array);

    assert(cgArrayIterator_fetch(cgInteger, iter) == NULL);

    cgArrayIterator_delete(cgInteger, iter);

    cgArray_deleteValues(cgInteger, array);
    cgArray_delete(cgInteger, array);
    
    printf("ok -- ");
}

void testUnFetch() {
    printf("%s... ", __func__);

    cgInteger* i1 = cgInteger__new(1);
    cgInteger* i2 = cgInteger__new(2);
    cgArray(cgInteger)* array = cgArray__newFromInitializerList(cgInteger, i1, i2, NULL);
    cgArrayIterator(cgInteger)* iter = cgArrayIterator__new(cgInteger, array);

    cgInteger* iFetch;
    iFetch = cgArrayIterator_fetch(cgInteger, iter);
    assert(iFetch == i1);
    cgArrayIterator_unFetch(cgInteger, iter);

    iFetch = cgArrayIterator_fetch(cgInteger, iter);
    assert(iFetch == i1);

    cgArrayIterator_delete(cgInteger, iter);

    cgArray_deleteValues(cgInteger, array);
    cgArray_delete(cgInteger, array);
    
    printf("ok -- ");
}
void testMoveToIndex() {
    printf("%s... ", __func__);

    cgInteger* i1 = cgInteger__new(1);
    cgInteger* i2 = cgInteger__new(2);
    cgArray(cgInteger)* array = cgArray__newFromInitializerList(cgInteger, i1, i2, NULL);
    cgArrayIterator(cgInteger)* iter = cgArrayIterator__new(cgInteger, array);

    cgArrayIterator_moveToIndex(cgInteger, iter, 0);

    cgInteger* iFetch;
    iFetch = cgArrayIterator_fetch(cgInteger, iter);
    assert(iFetch == i2);

    cgArrayIterator_moveToIndex(cgInteger, iter, 1);
    iFetch = cgArrayIterator_fetch(cgInteger, iter);
    assert(iFetch == NULL);

    cgArrayIterator_moveToIndex(cgInteger, iter, 0);
    cgArrayIterator_unFetch(cgInteger, iter);
    iFetch = cgArrayIterator_fetch(cgInteger, iter);
    assert(iFetch == i1);

    cgArrayIterator_delete(cgInteger, iter);

    cgArray_deleteValues(cgInteger, array);
    cgArray_delete(cgInteger, array);
    
    printf("ok -- ");
}
void testClone() {
    printf("%s... ", __func__);

    cgInteger* i1 = cgInteger__new(1);
    cgInteger* i2 = cgInteger__new(2);
    cgArray(cgInteger)* array = cgArray__newFromInitializerList(cgInteger, i1, i2, NULL);
    cgArrayIterator(cgInteger)* iter = cgArrayIterator__new(cgInteger, array);
    cgInteger* iFetch;
    iFetch = cgArrayIterator_fetch(cgInteger, iter);
    assert(iFetch == i1);
    cgArrayIterator(cgInteger)* iter2 = cgArrayIterator_clone(cgInteger, iter);
    assert(iter2 != NULL);
    assert(iter2 != iter);
    iFetch = cgArrayIterator_fetch(cgInteger, iter);
    assert(iFetch == i2);

    cgArrayIterator_delete(cgInteger, iter);
    cgArrayIterator_delete(cgInteger, iter2);

    cgArray_deleteValues(cgInteger, array);
    cgArray_delete(cgInteger, array);
    
    printf("ok -- ");
}
int main() {
    printf("=== %s ===\n", __FILE__);
    cgAppState__init(__FILE__);
    appState = cgAppState__getInstance();

    testNewDelete();
    testIterate();
    testFetch();
    testFetchEmptyArray();
    testUnFetch();
    testMoveToIndex();
    testClone();

    cgAppState__deInit();
    printf("=== %s ok ===\n", __FILE__);
    return 0;
}
