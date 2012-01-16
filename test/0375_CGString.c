#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include<string.h>
#include"CGAppState.h"
#include"CGString.h"

CGAppState* appState;

void testNewDelete() {
    printf("%s...\n", __func__);
    CGString* s = CGString__new(appState, "abcde");
    assert(s != NULL);
    assert(!strcmp(s->vector, "abcde"));
    CGString_delete(appState, s);
    printf("%s ok\n", __func__);
}
void testToVector() {
    printf("%s...\n", __func__);
    CGString* s = CGString__new(appState, "abcde");
    char *v = CGString_toVector(appState, s);
    assert(!strcmp(v, s->vector));
    free(v);
    CGString_delete(appState, s);
    printf("%s ok\n", __func__);
}

void testClone() {
    printf("%s...\n", __func__);
    CGString* s = CGString__new(appState, "abcde");
    CGString* s2 = CGString_clone(appState, s);
    assert(s2 != NULL);
    assert(!strcmp(s2->vector, "abcde"));
    CGString_delete(appState, s2);
    CGString_delete(appState, s);
    printf("%s ok\n", __func__);
}


int main() {
    printf("=== %s ===\n", __FILE__);

    appState = CGAppState__new();

    testNewDelete();
    testClone();
    testToVector();

    CGAppState_delete(appState);
    printf("=== %s ok ===\n", __FILE__);
    return 0;
}
