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
    printf("%s...\n", __func__);

    CGInteger* i = CGInteger__new(appState, 22);
    assert(i != NULL);
    assert(*i == 22);
    CGLinkedListElement(CGInteger)* lle = CGLinkedListElement__new(appState, CGInteger, i);
    assert(lle != NULL);
    assert(CGLinkedListElement_getValue(appState, CGInteger, lle) == i);
    CGLinkedListElement_delete(appState, CGInteger, lle);
    CGInteger_delete(appState, i);
    
    printf("ok\n");
}

void testListNewDelete() {
    printf("%s...\n", __func__);

    CGLinkedListElement(CGInteger)* i1 = CGLinkedListElement__new(appState, CGInteger, CGInteger__new(appState, 1));
    CGLinkedList(CGInteger)* ll = CGLinkedList__new(appState, CGInteger, i1);
    CGLinkedList_delete(appState, CGInteger, ll);
    CGLinkedListElement_delete(appState, CGInteger, i1);
    
    printf("ok\n");
}
void testInsertElements() {
    printf("%s...\n", __func__);

    CGLinkedListElement(CGInteger)* i1 = CGLinkedListElement__new(appState, CGInteger, CGInteger__new(appState, 1));
    CGLinkedListElement(CGInteger)* i2 = CGLinkedListElement__new(appState, CGInteger, CGInteger__new(appState, 2));
    CGLinkedListElement(CGInteger)* i3 = CGLinkedListElement__new(appState, CGInteger, CGInteger__new(appState, 3));
    CGLinkedListElement(CGInteger)* i4 = CGLinkedListElement__new(appState, CGInteger, CGInteger__new(appState, 4));

    /* create list, insert root element */
    CGLinkedList(CGInteger)* ll = CGLinkedList__new(appState, CGInteger, i1);
    assert(ll != NULL);
    assert(CGLinkedList_getRootElement(appState, CGInteger, ll) == i1);
    /* add element at end */
    CGLinkedList_addElement(appState, CGInteger, ll, i2);

    /* insert at end */
    CGLinkedList_insertElementAfter(appState, CGInteger, ll, i2, i3);

    /* insert in middle */
    CGLinkedList_insertElementAfter(appState, CGInteger, ll, i2, i4);

    CGLinkedListElement(CGInteger)* cur = CGLinkedList_getRootElement(appState, CGInteger, ll);
    assert(cur == i1);
    cur = CGLinkedListElement_getNextElement(appState, CGInteger, cur);
    assert(cur == i2);
    cur = CGLinkedListElement_getNextElement(appState, CGInteger, cur);
    assert(cur == i4);
    cur = CGLinkedListElement_getNextElement(appState, CGInteger, cur);
    assert(cur == i3);
    cur = CGLinkedListElement_getNextElement(appState, CGInteger, cur);
    assert(cur == NULL);
    
    CGLinkedList_delete(appState, CGInteger, ll);
    CGLinkedListElement_delete(appState, CGInteger, i1);
    CGLinkedListElement_delete(appState, CGInteger, i2);
    CGLinkedListElement_delete(appState, CGInteger, i3);
    CGLinkedListElement_delete(appState, CGInteger, i4);
    printf("ok\n");
}

void testMoveToNext() {
    printf("%s...\n", __func__);

    CGLinkedListElement(CGInteger)* i1 = CGLinkedListElement__new(appState, CGInteger, CGInteger__new(appState, 1));
    CGLinkedListElement(CGInteger)* i2 = CGLinkedListElement__new(appState, CGInteger, CGInteger__new(appState, 2));
    CGLinkedListElement(CGInteger)* i3 = CGLinkedListElement__new(appState, CGInteger, CGInteger__new(appState, 3));
    CGLinkedListElement(CGInteger)* i4 = CGLinkedListElement__new(appState, CGInteger, CGInteger__new(appState, 4));

    /* create list, insert root element */
    CGLinkedList(CGInteger)* ll = CGLinkedList__new(appState, CGInteger, i1);
    assert(ll != NULL);
    assert(CGLinkedList_getRootElement(appState, CGInteger, ll) == i1);
    /* add element at end */
    CGLinkedList_addElement(appState, CGInteger, ll, i2);

    /* insert at end */
    CGLinkedList_insertElementAfter(appState, CGInteger, ll, i2, i3);

    /* insert in middle */
    CGLinkedList_insertElementAfter(appState, CGInteger, ll, i2, i4);

    CGLinkedListElement(CGInteger)* cur = CGLinkedList_moveToRootElement(appState, CGInteger, ll);
    assert(cur == i1);
    cur = CGLinkedList_moveToNextElement(appState, CGInteger, ll);
    assert(cur == i2);
    cur = CGLinkedList_moveToNextElement(appState, CGInteger, ll);
    assert(cur == i4);
    cur = CGLinkedList_moveToNextElement(appState, CGInteger, ll);
    assert(cur == i3);
    cur = CGLinkedList_moveToNextElement(appState, CGInteger, ll);
    assert(cur == NULL);

    cur = CGLinkedList_start(appState, CGInteger, ll);
    assert(cur == i1);
    cur = CGLinkedList_next(appState, CGInteger, ll);
    assert(cur == i2);
    cur = CGLinkedList_next(appState, CGInteger, ll);
    assert(cur == i4);
    cur = CGLinkedList_next(appState, CGInteger, ll);
    assert(cur == i3);
    cur = CGLinkedList_next(appState, CGInteger, ll);
    assert(cur == NULL);

    printf("ok\n");
}

