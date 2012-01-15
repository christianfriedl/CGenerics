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
Int* Int_clone(AppState* appState, Int* this) {
    return Int__new(*this);
}
void Int_delete(int* this) {
    free(this);
}
Person* Person_clone(AppState* appState, Person* this) {
    return NULL; /* stub, unneeded */
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
void testNewDelete() {
    printf("%s...\n", __func__);

    Array(Int)* intArray = Array__new(appState, Int, 20);
    Array(Person)* personArray = Array__new(appState, Person, 20);

    Array_deleteValues(appState, Int, intArray);
    Array_delete(appState, Int, intArray);
    Array_deleteValues(appState, Person, personArray);
    Array_delete(appState, Person, personArray);
    
    printf("ok\n");
}

void testClone() {
    printf("%s...\n", __func__);

    Array(Int)* intArray = Array__new(appState, Int, 20);
    int i;
    srandom(time(NULL));
    for (i=0; i < 20; ++i) {
        Int* x = Int__new(i);
        Array_push(appState, Int, intArray, x);
    }
    Array(Int)* clonedArray = Array_clone(appState, Int, intArray);
    assert(clonedArray != NULL);
    assert(AppState_isExceptionRaised(appState) == false);
    assert(Array_getSize(appState, Int, clonedArray) == Array_getSize(appState, Int, intArray));
    assert(Array_getCapacity(appState, Int, clonedArray) == Array_getCapacity(appState, Int, intArray));
    for (i=0; i < 20; ++i) {
        assert(*(Array_getValueAt(appState, Int, clonedArray, i)) == *(Array_getValueAt(appState, Int, intArray, i)));
    }

    Array_deleteValues(appState, Int, clonedArray);
    Array_delete(appState, Int, clonedArray);
    Array_deleteValues(appState, Int, intArray);
    Array_delete(appState, Int, intArray);

    printf("ok\n");
}
void testIntArray() {
    printf("%s...\n", __func__);
    Int *x;
    Array(Int)* array = Array__new(appState, Int, 20);

    assert(Array_getCapacity(appState, Int, array) == 32);
    assert(Array_getSize(appState, Int, array) == 0);

    x = Int__new(2);
    Array_add(appState, Int, array, x);
    x = Int__new(3);
    Array_add(appState, Int, array, x);
    x = Int__new(4);
    Array_push(appState, Int, array, x);

    assert(Array_getSize(appState, Int, array) == 3);

    x = Array_shift(appState, Int, array);
    assert(*x == 2);
    assert(*(Array_getValueAt(appState, Int, array, 0)) == 3);
    assert(*(Array_getValueAt(appState, Int, array, 1)) == 4);

    assert(Array_getSize(appState, Int, array) == 2);

    x = Int__new(2);
    Array_unshift(appState, Int, array, x);

    x = Array_getValueAt(appState, Int, array, 0);
    assert(*x == 2);
    x = Array_getValueAt(appState, Int, array, 1);
    assert(*x == 3);
    x = Array_getValueAt(appState, Int, array, 2);
    assert(*x == 4);

    x = Int__new(2);
    Array_insertValueAt(appState, Int, array, x, 0);
    assert(Array_getSize(appState, Int, array) == 4);
    assert(*(Array_getValueAt(appState, Int, array, 0)) == 2);
    assert(*(Array_getValueAt(appState, Int, array, 1)) == 2);
    assert(*(Array_getValueAt(appState, Int, array, 2)) == 3);
    assert(*(Array_getValueAt(appState, Int, array, 3)) == 4);
    Array_removeValueAt(appState, Int, array, 0);
    assert(Array_getSize(appState, Int, array) == 3);
    x = Int__new(3);
    Array_insertValueAt(appState, Int, array, x, 1);
    assert(Array_getSize(appState, Int, array) == 4);
    assert(*Array_getValueAt(appState, Int, array, 0) == 2);
    assert(*Array_getValueAt(appState, Int, array, 1) == 3);
    assert(*Array_getValueAt(appState, Int, array, 2) == 3);
    assert(*Array_getValueAt(appState, Int, array, 3) == 4);
    Array_removeValueAt(appState, Int, array, 1);
    assert(Array_getSize(appState, Int, array) == 3);
    x = Int__new(4);
    Array_insertValueAt(appState, Int, array, x, 2);
    assert(Array_getSize(appState, Int, array) == 4);
    assert(*Array_getValueAt(appState, Int, array, 0) == 2);
    assert(*Array_getValueAt(appState, Int, array, 1) == 3);
    assert(*Array_getValueAt(appState, Int, array, 2) == 4);
    assert(*Array_getValueAt(appState, Int, array, 3) == 4);
    Array_removeValueAt(appState, Int, array, 2);
    assert(Array_getSize(appState, Int, array) == 3);
    x = Int__new(5);
    Array_insertValueAt(appState, Int, array, x, 3);
    assert(Array_getSize(appState, Int, array) == 4);
    assert(*Array_getValueAt(appState, Int, array, 0) == 2);
    assert(*Array_getValueAt(appState, Int, array, 1) == 3);
    assert(*Array_getValueAt(appState, Int, array, 2) == 4);
    assert(*Array_getValueAt(appState, Int, array, 3) == 5);
    Array_removeValueAt(appState, Int, array, 3);
    assert(Array_getSize(appState, Int, array) == 3);
    assert(*Array_getValueAt(appState, Int, array, 0) == 2);
    assert(*Array_getValueAt(appState, Int, array, 1) == 3);
    assert(*Array_getValueAt(appState, Int, array, 2) == 4);

    x = Array_pop(appState, Int, array);
    assert(*x == 4);
    x = Array_pop(appState, Int, array);
    assert(*x == 3);
    x = Array_pop(appState, Int, array);
    assert(*x == 2);

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
    assert(!strcmp(y->first_name, x->first_name));
    assert(!strcmp(y->last_name, x->last_name));
    x = malloc(sizeof(*x));
    strcpy(x->first_name, "Cornelia");
    strcpy(x->last_name, "Nalepka");
    Array_push(appState, Person, array, x);
    y = Array_getValueAt(appState, Person, array, 1);
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
    assert(AppState_isExceptionRaisedWithID(appState, ExceptionID_ArrayIndexOutOfBounds));
    AppState_catchException(appState);
    Array_pop(appState, Int, intArray);
    assert(AppState_isExceptionRaised(appState));
    AppState_catchException(appState);
    Array_shift(appState, Int, intArray);
    assert(AppState_isExceptionRaised(appState));
    AppState_catchException(appState);
    Array_getValueAt(appState, Int, intArray, 20);
    assert(AppState_isExceptionRaised(appState));
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
    Array_qsort(appState, Int, intArray, intComparison);
    for (i=0; i < 19; ++i)
        assert(*Array_getValueAt(appState, Int, intArray, i) <= *Array_getValueAt(appState, Int, intArray, i+1));
    Array_qsort(appState, Int, intArray, intComparisonReversed);
    for (i=0; i < 19; ++i)
        assert(*Array_getValueAt(appState, Int, intArray, i) >= *Array_getValueAt(appState, Int, intArray, i+1));

    Array_deleteValues(appState, Int, intArray);
    Array_delete(appState, Int, intArray);

    printf("ok\n");
}

void testFindIndex() {
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
    assert(i == 2);
    x = Int__new(20);
    i = Array_findIndex(appState, Int, intArray, (const Int*)x, intComparison);
    assert(i == 0);
    assert(AppState_catchExceptionWithID(appState, ExceptionID_ElementNotFound) == true);

    Array_deleteValues(appState, Int, intArray);
    Array_delete(appState, Int, intArray);

    printf("ok\n");
}

void testFind() {
    printf("%s...\n", __func__);

    Array(Int)* intArray = Array__new(appState, Int, 20);
    int i;
    srandom(time(NULL));
    for (i=0; i < 20; ++i) {
        Int* x = Int__new(i);
        Array_push(appState, Int, intArray, x);
    }

    Int *x = Int__new(2);
    Int *y = Array_find(appState, Int, intArray, (const Int*)x, intComparison);
    assert(*y == *x);
    x = Int__new(20);
    y = Array_find(appState, Int, intArray, (const Int*)x, intComparison);
    assert(y == NULL);
    assert(AppState_catchExceptionWithID(appState, ExceptionID_ElementNotFound) == true);

    Array_deleteValues(appState, Int, intArray);
    Array_delete(appState, Int, intArray);

    printf("ok\n");
}

void addOne(AppState* appState, Int* x) {
    *x += 1;
}
void printInt(AppState* appState, const Int* x) {
    printf("%i ", *x);
}
void testMap() {
    printf("%s...\n", __func__);

    Array(Int)* intArray = Array__new(appState, Int, 20);
    int i;
    srandom(time(NULL));
    for (i=0; i < 20; ++i) {
        Int* x = Int__new(i);
        Array_push(appState, Int, intArray, x);
    }
    Array(Int)* mappedArray = Array_map(appState, Int, intArray, addOne);
    Array_mapConstant(appState, Int, intArray, printInt);
    printf("\n new: ");
    Array_mapConstant(appState, Int, mappedArray, printInt);

    Array_deleteValues(appState, Int, intArray);
    Array_delete(appState, Int, intArray);

    printf("ok\n");
}

int main() {
    printf("=== %s ===\n", __FILE__);
    appState = AppState__new();
    testNewDelete();
    testClone();
    testIntArray();
    testPersonArray();
    testExceptions();
    testArrayGrow();
    testSorting();
    testFindIndex();
    testFind();
    testMap();
    AppState_delete(appState);
    printf("=== %s ok ===\n", __FILE__);
    return 0;
}
