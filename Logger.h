#ifndef _LOGGER_H
#define _LOGGER_H

#include<syslog.h>
#include<stdarg.h>

void Logger__log(int priority, char* msg, ...);
void Logger__vlog(int priority, char* msg, va_list args);
void Logger__debug(char* msg, ...);
void Logger__vdebug(char* msg, va_list args);
void Logger__notice(char* msg, ...);
void Logger__vnotice(char* msg, va_list args);
void Logger__warn(char* msg, ...);
void Logger__vwarn(char* msg, va_list args);
void Logger__error(char* msg, ...);
void Logger__verror(char* msg, va_list args);

#endif
