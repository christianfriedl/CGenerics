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
    assert(!strcmp(s, "abcde"));
    CGString_delete(appState, s);
    printf("%s ok\n", __func__);
}
void testNewFromLengthAndPreset() {
    printf("%s...\n", __func__);
    CGString* s = CGString__newFromLengthAndPreset(appState, 20, 'x');
    assert(s != NULL);
    assert(!strcmp(s, "xxxxxxxxxxxxxxxxxxxx"));
    CGString_delete(appState, s);
    printf("%s ok\n", __func__);
}
void testToVector() {
    printf("%s...\n", __func__);
    CGString* s = CGString__new(appState, "abcde");
    char *v = CGString_toVector(appState, s);
    assert(!strcmp(v, s));
    free(v);
    CGString_delete(appState, s);
    printf("%s ok\n", __func__);
}

void testClone() {
    printf("%s...\n", __func__);
    CGString* s = CGString__new(appState, "abcde");
    CGString* s2 = CGString_clone(appState, s);
    assert(s2 != NULL);
    assert(!strcmp(s2, "abcde"));
    CGString_delete(appState, s2);
    CGString_delete(appState, s);
    printf("%s ok\n", __func__);
}

void testAppend() {
    printf("%s...\n", __func__);
    CGString* s = CGString__new(appState, "abcde");
    CGString* s2 = CGString__new(appState, "fghijk");
    CGString_append(appState, s, s2);
    CGString* c = CGString__new(appState, "abcdefghijk");
    assert(!CGString__compare(appState, s, c));
    CGString_delete(appState, c);
    CGString_delete(appState, s2);
    CGString_delete(appState, s);
    printf("%s ok\n", __func__);
}

void testSize() {
    printf("%s...\n", __func__);
    CGString* s = CGString__new(appState, "abcde");
    assert(CGString_getSize(appState, s) == 5);
    CGString_delete(appState, s);
    printf("%s ok\n", __func__);
}



int main() {
    printf("=== %s ===\n", __FILE__);

    appState = CGAppState__new();

    testNewDelete();
    testNewFromLengthAndPreset();
    testClone();
    testToVector();
    testAppend();
    testSize();

    CGAppState_delete(appState);
    printf("=== %s ok ===\n", __FILE__);
    return 0;
}
