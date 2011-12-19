#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

#include<stdlib.h>
#include<string.h>

#ifndef min
    #define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

#ifndef max
    #define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif


/* everything below this line is type-specific! */

/* declarations */

/** 
    This will init the LinkedList for one typename
    NOTE: TYPENAME is a valid identifier; if you plan for a, say, LinkedList<int*>, then do a typedef int* intPtr or the like...
*/

#define INIT_LINKEDLIST(TYPENAME) \
struct LinkedListElementOf##TYPENAME##_struct { \
    TYPENAME value; \
    struct LinkedListElementOf##TYPENAME##_struct* next; \
}; \
typedef struct LinkedListElementOf##TYPENAME##_struct LinkedListElementOf##TYPENAME; \
 \
typedef struct { \
    LinkedListElementOf##TYPENAME* rootElement; \
    LinkedListElementOf##TYPENAME* currentElement; \
} LinkedListOf##TYPENAME; \
\
LinkedListElementOf##TYPENAME* LinkedListElementOf##TYPENAME##__new(AppState* appState, const TYPENAME value) { \
    ArrayOf##TYPENAME* this = malloc(sizeof(*this)); \
    if (this != NULL) { \
        this->value = value; \
    } else \
        AppState_throwException(appState, Exception__new(Severity_error, ExceptionID_CannotAllocate, "unable to allocate LinkedList for %s", "TYPENAME")); \
    return this; \
} \
\
void LinkedListElementOf##TYPENAME_delete(AppState* appState, LinkedListElementOf##TYPENAME* this)

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


