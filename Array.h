#ifndef _ARRAY_H
#define _ARRAY_H

#include<stdlib.h>
#include<string.h>
#include"AppState.h"

#define ExceptionID_ArrayIndexOutOfBounds (100)

#ifndef min
    #define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

#ifndef max
    #define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif


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
    TYPENAME* vector; \
    unsigned int usedElements; /* the size of the array */ \
    unsigned int capacityElements; /* the currently possible maximum size of the array */ \
} ArrayOf##TYPENAME; \
\
ArrayOf##TYPENAME* ArrayOf##TYPENAME##__new(AppState* appState, const unsigned int initialCapacity) { \
    ArrayOf##TYPENAME* this = malloc(sizeof(*this)); \
    assert(this != NULL); \
    /* TODO error call */ \
    if (this != NULL) { \
        this->usedElements = 0; \
        this->capacityElements = calculateNeededElementCount(appState, 1, initialCapacity, MAX_GROWTH_COUNT); \
        this->vector = malloc(sizeof(TYPENAME) * initialCapacity); \
        /* TODO error */ \
    } \
    return this; \
} \
\
void ArrayOf##TYPENAME##_delete(AppState* appState, ArrayOf##TYPENAME* this) { \
    free(this->vector); \
    free(this); \
} \
\
void ArrayOf##TYPENAME##_grow_(AppState* appState, ArrayOf##TYPENAME* this, unsigned int requestedCapacity) { \
    unsigned int newCapacity = calculateNeededElementCount(appState, this->capacityElements, requestedCapacity, MAX_GROWTH_COUNT); \
    this->vector = realloc(this->vector, sizeof(TYPENAME) * newCapacity); \
        /* TODO error */ \
    this->capacityElements = newCapacity; \
} \
\
TYPENAME ArrayOf##TYPENAME##_add(AppState* appState, ArrayOf##TYPENAME* this, TYPENAME value) { \
    if (this->usedElements == this->capacityElements) \
        ArrayOf##TYPENAME##_grow_(appState, this, this->capacityElements + 1); \
    *(this->vector + this->usedElements) = value; \
    ++(this->usedElements); \
    return value; \
} \
\
TYPENAME ArrayOf##TYPENAME##_getValueAt(AppState* appState, ArrayOf##TYPENAME* this, const unsigned int at) { \
    if (at >= this->usedElements) \
        exit(1); /* TODO errors */ \
    return *(this->vector + at); \
} \
\
TYPENAME ArrayOf##TYPENAME##_pop(AppState* appState, ArrayOf##TYPENAME* this) { \
    if (this->usedElements == 0) \
        exit(1); /* TODO errors */ \
    --this->usedElements; \
    return *(this->vector + this->usedElements); \
} \
\
TYPENAME ArrayOf##TYPENAME##_shift(AppState* appState, ArrayOf##TYPENAME* this) { \
    if (this->usedElements == 0) \
        exit(1); /* TODO errors */ \
    TYPENAME firstValue = *(this->vector); \
    --this->usedElements; \
    memmove(this->vector, (this->vector + 1), sizeof(TYPENAME) * this->usedElements); \
    return firstValue; \
} \
\
void ArrayOf##TYPENAME##_unshift(AppState* appState, ArrayOf##TYPENAME* this, TYPENAME value) { \
    if (this->usedElements == this->capacityElements) \
        ArrayOf##TYPENAME##_grow_(appState, this, this->capacityElements + 1); \
    memmove((this->vector + 1), this->vector, sizeof(TYPENAME) * this->usedElements); \
    *(this->vector) = value; \
    ++this->usedElements; \
} \
\
void ArrayOf##TYPENAME##_insertValueAt(AppState* appState, ArrayOf##TYPENAME* this, TYPENAME value, unsigned int at) { \
    if (this->usedElements == this->capacityElements) \
        ArrayOf##TYPENAME##_grow_(appState, this, this->capacityElements + 1); \
    memmove((this->vector + at + 1), (this->vector + at), sizeof(TYPENAME) * (this->usedElements - at)); \
    *(this->vector + at) = value; \
    ++this->usedElements; \
} \
\
TYPENAME ArrayOf##TYPENAME##_removeValueAt(AppState* appState, ArrayOf##TYPENAME* this, unsigned int at) { \
    if (this->usedElements == 0) {\
        AppState_throwException(appState, Exception__new(Sincerety_error, ExceptionID_ArrayIndexOutOfBounds, "cannot remove value beyond array end")); \
        return *(this->vector); \
    } \
    TYPENAME value = *(this->vector + at); \
    --this->usedElements; \
    memmove((this->vector + at), (this->vector + at + 1), sizeof(TYPENAME) * (this->usedElements - at)); \
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


/* type definition */

#define Array(TYPENAME) ArrayOf##TYPENAME


/* callers */

#define Array__new(TYPENAME, initialCapacity) ArrayOf##TYPENAME##__new(appState, (initialCapacity))
#define Array_delete(TYPENAME, array) ArrayOf##TYPENAME##_delete(appState, (array))
#define Array_add(TYPENAME, array, value) ArrayOf##TYPENAME##_add(appState, (array), (value))
#define Array_getValueAt(TYPENAME, array, at) ArrayOf##TYPENAME##_getValueAt(appState, (array), (at))
#define Array_push Array_add
#define Array_pop(TYPENAME, array) ArrayOf##TYPENAME##_pop(appState, (array))
#define Array_getCapacity(TYPENAME, array) ArrayOf##TYPENAME##_getCapacity(appState, (array))
#define Array_getSize(TYPENAME, array) ArrayOf##TYPENAME##_getSize(appState, (array))
#define Array_shift(TYPENAME, array) ArrayOf##TYPENAME##_shift(appState, (array))
#define Array_unshift(TYPENAME, array, value) ArrayOf##TYPENAME##_unshift(appState, (array), (value))
#define Array_insertValueAt(TYPENAME, array, value, at) ArrayOf##TYPENAME##_insertValueAt(appState, (array), (value), (at))
#define Array_removeValueAt(TYPENAME, array, at) ArrayOf##TYPENAME##_removeValueAt(appState, (array), (at))


#endif 
