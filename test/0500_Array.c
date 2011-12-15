#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include"Array.h"

typedef struct {
    char first_name[20];
    char last_name[20];
} Person;

typedef int* intPtr;

INIT_ARRAY(int)
INIT_ARRAY(intPtr)
INIT_ARRAY(Person)

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
    srandom(time(NULL));
    for (i=0; i < 200000; ++i)
        Array_pop(int, intArray);
    printf("cap %u size %u\n", Array_getCapacity(int, intArray), Array_getSize(int, intArray));
    for (i=0; i < 200000; ++i)
        Array_unshift(int, intArray, i);
    printf("cap %u size %u\n", Array_getCapacity(int, intArray), Array_getSize(int, intArray));
    srandom(time(NULL));
    for (i=0; i < 200000; ++i)
        Array_shift(int, intArray);
    printf("cap %u size %u\n", Array_getCapacity(int, intArray), Array_getSize(int, intArray));

    //printArray(intArray);   
    printf("ok\n");
}

int main() {
    testArrayNewDelete();
    testIntArray();
    testPersonArray();
    testManyPushes();
    return 0;
}
