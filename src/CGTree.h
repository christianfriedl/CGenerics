#ifndef _CGTREE_H
#define _CGTREE_H

/*
 * general note for container types:
 * containers contain references - that means that the objects in the
 * container are never automatically delete'd by delete'ing the
 * continer, and that *_clone never returns a deep copy, nor does *_add
 * etc. copy the object
 */

/* NOMAKEMAN */

#include<stdlib.h>
#include<string.h>
#include<stdarg.h>
#include"CGAppState.h"
#include"CGArray.h"
#include"CGArrayIterator.h"

typedef enum { CGTreeStrategy_depthFirst = 0, CGTreeStrategy_breadthFirst } CGTreeStrategy;

/* everything below this line is type-specific! */

/* declarations */

#define DECLARE_TREE_TYPE(TYPENAME) \
    struct CGTreeOf##TYPENAME##_struct; \
    typedef struct CGTreeOf##TYPENAME##_struct CGTreeOf##TYPENAME; \
    DECLARE_ARRAY_TYPE(CGTreeOf##TYPENAME) \
    struct CGTreeOf##TYPENAME##_struct { \
        TYPENAME* value; \
        CGTreeOf##TYPENAME* parent; \
        CGArrayOfCGTreeOf##TYPENAME* subTrees; \
    }; \
    DECLARE_ARRAY_ITERATOR_TYPE(CGTreeOf##TYPENAME) \

#define DECLARE_TREE_FUNCS(TYPENAME) \
    DECLARE_ARRAY_FUNCS(CGTreeOf##TYPENAME) \
    DECLARE_ARRAY_ITERATOR_FUNCS(CGTreeOf##TYPENAME) \
    CGTreeOf##TYPENAME* CGTreeOf##TYPENAME##_clone(CGTreeOf##TYPENAME* this); \
    DECLARE_ARRAY_FUNCS(CGTreeOf##TYPENAME) \
    DECLARE_ARRAY_ITERATOR_FUNCS(CGTreeOf##TYPENAME) \
    CGTreeOf##TYPENAME* CGTreeOf##TYPENAME##__new(TYPENAME* value); \
    void CGTreeOf##TYPENAME##_delete(CGTreeOf##TYPENAME* this); \
    void CGTreeOf##TYPENAME##_addSubTree(CGTreeOf##TYPENAME* this, CGTreeOf##TYPENAME* subTree); \
    CGArrayOfCGTreeOf##TYPENAME* CGTreeOf##TYPENAME##_getSubTrees(CGTreeOf##TYPENAME* this); \
    CGTreeOf##TYPENAME* CGTreeOf##TYPENAME##_getSubTreeAt(CGTreeOf##TYPENAME* this, const unsigned int at); \
    CGTreeOf##TYPENAME* CGTreeOf##TYPENAME##_removeSubTreeAt(CGTreeOf##TYPENAME* this, const unsigned int at); \
    TYPENAME* CGTreeOf##TYPENAME##_getValue(CGTreeOf##TYPENAME* this); \
    CGTreeOf##TYPENAME* CGTreeOf##TYPENAME##_getParent(CGTreeOf##TYPENAME* this); \
    void CGTreeOf##TYPENAME##_setParent(CGTreeOf##TYPENAME* this, CGTreeOf##TYPENAME* parent); \
    unsigned int CGTreeOf##TYPENAME##_getSubTreeSize(CGTreeOf##TYPENAME* this); \
    CGTreeOf##TYPENAME* CGTreeOf##TYPENAME##__newFromInitializerList(TYPENAME* value, CGTreeOf##TYPENAME* subTree, ...); \
    bool CGTreeOf##TYPENAME##_mapConstant(CGTreeOf##TYPENAME* this, bool (*mapFunction)(const TYPENAME*, void *), CGTreeStrategy strategy, void *userData); \

#define DEFINE_TREE_FUNCS(TYPENAME) \
    \
    DEFINE_ARRAY_FUNCS(CGTreeOf##TYPENAME) \
    DEFINE_ARRAY_ITERATOR_FUNCS(CGTreeOf##TYPENAME) \
    CGTreeOf##TYPENAME* CGTreeOf##TYPENAME##__new(TYPENAME* value) { \
        CGTreeOf##TYPENAME* this = malloc(sizeof(*this)); \
        if (this != NULL) { \
            this->parent = NULL; \
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
    void CGTreeOf##TYPENAME##_deleteValues(CGTreeOf##TYPENAME* this) { \
        CGArrayOfCGTreeOf##TYPENAME##Iterator* iter = CGArrayOfCGTreeOf##TYPENAME##Iterator__new(this->subTrees); \
        CGTreeOf##TYPENAME* tree = NULL; \
        while ((tree = CGArrayOfCGTreeOf##TYPENAME##Iterator_fetch(iter)) != NULL) { \
            TYPENAME##_delete(CGTreeOf##TYPENAME##_getValue(tree)); \
        } \
        TYPENAME##_delete(this->value); \
    } \
    \
    TYPENAME* CGTreeOf##TYPENAME##_getValue(CGTreeOf##TYPENAME* this) { \
        return this->value; \
    } \
    \
    CGTreeOf##TYPENAME* CGTreeOf##TYPENAME##_getParent(CGTreeOf##TYPENAME* this) { \
        return this->parent; \
    } \
    \
    void CGTreeOf##TYPENAME##_setParent(CGTreeOf##TYPENAME* this, CGTreeOf##TYPENAME* parent) { \
        this->parent = parent; \
    } \
    \
    void CGTreeOf##TYPENAME##_addSubTree(CGTreeOf##TYPENAME* this, CGTreeOf##TYPENAME* subTree) { \
        CGArray_add(CGTreeOf##TYPENAME, this->subTrees, subTree); \
        CGTreeOf##TYPENAME##_setParent(subTree, this); \
    } \
    \
    CGTreeOf##TYPENAME* CGTreeOf##TYPENAME##_getSubTreeAt(CGTreeOf##TYPENAME* this, const unsigned int at) { \
        return CGArray_getValueAt(CGTreeOf##TYPENAME, this->subTrees, at); \
    } \
    \
    CGTreeOf##TYPENAME* CGTreeOf##TYPENAME##_removeSubTreeAt(CGTreeOf##TYPENAME* this, const unsigned int at) { \
        return CGArray_removeValueAt(CGTreeOf##TYPENAME, this->subTrees, at); \
    } \
    \
    CGArrayOfCGTreeOf##TYPENAME* CGTreeOf##TYPENAME##_getSubTrees(CGTreeOf##TYPENAME* this) { \
        return this->subTrees; \
    } \
    \
    unsigned int CGTreeOf##TYPENAME##_getSubTreeSize(CGTreeOf##TYPENAME* this) { \
        return CGArray_getSize(CGTreeOf##TYPENAME, this->subTrees); \
    } \
    \
    /*
        returns true if all leaves were mapped, false otherwise
    */ \
    bool CGTreeOf##TYPENAME##_mapConstantDepthFirst_(CGTreeOf##TYPENAME* this, bool (*mapFunction)(const TYPENAME*, void *), void *userData) { \
        CGArrayOfCGTreeOf##TYPENAME##Iterator* iter = CGArrayOfCGTreeOf##TYPENAME##Iterator__new(this->subTrees); \
        CGTreeOf##TYPENAME* tree; \
        while ((tree = CGArrayOfCGTreeOf##TYPENAME##Iterator_fetch(iter)) != NULL) { \
            if (CGTreeOf##TYPENAME##_mapConstantDepthFirst_(tree, mapFunction, userData) == false) \
                return false; \
        } \
        return mapFunction(CGTreeOf##TYPENAME##_getValue(this), userData); \
    } \
    bool CGTreeOf##TYPENAME##_mapConstantBreadthFirst_(CGTreeOf##TYPENAME* this, bool (*mapFunction)(const TYPENAME*, void *), void *userData, bool isRoot) { \
        CGArrayOfCGTreeOf##TYPENAME##Iterator* iter = CGArrayOfCGTreeOf##TYPENAME##Iterator__new(this->subTrees); \
        CGTreeOf##TYPENAME* tree; \
        if (isRoot == true) { \
            if (mapFunction(CGTreeOf##TYPENAME##_getValue(this), userData) == false) \
                return false; \
        } \
        while ((tree = CGArrayOfCGTreeOf##TYPENAME##Iterator_fetch(iter)) != NULL) { \
            if (mapFunction(CGTreeOf##TYPENAME##_getValue(tree), userData) == false) \
                return false; \
        } \
        CGArrayOfCGTreeOf##TYPENAME##Iterator_reset(iter); \
        while ((tree = CGArrayOfCGTreeOf##TYPENAME##Iterator_fetch(iter)) != NULL) { \
            if (CGTreeOf##TYPENAME##_mapConstantBreadthFirst_(tree, mapFunction, userData, false) == false) \
                return false; \
        } \
        return true; \
    } \
    bool CGTreeOf##TYPENAME##_mapConstant(CGTreeOf##TYPENAME* this, bool (*mapFunction)(const TYPENAME*, void *), CGTreeStrategy strategy, void *userData) { \
        if (strategy == CGTreeStrategy_depthFirst) \
            return CGTreeOf##TYPENAME##_mapConstantDepthFirst_(this, mapFunction, userData); \
        else \
            return CGTreeOf##TYPENAME##_mapConstantBreadthFirst_(this, mapFunction, userData, true); \
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


#define CGTree__new(TYPENAME, value) CGTreeOf##TYPENAME##__new((value))
#define CGTree__newFromInitializerList(TYPENAME, value, ...) CGTreeOf##TYPENAME##__newFromInitializerList((value), __VA_ARGS__)
/* NOTE: clone for container types does not provide a deep copy, as we cannot know the signature of the constructors of the hosted types */
#define CGTree_clone(TYPENAME, tree) CGTreeOf##TYPENAME##_clone((tree))
#define CGTree_getValue(TYPENAME, tree) CGTreeOf##TYPENAME##_getValue((tree))
#define CGTree_delete(TYPENAME, tree) CGTreeOf##TYPENAME##_delete((tree))
#define CGTree_deleteValues(TYPENAME, tree) CGTreeOf##TYPENAME##_deleteValues((tree))
#define CGTree_addSubTree(TYPENAME, tree, subTree) CGTreeOf##TYPENAME##_addSubTree((tree), (subTree))
#define CGTree_getSubTrees(TYPENAME, tree) CGTreeOf##TYPENAME##_getSubTrees((tree))
#define CGTree_getSubTreeSize(TYPENAME, tree) CGTreeOf##TYPENAME##_getSubTreeSize((tree))
#define CGTree_getSubTreeAt(TYPENAME, tree, at) CGTreeOf##TYPENAME##_getSubTreeAt((tree), (at))
#define CGTree_removeSubTreeAt(TYPENAME, tree, at) CGTreeOf##TYPENAME##_removeSubTreeAt((tree), (at))
#define CGTree_mapConstant(TYPENAME, tree, function, strategy, userData) CGTreeOf##TYPENAME##_mapConstant((tree), (function), (strategy), (userData))
#define CGTree_getParent(TYPENAME, tree) CGTreeOf##TYPENAME##_getParent((tree))
#define CGTree_setParent(TYPENAME, tree, parent) CGTreeOf##TYPENAME##_setParent((tree), (parent))

#endif 
