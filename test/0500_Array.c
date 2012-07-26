#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include"cgAppState.h"

#include"cgArray.h"

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

cgAppState *appState;

void printCGArray(cgArray(Int)* array) {
    unsigned i;
    for (i = 0; i < cgArray_getSize(Int, array); ++i)
        printf("%i ", *(cgArray_getValueAt(Int, array, i)));
    printf("\n");
}
void testNewDelete() {
    printf("%s... ", __func__);

    cgArray(Int)* intCGArray = cgArray__new(Int, 20);
    cgArray(Person)* personCGArray = cgArray__new(Person, 20);

    cgArray_deleteValues(Int, intCGArray);
    cgArray_delete(Int, intCGArray);
    cgArray_deleteValues(Person, personCGArray);
    cgArray_delete(Person, personCGArray);
    
    printf("ok -- ");
}

void testNewFromInitializerList() {
    printf("%s... ", __func__);

    Int* i1 = Int__new(1);
    Int* i2 = Int__new(2);
    cgArray(Int)* intCGArray = cgArray__newFromInitializerList(Int, i1, NULL);
    assert(intCGArray != NULL);
    assert(cgArray_getValueAt(Int, intCGArray, 0) == i1);
    assert(cgArray_getSize(Int, intCGArray) == 1);
    assert(cgArray_getCapacity(Int, intCGArray) >= 1);
    cgArray_delete(Int, intCGArray);
    assert(!cgAppState_isExceptionRaised(appState));

    cgArray(Int)* intCGArray2 = cgArray__newFromInitializerList(Int, i1, i2, NULL);
    assert(intCGArray2 != NULL);
    assert(cgArray_getValueAt(Int, intCGArray2, 0) == i1);
    assert(cgArray_getValueAt(Int, intCGArray2, 1) == i2);
    assert(cgArray_getSize(Int, intCGArray2) == 2);
    assert(cgArray_getCapacity(Int, intCGArray2) >= 2);
    cgArray_delete(Int, intCGArray2);
    Int_delete(i1);
    Int_delete(i2);
    assert(!cgAppState_isExceptionRaised(appState));
    
    printf("ok -- ");
}

