/*
    =====================================================================
    CGenerics - Datatypes and Functions for Generic and OO Programming in C

    Copyright (C) 2012  Christian Friedl

    This file is part of CGenerics.

    CGenerics is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    CGenerics is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    =====================================================================
*/

#ifndef _CGARRAY_H
#define _CGARRAY_H

/* NOMAKEMAN */

#include<stdlib.h>
#include<string.h>
#include<stdarg.h>
#include"cgAppState.h"

#define MAX_GROWTH_COUNT 65536

/** 
    calculate the needed element count from the current given count, the requested count, and the maximum size to grow per iteration
    - up to the maximum growth size count, we double the size each time
*/
static unsigned int calculateNeededElementCount(unsigned int currentCount, const unsigned int requested,
                                                const unsigned int maxGrowthCount) {
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
    This will init the cgArray for one typename
    NOTE: TYPENAME is a valid identifier; if you plan for a, say, cgArray<int*>, then do a typedef int* intPtr or the like...
*/

#define DECLARE_ARRAY_TYPE(TYPENAME) \
typedef struct { \
    TYPENAME** vector; \
    unsigned int usedElements; /* the size of the array */ \
    unsigned int capacityElements; /* the currently possible maximum size of the array */ \
} cgArrayOf##TYPENAME; \

#define DECLARE_ARRAY_FUNCS(TYPENAME) \
    cgArrayOf##TYPENAME* cgArrayOf##TYPENAME##__new(const unsigned int initialCapacity); \
    cgArrayOf##TYPENAME* cgArrayOf##TYPENAME##__newFromInitializerList(TYPENAME* item, ...); \
    void cgArrayOf##TYPENAME##_delete(cgArrayOf##TYPENAME* this); \
    void cgArrayOf##TYPENAME##_deleteValues(cgArrayOf##TYPENAME* this); \
    cgArrayOf##TYPENAME* cgArrayOf##TYPENAME##_clone(cgArrayOf##TYPENAME* this); \
    void cgArrayOf##TYPENAME##_delete(cgArrayOf##TYPENAME* this); \
    void cgArrayOf##TYPENAME##_grow_(cgArrayOf##TYPENAME* this, unsigned int requestedCapacity); \
    TYPENAME* cgArrayOf##TYPENAME##_add(cgArrayOf##TYPENAME* this, TYPENAME* value); \
    void cgArrayOf##TYPENAME##_append(cgArrayOf##TYPENAME* this, cgArrayOf##TYPENAME* that); \
    TYPENAME* cgArrayOf##TYPENAME##_getValueAt(cgArrayOf##TYPENAME* this, const unsigned int at); \
    TYPENAME* cgArrayOf##TYPENAME##_pop(cgArrayOf##TYPENAME* this); \
    TYPENAME* cgArrayOf##TYPENAME##_shift(cgArrayOf##TYPENAME* this); \
    void cgArrayOf##TYPENAME##_unshift(cgArrayOf##TYPENAME* this, TYPENAME* value); \
    void cgArrayOf##TYPENAME##_insertValueAtAfterEnd_(cgArrayOf##TYPENAME* this, TYPENAME* value, const unsigned int at); \
    void cgArrayOf##TYPENAME##_insertValueAt(cgArrayOf##TYPENAME* this, TYPENAME* value, const unsigned int at); \
    TYPENAME* cgArrayOf##TYPENAME##_removeValueAt(cgArrayOf##TYPENAME* this, unsigned int at); \
    unsigned int cgArrayOf##TYPENAME##_getCapacity(cgArrayOf##TYPENAME* this); \
    unsigned int cgArrayOf##TYPENAME##_getSize(cgArrayOf##TYPENAME* this); \
    void cgArrayOf##TYPENAME##_qsort(cgArrayOf##TYPENAME* this, int (*comparingFunction)(const TYPENAME**, const TYPENAME**)); \
    void cgArrayOf##TYPENAME##_print(cgArrayOf##TYPENAME* this, const char *printFormat); \
    unsigned int cgArrayOf##TYPENAME##_findIndex(cgArrayOf##TYPENAME* this, const TYPENAME* elementPointer, int (*comparingFunction)(const TYPENAME**, const TYPENAME**)); \
    TYPENAME* cgArrayOf##TYPENAME##_find(cgArrayOf##TYPENAME* this, const TYPENAME* elementPointer, int (*comparingFunction)(const TYPENAME**, const TYPENAME**)); \
    cgArrayOf##TYPENAME* cgArrayOf##TYPENAME##_map(cgArrayOf##TYPENAME* this, void (*mapFunction)(TYPENAME*, void *), void* userData); \
    bool cgArrayOf##TYPENAME##_mapConstant(cgArrayOf##TYPENAME* this, bool (*mapFunction)(const TYPENAME*, void*), void* userData); \

#define DEFINE_ARRAY_FUNCS(TYPENAME) \
    \
    cgArrayOf##TYPENAME* cgArrayOf##TYPENAME##__new(const unsigned int initialCapacity) { \
        cgArrayOf##TYPENAME* this = malloc(sizeof(*this)); \
        if (this != NULL) { \
            this->usedElements = 0; \
            this->capacityElements = calculateNeededElementCount(1, initialCapacity, MAX_GROWTH_COUNT); \
            this->vector = malloc(sizeof(TYPENAME*) * this->capacityElements); \
            if (this->vector == NULL) \
                cgAppState_THROW(cgAppState__getInstance(), Severity_error, cgExceptionID_CannotAllocate, "cannot allocate cgArray"); \
        } else \
            cgAppState_THROW(cgAppState__getInstance(), Severity_error, cgExceptionID_CannotAllocate, "cannot allocate cgArray"); \
        return this; \
    } \
    \
    /**
        this expects a sentinel parameter (NULL) at the end of the initializer list
    */ \
    cgArrayOf##TYPENAME* cgArrayOf##TYPENAME##__newFromInitializerList(TYPENAME* item, ...) { \
        cgArrayOf##TYPENAME* this = cgArrayOf##TYPENAME##__new(2); \
        if (this != NULL) { \
            va_list args; \
            va_start(args, item); \
            while (item != NULL) { \
                cgAppState_catchAndDeleteException(cgAppState__getInstance()); \
                cgArrayOf##TYPENAME##_add(this, item); \
                if (cgAppState_isExceptionRaised(cgAppState__getInstance())) { \
                    printf("warning - exception %s\n", cgException_getMsg(cgAppState_getException(cgAppState__getInstance()))); \
                    break; \
                } \
                item = va_arg(args, TYPENAME*); \
            } \
            va_end(args); \
        } \
        return this; \
    } \
    \
    void cgArrayOf##TYPENAME##_delete(cgArrayOf##TYPENAME* this); \
    cgArrayOf##TYPENAME* cgArrayOf##TYPENAME##_clone(cgArrayOf##TYPENAME* this) { \
        cgArrayOf##TYPENAME* that = cgArrayOf##TYPENAME##__new(this->capacityElements); \
        if (cgAppState_isExceptionRaisedWithID(cgAppState__getInstance(), cgExceptionID_CannotAllocate)) \
            return NULL; \
        unsigned int i; \
        for (i=0; i < this->usedElements; ++i) { \
            *(that->vector + i) = TYPENAME##_clone(*(this->vector + i)); \
            if (cgAppState_isExceptionRaised(cgAppState__getInstance())) { \
                cgArrayOf##TYPENAME##_delete(that); \
                return NULL; \
            } \
        } \
        that->usedElements = this->usedElements; \
        return that; \
    } \
    \
    void cgArrayOf##TYPENAME##_delete(cgArrayOf##TYPENAME* this) { \
        free(this->vector); \
        free(this); \
    } \
    \
    void TYPENAME##_delete(TYPENAME* this); \
    void cgArrayOf##TYPENAME##_deleteValues(cgArrayOf##TYPENAME* this) { \
        unsigned int i; \
        for (i=0; i < this->usedElements; ++i) \
            TYPENAME##_delete(*(this->vector + i)); \
    } \
    \
    void cgArrayOf##TYPENAME##_grow_(cgArrayOf##TYPENAME* this, unsigned int requestedCapacity) { \
        unsigned int newCapacity = calculateNeededElementCount(this->capacityElements, requestedCapacity, MAX_GROWTH_COUNT); \
        this->vector = realloc(this->vector, sizeof(TYPENAME*) * newCapacity); \
        if (this->vector == NULL) \
            cgAppState_THROW(cgAppState__getInstance(), Severity_error, cgExceptionID_CannotAllocate, "cannot allocate cgArray"); \
        else \
            this->capacityElements = newCapacity; \
    } \
    \
    TYPENAME* cgArrayOf##TYPENAME##_add(cgArrayOf##TYPENAME* this, TYPENAME* value) { \
        if (this->usedElements == this->capacityElements) \
            cgArrayOf##TYPENAME##_grow_(this, this->capacityElements + 1); \
        *(this->vector + this->usedElements) = value; \
        ++(this->usedElements); \
        return value; \
    } \
    \
    void cgArrayOf##TYPENAME##_append(cgArrayOf##TYPENAME* this, cgArrayOf##TYPENAME* that) { \
        if (this->usedElements + that->usedElements >= this->capacityElements) \
            cgArrayOf##TYPENAME##_grow_(this, this->usedElements + that->usedElements); \
        memmove(this->vector + this->usedElements, that->vector, (that->usedElements * sizeof(TYPENAME*))); \
        this->usedElements += that->usedElements; \
    } \
    \
    TYPENAME* cgArrayOf##TYPENAME##_getValueAt(cgArrayOf##TYPENAME* this, const unsigned int at) { \
        if (at >= this->usedElements) { \
            cgAppState_THROW(cgAppState__getInstance(), Severity_error, cgExceptionID_ArrayIndexOutOfBounds, "cannot get value beyond array end (requested position: %u)", at); \
            return *(this->vector); \
        } \
        return *(this->vector + at); \
    } \
    \
    TYPENAME* cgArrayOf##TYPENAME##_pop(cgArrayOf##TYPENAME* this) { \
        if (this->usedElements == 0) { \
            cgAppState_THROW(cgAppState__getInstance(), Severity_error, cgExceptionID_ArrayIndexOutOfBounds, "cannot pop from empty array"); \
            return *(this->vector); \
        } \
        --this->usedElements; \
        return *(this->vector + this->usedElements); \
    } \
    \
    TYPENAME* cgArrayOf##TYPENAME##_shift(cgArrayOf##TYPENAME* this) { \
        if (this->usedElements == 0) {\
            cgAppState_THROW(cgAppState__getInstance(), Severity_error, cgExceptionID_ArrayIndexOutOfBounds, "cannot shift from empty array"); \
            return *(this->vector); \
        } \
        TYPENAME* firstValue = *(this->vector); \
        --this->usedElements; \
        memmove(this->vector, (this->vector + 1), sizeof(TYPENAME*) * this->usedElements); \
        return firstValue; \
    } \
    \
    void cgArrayOf##TYPENAME##_unshift(cgArrayOf##TYPENAME* this, TYPENAME* value) { \
        if (this->usedElements == this->capacityElements) \
            cgArrayOf##TYPENAME##_grow_(this, this->capacityElements + 1); \
        memmove((this->vector + 1), this->vector, sizeof(TYPENAME*) * this->usedElements); \
        *(this->vector) = value; \
        ++this->usedElements; \
    } \
    \
    void cgArrayOf##TYPENAME##_insertValueAtAfterEnd_(cgArrayOf##TYPENAME* this, TYPENAME* value, const unsigned int at) { \
        unsigned int neededCapacityElements = max(at + 1, this->capacityElements); \
        cgArrayOf##TYPENAME##_grow_(this, neededCapacityElements); \
        *(this->vector + at) = value; \
        this->usedElements = at + 1; \
    } \
    \
    void cgArrayOf##TYPENAME##_insertValueAt(cgArrayOf##TYPENAME* this, TYPENAME* value, const unsigned int at) { \
        if (at >= this->usedElements) { \
            cgArrayOf##TYPENAME##_insertValueAtAfterEnd_(this, value, at); \
        } else {\
            if (this->usedElements == this->capacityElements) \
                cgArrayOf##TYPENAME##_grow_(this, this->capacityElements + 1); \
            memmove((this->vector + at + 1), (this->vector + at), sizeof(TYPENAME*) * (this->usedElements - at)); \
            *(this->vector + at) = value; \
            ++this->usedElements; \
        } \
    } \
    \
    TYPENAME* cgArrayOf##TYPENAME##_removeValueAt(cgArrayOf##TYPENAME* this, unsigned int at) { \
        if (at >= this->usedElements) { \
            cgAppState_THROW(cgAppState__getInstance(), Severity_error, cgExceptionID_ArrayIndexOutOfBounds, "cannot remove value beyond array end"); \
            return *(this->vector); \
        } \
        TYPENAME* value = *(this->vector + at); \
        --this->usedElements; \
        memmove((this->vector + at), (this->vector + at + 1), sizeof(TYPENAME*) * (this->usedElements - at)); \
        return value; \
    } \
    \
    unsigned int cgArrayOf##TYPENAME##_getCapacity(cgArrayOf##TYPENAME* this) { \
        return this->capacityElements; \
    } \
    \
    unsigned int cgArrayOf##TYPENAME##_getSize(cgArrayOf##TYPENAME* this) { \
        return this->usedElements; \
    } \
    void cgArrayOf##TYPENAME##_qsort(cgArrayOf##TYPENAME* this, int (*comparingFunction)(const TYPENAME**, const TYPENAME**)) { \
        /* \
        void qsort(void *base, size_t nel, size_t width, int (*compar)(const void *, const void *)); \
        compar: <0, 0, >0
        */ \
        qsort(this->vector, this->usedElements, sizeof(TYPENAME*), (int(*)(const void*, const void*))comparingFunction); \
    } \
    \
    void cgArrayOf##TYPENAME##_print(cgArrayOf##TYPENAME* this, const char *printFormat) { \
        unsigned int i; \
        char *printFormatWithSpace = malloc(sizeof(char) * strlen(printFormat) + 2); \
        sprintf(printFormatWithSpace, "%s ", printFormat); \
        for (i=0; i < this->usedElements; ++i) \
            printf(printFormatWithSpace, *(this->vector + i)); \
        printf("\n"); \
        free(printFormatWithSpace); \
    } \
    \
    unsigned int cgArrayOf##TYPENAME##_findIndex(cgArrayOf##TYPENAME* this, const TYPENAME* elementPointer, int (*comparingFunction)(const TYPENAME**, const TYPENAME**)) { \
        cgAppState_catchAndDeleteExceptionWithID(cgAppState__getInstance(), cgExceptionID_ElementNotFound); \
        unsigned int i; \
        for (i = 0; i < this->usedElements; ++i) \
            if ((comparingFunction)((const TYPENAME**)this->vector + i, (const TYPENAME**)&elementPointer) == 0) \
                return i; \
        cgAppState_THROW(cgAppState__getInstance(), Severity_none, cgExceptionID_ElementNotFound, NULL); \
        return 0; \
    } \
    \
    TYPENAME* cgArrayOf##TYPENAME##_find(cgArrayOf##TYPENAME* this, const TYPENAME* elementPointer, int (*comparingFunction)(const TYPENAME**, const TYPENAME**)) { \
        cgAppState_catchAndDeleteExceptionWithID(cgAppState__getInstance(), cgExceptionID_ElementNotFound); \
        unsigned int index = cgArrayOf##TYPENAME##_findIndex(this, elementPointer, comparingFunction); \
        if (cgAppState_isExceptionRaisedWithID(cgAppState__getInstance(), cgExceptionID_ElementNotFound)) \
            return NULL; \
        else \
            return this->vector[index]; \
    } \
    \
    cgArrayOf##TYPENAME* cgArrayOf##TYPENAME##_map(cgArrayOf##TYPENAME* this, void (*mapFunction)(TYPENAME*, void *), void* userData) { \
        unsigned int i; \
        cgArrayOf##TYPENAME* that = cgArrayOf##TYPENAME##_clone(this); \
        if (cgAppState_isExceptionRaised(cgAppState__getInstance())) \
            return NULL; \
        for (i = 0; i < that->usedElements; ++i) \
            (mapFunction)(*(that->vector + i), userData); \
        return that; \
    } \
    \
    bool cgArrayOf##TYPENAME##_mapConstant(cgArrayOf##TYPENAME* this, bool (*mapFunction)(const TYPENAME*, void *), void* userData) { \
        unsigned int i; \
        for (i = 0; i < this->usedElements; ++i) \
            if ((mapFunction)(*(this->vector + i), userData) != true) \
                return false; \
        return true; \
    } \
    \

