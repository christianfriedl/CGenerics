#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include"CGAppState.h"
#include"CGInteger.h"

CGAppState* appState;

void testNewDelete() {
    printf("%s...\n", __func__);
    CGInteger* i = CGInteger__new(1);
    assert(i != NULL);
    assert(*i == 1);
    CGInteger_delete(i);
    printf("%s ok\n", __func__);
}
void testToInt() {
    printf("%s...\n", __func__);
    CGInteger* i = CGInteger__new(1);
    assert(CGInteger_toInt(i) == 1);
    CGInteger_delete(i);
    printf("%s ok\n", __func__);
}

void testClone() {
    printf("%s...\n", __func__);
    CGInteger* i = CGInteger__new(1);
    CGInteger* i2 = CGInteger_clone(i);
    assert(i2 != NULL);
    assert(CGInteger_toInt(i2) == 1);
    CGInteger_delete(i);
    printf("%s ok\n", __func__);
}


int main() {
    printf("=== %s ===\n", __FILE__);

    CGAppState__init(__FILE__);
    appState = CGAppState__getInstance();

    testNewDelete();
    testClone();
    testToInt();

    CGAppState__deInit();
    printf("=== %s ok ===\n", __FILE__);
    return 0;
}
