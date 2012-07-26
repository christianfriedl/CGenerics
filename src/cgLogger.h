#ifndef _CGLOGGER_H
#define _CGLOGGER_H

#include<syslog.h>
#include<stdarg.h>

void cgLogger__init(const char* ident);
void cgLogger__log(int priority, char* msg, ...);
void cgLogger__vlog(int priority, char* msg, va_list args);
void cgLogger__debug(char* msg, ...);
void cgLogger__vdebug(char* msg, va_list args);
void cgLogger__notice(char* msg, ...);
void cgLogger__vnotice(char* msg, va_list args);
void cgLogger__warn(char* msg, ...);
void cgLogger__vwarn(char* msg, va_list args);
void cgLogger__error(char* msg, ...);
void cgLogger__verror(char* msg, va_list args);

#endif
