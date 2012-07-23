#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include"CGAppState.h"
#include"CGInteger.h"
#include"CGLinkedList.h"

INIT_LINKEDLIST(CGInteger)

CGAppState *appState;

void testElementNewDelete() {
    printf("%s... ", __func__);

    CGInteger* i = CGInteger__new(22);
    assert(i != NULL);
    assert(*i == 22);
    CGLinkedListElement(CGInteger)* lle = CGLinkedListElement__new(CGInteger, i);
    assert(lle != NULL);
    assert(CGLinkedListElement_getValue(CGInteger, lle) == i);
    CGLinkedListElement_delete(CGInteger, lle);
    CGInteger_delete(i);
    
    printf("ok -- ");
}

void testListNewDelete() {
    printf("%s... ", __func__);

    CGLinkedListElement(CGInteger)* i1 = CGLinkedListElement__new(CGInteger, CGInteger__new(1));
    CGLinkedList(CGInteger)* ll = CGLinkedList__new(CGInteger, i1);
    CGLinkedList_delete(CGInteger, ll);
    CGLinkedListElement_delete(CGInteger, i1);
    
    printf("ok -- ");
}
void testInsertElements() {
    printf("%s... ", __func__);

    CGLinkedListElement(CGInteger)* i1 = CGLinkedListElement__new(CGInteger, CGInteger__new(1));
    CGLinkedListElement(CGInteger)* i2 = CGLinkedListElement__new(CGInteger, CGInteger__new(2));
    CGLinkedListElement(CGInteger)* i3 = CGLinkedListElement__new(CGInteger, CGInteger__new(3));
    CGLinkedListElement(CGInteger)* i4 = CGLinkedListElement__new(CGInteger, CGInteger__new(4));

    /* create list, insert root element */
    CGLinkedList(CGInteger)* ll = CGLinkedList__new(CGInteger, i1);
    assert(ll != NULL);
    assert(CGLinkedList_getRootElement(CGInteger, ll) == i1);
    /* add element at end */
    CGLinkedList_addElement(CGInteger, ll, i2);

    /* insert at end */
    CGLinkedList_insertElementAfter(CGInteger, ll, i2, i3);

    /* insert in middle */
    CGLinkedList_insertElementAfter(CGInteger, ll, i2, i4);

    CGLinkedListElement(CGInteger)* cur = CGLinkedList_getRootElement(CGInteger, ll);
    assert(cur == i1);
    cur = CGLinkedListElement_getNextElement(CGInteger, cur);
    assert(cur == i2);
    cur = CGLinkedListElement_getNextElement(CGInteger, cur);
    assert(cur == i4);
    cur = CGLinkedListElement_getNextElement(CGInteger, cur);
    assert(cur == i3);
    cur = CGLinkedListElement_getNextElement(CGInteger, cur);
    assert(cur == NULL);
    
    CGLinkedList_delete(CGInteger, ll);
    CGLinkedListElement_delete(CGInteger, i1);
    CGLinkedListElement_delete(CGInteger, i2);
    CGLinkedListElement_delete(CGInteger, i3);
    CGLinkedListElement_delete(CGInteger, i4);
    printf("ok -- ");
}

void testMoveToNext() {
    printf("%s... ", __func__);

    CGLinkedListElement(CGInteger)* i1 = CGLinkedListElement__new(CGInteger, CGInteger__new(1));
    CGLinkedListElement(CGInteger)* i2 = CGLinkedListElement__new(CGInteger, CGInteger__new(2));
    CGLinkedListElement(CGInteger)* i3 = CGLinkedListElement__new(CGInteger, CGInteger__new(3));
    CGLinkedListElement(CGInteger)* i4 = CGLinkedListElement__new(CGInteger, CGInteger__new(4));

    /* create list, insert root element */
    CGLinkedList(CGInteger)* ll = CGLinkedList__new(CGInteger, i1);
    assert(ll != NULL);
    assert(CGLinkedList_getRootElement(CGInteger, ll) == i1);
    /* add element at end */
    CGLinkedList_addElement(CGInteger, ll, i2);

    /* insert at end */
    CGLinkedList_insertElementAfter(CGInteger, ll, i2, i3);

    /* insert in middle */
    CGLinkedList_insertElementAfter(CGInteger, ll, i2, i4);

    CGLinkedListElement(CGInteger)* cur = CGLinkedList_moveToRootElement(CGInteger, ll);
    assert(cur == i1);
    cur = CGLinkedList_moveToNextElement(CGInteger, ll);
    assert(cur == i2);
    cur = CGLinkedList_moveToNextElement(CGInteger, ll);
    assert(cur == i4);
    cur = CGLinkedList_moveToNextElement(CGInteger, ll);
    assert(cur == i3);
    cur = CGLinkedList_moveToNextElement(CGInteger, ll);
    assert(cur == NULL);

    cur = CGLinkedList_start(CGInteger, ll);
    assert(cur == i1);
    cur = CGLinkedList_next(CGInteger, ll);
    assert(cur == i2);
    cur = CGLinkedList_next(CGInteger, ll);
    assert(cur == i4);
    cur = CGLinkedList_next(CGInteger, ll);
    assert(cur == i3);
    cur = CGLinkedList_next(CGInteger, ll);
    assert(cur == NULL);

    printf("ok -- ");
}

