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

#ifndef _CGLINKEDLIST_H
#define _CGLINKEDLIST_H

/* NOMAKEMAN */

#include<stdlib.h>
#include<string.h>
#include"cgenerics.h"
#include"cgException.h"

/* everything below this line is type-specific! */

/* declarations */

/** 
    This will init the cgLinkedList for one typename
    NOTE: TYPENAME is a valid identifier; if you plan for a, say, cgLinkedList<int*>, then do a typedef int* intPtr or the like...
*/

#define INIT_LINKEDLIST(TYPENAME) \
struct cgLinkedListElementOf##TYPENAME##_struct { \
    TYPENAME* value; \
    struct cgLinkedListElementOf##TYPENAME##_struct* nextElement; \
}; \
typedef struct cgLinkedListElementOf##TYPENAME##_struct cgLinkedListElementOf##TYPENAME; \
 \
typedef struct { \
    cgLinkedListElementOf##TYPENAME* rootElement; \
    cgLinkedListElementOf##TYPENAME* currentElement; \
    cgLinkedListElementOf##TYPENAME* lastElement; \
} cgLinkedListOf##TYPENAME; \
\
cgLinkedListElementOf##TYPENAME* cgLinkedListElementOf##TYPENAME##__new(TYPENAME* value) { \
    cgLinkedListElementOf##TYPENAME* this = malloc(sizeof(*this)); \
    if (this != NULL) { \
        this->value = value; \
        this->nextElement = NULL; \
    } else \
        cgAppState_throwException(cgAppState__getInstance(), cgException__new(Severity_error, cgExceptionID_CannotAllocate, "unable to allocate cgLinkedListElement for '%s'", "TYPENAME")); \
    return this; \
} \
\
void cgLinkedListElementOf##TYPENAME##_delete(cgLinkedListElementOf##TYPENAME* this) { \
	free(this); \
} \
\
cgLinkedListElementOf##TYPENAME* cgLinkedListElementOf##TYPENAME##_clone(cgLinkedListElementOf##TYPENAME* this) { \
    cgLinkedListElementOf##TYPENAME* elem = cgLinkedListElementOf##TYPENAME##__new(this->value); \
    if (this->nextElement == NULL) \
        return elem; \
    else \
        return cgLinkedListElementOf##TYPENAME##_clone(this->nextElement); \
} \
\
cgLinkedListElementOf##TYPENAME* cgLinkedListElementOf##TYPENAME##_getNextElement(cgLinkedListElementOf##TYPENAME* this) { \
    return this->nextElement; \
} \
TYPENAME* cgLinkedListElementOf##TYPENAME##_getValue(cgLinkedListElementOf##TYPENAME* this) { \
    return this->value; \
} \
\
void cgLinkedListElementOf##TYPENAME##_setNextElement(cgLinkedListElementOf##TYPENAME* this, cgLinkedListElementOf##TYPENAME* nextElement) { \
	this->nextElement = nextElement; \
} \
\
cgLinkedListOf##TYPENAME* cgLinkedListOf##TYPENAME##__new(cgLinkedListElementOf##TYPENAME* rootElement) { \
	cgLinkedListOf##TYPENAME* this = malloc(sizeof(*this)); \
	if (this != NULL) { \
		this->rootElement = rootElement; \
		this->currentElement = rootElement; \
		this->lastElement = rootElement; \
	} else \
		cgAppState_throwException(cgAppState__getInstance(), cgException__new(Severity_error, cgExceptionID_CannotAllocate, "unable to allocate cgLinkedList for '%s'", "TYPENAME")); \
	return this; \
} \
\
cgLinkedListOf##TYPENAME* cgLinkedListOf##TYPENAME##_clone(cgLinkedListOf##TYPENAME* this) { \
    return cgLinkedListOf##TYPENAME##__new(cgLinkedListElementOf##TYPENAME##_clone(this->rootElement)); \
} \
\
void cgLinkedListOf##TYPENAME##_delete(cgLinkedListOf##TYPENAME* this) { \
    free(this); \
} \
\
void cgLinkedListOf##TYPENAME##_addElement(cgLinkedListOf##TYPENAME* this, cgLinkedListElementOf##TYPENAME* element) { \
	cgLinkedListElementOf##TYPENAME##_setNextElement(this->lastElement, element); \
	this->lastElement = element; \
} \
\
void cgLinkedListOf##TYPENAME##_insertElementAfter(cgLinkedListOf##TYPENAME* this, cgLinkedListElementOf##TYPENAME* afterElement, cgLinkedListElementOf##TYPENAME* element) { \
	if (this->lastElement == afterElement) \
		cgLinkedListOf##TYPENAME##_addElement(this, element); \
	else {\
		cgLinkedListElementOf##TYPENAME##_setNextElement(element, cgLinkedListElementOf##TYPENAME##_getNextElement(afterElement)); \
		cgLinkedListElementOf##TYPENAME##_setNextElement(afterElement, element); \
	} \
} \
\
cgLinkedListElementOf##TYPENAME* cgLinkedListOf##TYPENAME##_remove(cgLinkedListOf##TYPENAME* this, cgLinkedListElementOf##TYPENAME* element) { \
    cgLinkedListElementOf##TYPENAME* cur = this->rootElement; \
    while (cur->nextElement != NULL) { \
        if (cur->nextElement == element) {\
            cur->nextElement = element->nextElement; \
            return element; \
        } \
        cur = cur->nextElement; \
    } \
    return NULL; \
} \
\
cgLinkedListElementOf##TYPENAME* cgLinkedListOf##TYPENAME##_getRootElement(cgLinkedListOf##TYPENAME* this) { \
    return this->rootElement; \
} \
\
cgLinkedListElementOf##TYPENAME* cgLinkedListOf##TYPENAME##_getCurrentElement(cgLinkedListOf##TYPENAME* this) { \
    return this->currentElement; \
} \
\
cgLinkedListElementOf##TYPENAME* cgLinkedListOf##TYPENAME##_moveToNextElement(cgLinkedListOf##TYPENAME* this) { \
    cgLinkedListElementOf##TYPENAME* element = cgLinkedListElementOf##TYPENAME##_getNextElement(this->currentElement); \
    this->currentElement = element; \
    return element; \
} \
\
cgLinkedListElementOf##TYPENAME* cgLinkedListOf##TYPENAME##_moveToRootElement(cgLinkedListOf##TYPENAME* this) { \
    this->currentElement = this->rootElement; \
    return this->rootElement; \
} \
\
cgLinkedListElementOf##TYPENAME* cgLinkedListOf##TYPENAME##_findElement(cgLinkedListOf##TYPENAME* this, const TYPENAME* value, int (*comparingFunction)(const TYPENAME*, const TYPENAME*)) { \
    cgLinkedListElementOf##TYPENAME* cur; \
    for (cur = this->rootElement; cur != NULL; cur = cur->nextElement) { \
        if ((comparingFunction)((const TYPENAME*)cur->value, (const TYPENAME*)value) == 0) \
            return cur; \
    } \
    cgAppState_throwException(cgAppState__getInstance(), cgException__new(Severity_none, cgExceptionID_ElementNotFound, "")); \
    return NULL; \
} \
\
TYPENAME* cgLinkedListOf##TYPENAME##_findValue(cgLinkedListOf##TYPENAME* this, const TYPENAME* value, int (*comparingFunction)(const TYPENAME*, const TYPENAME*)) { \
    cgLinkedListElementOf##TYPENAME* element = cgLinkedListOf##TYPENAME##_findElement(this, value, comparingFunction); \
    if (element != NULL) \
        return cgLinkedListElementOf##TYPENAME##_getValue(element); \
    else \
        return NULL; \
} \
\

