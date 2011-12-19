#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include"Array.h"
#include"AppState.h"

AppState* appState;
void int_delete(int* this) {
    free(this);
}

INIT_ARRAY(int)

void testManyPushes() {
    printf("%s...\n", __func__);

    Array(int)* intArray = Array__new(appState, int, 1);

    int i;
    int *x;
    for (i=0; i < 200000; ++i) {
        x = malloc(sizeof(*x));
        if (x) {
            *x = i;
            Array_push(appState, int, intArray, x);
        } else printf("unable to alloc at %i\n", i);
    }
    printf("cap %u size %u\n", Array_getCapacity(appState, int, intArray), Array_getSize(appState, int, intArray));
    for (i=0; i < 200000; ++i) {
        x = Array_pop(appState, int, intArray);
        int_delete(x);
    }
    printf("cap %u size %u\n", Array_getCapacity(appState, int, intArray), Array_getSize(appState, int, intArray));
    printf("ok\n");
}
void testManyShifts() {
    printf("%s...\n", __func__);

    Array(int)* intArray = Array__new(appState, int, 1);

    int i;
    int *x;
    for (i=0; i < 200000; ++i) {
        x = malloc(sizeof(*x));
        Array_unshift(appState, int, intArray, x);
    } 
    printf("cap %u size %u\n", Array_getCapacity(appState, int, intArray), Array_getSize(appState, int, intArray));
    for (i=0; i < 200000; ++i) {
        x = Array_shift(appState, int, intArray);
        int_delete(x);
    }
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
