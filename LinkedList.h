#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

#include<stdlib.h>
#include<string.h>
#include"CGenerics.h"
#include"Exception.h"


/* everything below this line is type-specific! */

/* declarations */

/** 
    This will init the LinkedList for one typename
    NOTE: TYPENAME is a valid identifier; if you plan for a, say, LinkedList<int*>, then do a typedef int* intPtr or the like...
*/

#define INIT_LINKEDLIST(TYPENAME) \
struct LinkedListElementOf##TYPENAME##_struct { \
    TYPENAME* value; \
    struct LinkedListElementOf##TYPENAME##_struct* nextElement; \
}; \
typedef struct LinkedListElementOf##TYPENAME##_struct LinkedListElementOf##TYPENAME; \
 \
typedef struct { \
    LinkedListElementOf##TYPENAME* rootElement; \
    LinkedListElementOf##TYPENAME* currentElement; \
    LinkedListElementOf##TYPENAME* lastElement; \
} LinkedListOf##TYPENAME; \
\
LinkedListElementOf##TYPENAME* LinkedListElementOf##TYPENAME##__new(AppState* appState, TYPENAME* value) { \
    LinkedListElementOf##TYPENAME* this = malloc(sizeof(*this)); \
    if (this != NULL) { \
        this->value = value; \
        this->nextElement = NULL; \
    } else \
        AppState_throwException(appState, Exception__new(Severity_error, ExceptionID_CannotAllocate, "unable to allocate LinkedListElement for '%s'", "TYPENAME")); \
    return this; \
} \
\
void LinkedListElementOf##TYPENAME##_delete(AppState* appState, LinkedListElementOf##TYPENAME* this) { \
	free(this); \
} \
\
LinkedListElementOf##TYPENAME* LinkedListElementOf##TYPENAME##_getNextElement(AppState* appState, LinkedListElementOf##TYPENAME* this) { \
    return this->nextElement; \
} \
TYPENAME* LinkedListElementOf##TYPENAME##_getValue(AppState* appState, LinkedListElementOf##TYPENAME* this) { \
    return this->value; \
} \
\
void LinkedListElementOf##TYPENAME##_setNextElement(AppState* appState, LinkedListElementOf##TYPENAME* this, LinkedListElementOf##TYPENAME* nextElement) { \
	this->nextElement = nextElement; \
} \
\
LinkedListOf##TYPENAME* LinkedListOf##TYPENAME##__new(AppState* appState, LinkedListElementOf##TYPENAME* rootElement) { \
	LinkedListOf##TYPENAME* this = malloc(sizeof(*this)); \
	if (this != NULL) { \
		this->rootElement = rootElement; \
		this->currentElement = rootElement; \
		this->lastElement = rootElement; \
	} else \
		AppState_throwException(appState, Exception__new(Severity_error, ExceptionID_CannotAllocate, "unable to allocate LinkedList for '%s'", "TYPENAME")); \
	return this; \
} \
\
void LinkedListOf##TYPENAME##_delete(AppState* appState, LinkedListOf##TYPENAME* this) { \
    free(this); \
} \
\
void LinkedListOf##TYPENAME##_addElement(AppState* appState, LinkedListOf##TYPENAME* this, LinkedListElementOf##TYPENAME* element) { \
	LinkedListElementOf##TYPENAME##_setNextElement(appState, this->lastElement, element); \
	this->lastElement = element; \
} \
\
void LinkedListOf##TYPENAME##_insertElementAfter(AppState* appState, LinkedListOf##TYPENAME* this, LinkedListElementOf##TYPENAME* afterElement, LinkedListElementOf##TYPENAME* element) { \
	if (this->lastElement == afterElement) \
		LinkedListOf##TYPENAME##_addElement(appState, this, element); \
	else {\
		LinkedListElementOf##TYPENAME##_setNextElement(appState, element, LinkedListElementOf##TYPENAME##_getNextElement(appState, afterElement)); \
		LinkedListElementOf##TYPENAME##_setNextElement(appState, afterElement, element); \
	} \
} \
\
LinkedListElementOf##TYPENAME* LinkedListOf##TYPENAME##_remove(AppState* appState, LinkedListOf##TYPENAME* this, LinkedListElementOf##TYPENAME* element) { \
    LinkedListElementOf##TYPENAME* cur = this->rootElement; \
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
LinkedListElementOf##TYPENAME* LinkedListOf##TYPENAME##_getRootElement(AppState* appState, LinkedListOf##TYPENAME* this) { \
    return this->rootElement; \
} \
\
LinkedListElementOf##TYPENAME* LinkedListOf##TYPENAME##_getCurrentElement(AppState* appState, LinkedListOf##TYPENAME* this) { \
    return this->currentElement; \
} \
\
LinkedListElementOf##TYPENAME* LinkedListOf##TYPENAME##_moveToNextElement(AppState* appState, LinkedListOf##TYPENAME* this) { \
    LinkedListElementOf##TYPENAME* element = LinkedListElementOf##TYPENAME##_getNextElement(appState, this->currentElement); \
    this->currentElement = element; \
    return element; \
} \
\
LinkedListElementOf##TYPENAME* LinkedListOf##TYPENAME##_moveToRootElement(AppState* appState, LinkedListOf##TYPENAME* this) { \
    this->currentElement = this->rootElement; \
    return this->rootElement; \
} \
\
LinkedListElementOf##TYPENAME* LinkedListOf##TYPENAME##_findElement(AppState* appState, LinkedListOf##TYPENAME* this, const TYPENAME* value, int (*comparingFunction)(AppState*, const TYPENAME*, const TYPENAME*)) { \
    LinkedListElementOf##TYPENAME* cur; \
    for (cur = this->rootElement; cur != NULL; cur = cur->nextElement) { \
        if ((comparingFunction)(appState, (const TYPENAME*)cur->value, (const TYPENAME*)value) == 0) \
            return cur; \
    } \
    AppState_throwException(appState, Exception__new(Severity_none, ExceptionID_ElementNotFound, "")); \
    return NULL; \
} \
\
TYPENAME* LinkedListOf##TYPENAME##_findValue(AppState* appState, LinkedListOf##TYPENAME* this, const TYPENAME* value, int (*comparingFunction)(AppState*, const TYPENAME*, const TYPENAME*)) { \
    LinkedListElementOf##TYPENAME* element = LinkedListOf##TYPENAME##_findElement(appState, this, value, comparingFunction); \
    if (element != NULL) \
        return LinkedListElementOf##TYPENAME##_getValue(appState, element); \
    else \
        return NULL; \
} \
\