void testClone() {
    printf("%s... ", __func__);

    cgArray(Int)* intCGArray = cgArray__new(Int, 20);
    int i;
    srandom(time(NULL));
    for (i=0; i < 20; ++i) {
        Int* x = Int__new(i);
        cgArray_push(Int, intCGArray, x);
    }
    cgArray(Int)* clonedCGArray = cgArray_clone(Int, intCGArray);
    assert(clonedCGArray != NULL);
    assert(cgAppState_isExceptionRaised(appState) == false);
    assert(cgArray_getSize(Int, clonedCGArray) == cgArray_getSize(Int, intCGArray));
    assert(cgArray_getCapacity(Int, clonedCGArray) == cgArray_getCapacity(Int, intCGArray));
    for (i=0; i < 20; ++i) {
        assert(*(cgArray_getValueAt(Int, clonedCGArray, i)) == *(cgArray_getValueAt(Int, intCGArray, i)));
        /* assert deep copy */
        assert(cgArray_getValueAt(Int, clonedCGArray, i) != cgArray_getValueAt(Int, intCGArray, i));
    }

    cgArray_deleteValues(Int, clonedCGArray);
    cgArray_delete(Int, clonedCGArray);
    cgArray_deleteValues(Int, intCGArray);
    cgArray_delete(Int, intCGArray);

    printf("ok -- ");
}
void testIntCGArray() {
    printf("%s... ", __func__);
    Int *x;
    cgArray(Int)* array = cgArray__new(Int, 20);

    assert(cgArray_getCapacity(Int, array) == 32);
    assert(cgArray_getSize(Int, array) == 0);

    x = Int__new(2);
    cgArray_add(Int, array, x);
    x = Int__new(3);
    cgArray_add(Int, array, x);
    x = Int__new(4);
    cgArray_push(Int, array, x);

    assert(cgArray_getSize(Int, array) == 3);

    x = cgArray_shift(Int, array);
    assert(*x == 2);
    assert(*(cgArray_getValueAt(Int, array, 0)) == 3);
    assert(*(cgArray_getValueAt(Int, array, 1)) == 4);

    assert(cgArray_getSize(Int, array) == 2);

    x = Int__new(2);
    cgArray_unshift(Int, array, x);

    x = cgArray_getValueAt(Int, array, 0);
    assert(*x == 2);
    x = cgArray_getValueAt(Int, array, 1);
    assert(*x == 3);
    x = cgArray_getValueAt(Int, array, 2);
    assert(*x == 4);

    x = Int__new(2);
    cgArray_insertValueAt(Int, array, x, 0);
    assert(cgArray_getSize(Int, array) == 4);
    assert(*(cgArray_getValueAt(Int, array, 0)) == 2);
    assert(*(cgArray_getValueAt(Int, array, 1)) == 2);
    assert(*(cgArray_getValueAt(Int, array, 2)) == 3);
    assert(*(cgArray_getValueAt(Int, array, 3)) == 4);
    cgArray_removeValueAt(Int, array, 0);
    assert(cgArray_getSize(Int, array) == 3);
    x = Int__new(3);
    cgArray_insertValueAt(Int, array, x, 1);
    assert(cgArray_getSize(Int, array) == 4);
    assert(*cgArray_getValueAt(Int, array, 0) == 2);
    assert(*cgArray_getValueAt(Int, array, 1) == 3);
    assert(*cgArray_getValueAt(Int, array, 2) == 3);
    assert(*cgArray_getValueAt(Int, array, 3) == 4);
    cgArray_removeValueAt(Int, array, 1);
    assert(cgArray_getSize(Int, array) == 3);
    x = Int__new(4);
    cgArray_insertValueAt(Int, array, x, 2);
    assert(cgArray_getSize(Int, array) == 4);
    assert(*cgArray_getValueAt(Int, array, 0) == 2);
    assert(*cgArray_getValueAt(Int, array, 1) == 3);
    assert(*cgArray_getValueAt(Int, array, 2) == 4);
    assert(*cgArray_getValueAt(Int, array, 3) == 4);
    cgArray_removeValueAt(Int, array, 2);
    assert(cgArray_getSize(Int, array) == 3);
    x = Int__new(5);
    cgArray_insertValueAt(Int, array, x, 3);
    assert(cgArray_getSize(Int, array) == 4);
    assert(*cgArray_getValueAt(Int, array, 0) == 2);
    assert(*cgArray_getValueAt(Int, array, 1) == 3);
    assert(*cgArray_getValueAt(Int, array, 2) == 4);
    assert(*cgArray_getValueAt(Int, array, 3) == 5);
    cgArray_removeValueAt(Int, array, 3);
    assert(cgArray_getSize(Int, array) == 3);
    assert(*cgArray_getValueAt(Int, array, 0) == 2);
    assert(*cgArray_getValueAt(Int, array, 1) == 3);
    assert(*cgArray_getValueAt(Int, array, 2) == 4);

    x = cgArray_pop(Int, array);
    assert(*x == 4);
    x = cgArray_pop(Int, array);
    assert(*x == 3);
    x = cgArray_pop(Int, array);
    assert(*x == 2);

    assert(cgArray_getSize(Int, array) == 0);

    cgArray_delete(Int, array);

    printf("ok -- ");
}
void testPersonCGArray() {
    printf("%s... ", __func__);
    Person* x = malloc(sizeof(*x));
    Person* y = malloc(sizeof(*y));
    cgArray(Person)* array = cgArray__new(Person, 20);
    strcpy(x->first_name, "Christian");
    strcpy(x->last_name, "Friedl");
    cgArray_push(Person, array, x);
    y = cgArray_getValueAt(Person, array, 0);
    assert(!strcmp(y->first_name, x->first_name));
    assert(!strcmp(y->last_name, x->last_name));
    x = malloc(sizeof(*x));
    strcpy(x->first_name, "Cornelia");
    strcpy(x->last_name, "Nalepka");
    cgArray_push(Person, array, x);
    y = cgArray_getValueAt(Person, array, 1);
    assert(!strcmp(y->first_name, x->first_name));
    assert(!strcmp(y->last_name, x->last_name));

    cgArray_deleteValues(Person, array);
    cgArray_delete(Person, array);

    printf("ok -- ");
}

