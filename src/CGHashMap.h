#ifndef _CG_HASH_MAP_H
#define _CG_HASH_MAP_H

/* NOMAKEMAN */

#include<stdlib.h>
#include<stdarg.h>
#include<stdint.h>
#include"debug.h"
#include"CGAppState.h"
#include"CGArray.h"

uint32_t hashlittle( const void *key, size_t length, uint32_t initval);

#define CG_HASH_MAP_BUCKETS (256)
#define CG_HASH_MAP_SEED (13)


/* everything below this line is type-specific! */

/* declarations */

/** 
    NOTE: TYPENAME is a valid identifier; if you plan for a, say, CGHashMap<int*>, then do a typedef int* intPtr or the like...
*/

#define DECLARE_HASH_MAP_TYPE(TYPENAME1, TYPENAME2) \
typedef struct { \
    uint32_t seed; \
    CGArrayOfCGKVPairOf##TYPENAME1##TYPENAME2* buckets[CG_HASH_MAP_BUCKETS]; \
} CGHashMapOf##TYPENAME1##TYPENAME2;

#define DECLARE_HASH_MAP_FUNCS(TYPENAME1, TYPENAME2) \
    CGHashMapOf##TYPENAME1##TYPENAME2* CGHashMapOf##TYPENAME1##TYPENAME2##__new(); \
    void CGHashMapOf##TYPENAME1##TYPENAME2##_delete(CGHashMapOf##TYPENAME1##TYPENAME2* this); \

