#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include"cgAppState.h"
#include"cgInteger.h"
#include"cgLinkedList.h"

INIT_LINKEDLIST(cgInteger)

cgAppState *appState;

void testElementNewDelete() {
    printf("%s... ", __func__);

    cgInteger* i = cgInteger__new(22);
    assert(i != NULL);
    assert(*i == 22);
    cgLinkedListElement(cgInteger)* lle = cgLinkedListElement__new(cgInteger, i);
    assert(lle != NULL);
    assert(cgLinkedListElement_getValue(cgInteger, lle) == i);
    cgLinkedListElement_delete(cgInteger, lle);
    cgInteger_delete(i);
    
    printf("ok -- ");
}

void testListNewDelete() {
    printf("%s... ", __func__);

    cgLinkedListElement(cgInteger)* i1 = cgLinkedListElement__new(cgInteger, cgInteger__new(1));
    cgLinkedList(cgInteger)* ll = cgLinkedList__new(cgInteger, i1);
    cgLinkedList_delete(cgInteger, ll);
    cgLinkedListElement_delete(cgInteger, i1);
    
    printf("ok -- ");
}
void testInsertElements() {
    printf("%s... ", __func__);

    cgLinkedListElement(cgInteger)* i1 = cgLinkedListElement__new(cgInteger, cgInteger__new(1));
    cgLinkedListElement(cgInteger)* i2 = cgLinkedListElement__new(cgInteger, cgInteger__new(2));
    cgLinkedListElement(cgInteger)* i3 = cgLinkedListElement__new(cgInteger, cgInteger__new(3));
    cgLinkedListElement(cgInteger)* i4 = cgLinkedListElement__new(cgInteger, cgInteger__new(4));

    /* create list, insert root element */
    cgLinkedList(cgInteger)* ll = cgLinkedList__new(cgInteger, i1);
    assert(ll != NULL);
    assert(cgLinkedList_getRootElement(cgInteger, ll) == i1);
    /* add element at end */
    cgLinkedList_addElement(cgInteger, ll, i2);

    /* insert at end */
    cgLinkedList_insertElementAfter(cgInteger, ll, i2, i3);

    /* insert in middle */
    cgLinkedList_insertElementAfter(cgInteger, ll, i2, i4);

    cgLinkedListElement(cgInteger)* cur = cgLinkedList_getRootElement(cgInteger, ll);
    assert(cur == i1);
    cur = cgLinkedListElement_getNextElement(cgInteger, cur);
    assert(cur == i2);
    cur = cgLinkedListElement_getNextElement(cgInteger, cur);
    assert(cur == i4);
    cur = cgLinkedListElement_getNextElement(cgInteger, cur);
    assert(cur == i3);
    cur = cgLinkedListElement_getNextElement(cgInteger, cur);
    assert(cur == NULL);
    
    cgLinkedList_delete(cgInteger, ll);
    cgLinkedListElement_delete(cgInteger, i1);
    cgLinkedListElement_delete(cgInteger, i2);
    cgLinkedListElement_delete(cgInteger, i3);
    cgLinkedListElement_delete(cgInteger, i4);
    printf("ok -- ");
}

void testMoveToNext() {
    printf("%s... ", __func__);

    cgLinkedListElement(cgInteger)* i1 = cgLinkedListElement__new(cgInteger, cgInteger__new(1));
    cgLinkedListElement(cgInteger)* i2 = cgLinkedListElement__new(cgInteger, cgInteger__new(2));
    cgLinkedListElement(cgInteger)* i3 = cgLinkedListElement__new(cgInteger, cgInteger__new(3));
    cgLinkedListElement(cgInteger)* i4 = cgLinkedListElement__new(cgInteger, cgInteger__new(4));

    /* create list, insert root element */
    cgLinkedList(cgInteger)* ll = cgLinkedList__new(cgInteger, i1);
    assert(ll != NULL);
    assert(cgLinkedList_getRootElement(cgInteger, ll) == i1);
    /* add element at end */
    cgLinkedList_addElement(cgInteger, ll, i2);

    /* insert at end */
    cgLinkedList_insertElementAfter(cgInteger, ll, i2, i3);

    /* insert in middle */
    cgLinkedList_insertElementAfter(cgInteger, ll, i2, i4);

    cgLinkedListElement(cgInteger)* cur = cgLinkedList_moveToRootElement(cgInteger, ll);
    assert(cur == i1);
    cur = cgLinkedList_moveToNextElement(cgInteger, ll);
    assert(cur == i2);
    cur = cgLinkedList_moveToNextElement(cgInteger, ll);
    assert(cur == i4);
    cur = cgLinkedList_moveToNextElement(cgInteger, ll);
    assert(cur == i3);
    cur = cgLinkedList_moveToNextElement(cgInteger, ll);
    assert(cur == NULL);

    cur = cgLinkedList_start(cgInteger, ll);
    assert(cur == i1);
    cur = cgLinkedList_next(cgInteger, ll);
    assert(cur == i2);
    cur = cgLinkedList_next(cgInteger, ll);
    assert(cur == i4);
    cur = cgLinkedList_next(cgInteger, ll);
    assert(cur == i3);
    cur = cgLinkedList_next(cgInteger, ll);
    assert(cur == NULL);

    printf("ok -- ");
}

