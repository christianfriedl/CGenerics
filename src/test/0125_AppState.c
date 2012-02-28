#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include"CGAppState.h"

CGAppState* appState = NULL;

void testNewDelete() {
    printf("%s... ", __func__);
    CGAppState__init(__FILE__);
    appState = CGAppState__getInstance();
    assert(appState != NULL);
    printf("ok -- ");
}

void testExceptionNewDelete() {
    printf("%s... ", __func__);

    CGException* e = CGException__new(Severity_error, CGExceptionID_GeneralFatalException, "testing");
    assert(e != NULL);
    assert(CGException_getId(e) == CGExceptionID_GeneralFatalException);
    assert(CGException_getSeverity(e) == Severity_error);
    char *msg = CGException_getMsg(e);
    assert(!strcmp(msg, "testing"));
    free(msg);
    CGException_delete(e);

    e = CGException__new(Severity_error, CGExceptionID_GeneralFatalException, NULL);
    assert(CGException_getMsg(e) == NULL);
    CGException_delete(e);

    printf("ok -- ");
}
void testThrowCatch() {
    printf("%s... ", __func__);
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
    printf("ok -- ");
}
void testThrowCatchNoMsg() {
    printf("%s... ", __func__);

    assert(CGAppState_isExceptionRaised(appState) == false);
    CGException* e = CGException__new(Severity_error, CGExceptionID_GeneralFatalException, NULL);
    CGAppState_throwException(appState, e);
    assert(CGAppState_isExceptionRaised(appState) == true);
    assert(CGAppState_isExceptionRaisedWithID(appState, CGExceptionID_CannotAllocate) == false);
    assert(CGAppState_isExceptionRaisedWithID(appState, CGExceptionID_GeneralFatalException) == true);
    assert(CGAppState_getException(appState) == e);
    assert(CGAppState_catchExceptionWithID(appState, CGExceptionID_CannotAllocate) == NULL);
    assert(CGAppState_isExceptionRaisedWithID(appState, CGExceptionID_GeneralFatalException) == true);
    assert(CGAppState_catchExceptionWithID(appState, CGExceptionID_GeneralFatalException) == e);
    assert(CGAppState_catchExceptionWithID(appState, CGExceptionID_GeneralFatalException) == NULL);
    CGException_delete(e);

    printf("ok -- ");
}


int main() {
    printf("=== %s ===\n", __FILE__);

    testNewDelete();
    testExceptionNewDelete();
    testThrowCatch();
    testThrowCatchNoMsg();

    printf("=== %s ok ===\n", __FILE__);
    return 0;
}

