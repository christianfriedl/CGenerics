#ifndef _ARRAY_H
#define _ARRAY_H

#include<stdlib.h>
#include<string.h>
#include"AppState.h"

#define MAX_GROWTH_COUNT 65536

/** 
    calculate the needed element count from the current given count, the requested count, and the maximum size to grow per iteration
    - up to the maximum growth size count, we double the size each time
*/
unsigned int calculateNeededElementCount(AppState* appState, unsigned int currentCount, const unsigned int requested, const unsigned int maxGrowthCount) {
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
    This will init the Array for one typename
    NOTE: TYPENAME is a valid identifier; if you plan for a, say, Array<int*>, then do a typedef int* intPtr or the like...
*/

#define INIT_ARRAY(TYPENAME) \
typedef struct { \
    TYPENAME** vector; \
    unsigned int usedElements; /* the size of the array */ \
    unsigned int capacityElements; /* the currently possible maximum size of the array */ \
} ArrayOf##TYPENAME; \
\
ArrayOf##TYPENAME* ArrayOf##TYPENAME##__new(AppState* appState, const unsigned int initialCapacity) { \
    ArrayOf##TYPENAME* this = malloc(sizeof(*this)); \
    if (this != NULL) { \
        this->usedElements = 0; \
        this->capacityElements = calculateNeededElementCount(appState, 1, initialCapacity, MAX_GROWTH_COUNT); \
        this->vector = malloc(sizeof(TYPENAME*) * initialCapacity); \
        if (this->vector == NULL) \
            AppState_throwException(appState, Exception__new(Severity_error, ExceptionID_CannotAllocate, "cannot allocate Array")); \
    } else \
        AppState_throwException(appState, Exception__new(Severity_error, ExceptionID_CannotAllocate, "cannot allocate Array")); \
    return this; \
} \
\
ArrayOf##TYPENAME* ArrayOf##TYPENAME##_clone(AppState* appState, ArrayOf##TYPENAME* this) { \
    ArrayOf##TYPENAME* that = ArrayOf##TYPENAME##__new(appState, this->capacityElements); \
    if (AppState_isExceptionRaisedWithID(appState, ExceptionID_CannotAllocate)) \
        return NULL; \
    memcpy(that->vector, this->vector, sizeof(TYPENAME*) * this->usedElements); \
    that->usedElements = this->usedElements; \
    return that; \
} \
\
void ArrayOf##TYPENAME##_delete(AppState* appState, ArrayOf##TYPENAME* this) { \
    free(this->vector); \
    free(this); \
} \
\
void TYPENAME##_delete(TYPENAME* this); \
void ArrayOf##TYPENAME##_deleteValues(AppState* appState, ArrayOf##TYPENAME* this) { \
    unsigned int i; \
    for (i=0; i < this->usedElements; ++i) \
        TYPENAME##_delete(*(this->vector + i)); \
} \
\
void ArrayOf##TYPENAME##_grow_(AppState* appState, ArrayOf##TYPENAME* this, unsigned int requestedCapacity) { \
    unsigned int newCapacity = calculateNeededElementCount(appState, this->capacityElements, requestedCapacity, MAX_GROWTH_COUNT); \
    this->vector = realloc(this->vector, sizeof(TYPENAME*) * newCapacity); \
    if (this->vector == NULL) \
        AppState_throwException(appState, Exception__new(Severity_error, ExceptionID_CannotAllocate, "cannot allocate Array")); \
    else \
        this->capacityElements = newCapacity; \
} \
\
TYPENAME* ArrayOf##TYPENAME##_add(AppState* appState, ArrayOf##TYPENAME* this, TYPENAME* value) { \
    if (this->usedElements == this->capacityElements) \
        ArrayOf##TYPENAME##_grow_(appState, this, this->capacityElements + 1); \
    *(this->vector + this->usedElements) = value; \
    ++(this->usedElements); \
    return value; \
} \
\
TYPENAME* ArrayOf##TYPENAME##_getValueAt(AppState* appState, ArrayOf##TYPENAME* this, const unsigned int at) { \
    if (at >= this->usedElements) { \
        AppState_throwException(appState, Exception__new(Severity_error, ExceptionID_ArrayIndexOutOfBounds, "cannot get value beyond array end (requested position: %u)", at)); \
        return *(this->vector); \
    } \
    return *(this->vector + at); \
} \
\
TYPENAME* ArrayOf##TYPENAME##_pop(AppState* appState, ArrayOf##TYPENAME* this) { \
    if (this->usedElements == 0) { \
        AppState_throwException(appState, Exception__new(Severity_error, ExceptionID_ArrayIndexOutOfBounds, "cannot pop from empty array")); \
        return *(this->vector); \
    } \
    --this->usedElements; \
    return *(this->vector + this->usedElements); \
} \
\
TYPENAME* ArrayOf##TYPENAME##_shift(AppState* appState, ArrayOf##TYPENAME* this) { \
    if (this->usedElements == 0) {\
        AppState_throwException(appState, Exception__new(Severity_error, ExceptionID_ArrayIndexOutOfBounds, "cannot shift from empty array")); \
        return *(this->vector); \
    } \
    TYPENAME* firstValue = *(this->vector); \
    --this->usedElements; \
    memmove(this->vector, (this->vector + 1), sizeof(TYPENAME*) * this->usedElements); \
    return firstValue; \
} \
\
void ArrayOf##TYPENAME##_unshift(AppState* appState, ArrayOf##TYPENAME* this, TYPENAME* value) { \
    if (this->usedElements == this->capacityElements) \
        ArrayOf##TYPENAME##_grow_(appState, this, this->capacityElements + 1); \
    memmove((this->vector + 1), this->vector, sizeof(TYPENAME*) * this->usedElements); \
    *(this->vector) = value; \
    ++this->usedElements; \
} \
\
void ArrayOf##TYPENAME##_insertValueAtAfterEnd_(AppState* appState, ArrayOf##TYPENAME* this, TYPENAME* value, const unsigned int at) { \
    unsigned int neededCapacityElements = max(at + 1, this->capacityElements); \
    ArrayOf##TYPENAME##_grow_(appState, this, neededCapacityElements); \
    *(this->vector + at) = value; \
    this->usedElements = at + 1; \
} \
\
void ArrayOf##TYPENAME##_insertValueAt(AppState* appState, ArrayOf##TYPENAME* this, TYPENAME* value, const unsigned int at) { \
    if (at >= this->usedElements) { \
        ArrayOf##TYPENAME##_insertValueAtAfterEnd_(appState, this, value, at); \
    } else {\
        if (this->usedElements == this->capacityElements) \
            ArrayOf##TYPENAME##_grow_(appState, this, this->capacityElements + 1); \
        memmove((this->vector + at + 1), (this->vector + at), sizeof(TYPENAME*) * (this->usedElements - at)); \
        *(this->vector + at) = value; \
        ++this->usedElements; \
    } \
} \
\
TYPENAME* ArrayOf##TYPENAME##_removeValueAt(AppState* appState, ArrayOf##TYPENAME* this, unsigned int at) { \
    if (at >= this->usedElements) { \
        AppState_throwException(appState, Exception__new(Severity_error, ExceptionID_ArrayIndexOutOfBounds, "cannot remove value beyond array end")); \
        return *(this->vector); \
    } \
    TYPENAME* value = *(this->vector + at); \
    --this->usedElements; \
    memmove((this->vector + at), (this->vector + at + 1), sizeof(TYPENAME*) * (this->usedElements - at)); \
    return value; \
} \
\
unsigned int ArrayOf##TYPENAME##_getCapacity(AppState* appState, ArrayOf##TYPENAME* this) { \
    return this->capacityElements; \
} \
\
unsigned int ArrayOf##TYPENAME##_getSize(AppState* appState, ArrayOf##TYPENAME* this) { \
    return this->usedElements; \
} \
void ArrayOf##TYPENAME##_qsort(AppState* appState, ArrayOf##TYPENAME* this, int (*comparingFunction)(const TYPENAME**, const TYPENAME**)) { \
    /* \
    void qsort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *)); \
    compar: <0, 0, >0
    */ \
    qsort(this->vector, this->usedElements, sizeof(TYPENAME*), (int(*)(const void*, const void*))comparingFunction); \
} \
\
void ArrayOf##TYPENAME##_print(AppState* appState, ArrayOf##TYPENAME* this, const char *printFormat) { \
    unsigned int i; \
    char *printFormatWithSpace = malloc(sizeof(char) * strlen(printFormat) + 2); \
    sprintf(printFormatWithSpace, "%s ", printFormat); \
    for (i=0; i < this->usedElements; ++i) \
        printf(printFormatWithSpace, *(this->vector + i)); \
    printf("\n"); \
    free(printFormatWithSpace); \
} \
\
unsigned int ArrayOf##TYPENAME##_findIndex(AppState *appState, ArrayOf##TYPENAME* this, const TYPENAME* elementPointer, int (*comparingFunction)(const TYPENAME**, const TYPENAME**)) { \
    unsigned int i; \
    for (i = 0; i < this->usedElements; ++i) \
        if ((comparingFunction)((const TYPENAME**)this->vector + i, (const TYPENAME**)&elementPointer) == 0) \
            return i; \
    AppState_throwException(appState, Exception__new(Severity_none, ExceptionID_ElementNotFound, "")); \
    return 0; \
} \
\
TYPENAME* ArrayOf##TYPENAME##_find(AppState* appState, ArrayOf##TYPENAME* this, const TYPENAME* elementPointer, int (*comparingFunction)(const TYPENAME**, const TYPENAME**)) { \
    unsigned int index = ArrayOf##TYPENAME##_findIndex(appState, this, elementPointer, comparingFunction); \
    if (AppState_isExceptionRaisedWithID(appState, ExceptionID_ElementNotFound)) \
        return NULL; \
    else \
        return this->vector[index]; \
} \
\
ArrayOf##TYPENAME* ArrayOf##TYPENAME##_map(AppState* appState, ArrayOf##TYPENAME* this, int (*mapFunction)(TYPENAME*)) { \
    unsigned int i; \
    ArrayOf##TYPENAME* that = ArrayOf##TYPENAME##_clone(appState, this); \
    if (AppState_isExceptionRaised(appState)) \
        return NULL; \
    for (i = 0; i < that->usedElements; ++i) \
        (mapFunction)((that->vector + i)); \
    return that; \
} \
        

