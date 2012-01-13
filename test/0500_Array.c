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

typedef int Int;

Int* Int__new(int value) {
    Int* this = malloc(sizeof(*this));
    /* TODO exception */
    *this = value;
    return this;
}
void Int_delete(int* this) {
    free(this);
}
void Person_delete(Person* this) {
    free(this);
}

INIT_ARRAY(Int)
INIT_ARRAY(Person)

AppState *appState;

void printArray(Array(Int)* array) {
    unsigned i;
    for (i = 0; i < Array_getSize(appState, Int, array); ++i)
        printf("%i ", *(Array_getValueAt(appState, Int, array, i)));
    printf("\n");
}
void testArrayNewDelete() {
    printf("%s...\n", __func__);

    Array(Int)* intArray = Array__new(appState, Int, 20);
    Array(Person)* personArray = Array__new(appState, Person, 20);

    Array_deleteValues(appState, Int, intArray);
    Array_delete(appState, Int, intArray);
    Array_deleteValues(appState, Person, personArray);
    Array_delete(appState, Person, personArray);
    
    printf("ok\n");
}

void testIntArray() {
    printf("%s...\n", __func__);
    Int *x;
    Array(Int)* array = Array__new(appState, Int, 20);

    printf("capacity: %u\n", Array_getCapacity(appState, Int, array));

    x = Int__new(2);
    Array_add(appState, Int, array, x);
    x = Int__new(3);
    Array_add(appState, Int, array, x);
    x = Int__new(4);
    Array_push(appState, Int, array, x);

    printf("size: %u\n", Array_getSize(appState, Int, array));
    assert(Array_getSize(appState, Int, array) == 3);

    x = Array_shift(appState, Int, array);
    printf("x from shift: %u\n", *x);
    printf("after shift %u %u\n", *(Array_getValueAt(appState, Int, array, 0)), *(Array_getValueAt(appState, Int, array, 1)));

    printf("size: %u\n", Array_getSize(appState, Int, array));
    assert(Array_getSize(appState, Int, array) == 2);

    x = Int__new(2);
    Array_unshift(appState, Int, array, x);

    x = Array_getValueAt(appState, Int, array, 0);
    printf("x@0: %u\n", *x);
    assert(*x == 2);
    x = Array_getValueAt(appState, Int, array, 1);
    printf("x@1: %u\n", *x);
    assert(*x == 3);
    x = Array_getValueAt(appState, Int, array, 2);
    printf("x@2: %u\n", *x);
    assert(*x == 4);

    x = Int__new(2);
    Array_insertValueAt(appState, Int, array, x, 0);
    assert(Array_getSize(appState, Int, array) == 4);
    assert(*(Array_getValueAt(appState, Int, array, 0)) == 2);
    assert(*(Array_getValueAt(appState, Int, array, 1)) == 2);
    assert(*(Array_getValueAt(appState, Int, array, 2)) == 3);
    assert(*(Array_getValueAt(appState, Int, array, 3)) == 4);
    printArray(array);
    Array_removeValueAt(appState, Int, array, 0);
    assert(Array_getSize(appState, Int, array) == 3);
    printArray(array);
    x = Int__new(3);
    Array_insertValueAt(appState, Int, array, x, 1);
    assert(Array_getSize(appState, Int, array) == 4);
    assert(*Array_getValueAt(appState, Int, array, 0) == 2);
    assert(*Array_getValueAt(appState, Int, array, 1) == 3);
    assert(*Array_getValueAt(appState, Int, array, 2) == 3);
    assert(*Array_getValueAt(appState, Int, array, 3) == 4);
    printArray(array);
    Array_removeValueAt(appState, Int, array, 1);
    assert(Array_getSize(appState, Int, array) == 3);
    printArray(array);
    x = Int__new(4);
    Array_insertValueAt(appState, Int, array, x, 2);
    assert(Array_getSize(appState, Int, array) == 4);
    assert(*Array_getValueAt(appState, Int, array, 0) == 2);
    assert(*Array_getValueAt(appState, Int, array, 1) == 3);
    assert(*Array_getValueAt(appState, Int, array, 2) == 4);
    assert(*Array_getValueAt(appState, Int, array, 3) == 4);
    printArray(array);
    Array_removeValueAt(appState, Int, array, 2);
    assert(Array_getSize(appState, Int, array) == 3);
    printArray(array);
    x = Int__new(5);
    Array_insertValueAt(appState, Int, array, x, 3);
    assert(Array_getSize(appState, Int, array) == 4);
    assert(*Array_getValueAt(appState, Int, array, 0) == 2);
    assert(*Array_getValueAt(appState, Int, array, 1) == 3);
    assert(*Array_getValueAt(appState, Int, array, 2) == 4);
    assert(*Array_getValueAt(appState, Int, array, 3) == 5);
    printArray(array);
    Array_removeValueAt(appState, Int, array, 3);
    assert(Array_getSize(appState, Int, array) == 3);
    assert(*Array_getValueAt(appState, Int, array, 0) == 2);
    assert(*Array_getValueAt(appState, Int, array, 1) == 3);
    assert(*Array_getValueAt(appState, Int, array, 2) == 4);
    printArray(array);

    x = Array_pop(appState, Int, array);
    printf("x@2: %u\n", *x);
    assert(*x == 4);
    x = Array_pop(appState, Int, array);
    printf("x@1: %u\n", *x);
    assert(*x == 3);
    x = Array_pop(appState, Int, array);
    printf("x@0: %u\n", *x);
    assert(*x == 2);

    printf("size: %u\n", Array_getSize(appState, Int, array));
    assert(Array_getSize(appState, Int, array) == 0);

    Array_delete(appState, Int, array);

    printf("ok\n");
}
void testPersonArray() {
    printf("%s...\n", __func__);
    Person* x = malloc(sizeof(*x));
    Person* y = malloc(sizeof(*y));
    Array(Person)* array = Array__new(appState, Person, 20);
    strcpy(x->first_name, "Christian");
    strcpy(x->last_name, "Friedl");
    Array_push(appState, Person, array, x);
    y = Array_getValueAt(appState, Person, array, 0);
    printf("%s %s\n", y->first_name, y->last_name);
    assert(!strcmp(y->first_name, x->first_name));
    assert(!strcmp(y->last_name, x->last_name));
    x = malloc(sizeof(*x));
    strcpy(x->first_name, "Cornelia");
    strcpy(x->last_name, "Nalepka");
    Array_push(appState, Person, array, x);
    y = Array_getValueAt(appState, Person, array, 1);
    printf("%s %s\n", y->first_name, y->last_name);
    assert(!strcmp(y->first_name, x->first_name));
    assert(!strcmp(y->last_name, x->last_name));

    Array_deleteValues(appState, Person, array);
    Array_delete(appState, Person, array);

    printf("ok\n");
}

