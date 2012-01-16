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
    CGInteger* i = CGInteger__new(appState, 1);
    assert(i != NULL);
    assert(*i == 1);
    CGInteger_delete(appState, i);
    printf("%s ok\n", __func__);
}
void testToInt() {
    printf("%s...\n", __func__);
    CGInteger* i = CGInteger__new(appState, 1);
    assert(CGInteger_toInt(appState, i) == 1);
    CGInteger_delete(appState, i);
    printf("%s ok\n", __func__);
}

void testClone() {
    printf("%s...\n", __func__);
    CGInteger* i = CGInteger__new(appState, 1);
    CGInteger* i2 = CGInteger_clone(appState, i);
    assert(i2 != NULL);
    assert(CGInteger_toInt(appState, i2) == 1);
    CGInteger_delete(appState, i);
    printf("%s ok\n", __func__);
}


int main() {
    printf("=== %s ===\n", __FILE__);

    appState = CGAppState__new();

    testNewDelete();
    testClone();
    testToInt();

    CGAppState_delete(appState);
    printf("=== %s ok ===\n", __FILE__);
    return 0;
}
