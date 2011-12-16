#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include"AppState.h"
#include"Array.h"

typedef struct {
    char first_name[20];
    char last_name[20];
} Person;

typedef int* intPtr;

INIT_ARRAY(int)
INIT_ARRAY(intPtr)
INIT_ARRAY(Person)

AppState *appState;

void printArray(Array(int)* array) {
    unsigned i;
    for (i = 0; i < Array_getSize(int, array); ++i)
        printf("%i ", Array_getValueAt(int, array, i));
    printf("\n");
}
void testArrayNewDelete() {
    printf("%s...\n", __func__);

    Array(int)* intArray = Array__new(int, 20);
    Array(intPtr)* intPtrArray = Array__new(intPtr, 20);
    Array(Person)* personArray = Array__new(Person, 20);

    Array_delete(int, intArray);
    Array_delete(intPtr, intPtrArray);
    Array_delete(Person, personArray);
    
    printf("ok\n");
}

void testIntArray() {
    printf("%s...\n", __func__);
    int x;
    Array(int)* array = Array__new(int, 20);

    printf("capacity: %u\n", Array_getCapacity(int, array));

    Array_add(int, array, 2);
    Array_add(int, array, 3);
    Array_push(int, array, 4);

    printf("size: %u\n", Array_getSize(int, array));
    assert(Array_getSize(int, array) == 3);

    x = Array_shift(int, array);
    printf("x from shift: %u\n", x);
    printf("after shift %u %u\n", Array_getValueAt(int, array, 0), Array_getValueAt(int, array, 1));

    printf("size: %u\n", Array_getSize(int, array));
    assert(Array_getSize(int, array) == 2);

    Array_unshift(int, array, x);

    x = Array_getValueAt(int, array, 0);
    printf("x@0: %u\n", x);
    assert(x == 2);
    x = Array_getValueAt(int, array, 1);
    printf("x@1: %u\n", x);
    assert(x == 3);
    x = Array_getValueAt(int, array, 2);
    printf("x@2: %u\n", x);
    assert(x == 4);

    Array_insertValueAt(int, array, 2, 0);
    assert(Array_getSize(int, array) == 4);
    assert(Array_getValueAt(int, array, 0) == 2);
    assert(Array_getValueAt(int, array, 1) == 2);
    assert(Array_getValueAt(int, array, 2) == 3);
    assert(Array_getValueAt(int, array, 3) == 4);
    printArray(array);
    Array_removeValueAt(int, array, 0);
    assert(Array_getSize(int, array) == 3);
    printArray(array);
    Array_insertValueAt(int, array, 3, 1);
    assert(Array_getSize(int, array) == 4);
    assert(Array_getValueAt(int, array, 0) == 2);
    assert(Array_getValueAt(int, array, 1) == 3);
    assert(Array_getValueAt(int, array, 2) == 3);
    assert(Array_getValueAt(int, array, 3) == 4);
    printArray(array);
    Array_removeValueAt(int, array, 1);
    assert(Array_getSize(int, array) == 3);
    printArray(array);
    Array_insertValueAt(int, array, 4, 2);
    assert(Array_getSize(int, array) == 4);
    assert(Array_getValueAt(int, array, 0) == 2);
    assert(Array_getValueAt(int, array, 1) == 3);
    assert(Array_getValueAt(int, array, 2) == 4);
    assert(Array_getValueAt(int, array, 3) == 4);
    printArray(array);
    Array_removeValueAt(int, array, 2);
    assert(Array_getSize(int, array) == 3);
    printArray(array);
    Array_insertValueAt(int, array, 5, 3);
    assert(Array_getSize(int, array) == 4);
    assert(Array_getValueAt(int, array, 0) == 2);
    assert(Array_getValueAt(int, array, 1) == 3);
    assert(Array_getValueAt(int, array, 2) == 4);
    assert(Array_getValueAt(int, array, 3) == 5);
    printArray(array);
    Array_removeValueAt(int, array, 3);
    assert(Array_getSize(int, array) == 3);
    assert(Array_getValueAt(int, array, 0) == 2);
    assert(Array_getValueAt(int, array, 1) == 3);
    assert(Array_getValueAt(int, array, 2) == 4);
    printArray(array);

    x = Array_pop(int, array);
    printf("x@2: %u\n", x);
    assert(x == 4);
    x = Array_pop(int, array);
    printf("x@1: %u\n", x);
    assert(x == 3);
    x = Array_pop(int, array);
    printf("x@0: %u\n", x);
    assert(x == 2);

    printf("size: %u\n", Array_getSize(int, array));
    assert(Array_getSize(int, array) == 0);

    Array_delete(int, array);

    printf("ok\n");
}
void testPersonArray() {
    printf("%s...\n", __func__);
    Person x, y;
    Array(Person)* array = Array__new(Person, 20);
    strcpy(x.first_name, "Christian");
    strcpy(x.last_name, "Friedl");
    Array_push(Person, array, x);
    y = Array_getValueAt(Person, array, 0);
    printf("%s %s\n", y.first_name, y.last_name);
    assert(!strcmp(y.first_name, x.first_name));
    assert(!strcmp(y.last_name, x.last_name));
    strcpy(x.first_name, "Cornelia");
    strcpy(x.last_name, "Nalepka");
    Array_push(Person, array, x);
    y = Array_getValueAt(Person, array, 1);
    printf("%s %s\n", y.first_name, y.last_name);
    assert(!strcmp(y.first_name, x.first_name));
    assert(!strcmp(y.last_name, x.last_name));

    Array_delete(Person, array);

    printf("ok\n");
}