void testRemove() {
    printf("%s... ", __func__);

    CGLinkedListElement(CGInteger)* i1 = CGLinkedListElement__new(CGInteger, CGInteger__new(1));
    CGLinkedListElement(CGInteger)* i2 = CGLinkedListElement__new(CGInteger, CGInteger__new(2));
    CGLinkedListElement(CGInteger)* i3 = CGLinkedListElement__new(CGInteger, CGInteger__new(3));
    CGLinkedListElement(CGInteger)* i4 = CGLinkedListElement__new(CGInteger, CGInteger__new(4));

    /* create list, insert root element */
    CGLinkedList(CGInteger)* ll = CGLinkedList__new(CGInteger, i1);
    assert(ll != NULL);
    assert(CGLinkedList_getRootElement(CGInteger, ll) == i1);
    /* add elements at end */
    CGLinkedList_addElement(CGInteger, ll, i2);
    CGLinkedList_addElement(CGInteger, ll, i3);
    CGLinkedList_addElement(CGInteger, ll, i4);

    CGLinkedListElement(CGInteger)* r = CGLinkedList_remove(CGInteger, ll, i3);
    assert(r == i3);
    assert(CGLinkedListElement_getNextElement(CGInteger, i2) == i4);
}

void testFind() {
    printf("%s... ", __func__);

    CGLinkedListElement(CGInteger)* i1 = CGLinkedListElement__new(CGInteger, CGInteger__new(1));
    CGLinkedListElement(CGInteger)* i2 = CGLinkedListElement__new(CGInteger, CGInteger__new(2));
    CGLinkedListElement(CGInteger)* i3 = CGLinkedListElement__new(CGInteger, CGInteger__new(3));
    CGLinkedListElement(CGInteger)* i4 = CGLinkedListElement__new(CGInteger, CGInteger__new(4));

    /* create list, insert root element */
    CGLinkedList(CGInteger)* ll = CGLinkedList__new(CGInteger, i1);
    assert(ll != NULL);
    assert(CGLinkedList_getRootElement(CGInteger, ll) == i1);
    /* add elements at end */
    CGLinkedList_addElement(CGInteger, ll, i2);
    CGLinkedList_addElement(CGInteger, ll, i3);
    CGLinkedList_addElement(CGInteger, ll, i4);

    CGInteger* tofind = CGInteger__new(1);
    CGLinkedListElement(CGInteger)* found = CGLinkedList_findElement(CGInteger, ll, tofind, CGInteger__compare);
    assert(CGInteger_toInt(tofind) == CGInteger_toInt(CGLinkedListElement_getValue(CGInteger, found)));

    CGInteger* foundCGInteger = CGLinkedList_findValue(CGInteger, ll, tofind, CGInteger__compare);
    assert(CGInteger_toInt(tofind) == CGInteger_toInt(foundCGInteger));

    CGInteger_delete(tofind);
    tofind = CGInteger__new(5);
    found = CGLinkedList_findElement(CGInteger, ll, tofind, CGInteger__compare);
    assert(found == NULL);
    assert(CGAppState_catchExceptionWithID(appState, CGExceptionID_ElementNotFound) != NULL);

    foundCGInteger = CGLinkedList_findValue(CGInteger, ll, tofind, CGInteger__compare);
    assert(foundCGInteger== NULL);
    assert(CGAppState_catchExceptionWithID(appState, CGExceptionID_ElementNotFound) != NULL);

    CGInteger_delete(tofind);
    CGLinkedListElement_delete(CGInteger, i1);
    CGLinkedListElement_delete(CGInteger, i2);
    CGLinkedListElement_delete(CGInteger, i3);
    CGLinkedListElement_delete(CGInteger, i4);

    CGLinkedList_delete(CGInteger, ll);

    printf("ok -- ");
}


int main() {
    printf("=== %s ===\n", __FILE__);
    CGAppState__init(__FILE__);
    appState = CGAppState__getInstance();

    testElementNewDelete();
    testListNewDelete();
    testInsertElements();
    testMoveToNext();
    testRemove();
    testFind();

    CGAppState__deInit();
    printf("=== %s ok ===\n", __FILE__);
    return 0;
}