void testArrayGrow() {
    printf("%s...\n", __func__);

    Array(Int)* intArray = Array__new(appState, Int, 1);

    Int *x = Int__new(20);
    Array_insertValueAt(appState, Int, intArray, x, 20);
    assert(*Array_getValueAt(appState, Int, intArray, 20) == 20);
    printf("%u\n", Array_getCapacity(appState, Int, intArray));
    assert(Array_getCapacity(appState, Int, intArray) >= 21);
    assert(Array_getSize(appState, Int, intArray) == 21);

    Array_delete(appState, Int, intArray);

    free(x);
    printf("ok\n");
}

void testExceptions() {
    printf("%s...\n", __func__);

    Array(Int)* intArray = Array__new(appState, Int, 1);
    Array_removeValueAt(appState, Int, intArray, 1);
    if (AppState_isExceptionRaisedWithID(appState, ExceptionID_ArrayIndexOutOfBounds))
        printf("Exception caught, msg was '%s'\n", (AppState_getException(appState))->msg);
    assert(AppState_isExceptionRaisedWithID(appState, ExceptionID_ArrayIndexOutOfBounds));
    AppState_catchException(appState);
    Array_pop(appState, Int, intArray);
    if (AppState_isExceptionRaised(appState))
        printf("Exception caught, msg was '%s'\n", (AppState_getException(appState))->msg);
    AppState_catchException(appState);
    Array_shift(appState, Int, intArray);
    if (AppState_isExceptionRaised(appState))
        printf("Exception caught, msg was '%s'\n", (AppState_getException(appState))->msg);
    AppState_catchException(appState);
    Array_getValueAt(appState, Int, intArray, 20);
    if (AppState_isExceptionRaised(appState))
        printf("Exception caught, msg was '%s'\n", (AppState_getException(appState))->msg);
    AppState_catchException(appState);

    Array_delete(appState, Int, intArray);

    printf("ok\n");
}

int intComparison(const Int **i1, const Int **i2) {
    return ((**i1 < **i2) ? -1 : (**i1 == **i2) ? 0 : 1);
}
int intComparisonReversed(const Int **i1, const Int **i2) {
    return ((**i1 < **i2) ? 1 : (**i1 == **i2) ? 0 : -1);
}

void testSorting() {
    printf("%s...\n", __func__);

    Array(Int)* intArray = Array__new(appState, Int, 20);
    int i;
    srandom(time(NULL));
    for (i=0; i < 20; ++i) {
        Int *x = Int__new(random() % 65536);
        Array_push(appState, Int, intArray, x);
    }
    printf("unsorted: ");
    Array_print(appState, Int, intArray, "%i");
    Array_qsort(appState, Int, intArray, intComparison);
    printf("sorted: ");
    Array_print(appState, Int, intArray, "%i");
    for (i=0; i < 19; ++i)
        assert(*Array_getValueAt(appState, Int, intArray, i) <= *Array_getValueAt(appState, Int, intArray, i+1));
    Array_qsort(appState, Int, intArray, intComparisonReversed);
    printf("sorted reversed: ");
    Array_print(appState, Int, intArray, "%i");
    for (i=0; i < 19; ++i)
        assert(*Array_getValueAt(appState, Int, intArray, i) >= *Array_getValueAt(appState, Int, intArray, i+1));

    Array_deleteValues(appState, Int, intArray);
    Array_delete(appState, Int, intArray);

    printf("ok\n");
}

void testSearch() {
    printf("%s...\n", __func__);

    Array(Int)* intArray = Array__new(appState, Int, 20);
    int i;
    srandom(time(NULL));
    for (i=0; i < 20; ++i) {
        Int* x = Int__new(i);
        Array_push(appState, Int, intArray, x);
    }

    Int *x = Int__new(2);
    i = Array_findIndex(appState, Int, intArray, (const Int*)x, intComparison);
    printf("%u\n", i);
    assert(i == 2);
    x = Int__new(20);
    i = Array_findIndex(appState, Int, intArray, (const Int*)x, intComparison);
    printf("%u\n", i);
    assert(i == 0);
    assert(AppState_catchExceptionWithID(appState, ExceptionID_ElementNotFound) == true);

    Array_deleteValues(appState, Int, intArray);
    Array_delete(appState, Int, intArray);

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
