#ifndef _CGARRAY_ITERATOR_H
#define _CGARRAY_ITERATOR_H

#include"CGArray.h"

#define DECLARE_ARRAY_ITERATOR_TYPE(TYPENAME) \
typedef struct { \
    CGArrayOf##TYPENAME* array; \
    unsigned int currentIndex; \
} CGArrayOf##TYPENAME##Iterator; \
\

#define DECLARE_ARRAY_ITERATOR_FUNCS(TYPENAME) \
CGArrayOf##TYPENAME##Iterator* CGArrayOf##TYPENAME##Iterator__new(CGAppState* appState, CGArrayOf##TYPENAME* array); \
bool CGArrayOf##TYPENAME##Iterator_isInsideBounds(CGAppState* appState, CGArrayOf##TYPENAME##Iterator* this); \
void CGArrayOf##TYPENAME##Iterator_delete(CGAppState* appState, CGArrayOf##TYPENAME##Iterator* this); \
unsigned int CGArrayOf##TYPENAME##Iterator_getCurrentIndex(CGAppState* appState, CGArrayOf##TYPENAME##Iterator* this); \
TYPENAME* CGArrayOf##TYPENAME##Iterator_getCurrentElement(CGAppState* appState, CGArrayOf##TYPENAME##Iterator* this); \
bool CGArrayOf##TYPENAME##Iterator_moveToNextElement(CGAppState* appState, CGArrayOf##TYPENAME##Iterator* this); \
TYPENAME* CGArrayOf##TYPENAME##Iterator_getNextElement(CGAppState* appState, CGArrayOf##TYPENAME##Iterator* this); \
void CGArrayOf##TYPENAME##Iterator_reset(CGAppState* appState, CGArrayOf##TYPENAME##Iterator* this); \
\

#define DEFINE_ARRAY_ITERATOR_FUNCS(TYPENAME) \
CGArrayOf##TYPENAME##Iterator* CGArrayOf##TYPENAME##Iterator__new(CGAppState* appState, CGArrayOf##TYPENAME* array) { \
    CGArrayOf##TYPENAME##Iterator* this = malloc(sizeof(*this)); \
    if (this != NULL) { \
        this->array = array; \
        this->currentIndex = 0; \
    } else \
        CGAppState_throwException(appState, CGException__new(Severity_error, CGExceptionID_CannotAllocate, "cannot allocate CGArrayIterator")); \
    return this; \
} \
\
void CGArrayOf##TYPENAME##Iterator_delete(CGAppState* appState, CGArrayOf##TYPENAME##Iterator* this) { \
    free(this); \
} \
\
/** \
    NOTE: this works because the unsigned currentIndex will overflow and become INT_MAX if you subtract from it and it is 0 \
*/ \
bool CGArrayOf##TYPENAME##Iterator_isInsideBounds(CGAppState* appState, CGArrayOf##TYPENAME##Iterator* this) { \
    return (CGArrayOf##TYPENAME##_getSize(appState, this->array) > this->currentIndex) ? true : false; \
} \
\
unsigned int CGArrayOf##TYPENAME##Iterator_getCurrentIndex(CGAppState* appState, CGArrayOf##TYPENAME##Iterator* this) { \
    return this->currentIndex; \
} \
\
TYPENAME* CGArrayOf##TYPENAME##Iterator_getCurrentElement(CGAppState* appState, CGArrayOf##TYPENAME##Iterator* this) { \
    if (CGArrayOf##TYPENAME##Iterator_isInsideBounds(appState, this)) \
        return CGArrayOf##TYPENAME##_getValueAt(appState, this->array, this->currentIndex); \
    else \
        return NULL; \
} \
\
bool CGArrayOf##TYPENAME##Iterator_moveToNextElement(CGAppState* appState, CGArrayOf##TYPENAME##Iterator* this) { \
    this->currentIndex++; \
    if (CGArrayOf##TYPENAME##Iterator_isInsideBounds(appState, this)) \
        return true; \
    else \
        return false; \
} \
\
TYPENAME* CGArrayOf##TYPENAME##Iterator_getNextElement(CGAppState* appState, CGArrayOf##TYPENAME##Iterator* this) { \
    if (CGArrayOf##TYPENAME##Iterator_moveToNextElement(appState, this)) \
        return CGArrayOf##TYPENAME##_getValueAt(appState, this->array, this->currentIndex); \
    else { \
        CGAppState_throwException(appState, CGException__new(Severity_error, CGExceptionID_ArrayIndexOutOfBounds, "Cannot allocate CGArrayIterator")); \
        return NULL; \
    } \
} \
\
void CGArrayOf##TYPENAME##Iterator_reset(CGAppState* appState, CGArrayOf##TYPENAME##Iterator* this) { \
    this->currentIndex = 0; \
} \
\

#define DECLARE_ARRAY_ITERATOR(TYPENAME) \
    DECLARE_ARRAY_ITERATOR_TYPE(TYPENAME) \
    DECLARE_ARRAY_ITERATOR_FUNCS(TYPENAME) 

#define DEFINE_ARRAY_ITERATOR(TYPENAME) \
    DEFINE_ARRAY_ITERATOR_FUNCS(TYPENAME) 

#define INIT_ARRAY_ITERATOR(TYPENAME) \
    DECLARE_ARRAY_ITERATOR(TYPENAME) \
    DEFINE_ARRAY_ITERATOR(TYPENAME)


/* type definition */

#define CGArrayIterator(TYPENAME) CGArrayOf##TYPENAME##Iterator


/* callers */

#define CGArrayIterator__new(appState, TYPENAME, array) CGArrayOf##TYPENAME##Iterator__new((appState), (array)) 
#define CGArrayIterator_isInsideBounds(appState, TYPENAME, this) CGArrayOf##TYPENAME##Iterator_isInsideBounds((appState), (this))
#define CGArrayIterator_delete(appState, TYPENAME, this) CGArrayOf##TYPENAME##Iterator_delete((appState), (this)) 
#define CGArrayIterator_getCurrentIndex(appState, TYPENAME, this) CGArrayOf##TYPENAME##Iterator_getCurrentIndex((appState), (this)) 
#define CGArrayIterator_getCurrentElement(appState, TYPENAME, this) CGArrayOf##TYPENAME##Iterator_getCurrentElement((appState), (this)) 
#define CGArrayIterator_moveToNextElement(appState, TYPENAME, this) CGArrayOf##TYPENAME##Iterator_moveToNextElement((appState), (this)) 
#define CGArrayIterator_getNextElement(appState, TYPENAME, this) CGArrayOf##TYPENAME##Iterator_getNextElement((appState), (this)) 
#define CGArrayIterator_reset(appState, TYPENAME, this) CGArrayOf##TYPENAME##Iterator_reset((appState), (this)) 

#endif
