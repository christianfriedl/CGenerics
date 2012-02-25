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
static unsigned int calculateNeededElementCount(unsigned int currentCount, const unsigned int requested, const unsigned int maxGrowthCount) {
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
CGArrayOf##TYPENAME* CGArrayOf##TYPENAME##__new(const unsigned int initialCapacity); \
CGArrayOf##TYPENAME* CGArrayOf##TYPENAME##__newFromInitializerList(TYPENAME* item, ...); \
void CGArrayOf##TYPENAME##_delete(CGArrayOf##TYPENAME* this); \
void CGArrayOf##TYPENAME##_deleteValues(CGArrayOf##TYPENAME* this); \
CGArrayOf##TYPENAME* CGArrayOf##TYPENAME##_clone(CGArrayOf##TYPENAME* this); \
void CGArrayOf##TYPENAME##_delete(CGArrayOf##TYPENAME* this); \
void CGArrayOf##TYPENAME##_grow_(CGArrayOf##TYPENAME* this, unsigned int requestedCapacity); \
TYPENAME* CGArrayOf##TYPENAME##_add(CGArrayOf##TYPENAME* this, TYPENAME* value); \
TYPENAME* CGArrayOf##TYPENAME##_getValueAt(CGArrayOf##TYPENAME* this, const unsigned int at); \
TYPENAME* CGArrayOf##TYPENAME##_pop(CGArrayOf##TYPENAME* this); \
TYPENAME* CGArrayOf##TYPENAME##_shift(CGArrayOf##TYPENAME* this); \
void CGArrayOf##TYPENAME##_unshift(CGArrayOf##TYPENAME* this, TYPENAME* value); \
void CGArrayOf##TYPENAME##_insertValueAtAfterEnd_(CGArrayOf##TYPENAME* this, TYPENAME* value, const unsigned int at); \
void CGArrayOf##TYPENAME##_insertValueAt(CGArrayOf##TYPENAME* this, TYPENAME* value, const unsigned int at); \
TYPENAME* CGArrayOf##TYPENAME##_removeValueAt(CGArrayOf##TYPENAME* this, unsigned int at); \
unsigned int CGArrayOf##TYPENAME##_getCapacity(CGArrayOf##TYPENAME* this); \
unsigned int CGArrayOf##TYPENAME##_getSize(CGArrayOf##TYPENAME* this); \
void CGArrayOf##TYPENAME##_qsort(CGArrayOf##TYPENAME* this, int (*comparingFunction)(const TYPENAME**, const TYPENAME**)); \
void CGArrayOf##TYPENAME##_print(CGArrayOf##TYPENAME* this, const char *printFormat); \
unsigned int CGArrayOf##TYPENAME##_findIndex(CGArrayOf##TYPENAME* this, const TYPENAME* elementPointer, int (*comparingFunction)(const TYPENAME**, const TYPENAME**)); \
TYPENAME* CGArrayOf##TYPENAME##_find(CGArrayOf##TYPENAME* this, const TYPENAME* elementPointer, int (*comparingFunction)(const TYPENAME**, const TYPENAME**)); \
CGArrayOf##TYPENAME* CGArrayOf##TYPENAME##_map(CGArrayOf##TYPENAME* this, void (*mapFunction)(TYPENAME*)); \
void CGArrayOf##TYPENAME##_mapConstant(CGArrayOf##TYPENAME* this, void (*mapFunction)(const TYPENAME*)); \

#define DEFINE_ARRAY_FUNCS(TYPENAME) \
\
CGArrayOf##TYPENAME* CGArrayOf##TYPENAME##__new(const unsigned int initialCapacity) { \
    CGArrayOf##TYPENAME* this = malloc(sizeof(*this)); \
    if (this != NULL) { \
        this->usedElements = 0; \
        this->capacityElements = calculateNeededElementCount(1, initialCapacity, MAX_GROWTH_COUNT); \
        this->vector = malloc(sizeof(TYPENAME*) * initialCapacity); \
        if (this->vector == NULL) \
            CGAppState_THROW(CGAppState__getInstance(), Severity_error, CGExceptionID_CannotAllocate, "cannot allocate CGArray"); \
    } else \
        CGAppState_THROW(CGAppState__getInstance(), Severity_error, CGExceptionID_CannotAllocate, "cannot allocate CGArray"); \
    return this; \
} \
\
/**
    this expects a sentinel parameter (NULL) at the end of the initializer list
*/ \
CGArrayOf##TYPENAME* CGArrayOf##TYPENAME##__newFromInitializerList(TYPENAME* item, ...) { \
    CGArrayOf##TYPENAME* this = CGArrayOf##TYPENAME##__new(1); \
    if (this != NULL) { \
        va_list args; \
        va_start(args, item); \
        while (item) { \
            CGArrayOf##TYPENAME##_add(this, item); \
            if (CGAppState_isExceptionRaised(CGAppState__getInstance())) \
                break; \
            item = va_arg(args, TYPENAME*); \
        } \
        va_end(args); \
    } \
    return this; \
} \
\
void CGArrayOf##TYPENAME##_delete(CGArrayOf##TYPENAME* this); \
CGArrayOf##TYPENAME* CGArrayOf##TYPENAME##_clone(CGArrayOf##TYPENAME* this) { \
    CGArrayOf##TYPENAME* that = CGArrayOf##TYPENAME##__new(this->capacityElements); \
    if (CGAppState_isExceptionRaisedWithID(CGAppState__getInstance(), CGExceptionID_CannotAllocate)) \
        return NULL; \
    unsigned int i; \
    for (i=0; i < this->usedElements; ++i) { \
        *(that->vector + i) = TYPENAME##_clone(*(this->vector + i)); \
        if (CGAppState_isExceptionRaised(CGAppState__getInstance())) { \
            CGArrayOf##TYPENAME##_delete(that); \
            return NULL; \
        } \
    } \
    that->usedElements = this->usedElements; \
    return that; \
} \
\
void CGArrayOf##TYPENAME##_delete(CGArrayOf##TYPENAME* this) { \
    free(this->vector); \
    free(this); \
} \
\
void TYPENAME##_delete(TYPENAME* this); \
void CGArrayOf##TYPENAME##_deleteValues(CGArrayOf##TYPENAME* this) { \
    unsigned int i; \
    for (i=0; i < this->usedElements; ++i) \
        TYPENAME##_delete(*(this->vector + i)); \
} \
\
void CGArrayOf##TYPENAME##_grow_(CGArrayOf##TYPENAME* this, unsigned int requestedCapacity) { \
    unsigned int newCapacity = calculateNeededElementCount(this->capacityElements, requestedCapacity, MAX_GROWTH_COUNT); \
    this->vector = realloc(this->vector, sizeof(TYPENAME*) * newCapacity); \
    if (this->vector == NULL) \
        CGAppState_THROW(CGAppState__getInstance(), Severity_error, CGExceptionID_CannotAllocate, "cannot allocate CGArray"); \
    else \
        this->capacityElements = newCapacity; \
} \
\
TYPENAME* CGArrayOf##TYPENAME##_add(CGArrayOf##TYPENAME* this, TYPENAME* value) { \
    if (this->usedElements == this->capacityElements) \
        CGArrayOf##TYPENAME##_grow_(this, this->capacityElements + 1); \
    *(this->vector + this->usedElements) = value; \
    ++(this->usedElements); \
    return value; \
} \
\
TYPENAME* CGArrayOf##TYPENAME##_getValueAt(CGArrayOf##TYPENAME* this, const unsigned int at) { \
    if (at >= this->usedElements) { \
        CGAppState_THROW(CGAppState__getInstance(), Severity_error, CGExceptionID_ArrayIndexOutOfBounds, "cannot get value beyond array end (requested position: %u)", at); \
        return *(this->vector); \
    } \
    return *(this->vector + at); \
} \
\
TYPENAME* CGArrayOf##TYPENAME##_pop(CGArrayOf##TYPENAME* this) { \
    if (this->usedElements == 0) { \
        CGAppState_THROW(CGAppState__getInstance(), Severity_error, CGExceptionID_ArrayIndexOutOfBounds, "cannot pop from empty array"); \
        return *(this->vector); \
    } \
    --this->usedElements; \
    return *(this->vector + this->usedElements); \
} \
\
TYPENAME* CGArrayOf##TYPENAME##_shift(CGArrayOf##TYPENAME* this) { \
    if (this->usedElements == 0) {\
        CGAppState_THROW(CGAppState__getInstance(), Severity_error, CGExceptionID_ArrayIndexOutOfBounds, "cannot shift from empty array"); \
        return *(this->vector); \
    } \
    TYPENAME* firstValue = *(this->vector); \
    --this->usedElements; \
    memmove(this->vector, (this->vector + 1), sizeof(TYPENAME*) * this->usedElements); \
    return firstValue; \
} \
\
void CGArrayOf##TYPENAME##_unshift(CGArrayOf##TYPENAME* this, TYPENAME* value) { \
    if (this->usedElements == this->capacityElements) \
        CGArrayOf##TYPENAME##_grow_(this, this->capacityElements + 1); \
    memmove((this->vector + 1), this->vector, sizeof(TYPENAME*) * this->usedElements); \
    *(this->vector) = value; \
    ++this->usedElements; \
} \
\
void CGArrayOf##TYPENAME##_insertValueAtAfterEnd_(CGArrayOf##TYPENAME* this, TYPENAME* value, const unsigned int at) { \
    unsigned int neededCapacityElements = max(at + 1, this->capacityElements); \
    CGArrayOf##TYPENAME##_grow_(this, neededCapacityElements); \
    *(this->vector + at) = value; \
    this->usedElements = at + 1; \
} \
\
void CGArrayOf##TYPENAME##_insertValueAt(CGArrayOf##TYPENAME* this, TYPENAME* value, const unsigned int at) { \
    if (at >= this->usedElements) { \
        CGArrayOf##TYPENAME##_insertValueAtAfterEnd_(this, value, at); \
    } else {\
        if (this->usedElements == this->capacityElements) \
            CGArrayOf##TYPENAME##_grow_(this, this->capacityElements + 1); \
        memmove((this->vector + at + 1), (this->vector + at), sizeof(TYPENAME*) * (this->usedElements - at)); \
        *(this->vector + at) = value; \
        ++this->usedElements; \
    } \
} \
\
TYPENAME* CGArrayOf##TYPENAME##_removeValueAt(CGArrayOf##TYPENAME* this, unsigned int at) { \
    if (at >= this->usedElements) { \
        CGAppState_THROW(CGAppState__getInstance(), Severity_error, CGExceptionID_ArrayIndexOutOfBounds, "cannot remove value beyond array end"); \
        return *(this->vector); \
    } \
    TYPENAME* value = *(this->vector + at); \
    --this->usedElements; \
    memmove((this->vector + at), (this->vector + at + 1), sizeof(TYPENAME*) * (this->usedElements - at)); \
    return value; \
} \
\
unsigned int CGArrayOf##TYPENAME##_getCapacity(CGArrayOf##TYPENAME* this) { \
    return this->capacityElements; \
} \
\
unsigned int CGArrayOf##TYPENAME##_getSize(CGArrayOf##TYPENAME* this) { \
    return this->usedElements; \
} \
void CGArrayOf##TYPENAME##_qsort(CGArrayOf##TYPENAME* this, int (*comparingFunction)(const TYPENAME**, const TYPENAME**)) { \
    /* \
    void qsort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *)); \
    compar: <0, 0, >0
    */ \
    qsort(this->vector, this->usedElements, sizeof(TYPENAME*), (int(*)(const void*, const void*))comparingFunction); \
} \
\
void CGArrayOf##TYPENAME##_print(CGArrayOf##TYPENAME* this, const char *printFormat) { \
    unsigned int i; \
    char *printFormatWithSpace = malloc(sizeof(char) * strlen(printFormat) + 2); \
    sprintf(printFormatWithSpace, "%s ", printFormat); \
    for (i=0; i < this->usedElements; ++i) \
        printf(printFormatWithSpace, *(this->vector + i)); \
    printf("\n"); \
    free(printFormatWithSpace); \
} \
\
unsigned int CGArrayOf##TYPENAME##_findIndex(CGArrayOf##TYPENAME* this, const TYPENAME* elementPointer, int (*comparingFunction)(const TYPENAME**, const TYPENAME**)) { \
    unsigned int i; \
    for (i = 0; i < this->usedElements; ++i) \
        if ((comparingFunction)((const TYPENAME**)this->vector + i, (const TYPENAME**)&elementPointer) == 0) \
            return i; \
    CGAppState_THROW(CGAppState__getInstance(), Severity_none, CGExceptionID_ElementNotFound, NULL); \
    return 0; \
} \
\
TYPENAME* CGArrayOf##TYPENAME##_find(CGArrayOf##TYPENAME* this, const TYPENAME* elementPointer, int (*comparingFunction)(const TYPENAME**, const TYPENAME**)) { \
    unsigned int index = CGArrayOf##TYPENAME##_findIndex(this, elementPointer, comparingFunction); \
    if (CGAppState_isExceptionRaisedWithID(CGAppState__getInstance(), CGExceptionID_ElementNotFound)) \
        return NULL; \
    else \
        return this->vector[index]; \
} \
\
CGArrayOf##TYPENAME* CGArrayOf##TYPENAME##_map(CGArrayOf##TYPENAME* this, void (*mapFunction)(TYPENAME*)) { \
    unsigned int i; \
    CGArrayOf##TYPENAME* that = CGArrayOf##TYPENAME##_clone(this); \
    if (CGAppState_isExceptionRaised(CGAppState__getInstance())) \
        return NULL; \
    for (i = 0; i < that->usedElements; ++i) \
        (mapFunction)(*(that->vector + i)); \
    return that; \
} \
\
void CGArrayOf##TYPENAME##_mapConstant(CGArrayOf##TYPENAME* this, void (*mapFunction)(const TYPENAME*)) { \
    unsigned int i; \
    for (i = 0; i < this->usedElements; ++i) \
        (mapFunction)(*(this->vector + i)); \
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

