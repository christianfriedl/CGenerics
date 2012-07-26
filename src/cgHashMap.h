#ifndef _CG_HASH_MAP_H
#define _CG_HASH_MAP_H

/* NOMAKEMAN */

#include<stdlib.h>
#include<stdarg.h>
#include<stdint.h>
#include"debug.h"
#include"cgAppState.h"
#include"cgArray.h"

uint32_t hashlittle( const void *key, size_t length, uint32_t initval);

#define CG_HASH_MAP_BUCKETS (256)
#define CG_HASH_MAP_SEED (13)


/* everything below this line is type-specific! */

/* declarations */

/** 
    NOTE: TYPENAME is a valid identifier; if you plan for a, say, cgHashMap<int*>, then do a typedef int* intPtr or the like...
*/

#define DECLARE_HASH_MAP_TYPE(TYPENAME1, TYPENAME2) \
typedef struct { \
    uint32_t seed; \
    cgArrayOfcgKVPairOf##TYPENAME1##TYPENAME2* buckets[CG_HASH_MAP_BUCKETS]; \
} cgHashMapOf##TYPENAME1##TYPENAME2;

#define DECLARE_HASH_MAP_FUNCS(TYPENAME1, TYPENAME2) \
    cgHashMapOf##TYPENAME1##TYPENAME2* cgHashMapOf##TYPENAME1##TYPENAME2##__new(); \
    void cgHashMapOf##TYPENAME1##TYPENAME2##_delete(cgHashMapOf##TYPENAME1##TYPENAME2* this); \

