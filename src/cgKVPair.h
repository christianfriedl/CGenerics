#ifndef _CG_KV_PAIR_H
#define _CG_KV_PAIR_H

/* NOMAKEMAN */

#include<stdlib.h>
#include<stdarg.h>
#include"cgAppState.h"


/* everything below this line is type-specific! */

/* declarations */

/** 
    This will init the cgKVPair for one typename
    NOTE: TYPENAME is a valid identifier; if you plan for a, say, cgKVPair<int*>, then do a typedef int* intPtr or the like...
*/

#define DECLARE_KV_PAIR_TYPE(TYPENAME1, TYPENAME2) \
typedef struct { \
    TYPENAME1* key; \
    TYPENAME2* value; \
} cgKVPairOf##TYPENAME1##TYPENAME2;

#define DECLARE_KV_PAIR_FUNCS(TYPENAME1, TYPENAME2) \
    cgKVPairOf##TYPENAME1##TYPENAME2* cgKVPairOf##TYPENAME1##TYPENAME2##__new(TYPENAME1* key, TYPENAME2* value); \
    void cgKVPairOf##TYPENAME1##TYPENAME2##_delete(cgKVPairOf##TYPENAME1##TYPENAME2* this); \

#define DEFINE_KV_PAIR_FUNCS(TYPENAME1, TYPENAME2) \
    \
    cgKVPairOf##TYPENAME1##TYPENAME2* cgKVPairOf##TYPENAME1##TYPENAME2##__new(TYPENAME1* key, TYPENAME2* value) { \
        cgKVPairOf##TYPENAME1##TYPENAME2* this = malloc(sizeof(*this)); \
        if (this != NULL) { \
            this->key = key; \
            this->value = value; \
        } else \
            cgAppState_THROW(cgAppState__getInstance(), Severity_error, cgExceptionID_CannotAllocate, "cannot allocate cgKVPair"); \
        return this; \
    } \
    \
    /* NOTE: we already deep-copy the contents here, TODO for the other containers */ \
    cgKVPairOf##TYPENAME1##TYPENAME2* cgKVPairOf##TYPENAME1##TYPENAME2##_clone(cgKVPairOf##TYPENAME1##TYPENAME2* this) { \
        cgKVPairOf##TYPENAME1##TYPENAME2* that = cgKVPairOf##TYPENAME1##TYPENAME2##__new(TYPENAME1##_clone(this->key), TYPENAME2##_clone(this->value)); \
        if (cgAppState_isExceptionRaisedWithID(cgAppState__getInstance(), cgExceptionID_CannotAllocate)) \
            return NULL; \
        return that; \
    } \
    \
    void cgKVPairOf##TYPENAME1##TYPENAME2##_delete(cgKVPairOf##TYPENAME1##TYPENAME2* this) { \
        free(this); \
    } \
    \
    void TYPENAME1##_delete(TYPENAME1* this); void TYPENAME2##_delete(TYPENAME2* this); \
    void cgKVPairOf##TYPENAME1##TYPENAME2##_deleteValues(cgKVPairOf##TYPENAME1##TYPENAME2* this) { \
        TYPENAME1##_delete(this->key); \
        TYPENAME2##_delete(this->value); \
    } \
    \
    TYPENAME1* cgKVPairOf##TYPENAME1##TYPENAME2##_getKey(cgKVPairOf##TYPENAME1##TYPENAME2* this) { \
        return this->key; \
    } \
    \
    TYPENAME2* cgKVPairOf##TYPENAME1##TYPENAME2##_getValue(cgKVPairOf##TYPENAME1##TYPENAME2* this) { \
        return this->value; \
    } \
    \
    void cgKVPairOf##TYPENAME1##TYPENAME2##_setKey(cgKVPairOf##TYPENAME1##TYPENAME2* this, TYPENAME1* key) { \
        this->key = key; \
    } \
    \
    void cgKVPairOf##TYPENAME1##TYPENAME2##_setValue(cgKVPairOf##TYPENAME1##TYPENAME2* this, TYPENAME2* value) { \
        this->value = value; \
    } \

#define DECLARE_KV_PAIR(TYPENAME1, TYPENAME2) \
    DECLARE_KV_PAIR_TYPE(TYPENAME1, TYPENAME2) \
    DECLARE_KV_PAIR_FUNCS(TYPENAME1, TYPENAME2) 

#define DEFINE_KV_PAIR(TYPENAME1, TYPENAME2) \
    DEFINE_KV_PAIR_FUNCS(TYPENAME1, TYPENAME2) 

#define INIT_KV_PAIR(TYPENAME1, TYPENAME2) \
    DECLARE_KV_PAIR(TYPENAME1, TYPENAME2) \
    DEFINE_KV_PAIR(TYPENAME1, TYPENAME2)


/* MAKEMAN */
/* type definition */

#define cgKVPair(TYPENAME1, TYPENAME2) cgKVPairOf##TYPENAME1##TYPENAME2


/* callers */


#define cgKVPair__new(TYPENAME1, TYPENAME2, key, value) cgKVPairOf##TYPENAME1##TYPENAME2##__new((key), (value))
#define cgKVPair_clone(TYPENAME1, TYPENAME2, this) cgKVPairOf##TYPENAME1##TYPENAME2##_clone((this))
#define cgKVPair_delete(TYPENAME1, TYPENAME2, this) cgKVPairOf##TYPENAME1##TYPENAME2##_delete((this))
#define cgKVPair_deleteValues(TYPENAME1, TYPENAME2, this) cgKVPairOf##TYPENAME1##TYPENAME2##_deleteValues((this))
#define cgKVPair_getKey(TYPENAME1, TYPENAME2, this) cgKVPairOf##TYPENAME1##TYPENAME2##_getKey((this))
#define cgKVPair_getValue(TYPENAME1, TYPENAME2, this) cgKVPairOf##TYPENAME1##TYPENAME2##_getValue((this))
#define cgKVPair_setKey(TYPENAME1, TYPENAME2, this, key) cgKVPairOf##TYPENAME1##TYPENAME2##_setKey((this), (key))
#define cgKVPair_setValue(TYPENAME1, TYPENAME2, this, value) cgKVPairOf##TYPENAME1##TYPENAME2##_setValue((this), (value))


#endif 
