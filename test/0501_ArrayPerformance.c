#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include"CGArray.h"
#include"CGAppState.h"

CGAppState* appState;
void int_delete(int* this) {
    free(this);
}

INIT_ARRAY(int)

void testManyPushes() {
    printf("%s...\n", __func__);

    CGArray(int)* intCGArray = CGArray__new(appState, int, 1);

    int i;
    int *x;
    for (i=0; i < 200000; ++i) {
        x = malloc(sizeof(*x));
        if (x) {
            *x = i;
            CGArray_push(appState, int, intCGArray, x);
        } else printf("unable to alloc at %i\n", i);
    }
    printf("cap %u size %u\n", CGArray_getCapacity(appState, int, intCGArray), CGArray_getSize(appState, int, intCGArray));
    for (i=0; i < 200000; ++i) {
        x = CGArray_pop(appState, int, intCGArray);
        int_delete(x);
    }
    printf("cap %u size %u\n", CGArray_getCapacity(appState, int, intCGArray), CGArray_getSize(appState, int, intCGArray));
    printf("ok\n");
}
void testManyShifts() {
    printf("%s...\n", __func__);

    CGArray(int)* intCGArray = CGArray__new(appState, int, 1);

    int i;
    int *x;
    for (i=0; i < 200000; ++i) {
        x = malloc(sizeof(*x));
        CGArray_unshift(appState, int, intCGArray, x);
    } 
    printf("cap %u size %u\n", CGArray_getCapacity(appState, int, intCGArray), CGArray_getSize(appState, int, intCGArray));
    for (i=0; i < 200000; ++i) {
        x = CGArray_shift(appState, int, intCGArray);
        int_delete(x);
    }
    printf("cap %u size %u\n", CGArray_getCapacity(appState, int, intCGArray), CGArray_getSize(appState, int, intCGArray));

    //printCGArray(intCGArray);   
    CGArray_delete(appState, int, intCGArray);
    printf("ok\n");
}

int main() {
    appState = CGAppState__new();
    
    testManyPushes();
    testManyShifts();

    CGAppState_delete(appState);
    return 0;
}
