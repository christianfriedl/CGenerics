#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include"AppState.h"
#include"Integer.h"
#include"LinkedList.h"

INIT_LINKEDLIST(Integer)

AppState *appState;

void testElementNewDelete() {
    printf("%s...\n", __func__);

    Integer* i = Integer__new(appState, 22);
    assert(i != NULL);
    assert(*i == 22);
    LinkedListElement(Integer)* lle = LinkedListElement__new(appState, Integer, i);
    assert(lle != NULL);
    assert(LinkedListElement_getValue(appState, Integer, lle) == i);
    LinkedListElement_delete(appState, Integer, lle);
    Integer_delete(appState, i);
    
    printf("ok\n");
}

void testListNewDelete() {
    printf("%s...\n", __func__);

    LinkedListElement(Integer)* i1 = LinkedListElement__new(appState, Integer, Integer__new(appState, 1));
    LinkedList(Integer)* ll = LinkedList__new(appState, Integer, i1);
    LinkedList_delete(appState, Integer, ll);
    LinkedListElement_delete(appState, Integer, i1);
    
    printf("ok\n");
}
void testInsertElements() {
    printf("%s...\n", __func__);

    LinkedListElement(Integer)* i1 = LinkedListElement__new(appState, Integer, Integer__new(appState, 1));
    LinkedListElement(Integer)* i2 = LinkedListElement__new(appState, Integer, Integer__new(appState, 2));
    LinkedListElement(Integer)* i3 = LinkedListElement__new(appState, Integer, Integer__new(appState, 3));
    LinkedListElement(Integer)* i4 = LinkedListElement__new(appState, Integer, Integer__new(appState, 4));

    /* create list, insert root element */
    LinkedList(Integer)* ll = LinkedList__new(appState, Integer, i1);
    assert(ll != NULL);
    assert(LinkedList_getRootElement(appState, Integer, ll) == i1);
    /* add element at end */
    LinkedList_addElement(appState, Integer, ll, i2);

    /* insert at end */
    LinkedList_insertElementAfter(appState, Integer, ll, i2, i3);

    /* insert in middle */
    LinkedList_insertElementAfter(appState, Integer, ll, i2, i4);

    LinkedListElement(Integer)* cur = LinkedList_getRootElement(appState, Integer, ll);
    assert(cur == i1);
    cur = LinkedListElement_getNextElement(appState, Integer, cur);
    assert(cur == i2);
    cur = LinkedListElement_getNextElement(appState, Integer, cur);
    assert(cur == i4);
    cur = LinkedListElement_getNextElement(appState, Integer, cur);
    assert(cur == i3);
    cur = LinkedListElement_getNextElement(appState, Integer, cur);
    assert(cur == NULL);
    
    LinkedList_delete(appState, Integer, ll);
    LinkedListElement_delete(appState, Integer, i1);
    LinkedListElement_delete(appState, Integer, i2);
    LinkedListElement_delete(appState, Integer, i3);
    LinkedListElement_delete(appState, Integer, i4);
    printf("ok\n");
}

void testMoveToNext() {
    printf("%s...\n", __func__);

    LinkedListElement(Integer)* i1 = LinkedListElement__new(appState, Integer, Integer__new(appState, 1));
    LinkedListElement(Integer)* i2 = LinkedListElement__new(appState, Integer, Integer__new(appState, 2));
    LinkedListElement(Integer)* i3 = LinkedListElement__new(appState, Integer, Integer__new(appState, 3));
    LinkedListElement(Integer)* i4 = LinkedListElement__new(appState, Integer, Integer__new(appState, 4));

    /* create list, insert root element */
    LinkedList(Integer)* ll = LinkedList__new(appState, Integer, i1);
    assert(ll != NULL);
    assert(LinkedList_getRootElement(appState, Integer, ll) == i1);
    /* add element at end */
    LinkedList_addElement(appState, Integer, ll, i2);

    /* insert at end */
    LinkedList_insertElementAfter(appState, Integer, ll, i2, i3);

    /* insert in middle */
    LinkedList_insertElementAfter(appState, Integer, ll, i2, i4);

    LinkedListElement(Integer)* cur = LinkedList_moveToRootElement(appState, Integer, ll);
    assert(cur == i1);
    cur = LinkedList_moveToNextElement(appState, Integer, ll);
    assert(cur == i2);
    cur = LinkedList_moveToNextElement(appState, Integer, ll);
    assert(cur == i4);
    cur = LinkedList_moveToNextElement(appState, Integer, ll);
    assert(cur == i3);
    cur = LinkedList_moveToNextElement(appState, Integer, ll);
    assert(cur == NULL);

    cur = LinkedList_start(appState, Integer, ll);
    assert(cur == i1);
    cur = LinkedList_next(appState, Integer, ll);
    assert(cur == i2);
    cur = LinkedList_next(appState, Integer, ll);
    assert(cur == i4);
    cur = LinkedList_next(appState, Integer, ll);
    assert(cur == i3);
    cur = LinkedList_next(appState, Integer, ll);
    assert(cur == NULL);

    printf("ok\n");
}

void testRemove() {
    printf("%s...\n", __func__);

    LinkedListElement(Integer)* i1 = LinkedListElement__new(appState, Integer, Integer__new(appState, 1));
    LinkedListElement(Integer)* i2 = LinkedListElement__new(appState, Integer, Integer__new(appState, 2));
    LinkedListElement(Integer)* i3 = LinkedListElement__new(appState, Integer, Integer__new(appState, 3));
    LinkedListElement(Integer)* i4 = LinkedListElement__new(appState, Integer, Integer__new(appState, 4));

    /* create list, insert root element */
    LinkedList(Integer)* ll = LinkedList__new(appState, Integer, i1);
    assert(ll != NULL);
    assert(LinkedList_getRootElement(appState, Integer, ll) == i1);
    /* add elements at end */
    LinkedList_addElement(appState, Integer, ll, i2);
    LinkedList_addElement(appState, Integer, ll, i3);
    LinkedList_addElement(appState, Integer, ll, i4);

    LinkedListElement(Integer)* r = LinkedList_remove(appState, Integer, ll, i3);
    assert(r == i3);
    assert(LinkedListElement_getNextElement(appState, Integer, i2) == i4);
}


int main() {
    appState = AppState__new();

    testElementNewDelete();
    testListNewDelete();
    testInsertElements();
    testMoveToNext();
    testRemove();

    AppState_delete(appState);
    return 0;
}
