#ifndef _CGARRAY_H
#define _CGARRAY_H

#include<stdlib.h>
#include<string.h>
#include<stdarg.h>
#include"CGAppState.h"

#define MAX_GROWTH_COUNT 65536

/** 
    calculate the needed element count from the current given count, the requested count, and the maximum size to grow per iteration
    - up to the maximum growth size count, we double the size each time
*/
static unsigned int calculateNeededElementCount(CGAppState* appState, unsigned int currentCount, const unsigned int requested, const unsigned int maxGrowthCount) {
    while (currentCount < requested)
        if (currentCount < maxGrowthCount)
            currentCount = currentCount << 1;
        else
            currentCount = currentCount + maxGrowthCount;
    return currentCount;
}


/* everything below this line is type-specific! */

/* declarations */

/** 
    This will init the CGArray for one typename
    NOTE: TYPENAME is a valid identifier; if you plan for a, say, CGArray<int*>, then do a typedef int* intPtr or the like...
*/

#define DECLARE_ARRAY_TYPE(TYPENAME) \
typedef struct { \
    TYPENAME** vector; \
    unsigned int usedElements; /* the size of the array */ \
    unsigned int capacityElements; /* the currently possible maximum size of the array */ \
} CGArrayOf##TYPENAME; \

#define DECLARE_ARRAY_FUNCS(TYPENAME) \
CGArrayOf##TYPENAME* CGArrayOf##TYPENAME##__new(CGAppState* appState, const unsigned int initialCapacity); \
CGArrayOf##TYPENAME* CGArrayOf##TYPENAME##__newFromInitializerList(CGAppState* appState, TYPENAME* item, ...); \
void CGArrayOf##TYPENAME##_delete(CGAppState* appState, CGArrayOf##TYPENAME* this); \
void CGArrayOf##TYPENAME##_deleteValues(CGAppState* appState, CGArrayOf##TYPENAME* this); \
CGArrayOf##TYPENAME* CGArrayOf##TYPENAME##_clone(CGAppState* appState, CGArrayOf##TYPENAME* this); \
void CGArrayOf##TYPENAME##_delete(CGAppState* appState, CGArrayOf##TYPENAME* this); \
void CGArrayOf##TYPENAME##_grow_(CGAppState* appState, CGArrayOf##TYPENAME* this, unsigned int requestedCapacity); \
TYPENAME* CGArrayOf##TYPENAME##_add(CGAppState* appState, CGArrayOf##TYPENAME* this, TYPENAME* value); \
TYPENAME* CGArrayOf##TYPENAME##_getValueAt(CGAppState* appState, CGArrayOf##TYPENAME* this, const unsigned int at); \
TYPENAME* CGArrayOf##TYPENAME##_pop(CGAppState* appState, CGArrayOf##TYPENAME* this); \
TYPENAME* CGArrayOf##TYPENAME##_shift(CGAppState* appState, CGArrayOf##TYPENAME* this); \
void CGArrayOf##TYPENAME##_unshift(CGAppState* appState, CGArrayOf##TYPENAME* this, TYPENAME* value); \
void CGArrayOf##TYPENAME##_insertValueAtAfterEnd_(CGAppState* appState, CGArrayOf##TYPENAME* this, TYPENAME* value, const unsigned int at); \
void CGArrayOf##TYPENAME##_insertValueAt(CGAppState* appState, CGArrayOf##TYPENAME* this, TYPENAME* value, const unsigned int at); \
TYPENAME* CGArrayOf##TYPENAME##_removeValueAt(CGAppState* appState, CGArrayOf##TYPENAME* this, unsigned int at); \
unsigned int CGArrayOf##TYPENAME##_getCapacity(CGAppState* appState, CGArrayOf##TYPENAME* this); \
unsigned int CGArrayOf##TYPENAME##_getSize(CGAppState* appState, CGArrayOf##TYPENAME* this); \
void CGArrayOf##TYPENAME##_qsort(CGAppState* appState, CGArrayOf##TYPENAME* this, int (*comparingFunction)(const TYPENAME**, const TYPENAME**)); \
void CGArrayOf##TYPENAME##_print(CGAppState* appState, CGArrayOf##TYPENAME* this, const char *printFormat); \
unsigned int CGArrayOf##TYPENAME##_findIndex(CGAppState *appState, CGArrayOf##TYPENAME* this, const TYPENAME* elementPointer, int (*comparingFunction)(const TYPENAME**, const TYPENAME**)); \
TYPENAME* CGArrayOf##TYPENAME##_find(CGAppState* appState, CGArrayOf##TYPENAME* this, const TYPENAME* elementPointer, int (*comparingFunction)(const TYPENAME**, const TYPENAME**)); \
CGArrayOf##TYPENAME* CGArrayOf##TYPENAME##_map(CGAppState* appState, CGArrayOf##TYPENAME* this, void (*mapFunction)(CGAppState*, TYPENAME*)); \
void CGArrayOf##TYPENAME##_mapConstant(CGAppState* appState, CGArrayOf##TYPENAME* this, void (*mapFunction)(CGAppState*, const TYPENAME*)); \