/* MAKEMAN */
/* type definition */

#define cgLinkedListElement(TYPENAME) cgLinkedListElementOf##TYPENAME
#define cgLinkedList(TYPENAME) cgLinkedListOf##TYPENAME

/* callers */

#define cgLinkedListElement__new(TYPENAME, value) cgLinkedListElementOf##TYPENAME##__new((value))
#define cgLinkedListElement_delete(TYPENAME, element) cgLinkedListElementOf##TYPENAME##_delete(element)
#define cgLinkedListElement_getValue(TYPENAME, element) cgLinkedListElementOf##TYPENAME##_getValue(element)
#define cgLinkedListElement_setNextElement(TYPENAME, element, nextElement) cgLinkedListElementOf##TYPENAME##_getNextElement((element), (nextElement))
#define cgLinkedListElement_getNextElement(TYPENAME, element) cgLinkedListElementOf##TYPENAME##_getNextElement(element)
#define cgLinkedListElement_clone(TYPENAME, element) cgLinkedListElementOf##TYPENAME##_clone((element))

#define cgLinkedList__new(TYPENAME, rootElement) cgLinkedListOf##TYPENAME##__new((rootElement))
#define cgLinkedList_delete(TYPENAME, list) cgLinkedListOf##TYPENAME##_delete((list))
#define cgLinkedList_clone(TYPENAME, list) cgLinkedListOf##TYPENAME##_clone((list))
#define cgLinkedList_addElement(TYPENAME, list, element) cgLinkedListOf##TYPENAME##_addElement((list), (element))
#define cgLinkedList_insertElementAfter(TYPENAME, list, afterElement, element) cgLinkedListOf##TYPENAME##_insertElementAfter((list), (afterElement), (element))
#define cgLinkedList_remove(TYPENAME, list, element) cgLinkedListOf##TYPENAME##_remove((list), (element))
#define cgLinkedList_getRootElement(TYPENAME, list) cgLinkedListOf##TYPENAME##_getRootElement((list))
#define cgLinkedList_getCurrentElement(TYPENAME, list) cgLinkedListOf##TYPENAME##_getCurrentElement((list))
#define cgLinkedList_moveToNextElement(TYPENAME, list) cgLinkedListOf##TYPENAME##_moveToNextElement((list))
#define cgLinkedList_moveToRootElement(TYPENAME, list) cgLinkedListOf##TYPENAME##_moveToRootElement((list))
#define cgLinkedList_start(TYPENAME, list) cgLinkedListOf##TYPENAME##_moveToRootElement((list))
#define cgLinkedList_next(TYPENAME, list) cgLinkedListOf##TYPENAME##_moveToNextElement((list))
#define cgLinkedList_findElement(TYPENAME, list, value, comparingFunction) cgLinkedListOf##TYPENAME##_findElement((list), (value), (comparingFunction))
#define cgLinkedList_findValue(TYPENAME, list, value, comparingFunction) cgLinkedListOf##TYPENAME##_findValue((list), (value), (comparingFunction))
#endif