#define DEFINE_HASH_MAP_FUNCS(TYPENAME1, TYPENAME2) \
    \
    CGHashMapOf##TYPENAME1##TYPENAME2* CGHashMapOf##TYPENAME1##TYPENAME2##__new() { \
        CGHashMapOf##TYPENAME1##TYPENAME2* this = malloc(sizeof(*this)); \
        if (this != NULL) { \
            unsigned int i = 0; \
            for (i = 0; i < CG_HASH_MAP_BUCKETS; ++i) { \
                this->buckets[i] = NULL; \
            } \
        } else \
            CGAppState_THROW(CGAppState__getInstance(), Severity_error, CGExceptionID_CannotAllocate, "cannot allocate CGHashMap"); \
        return this; \
    } \
    \
    bool CGHashMapOf##TYPENAME1##TYPENAME2##_createBucket_(CGHashMapOf##TYPENAME1##TYPENAME2* this, unsigned int index) { \
        this->buckets[index] = CGArrayOfCGKVPairOf##TYPENAME1##TYPENAME2##__new(1); \
        if (CGAppState_isExceptionRaised(CGAppState__getInstance())) \
            return false; \
        return true; \
    } \
    \
    CGHashMapOf##TYPENAME1##TYPENAME2* CGHashMapOf##TYPENAME1##TYPENAME2##_clone(CGHashMapOf##TYPENAME1##TYPENAME2* this) { \
        CGHashMapOf##TYPENAME1##TYPENAME2* that = CGHashMapOf##TYPENAME1##TYPENAME2##__new(); \
        if (CGAppState_isExceptionRaisedWithID(CGAppState__getInstance(), CGExceptionID_CannotAllocate)) \
            return NULL; \
        unsigned int i=0; \
        /* NOTE: this implies that we actually do clone the objects in the Pairs, i.e. the original keys and values */ \
        for (i=0; i < CGArrayOfCGKVPairOf##TYPENAME1##TYPENAME2##_getSize(this->buckets); ++i) \
            that->buckets[i] = CGArrayOfCGKVPairOf##TYPENAME1##TYPENAME2##_clone(this->buckets[i]); \
        return that; \
    } \
    \
    void CGHashMapOf##TYPENAME1##TYPENAME2##_delete(CGHashMapOf##TYPENAME1##TYPENAME2* this) { \
        free(this); \
    } \
    \
    void TYPENAME1##_delete(TYPENAME1* this); void TYPENAME2##_delete(TYPENAME2* this); \
    void CGHashMapOf##TYPENAME1##TYPENAME2##_deleteValues(CGHashMapOf##TYPENAME1##TYPENAME2* this) { \
    } \
    \
    uint32_t CGHashMapOf##TYPENAME1##TYPENAME2##_getHashValue_(CGHashMapOf##TYPENAME1##TYPENAME2* this, TYPENAME1* key) { \
        return hashlittle(key, TYPENAME1##_getByteSize(key), CG_HASH_MAP_SEED) % CG_HASH_MAP_BUCKETS; \
    } \
    \
    void CGHashMapOf##TYPENAME1##TYPENAME2##_add(CGHashMapOf##TYPENAME1##TYPENAME2* this, TYPENAME1* key, TYPENAME2* value) { \
        CGKVPairOf##TYPENAME1##TYPENAME2* pair = CGKVPairOf##TYPENAME1##TYPENAME2##__new(key, value); \
        if (CGAppState_isExceptionRaised(CGAppState__getInstance())) \
            return; \
        uint32_t index = CGHashMapOf##TYPENAME1##TYPENAME2##_getHashValue_(this, key); \
        debugPrint("adding hash to bucket %u\n", index); \
        if (this->buckets[index] == NULL) { \
            if (CGHashMapOf##TYPENAME1##TYPENAME2##_createBucket_(this, index) != true) \
                return; \
        } \
        CGArrayOfCGKVPairOf##TYPENAME1##TYPENAME2##_add(this->buckets[index], pair); \
        debugPrint("bucket size of bucket %u is %u\n", index, CGArrayOfCGKVPairOf##TYPENAME1##TYPENAME2##_getSize(this->buckets[index])); \
        this->seed = index; \
    } \
    \
    TYPENAME2* CGHashMapOf##TYPENAME1##TYPENAME2##_getFirst(CGHashMapOf##TYPENAME1##TYPENAME2* this, TYPENAME1* key) { \
        uint32_t bIndex = CGHashMapOf##TYPENAME1##TYPENAME2##_getHashValue_(this, key); \
        debugPrint("will scan bucket %u\n", bIndex); \
        unsigned int aIndex = 0; \
        debugPrint("bucket size of bucket %u is %u\n", bIndex, CGArrayOfCGKVPairOf##TYPENAME1##TYPENAME2##_getSize(this->buckets[bIndex])); \
        for (aIndex = 0; aIndex < CGArrayOfCGKVPairOf##TYPENAME1##TYPENAME2##_getSize(this->buckets[bIndex]); ++aIndex) { \
            debugPrint("testing index %u of bucket %u\n", aIndex, bIndex); \
            if (TYPENAME1##_isEqual(CGKVPairOf##TYPENAME1##TYPENAME2##_getKey( \
                            CGArrayOfCGKVPairOf##TYPENAME1##TYPENAME2##_getValueAt(this->buckets[bIndex], aIndex)), \
                        key)) \
                return CGKVPairOf##TYPENAME1##TYPENAME2##_getValue(CGArrayOfCGKVPairOf##TYPENAME1##TYPENAME2##_getValueAt(this->buckets[bIndex], aIndex)); \
        } \
        return NULL; \
    } \
    \
    CGArrayOf##TYPENAME2* CGHashMapOf##TYPENAME1##TYPENAME2##_getAll(CGHashMapOf##TYPENAME1##TYPENAME2* this, TYPENAME1* key) { \
        CGArrayOf##TYPENAME2* values = CGArrayOf##TYPENAME2##__new(1); \
        uint32_t bIndex = CGHashMapOf##TYPENAME1##TYPENAME2##_getHashValue_(this, key); \
        debugPrint("will scan bucket %u\n", bIndex); \
        unsigned int aIndex = 0; \
        debugPrint("bucket size of bucket %u is %u\n", bIndex, CGArrayOfCGKVPairOf##TYPENAME1##TYPENAME2##_getSize(this->buckets[bIndex])); \
        for (aIndex = 0; aIndex < CGArrayOfCGKVPairOf##TYPENAME1##TYPENAME2##_getSize(this->buckets[bIndex]); ++aIndex) { \
            debugPrint("testing index %u of bucket %u\n", aIndex, bIndex); \
            if (TYPENAME1##_isEqual(CGKVPairOf##TYPENAME1##TYPENAME2##_getKey( \
                            CGArrayOfCGKVPairOf##TYPENAME1##TYPENAME2##_getValueAt(this->buckets[bIndex], aIndex)), \
                        key)) \
                CGArrayOf##TYPENAME2##_add(values, \
                        CGKVPairOf##TYPENAME1##TYPENAME2##_getValue( \
                            CGArrayOfCGKVPairOf##TYPENAME1##TYPENAME2##_getValueAt(this->buckets[bIndex], aIndex)) \
                        ); \
        } \
        if (CGArrayOf##TYPENAME2##_getSize(values) == 0) { \
            CGArrayOf##TYPENAME2##_delete(values); \
            values = NULL; \
        } \
        return values; \
    } \
    \
    CGArrayOf##TYPENAME1* CGHashMapOf##TYPENAME1##TYPENAME2##_getKeys(CGHashMapOf##TYPENAME1##TYPENAME2* this) { \
        CGArrayOf##TYPENAME1* results = CGArrayOf##TYPENAME1##__new(1); \
        uint32_t bIndex = 0; \
        unsigned int aIndex = 0; \
        for (bIndex = 0; bIndex < CG_HASH_MAP_BUCKETS; ++bIndex) \
            if (this->buckets[bIndex] != NULL) { \
                for (aIndex = 0; aIndex < CGArrayOfCGKVPairOf##TYPENAME1##TYPENAME2##_getSize(this->buckets[bIndex]); ++aIndex) \
                    CGArrayOf##TYPENAME1##_add(results, CGKVPairOf##TYPENAME1##TYPENAME2##_getKey( \
                            CGArrayOfCGKVPairOf##TYPENAME1##TYPENAME2##_getValueAt(this->buckets[bIndex], aIndex))); \
            } \
        if (CGArrayOf##TYPENAME1##_getSize(results) == 0) { \
            CGArrayOf##TYPENAME1##_delete(results); \
            results = NULL; \
        } \
        return results; \
    } \
    \
    CGArrayOf##TYPENAME2* CGHashMapOf##TYPENAME1##TYPENAME2##_getValues(CGHashMapOf##TYPENAME1##TYPENAME2* this) { \
        CGArrayOf##TYPENAME2* results = CGArrayOf##TYPENAME2##__new(1); \
        uint32_t bIndex = 0; \
        unsigned int aIndex = 0; \
        for (bIndex = 0; bIndex < CG_HASH_MAP_BUCKETS; ++bIndex) \
            if (this->buckets[bIndex] != NULL) { \
                for (aIndex = 0; aIndex < CGArrayOfCGKVPairOf##TYPENAME1##TYPENAME2##_getSize(this->buckets[bIndex]); ++aIndex) \
                    CGArrayOf##TYPENAME2##_add(results, CGKVPairOf##TYPENAME1##TYPENAME2##_getValue( \
                            CGArrayOfCGKVPairOf##TYPENAME1##TYPENAME2##_getValueAt(this->buckets[bIndex], aIndex))); \
            } \
        if (CGArrayOf##TYPENAME2##_getSize(results) == 0) { \
            CGArrayOf##TYPENAME2##_delete(results); \
            results = NULL; \
        } \
        return results; \
    } \
    \

