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
Int* Int_clone(Int* this) {
    return Int__new(*this);
}
void Int_delete(int* this) {
    free(this);
}
Person* Person_clone(Person* this) {
    return NULL; /* stub, unneeded */
}
void Person_delete(Person* this) {
    free(this);
}

DECLARE_ARRAY_TYPE(Int)
DECLARE_ARRAY_FUNCS(Int)
DEFINE_ARRAY_FUNCS(Int)
INIT_ARRAY(Person)

CGAppState *appState;

void printCGArray(CGArray(Int)* array) {
    unsigned i;
    for (i = 0; i < CGArray_getSize(Int, array); ++i)
        printf("%i ", *(CGArray_getValueAt(Int, array, i)));
    printf("\n");
}
void testNewDelete() {
    printf("%s... ", __func__);

    CGArray(Int)* intCGArray = CGArray__new(Int, 20);
    CGArray(Person)* personCGArray = CGArray__new(Person, 20);

    CGArray_deleteValues(Int, intCGArray);
    CGArray_delete(Int, intCGArray);
    CGArray_deleteValues(Person, personCGArray);
    CGArray_delete(Person, personCGArray);
    
    printf("ok -- ");
}

void testNewFromInitializerList() {
    printf("%s... ", __func__);

    Int* i1 = Int__new(1);
    Int* i2 = Int__new(2);
    CGArray(Int)* intCGArray = CGArray__newFromInitializerList(Int, i1, NULL);
    assert(intCGArray != NULL);
    assert(CGArray_getValueAt(Int, intCGArray, 0) == i1);
    assert(CGArray_getSize(Int, intCGArray) == 1);
    assert(CGArray_getCapacity(Int, intCGArray) >= 1);
    CGArray_delete(Int, intCGArray);
    assert(!CGAppState_isExceptionRaised(appState));

    CGArray(Int)* intCGArray2 = CGArray__newFromInitializerList(Int, i1, i2, NULL);
    assert(intCGArray2 != NULL);
    assert(CGArray_getValueAt(Int, intCGArray2, 0) == i1);
    assert(CGArray_getValueAt(Int, intCGArray2, 1) == i2);
    assert(CGArray_getSize(Int, intCGArray2) == 2);
    assert(CGArray_getCapacity(Int, intCGArray2) >= 2);
    CGArray_delete(Int, intCGArray2);
    Int_delete(i1);
    Int_delete(i2);
    assert(!CGAppState_isExceptionRaised(appState));
    
    printf("ok -- ");
}

