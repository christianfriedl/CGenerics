#ifndef _CGARRAY_ITERATOR_H
#define _CGARRAY_ITERATOR_H

/* NOMAKEMAN */

#include"CGArray.h"

#define DECLARE_ARRAY_ITERATOR_TYPE(TYPENAME) \
typedef struct { \
    CGArrayOf##TYPENAME* array; \
    unsigned int currentIndex; \
} CGArrayOf##TYPENAME##Iterator; \
\

#define DECLARE_ARRAY_ITERATOR_FUNCS(TYPENAME) \
\
    CGArrayOf##TYPENAME##Iterator* CGArrayOf##TYPENAME##Iterator__new(CGArrayOf##TYPENAME* array); \
    bool CGArrayOf##TYPENAME##Iterator_isInsideBounds(CGArrayOf##TYPENAME##Iterator* this); \
    void CGArrayOf##TYPENAME##Iterator_delete(CGArrayOf##TYPENAME##Iterator* this); \
    unsigned int CGArrayOf##TYPENAME##Iterator_getCurrentIndex(CGArrayOf##TYPENAME##Iterator* this); \
    TYPENAME* CGArrayOf##TYPENAME##Iterator_getCurrentElement(CGArrayOf##TYPENAME##Iterator* this); \
    bool CGArrayOf##TYPENAME##Iterator_moveToNextElement(CGArrayOf##TYPENAME##Iterator* this); \
    TYPENAME* CGArrayOf##TYPENAME##Iterator_getNextElement(CGArrayOf##TYPENAME##Iterator* this); \
    void CGArrayOf##TYPENAME##Iterator_reset(CGArrayOf##TYPENAME##Iterator* this); \
\

#define DEFINE_ARRAY_ITERATOR_FUNCS(TYPENAME) \
\
    CGArrayOf##TYPENAME##Iterator* CGArrayOf##TYPENAME##Iterator__new(CGArrayOf##TYPENAME* array) { \
        CGArrayOf##TYPENAME##Iterator* this = malloc(sizeof(*this)); \
        if (this != NULL) { \
            this->array = array; \
            this->currentIndex = 0; \
        } else \
            CGAppState_throwException(CGAppState__getInstance(), CGException__new(Severity_error, CGExceptionID_CannotAllocate, "cannot allocate CGArrayIterator")); \
        return this; \
    } \
    \
    void CGArrayOf##TYPENAME##Iterator_delete(CGArrayOf##TYPENAME##Iterator* this) { \
        free(this); \
    } \
    \
    /** \
        NOTE: this works because the unsigned currentIndex will overflow and become INT_MAX if you subtract from it and it is 0 \
    */ \
    bool CGArrayOf##TYPENAME##Iterator_isInsideBounds(CGArrayOf##TYPENAME##Iterator* this) { \
        return (CGArrayOf##TYPENAME##_getSize(this->array) > this->currentIndex) ? true : false; \
    } \
    \
    unsigned int CGArrayOf##TYPENAME##Iterator_getCurrentIndex(CGArrayOf##TYPENAME##Iterator* this) { \
        return this->currentIndex; \
    } \
    \
    TYPENAME* CGArrayOf##TYPENAME##Iterator_getCurrentElement(CGArrayOf##TYPENAME##Iterator* this) { \
        if (CGArrayOf##TYPENAME##Iterator_isInsideBounds(this)) \
            return CGArrayOf##TYPENAME##_getValueAt(this->array, this->currentIndex); \
        else \
            return NULL; \
    } \
    \
    bool CGArrayOf##TYPENAME##Iterator_moveToNextElement(CGArrayOf##TYPENAME##Iterator* this) { \
        this->currentIndex++; \
        if (CGArrayOf##TYPENAME##Iterator_isInsideBounds(this)) \
            return true; \
        else \
            return false; \
    } \
    \
    TYPENAME* CGArrayOf##TYPENAME##Iterator_getNextElement(CGArrayOf##TYPENAME##Iterator* this) { \
        if (CGArrayOf##TYPENAME##Iterator_moveToNextElement(this)) \
            return CGArrayOf##TYPENAME##_getValueAt(this->array, this->currentIndex); \
        else { \
            CGAppState_throwException(CGAppState__getInstance(), CGException__new(Severity_error, CGExceptionID_ArrayIndexOutOfBounds, "Cannot allocate CGArrayIterator")); \
            return NULL; \
        } \
    } \
    \
    void CGArrayOf##TYPENAME##Iterator_reset(CGArrayOf##TYPENAME##Iterator* this) { \
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

/* MAKEMAN */

#define CGArrayIterator(TYPENAME) CGArrayOf##TYPENAME##Iterator


/* callers */

#define CGArrayIterator__new(TYPENAME, array) CGArrayOf##TYPENAME##Iterator__new((array)) 
#define CGArrayIterator_isInsideBounds(TYPENAME, this) CGArrayOf##TYPENAME##Iterator_isInsideBounds((this))
#define CGArrayIterator_delete(TYPENAME, this) CGArrayOf##TYPENAME##Iterator_delete((this)) 
#define CGArrayIterator_getCurrentIndex(TYPENAME, this) CGArrayOf##TYPENAME##Iterator_getCurrentIndex((this)) 
#define CGArrayIterator_getCurrentElement(TYPENAME, this) CGArrayOf##TYPENAME##Iterator_getCurrentElement((this)) 
#define CGArrayIterator_moveToNextElement(TYPENAME, this) CGArrayOf##TYPENAME##Iterator_moveToNextElement((this)) 
#define CGArrayIterator_getNextElement(TYPENAME, this) CGArrayOf##TYPENAME##Iterator_getNextElement((this)) 
#define CGArrayIterator_reset(TYPENAME, this) CGArrayOf##TYPENAME##Iterator_reset((this)) 

#endif
