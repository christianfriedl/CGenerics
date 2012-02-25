#ifndef _CGLINKEDLIST_H
#define _CGLINKEDLIST_H

#include<stdlib.h>
#include<string.h>
#include"CGenerics.h"
#include"CGException.h"


/* everything below this line is type-specific! */

/* declarations */

/** 
    This will init the CGLinkedList for one typename
    NOTE: TYPENAME is a valid identifier; if you plan for a, say, CGLinkedList<int*>, then do a typedef int* intPtr or the like...
*/

#define INIT_LINKEDLIST(TYPENAME) \
struct CGLinkedListElementOf##TYPENAME##_struct { \
    TYPENAME* value; \
    struct CGLinkedListElementOf##TYPENAME##_struct* nextElement; \
}; \
typedef struct CGLinkedListElementOf##TYPENAME##_struct CGLinkedListElementOf##TYPENAME; \
 \
typedef struct { \
    CGLinkedListElementOf##TYPENAME* rootElement; \
    CGLinkedListElementOf##TYPENAME* currentElement; \
    CGLinkedListElementOf##TYPENAME* lastElement; \
} CGLinkedListOf##TYPENAME; \
\
CGLinkedListElementOf##TYPENAME* CGLinkedListElementOf##TYPENAME##__new(TYPENAME* value) { \
    CGLinkedListElementOf##TYPENAME* this = malloc(sizeof(*this)); \
    if (this != NULL) { \
        this->value = value; \
        this->nextElement = NULL; \
    } else \
        CGAppState_throwException(CGAppState__getInstance(), CGException__new(Severity_error, CGExceptionID_CannotAllocate, "unable to allocate CGLinkedListElement for '%s'", "TYPENAME")); \
    return this; \
} \
\
void CGLinkedListElementOf##TYPENAME##_delete(CGLinkedListElementOf##TYPENAME* this) { \
	free(this); \
} \
\
CGLinkedListElementOf##TYPENAME* CGLinkedListElementOf##TYPENAME##_getNextElement(CGLinkedListElementOf##TYPENAME* this) { \
    return this->nextElement; \
} \
TYPENAME* CGLinkedListElementOf##TYPENAME##_getValue(CGLinkedListElementOf##TYPENAME* this) { \
    return this->value; \
} \
\
void CGLinkedListElementOf##TYPENAME##_setNextElement(CGLinkedListElementOf##TYPENAME* this, CGLinkedListElementOf##TYPENAME* nextElement) { \
	this->nextElement = nextElement; \
} \
\
CGLinkedListOf##TYPENAME* CGLinkedListOf##TYPENAME##__new(CGLinkedListElementOf##TYPENAME* rootElement) { \
	CGLinkedListOf##TYPENAME* this = malloc(sizeof(*this)); \
	if (this != NULL) { \
		this->rootElement = rootElement; \
		this->currentElement = rootElement; \
		this->lastElement = rootElement; \
	} else \
		CGAppState_throwException(CGAppState__getInstance(), CGException__new(Severity_error, CGExceptionID_CannotAllocate, "unable to allocate CGLinkedList for '%s'", "TYPENAME")); \
	return this; \
} \
\
void CGLinkedListOf##TYPENAME##_delete(CGLinkedListOf##TYPENAME* this) { \
    free(this); \
} \
\
void CGLinkedListOf##TYPENAME##_addElement(CGLinkedListOf##TYPENAME* this, CGLinkedListElementOf##TYPENAME* element) { \
	CGLinkedListElementOf##TYPENAME##_setNextElement(this->lastElement, element); \
	this->lastElement = element; \
} \
\
void CGLinkedListOf##TYPENAME##_insertElementAfter(CGLinkedListOf##TYPENAME* this, CGLinkedListElementOf##TYPENAME* afterElement, CGLinkedListElementOf##TYPENAME* element) { \
	if (this->lastElement == afterElement) \
		CGLinkedListOf##TYPENAME##_addElement(this, element); \
	else {\
		CGLinkedListElementOf##TYPENAME##_setNextElement(element, CGLinkedListElementOf##TYPENAME##_getNextElement(afterElement)); \
		CGLinkedListElementOf##TYPENAME##_setNextElement(afterElement, element); \
	} \
} \
\
CGLinkedListElementOf##TYPENAME* CGLinkedListOf##TYPENAME##_remove(CGLinkedListOf##TYPENAME* this, CGLinkedListElementOf##TYPENAME* element) { \
    CGLinkedListElementOf##TYPENAME* cur = this->rootElement; \
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
CGLinkedListElementOf##TYPENAME* CGLinkedListOf##TYPENAME##_getRootElement(CGLinkedListOf##TYPENAME* this) { \
    return this->rootElement; \
} \
\
CGLinkedListElementOf##TYPENAME* CGLinkedListOf##TYPENAME##_getCurrentElement(CGLinkedListOf##TYPENAME* this) { \
    return this->currentElement; \
} \
\
CGLinkedListElementOf##TYPENAME* CGLinkedListOf##TYPENAME##_moveToNextElement(CGLinkedListOf##TYPENAME* this) { \
    CGLinkedListElementOf##TYPENAME* element = CGLinkedListElementOf##TYPENAME##_getNextElement(this->currentElement); \
    this->currentElement = element; \
    return element; \
} \
\
CGLinkedListElementOf##TYPENAME* CGLinkedListOf##TYPENAME##_moveToRootElement(CGLinkedListOf##TYPENAME* this) { \
    this->currentElement = this->rootElement; \
    return this->rootElement; \
} \
\
CGLinkedListElementOf##TYPENAME* CGLinkedListOf##TYPENAME##_findElement(CGLinkedListOf##TYPENAME* this, const TYPENAME* value, int (*comparingFunction)(const TYPENAME*, const TYPENAME*)) { \
    CGLinkedListElementOf##TYPENAME* cur; \
    for (cur = this->rootElement; cur != NULL; cur = cur->nextElement) { \
        if ((comparingFunction)((const TYPENAME*)cur->value, (const TYPENAME*)value) == 0) \
            return cur; \
    } \
    CGAppState_throwException(CGAppState__getInstance(), CGException__new(Severity_none, CGExceptionID_ElementNotFound, "")); \
    return NULL; \
} \
\
TYPENAME* CGLinkedListOf##TYPENAME##_findValue(CGLinkedListOf##TYPENAME* this, const TYPENAME* value, int (*comparingFunction)(const TYPENAME*, const TYPENAME*)) { \
    CGLinkedListElementOf##TYPENAME* element = CGLinkedListOf##TYPENAME##_findElement(this, value, comparingFunction); \
    if (element != NULL) \
        return CGLinkedListElementOf##TYPENAME##_getValue(element); \
    else \
        return NULL; \
} \
\