void testClone() {
    printf("%s... ", __func__);

    CGArray(Int)* intCGArray = CGArray__new(Int, 20);
    int i;
    srandom(time(NULL));
    for (i=0; i < 20; ++i) {
        Int* x = Int__new(i);
        CGArray_push(Int, intCGArray, x);
    }
    CGArray(Int)* clonedCGArray = CGArray_clone(Int, intCGArray);
    assert(clonedCGArray != NULL);
    assert(CGAppState_isExceptionRaised(appState) == false);
    assert(CGArray_getSize(Int, clonedCGArray) == CGArray_getSize(Int, intCGArray));
    assert(CGArray_getCapacity(Int, clonedCGArray) == CGArray_getCapacity(Int, intCGArray));
    for (i=0; i < 20; ++i) {
        assert(*(CGArray_getValueAt(Int, clonedCGArray, i)) == *(CGArray_getValueAt(Int, intCGArray, i)));
        /* assert deep copy */
        assert(CGArray_getValueAt(Int, clonedCGArray, i) != CGArray_getValueAt(Int, intCGArray, i));
    }

    CGArray_deleteValues(Int, clonedCGArray);
    CGArray_delete(Int, clonedCGArray);
    CGArray_deleteValues(Int, intCGArray);
    CGArray_delete(Int, intCGArray);

    printf("ok -- ");
}
void testIntCGArray() {
    printf("%s... ", __func__);
    Int *x;
    CGArray(Int)* array = CGArray__new(Int, 20);

    assert(CGArray_getCapacity(Int, array) == 32);
    assert(CGArray_getSize(Int, array) == 0);

    x = Int__new(2);
    CGArray_add(Int, array, x);
    x = Int__new(3);
    CGArray_add(Int, array, x);
    x = Int__new(4);
    CGArray_push(Int, array, x);

    assert(CGArray_getSize(Int, array) == 3);

    x = CGArray_shift(Int, array);
    assert(*x == 2);
    assert(*(CGArray_getValueAt(Int, array, 0)) == 3);
    assert(*(CGArray_getValueAt(Int, array, 1)) == 4);

    assert(CGArray_getSize(Int, array) == 2);

    x = Int__new(2);
    CGArray_unshift(Int, array, x);

    x = CGArray_getValueAt(Int, array, 0);
    assert(*x == 2);
    x = CGArray_getValueAt(Int, array, 1);
    assert(*x == 3);
    x = CGArray_getValueAt(Int, array, 2);
    assert(*x == 4);

    x = Int__new(2);
    CGArray_insertValueAt(Int, array, x, 0);
    assert(CGArray_getSize(Int, array) == 4);
    assert(*(CGArray_getValueAt(Int, array, 0)) == 2);
    assert(*(CGArray_getValueAt(Int, array, 1)) == 2);
    assert(*(CGArray_getValueAt(Int, array, 2)) == 3);
    assert(*(CGArray_getValueAt(Int, array, 3)) == 4);
    CGArray_removeValueAt(Int, array, 0);
    assert(CGArray_getSize(Int, array) == 3);
    x = Int__new(3);
    CGArray_insertValueAt(Int, array, x, 1);
    assert(CGArray_getSize(Int, array) == 4);
    assert(*CGArray_getValueAt(Int, array, 0) == 2);
    assert(*CGArray_getValueAt(Int, array, 1) == 3);
    assert(*CGArray_getValueAt(Int, array, 2) == 3);
    assert(*CGArray_getValueAt(Int, array, 3) == 4);
    CGArray_removeValueAt(Int, array, 1);
    assert(CGArray_getSize(Int, array) == 3);
    x = Int__new(4);
    CGArray_insertValueAt(Int, array, x, 2);
    assert(CGArray_getSize(Int, array) == 4);
    assert(*CGArray_getValueAt(Int, array, 0) == 2);
    assert(*CGArray_getValueAt(Int, array, 1) == 3);
    assert(*CGArray_getValueAt(Int, array, 2) == 4);
    assert(*CGArray_getValueAt(Int, array, 3) == 4);
    CGArray_removeValueAt(Int, array, 2);
    assert(CGArray_getSize(Int, array) == 3);
    x = Int__new(5);
    CGArray_insertValueAt(Int, array, x, 3);
    assert(CGArray_getSize(Int, array) == 4);
    assert(*CGArray_getValueAt(Int, array, 0) == 2);
    assert(*CGArray_getValueAt(Int, array, 1) == 3);
    assert(*CGArray_getValueAt(Int, array, 2) == 4);
    assert(*CGArray_getValueAt(Int, array, 3) == 5);
    CGArray_removeValueAt(Int, array, 3);
    assert(CGArray_getSize(Int, array) == 3);
    assert(*CGArray_getValueAt(Int, array, 0) == 2);
    assert(*CGArray_getValueAt(Int, array, 1) == 3);
    assert(*CGArray_getValueAt(Int, array, 2) == 4);

    x = CGArray_pop(Int, array);
    assert(*x == 4);
    x = CGArray_pop(Int, array);
    assert(*x == 3);
    x = CGArray_pop(Int, array);
    assert(*x == 2);

    assert(CGArray_getSize(Int, array) == 0);

    CGArray_delete(Int, array);

    printf("ok -- ");
}
void testPersonCGArray() {
    printf("%s... ", __func__);
    Person* x = malloc(sizeof(*x));
    Person* y = malloc(sizeof(*y));
    CGArray(Person)* array = CGArray__new(Person, 20);
    strcpy(x->first_name, "Christian");
    strcpy(x->last_name, "Friedl");
    CGArray_push(Person, array, x);
    y = CGArray_getValueAt(Person, array, 0);
    assert(!strcmp(y->first_name, x->first_name));
    assert(!strcmp(y->last_name, x->last_name));
    x = malloc(sizeof(*x));
    strcpy(x->first_name, "Cornelia");
    strcpy(x->last_name, "Nalepka");
    CGArray_push(Person, array, x);
    y = CGArray_getValueAt(Person, array, 1);
    assert(!strcmp(y->first_name, x->first_name));
    assert(!strcmp(y->last_name, x->last_name));

    CGArray_deleteValues(Person, array);
    CGArray_delete(Person, array);

    printf("ok -- ");
}

