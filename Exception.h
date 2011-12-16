#ifndef _EXCEPTION_H
#define _EXCEPTION_H

#define ExceptionID_GeneralFatalException       0

typedef enum { Severity_none = 0, Severity_notice = 1, Severity_warning = 2, Severity_error = 3, Severity_fatal = 4 } Severity;

typedef struct {
    Severity sincerety;
    int id;   
    char *msg;
} Exception;

/* generic exception that will result in aborting the program */
extern Exception GeneralFatalException;

Exception* Exception__new(const Severity sincerety, const int id, const char* msg, ...);
void Exception_delete(Exception* this);
void Exception_log(Exception* this);

#endif
