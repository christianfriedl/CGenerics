#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"Exception.h"
#include"Logger.h"

Exception GeneralFatalException = { Severity_fatal, ExceptionID_GeneralFatalException, "General Fatal Exception" };

Exception* Exception__new(const Severity sincerety, const int id, const char* msg, ...) {
    Exception* this = malloc(sizeof(*this));
    if (this != NULL) {
        this->sincerety = sincerety;
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
void Exception_delete(Exception* this) {
    free(this->msg);
    free(this);
}

void Exception_log(Exception* this) {
    switch(this->sincerety) {
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

