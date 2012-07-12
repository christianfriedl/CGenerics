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
    printf("%s... ", __func__);
    CGString* s = CGString__new("abcde");
    assert(s != NULL);
    assert(!strcmp(s, "abcde"));
    CGString_delete(s);
    printf("ok -- ");
}
void testNewFromLengthAndPreset() {
    printf("%s... ", __func__);
    CGString* s = CGString__newFromLengthAndPreset(20, 'x');
    assert(s != NULL);
    assert(!strcmp(s, "xxxxxxxxxxxxxxxxxxxx"));
    CGString_delete(s);
    printf("ok -- ");
}
void testToVector() {
    printf("%s... ", __func__);
    CGString* s = CGString__new("abcde");
    char *v = CGString_toVector(s);
    assert(!strcmp(v, s));
    free(v);
    CGString_delete(s);
    printf("ok -- ");
}

void testClone() {
    printf("%s... ", __func__);
    CGString* s = CGString__new("abcde");
    CGString* s2 = CGString_clone(s);
    assert(s2 != NULL);
    assert(!strcmp(s2, "abcde"));
    CGString_delete(s2);
    CGString_delete(s);
    printf("ok -- ");
}

void testAppend() {
    printf("%s... ", __func__);
    CGString* s = CGString__new("abcde");
    CGString* s2 = CGString__new("fghijk");
    CGString* s3 = CGString_append(s, s2);
    CGString* c = CGString__new("abcdefghijk");
    assert(!CGString__compare(s3, c));
    CGString_delete(c);
    CGString_delete(s3);
    CGString_delete(s2);
    CGString_delete(s);
    printf("ok -- ");
}

void testSize() {
    printf("%s... ", __func__);
    CGString* s = CGString__new("abcde");
    assert(CGString_getSize(s) == 5);
    CGString_delete(s);
    printf("ok -- ");
}

void testSubstring() {
    printf("%s... ", __func__);
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
    printf("ok -- ");
}

void testNewWithSprintf() {
    printf("%s... ", __func__);
    CGString* s = CGString__newWithSprintf("%s %i", "abcde", 20);
    assert(!CGString__compare(s, "abcde 20"));

    CGString_delete(s);
    printf("ok -- ");
}

void testGetCharAt() {
    printf("%s... ", __func__);
    CGString* s = CGString__new("xyz");
    assert(CGString_getCharAt(s, 0) == 'x');
    assert(CGString_getCharAt(s, 1) == 'y');
    assert(CGString_getCharAt(s, 2) == 'z');
    assert(CGString_getCharAt(s, 3) == '\0');
    assert(CGAppState_isExceptionRaisedWithID(CGAppState__getInstance(), CGExceptionID_StringError) == true);

    CGString_delete(s);
    printf("ok -- ");
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
    testGetCharAt();

    CGAppState__deInit();
    printf("=== %s ok ===\n", __FILE__);
    return 0;
}
