#include"Logger.h"

void Logger__log(int priority, char* msg, ...) {
    va_list args;
    va_start(args, msg);
    vsyslog(priority, msg, args);
    va_end(args);
}
void Logger__vlog(int priority, char* msg, va_list args) {
    vsyslog(priority, msg, args);
}
void Logger__debug(char* msg, ...) {
    va_list args;
    va_start(args, msg);
    vsyslog(LOG_DEBUG, msg, args);
    va_end(args);
}
void Logger__vdebug(char* msg, va_list args) {
    vsyslog(LOG_DEBUG, msg, args);
}
void Logger__notice(char* msg, ...) {
    va_list args;
    va_start(args, msg);
    vsyslog(LOG_NOTICE, msg, args);
    va_end(args);
}
void Logger__vnotice(char* msg, va_list args) {
    vsyslog(LOG_NOTICE, msg, args);
}
void Logger__warn(char* msg, ...) {
    va_list args;
    va_start(args, msg);
    vsyslog(LOG_WARNING, msg, args);
    va_end(args);
}
void Logger__vwarn(char* msg, va_list args) {
    vsyslog(LOG_WARNING, msg, args);
}
void Logger__error(char* msg, ...) {
    va_list args;
    va_start(args, msg);
    vsyslog(LOG_ERR, msg, args);
    va_end(args);
}
void Logger__verror(char* msg, va_list args) {
    vsyslog(LOG_ERR, msg, args);
}
