#ifndef _CGEXCEPTION_H
#define _CGEXCEPTION_H

#define cgExceptionID_GeneralFatalException       (0)
#define cgExceptionID_GeneralNonfatalException    (1)
#define cgExceptionID_CannotAllocate              (2) 
#define cgExceptionID_ArrayIndexOutOfBounds     (100) 
#define cgExceptionID_ElementNotFound           (102)
#define cgExceptionID_StringError               (103)


typedef enum { Severity_none = 0, Severity_notice = 1, Severity_warning = 2, Severity_error = 3, Severity_fatal = 4 } Severity;

typedef struct {
    Severity severity;
    int id;   
    char *msg;
} cgException;

/* generic exception that will result in aborting the program */
extern cgException cgGeneralFatalException;

cgException* cgException__new(const Severity severity, const int id, const char* msg, ...);
cgException* cgException__newWithMetadata(const Severity severity, const int id, const char* file, const char* func, const int line, const char* msg, ...);
void cgException_delete(cgException* this);
Severity cgException_getSeverity(const cgException* this);
int cgException_getId(const cgException* this);
char *cgException_getMsg(const cgException* this);
void cgException_log(cgException* this);


#endif
