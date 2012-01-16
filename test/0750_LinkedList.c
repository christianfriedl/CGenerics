#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include"CGAppState.h"
#include"CGInteger.h"
#include"LinkedList.h"

INIT_LINKEDLIST(CGInteger)

CGAppState *appState;

void testElementNewDelete() {
    printf("%s...\n", __func__);

    CGInteger* i = CGInteger__new(appState, 22);
    assert(i != NULL);
    assert(*i == 22);
    LinkedListElement(CGInteger)* lle = LinkedListElement__new(appState, CGInteger, i);
    assert(lle != NULL);
    assert(LinkedListElement_getValue(appState, CGInteger, lle) == i);
    LinkedListElement_delete(appState, CGInteger, lle);
    CGInteger_delete(appState, i);
    
    printf("ok\n");
}

void testListNewDelete() {
    printf("%s...\n", __func__);

    LinkedListElement(CGInteger)* i1 = LinkedListElement__new(appState, CGInteger, CGInteger__new(appState, 1));
    LinkedList(CGInteger)* ll = LinkedList__new(appState, CGInteger, i1);
    LinkedList_delete(appState, CGInteger, ll);
    LinkedListElement_delete(appState, CGInteger, i1);
    
    printf("ok\n");
}
void testInsertElements() {
    printf("%s...\n", __func__);

    LinkedListElement(CGInteger)* i1 = LinkedListElement__new(appState, CGInteger, CGInteger__new(appState, 1));
    LinkedListElement(CGInteger)* i2 = LinkedListElement__new(appState, CGInteger, CGInteger__new(appState, 2));
    LinkedListElement(CGInteger)* i3 = LinkedListElement__new(appState, CGInteger, CGInteger__new(appState, 3));
    LinkedListElement(CGInteger)* i4 = LinkedListElement__new(appState, CGInteger, CGInteger__new(appState, 4));

    /* create list, insert root element */
    LinkedList(CGInteger)* ll = LinkedList__new(appState, CGInteger, i1);
    assert(ll != NULL);
    assert(LinkedList_getRootElement(appState, CGInteger, ll) == i1);
    /* add element at end */
    LinkedList_addElement(appState, CGInteger, ll, i2);

    /* insert at end */
    LinkedList_insertElementAfter(appState, CGInteger, ll, i2, i3);

    /* insert in middle */
    LinkedList_insertElementAfter(appState, CGInteger, ll, i2, i4);

    LinkedListElement(CGInteger)* cur = LinkedList_getRootElement(appState, CGInteger, ll);
    assert(cur == i1);
    cur = LinkedListElement_getNextElement(appState, CGInteger, cur);
    assert(cur == i2);
    cur = LinkedListElement_getNextElement(appState, CGInteger, cur);
    assert(cur == i4);
    cur = LinkedListElement_getNextElement(appState, CGInteger, cur);
    assert(cur == i3);
    cur = LinkedListElement_getNextElement(appState, CGInteger, cur);
    assert(cur == NULL);
    
    LinkedList_delete(appState, CGInteger, ll);
    LinkedListElement_delete(appState, CGInteger, i1);
    LinkedListElement_delete(appState, CGInteger, i2);
    LinkedListElement_delete(appState, CGInteger, i3);
    LinkedListElement_delete(appState, CGInteger, i4);
    printf("ok\n");
}

void testMoveToNext() {
    printf("%s...\n", __func__);

    LinkedListElement(CGInteger)* i1 = LinkedListElement__new(appState, CGInteger, CGInteger__new(appState, 1));
    LinkedListElement(CGInteger)* i2 = LinkedListElement__new(appState, CGInteger, CGInteger__new(appState, 2));
    LinkedListElement(CGInteger)* i3 = LinkedListElement__new(appState, CGInteger, CGInteger__new(appState, 3));
    LinkedListElement(CGInteger)* i4 = LinkedListElement__new(appState, CGInteger, CGInteger__new(appState, 4));

    /* create list, insert root element */
    LinkedList(CGInteger)* ll = LinkedList__new(appState, CGInteger, i1);
    assert(ll != NULL);
    assert(LinkedList_getRootElement(appState, CGInteger, ll) == i1);
    /* add element at end */
    LinkedList_addElement(appState, CGInteger, ll, i2);

    /* insert at end */
    LinkedList_insertElementAfter(appState, CGInteger, ll, i2, i3);

    /* insert in middle */
    LinkedList_insertElementAfter(appState, CGInteger, ll, i2, i4);

    LinkedListElement(CGInteger)* cur = LinkedList_moveToRootElement(appState, CGInteger, ll);
    assert(cur == i1);
    cur = LinkedList_moveToNextElement(appState, CGInteger, ll);
    assert(cur == i2);
    cur = LinkedList_moveToNextElement(appState, CGInteger, ll);
    assert(cur == i4);
    cur = LinkedList_moveToNextElement(appState, CGInteger, ll);
    assert(cur == i3);
    cur = LinkedList_moveToNextElement(appState, CGInteger, ll);
    assert(cur == NULL);

    cur = LinkedList_start(appState, CGInteger, ll);
    assert(cur == i1);
    cur = LinkedList_next(appState, CGInteger, ll);
    assert(cur == i2);
    cur = LinkedList_next(appState, CGInteger, ll);
    assert(cur == i4);
    cur = LinkedList_next(appState, CGInteger, ll);
    assert(cur == i3);
    cur = LinkedList_next(appState, CGInteger, ll);
    assert(cur == NULL);

    printf("ok\n");
}