/* type definition */

#define Array(TYPENAME) ArrayOf##TYPENAME


/* callers */

#define Array__new(appState, TYPENAME, initialCapacity) ArrayOf##TYPENAME##__new((appState), (initialCapacity))
#define Array_clone(appState, TYPENAME, array) ArrayOf##TYPENAME##_clone((appState), (array))
#define Array_delete(appState, TYPENAME, array) ArrayOf##TYPENAME##_delete((appState), (array))
#define Array_deleteValues(appState, TYPENAME, array) ArrayOf##TYPENAME##_deleteValues((appState), (array))
#define Array_add(appState, TYPENAME, array, value) ArrayOf##TYPENAME##_add((appState), (array), (value))
#define Array_getValueAt(appState, TYPENAME, array, at) ArrayOf##TYPENAME##_getValueAt((appState), (array), (at))
#define Array_push Array_add
#define Array_pop(appState, TYPENAME, array) ArrayOf##TYPENAME##_pop((appState), (array))
#define Array_getCapacity(appState, TYPENAME, array) ArrayOf##TYPENAME##_getCapacity((appState), (array))
#define Array_getSize(appState, TYPENAME, array) ArrayOf##TYPENAME##_getSize((appState), (array))
#define Array_shift(appState, TYPENAME, array) ArrayOf##TYPENAME##_shift((appState), (array))
#define Array_unshift(appState, TYPENAME, array, value) ArrayOf##TYPENAME##_unshift((appState), (array), (value))
#define Array_insertValueAt(appState, TYPENAME, array, value, at) ArrayOf##TYPENAME##_insertValueAt((appState), (array), (value), (at))
#define Array_removeValueAt(appState, TYPENAME, array, at) ArrayOf##TYPENAME##_removeValueAt((appState), (array), (at))
#define Array_qsort(appState, TYPENAME, array, comparingFunction) ArrayOf##TYPENAME##_qsort((appState), (array), (comparingFunction))
#define Array_qsort_r(appState, TYPENAME, array, comparingFunction) ArrayOf##TYPENAME##_qsort_r((appState), (array), (comparingFunction))
#define Array_print(appState, TYPENAME, array, printFormat) ArrayOf##TYPENAME##_print((appState), (array), (printFormat))
#define Array_findIndex(appState, TYPENAME, array, elementPointer, comparingFunction) ArrayOf##TYPENAME##_findIndex((appState), (array), (elementPointer), (comparingFunction))
#define Array_find(appState, TYPENAME, array, elementPointer, comparingFunction) ArrayOf##TYPENAME##_find((appState), (array), (elementPointer), (comparingFunction))
#define Array_map(appState, TYPENAME, array, mapFunction) ArrayOf##TYPENAME##_map((appState), (array), (mapFunction))


#endif 
