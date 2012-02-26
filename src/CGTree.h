#ifndef _CGTREE_H
#define _CGTREE_H

/* NOMAKEMAN */

#include<stdlib.h>
#include<string.h>
#include<stdarg.h>
#include"CGAppState.h"
#include"CGArray.h"
#include"CGArrayIterator.h"

/* everything below this line is type-specific! */

/* declarations */

#define DECLARE_TREE_TYPE(TYPENAME) \
    struct CGTreeOf##TYPENAME##_struct; \
    typedef struct CGTreeOf##TYPENAME##_struct CGTreeOf##TYPENAME; \
    DECLARE_ARRAY_TYPE(CGTreeOf##TYPENAME) \
    struct CGTreeOf##TYPENAME##_struct { \
        TYPENAME* value; \
        CGArrayOfCGTreeOf##TYPENAME* subTrees; \
    }; \
    DECLARE_ARRAY_ITERATOR_TYPE(CGTreeOf##TYPENAME) \

#define DECLARE_TREE_FUNCS(TYPENAME) \
    DECLARE_ARRAY_FUNCS(CGTreeOf##TYPENAME) \
    DECLARE_ARRAY_ITERATOR_FUNCS(CGTreeOf##TYPENAME) \
    CGTreeOf##TYPENAME* CGTreeOf##TYPENAME##_clone(CGTreeOf##TYPENAME* this); \
    DEFINE_ARRAY_FUNCS(CGTreeOf##TYPENAME) \
    DEFINE_ARRAY_ITERATOR_FUNCS(CGTreeOf##TYPENAME) \
    CGTreeOf##TYPENAME* CGTreeOf##TYPENAME##__new(TYPENAME* value); \
    void CGTreeOf##TYPENAME##_delete(CGTreeOf##TYPENAME* this); \
    void CGTreeOf##TYPENAME##_addSubTree(CGTreeOf##TYPENAME* this, CGTreeOf##TYPENAME* subTree); \
    CGArrayOfCGTreeOf##TYPENAME* CGTreeOf##TYPENAME##_getSubTrees(CGTreeOf##TYPENAME* this); \
    CGTreeOf##TYPENAME* CGTreeOf##TYPENAME##_getSubTreeAt(CGTreeOf##TYPENAME* this, const unsigned int at); \
    TYPENAME* CGTreeOf##TYPENAME##_removeSubTreeAt(CGTreeOf##TYPENAME* this); \
    TYPENAME* CGTreeOf##TYPENAME##_getValue(CGTreeOf##TYPENAME* this); \
    /*
    CGTreeOf##TYPENAME* CGTreeOf##TYPENAME##__newFromInitializerList(TYPENAME* item, ...); \
    */

#define DEFINE_TREE_FUNCS(TYPENAME) \
    \
    CGTreeOf##TYPENAME* CGTreeOf##TYPENAME##__new(TYPENAME* value) { \
        CGTreeOf##TYPENAME* this = malloc(sizeof(*this)); \
        if (this != NULL) { \
            this->value = value; \
            this->subTrees = CGArray__new(CGTreeOf##TYPENAME, 2); \
        } else \
            CGAppState_THROW(CGAppState__getInstance(), Severity_error, CGExceptionID_CannotAllocate, "cannot allocate CGTree"); \
        return this; \
    } \
    \
    /**
        this expects a sentinel parameter (NULL) at the end of the initializer list
    */ \
    CGTreeOf##TYPENAME* CGTreeOf##TYPENAME##__newFromInitializerList(TYPENAME* value, CGTreeOf##TYPENAME* subTree, ...) { \
        CGTreeOf##TYPENAME* this = CGTreeOf##TYPENAME##__new(value); \
        if (this != NULL) { \
            va_list args; \
            va_start(args, subTree); \
            while (subTree) { \
                CGTreeOf##TYPENAME##_addSubTree(this, subTree); \
                if (CGAppState_isExceptionRaised(CGAppState__getInstance())) \
                    break; \
                subTree = va_arg(args, CGTreeOf##TYPENAME*); \
            } \
            va_end(args); \
        } \
        return this; \
    } \
    \
    CGTreeOf##TYPENAME* CGTreeOf##TYPENAME##_clone(CGTreeOf##TYPENAME* this) { \
        printf("CGTree_clone called, undefined function - aborting!\n"); \
        abort(); \
    } \
    \
    void CGTreeOf##TYPENAME##_delete(CGTreeOf##TYPENAME* this) { \
        CGArrayIterator(CGTreeOf##TYPENAME)* iter = CGArrayIterator__new(CGTreeOf##TYPENAME, this->subTrees); \
        while (CGArrayIterator_isInsideBounds(CGTreeOf##TYPENAME, iter)) { \
            free(CGArrayIterator_getCurrentElement(CGTreeOf##TYPENAME, iter)); \
            CGArrayIterator_moveToNextElement(CGTreeOf##TYPENAME, iter); \
        } \
        free(this); \
    } \
    \
    TYPENAME* CGTreeOf##TYPENAME##_getValue(CGTreeOf##TYPENAME* this) { \
        return this->value; \
    } \
    \
    void CGTreeOf##TYPENAME##_addSubTree(CGTreeOf##TYPENAME* this, CGTreeOf##TYPENAME* subTree) { \
        CGArray_add(CGTreeOf##TYPENAME, this->subTrees, subTree); \
    } \
    \
    CGTreeOf##TYPENAME* CGTreeOf##TYPENAME##_getSubTreeAt(CGTreeOf##TYPENAME* this, const unsigned int at) { \
        return CGArray_getValueAt(CGTreeOf##TYPENAME, this->subTrees, at); \
    } \
    \
    CGArrayOfCGTreeOf##TYPENAME* CGTreeOf##TYPENAME##_getSubTrees(CGTreeOf##TYPENAME* this) { \
        return this->subTrees; \
    } \
    \
    


#define DECLARE_TREE(TYPENAME) \
    DECLARE_TREE_TYPE(TYPENAME) \
    DECLARE_TREE_FUNCS(TYPENAME) 

#define DEFINE_TREE(TYPENAME) \
    DEFINE_TREE_FUNCS(TYPENAME) 

#define INIT_TREE(TYPENAME) \
    DECLARE_TREE(TYPENAME) \
    DEFINE_TREE(TYPENAME)


/* MAKEMAN */
/* type definition */

#define CGTree(TYPENAME) CGTreeOf##TYPENAME


/* callers */


#define CGTree__new(TYPENAME, initialCapacity) CGTreeOf##TYPENAME##__new((initialCapacity))
#define CGTree__newFromInitializerList(TYPENAME, ...) CGTreeOf##TYPENAME##__newFromInitializerList(__VA_ARGS__)
#define CGTree_clone(TYPENAME, tree) CGTreeOf##TYPENAME##_clone((tree))
#define CGTree_getValue(TYPENAME, tree) CGTreeOf##TYPENAME##_getValue((tree))
#define CGTree_delete(TYPENAME, array) CGTreeOf##TYPENAME##_delete((array))
#define CGTree_deleteValues(TYPENAME, array) CGTreeOf##TYPENAME##_deleteValues((array))
#define CGTree_addSubTree(TYPENAME, tree, subTree) CGTreeOf##TYPENAME##_addSubTree((tree), (subTree))
#define CGTree_getSubTrees(TYPENAME, tree) CGTreeOf##TYPENAME##_getSubTrees((tree))
#define CGTree_getSubTreeAt(TYPENAME, tree, at) CGTreeOf##TYPENAME##_getSubTreeAt((tree), (at))
#define CGTree_removeSubTreeAt(TYPENAME, array, at) CGTreeOf##TYPENAME##_removeValueAt((array), (at))

#endif 