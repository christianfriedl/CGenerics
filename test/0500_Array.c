#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include"CGAppState.h"
#include"CGArray.h"

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
Int* Int_clone(CGAppState* appState, Int* this) {
    return Int__new(*this);
}
void Int_delete(int* this) {
    free(this);
}
Person* Person_clone(CGAppState* appState, Person* this) {
    return NULL; /* stub, unneeded */
}
void Person_delete(Person* this) {
    free(this);
}

INIT_ARRAY(Int)
INIT_ARRAY(Person)

CGAppState *appState;

void printCGArray(CGArray(Int)* array) {
    unsigned i;
    for (i = 0; i < CGArray_getSize(appState, Int, array); ++i)
        printf("%i ", *(CGArray_getValueAt(appState, Int, array, i)));
    printf("\n");
}
void testNewDelete() {
    printf("%s...\n", __func__);

    CGArray(Int)* intCGArray = CGArray__new(appState, Int, 20);
    CGArray(Person)* personCGArray = CGArray__new(appState, Person, 20);

    CGArray_deleteValues(appState, Int, intCGArray);
    CGArray_delete(appState, Int, intCGArray);
    CGArray_deleteValues(appState, Person, personCGArray);
    CGArray_delete(appState, Person, personCGArray);
    
    printf("ok\n");
}

