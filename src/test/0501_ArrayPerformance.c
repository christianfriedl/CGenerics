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
    printf("%s... ", __func__);

    CGArray(int)* intCGArray = CGArray__new(int, 1);

    int i;
    int *x;
    for (i=0; i < 200000; ++i) {
        x = malloc(sizeof(*x));
        if (x) {
            *x = i;
            CGArray_push(int, intCGArray, x);
        } else printf("unable to alloc at %i\n", i);
    }
    printf("cap %u size %u\n", CGArray_getCapacity(int, intCGArray), CGArray_getSize(appState, int, intCGArray));
    for (i=0; i < 200000; ++i) {
        x = CGArray_pop(int, intCGArray);
        int_delete(x);
    }
    printf("cap %u size %u\n", CGArray_getCapacity(int, intCGArray), CGArray_getSize(appState, int, intCGArray));
    printf("ok -- ");
}
void testManyShifts() {
    printf("%s... ", __func__);

    CGArray(int)* intCGArray = CGArray__new(int, 1);

    int i;
    int *x;
    for (i=0; i < 200000; ++i) {
        x = malloc(sizeof(*x));
        CGArray_unshift(int, intCGArray, x);
    } 
    printf("cap %u size %u\n", CGArray_getCapacity(int, intCGArray), CGArray_getSize(appState, int, intCGArray));
    for (i=0; i < 200000; ++i) {
        x = CGArray_shift(int, intCGArray);
        int_delete(x);
    }
    printf("cap %u size %u\n", CGArray_getCapacity(int, intCGArray), CGArray_getSize(appState, int, intCGArray));

    //printCGArray(intCGArray);   
    CGArray_delete(int, intCGArray);
    printf("ok -- ");
}

int main() {
    CGAppState__init(__FILE__);
    appState = CGAppState__getInstance();
    
    testManyPushes();
    testManyShifts();

    CGAppState__deInit();
    return 0;
}