void testCGArrayGrow() {
    printf("%s... ", __func__);

    CGArray(Int)* intCGArray = CGArray__new(Int, 1);

    Int *x = Int__new(20);
    CGArray_insertValueAt(Int, intCGArray, x, 20);
    assert(*CGArray_getValueAt(Int, intCGArray, 20) == 20);
    assert(CGArray_getCapacity(Int, intCGArray) >= 21);
    assert(CGArray_getSize(Int, intCGArray) == 21);

    CGArray_delete(Int, intCGArray);

    free(x);
    printf("ok -- ");
}

void testCGExceptions() {
    printf("%s... ", __func__);
    
    CGArray(Int)* intCGArray = CGArray__new(Int, 1);
    CGArray_removeValueAt(Int, intCGArray, 1);
    assert(CGAppState_isExceptionRaisedWithID(appState, CGExceptionID_ArrayIndexOutOfBounds));
    CGAppState_catchAndDeleteException(appState);
    CGArray_pop(Int, intCGArray);
    assert(CGAppState_isExceptionRaised(appState));
    CGAppState_catchAndDeleteException(appState);
    CGArray_shift(Int, intCGArray);
    assert(CGAppState_isExceptionRaised(appState));
    CGAppState_catchAndDeleteException(appState);
    CGArray_getValueAt(Int, intCGArray, 20);
    assert(CGAppState_isExceptionRaised(appState));
    CGAppState_catchAndDeleteException(appState);

    CGArray_delete(Int, intCGArray);

    printf("ok -- ");
}

int intComparison(const Int **i1, const Int **i2) {
    return ((**i1 < **i2) ? -1 : (**i1 == **i2) ? 0 : 1);
}
int intComparisonReversed(const Int **i1, const Int **i2) {
    return ((**i1 < **i2) ? 1 : (**i1 == **i2) ? 0 : -1);
}

void testSorting() {
    printf("%s... ", __func__);

    CGArray(Int)* intCGArray = CGArray__new(Int, 20);
    int i;
    srandom(time(NULL));
    for (i=0; i < 20; ++i) {
        Int *x = Int__new(random() % 65536);
        CGArray_push(Int, intCGArray, x);
    }
    CGArray_qsort(Int, intCGArray, intComparison);
    for (i=0; i < 19; ++i)
        assert(*CGArray_getValueAt(Int, intCGArray, i) <= *CGArray_getValueAt(Int, intCGArray, i+1));
    CGArray_qsort(Int, intCGArray, intComparisonReversed);
    for (i=0; i < 19; ++i)
        assert(*CGArray_getValueAt(Int, intCGArray, i) >= *CGArray_getValueAt(Int, intCGArray, i+1));

    CGArray_deleteValues(Int, intCGArray);
    CGArray_delete(Int, intCGArray);

    printf("ok -- ");
}

void testFindIndex() {
    printf("%s... ", __func__);

    CGArray(Int)* intCGArray = CGArray__new(Int, 20);
    int i;
    srandom(time(NULL));
    for (i=0; i < 20; ++i) {
        Int* x = Int__new(i);
        CGArray_push(Int, intCGArray, x);
    }

    Int *x = Int__new(2);
    i = CGArray_findIndex(Int, intCGArray, (const Int*)x, intComparison);
    assert(i == 2);
    x = Int__new(20);
    i = CGArray_findIndex(Int, intCGArray, (const Int*)x, intComparison);
    assert(i == 0);
    CGException* e = CGAppState_catchExceptionWithID(appState, CGExceptionID_ElementNotFound);
    assert(e != NULL);
    CGException_delete(e);

    CGArray_deleteValues(Int, intCGArray);
    CGArray_delete(Int, intCGArray);

    printf("ok -- ");
}