void testRemove() {
    printf("%s... ", __func__);

    cgLinkedListElement(cgInteger)* i1 = cgLinkedListElement__new(cgInteger, cgInteger__new(1));
    cgLinkedListElement(cgInteger)* i2 = cgLinkedListElement__new(cgInteger, cgInteger__new(2));
    cgLinkedListElement(cgInteger)* i3 = cgLinkedListElement__new(cgInteger, cgInteger__new(3));
    cgLinkedListElement(cgInteger)* i4 = cgLinkedListElement__new(cgInteger, cgInteger__new(4));

    /* create list, insert root element */
    cgLinkedList(cgInteger)* ll = cgLinkedList__new(cgInteger, i1);
    assert(ll != NULL);
    assert(cgLinkedList_getRootElement(cgInteger, ll) == i1);
    /* add elements at end */
    cgLinkedList_addElement(cgInteger, ll, i2);
    cgLinkedList_addElement(cgInteger, ll, i3);
    cgLinkedList_addElement(cgInteger, ll, i4);

    cgLinkedListElement(cgInteger)* r = cgLinkedList_remove(cgInteger, ll, i3);
    assert(r == i3);
    assert(cgLinkedListElement_getNextElement(cgInteger, i2) == i4);
}

void testFind() {
    printf("%s... ", __func__);

    cgLinkedListElement(cgInteger)* i1 = cgLinkedListElement__new(cgInteger, cgInteger__new(1));
    cgLinkedListElement(cgInteger)* i2 = cgLinkedListElement__new(cgInteger, cgInteger__new(2));
    cgLinkedListElement(cgInteger)* i3 = cgLinkedListElement__new(cgInteger, cgInteger__new(3));
    cgLinkedListElement(cgInteger)* i4 = cgLinkedListElement__new(cgInteger, cgInteger__new(4));

    /* create list, insert root element */
    cgLinkedList(cgInteger)* ll = cgLinkedList__new(cgInteger, i1);
    assert(ll != NULL);
    assert(cgLinkedList_getRootElement(cgInteger, ll) == i1);
    /* add elements at end */
    cgLinkedList_addElement(cgInteger, ll, i2);
    cgLinkedList_addElement(cgInteger, ll, i3);
    cgLinkedList_addElement(cgInteger, ll, i4);

    cgInteger* tofind = cgInteger__new(1);
    cgLinkedListElement(cgInteger)* found = cgLinkedList_findElement(cgInteger, ll, tofind, cgInteger__compare);
    assert(cgInteger_toInt(tofind) == cgInteger_toInt(cgLinkedListElement_getValue(cgInteger, found)));

    cgInteger* foundCGInteger = cgLinkedList_findValue(cgInteger, ll, tofind, cgInteger__compare);
    assert(cgInteger_toInt(tofind) == cgInteger_toInt(foundCGInteger));

    cgInteger_delete(tofind);
    tofind = cgInteger__new(5);
    found = cgLinkedList_findElement(cgInteger, ll, tofind, cgInteger__compare);
    assert(found == NULL);
    assert(cgAppState_catchExceptionWithID(appState, cgExceptionID_ElementNotFound) != NULL);

    foundCGInteger = cgLinkedList_findValue(cgInteger, ll, tofind, cgInteger__compare);
    assert(foundCGInteger== NULL);
    assert(cgAppState_catchExceptionWithID(appState, cgExceptionID_ElementNotFound) != NULL);

    cgInteger_delete(tofind);
    cgLinkedListElement_delete(cgInteger, i1);
    cgLinkedListElement_delete(cgInteger, i2);
    cgLinkedListElement_delete(cgInteger, i3);
    cgLinkedListElement_delete(cgInteger, i4);

    cgLinkedList_delete(cgInteger, ll);

    printf("ok -- ");
}


int main() {
    printf("=== %s ===\n", __FILE__);
    cgAppState__init(__FILE__);
    appState = cgAppState__getInstance();

    testElementNewDelete();
    testListNewDelete();
    testInsertElements();
    testMoveToNext();
    testRemove();
    testFind();

    cgAppState__deInit();
    printf("=== %s ok ===\n", __FILE__);
    return 0;
}