void testCGArrayGrow() {
    printf("%s... ", __func__);

    cgArray(Int)* intCGArray = cgArray__new(Int, 1);

    Int *x = Int__new(20);
    cgArray_insertValueAt(Int, intCGArray, x, 20);
    assert(*cgArray_getValueAt(Int, intCGArray, 20) == 20);
    assert(cgArray_getCapacity(Int, intCGArray) >= 21);
    assert(cgArray_getSize(Int, intCGArray) == 21);

    cgArray_delete(Int, intCGArray);

    free(x);
    printf("ok -- ");
}

void testCGExceptions() {
    printf("%s... ", __func__);
    
    cgArray(Int)* intCGArray = cgArray__new(Int, 1);
    cgArray_removeValueAt(Int, intCGArray, 1);
    assert(cgAppState_isExceptionRaisedWithID(appState, cgExceptionID_ArrayIndexOutOfBounds));
    cgAppState_catchAndDeleteException(appState);
    cgArray_pop(Int, intCGArray);
    assert(cgAppState_isExceptionRaised(appState));
    cgAppState_catchAndDeleteException(appState);
    cgArray_shift(Int, intCGArray);
    assert(cgAppState_isExceptionRaised(appState));
    cgAppState_catchAndDeleteException(appState);
    cgArray_getValueAt(Int, intCGArray, 20);
    assert(cgAppState_isExceptionRaised(appState));
    cgAppState_catchAndDeleteException(appState);

    cgArray_delete(Int, intCGArray);

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

    cgArray(Int)* intCGArray = cgArray__new(Int, 20);
    int i;
    srandom(time(NULL));
    for (i=0; i < 20; ++i) {
        Int *x = Int__new(random() % 65536);
        cgArray_push(Int, intCGArray, x);
    }
    cgArray_qsort(Int, intCGArray, intComparison);
    for (i=0; i < 19; ++i)
        assert(*cgArray_getValueAt(Int, intCGArray, i) <= *cgArray_getValueAt(Int, intCGArray, i+1));
    cgArray_qsort(Int, intCGArray, intComparisonReversed);
    for (i=0; i < 19; ++i)
        assert(*cgArray_getValueAt(Int, intCGArray, i) >= *cgArray_getValueAt(Int, intCGArray, i+1));

    cgArray_deleteValues(Int, intCGArray);
    cgArray_delete(Int, intCGArray);

    printf("ok -- ");
}

void testFindIndex() {
    printf("%s... ", __func__);

    cgArray(Int)* intCGArray = cgArray__new(Int, 20);
    int i;
    srandom(time(NULL));
    for (i=0; i < 20; ++i) {
        Int* x = Int__new(i);
        cgArray_push(Int, intCGArray, x);
    }

    Int *x = Int__new(2);
    i = cgArray_findIndex(Int, intCGArray, (const Int*)x, intComparison);
    assert(i == 2);
    x = Int__new(20);
    i = cgArray_findIndex(Int, intCGArray, (const Int*)x, intComparison);
    assert(i == 0);
    cgException* e = cgAppState_catchExceptionWithID(appState, cgExceptionID_ElementNotFound);
    assert(e != NULL);
    cgException_delete(e);

    cgArray_deleteValues(Int, intCGArray);
    cgArray_delete(Int, intCGArray);

    printf("ok -- ");
}