#define DEFINE_HASH_MAP_FUNCS(TYPENAME1, TYPENAME2) \
    \
    cgHashMapOf##TYPENAME1##TYPENAME2* cgHashMapOf##TYPENAME1##TYPENAME2##__new() { \
        cgHashMapOf##TYPENAME1##TYPENAME2* this = malloc(sizeof(*this)); \
        if (this != NULL) { \
            unsigned int i = 0; \
            for (i = 0; i < CG_HASH_MAP_BUCKETS; ++i) { \
                this->buckets[i] = NULL; \
            } \
        } else \
            cgAppState_THROW(cgAppState__getInstance(), Severity_error, cgExceptionID_CannotAllocate, "cannot allocate cgHashMap"); \
        return this; \
    } \
    \
    bool cgHashMapOf##TYPENAME1##TYPENAME2##_createBucket_(cgHashMapOf##TYPENAME1##TYPENAME2* this, unsigned int index) { \
        this->buckets[index] = cgArrayOfcgKVPairOf##TYPENAME1##TYPENAME2##__new(1); \
        if (cgAppState_isExceptionRaised(cgAppState__getInstance())) \
            return false; \
        return true; \
    } \
    \
    cgHashMapOf##TYPENAME1##TYPENAME2* cgHashMapOf##TYPENAME1##TYPENAME2##_clone(cgHashMapOf##TYPENAME1##TYPENAME2* this) { \
        cgHashMapOf##TYPENAME1##TYPENAME2* that = cgHashMapOf##TYPENAME1##TYPENAME2##__new(); \
        if (cgAppState_isExceptionRaisedWithID(cgAppState__getInstance(), cgExceptionID_CannotAllocate)) \
            return NULL; \
        unsigned int i=0; \
        /* NOTE: this implies that we actually do clone the objects in the Pairs, i.e. the original keys and values */ \
        for (i=0; i < cgArrayOfcgKVPairOf##TYPENAME1##TYPENAME2##_getSize(this->buckets); ++i) \
            that->buckets[i] = cgArrayOfcgKVPairOf##TYPENAME1##TYPENAME2##_clone(this->buckets[i]); \
        return that; \
    } \
    \
    void cgHashMapOf##TYPENAME1##TYPENAME2##_delete(cgHashMapOf##TYPENAME1##TYPENAME2* this) { \
        free(this); \
    } \
    \
    void TYPENAME1##_delete(TYPENAME1* this); void TYPENAME2##_delete(TYPENAME2* this); \
    void cgHashMapOf##TYPENAME1##TYPENAME2##_deleteValues(cgHashMapOf##TYPENAME1##TYPENAME2* this) { \
    } \
    \
    uint32_t cgHashMapOf##TYPENAME1##TYPENAME2##_getHashValue_(cgHashMapOf##TYPENAME1##TYPENAME2* this, TYPENAME1* key) { \
        return hashlittle(key, TYPENAME1##_getByteSize(key), CG_HASH_MAP_SEED) % CG_HASH_MAP_BUCKETS; \
    } \
    \
    void cgHashMapOf##TYPENAME1##TYPENAME2##_add(cgHashMapOf##TYPENAME1##TYPENAME2* this, TYPENAME1* key, TYPENAME2* value) { \
        cgKVPairOf##TYPENAME1##TYPENAME2* pair = cgKVPairOf##TYPENAME1##TYPENAME2##__new(key, value); \
        if (cgAppState_isExceptionRaised(cgAppState__getInstance())) \
            return; \
        uint32_t index = cgHashMapOf##TYPENAME1##TYPENAME2##_getHashValue_(this, key); \
        debugPrint("adding hash to bucket %u\n", index); \
        if (this->buckets[index] == NULL) { \
            if (cgHashMapOf##TYPENAME1##TYPENAME2##_createBucket_(this, index) != true) \
                return; \
        } \
        cgArrayOfcgKVPairOf##TYPENAME1##TYPENAME2##_add(this->buckets[index], pair); \
        debugPrint("bucket size of bucket %u is %u\n", index, cgArrayOfcgKVPairOf##TYPENAME1##TYPENAME2##_getSize(this->buckets[index])); \
        this->seed = index; \
    } \
    \
    TYPENAME2* cgHashMapOf##TYPENAME1##TYPENAME2##_getFirst(cgHashMapOf##TYPENAME1##TYPENAME2* this, TYPENAME1* key) { \
        uint32_t bIndex = cgHashMapOf##TYPENAME1##TYPENAME2##_getHashValue_(this, key); \
        debugPrint("will scan bucket %u\n", bIndex); \
        unsigned int aIndex = 0; \
        debugPrint("bucket size of bucket %u is %u\n", bIndex, cgArrayOfcgKVPairOf##TYPENAME1##TYPENAME2##_getSize(this->buckets[bIndex])); \
        for (aIndex = 0; aIndex < cgArrayOfcgKVPairOf##TYPENAME1##TYPENAME2##_getSize(this->buckets[bIndex]); ++aIndex) { \
            debugPrint("testing index %u of bucket %u\n", aIndex, bIndex); \
            if (TYPENAME1##_isEqual(cgKVPairOf##TYPENAME1##TYPENAME2##_getKey( \
                            cgArrayOfcgKVPairOf##TYPENAME1##TYPENAME2##_getValueAt(this->buckets[bIndex], aIndex)), \
                        key)) \
                return cgKVPairOf##TYPENAME1##TYPENAME2##_getValue(cgArrayOfcgKVPairOf##TYPENAME1##TYPENAME2##_getValueAt(this->buckets[bIndex], aIndex)); \
        } \
        return NULL; \
    } \
    \
    cgArrayOf##TYPENAME2* cgHashMapOf##TYPENAME1##TYPENAME2##_getAll(cgHashMapOf##TYPENAME1##TYPENAME2* this, TYPENAME1* key) { \
        cgArrayOf##TYPENAME2* values = cgArrayOf##TYPENAME2##__new(1); \
        uint32_t bIndex = cgHashMapOf##TYPENAME1##TYPENAME2##_getHashValue_(this, key); \
        debugPrint("will scan bucket %u\n", bIndex); \
        unsigned int aIndex = 0; \
        debugPrint("bucket size of bucket %u is %u\n", bIndex, cgArrayOfcgKVPairOf##TYPENAME1##TYPENAME2##_getSize(this->buckets[bIndex])); \
        for (aIndex = 0; aIndex < cgArrayOfcgKVPairOf##TYPENAME1##TYPENAME2##_getSize(this->buckets[bIndex]); ++aIndex) { \
            debugPrint("testing index %u of bucket %u\n", aIndex, bIndex); \
            if (TYPENAME1##_isEqual(cgKVPairOf##TYPENAME1##TYPENAME2##_getKey( \
                            cgArrayOfcgKVPairOf##TYPENAME1##TYPENAME2##_getValueAt(this->buckets[bIndex], aIndex)), \
                        key)) \
                cgArrayOf##TYPENAME2##_add(values, \
                        cgKVPairOf##TYPENAME1##TYPENAME2##_getValue( \
                            cgArrayOfcgKVPairOf##TYPENAME1##TYPENAME2##_getValueAt(this->buckets[bIndex], aIndex)) \
                        ); \
        } \
        if (cgArrayOf##TYPENAME2##_getSize(values) == 0) { \
            cgArrayOf##TYPENAME2##_delete(values); \
            values = NULL; \
        } \
        return values; \
    } \
    \
    cgArrayOf##TYPENAME1* cgHashMapOf##TYPENAME1##TYPENAME2##_getKeys(cgHashMapOf##TYPENAME1##TYPENAME2* this) { \
        cgArrayOf##TYPENAME1* results = cgArrayOf##TYPENAME1##__new(1); \
        uint32_t bIndex = 0; \
        unsigned int aIndex = 0; \
        for (bIndex = 0; bIndex < CG_HASH_MAP_BUCKETS; ++bIndex) \
            if (this->buckets[bIndex] != NULL) { \
                for (aIndex = 0; aIndex < cgArrayOfcgKVPairOf##TYPENAME1##TYPENAME2##_getSize(this->buckets[bIndex]); ++aIndex) \
                    cgArrayOf##TYPENAME1##_add(results, cgKVPairOf##TYPENAME1##TYPENAME2##_getKey( \
                            cgArrayOfcgKVPairOf##TYPENAME1##TYPENAME2##_getValueAt(this->buckets[bIndex], aIndex))); \
            } \
        if (cgArrayOf##TYPENAME1##_getSize(results) == 0) { \
            cgArrayOf##TYPENAME1##_delete(results); \
            results = NULL; \
        } \
        return results; \
    } \
    \
    cgArrayOf##TYPENAME2* cgHashMapOf##TYPENAME1##TYPENAME2##_getValues(cgHashMapOf##TYPENAME1##TYPENAME2* this) { \
        cgArrayOf##TYPENAME2* results = cgArrayOf##TYPENAME2##__new(1); \
        uint32_t bIndex = 0; \
        unsigned int aIndex = 0; \
        for (bIndex = 0; bIndex < CG_HASH_MAP_BUCKETS; ++bIndex) \
            if (this->buckets[bIndex] != NULL) { \
                for (aIndex = 0; aIndex < cgArrayOfcgKVPairOf##TYPENAME1##TYPENAME2##_getSize(this->buckets[bIndex]); ++aIndex) \
                    cgArrayOf##TYPENAME2##_add(results, cgKVPairOf##TYPENAME1##TYPENAME2##_getValue( \
                            cgArrayOfcgKVPairOf##TYPENAME1##TYPENAME2##_getValueAt(this->buckets[bIndex], aIndex))); \
            } \
        if (cgArrayOf##TYPENAME2##_getSize(results) == 0) { \
            cgArrayOf##TYPENAME2##_delete(results); \
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

#define cgHashMap(TYPENAME1, TYPENAME2) cgHashMapOf##TYPENAME1##TYPENAME2


/* callers */


#define cgHashMap__new(TYPENAME1, TYPENAME2) cgHashMapOf##TYPENAME1##TYPENAME2##__new()
#define cgHashMap_clone(TYPENAME1, TYPENAME2, this) cgHashMapOf##TYPENAME1##TYPENAME2##_clone((this))
#define cgHashMap_delete(TYPENAME1, TYPENAME2, this) cgHashMapOf##TYPENAME1##TYPENAME2##_delete((this))
#define cgHashMap_deleteValues(TYPENAME1, TYPENAME2, this) cgHashMapOf##TYPENAME1##TYPENAME2##_deleteValues((this))
/** 
 * cgHashMap_get: get the value for a specified key - assuming that the keys are unique
 */
#define cgHashMap_get(TYPENAME1, TYPENAME2, this, key) cgHashMapOf##TYPENAME1##TYPENAME2##_getFirst((this), key)
#define cgHashMap_getAll(TYPENAME1, TYPENAME2, this, key) cgHashMapOf##TYPENAME1##TYPENAME2##_getAll((this), key)
#define cgHashMap_getKeys(TYPENAME1, TYPENAME2, this) cgHashMapOf##TYPENAME1##TYPENAME2##_getKeys((this))
#define cgHashMap_getValues(TYPENAME1, TYPENAME2, this) cgHashMapOf##TYPENAME1##TYPENAME2##_getValues((this))
#define cgHashMap_add(TYPENAME1, TYPENAME2, this, key, value) cgHashMapOf##TYPENAME1##TYPENAME2##_add((this), (key), (value))


#endif 
