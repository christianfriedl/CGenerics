#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include<string.h>
#include"cgAppState.h"
#include"cgString.h"

cgAppState* appState;

void testNewDelete() {
    printf("%s... ", __func__);
    cgString* s = cgString__new("abcde");
    assert(s != NULL);
    assert(!strcmp(s, "abcde"));
    cgString_delete(s);
    printf("ok -- ");
}

void testDeleteAll() {
    printf("%s... ", __func__);
    cgString* s = cgString__new("abcde");
    cgString* s2 = cgString__new("fgh");
    assert(s != NULL);
    assert(s2 != NULL);
    cgString_deleteAll(s, s2, NULL);
    printf("ok -- ");
}

void testNewFromLengthAndPreset() {
    printf("%s... ", __func__);
    cgString* s = cgString__newFromLengthAndPreset(20, 'x');
    assert(s != NULL);
    assert(!strcmp(s, "xxxxxxxxxxxxxxxxxxxx"));
    cgString_delete(s);
    printf("ok -- ");
}

void testToVector() {
    printf("%s... ", __func__);
    cgString* s = cgString__new("abcde");
    char *v = cgString_toVector(s);
    assert(!strcmp(v, s));
    free(v);
    cgString_delete(s);
    printf("ok -- ");
}

void testClone() {
    printf("%s... ", __func__);
    cgString* s = cgString__new("abcde");
    cgString* s2 = cgString_clone(s);
    assert(s2 != NULL);
    assert(!strcmp(s2, "abcde"));
    cgString_delete(s2);
    cgString_delete(s);
    printf("ok -- ");
}

void testAppend() {
    printf("%s... ", __func__);
    cgString* s = cgString__new("abcde");
    cgString* s2 = cgString__new("fghijk");
    cgString* s3 = cgString_append(s, s2);
    cgString* c = cgString__new("abcdefghijk");
    assert(!cgString__compare(s3, c));
    cgString_delete(c);
    cgString_delete(s3);
    cgString_delete(s2);
    cgString_delete(s);
    printf("ok -- ");
}

void testAppend2() {
    printf("%s... ", __func__);
    cgString* s = cgString__new("");
    cgString* s3 = cgString__newWithSprintf("%i", 1);
    cgString* s2 = cgString_append(s, s3);
    cgString* s4 = cgString__new("1");
    assert(!cgString__compare(s2, s4));
    cgString_delete(s);
    cgString_delete(s2);
    cgString_delete(s3);
    cgString_delete(s4);
    printf("ok -- ");
}

void testSize() {
    printf("%s... ", __func__);
    cgString* s = cgString__new("abcde");
    assert(cgString_getSize(s) == 5);
    cgString_delete(s);
    printf("ok -- ");
}

void testSubstring() {
    printf("%s... ", __func__);
    cgString* s = cgString__new("abcde");
    cgString* s2 = cgString_createSubstring(s, 1, 3);
    assert(!cgString__compare(s2, "bcd"));
    cgString_delete(s2);
    s2 = cgString_createSubstring(s, 1, 300);
    assert(!cgString__compare(s2, "bcde"));
    cgString_delete(s2);
    s2 = cgString_createSubstring(s, 10, 1);
    assert(cgAppState_catchAndDeleteExceptionWithID(appState, cgExceptionID_StringError) == true);
    assert(s2 == NULL);

    cgString_delete(s);
    printf("ok -- ");
}

void testNewWithSprintf() {
    printf("%s... ", __func__);
    cgString* s = cgString__newWithSprintf("%s %i", "abcde", 20);
    assert(!cgString__compare(s, "abcde 20"));

    cgString_delete(s);
    printf("ok -- ");
}

void testGetCharAt() {
    printf("%s... ", __func__);
    cgString* s = cgString__new("xyz");
    assert(cgString_getCharAt(s, 0) == 'x');
    assert(cgString_getCharAt(s, 1) == 'y');
    assert(cgString_getCharAt(s, 2) == 'z');
    assert(cgString_getCharAt(s, 3) == '\0');
    assert(cgAppState_isExceptionRaisedWithID(cgAppState__getInstance(), cgExceptionID_StringError) == true);

    cgString_delete(s);
    printf("ok -- ");
}

void testAppendI() {
    printf("%s... ", __func__);
    cgString* s = cgString__new("xyz");
    cgString* s2 = cgString__new("abc");
    s = cgString_append_I(s, s2);
    assert(!cgString__compare(s, "xyzabc"));
    s = cgString_appendWithSprintf_I(s, "--%s", s2);
    assert(!cgString__compare(s, "xyzabc--abc"));
    cgString_delete(s);
    cgString_delete(s2);
    printf("ok -- ");
}

int main() {
    printf("=== %s ===\n", __FILE__);

    cgAppState__init(__FILE__);
    appState = cgAppState__getInstance();

    testNewDelete();
    testDeleteAll();
    testNewFromLengthAndPreset();
    testNewWithSprintf();
    testClone();
    testToVector();
    testAppend();
    testAppend2();
    testAppendI();
    testSize();
    testSubstring();
    testGetCharAt();

    cgAppState__deInit();
    printf("=== %s ok ===\n", __FILE__);
    return 0;
}