void testFind() {
    printf("%s... ", __func__);

    cgArray(Int)* intCGArray = cgArray__new(Int, 20);
    int i;
    srandom(time(NULL));
    for (i=0; i < 20; ++i) {
        Int* x = Int__new(i);
        cgArray_push(Int, intCGArray, x);
    }

    Int *x = Int__new(2);
    Int *y = cgArray_find(Int, intCGArray, (const Int*)x, intComparison);
    assert(*y == *x);
    x = Int__new(20);
    y = cgArray_find(Int, intCGArray, (const Int*)x, intComparison);
    assert(y == NULL);
    cgException* e = cgAppState_catchExceptionWithID(appState, cgExceptionID_ElementNotFound);
    assert(e != NULL);
    cgException_delete(e);

    cgArray_deleteValues(Int, intCGArray);
    cgArray_delete(Int, intCGArray);

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

    cgArray(Int)* intCGArray = cgArray__new(Int, 20);
    int i;
    srandom(time(NULL));
    for (i=0; i < 20; ++i) {
        Int* x = Int__new(i);
        cgArray_push(Int, intCGArray, x);
    }
    cgArray(Int)* mappedCGArray = cgArray_map(Int, intCGArray, addOne, NULL);

    globalOk = true;
    globalIndex = 0;
    cgArray_mapConstant(Int, intCGArray, intIsEqualToIndex, NULL);
    assert(globalOk);

    globalOk = true;
    globalIndex = 1;
    cgArray_mapConstant(Int, mappedCGArray, intIsEqualToIndex, NULL);
    assert(globalOk);

    cgArray_deleteValues(Int, intCGArray);
    cgArray_delete(Int, intCGArray);

    printf("ok -- ");
}
void testEdge_initialCapacity0() {
    printf("%s... ", __func__);

    cgArray(Int)* intCGArray = cgArray__new(Int, 0);
    assert(intCGArray != NULL);
    assert(cgArray_getSize(Int, intCGArray) == 0);
    assert(cgArray_getCapacity(Int, intCGArray) == 1);

    cgArray_deleteValues(Int, intCGArray);
    cgArray_delete(Int, intCGArray);
    
    intCGArray = cgArray__new(Int, 0);
    cgArray_add(Int, intCGArray, Int__new(1));
    
    assert(cgArray_getSize(Int, intCGArray) == 1);
    assert(cgArray_getCapacity(Int, intCGArray) >= 1);

    cgArray_deleteValues(Int, intCGArray);
    cgArray_delete(Int, intCGArray);
    
    printf("ok -- ");
}
void testAppend() {
    printf("%s... ", __func__);


    Int* i1 = Int__new(0);
    Int* i2 = Int__new(1);
    cgArray(Int)* array1 = cgArray__newFromInitializerList(Int, i1, i2, NULL);
    Int* i3 = Int__new(2);
    Int* i4 = Int__new(3);
    cgArray(Int)* array2 = cgArray__newFromInitializerList(Int, i3, i4, NULL);

    cgArray_append(Int, array1, array2);

    assert(cgArray_getCapacity(Int, array1) >= 4);
    assert(cgArray_getSize(Int, array1) == 4);

    int i;
    for (i=0; i<4; ++i) // printf("-> %i <- ", *(cgArray_getValueAt(Int, array1, i))); 
        assert(*(cgArray_getValueAt(Int, array1, i)) == i);

    cgArray_deleteValues(Int, array1);
    cgArray_delete(Int, array2);
    
    printf("ok -- ");
}
int main() {
    printf("=== %s ===\n", __FILE__);
    cgAppState__init(__FILE__);
    appState = cgAppState__getInstance();
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
    cgAppState__deInit();
    printf("=== %s ok ===\n", __FILE__);
    return 0;
}
