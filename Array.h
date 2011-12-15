#ifndef _ARRAY_H
#define _ARRAY_H

#include<stdlib.h>

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
ArrayOf##TYPENAME* ArrayOf##TYPENAME##__new(const unsigned int initialCapacity) { \
    ArrayOf##TYPENAME* this = malloc(sizeof(*this)); \
    assert(this != NULL); \
    /* TODO error call */ \
    if (this != NULL) { \
        this->usedElements = 0; \
        this->capacityElements = calculateNeededElementCount(1, initialCapacity, MAX_GROWTH_COUNT); \
        this->vector = malloc(sizeof(TYPENAME) * initialCapacity); \
        /* TODO error */ \
    } \
    return this; \
} \
\
void ArrayOf##TYPENAME##_delete(ArrayOf##TYPENAME* this) { \
    free(this->vector); \
    free(this); \
} \
\
void ArrayOf##TYPENAME##_grow_(ArrayOf##TYPENAME* this, unsigned int requestedCapacity) { \
    unsigned int newCapacity = calculateNeededElementCount(this->capacityElements, requestedCapacity, MAX_GROWTH_COUNT); \
    this->vector = realloc(this->vector, sizeof(TYPENAME) * newCapacity); \
        /* TODO error */ \
    this->capacityElements = newCapacity; \
} \
\
TYPENAME ArrayOf##TYPENAME##_add(ArrayOf##TYPENAME* this, TYPENAME value) { \
    if (this->usedElements == this->capacityElements) \
        ArrayOf##TYPENAME##_grow_(this, this->capacityElements + 1); \
    *(this->vector + this->usedElements) = value; \
    ++(this->usedElements); \
    return value; \
} \
\
TYPENAME ArrayOf##TYPENAME##_getValueAt(ArrayOf##TYPENAME* this, const unsigned int at) { \
    if (at >= this->usedElements) \
        exit(1); /* TODO errors */ \
    return *(this->vector + at); \
} \
\
TYPENAME ArrayOf##TYPENAME##_pop(ArrayOf##TYPENAME* this) { \
    if (this->usedElements == 0) \
        exit(1); /* TODO errors */ \
    --this->usedElements; \
    return *(this->vector + this->usedElements); \
} \
\
unsigned int ArrayOf##TYPENAME##_getCapacity(ArrayOf##TYPENAME* this) { \
    return this->capacityElements; \
} \
\
unsigned int ArrayOf##TYPENAME##_getSize(ArrayOf##TYPENAME* this) { \
    return this->usedElements; \
} \


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
#define Array_shift(TYPENAME, array) assert(1==0)
#define Array_unshift(TYPENAME, array, value) assert(1==0)
#define Array_insertValueAt(TYPENAME, array, value, at) assert(1==0)
#define Array_removeValueAt(TYPENAME, array, value, at) assert(1==0)