#define CGArray__new(TYPENAME, initialCapacity) CGArrayOf##TYPENAME##__new((initialCapacity))
#define CGArray__newFromInitializerList(TYPENAME, ...) CGArrayOf##TYPENAME##__newFromInitializerList(__VA_ARGS__)
#define CGArray_clone(TYPENAME, array) CGArrayOf##TYPENAME##_clone((array))
#define CGArray_delete(TYPENAME, array) CGArrayOf##TYPENAME##_delete((array))
#define CGArray_deleteValues(TYPENAME, array) CGArrayOf##TYPENAME##_deleteValues((array))
#define CGArray_add(TYPENAME, array, value) CGArrayOf##TYPENAME##_add((array), (value))
#define CGArray_getValueAt(TYPENAME, array, at) CGArrayOf##TYPENAME##_getValueAt((array), (at))
#define CGArray_push CGArray_add
#define CGArray_pop(TYPENAME, array) CGArrayOf##TYPENAME##_pop((array))
#define CGArray_getCapacity(TYPENAME, array) CGArrayOf##TYPENAME##_getCapacity((array))
#define CGArray_getSize(TYPENAME, array) CGArrayOf##TYPENAME##_getSize((array))
#define CGArray_shift(TYPENAME, array) CGArrayOf##TYPENAME##_shift((array))
#define CGArray_unshift(TYPENAME, array, value) CGArrayOf##TYPENAME##_unshift((array), (value))
#define CGArray_insertValueAt(TYPENAME, array, value, at) CGArrayOf##TYPENAME##_insertValueAt((array), (value), (at))
#define CGArray_removeValueAt(TYPENAME, array, at) CGArrayOf##TYPENAME##_removeValueAt((array), (at))
#define CGArray_qsort(TYPENAME, array, comparingFunction) CGArrayOf##TYPENAME##_qsort((array), (comparingFunction))
#define CGArray_qsort_r(TYPENAME, array, comparingFunction) CGArrayOf##TYPENAME##_qsort_r((array), (comparingFunction))
#define CGArray_print(TYPENAME, array, printFormat) CGArrayOf##TYPENAME##_print((array), (printFormat))
#define CGArray_findIndex(TYPENAME, array, elementPointer, comparingFunction) CGArrayOf##TYPENAME##_findIndex((array), (elementPointer), (comparingFunction))
#define CGArray_find(TYPENAME, array, elementPointer, comparingFunction) CGArrayOf##TYPENAME##_find((array), (elementPointer), (comparingFunction))
#define CGArray_map(TYPENAME, array, mapFunction) CGArrayOf##TYPENAME##_map((array), (mapFunction))
#define CGArray_mapConstant(TYPENAME, array, mapFunction) CGArrayOf##TYPENAME##_mapConstant((array), (mapFunction))


#endif 
