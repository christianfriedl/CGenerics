#ifndef _CGEXCEPTION_H
#define _CGEXCEPTION_H

#define CGExceptionID_GeneralFatalException       (0)
#define CGExceptionID_CannotAllocate              (1) 
#define CGExceptionID_ArrayIndexOutOfBounds   (100) 
#define CGExceptionID_ElementNotFound (102)


typedef enum { Severity_none = 0, Severity_notice = 1, Severity_warning = 2, Severity_error = 3, Severity_fatal = 4 } Severity;

typedef struct {
    Severity severity;
    int id;   
    char *msg;
} CGException;

/* generic exception that will result in aborting the program */
extern CGException CGGeneralFatalException;

CGException* CGException__new(const Severity severity, const int id, const char* msg, ...);
void CGException_delete(CGException* this);
Severity CGException_getSeverity(const CGException* this);
int CGException_getId(const CGException* this);
char *CGException_getMsg(const CGException* this);
void CGException_log(CGException* this);

#endif
