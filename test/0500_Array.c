#include<stdio.h>
#include<stdlib.h>
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
    Array(int)* array = Array__new(int, 20);

    printf("capacity: %u\n", Array_getCapacity(int, array));

    Array_add(int, array, 2);
    Array_add(int, array, 3);
    Array_push(int, array, 4);

    printf("size: %u\n", Array_getSize(int, array));
    assert(Array_getSize(int, array) == 3);

    int x = Array_getValueAt(int, array, 0);
    printf("x@0: %u\n", x);
    assert(x == 2);
    x = Array_getValueAt(int, array, 1);
    printf("x@1: %u\n", x);
    assert(x == 3);
    x = Array_getValueAt(int, array, 2);
    printf("x@2: %u\n", x);
    assert(x == 4);


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

int main() {
    testArrayNewDelete();
    testIntArray();
    return 0;
}