#define DECLARE_HASH_MAP(TYPENAME1, TYPENAME2) \
    DECLARE_HASH_MAP_TYPE(TYPENAME1, TYPENAME2) \
    DECLARE_HASH_MAP_FUNCS(TYPENAME1, TYPENAME2) 

#define DEFINE_HASH_MAP(TYPENAME1, TYPENAME2) \
    DEFINE_HASH_MAP_FUNCS(TYPENAME1, TYPENAME2) 

#define INIT_HASH_MAP(TYPENAME1, TYPENAME2) \
    DECLARE_HASH_MAP(TYPENAME1, TYPENAME2) \
    DEFINE_HASH_MAP(TYPENAME1, TYPENAME2)


/* MAKEMAN */
/* type definition */

#define CGHashMap(TYPENAME1, TYPENAME2) CGHashMapOf##TYPENAME1##TYPENAME2


/* callers */


#define CGHashMap__new(TYPENAME1, TYPENAME2) CGHashMapOf##TYPENAME1##TYPENAME2##__new()
#define CGHashMap_clone(TYPENAME1, TYPENAME2, this) CGHashMapOf##TYPENAME1##TYPENAME2##_clone((this))
#define CGHashMap_delete(TYPENAME1, TYPENAME2, this) CGHashMapOf##TYPENAME1##TYPENAME2##_delete((this))
#define CGHashMap_deleteValues(TYPENAME1, TYPENAME2, this) CGHashMapOf##TYPENAME1##TYPENAME2##_deleteValues((this))
/** 
 * CGHashMap_get: get the value for a specified key - assuming that the keys are unique
 */
#define CGHashMap_get(TYPENAME1, TYPENAME2, this, key) CGHashMapOf##TYPENAME1##TYPENAME2##_getFirst((this), key)
#define CGHashMap_getAll(TYPENAME1, TYPENAME2, this, key) CGHashMapOf##TYPENAME1##TYPENAME2##_getAll((this), key)
#define CGHashMap_getKeys(TYPENAME1, TYPENAME2, this) CGHashMapOf##TYPENAME1##TYPENAME2##_getKeys((this))
#define CGHashMap_getValues(TYPENAME1, TYPENAME2, this) CGHashMapOf##TYPENAME1##TYPENAME2##_getValues((this))
#define CGHashMap_add(TYPENAME1, TYPENAME2, this, key, value) CGHashMapOf##TYPENAME1##TYPENAME2##_add((this), (key), (value))


#endif 
