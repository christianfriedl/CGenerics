#include<string.h>
#include<stdlib.h>
#include"Exception.h"
#include"Logger.h"

Exception GeneralFatalException = { Sincerety_fatal, ExceptionID_GeneralFatalException, "General Fatal Exception" };

Exception* Exception__new(const Sincerety sincerety, const int id, const char* msg) {
    Exception* this = malloc(sizeof(*this));
    if (this != NULL) {
        this->sincerety = sincerety;
        this->id = id;
        this->msg = strdup(msg);
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
        case Sincerety_none:
            break;
        case Sincerety_notice:
            Logger__notice(this->msg);
            break;
        case Sincerety_warning:
            Logger__warn(this->msg);
            break;
        case Sincerety_error:
            Logger__error(this->msg);
            break;
        case Sincerety_fatal:
            Logger__error(this->msg);
            Logger__error("aborting");
            abort();
            break;
    }
}

