#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

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
CGLinkedListElementOf##TYPENAME* CGLinkedListElementOf##TYPENAME##__new(CGAppState* appState, TYPENAME* value) { \
    CGLinkedListElementOf##TYPENAME* this = malloc(sizeof(*this)); \
    if (this != NULL) { \
        this->value = value; \
        this->nextElement = NULL; \
    } else \
        CGAppState_throwException(appState, CGException__new(Severity_error, CGExceptionID_CannotAllocate, "unable to allocate CGLinkedListElement for '%s'", "TYPENAME")); \
    return this; \
} \
\
void CGLinkedListElementOf##TYPENAME##_delete(CGAppState* appState, CGLinkedListElementOf##TYPENAME* this) { \
	free(this); \
} \
\
CGLinkedListElementOf##TYPENAME* CGLinkedListElementOf##TYPENAME##_getNextElement(CGAppState* appState, CGLinkedListElementOf##TYPENAME* this) { \
    return this->nextElement; \
} \
TYPENAME* CGLinkedListElementOf##TYPENAME##_getValue(CGAppState* appState, CGLinkedListElementOf##TYPENAME* this) { \
    return this->value; \
} \
\
void CGLinkedListElementOf##TYPENAME##_setNextElement(CGAppState* appState, CGLinkedListElementOf##TYPENAME* this, CGLinkedListElementOf##TYPENAME* nextElement) { \
	this->nextElement = nextElement; \
} \
\
CGLinkedListOf##TYPENAME* CGLinkedListOf##TYPENAME##__new(CGAppState* appState, CGLinkedListElementOf##TYPENAME* rootElement) { \
	CGLinkedListOf##TYPENAME* this = malloc(sizeof(*this)); \
	if (this != NULL) { \
		this->rootElement = rootElement; \
		this->currentElement = rootElement; \
		this->lastElement = rootElement; \
	} else \
		CGAppState_throwException(appState, CGException__new(Severity_error, CGExceptionID_CannotAllocate, "unable to allocate CGLinkedList for '%s'", "TYPENAME")); \
	return this; \
} \
\
void CGLinkedListOf##TYPENAME##_delete(CGAppState* appState, CGLinkedListOf##TYPENAME* this) { \
    free(this); \
} \
\
void CGLinkedListOf##TYPENAME##_addElement(CGAppState* appState, CGLinkedListOf##TYPENAME* this, CGLinkedListElementOf##TYPENAME* element) { \
	CGLinkedListElementOf##TYPENAME##_setNextElement(appState, this->lastElement, element); \
	this->lastElement = element; \
} \
\
void CGLinkedListOf##TYPENAME##_insertElementAfter(CGAppState* appState, CGLinkedListOf##TYPENAME* this, CGLinkedListElementOf##TYPENAME* afterElement, CGLinkedListElementOf##TYPENAME* element) { \
	if (this->lastElement == afterElement) \
		CGLinkedListOf##TYPENAME##_addElement(appState, this, element); \
	else {\
		CGLinkedListElementOf##TYPENAME##_setNextElement(appState, element, CGLinkedListElementOf##TYPENAME##_getNextElement(appState, afterElement)); \
		CGLinkedListElementOf##TYPENAME##_setNextElement(appState, afterElement, element); \
	} \
} \
\
CGLinkedListElementOf##TYPENAME* CGLinkedListOf##TYPENAME##_remove(CGAppState* appState, CGLinkedListOf##TYPENAME* this, CGLinkedListElementOf##TYPENAME* element) { \
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
CGLinkedListElementOf##TYPENAME* CGLinkedListOf##TYPENAME##_getRootElement(CGAppState* appState, CGLinkedListOf##TYPENAME* this) { \
    return this->rootElement; \
} \
\
CGLinkedListElementOf##TYPENAME* CGLinkedListOf##TYPENAME##_getCurrentElement(CGAppState* appState, CGLinkedListOf##TYPENAME* this) { \
    return this->currentElement; \
} \
\
CGLinkedListElementOf##TYPENAME* CGLinkedListOf##TYPENAME##_moveToNextElement(CGAppState* appState, CGLinkedListOf##TYPENAME* this) { \
    CGLinkedListElementOf##TYPENAME* element = CGLinkedListElementOf##TYPENAME##_getNextElement(appState, this->currentElement); \
    this->currentElement = element; \
    return element; \
} \
\
CGLinkedListElementOf##TYPENAME* CGLinkedListOf##TYPENAME##_moveToRootElement(CGAppState* appState, CGLinkedListOf##TYPENAME* this) { \
    this->currentElement = this->rootElement; \
    return this->rootElement; \
} \
\
CGLinkedListElementOf##TYPENAME* CGLinkedListOf##TYPENAME##_findElement(CGAppState* appState, CGLinkedListOf##TYPENAME* this, const TYPENAME* value, int (*comparingFunction)(CGAppState*, const TYPENAME*, const TYPENAME*)) { \
    CGLinkedListElementOf##TYPENAME* cur; \
    for (cur = this->rootElement; cur != NULL; cur = cur->nextElement) { \
        if ((comparingFunction)(appState, (const TYPENAME*)cur->value, (const TYPENAME*)value) == 0) \
            return cur; \
    } \
    CGAppState_throwException(appState, CGException__new(Severity_none, CGExceptionID_ElementNotFound, "")); \
    return NULL; \
} \
\
TYPENAME* CGLinkedListOf##TYPENAME##_findValue(CGAppState* appState, CGLinkedListOf##TYPENAME* this, const TYPENAME* value, int (*comparingFunction)(CGAppState*, const TYPENAME*, const TYPENAME*)) { \
    CGLinkedListElementOf##TYPENAME* element = CGLinkedListOf##TYPENAME##_findElement(appState, this, value, comparingFunction); \
    if (element != NULL) \
        return CGLinkedListElementOf##TYPENAME##_getValue(appState, element); \
    else \
        return NULL; \
} \
\

