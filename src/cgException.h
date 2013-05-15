/*
    =====================================================================
    CGenerics - Datatypes and Functions for Generic and OO Programming in C

    Copyright (C) 2012  Christian Friedl

    This file is part of CGenerics.

    CGenerics is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    CGenerics is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    =====================================================================
*/

#ifndef _CGEXCEPTION_H
#define _CGEXCEPTION_H

#define cgExceptionID_GeneralFatalException       (0)
#define cgExceptionID_GeneralNonfatalException    (1)
#define cgExceptionID_CannotAllocate              (2)
#define cgExceptionID_CannotOpenFileForReading	  (3)
#define cgExceptionID_CannotOpenFileForWriting	  (4)

/* this is currently not used in the CG suite itself, but it is a might handy
 * for other cases and shouldn't be redefined for each seperate library, so
 * it's included here */
#define cgExceptionID_NoSuchMethod                (3)
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

cgException *cgException__new(const Severity severity, const int id, const char *msg, ...);

cgException *cgException__newWithMetadata(const Severity severity, const int id, const char *file, const char *func,
                                          const int line, const char *msg, ...);
void cgException_delete(cgException * this);

Severity cgException_getSeverity(const cgException * this);

int cgException_getId(const cgException * this);

char *cgException_getMsg(const cgException * this);

void cgException_log(cgException * this);
#endif
