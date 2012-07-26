#define _GNU_SOURCE
#include<stdio.h>
#undef _GNU_SOURCE
#include<string.h>
#include<stdlib.h>
#include"cgException.h"
#include"cgLogger.h"

cgException cgGeneralFatalException = { Severity_fatal, cgExceptionID_GeneralFatalException, "General Fatal cgException" };

cgException* cgException__new(const Severity severity, const int id, const char* msg, ...) {
    cgException* this = malloc(sizeof(*this));
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
        cgLogger__error("Cannot allocate exception, aborting.");
        abort();
    }
    return this;
}
cgException* cgException__newWithMetadata(const Severity severity, const int id, const char* file, const char* func, const int line, const char* msg, ...) {
    cgException* this = malloc(sizeof(*this));
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
        cgLogger__error("Cannot allocate exception, aborting.");
        abort();
    }
    return this;
}
void cgException_delete(cgException* this) {
    free(this);
}

void cgException_log(cgException* this) {
    switch(this->severity) {
        case Severity_none:
            break;
        case Severity_notice:
            cgLogger__notice(this->msg);
            break;
        case Severity_warning:
            cgLogger__warn(this->msg);
            break;
        case Severity_error:
            cgLogger__error(this->msg);
            break;
        case Severity_fatal:
            cgLogger__error(this->msg);
            cgLogger__error("aborting");
            abort();
            break;
    }
}
Severity cgException_getSeverity(const cgException* this) {
    return this->severity;
}
int cgException_getId(const cgException* this) {
    return this->id;
}
char *cgException_getMsg(const cgException* this) {
    if (this->msg != NULL)
        return strdup(this->msg);
    else
        return NULL;
}
