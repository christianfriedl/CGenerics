#include"cgLogger.h"

void cgLogger__init(const char* ident) {
    openlog(ident, LOG_PERROR, LOG_USER);
}
void cgLogger__log(int priority, char* msg, ...) {
    va_list args;
    va_start(args, msg);
    vsyslog(priority, msg, args);
    va_end(args);
}
void cgLogger__vlog(int priority, char* msg, va_list args) {
    vsyslog(priority, msg, args);
}
void cgLogger__debug(char* msg, ...) {
    va_list args;
    va_start(args, msg);
    vsyslog(LOG_DEBUG, msg, args);
    va_end(args);
}
void cgLogger__vdebug(char* msg, va_list args) {
    vsyslog(LOG_DEBUG, msg, args);
}
void cgLogger__notice(char* msg, ...) {
    va_list args;
    va_start(args, msg);
    vsyslog(LOG_NOTICE, msg, args);
    va_end(args);
}
void cgLogger__vnotice(char* msg, va_list args) {
    vsyslog(LOG_NOTICE, msg, args);
}
void cgLogger__warn(char* msg, ...) {
    va_list args;
    va_start(args, msg);
    vsyslog(LOG_WARNING, msg, args);
    va_end(args);
}
void cgLogger__vwarn(char* msg, va_list args) {
    vsyslog(LOG_WARNING, msg, args);
}
void cgLogger__error(char* msg, ...) {
    va_list args;
    va_start(args, msg);
    vsyslog(LOG_ERR, msg, args);
    va_end(args);
}
void cgLogger__verror(char* msg, va_list args) {
    vsyslog(LOG_ERR, msg, args);
}
