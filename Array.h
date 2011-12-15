#ifndef _ARRAY_H
#define _ARRAY_H

#include<stdlib.h>

#define INIT_ARRAY(ELEMENTTYPE, READABLETYPE) \
typedef struct { \
    (ELEMENTTYPE)* vector; \
    unsigned int usedElements; \
    unsigned int capacityElements; \
} Array; \
 \
Array* Array__new_READABLETYPE(const unsigned int initialCapacity) { \
    Array* this = malloc(sizeof(*this)); \
    assert(this != NULL); /* TODO error call */ \
    if (this != NULL) { \
        this->usedElements = 0; \
        this->capacityElements = initialCapacity; \
        this->vector = malloc(sizeof((ELEMENTTYPE)) * initialCapacity); \
    } \
    return this; \
} 

#define Array__new(READABLETYPE, initialCapacity) Array__new_READABLETYPE((initialCapacity))


#endif
