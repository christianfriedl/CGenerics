#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include"CGAppState.h"

void testNewDelete() {
    printf("%s...\n", __func__);
    CGAppState* appState = CGAppState__new(__FILE__);
    assert(appState != NULL);
    CGAppState_delete(appState);
    printf("%s ok\n", __func__);
}

void testExceptionNewDelete() {
    printf("%s...\n", __func__);

    CGException* e = CGException__new(Severity_error, CGExceptionID_GeneralFatalException, "testing");
    assert(e != NULL);
    assert(CGException_getId(e) == CGExceptionID_GeneralFatalException);
    assert(CGException_getSeverity(e) == Severity_error);
    char *msg = CGException_getMsg(e);
    assert(!strcmp(msg, "testing"));
    free(msg);
    CGException_delete(e);

    printf("%s ok\n", __func__);
}
void testThrowCatch() {
    printf("%s...\n", __func__);
    CGAppState* appState = CGAppState__new(__FILE__);
    assert(CGAppState_isExceptionRaised(appState) == false);
    CGException* e = CGException__new(Severity_error, CGExceptionID_GeneralFatalException, "testing");
    CGAppState_throwException(appState, e);
    assert(CGAppState_isExceptionRaised(appState) == true);
    assert(CGAppState_isExceptionRaisedWithID(appState, CGExceptionID_CannotAllocate) == false);
    assert(CGAppState_isExceptionRaisedWithID(appState, CGExceptionID_GeneralFatalException) == true);
    assert(CGAppState_getException(appState) == e);
    assert(CGAppState_catchExceptionWithID(appState, CGExceptionID_CannotAllocate) == NULL);
    assert(CGAppState_isExceptionRaisedWithID(appState, CGExceptionID_GeneralFatalException) == true);
    assert(CGAppState_catchExceptionWithID(appState, CGExceptionID_GeneralFatalException) == e);
    assert(CGAppState_catchExceptionWithID(appState, CGExceptionID_GeneralFatalException) == NULL);
    e = CGException__new(Severity_error, CGExceptionID_GeneralFatalException, "testing");
    CGAppState_throwException(appState, e);
    assert(CGAppState_catchException(appState) == e);
    assert(CGAppState_catchException(appState) == NULL);
    CGException_delete(e);
    e = CGException__new(Severity_error, CGExceptionID_GeneralFatalException, "testing");
    CGAppState_throwException(appState, e);
    assert(CGAppState_isExceptionRaisedWithSeverity(appState, Severity_none) == false);
    assert(CGAppState_isExceptionRaisedWithSeverity(appState, Severity_error) == true);
    assert(CGAppState_catchExceptionWithSeverity(appState, Severity_none) == NULL);
    assert(CGAppState_catchExceptionWithSeverity(appState, Severity_error) == e);
    CGAppState_delete(appState);
    printf("%s ok\n", __func__);
}


int main() {
    printf("=== %s ===\n", __FILE__);

    testNewDelete();
    testExceptionNewDelete();
    testThrowCatch();

    printf("=== %s ok ===\n", __FILE__);
    return 0;
}

