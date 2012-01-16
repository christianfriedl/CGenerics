#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"CGException.h"
#include"Logger.h"

CGException GeneralFatalCGException = { Severity_fatal, CGExceptionID_GeneralFatalException, "General Fatal CGException" };

CGException* CGException__new(const Severity severity, const int id, const char* msg, ...) {
    CGException* this = malloc(sizeof(*this));
    if (this != NULL) {
        this->severity = severity;
        this->id = id;
        va_list args;
        va_start(args, msg);
        vasprintf(&this->msg, msg, args);
        va_end(args);
    } else {
        Logger__error("Cannot allocate exception, aborting.");
        abort();
    }
    return this;
}
void CGException_delete(CGException* this) {
    free(this->msg);
    free(this);
}

void CGException_log(CGException* this) {
    switch(this->severity) {
        case Severity_none:
            break;
        case Severity_notice:
            Logger__notice(this->msg);
            break;
        case Severity_warning:
            Logger__warn(this->msg);
            break;
        case Severity_error:
            Logger__error(this->msg);
            break;
        case Severity_fatal:
            Logger__error(this->msg);
            Logger__error("aborting");
            abort();
            break;
    }
}
Severity CGException_getSeverity(const CGException* this) {
    return this->severity;
}
int CGException_getId(const CGException* this) {
    return this->id;
}
char *CGException_getMsg(const CGException* this) {
    return strdup(this->msg);
}
