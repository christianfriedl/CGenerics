#ifndef _EXCEPTION_H
#define _EXCEPTION_H

#define ExceptionID_GeneralFatalException       0

typedef enum { Sincerety_none = 0, Sincerety_notice = 1, Sincerety_warning = 2, Sincerety_error = 3, Sincerety_fatal = 4 } Sincerety;

typedef struct {
    Sincerety sincerety;
    int id;   
    char *msg;
} Exception;

/* generic exception that will result in aborting the program */
extern Exception GeneralFatalException;

Exception* Exception__new(const Sincerety sincerety, const int id, const char* msg);
void Exception_delete(Exception* this);
void Exception_log(Exception* this);

#endif
