#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include"CGAppState.h"
#include"Integer.h"

CGAppState* appState;

void testNewDelete() {
    printf("%s...\n", __func__);
    Integer* i = Integer__new(appState, 1);
    assert(i != NULL);
    assert(*i == 1);
    Integer_delete(appState, i);
    printf("%s ok\n", __func__);
}
void testToInt() {
    printf("%s...\n", __func__);
    Integer* i = Integer__new(appState, 1);
    assert(Integer_toInt(appState, i) == 1);
    Integer_delete(appState, i);
    printf("%s ok\n", __func__);
}

void testClone() {
    printf("%s...\n", __func__);
    Integer* i = Integer__new(appState, 1);
    Integer* i2 = Integer_clone(appState, i);
    assert(i2 != NULL);
    assert(Integer_toInt(appState, i2) == 1);
    Integer_delete(appState, i);
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