#define DEFINE_ARRAY_FUNCS(TYPENAME) \
\
CGArrayOf##TYPENAME* CGArrayOf##TYPENAME##__new(CGAppState* appState, const unsigned int initialCapacity) { \
    CGArrayOf##TYPENAME* this = malloc(sizeof(*this)); \
    if (this != NULL) { \
        this->usedElements = 0; \
        this->capacityElements = calculateNeededElementCount(appState, 1, initialCapacity, MAX_GROWTH_COUNT); \
        this->vector = malloc(sizeof(TYPENAME*) * initialCapacity); \
        if (this->vector == NULL) \
            CGAppState_THROW(appState, Severity_error, CGExceptionID_CannotAllocate, "cannot allocate CGArray"); \
    } else \
        CGAppState_THROW(appState, Severity_error, CGExceptionID_CannotAllocate, "cannot allocate CGArray"); \
    return this; \
} \
\
/**
    this expects a sentinel parameter (NULL) at the end of the initializer list
*/ \
CGArrayOf##TYPENAME* CGArrayOf##TYPENAME##__newFromInitializerList(CGAppState* appState, TYPENAME* item, ...) { \
    CGArrayOf##TYPENAME* this = CGArrayOf##TYPENAME##__new(appState, 1); \
    if (this != NULL) { \
        va_list args; \
        va_start(args, item); \
        while (item) { \
            CGArrayOf##TYPENAME##_add(appState, this, item); \
            if (CGAppState_isExceptionRaised(appState)) \
                break; \
            item = va_arg(args, TYPENAME*); \
        } \
        va_end(args); \
    } \
    return this; \
} \
\
void CGArrayOf##TYPENAME##_delete(CGAppState* appState, CGArrayOf##TYPENAME* this); \
CGArrayOf##TYPENAME* CGArrayOf##TYPENAME##_clone(CGAppState* appState, CGArrayOf##TYPENAME* this) { \
    CGArrayOf##TYPENAME* that = CGArrayOf##TYPENAME##__new(appState, this->capacityElements); \
    if (CGAppState_isExceptionRaisedWithID(appState, CGExceptionID_CannotAllocate)) \
        return NULL; \
    unsigned int i; \
    for (i=0; i < this->usedElements; ++i) { \
        *(that->vector + i) = TYPENAME##_clone(appState, *(this->vector + i)); \
        if (CGAppState_isExceptionRaised(appState)) { \
            CGArrayOf##TYPENAME##_delete(appState, that); \
            return NULL; \
        } \
    } \
    that->usedElements = this->usedElements; \
    return that; \
} \
\
void CGArrayOf##TYPENAME##_delete(CGAppState* appState, CGArrayOf##TYPENAME* this) { \
    free(this->vector); \
    free(this); \
} \
\
void TYPENAME##_delete(CGAppState* appState, TYPENAME* this); \
void CGArrayOf##TYPENAME##_deleteValues(CGAppState* appState, CGArrayOf##TYPENAME* this) { \
    unsigned int i; \
    for (i=0; i < this->usedElements; ++i) \
        TYPENAME##_delete(appState, *(this->vector + i)); \
} \
\
void CGArrayOf##TYPENAME##_grow_(CGAppState* appState, CGArrayOf##TYPENAME* this, unsigned int requestedCapacity) { \
    unsigned int newCapacity = calculateNeededElementCount(appState, this->capacityElements, requestedCapacity, MAX_GROWTH_COUNT); \
    this->vector = realloc(this->vector, sizeof(TYPENAME*) * newCapacity); \
    if (this->vector == NULL) \
        CGAppState_THROW(appState, Severity_error, CGExceptionID_CannotAllocate, "cannot allocate CGArray"); \
    else \
        this->capacityElements = newCapacity; \
} \
\
TYPENAME* CGArrayOf##TYPENAME##_add(CGAppState* appState, CGArrayOf##TYPENAME* this, TYPENAME* value) { \
    if (this->usedElements == this->capacityElements) \
        CGArrayOf##TYPENAME##_grow_(appState, this, this->capacityElements + 1); \
    *(this->vector + this->usedElements) = value; \
    ++(this->usedElements); \
    return value; \
} \
\
TYPENAME* CGArrayOf##TYPENAME##_getValueAt(CGAppState* appState, CGArrayOf##TYPENAME* this, const unsigned int at) { \
    if (at >= this->usedElements) { \
        CGAppState_THROW(appState, Severity_error, CGExceptionID_ArrayIndexOutOfBounds, "cannot get value beyond array end (requested position: %u)", at); \
        return *(this->vector); \
    } \
    return *(this->vector + at); \
} \
\
TYPENAME* CGArrayOf##TYPENAME##_pop(CGAppState* appState, CGArrayOf##TYPENAME* this) { \
    if (this->usedElements == 0) { \
        CGAppState_THROW(appState, Severity_error, CGExceptionID_ArrayIndexOutOfBounds, "cannot pop from empty array"); \
        return *(this->vector); \
    } \
    --this->usedElements; \
    return *(this->vector + this->usedElements); \
} \
\
TYPENAME* CGArrayOf##TYPENAME##_shift(CGAppState* appState, CGArrayOf##TYPENAME* this) { \
    if (this->usedElements == 0) {\
        CGAppState_THROW(appState, Severity_error, CGExceptionID_ArrayIndexOutOfBounds, "cannot shift from empty array"); \
        return *(this->vector); \
    } \
    TYPENAME* firstValue = *(this->vector); \
    --this->usedElements; \
    memmove(this->vector, (this->vector + 1), sizeof(TYPENAME*) * this->usedElements); \
    return firstValue; \
} \
\
void CGArrayOf##TYPENAME##_unshift(CGAppState* appState, CGArrayOf##TYPENAME* this, TYPENAME* value) { \
    if (this->usedElements == this->capacityElements) \
        CGArrayOf##TYPENAME##_grow_(appState, this, this->capacityElements + 1); \
    memmove((this->vector + 1), this->vector, sizeof(TYPENAME*) * this->usedElements); \
    *(this->vector) = value; \
    ++this->usedElements; \
} \
\
void CGArrayOf##TYPENAME##_insertValueAtAfterEnd_(CGAppState* appState, CGArrayOf##TYPENAME* this, TYPENAME* value, const unsigned int at) { \
    unsigned int neededCapacityElements = max(at + 1, this->capacityElements); \
    CGArrayOf##TYPENAME##_grow_(appState, this, neededCapacityElements); \
    *(this->vector + at) = value; \
    this->usedElements = at + 1; \
} \
\
void CGArrayOf##TYPENAME##_insertValueAt(CGAppState* appState, CGArrayOf##TYPENAME* this, TYPENAME* value, const unsigned int at) { \
    if (at >= this->usedElements) { \
        CGArrayOf##TYPENAME##_insertValueAtAfterEnd_(appState, this, value, at); \
    } else {\
        if (this->usedElements == this->capacityElements) \
            CGArrayOf##TYPENAME##_grow_(appState, this, this->capacityElements + 1); \
        memmove((this->vector + at + 1), (this->vector + at), sizeof(TYPENAME*) * (this->usedElements - at)); \
        *(this->vector + at) = value; \
        ++this->usedElements; \
    } \
} \
\
TYPENAME* CGArrayOf##TYPENAME##_removeValueAt(CGAppState* appState, CGArrayOf##TYPENAME* this, unsigned int at) { \
    if (at >= this->usedElements) { \
        CGAppState_THROW(appState, Severity_error, CGExceptionID_ArrayIndexOutOfBounds, "cannot remove value beyond array end"); \
        return *(this->vector); \
    } \
    TYPENAME* value = *(this->vector + at); \
    --this->usedElements; \
    memmove((this->vector + at), (this->vector + at + 1), sizeof(TYPENAME*) * (this->usedElements - at)); \
    return value; \
} \
\
unsigned int CGArrayOf##TYPENAME##_getCapacity(CGAppState* appState, CGArrayOf##TYPENAME* this) { \
    return this->capacityElements; \
} \
\
unsigned int CGArrayOf##TYPENAME##_getSize(CGAppState* appState, CGArrayOf##TYPENAME* this) { \
    return this->usedElements; \
} \
void CGArrayOf##TYPENAME##_qsort(CGAppState* appState, CGArrayOf##TYPENAME* this, int (*comparingFunction)(const TYPENAME**, const TYPENAME**)) { \
    /* \
    void qsort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *)); \
    compar: <0, 0, >0
    */ \
    qsort(this->vector, this->usedElements, sizeof(TYPENAME*), (int(*)(const void*, const void*))comparingFunction); \
} \
\
void CGArrayOf##TYPENAME##_print(CGAppState* appState, CGArrayOf##TYPENAME* this, const char *printFormat) { \
    unsigned int i; \
    char *printFormatWithSpace = malloc(sizeof(char) * strlen(printFormat) + 2); \
    sprintf(printFormatWithSpace, "%s ", printFormat); \
    for (i=0; i < this->usedElements; ++i) \
        printf(printFormatWithSpace, *(this->vector + i)); \
    printf("\n"); \
    free(printFormatWithSpace); \
} \
\
unsigned int CGArrayOf##TYPENAME##_findIndex(CGAppState *appState, CGArrayOf##TYPENAME* this, const TYPENAME* elementPointer, int (*comparingFunction)(const TYPENAME**, const TYPENAME**)) { \
    unsigned int i; \
    for (i = 0; i < this->usedElements; ++i) \
        if ((comparingFunction)((const TYPENAME**)this->vector + i, (const TYPENAME**)&elementPointer) == 0) \
            return i; \
    CGAppState_THROW(appState, Severity_none, CGExceptionID_ElementNotFound, NULL); \
    return 0; \
} \
\
TYPENAME* CGArrayOf##TYPENAME##_find(CGAppState* appState, CGArrayOf##TYPENAME* this, const TYPENAME* elementPointer, int (*comparingFunction)(const TYPENAME**, const TYPENAME**)) { \
    unsigned int index = CGArrayOf##TYPENAME##_findIndex(appState, this, elementPointer, comparingFunction); \
    if (CGAppState_isExceptionRaisedWithID(appState, CGExceptionID_ElementNotFound)) \
        return NULL; \
    else \
        return this->vector[index]; \
} \
\
CGArrayOf##TYPENAME* CGArrayOf##TYPENAME##_map(CGAppState* appState, CGArrayOf##TYPENAME* this, void (*mapFunction)(CGAppState*, TYPENAME*)) { \
    unsigned int i; \
    CGArrayOf##TYPENAME* that = CGArrayOf##TYPENAME##_clone(appState, this); \
    if (CGAppState_isExceptionRaised(appState)) \
        return NULL; \
    for (i = 0; i < that->usedElements; ++i) \
        (mapFunction)(appState, *(that->vector + i)); \
    return that; \
} \
\
void CGArrayOf##TYPENAME##_mapConstant(CGAppState* appState, CGArrayOf##TYPENAME* this, void (*mapFunction)(CGAppState*, const TYPENAME*)) { \
    unsigned int i; \
    for (i = 0; i < this->usedElements; ++i) \
        (mapFunction)(appState, *(this->vector + i)); \
} \

