#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include"AppState.h"

void testNewDelete() {
    printf("%s...\n", __func__);
    AppState* appState = AppState__new();
    assert(appState != NULL);
    AppState_delete(appState);
    printf("%s ok\n", __func__);
}

void testExceptionNewDelete() {
    printf("%s...\n", __func__);

    Exception* e = Exception__new(Severity_error, ExceptionID_GeneralFatalException, "testing");
    assert(e != NULL);
    assert(Exception_getId(e) == ExceptionID_GeneralFatalException);
    assert(Exception_getSeverity(e) == Severity_error);
    char *msg = Exception_getMsg(e);
    assert(!strcmp(msg, "testing"));
    free(msg);
    Exception_delete(e);

    printf("%s ok\n", __func__);
}
void testThrowCatch() {
    printf("%s...\n", __func__);
    AppState* appState = AppState__new();
    assert(AppState_isExceptionRaised(appState) == false);
    Exception* e = Exception__new(Severity_error, ExceptionID_GeneralFatalException, "testing");
    AppState_throwException(appState, e);
    assert(AppState_isExceptionRaised(appState) == true);
    assert(AppState_isExceptionRaisedWithID(appState, ExceptionID_CannotAllocate) == false);
    assert(AppState_isExceptionRaisedWithID(appState, ExceptionID_GeneralFatalException) == true);
    assert(AppState_getException(appState) == e);
    assert(AppState_catchExceptionWithID(appState, ExceptionID_CannotAllocate) == false);
    assert(AppState_isExceptionRaisedWithID(appState, ExceptionID_GeneralFatalException) == true);
    assert(AppState_catchExceptionWithID(appState, ExceptionID_GeneralFatalException) == true);
    assert(AppState_catchExceptionWithID(appState, ExceptionID_GeneralFatalException) == false);
    e = Exception__new(Severity_error, ExceptionID_GeneralFatalException, "testing");
    AppState_throwException(appState, e);
    assert(AppState_catchException(appState) == true);
    assert(AppState_catchException(appState) == false);
    e = Exception__new(Severity_error, ExceptionID_GeneralFatalException, "testing");
    AppState_throwException(appState, e);
    assert(AppState_isExceptionRaisedWithSeverity(appState, Severity_none) == false);
    assert(AppState_isExceptionRaisedWithSeverity(appState, Severity_error) == true);
    assert(AppState_catchExceptionWithSeverity(appState, Severity_none) == false);
    assert(AppState_catchExceptionWithSeverity(appState, Severity_error) == true);
    AppState_delete(appState);
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

