#define _GNU_SOURCE
#include<stdio.h>
#undef _GNU_SOURCE
#include<string.h>
#include<stdlib.h>
#include"CGException.h"
#include"CGLogger.h"

CGException CGGeneralFatalException = { Severity_fatal, CGExceptionID_GeneralFatalException, "General Fatal CGException" };

CGException* CGException__new(const Severity severity, const int id, const char* msg, ...) {
    CGException* this = malloc(sizeof(*this));
    if (this != NULL) {
        this->severity = severity;
        this->id = id;
        if (msg != NULL) {
            va_list args;
            va_start(args, msg);
            vasprintf(&this->msg, msg, args);
            va_end(args);
        } else
            this->msg = NULL;
    } else {
        CGLogger__error("Cannot allocate exception, aborting.");
        abort();
    }
    return this;
}
CGException* CGException__newWithMetadata(const Severity severity, const int id, const char* file, const char* func, const int line, const char* msg, ...) {
    CGException* this = malloc(sizeof(*this));
    if (this != NULL) {
        this->severity = severity;
        this->id = id;
        int len = 0;
        if (msg != NULL)
            len = strlen(msg);
        char *metatataFmt = " in %s (at %s:%i)";
        char *metadataMsg = NULL;
        asprintf(&metadataMsg, metatataFmt, func, file, line);
        char *msg2 = malloc((len + strlen(metadataMsg) + 1) * sizeof(char));
        if (len)
            strcpy(msg2, msg);
        else
            msg2[0] =  '\0';
        strcat(msg2, metadataMsg);
        if (msg != NULL) {
            va_list args;
            va_start(args, msg);
            vasprintf(&this->msg, msg2, args);
            va_end(args);
            free(msg2);
        } else
            this->msg = msg2;
    } else {
        CGLogger__error("Cannot allocate exception, aborting.");
        abort();
    }
    return this;
}
void CGException_delete(CGException* this) {
    free(this);
}

void CGException_log(CGException* this) {
    switch(this->severity) {
        case Severity_none:
            break;
        case Severity_notice:
            CGLogger__notice(this->msg);
            break;
        case Severity_warning:
            CGLogger__warn(this->msg);
            break;
        case Severity_error:
            CGLogger__error(this->msg);
            break;
        case Severity_fatal:
            CGLogger__error(this->msg);
            CGLogger__error("aborting");
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
    if (this->msg != NULL)
        return strdup(this->msg);
    else
        return NULL;
}
