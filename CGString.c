#include<stdlib.h>
#include"CGString.h"
#include"CGAppState.h"

String* String__new(CGAppState* appState, const char* value) {
    String* this = malloc(sizeof(*this));
    if (this != NULL) {
        this->vector = malloc(sizeof(char) * (strlen(value) + 1));
        if (this->vector != NULL)
            strcpy(this->vector, value);
        else
            CGAppState_throwException(appState, Exception__new(Severity_error, ExceptionID_CannotAllocate, "unable to allocate String vector for '%s'", value));
    } else
        CGAppState_throwException(appState, Exception__new(Severity_error, ExceptionID_CannotAllocate, "unable to allocate String for '%s'", value));
    return this;
}
String* String_clone(CGAppState* appState, const String* this) {
    return String__new(appState, (const char*)this->vector);
}
void String_delete(CGAppState* appState, String* this) {
    free(this->vector);
    free(this);
}
char* String_toVector(CGAppState* appState, const String* this) {
    return strdup(this->vector);
}
int String__compare(CGAppState* appState, const String* s1, const String* s2) {
    return (strcmp(s1->vector, s2->vector));
}