void testClone() {
    printf("%s...\n", __func__);

    CGArray(Int)* intCGArray = CGArray__new(appState, Int, 20);
    int i;
    srandom(time(NULL));
    for (i=0; i < 20; ++i) {
        Int* x = Int__new(i);
        CGArray_push(appState, Int, intCGArray, x);
    }
    CGArray(Int)* clonedCGArray = CGArray_clone(appState, Int, intCGArray);
    assert(clonedCGArray != NULL);
    assert(CGAppState_isExceptionRaised(appState) == false);
    assert(CGArray_getSize(appState, Int, clonedCGArray) == CGArray_getSize(appState, Int, intCGArray));
    assert(CGArray_getCapacity(appState, Int, clonedCGArray) == CGArray_getCapacity(appState, Int, intCGArray));
    for (i=0; i < 20; ++i) {
        assert(*(CGArray_getValueAt(appState, Int, clonedCGArray, i)) == *(CGArray_getValueAt(appState, Int, intCGArray, i)));
    }

    CGArray_deleteValues(appState, Int, clonedCGArray);
    CGArray_delete(appState, Int, clonedCGArray);
    CGArray_deleteValues(appState, Int, intCGArray);
    CGArray_delete(appState, Int, intCGArray);

    printf("ok\n");
}
void testIntCGArray() {
    printf("%s...\n", __func__);
    Int *x;
    CGArray(Int)* array = CGArray__new(appState, Int, 20);

    assert(CGArray_getCapacity(appState, Int, array) == 32);
    assert(CGArray_getSize(appState, Int, array) == 0);

    x = Int__new(2);
    CGArray_add(appState, Int, array, x);
    x = Int__new(3);
    CGArray_add(appState, Int, array, x);
    x = Int__new(4);
    CGArray_push(appState, Int, array, x);

    assert(CGArray_getSize(appState, Int, array) == 3);

    x = CGArray_shift(appState, Int, array);
    assert(*x == 2);
    assert(*(CGArray_getValueAt(appState, Int, array, 0)) == 3);
    assert(*(CGArray_getValueAt(appState, Int, array, 1)) == 4);

    assert(CGArray_getSize(appState, Int, array) == 2);

    x = Int__new(2);
    CGArray_unshift(appState, Int, array, x);

    x = CGArray_getValueAt(appState, Int, array, 0);
    assert(*x == 2);
    x = CGArray_getValueAt(appState, Int, array, 1);
    assert(*x == 3);
    x = CGArray_getValueAt(appState, Int, array, 2);
    assert(*x == 4);

    x = Int__new(2);
    CGArray_insertValueAt(appState, Int, array, x, 0);
    assert(CGArray_getSize(appState, Int, array) == 4);
    assert(*(CGArray_getValueAt(appState, Int, array, 0)) == 2);
    assert(*(CGArray_getValueAt(appState, Int, array, 1)) == 2);
    assert(*(CGArray_getValueAt(appState, Int, array, 2)) == 3);
    assert(*(CGArray_getValueAt(appState, Int, array, 3)) == 4);
    CGArray_removeValueAt(appState, Int, array, 0);
    assert(CGArray_getSize(appState, Int, array) == 3);
    x = Int__new(3);
    CGArray_insertValueAt(appState, Int, array, x, 1);
    assert(CGArray_getSize(appState, Int, array) == 4);
    assert(*CGArray_getValueAt(appState, Int, array, 0) == 2);
    assert(*CGArray_getValueAt(appState, Int, array, 1) == 3);
    assert(*CGArray_getValueAt(appState, Int, array, 2) == 3);
    assert(*CGArray_getValueAt(appState, Int, array, 3) == 4);
    CGArray_removeValueAt(appState, Int, array, 1);
    assert(CGArray_getSize(appState, Int, array) == 3);
    x = Int__new(4);
    CGArray_insertValueAt(appState, Int, array, x, 2);
    assert(CGArray_getSize(appState, Int, array) == 4);
    assert(*CGArray_getValueAt(appState, Int, array, 0) == 2);
    assert(*CGArray_getValueAt(appState, Int, array, 1) == 3);
    assert(*CGArray_getValueAt(appState, Int, array, 2) == 4);
    assert(*CGArray_getValueAt(appState, Int, array, 3) == 4);
    CGArray_removeValueAt(appState, Int, array, 2);
    assert(CGArray_getSize(appState, Int, array) == 3);
    x = Int__new(5);
    CGArray_insertValueAt(appState, Int, array, x, 3);
    assert(CGArray_getSize(appState, Int, array) == 4);
    assert(*CGArray_getValueAt(appState, Int, array, 0) == 2);
    assert(*CGArray_getValueAt(appState, Int, array, 1) == 3);
    assert(*CGArray_getValueAt(appState, Int, array, 2) == 4);
    assert(*CGArray_getValueAt(appState, Int, array, 3) == 5);
    CGArray_removeValueAt(appState, Int, array, 3);
    assert(CGArray_getSize(appState, Int, array) == 3);
    assert(*CGArray_getValueAt(appState, Int, array, 0) == 2);
    assert(*CGArray_getValueAt(appState, Int, array, 1) == 3);
    assert(*CGArray_getValueAt(appState, Int, array, 2) == 4);

    x = CGArray_pop(appState, Int, array);
    assert(*x == 4);
    x = CGArray_pop(appState, Int, array);
    assert(*x == 3);
    x = CGArray_pop(appState, Int, array);
    assert(*x == 2);

    assert(CGArray_getSize(appState, Int, array) == 0);

    CGArray_delete(appState, Int, array);

    printf("ok\n");
}
void testPersonCGArray() {
    printf("%s...\n", __func__);
    Person* x = malloc(sizeof(*x));
    Person* y = malloc(sizeof(*y));
    CGArray(Person)* array = CGArray__new(appState, Person, 20);
    strcpy(x->first_name, "Christian");
    strcpy(x->last_name, "Friedl");
    CGArray_push(appState, Person, array, x);
    y = CGArray_getValueAt(appState, Person, array, 0);
    assert(!strcmp(y->first_name, x->first_name));
    assert(!strcmp(y->last_name, x->last_name));
    x = malloc(sizeof(*x));
    strcpy(x->first_name, "Cornelia");
    strcpy(x->last_name, "Nalepka");
    CGArray_push(appState, Person, array, x);
    y = CGArray_getValueAt(appState, Person, array, 1);
    assert(!strcmp(y->first_name, x->first_name));
    assert(!strcmp(y->last_name, x->last_name));

    CGArray_deleteValues(appState, Person, array);
    CGArray_delete(appState, Person, array);

    printf("ok\n");
}

void testCGArrayGrow() {
    printf("%s...\n", __func__);

    CGArray(Int)* intCGArray = CGArray__new(appState, Int, 1);

    Int *x = Int__new(20);
    CGArray_insertValueAt(appState, Int, intCGArray, x, 20);
    assert(*CGArray_getValueAt(appState, Int, intCGArray, 20) == 20);
    assert(CGArray_getCapacity(appState, Int, intCGArray) >= 21);
    assert(CGArray_getSize(appState, Int, intCGArray) == 21);

    CGArray_delete(appState, Int, intCGArray);

    free(x);
    printf("ok\n");
}

