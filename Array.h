#ifndef _ARRAY_H
#define _ARRAY_H

#include<stdlib.h>

#ifndef min
    #define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

#define MAX_GROWTH_COUNT 65536

/** 
    calculate the needed element count from the current given count, the requested count, and the maximum size to grow per iteration
    - up to the maximum growth size count, we double the size each time
*/
unsigned int calculateNeededElementCount(unsigned int currentCount, const unsigned int requested, const unsigned int maxGrowthCount) {
    while (currentCount < requested)
        if (currentCount < maxGrowthCount)
            currentCount = currentCount << 1;
        else
            currentCount = currentCount + maxGrowthCount;
    return currentCount;
}

#endif 

/* everything below this line is type-specific! */

/* declarations */


#define INIT_ARRAY(ELEMENTTYPE, READABLETYPE) \
typedef struct { \
    ELEMENTTYPE* vector; \
    unsigned int usedElements; \
    unsigned int capacityElements; \
} Array##READABLETYPE; \
 \
Array##READABLETYPE* Array##READABLETYPE##__new(const unsigned int initialCapacity) { \
    Array##READABLETYPE* this = malloc(sizeof(*this)); \
    assert(this != NULL); \
    /* TODO error call */ \
    if (this != NULL) { \
        this->usedElements = 0; \
        this->capacityElements = calculateNeededElementCount(1, initialCapacity, MAX_GROWTH_COUNT); \
        this->vector = malloc(sizeof(ELEMENTTYPE) * initialCapacity); \
        /* TODO error */ \
    } \
    return this; \
} \
\
void Array##READABLETYPE##_delete(Array##READABLETYPE* this) { \
    free(this->vector); \
    free(this); \
} \
\
void Array##READABLETYPE##_grow_(Array##READABLETYPE* this, unsigned int requestedCapacity) { \
    unsigned int newCapacity = calculateNeededElementCount(this->capacityElements, requestedCapacity, MAX_GROWTH_COUNT); \
    this->vector = realloc(this->vector, sizeof(ELEMENTTYPE) * newCapacity); \
        /* TODO error */ \
    this->capacityElements = newCapacity; \
} \
\
ELEMENTTYPE Array##READABLETYPE##_add(Array##READABLETYPE* this, ELEMENTTYPE value) { \
    if (this->usedElements == this->capacityElements) \
        Array##READABLETYPE##_grow_(this, this->capacityElements + 1); \
    *(this->vector + this->usedElements) = value; \
    ++(this->usedElements); \
    return value; \
} \
\
ELEMENTTYPE Array##READABLETYPE##_getValueAt(Array##READABLETYPE* this, const unsigned int at) { \
    if (at >= this->usedElements) \
        exit(1); /* TODO errors */ \
    return *(this->vector + at); \
} \
\
ELEMENTTYPE Array##READABLETYPE##_pop(Array##READABLETYPE* this) { \
    if (this->usedElements == 0) \
        exit(1); /* TODO errors */ \
    --this->usedElements; \
    return *(this->vector + this->usedElements); \
} \
\
unsigned int Array##READABLETYPE##_getCapacity(Array##READABLETYPE* this) { \
    return this->capacityElements; \
} \
\
unsigned int Array##READABLETYPE##_getSize(Array##READABLETYPE* this) { \
    return this->usedElements; \
} \


/* type definition */

#define Array(READABLETYPE) Array##READABLETYPE


/* callers */

#define Array__new(READABLETYPE, initialCapacity) Array##READABLETYPE##__new((initialCapacity))
#define Array_delete(READABLETYPE, array) Array##READABLETYPE##_delete((array))
#define Array_add(READABLETYPE, array, value) Array##READABLETYPE##_add((array), (value))
#define Array_getValueAt(READABLETYPE, array, at) Array##READABLETYPE##_getValueAt((array), (at))
#define Array_push Array_add
#define Array_pop(READABLETYPE, array) Array##READABLETYPE##_pop((array))
#define Array_getCapacity(READABLETYPE, array) Array##READABLETYPE##_getCapacity((array))
#define Array_getSize(READABLETYPE, array) Array##READABLETYPE##_getSize((array))


