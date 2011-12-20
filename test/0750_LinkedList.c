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

    Integer* i = Integer__new(22);
    LinkedListElement(Integer)* lle = LinkedListElement__new(appState, Integer, i);
    LinkedListElement_delete(appState, lle);
    Integer_delete(i);
    
    printf("ok\n");
}


int main() {
    appState = AppState__new();
    testElementNewDelete();
    AppState_delete(appState);
    return 0;
}
