#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"Array.h"

INIT_ARRAY(int, int)

int main() {
    Array(int)* array = Array__new(int, 20);

    printf("capacity: %u\n", Array_getCapacity(int, array));

    Array_add(int, array, 2);
    Array_add(int, array, 3);
    Array_push(int, array, 4);

    printf("size: %u\n", Array_getSize(int, array));

    int x = Array_getValueAt(int, array, 0);
    printf("x@0: %u\n", x);
    x = Array_getValueAt(int, array, 1);
    printf("x@1: %u\n", x);
    x = Array_getValueAt(int, array, 2);
    printf("x@2: %u\n", x);


    x = Array_pop(int, array);
    printf("x@2: %u\n", x);
    x = Array_pop(int, array);
    printf("x@1: %u\n", x);
    x = Array_pop(int, array);
    printf("x@0: %u\n", x);

    printf("size: %u\n", Array_getSize(int, array));

    Array_delete(int, array);

    return 0;
}