/* type definition */

#define LinkedListElement(TYPENAME) LinkedListElementOf##TYPENAME
#define LinkedList(TYPENAME) LinkedListOf##TYPENAME


/* callers */

#define LinkedListElement__new(appState, TYPENAME, value) LinkedListElementOf##TYPENAME##__new((appState), (value))
#define LinkedListElement_delete(appState, TYPENAME, element) LinkedListElementOf##TYPENAME##_delete((appState), element)
#define LinkedListElement_getValue(appState, TYPENAME, element) LinkedListElementOf##TYPENAME##_getValue((appState), element)
#define LinkedListElement_setNextElement(appState, TYPENAME, element, nextElement) LinkedListElementOf##TYPENAME##_getNextElement((appState), (element), (nextElement))
#define LinkedListElement_getNextElement(appState, TYPENAME, element) LinkedListElementOf##TYPENAME##_getNextElement((appState), element)

#define LinkedList__new(appState, TYPENAME, rootElement) LinkedListOf##TYPENAME##__new((appState), (rootElement))
#define LinkedList_delete(appState, TYPENAME, list) LinkedListOf##TYPENAME##_delete((appState), (list))
#define LinkedList_addElement(appState, TYPENAME, list, element) LinkedListOf##TYPENAME##_addElement((appState), (list), (element))
#define LinkedList_insertElementAfter(appState, TYPENAME, list, afterElement, element) LinkedListOf##TYPENAME##_insertElementAfter((appState), (list), (afterElement), (element))
#define LinkedList_remove(appState, TYPENAME, list, element) LinkedListOf##TYPENAME##_remove((appState), (list), (element))
#define LinkedList_getRootElement(appState, TYPENAME, list) LinkedListOf##TYPENAME##_getRootElement((appState), (list))
#define LinkedList_getCurrentElement(appState, TYPENAME, list) LinkedListOf##TYPENAME##_getCurrentElement((appState), (list))
#define LinkedList_moveToNextElement(appState, TYPENAME, list) LinkedListOf##TYPENAME##_moveToNextElement((appState), (list))
#define LinkedList_moveToRootElement(appState, TYPENAME, list) LinkedListOf##TYPENAME##_moveToRootElement((appState), (list))
#define LinkedList_start(appState, TYPENAME, list) LinkedListOf##TYPENAME##_moveToRootElement((appState), (list))
#define LinkedList_next(appState, TYPENAME, list) LinkedListOf##TYPENAME##_moveToNextElement((appState), (list))
#define LinkedList_findElement(appState, TYPENAME, list, value, comparingFunction) LinkedListOf##TYPENAME##_findElement((appState), (list), (value), (comparingFunction))
#define LinkedList_findValue(appState, TYPENAME, list, value, comparingFunction) LinkedListOf##TYPENAME##_findValue((appState), (list), (value), (comparingFunction))

#endif