void testCGExceptions() {
    printf("%s...\n", __func__);

    CGArray(Int)* intCGArray = CGArray__new(appState, Int, 1);
    CGArray_removeValueAt(appState, Int, intCGArray, 1);
    assert(CGAppState_isExceptionRaisedWithID(appState, CGExceptionID_ArrayIndexOutOfBounds));
    CGAppState_catchException(appState);
    CGArray_pop(appState, Int, intCGArray);
    assert(CGAppState_isExceptionRaised(appState));
    CGAppState_catchException(appState);
    CGArray_shift(appState, Int, intCGArray);
    assert(CGAppState_isExceptionRaised(appState));
    CGAppState_catchException(appState);
    CGArray_getValueAt(appState, Int, intCGArray, 20);
    assert(CGAppState_isExceptionRaised(appState));
    CGAppState_catchException(appState);

    CGArray_delete(appState, Int, intCGArray);

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

    CGArray(Int)* intCGArray = CGArray__new(appState, Int, 20);
    int i;
    srandom(time(NULL));
    for (i=0; i < 20; ++i) {
        Int *x = Int__new(random() % 65536);
        CGArray_push(appState, Int, intCGArray, x);
    }
    CGArray_qsort(appState, Int, intCGArray, intComparison);
    for (i=0; i < 19; ++i)
        assert(*CGArray_getValueAt(appState, Int, intCGArray, i) <= *CGArray_getValueAt(appState, Int, intCGArray, i+1));
    CGArray_qsort(appState, Int, intCGArray, intComparisonReversed);
    for (i=0; i < 19; ++i)
        assert(*CGArray_getValueAt(appState, Int, intCGArray, i) >= *CGArray_getValueAt(appState, Int, intCGArray, i+1));

    CGArray_deleteValues(appState, Int, intCGArray);
    CGArray_delete(appState, Int, intCGArray);

    printf("ok\n");
}

void testFindIndex() {
    printf("%s...\n", __func__);

    CGArray(Int)* intCGArray = CGArray__new(appState, Int, 20);
    int i;
    srandom(time(NULL));
    for (i=0; i < 20; ++i) {
        Int* x = Int__new(i);
        CGArray_push(appState, Int, intCGArray, x);
    }

    Int *x = Int__new(2);
    i = CGArray_findIndex(appState, Int, intCGArray, (const Int*)x, intComparison);
    assert(i == 2);
    x = Int__new(20);
    i = CGArray_findIndex(appState, Int, intCGArray, (const Int*)x, intComparison);
    assert(i == 0);
    assert(CGAppState_catchExceptionWithID(appState, CGExceptionID_ElementNotFound) == true);

    CGArray_deleteValues(appState, Int, intCGArray);
    CGArray_delete(appState, Int, intCGArray);

    printf("ok\n");
}

void testFind() {
    printf("%s...\n", __func__);

    CGArray(Int)* intCGArray = CGArray__new(appState, Int, 20);
    int i;
    srandom(time(NULL));
    for (i=0; i < 20; ++i) {
        Int* x = Int__new(i);
        CGArray_push(appState, Int, intCGArray, x);
    }

    Int *x = Int__new(2);
    Int *y = CGArray_find(appState, Int, intCGArray, (const Int*)x, intComparison);
    assert(*y == *x);
    x = Int__new(20);
    y = CGArray_find(appState, Int, intCGArray, (const Int*)x, intComparison);
    assert(y == NULL);
    assert(CGAppState_catchExceptionWithID(appState, CGExceptionID_ElementNotFound) == true);

    CGArray_deleteValues(appState, Int, intCGArray);
    CGArray_delete(appState, Int, intCGArray);

    printf("ok\n");
}

void addOne(CGAppState* appState, Int* x) {
    *x += 1;
}
void printInt(CGAppState* appState, const Int* x) {
    printf("%i ", *x);
}
void testMap() {
    printf("%s...\n", __func__);

    CGArray(Int)* intCGArray = CGArray__new(appState, Int, 20);
    int i;
    srandom(time(NULL));
    for (i=0; i < 20; ++i) {
        Int* x = Int__new(i);
        CGArray_push(appState, Int, intCGArray, x);
    }
    CGArray(Int)* mappedCGArray = CGArray_map(appState, Int, intCGArray, addOne);
    CGArray_mapConstant(appState, Int, intCGArray, printInt);
    printf("\n new: ");
    CGArray_mapConstant(appState, Int, mappedCGArray, printInt);

    CGArray_deleteValues(appState, Int, intCGArray);
    CGArray_delete(appState, Int, intCGArray);

    printf("ok\n");
}

int main() {
    printf("=== %s ===\n", __FILE__);
    appState = CGAppState__new();
    testNewDelete();
    testClone();
    testIntCGArray();
    testPersonCGArray();
    testCGExceptions();
    testCGArrayGrow();
    testSorting();
    testFindIndex();
    testFind();
    testMap();
    CGAppState_delete(appState);
    printf("=== %s ok ===\n", __FILE__);
    return 0;
}