void testRemove() {
    printf("%s...\n", __func__);

    CGLinkedListElement(CGInteger)* i1 = CGLinkedListElement__new(appState, CGInteger, CGInteger__new(appState, 1));
    CGLinkedListElement(CGInteger)* i2 = CGLinkedListElement__new(appState, CGInteger, CGInteger__new(appState, 2));
    CGLinkedListElement(CGInteger)* i3 = CGLinkedListElement__new(appState, CGInteger, CGInteger__new(appState, 3));
    CGLinkedListElement(CGInteger)* i4 = CGLinkedListElement__new(appState, CGInteger, CGInteger__new(appState, 4));

    /* create list, insert root element */
    CGLinkedList(CGInteger)* ll = CGLinkedList__new(appState, CGInteger, i1);
    assert(ll != NULL);
    assert(CGLinkedList_getRootElement(appState, CGInteger, ll) == i1);
    /* add elements at end */
    CGLinkedList_addElement(appState, CGInteger, ll, i2);
    CGLinkedList_addElement(appState, CGInteger, ll, i3);
    CGLinkedList_addElement(appState, CGInteger, ll, i4);

    CGLinkedListElement(CGInteger)* r = CGLinkedList_remove(appState, CGInteger, ll, i3);
    assert(r == i3);
    assert(CGLinkedListElement_getNextElement(appState, CGInteger, i2) == i4);
}

void testFind() {
    printf("%s...\n", __func__);

    CGLinkedListElement(CGInteger)* i1 = CGLinkedListElement__new(appState, CGInteger, CGInteger__new(appState, 1));
    CGLinkedListElement(CGInteger)* i2 = CGLinkedListElement__new(appState, CGInteger, CGInteger__new(appState, 2));
    CGLinkedListElement(CGInteger)* i3 = CGLinkedListElement__new(appState, CGInteger, CGInteger__new(appState, 3));
    CGLinkedListElement(CGInteger)* i4 = CGLinkedListElement__new(appState, CGInteger, CGInteger__new(appState, 4));

    /* create list, insert root element */
    CGLinkedList(CGInteger)* ll = CGLinkedList__new(appState, CGInteger, i1);
    assert(ll != NULL);
    assert(CGLinkedList_getRootElement(appState, CGInteger, ll) == i1);
    /* add elements at end */
    CGLinkedList_addElement(appState, CGInteger, ll, i2);
    CGLinkedList_addElement(appState, CGInteger, ll, i3);
    CGLinkedList_addElement(appState, CGInteger, ll, i4);

    CGInteger* tofind = CGInteger__new(appState, 1);
    CGLinkedListElement(CGInteger)* found = CGLinkedList_findElement(appState, CGInteger, ll, tofind, CGInteger__compare);
    assert(CGInteger_toInt(appState, tofind) == CGInteger_toInt(appState, CGLinkedListElement_getValue(appState, CGInteger, found)));

    CGInteger* foundCGInteger = CGLinkedList_findValue(appState, CGInteger, ll, tofind, CGInteger__compare);
    assert(CGInteger_toInt(appState, tofind) == CGInteger_toInt(appState, foundCGInteger));

    CGInteger_delete(appState, tofind);
    tofind = CGInteger__new(appState, 5);
    found = CGLinkedList_findElement(appState, CGInteger, ll, tofind, CGInteger__compare);
    assert(found == NULL);
    assert(CGAppState_catchExceptionWithID(appState, CGExceptionID_ElementNotFound) != NULL);

    foundCGInteger = CGLinkedList_findValue(appState, CGInteger, ll, tofind, CGInteger__compare);
    assert(foundCGInteger== NULL);
    assert(CGAppState_catchExceptionWithID(appState, CGExceptionID_ElementNotFound) != NULL);

    CGInteger_delete(appState, tofind);
    CGLinkedListElement_delete(appState, CGInteger, i1);
    CGLinkedListElement_delete(appState, CGInteger, i2);
    CGLinkedListElement_delete(appState, CGInteger, i3);
    CGLinkedListElement_delete(appState, CGInteger, i4);

    CGLinkedList_delete(appState, CGInteger, ll);

    printf("ok\n");
}


int main() {
    printf("=== %s ===\n", __FILE__);
    appState = CGAppState__new(__FILE__);

    testElementNewDelete();
    testListNewDelete();
    testInsertElements();
    testMoveToNext();
    testRemove();
    testFind();

    CGAppState_delete(appState);
    printf("=== %s ok ===\n", __FILE__);
    return 0;
}
