#include"CGLogger.h"

void CGLogger__log(int priority, char* msg, ...) {
    va_list args;
    va_start(args, msg);
    vsyslog(priority, msg, args);
    va_end(args);
}
void CGLogger__vlog(int priority, char* msg, va_list args) {
    vsyslog(priority, msg, args);
}
void CGLogger__debug(char* msg, ...) {
    va_list args;
    va_start(args, msg);
    vsyslog(LOG_DEBUG, msg, args);
    va_end(args);
}
void CGLogger__vdebug(char* msg, va_list args) {
    vsyslog(LOG_DEBUG, msg, args);
}
void CGLogger__notice(char* msg, ...) {
    va_list args;
    va_start(args, msg);
    vsyslog(LOG_NOTICE, msg, args);
    va_end(args);
}
void CGLogger__vnotice(char* msg, va_list args) {
    vsyslog(LOG_NOTICE, msg, args);
}
void CGLogger__warn(char* msg, ...) {
    va_list args;
    va_start(args, msg);
    vsyslog(LOG_WARNING, msg, args);
    va_end(args);
}
void CGLogger__vwarn(char* msg, va_list args) {
    vsyslog(LOG_WARNING, msg, args);
}
void CGLogger__error(char* msg, ...) {
    va_list args;
    va_start(args, msg);
    vsyslog(LOG_ERR, msg, args);
    va_end(args);
}
void CGLogger__verror(char* msg, va_list args) {
    vsyslog(LOG_ERR, msg, args);
}
