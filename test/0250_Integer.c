#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include"cgAppState.h"
#include"cgInteger.h"

cgAppState* appState;

void testNewDelete() {
    printf("%s... ", __func__);
    cgInteger* i = cgInteger__new(1);
    assert(i != NULL);
    assert(*i == 1);
    cgInteger_delete(i);
    printf("ok -- ");
}
void testToInt() {
    printf("%s... ", __func__);
    cgInteger* i = cgInteger__new(1);
    assert(cgInteger_toInt(i) == 1);
    cgInteger_delete(i);
    printf("ok -- ");
}

void testClone() {
    printf("%s... ", __func__);
    cgInteger* i = cgInteger__new(1);
    cgInteger* i2 = cgInteger_clone(i);
    assert(i2 != NULL);
    assert(cgInteger_toInt(i2) == 1);
    cgInteger_delete(i);
    printf("ok -- ");
}


int main() {
    printf("=== %s ===\n", __FILE__);

    cgAppState__init(__FILE__);
    appState = cgAppState__getInstance();

    testNewDelete();
    testClone();
    testToInt();

    cgAppState__deInit();
    printf("=== %s ok ===\n", __FILE__);
    return 0;
}
