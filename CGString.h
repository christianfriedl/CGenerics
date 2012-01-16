#ifndef _STRING_H
#define _STRING_H

#include<string.h>
#include"CGAppState.h"

typedef struct {
    char* vector;
} String;

String* String__new(CGAppState* appState, const char* value);
String* String_clone(CGAppState* appState, const String* this);
void String_delete(CGAppState* appState, String* this);
char* String_toVector(CGAppState* appState, const String* this);
int String__compare(CGAppState* appState, const String* i1, const String* i2);

#endif
