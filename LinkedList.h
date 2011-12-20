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
    ArrayOf##TYPENAME* this = malloc(sizeof(*this)); \
    if (this != NULL) { \
        this->value = value; \
    } else \
        AppState_throwException(appState, Exception__new(Severity_error, ExceptionID_CannotAllocate, "unable to allocate LinkedListElement for '%s'", "TYPENAME")); \
    return this; \
} \
\
void LinkedListElementOf##TYPENAME_delete(AppState* appState, LinkedListElementOf##TYPENAME* this) { \
	TYPENAME_delete(this->value); \
	free(this); \
} \
\
void LinkedListElementOf##TYPENAME##_setNext(AppState* appState, LinkedListElementOf##TYPENAME* this, LinkedListElementOf##TYPENAME* nextElement) { \
	this->nextElement = nextElement; \
} \
\
LinkedListElementOf##TYPENAME* LinkedListElementOf##TYPENAME##_getNext(AppState* appState, LinkedListElementOf##TYPENAME* this) { \
	return this->nextElement; \
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
		LinkedListElementOf##TYPENAME##_add(appState, this, element); \
	else {\
		LinkedListElementOf##TYPENAME##_setNext(appState, element, LinkedListElementOf##TYPENAME##_getNext(appState, afterElement)); \
		LinkedListElementOf##TYPENAME##_setNext(appState, afterElement, element); \
	} \
} \
\
LinkedListElementOf##TYPENAME* LinkedListOf##TYPENAME##_remove(AppState* appState, LinkedListOf##TYPENAME* this, LinkedListElementOf##TYPENAME* element) { \
	
	

/* type definition */

#define Array(TYPENAME) ArrayOf##TYPENAME


/* callers */

#define Array__new(TYPENAME, initialCapacity) ArrayOf##TYPENAME##__new((initialCapacity))
#define Array_delete(TYPENAME, array) ArrayOf##TYPENAME##_delete((array))
#define Array_add(TYPENAME, array, value) ArrayOf##TYPENAME##_add((array), (value))
#define Array_getValueAt(TYPENAME, array, at) ArrayOf##TYPENAME##_getValueAt((array), (at))
#define Array_push Array_add
#define Array_pop(TYPENAME, array) ArrayOf##TYPENAME##_pop((array))
#define Array_getCapacity(TYPENAME, array) ArrayOf##TYPENAME##_getCapacity((array))
#define Array_getSize(TYPENAME, array) ArrayOf##TYPENAME##_getSize((array))
#define Array_shift(TYPENAME, array) ArrayOf##TYPENAME##_shift((array))
#define Array_unshift(TYPENAME, array, value) ArrayOf##TYPENAME##_unshift((array), (value))
#define Array_insertValueAt(TYPENAME, array, value, at) ArrayOf##TYPENAME##_insertValueAt((array), (value), (at))
#define Array_removeValueAt(TYPENAME, array, at) ArrayOf##TYPENAME##_removeValueAt((array), (at))


