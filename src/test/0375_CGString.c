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
    CGString* s = CGString__new("abcde");
    assert(s != NULL);
    assert(!strcmp(s, "abcde"));
    CGString_delete(s);
    printf("%s ok\n", __func__);
}
void testNewFromLengthAndPreset() {
    printf("%s...\n", __func__);
    CGString* s = CGString__newFromLengthAndPreset(20, 'x');
    assert(s != NULL);
    assert(!strcmp(s, "xxxxxxxxxxxxxxxxxxxx"));
    CGString_delete(s);
    printf("%s ok\n", __func__);
}
void testToVector() {
    printf("%s...\n", __func__);
    CGString* s = CGString__new("abcde");
    char *v = CGString_toVector(s);
    assert(!strcmp(v, s));
    free(v);
    CGString_delete(s);
    printf("%s ok\n", __func__);
}

void testClone() {
    printf("%s...\n", __func__);
    CGString* s = CGString__new("abcde");
    CGString* s2 = CGString_clone(s);
    assert(s2 != NULL);
    assert(!strcmp(s2, "abcde"));
    CGString_delete(s2);
    CGString_delete(s);
    printf("%s ok\n", __func__);
}

void testAppend() {
    printf("%s...\n", __func__);
    CGString* s = CGString__new("abcde");
    CGString* s2 = CGString__new("fghijk");
    CGString_append(s, s2);
    CGString* c = CGString__new("abcdefghijk");
    assert(!CGString__compare(s, c));
    CGString_delete(c);
    CGString_delete(s2);
    CGString_delete(s);
    printf("%s ok\n", __func__);
}

void testSize() {
    printf("%s...\n", __func__);
    CGString* s = CGString__new("abcde");
    assert(CGString_getSize(s) == 5);
    CGString_delete(s);
    printf("%s ok\n", __func__);
}

void testSubstring() {
    printf("%s...\n", __func__);
    CGString* s = CGString__new("abcde");
    CGString* s2 = CGString_createSubstring(s, 1, 3);
    assert(!CGString__compare(s2, "bcd"));
    CGString_delete(s2);
    s2 = CGString_createSubstring(s, 1, 300);
    assert(!CGString__compare(s2, "bcde"));
    CGString_delete(s2);
    s2 = CGString_createSubstring(s, 10, 1);
    assert(CGAppState_catchAndDeleteExceptionWithID(appState, CGExceptionID_StringError) == true);
    assert(s2 == NULL);

    CGString_delete(s);
    printf("%s ok\n", __func__);
}

void testNewWithSprintf() {
    printf("%s...\n", __func__);
    CGString* s = CGString__newWithSprintf("%s %i", "abcde", 20);
    assert(!CGString__compare(s, "abcde 20"));

    CGString_delete(s);
    printf("%s ok\n", __func__);
}



int main() {
    printf("=== %s ===\n", __FILE__);

    CGAppState__init(__FILE__);
    appState = CGAppState__getInstance();

    testNewDelete();
    testNewFromLengthAndPreset();
    testNewWithSprintf();
    testClone();
    testToVector();
    testAppend();
    testSize();
    testSubstring();

    CGAppState__deInit();
    printf("=== %s ok ===\n", __FILE__);
    return 0;
}
