#ifndef _CG_KV_PAIR_H
#define _CG_KV_PAIR_H

/* NOMAKEMAN */

#include<stdlib.h>
#include<stdarg.h>
#include"CGAppState.h"


/* everything below this line is type-specific! */

/* declarations */

/** 
    This will init the CGKVPair for one typename
    NOTE: TYPENAME is a valid identifier; if you plan for a, say, CGKVPair<int*>, then do a typedef int* intPtr or the like...
*/

#define DECLARE_KV_PAIR_TYPE(TYPENAME1, TYPENAME2) \
typedef struct { \
    TYPENAME1* key; \
    TYPENAME2* value; \
} CGKVPairOf##TYPENAME1##TYPENAME2;

#define DECLARE_KV_PAIR_FUNCS(TYPENAME1, TYPENAME2) \
    CGKVPairOf##TYPENAME1##TYPENAME2* CGKVPairOf##TYPENAME1##TYPENAME2##__new(TYPENAME1* key, TYPENAME2* value); \
    void CGKVPairOf##TYPENAME1##TYPENAME2##_delete(CGKVPairOf##TYPENAME1##TYPENAME2* this); \

#define DEFINE_KV_PAIR_FUNCS(TYPENAME1, TYPENAME2) \
    \
    CGKVPairOf##TYPENAME1##TYPENAME2* CGKVPairOf##TYPENAME1##TYPENAME2##__new(TYPENAME1* key, TYPENAME2* value) { \
        CGKVPairOf##TYPENAME1##TYPENAME2* this = malloc(sizeof(*this)); \
        if (this != NULL) { \
            this->key = key; \
            this->value = value; \
        } else \
            CGAppState_THROW(CGAppState__getInstance(), Severity_error, CGExceptionID_CannotAllocate, "cannot allocate CGKVPair"); \
        return this; \
    } \
    \
    /* NOTE: we already deep-copy the contents here, TODO for the other containers */ \
    CGKVPairOf##TYPENAME1##TYPENAME2* CGKVPairOf##TYPENAME1##TYPENAME2##_clone(CGKVPairOf##TYPENAME1##TYPENAME2* this) { \
        CGKVPairOf##TYPENAME1##TYPENAME2* that = CGKVPairOf##TYPENAME1##TYPENAME2##__new(TYPENAME1##_clone(this->key), TYPENAME2##_clone(this->value)); \
        if (CGAppState_isExceptionRaisedWithID(CGAppState__getInstance(), CGExceptionID_CannotAllocate)) \
            return NULL; \
        return that; \
    } \
    \
    void CGKVPairOf##TYPENAME1##TYPENAME2##_delete(CGKVPairOf##TYPENAME1##TYPENAME2* this) { \
        free(this); \
    } \
    \
    void TYPENAME1##_delete(TYPENAME1* this); void TYPENAME2##_delete(TYPENAME2* this); \
    void CGKVPairOf##TYPENAME1##TYPENAME2##_deleteValues(CGKVPairOf##TYPENAME1##TYPENAME2* this) { \
        TYPENAME1##_delete(this->key); \
        TYPENAME2##_delete(this->value); \
    } \
    \
    TYPENAME1* CGKVPairOf##TYPENAME1##TYPENAME2##_getKey(CGKVPairOf##TYPENAME1##TYPENAME2* this) { \
        return this->key; \
    } \
    \
    TYPENAME2* CGKVPairOf##TYPENAME1##TYPENAME2##_getValue(CGKVPairOf##TYPENAME1##TYPENAME2* this) { \
        return this->value; \
    } \
    \
    void CGKVPairOf##TYPENAME1##TYPENAME2##_setKey(CGKVPairOf##TYPENAME1##TYPENAME2* this, TYPENAME1* key) { \
        this->key = key; \
    } \
    \
    void CGKVPairOf##TYPENAME1##TYPENAME2##_setValue(CGKVPairOf##TYPENAME1##TYPENAME2* this, TYPENAME2* value) { \
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

#define CGKVPair(TYPENAME1, TYPENAME2) CGKVPairOf##TYPENAME1##TYPENAME2


/* callers */


#define CGKVPair__new(TYPENAME1, TYPENAME2, key, value) CGKVPairOf##TYPENAME1##TYPENAME2##__new((key), (value))
#define CGKVPair_clone(TYPENAME1, TYPENAME2, this) CGKVPairOf##TYPENAME1##TYPENAME2##_clone((this))
#define CGKVPair_delete(TYPENAME1, TYPENAME2, this) CGKVPairOf##TYPENAME1##TYPENAME2##_delete((this))
#define CGKVPair_deleteValues(TYPENAME1, TYPENAME2, this) CGKVPairOf##TYPENAME1##TYPENAME2##_deleteValues((this))
#define CGKVPair_getKey(TYPENAME1, TYPENAME2, this) CGKVPairOf##TYPENAME1##TYPENAME2##_getKey((this))
#define CGKVPair_getValue(TYPENAME1, TYPENAME2, this) CGKVPairOf##TYPENAME1##TYPENAME2##_getValue((this))
#define CGKVPair_setKey(TYPENAME1, TYPENAME2, this, key) CGKVPairOf##TYPENAME1##TYPENAME2##_setKey((this), (key))
#define CGKVPair_setValue(TYPENAME1, TYPENAME2, this, value) CGKVPairOf##TYPENAME1##TYPENAME2##_setValue((this), (value))


#endif 
