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

void testInsertElementAfter() {
    /* insert first element */
    /* insert at end */
    /* insert in middle */
}


int main() {
    appState = AppState__new();
    testElementNewDelete();
    AppState_delete(appState);
    return 0;
}