void testFind() {
    printf("%s... ", __func__);

    CGArray(Int)* intCGArray = CGArray__new(Int, 20);
    int i;
    srandom(time(NULL));
    for (i=0; i < 20; ++i) {
        Int* x = Int__new(i);
        CGArray_push(Int, intCGArray, x);
    }

    Int *x = Int__new(2);
    Int *y = CGArray_find(Int, intCGArray, (const Int*)x, intComparison);
    assert(*y == *x);
    x = Int__new(20);
    y = CGArray_find(Int, intCGArray, (const Int*)x, intComparison);
    assert(y == NULL);
    CGException* e = CGAppState_catchExceptionWithID(appState, CGExceptionID_ElementNotFound);
    assert(e != NULL);
    CGException_delete(e);

    CGArray_deleteValues(Int, intCGArray);
    CGArray_delete(Int, intCGArray);

    printf("ok -- ");
}

void addOne(Int* x, void *dummy) {
    *x += 1;
}
void printInt(const Int* x) {
    printf("%i ", *x);
}
static int globalIndex;
static bool globalOk;
static bool intIsEqualToIndex(const Int* x, void *dummy) {
    globalOk &= (*x == globalIndex);
    globalIndex++;
    return true;
}
void testMap() {
    printf("%s... ", __func__);

    CGArray(Int)* intCGArray = CGArray__new(Int, 20);
    int i;
    srandom(time(NULL));
    for (i=0; i < 20; ++i) {
        Int* x = Int__new(i);
        CGArray_push(Int, intCGArray, x);
    }
    CGArray(Int)* mappedCGArray = CGArray_map(Int, intCGArray, addOne, NULL);

    globalOk = true;
    globalIndex = 0;
    CGArray_mapConstant(Int, intCGArray, intIsEqualToIndex, NULL);
    assert(globalOk);

    globalOk = true;
    globalIndex = 1;
    CGArray_mapConstant(Int, mappedCGArray, intIsEqualToIndex, NULL);
    assert(globalOk);

    CGArray_deleteValues(Int, intCGArray);
    CGArray_delete(Int, intCGArray);

    printf("ok -- ");
}
void testEdge_initialCapacity0() {
    printf("%s... ", __func__);

    CGArray(Int)* intCGArray = CGArray__new(Int, 0);
    assert(intCGArray != NULL);
    assert(CGArray_getSize(Int, intCGArray) == 0);
    assert(CGArray_getCapacity(Int, intCGArray) == 1);

    CGArray_deleteValues(Int, intCGArray);
    CGArray_delete(Int, intCGArray);
    
    intCGArray = CGArray__new(Int, 0);
    CGArray_add(Int, intCGArray, Int__new(1));
    
    assert(CGArray_getSize(Int, intCGArray) == 1);
    assert(CGArray_getCapacity(Int, intCGArray) >= 1);

    CGArray_deleteValues(Int, intCGArray);
    CGArray_delete(Int, intCGArray);
    
    printf("ok -- ");
}
void testAppend() {
    printf("%s... ", __func__);


    Int* i1 = Int__new(0);
    Int* i2 = Int__new(1);
    CGArray(Int)* array1 = CGArray__newFromInitializerList(Int, i1, i2, NULL);
    Int* i3 = Int__new(2);
    Int* i4 = Int__new(3);
    CGArray(Int)* array2 = CGArray__newFromInitializerList(Int, i3, i4, NULL);

    CGArray_append(Int, array1, array2);

    assert(CGArray_getCapacity(Int, array1) >= 4);
    assert(CGArray_getSize(Int, array1) == 4);

    int i;
    for (i=0; i<4; ++i) // printf("-> %i <- ", *(CGArray_getValueAt(Int, array1, i))); 
        assert(*(CGArray_getValueAt(Int, array1, i)) == i);

    CGArray_deleteValues(Int, array1);
    CGArray_delete(Int, array2);
    
    printf("ok -- ");
}
int main() {
    printf("=== %s ===\n", __FILE__);
    CGAppState__init(__FILE__);
    appState = CGAppState__getInstance();
    testNewDelete();
    testNewFromInitializerList();
    testClone();
    testIntCGArray();
    testPersonCGArray();
    testCGExceptions();
    testCGArrayGrow();
    testSorting();
    testFindIndex();
    testFind();
    testMap();
    testAppend();
    testEdge_initialCapacity0();
    CGAppState__deInit();
    printf("=== %s ok ===\n", __FILE__);
    return 0;
}
