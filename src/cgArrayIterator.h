#ifndef _CGARRAY_ITERATOR_H
#define _CGARRAY_ITERATOR_H

/* NOMAKEMAN */

#include"cgArray.h"

#define DECLARE_ARRAY_ITERATOR_TYPE(TYPENAME) \
typedef struct { \
    cgArrayOf##TYPENAME* array; \
    unsigned int currentIndex; \
    bool hasStarted; \
} cgArrayOf##TYPENAME##Iterator; \
\

#define DECLARE_ARRAY_ITERATOR_FUNCS(TYPENAME) \
\
    cgArrayOf##TYPENAME##Iterator* cgArrayOf##TYPENAME##Iterator__new(cgArrayOf##TYPENAME* array); \
    bool cgArrayOf##TYPENAME##Iterator_isInsideBounds(cgArrayOf##TYPENAME##Iterator* this); \
    void cgArrayOf##TYPENAME##Iterator_delete(cgArrayOf##TYPENAME##Iterator* this); \
    unsigned int cgArrayOf##TYPENAME##Iterator_getCurrentIndex(cgArrayOf##TYPENAME##Iterator* this); \
    TYPENAME* cgArrayOf##TYPENAME##Iterator_getCurrentElement(cgArrayOf##TYPENAME##Iterator* this); \
    bool cgArrayOf##TYPENAME##Iterator_moveToNextElement(cgArrayOf##TYPENAME##Iterator* this); \
    TYPENAME* cgArrayOf##TYPENAME##Iterator_getNextElement(cgArrayOf##TYPENAME##Iterator* this); \
    TYPENAME* cgArrayOf##TYPENAME##Iterator_fetch(cgArrayOf##TYPENAME##Iterator* this); \
    void cgArrayOf##TYPENAME##Iterator_unFetch(cgArrayOf##TYPENAME##Iterator* this); \
    void cgArrayOf##TYPENAME##Iterator_reset(cgArrayOf##TYPENAME##Iterator* this); \
    cgArrayOf##TYPENAME##Iterator* cgArrayOf##TYPENAME##Iterator_clone(cgArrayOf##TYPENAME##Iterator* this); \
    bool cgArrayOf##TYPENAME##Iterator_getHasStarted(cgArrayOf##TYPENAME##Iterator* this); \
\