#define DECLARE_ARRAY(TYPENAME) \
    DECLARE_ARRAY_TYPE(TYPENAME) \
    DECLARE_ARRAY_FUNCS(TYPENAME) 

#define DEFINE_ARRAY(TYPENAME) \
    DEFINE_ARRAY_FUNCS(TYPENAME) 

#define INIT_ARRAY(TYPENAME) \
    DECLARE_ARRAY(TYPENAME) \
    DEFINE_ARRAY(TYPENAME)


/* type definition */

#define CGArray(TYPENAME) CGArrayOf##TYPENAME


/* callers */

#define CGArray__new(appState, TYPENAME, initialCapacity) CGArrayOf##TYPENAME##__new((appState), (initialCapacity))
#define CGArray__newFromInitializerList(appState, TYPENAME, ...) CGArrayOf##TYPENAME##__newFromInitializerList((appState), __VA_ARGS__)
#define CGArray_clone(appState, TYPENAME, array) CGArrayOf##TYPENAME##_clone((appState), (array))
#define CGArray_delete(appState, TYPENAME, array) CGArrayOf##TYPENAME##_delete((appState), (array))
#define CGArray_deleteValues(appState, TYPENAME, array) CGArrayOf##TYPENAME##_deleteValues((appState), (array))
#define CGArray_add(appState, TYPENAME, array, value) CGArrayOf##TYPENAME##_add((appState), (array), (value))
#define CGArray_getValueAt(appState, TYPENAME, array, at) CGArrayOf##TYPENAME##_getValueAt((appState), (array), (at))
#define CGArray_push CGArray_add
#define CGArray_pop(appState, TYPENAME, array) CGArrayOf##TYPENAME##_pop((appState), (array))
#define CGArray_getCapacity(appState, TYPENAME, array) CGArrayOf##TYPENAME##_getCapacity((appState), (array))
#define CGArray_getSize(appState, TYPENAME, array) CGArrayOf##TYPENAME##_getSize((appState), (array))
#define CGArray_shift(appState, TYPENAME, array) CGArrayOf##TYPENAME##_shift((appState), (array))
#define CGArray_unshift(appState, TYPENAME, array, value) CGArrayOf##TYPENAME##_unshift((appState), (array), (value))
#define CGArray_insertValueAt(appState, TYPENAME, array, value, at) CGArrayOf##TYPENAME##_insertValueAt((appState), (array), (value), (at))
#define CGArray_removeValueAt(appState, TYPENAME, array, at) CGArrayOf##TYPENAME##_removeValueAt((appState), (array), (at))
#define CGArray_qsort(appState, TYPENAME, array, comparingFunction) CGArrayOf##TYPENAME##_qsort((appState), (array), (comparingFunction))
#define CGArray_qsort_r(appState, TYPENAME, array, comparingFunction) CGArrayOf##TYPENAME##_qsort_r((appState), (array), (comparingFunction))
#define CGArray_print(appState, TYPENAME, array, printFormat) CGArrayOf##TYPENAME##_print((appState), (array), (printFormat))
#define CGArray_findIndex(appState, TYPENAME, array, elementPointer, comparingFunction) CGArrayOf##TYPENAME##_findIndex((appState), (array), (elementPointer), (comparingFunction))
#define CGArray_find(appState, TYPENAME, array, elementPointer, comparingFunction) CGArrayOf##TYPENAME##_find((appState), (array), (elementPointer), (comparingFunction))
#define CGArray_map(appState, TYPENAME, array, mapFunction) CGArrayOf##TYPENAME##_map((appState), (array), (mapFunction))
#define CGArray_mapConstant(appState, TYPENAME, array, mapFunction) CGArrayOf##TYPENAME##_mapConstant((appState), (array), (mapFunction))


#endif 