void testManyPushes() {
    printf("%s...\n", __func__);

    Array(int)* intArray = Array__new(int, 1);

    int i;
    for (i=0; i < 200000; ++i)
        Array_push(int, intArray, i);
    printf("cap %u size %u\n", Array_getCapacity(int, intArray), Array_getSize(int, intArray));
    for (i=0; i < 200000; ++i)
        Array_pop(int, intArray);
    printf("cap %u size %u\n", Array_getCapacity(int, intArray), Array_getSize(int, intArray));
    for (i=0; i < 200000; ++i)
        Array_unshift(int, intArray, i);
    printf("cap %u size %u\n", Array_getCapacity(int, intArray), Array_getSize(int, intArray));
    for (i=0; i < 200000; ++i)
        Array_shift(int, intArray);
    printf("cap %u size %u\n", Array_getCapacity(int, intArray), Array_getSize(int, intArray));

    //printArray(intArray);   
    Array_delete(int, intArray);

    printf("ok\n");
}

void testArrayGrow() {
    printf("%s...\n", __func__);

    Array(int)* intArray = Array__new(int, 1);

    Array_insertValueAt(int, intArray, 20, 20);
    assert(Array_getValueAt(int, intArray, 20) == 20);
    printf("%u\n", Array_getCapacity(int, intArray));
    assert(Array_getCapacity(int, intArray) >= 21);
    assert(Array_getSize(int, intArray) == 21);

    Array_delete(int, intArray);

    printf("ok\n");
}

void testExceptions() {
    printf("%s...\n", __func__);

    Array(int)* intArray = Array__new(int, 1);
    Array_removeValueAt(int, intArray, 1);
    if (AppState_isExceptionRaisedWithID(appState, ExceptionID_ArrayIndexOutOfBounds))
        printf("Exception caught, msg was '%s'\n", (AppState_getException(appState))->msg);
    assert(AppState_isExceptionRaisedWithID(appState, ExceptionID_ArrayIndexOutOfBounds));
    AppState_catchException(appState);
    Array_pop(int, intArray);
    if (AppState_isExceptionRaised(appState))
        printf("Exception caught, msg was '%s'\n", (AppState_getException(appState))->msg);
    AppState_catchException(appState);
    Array_shift(int, intArray);
    if (AppState_isExceptionRaised(appState))
        printf("Exception caught, msg was '%s'\n", (AppState_getException(appState))->msg);
    AppState_catchException(appState);
    Array_getValueAt(int, intArray, 20);
    if (AppState_isExceptionRaised(appState))
        printf("Exception caught, msg was '%s'\n", (AppState_getException(appState))->msg);
    AppState_catchException(appState);

    Array_delete(int, intArray);

    printf("ok\n");
}

int intComparison(const int *i1, const int *i2) {
    return ((*i1 < *i2) ? -1 : (*i1 == *i2) ? 0 : 1);
}
int intComparisonReversed(const int *i1, const int *i2) {
    return ((*i1 < *i2) ? 1 : (*i1 == *i2) ? 0 : -1);
}

void testSorting() {
    printf("%s...\n", __func__);

    Array(int)* intArray = Array__new(int, 20);
    int i;
    srandom(time(NULL));
    for (i=0; i < 20; ++i)
        Array_push(int, intArray, random() % 65536);
    printf("unsorted: ");
    Array_print(int, intArray, "%i");
    Array_qsort(int, intArray, intComparison);
    printf("sorted: ");
    Array_print(int, intArray, "%i");
    for (i=0; i < 19; ++i)
        assert(Array_getValueAt(int, intArray, i) <= Array_getValueAt(int, intArray, i+1));
    Array_qsort(int, intArray, intComparisonReversed);
    printf("sorted reversed: ");
    Array_print(int, intArray, "%i");
    for (i=0; i < 19; ++i)
        assert(Array_getValueAt(int, intArray, i) >= Array_getValueAt(int, intArray, i+1));

    Array_delete(int, intArray);

    printf("ok\n");
}

void testSearch() {
    printf("%s...\n", __func__);

    Array(int)* intArray = Array__new(int, 20);
    int i;
    srandom(time(NULL));
    for (i=0; i < 20; ++i)
        Array_push(int, intArray, i);

    int x = 2;
    i = Array_searchIndex(int, intArray, &x, intComparison);
    printf("%u\n", i);
    assert(i == 2);
    x = 20;
    i = Array_searchIndex(int, intArray, &x, intComparison);
    printf("%u\n", i);
    assert(i == 0);
    assert(AppState_catchExceptionWithID(appState, ExceptionID_ElementNotFound) == true);

    Array_delete(int, intArray);

    printf("ok\n");
}


int main() {
    appState = AppState__new();
    testArrayNewDelete();
    testIntArray();
    testPersonArray();
    testExceptions();
    testArrayGrow();
    testSorting();
    testSearch();
    //testManyPushes();
    AppState_delete(appState);
    return 0;
}
