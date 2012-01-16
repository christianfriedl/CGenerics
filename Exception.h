#ifndef _EXCEPTION_H
#define _EXCEPTION_H

#define ExceptionID_GeneralFatalException       (0)
#define ExceptionID_CannotAllocate              (1) 
#define ExceptionID_CGArrayIndexOutOfBounds   (100) 
#define ExceptionID_ElementNotFound (102)


typedef enum { Severity_none = 0, Severity_notice = 1, Severity_warning = 2, Severity_error = 3, Severity_fatal = 4 } Severity;

typedef struct {
    Severity severity;
    int id;   
    char *msg;
} Exception;

/* generic exception that will result in aborting the program */
extern Exception GeneralFatalException;

Exception* Exception__new(const Severity severity, const int id, const char* msg, ...);
void Exception_delete(Exception* this);
Severity Exception_getSeverity(const Exception* this);
int Exception_getId(const Exception* this);
char *Exception_getMsg(const Exception* this);
void Exception_log(Exception* this);

#endif