void testRemove() {
    printf("%s...\n", __func__);

    LinkedListElement(CGInteger)* i1 = LinkedListElement__new(appState, CGInteger, CGInteger__new(appState, 1));
    LinkedListElement(CGInteger)* i2 = LinkedListElement__new(appState, CGInteger, CGInteger__new(appState, 2));
    LinkedListElement(CGInteger)* i3 = LinkedListElement__new(appState, CGInteger, CGInteger__new(appState, 3));
    LinkedListElement(CGInteger)* i4 = LinkedListElement__new(appState, CGInteger, CGInteger__new(appState, 4));

    /* create list, insert root element */
    LinkedList(CGInteger)* ll = LinkedList__new(appState, CGInteger, i1);
    assert(ll != NULL);
    assert(LinkedList_getRootElement(appState, CGInteger, ll) == i1);
    /* add elements at end */
    LinkedList_addElement(appState, CGInteger, ll, i2);
    LinkedList_addElement(appState, CGInteger, ll, i3);
    LinkedList_addElement(appState, CGInteger, ll, i4);

    LinkedListElement(CGInteger)* r = LinkedList_remove(appState, CGInteger, ll, i3);
    assert(r == i3);
    assert(LinkedListElement_getNextElement(appState, CGInteger, i2) == i4);
}

void testFind() {
    printf("%s...\n", __func__);

    LinkedListElement(CGInteger)* i1 = LinkedListElement__new(appState, CGInteger, CGInteger__new(appState, 1));
    LinkedListElement(CGInteger)* i2 = LinkedListElement__new(appState, CGInteger, CGInteger__new(appState, 2));
    LinkedListElement(CGInteger)* i3 = LinkedListElement__new(appState, CGInteger, CGInteger__new(appState, 3));
    LinkedListElement(CGInteger)* i4 = LinkedListElement__new(appState, CGInteger, CGInteger__new(appState, 4));

    /* create list, insert root element */
    LinkedList(CGInteger)* ll = LinkedList__new(appState, CGInteger, i1);
    assert(ll != NULL);
    assert(LinkedList_getRootElement(appState, CGInteger, ll) == i1);
    /* add elements at end */
    LinkedList_addElement(appState, CGInteger, ll, i2);
    LinkedList_addElement(appState, CGInteger, ll, i3);
    LinkedList_addElement(appState, CGInteger, ll, i4);

    CGInteger* tofind = CGInteger__new(appState, 1);
    LinkedListElement(CGInteger)* found = LinkedList_findElement(appState, CGInteger, ll, tofind, CGInteger__compare);
    assert(CGInteger_toInt(appState, tofind) == CGInteger_toInt(appState, LinkedListElement_getValue(appState, CGInteger, found)));

    CGInteger* foundCGInteger = LinkedList_findValue(appState, CGInteger, ll, tofind, CGInteger__compare);
    assert(CGInteger_toInt(appState, tofind) == CGInteger_toInt(appState, foundCGInteger));

    CGInteger_delete(appState, tofind);
    tofind = CGInteger__new(appState, 5);
    found = LinkedList_findElement(appState, CGInteger, ll, tofind, CGInteger__compare);
    assert(found == NULL);
    assert(CGAppState_catchCGExceptionWithID(appState, CGExceptionID_ElementNotFound) == true);

    foundCGInteger = LinkedList_findValue(appState, CGInteger, ll, tofind, CGInteger__compare);
    assert(foundCGInteger== NULL);
    assert(CGAppState_catchCGExceptionWithID(appState, CGExceptionID_ElementNotFound) == true);

    CGInteger_delete(appState, tofind);
    LinkedListElement_delete(appState, CGInteger, i1);
    LinkedListElement_delete(appState, CGInteger, i2);
    LinkedListElement_delete(appState, CGInteger, i3);
    LinkedListElement_delete(appState, CGInteger, i4);

    LinkedList_delete(appState, CGInteger, ll);

    printf("ok\n");
}


int main() {
    printf("=== %s ===\n", __FILE__);
    appState = CGAppState__new();

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
