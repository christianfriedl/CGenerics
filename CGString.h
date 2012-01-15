#ifndef _STRING_H
#define _STRING_H

#include<string.h>
#include"AppState.h"

typedef struct {
    char* vector;
} String;

String* String__new(AppState* appState, const char* value);
String* String_clone(AppState* appState, const String* this);
void String_delete(AppState* appState, String* this);
char* String_toVector(AppState* appState, const String* this);
int String__compare(AppState* appState, const String* i1, const String* i2);

#endif
