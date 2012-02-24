#ifndef _CGLOGGER_H
#define _CGLOGGER_H

#include<syslog.h>
#include<stdarg.h>

void CGLogger__init(const char* ident);
void CGLogger__log(int priority, char* msg, ...);
void CGLogger__vlog(int priority, char* msg, va_list args);
void CGLogger__debug(char* msg, ...);
void CGLogger__vdebug(char* msg, va_list args);
void CGLogger__notice(char* msg, ...);
void CGLogger__vnotice(char* msg, va_list args);
void CGLogger__warn(char* msg, ...);
void CGLogger__vwarn(char* msg, va_list args);
void CGLogger__error(char* msg, ...);
void CGLogger__verror(char* msg, va_list args);

#endif
