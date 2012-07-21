#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include"CGArray.h"
#include"CGAppState.h"

#define numberOfElements (100000)

CGAppState* appState;


time_t lastTime = 0;
double diffSeconds = 0;
void startClock(char* operation) {
    printf("starting operation '%s'...\n", operation);
    lastTime = time(NULL);
}
void stopClock() {
    diffSeconds = difftime(time(NULL), lastTime);
}
void printClock() {
    printf("%ld %ld operation took %.5f seconds\n", lastTime, time(NULL), diffSeconds);
}
void int_delete(int* this) {
    free(this);
}

int* int_clone(const int* this) {
    int* that = malloc(sizeof(*that));
    *that = *this;
    return that;
}

INIT_ARRAY(int)

void testManyPushes() {
    printf("%s... ", __func__);

    CGArray(int)* intCGArray = CGArray__new(int, 1);

    int i;
    int *x;
    startClock("push");
    for (i=0; i < numberOfElements; ++i) {
        x = malloc(sizeof(*x));
        if (x) {
            *x = i;
            CGArray_push(int, intCGArray, x);
        } else printf("unable to alloc at %i\n", i);
        assert(!CGAppState_isExceptionRaised(appState));
    }
    stopClock();
    printf("capacity %u size %u\n", CGArray_getCapacity(int, intCGArray), CGArray_getSize(int, intCGArray));
    printClock();
    startClock("pop");
    for (i=0; i < numberOfElements; ++i) {
        x = CGArray_pop(int, intCGArray);
        int_delete(x);
    }
    stopClock();
    printf("capacity %u size %u\n", CGArray_getCapacity(int, intCGArray), CGArray_getSize(int, intCGArray));
    printClock();
    printf("ok -- ");
}
void testManyShifts() {
    printf("%s... ", __func__);

    CGArray(int)* intCGArray = CGArray__new(int, 1);

    int i;
    int *x;
    startClock("unshift");
    for (i=0; i < numberOfElements; ++i) {
        x = malloc(sizeof(*x));
        CGArray_unshift(int, intCGArray, x);
        assert(!CGAppState_isExceptionRaised(appState));
    }
    stopClock();
    printf("capacity %u size %u\n", CGArray_getCapacity(int, intCGArray), CGArray_getSize(int, intCGArray));
    printClock();
    startClock("shift");
    for (i=0; i < numberOfElements; ++i) {
        x = CGArray_shift(int, intCGArray);
        int_delete(x);
        assert(!CGAppState_isExceptionRaised(appState));
    }
    stopClock();
    printf("capacity %u size %u\n", CGArray_getCapacity(int, intCGArray), CGArray_getSize(int, intCGArray));
    printClock();

    //printCGArray(intCGArray);   
    CGArray_delete(int, intCGArray);
    printf("ok -- ");
}

int main() {
    CGAppState__init(__FILE__);
    appState = CGAppState__getInstance();

    printf("Testing CGArray with %d elements\n", numberOfElements);
    
    testManyPushes();
    testManyShifts();

    CGAppState__deInit();
    return 0;
}
