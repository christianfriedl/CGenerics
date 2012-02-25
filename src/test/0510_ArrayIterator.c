#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include"CGAppState.h"
#include"CGArray.h"
#include"CGArrayIterator.h"
#include"CGInteger.h"

INIT_ARRAY(CGInteger)
INIT_ARRAY_ITERATOR(CGInteger)

CGAppState *appState;

void testNewDelete() {
    printf("%s...\n", __func__);

    CGInteger* i1 = CGInteger__new(1);
    CGArray(CGInteger)* array = CGArray__newFromInitializerList(CGInteger, i1, NULL);
    CGArrayIterator(CGInteger)* iter = CGArrayIterator__new(CGInteger, array);
    CGArrayIterator_delete(CGInteger, iter);

    CGArray_deleteValues(CGInteger, array);
    CGArray_delete(CGInteger, array);
    
    printf("ok\n");
}
void testIterate() {
    printf("%s...\n", __func__);

    CGInteger* i1 = CGInteger__new(1);
    CGInteger* i2 = CGInteger__new(2);
    CGArray(CGInteger)* array = CGArray__newFromInitializerList(CGInteger, i1, i2, NULL);
    CGArrayIterator(CGInteger)* iter = CGArrayIterator__new(CGInteger, array);

    assert(CGArrayIterator_isInsideBounds(CGInteger, iter) == true);
    assert(CGArrayIterator_getCurrentIndex(CGInteger, iter) == 0);
    assert(CGArrayIterator_getCurrentElement(CGInteger, iter) == i1);

    assert(CGArrayIterator_moveToNextElement(CGInteger, iter) == true);
    assert(CGArrayIterator_isInsideBounds(CGInteger, iter) == true);
    assert(CGArrayIterator_getCurrentIndex(CGInteger, iter) == 1);
    assert(CGArrayIterator_getCurrentElement(CGInteger, iter) == i2);

    assert(CGArrayIterator_moveToNextElement(CGInteger, iter) == false);
    assert(CGArrayIterator_isInsideBounds(CGInteger, iter) == false);
    assert(CGArrayIterator_getCurrentElement(CGInteger, iter) == NULL);

    CGArrayIterator_reset(CGInteger, iter);
    assert(CGArrayIterator_isInsideBounds(CGInteger, iter) == true);
    assert(CGArrayIterator_getCurrentIndex(CGInteger, iter) == 0);
    assert(CGArrayIterator_getCurrentElement(CGInteger, iter) == i1);

    CGArrayIterator_delete(CGInteger, iter);

    CGArray_deleteValues(CGInteger, array);
    CGArray_delete(CGInteger, array);
    
    printf("ok\n");
}

int main() {
    printf("=== %s ===\n", __FILE__);
    CGAppState__init(__FILE__);
    appState = CGAppState__getInstance();

    testNewDelete();
    testIterate();

    CGAppState__deInit();
    printf("=== %s ok ===\n", __FILE__);
    return 0;
}