/* type definition */

#define CGLinkedListElement(TYPENAME) CGLinkedListElementOf##TYPENAME
#define CGLinkedList(TYPENAME) CGLinkedListOf##TYPENAME


/* callers */

#define CGLinkedListElement__new(appState, TYPENAME, value) CGLinkedListElementOf##TYPENAME##__new((appState), (value))
#define CGLinkedListElement_delete(appState, TYPENAME, element) CGLinkedListElementOf##TYPENAME##_delete((appState), element)
#define CGLinkedListElement_getValue(appState, TYPENAME, element) CGLinkedListElementOf##TYPENAME##_getValue((appState), element)
#define CGLinkedListElement_setNextElement(appState, TYPENAME, element, nextElement) CGLinkedListElementOf##TYPENAME##_getNextElement((appState), (element), (nextElement))
#define CGLinkedListElement_getNextElement(appState, TYPENAME, element) CGLinkedListElementOf##TYPENAME##_getNextElement((appState), element)

#define CGLinkedList__new(appState, TYPENAME, rootElement) CGLinkedListOf##TYPENAME##__new((appState), (rootElement))
#define CGLinkedList_delete(appState, TYPENAME, list) CGLinkedListOf##TYPENAME##_delete((appState), (list))
#define CGLinkedList_addElement(appState, TYPENAME, list, element) CGLinkedListOf##TYPENAME##_addElement((appState), (list), (element))
#define CGLinkedList_insertElementAfter(appState, TYPENAME, list, afterElement, element) CGLinkedListOf##TYPENAME##_insertElementAfter((appState), (list), (afterElement), (element))
#define CGLinkedList_remove(appState, TYPENAME, list, element) CGLinkedListOf##TYPENAME##_remove((appState), (list), (element))
#define CGLinkedList_getRootElement(appState, TYPENAME, list) CGLinkedListOf##TYPENAME##_getRootElement((appState), (list))
#define CGLinkedList_getCurrentElement(appState, TYPENAME, list) CGLinkedListOf##TYPENAME##_getCurrentElement((appState), (list))
#define CGLinkedList_moveToNextElement(appState, TYPENAME, list) CGLinkedListOf##TYPENAME##_moveToNextElement((appState), (list))
#define CGLinkedList_moveToRootElement(appState, TYPENAME, list) CGLinkedListOf##TYPENAME##_moveToRootElement((appState), (list))
#define CGLinkedList_start(appState, TYPENAME, list) CGLinkedListOf##TYPENAME##_moveToRootElement((appState), (list))
#define CGLinkedList_next(appState, TYPENAME, list) CGLinkedListOf##TYPENAME##_moveToNextElement((appState), (list))
#define CGLinkedList_findElement(appState, TYPENAME, list, value, comparingFunction) CGLinkedListOf##TYPENAME##_findElement((appState), (list), (value), (comparingFunction))
#define CGLinkedList_findValue(appState, TYPENAME, list, value, comparingFunction) CGLinkedListOf##TYPENAME##_findValue((appState), (list), (value), (comparingFunction))

#endif
