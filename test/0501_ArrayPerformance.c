#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include"Array.h"
#include"AppState.h"

AppState* appState;

INIT_ARRAY(int)

void testManyPushes() {
    printf("%s...\n", __func__);

    Array(int)* intArray = Array__new(appState, int, 1);

    int i;
    for (i=0; i < 200000; ++i)
        Array_push(appState, int, intArray, i);
    printf("cap %u size %u\n", Array_getCapacity(appState, int, intArray), Array_getSize(appState, int, intArray));
    for (i=0; i < 200000; ++i)
        Array_pop(appState, int, intArray);
    printf("cap %u size %u\n", Array_getCapacity(appState, int, intArray), Array_getSize(appState, int, intArray));
    printf("ok\n");
}
void testManyShifts() {
    printf("%s...\n", __func__);

    Array(int)* intArray = Array__new(appState, int, 1);

    int i;
    for (i=0; i < 200000; ++i)
        Array_unshift(appState, int, intArray, i);
    printf("cap %u size %u\n", Array_getCapacity(appState, int, intArray), Array_getSize(appState, int, intArray));
    for (i=0; i < 200000; ++i)
        Array_shift(appState, int, intArray);
    printf("cap %u size %u\n", Array_getCapacity(appState, int, intArray), Array_getSize(appState, int, intArray));

    //printArray(intArray);   
    Array_delete(appState, int, intArray);
    printf("ok\n");
}

int main() {
    appState = AppState__new();
    
    testManyPushes();
    testManyShifts();

    AppState_delete(appState);
    return 0;
}