#define DEFINE_ARRAY_ITERATOR_FUNCS(TYPENAME) \
\
    cgArrayOf##TYPENAME##Iterator* cgArrayOf##TYPENAME##Iterator__new(cgArrayOf##TYPENAME* array) { \
        cgArrayOf##TYPENAME##Iterator* this = malloc(sizeof(*this)); \
        if (this != NULL) { \
            this->array = array; \
            this->currentIndex = 0; \
            this->hasStarted = false; \
        } else {\
            cgAppState_throwException(cgAppState__getInstance(), cgException__new(Severity_error, cgExceptionID_CannotAllocate, "cannot allocate cgArrayIterator")); \
        } \
        return this; \
    } \
    \
    void cgArrayOf##TYPENAME##Iterator_delete(cgArrayOf##TYPENAME##Iterator* this) { \
        free(this); \
    } \
    \
    /** \
        NOTE: this works because the unsigned currentIndex will overflow and become INT_MAX if you subtract from it and it is 0 \
    */ \
    bool cgArrayOf##TYPENAME##Iterator_isInsideBounds(cgArrayOf##TYPENAME##Iterator* this) { \
        return (cgArrayOf##TYPENAME##_getSize(this->array) > this->currentIndex) ? true : false; \
    } \
    \
    unsigned int cgArrayOf##TYPENAME##Iterator_getCurrentIndex(cgArrayOf##TYPENAME##Iterator* this) { \
        return this->currentIndex; \
    } \
    \
    TYPENAME* cgArrayOf##TYPENAME##Iterator_getCurrentElement(cgArrayOf##TYPENAME##Iterator* this) { \
        if (cgArrayOf##TYPENAME##Iterator_isInsideBounds(this)) \
            return cgArrayOf##TYPENAME##_getValueAt(this->array, this->currentIndex); \
        else \
            return NULL; \
    } \
    \
    bool cgArrayOf##TYPENAME##Iterator_moveToNextElement(cgArrayOf##TYPENAME##Iterator* this) { \
        this->hasStarted = true; \
        ++this->currentIndex; \
        if (cgArrayOf##TYPENAME##Iterator_isInsideBounds(this)) \
            return true; \
        else \
            return false; \
    } \
    \
    bool cgArrayOf##TYPENAME##Iterator_moveToIndex(cgArrayOf##TYPENAME##Iterator* this, unsigned int index) { \
        this->hasStarted = true; \
        this->currentIndex = index; \
        if (cgArrayOf##TYPENAME##Iterator_isInsideBounds(this)) \
            return true; \
        else \
            return false; \
    } \
    \
    TYPENAME* cgArrayOf##TYPENAME##Iterator_getNextElement(cgArrayOf##TYPENAME##Iterator* this) { \
        this->hasStarted = true; \
        if (cgArrayOf##TYPENAME##Iterator_moveToNextElement(this)) \
            return cgArrayOf##TYPENAME##_getValueAt(this->array, this->currentIndex); \
        else { \
            cgAppState_throwException(cgAppState__getInstance(), cgException__new(Severity_none, cgExceptionID_ArrayIndexOutOfBounds, "Cannot move to next array element (current index: %u", this->currentIndex)); \
            return NULL; \
        } \
    } \
    \
    TYPENAME* cgArrayOf##TYPENAME##Iterator_fetch(cgArrayOf##TYPENAME##Iterator* this) { \
        if (this->hasStarted == true) \
            return cgArrayOf##TYPENAME##Iterator_getNextElement(this); \
        else { \
            this->hasStarted = true; \
            return cgArrayOf##TYPENAME##Iterator_getCurrentElement(this); \
        } \
    } \
    \
    void cgArrayOf##TYPENAME##Iterator_unFetch(cgArrayOf##TYPENAME##Iterator* this) { \
        if (this->hasStarted == true) { \
            if (this->currentIndex > 0) \
                --this->currentIndex; \
            else \
                this->hasStarted = false; \
        } else \
            cgAppState_throwException(cgAppState__getInstance(), cgException__new(Severity_none, cgExceptionID_ArrayIndexOutOfBounds, "Cannot unFetch on unstarted iterator")); \
    } \
    \
    void cgArrayOf##TYPENAME##Iterator_reset(cgArrayOf##TYPENAME##Iterator* this) { \
        this->currentIndex = 0; \
        this->hasStarted = false; \
    } \
    \
    cgArrayOf##TYPENAME##Iterator* cgArrayOf##TYPENAME##Iterator_clone(cgArrayOf##TYPENAME##Iterator* this) { \
        cgArrayOf##TYPENAME##Iterator* iter = cgArrayOf##TYPENAME##Iterator__new(this->array); \
        iter->currentIndex = this->currentIndex; \
        iter->hasStarted = this->hasStarted; \
        return iter; \
    } \
    \
    bool cgArrayOf##TYPENAME##Iterator_getHasStarted(cgArrayOf##TYPENAME##Iterator* this) { \
        return this->hasStarted; \
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

#define cgArrayIterator(TYPENAME) cgArrayOf##TYPENAME##Iterator


/* callers */

#define cgArrayIterator__new(TYPENAME, array) cgArrayOf##TYPENAME##Iterator__new((array)) 
#define cgArrayIterator_isInsideBounds(TYPENAME, this) cgArrayOf##TYPENAME##Iterator_isInsideBounds((this))
#define cgArrayIterator_delete(TYPENAME, this) cgArrayOf##TYPENAME##Iterator_delete((this)) 
#define cgArrayIterator_getCurrentIndex(TYPENAME, this) cgArrayOf##TYPENAME##Iterator_getCurrentIndex((this)) 
#define cgArrayIterator_getCurrentElement(TYPENAME, this) cgArrayOf##TYPENAME##Iterator_getCurrentElement((this)) 
#define cgArrayIterator_moveToNextElement(TYPENAME, this) cgArrayOf##TYPENAME##Iterator_moveToNextElement((this)) 
#define cgArrayIterator_moveToIndex(TYPENAME, this, index) cgArrayOf##TYPENAME##Iterator_moveToIndex((this), (index)) 
#define cgArrayIterator_getNextElement(TYPENAME, this) cgArrayOf##TYPENAME##Iterator_getNextElement((this)) 
#define cgArrayIterator_fetch(TYPENAME, this) cgArrayOf##TYPENAME##Iterator_fetch((this)) 
#define cgArrayIterator_unFetch(TYPENAME, this) cgArrayOf##TYPENAME##Iterator_unFetch((this)) 
#define cgArrayIterator_reset(TYPENAME, this) cgArrayOf##TYPENAME##Iterator_reset((this)) 
#define cgArrayIterator_getHasStarted(TYPENAME, this) cgArrayOf##TYPENAME##Iterator_getHasStarted((this))
#define cgArrayIterator_clone(TYPENAME, this) cgArrayOf##TYPENAME##Iterator_clone((this))

#endif
