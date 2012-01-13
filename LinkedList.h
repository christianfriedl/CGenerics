#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

#include<stdlib.h>
#include<string.h>
#include"CGenerics.h"


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
    } else \
        AppState_throwException(appState, Exception__new(Severity_error, ExceptionID_CannotAllocate, "unable to allocate LinkedListElement for '%s'", "TYPENAME")); \
    return this; \
} \
\
void LinkedListElementOf##TYPENAME##_delete(AppState* appState, LinkedListElementOf##TYPENAME* this) { \
	free(this); \
} \
\
LinkedListElementOf##TYPENAME* LinkedListElementOf##TYPENAME##_getNext(AppState* appState, LinkedListElementOf##TYPENAME* this) { \
    return this->nextElement; \
} \
TYPENAME* LinkedListElementOf##TYPENAME##_getValue(AppState* appState, LinkedListElementOf##TYPENAME* this) { \
    return this->value; \
} \
void LinkedListElementOf##TYPENAME##_setNext(AppState* appState, LinkedListElementOf##TYPENAME* this, LinkedListElementOf##TYPENAME* nextElement) { \
	this->nextElement = nextElement; \
} \
\
LinkedListOf##TYPENAME* LinkedList##TYPENAME##__new(AppState* appState, LinkedListElementOf##TYPENAME* rootElement) { \
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
void LinkedListOf##TYPENAME##_add(AppState* appState, LinkedListOf##TYPENAME* this, LinkedListElementOf##TYPENAME* element) { \
	LinkedListElementOf##TYPENAME##_setNext(appState, this->currentElement, element); \
	this->lastElement = element; \
} \
\
void LinkedListOf##TYPENAME##_insertElementAfter(AppState* appState, LinkedListOf##TYPENAME* this, LinkedListElementOf##TYPENAME* afterElement, LinkedListElementOf##TYPENAME* element) { \
	if (this->lastElement == afterElement) \
		LinkedListOf##TYPENAME##_add(appState, this, element); \
	else {\
		LinkedListElementOf##TYPENAME##_setNext(appState, element, LinkedListElementOf##TYPENAME##_getNext(appState, afterElement)); \
		LinkedListElementOf##TYPENAME##_setNext(appState, afterElement, element); \
	} \
} \
\
LinkedListElementOf##TYPENAME* LinkedListOf##TYPENAME##_remove(AppState* appState, LinkedListOf##TYPENAME* this, LinkedListElementOf##TYPENAME* element) { }\
	
	

/* type definition */

#define LinkedListElement(TYPENAME) LinkedListElementOf##TYPENAME
#define LinkedList(TYPENAME) LinkedListOf##TYPENAME


/* callers */

#define LinkedListElement__new(appState, TYPENAME, value) LinkedListElementOf##TYPENAME##__new((appState), (value))
#define LinkedListElement_delete(appState, TYPENAME, element) LinkedListElementOf##TYPENAME##_delete((appState), element)
#define LinkedListElement_getValue(appState, TYPENAME, element) LinkedListElementOf##TYPENAME##_getValue((appState), element)
#define LinkedListElement_getNext(appState, TYPENAME, element) LinkedListElementOf##TYPENAME##_getNext((appState), element)


#endif