#define DECLARE_ARRAY(TYPENAME) \
    DECLARE_ARRAY_TYPE(TYPENAME) \
    DECLARE_ARRAY_FUNCS(TYPENAME)

#define DEFINE_ARRAY(TYPENAME) \
    DEFINE_ARRAY_FUNCS(TYPENAME)

#define INIT_ARRAY(TYPENAME) \
    DECLARE_ARRAY(TYPENAME) \
    DEFINE_ARRAY(TYPENAME)

/* MAKEMAN */
/* type definition */

#define cgArray(TYPENAME) cgArrayOf##TYPENAME

/* callers */

#define cgArray__new(TYPENAME, initialCapacity) cgArrayOf##TYPENAME##__new((initialCapacity))
#define cgArray__newFromInitializerList(TYPENAME, ...) cgArrayOf##TYPENAME##__newFromInitializerList(__VA_ARGS__)
/**
 * cgArray_clone: returns a deep copy of the array
 */
#define cgArray_clone(TYPENAME, array) cgArrayOf##TYPENAME##_clone((array))
#define cgArray_delete(TYPENAME, array) cgArrayOf##TYPENAME##_delete((array))
#define cgArray_deleteValues(TYPENAME, array) cgArrayOf##TYPENAME##_deleteValues((array))
#define cgArray_add(TYPENAME, array, value) cgArrayOf##TYPENAME##_add((array), (value))
#define cgArray_append(TYPENAME, this, that) cgArrayOf##TYPENAME##_append((this), (that))
#define cgArray_getValueAt(TYPENAME, array, at) cgArrayOf##TYPENAME##_getValueAt((array), (at))
#define cgArray_push cgArray_add
#define cgArray_pop(TYPENAME, array) cgArrayOf##TYPENAME##_pop((array))
#define cgArray_getCapacity(TYPENAME, array) cgArrayOf##TYPENAME##_getCapacity((array))
#define cgArray_getSize(TYPENAME, array) cgArrayOf##TYPENAME##_getSize((array))
#define cgArray_shift(TYPENAME, array) cgArrayOf##TYPENAME##_shift((array))
#define cgArray_unshift(TYPENAME, array, value) cgArrayOf##TYPENAME##_unshift((array), (value))
#define cgArray_insertValueAt(TYPENAME, array, value, at) cgArrayOf##TYPENAME##_insertValueAt((array), (value), (at))
#define cgArray_removeValueAt(TYPENAME, array, at) cgArrayOf##TYPENAME##_removeValueAt((array), (at))
#define cgArray_qsort(TYPENAME, array, comparingFunction) cgArrayOf##TYPENAME##_qsort((array), (comparingFunction))
#define cgArray_qsort_r(TYPENAME, array, comparingFunction) cgArrayOf##TYPENAME##_qsort_r((array), (comparingFunction))
#define cgArray_print(TYPENAME, array, printFormat) cgArrayOf##TYPENAME##_print((array), (printFormat))
#define cgArray_findIndex(TYPENAME, array, elementPointer, comparingFunction) cgArrayOf##TYPENAME##_findIndex((array), (elementPointer), (comparingFunction))
#define cgArray_find(TYPENAME, array, elementPointer, comparingFunction) cgArrayOf##TYPENAME##_find((array), (elementPointer), (comparingFunction))
#define cgArray_map(TYPENAME, array, mapFunction, userData) cgArrayOf##TYPENAME##_map((array), (mapFunction), (userData))
#define cgArray_mapConstant(TYPENAME, array, mapFunction, userData) cgArrayOf##TYPENAME##_mapConstant((array), (mapFunction), (userData))
#endif