/* type definition */

#define CGLinkedListElement(TYPENAME) CGLinkedListElementOf##TYPENAME
#define CGLinkedList(TYPENAME) CGLinkedListOf##TYPENAME


/* callers */

#define CGLinkedListElement__new(TYPENAME, value) CGLinkedListElementOf##TYPENAME##__new((value))
#define CGLinkedListElement_delete(TYPENAME, element) CGLinkedListElementOf##TYPENAME##_delete(element)
#define CGLinkedListElement_getValue(TYPENAME, element) CGLinkedListElementOf##TYPENAME##_getValue(element)
#define CGLinkedListElement_setNextElement(TYPENAME, element, nextElement) CGLinkedListElementOf##TYPENAME##_getNextElement((element), (nextElement))
#define CGLinkedListElement_getNextElement(TYPENAME, element) CGLinkedListElementOf##TYPENAME##_getNextElement(element)

#define CGLinkedList__new(TYPENAME, rootElement) CGLinkedListOf##TYPENAME##__new((rootElement))
#define CGLinkedList_delete(TYPENAME, list) CGLinkedListOf##TYPENAME##_delete((list))
#define CGLinkedList_addElement(TYPENAME, list, element) CGLinkedListOf##TYPENAME##_addElement((list), (element))
#define CGLinkedList_insertElementAfter(TYPENAME, list, afterElement, element) CGLinkedListOf##TYPENAME##_insertElementAfter((list), (afterElement), (element))
#define CGLinkedList_remove(TYPENAME, list, element) CGLinkedListOf##TYPENAME##_remove((list), (element))
#define CGLinkedList_getRootElement(TYPENAME, list) CGLinkedListOf##TYPENAME##_getRootElement((list))
#define CGLinkedList_getCurrentElement(TYPENAME, list) CGLinkedListOf##TYPENAME##_getCurrentElement((list))
#define CGLinkedList_moveToNextElement(TYPENAME, list) CGLinkedListOf##TYPENAME##_moveToNextElement((list))
#define CGLinkedList_moveToRootElement(TYPENAME, list) CGLinkedListOf##TYPENAME##_moveToRootElement((list))
#define CGLinkedList_start(TYPENAME, list) CGLinkedListOf##TYPENAME##_moveToRootElement((list))
#define CGLinkedList_next(TYPENAME, list) CGLinkedListOf##TYPENAME##_moveToNextElement((list))
#define CGLinkedList_findElement(TYPENAME, list, value, comparingFunction) CGLinkedListOf##TYPENAME##_findElement((list), (value), (comparingFunction))
#define CGLinkedList_findValue(TYPENAME, list, value, comparingFunction) CGLinkedListOf##TYPENAME##_findValue((list), (value), (comparingFunction))

#endif
