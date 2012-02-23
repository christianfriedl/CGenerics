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

    CGInteger* i1 = CGInteger__new(appState, 1);
    CGArray(CGInteger)* array = CGArray__newFromInitializerList(appState, CGInteger, i1, NULL);
    CGArrayIterator(CGInteger)* iter = CGArrayIterator__new(appState, CGInteger, array);
    CGArrayIterator_delete(appState, CGInteger, iter);

    CGArray_deleteValues(appState, CGInteger, array);
    CGArray_delete(appState, CGInteger, array);
    
    printf("ok\n");
}
void testIterate() {
    printf("%s...\n", __func__);

    CGInteger* i1 = CGInteger__new(appState, 1);
    CGInteger* i2 = CGInteger__new(appState, 2);
    CGArray(CGInteger)* array = CGArray__newFromInitializerList(appState, CGInteger, i1, i2, NULL);
    CGArrayIterator(CGInteger)* iter = CGArrayIterator__new(appState, CGInteger, array);

    assert(CGArrayIterator_isInsideBounds(appState, CGInteger, iter) == true);
    assert(CGArrayIterator_getCurrentIndex(appState, CGInteger, iter) == 0);
    assert(CGArrayIterator_getCurrentElement(appState, CGInteger, iter) == i1);

    assert(CGArrayIterator_moveToNextElement(appState, CGInteger, iter) == true);
    assert(CGArrayIterator_isInsideBounds(appState, CGInteger, iter) == true);
    assert(CGArrayIterator_getCurrentIndex(appState, CGInteger, iter) == 1);
    assert(CGArrayIterator_getCurrentElement(appState, CGInteger, iter) == i2);

    assert(CGArrayIterator_moveToNextElement(appState, CGInteger, iter) == false);
    assert(CGArrayIterator_isInsideBounds(appState, CGInteger, iter) == false);
    assert(CGArrayIterator_getCurrentElement(appState, CGInteger, iter) == NULL);

    CGArrayIterator_reset(appState, CGInteger, iter);
    assert(CGArrayIterator_isInsideBounds(appState, CGInteger, iter) == true);
    assert(CGArrayIterator_getCurrentIndex(appState, CGInteger, iter) == 0);
    assert(CGArrayIterator_getCurrentElement(appState, CGInteger, iter) == i1);

    CGArrayIterator_delete(appState, CGInteger, iter);

    CGArray_deleteValues(appState, CGInteger, array);
    CGArray_delete(appState, CGInteger, array);
    
    printf("ok\n");
}

int main() {
    printf("=== %s ===\n", __FILE__);
    appState = CGAppState__new();

    testNewDelete();
    testIterate();

    CGAppState_delete(appState);
    printf("=== %s ok ===\n", __FILE__);
    return 0;
}
