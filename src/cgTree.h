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
#include"cgAppState.h"
#include"cgArray.h"
#include"cgArrayIterator.h"

typedef enum { cgTreeStrategy_depthFirst = 0, cgTreeStrategy_breadthFirst } cgTreeStrategy;

/* everything below this line is type-specific! */

/* declarations */

#define DECLARE_TREE_TYPE(TYPENAME) \
    struct cgTreeOf##TYPENAME##_struct; \
    typedef struct cgTreeOf##TYPENAME##_struct cgTreeOf##TYPENAME; \
    DECLARE_ARRAY_TYPE(cgTreeOf##TYPENAME) \
    struct cgTreeOf##TYPENAME##_struct { \
        TYPENAME* value; \
        cgTreeOf##TYPENAME* parent; \
        cgArrayOfcgTreeOf##TYPENAME* subTrees; \
    }; \
    DECLARE_ARRAY_ITERATOR_TYPE(cgTreeOf##TYPENAME) \

#define DECLARE_TREE_FUNCS(TYPENAME) \
    DECLARE_ARRAY_FUNCS(cgTreeOf##TYPENAME) \
    DECLARE_ARRAY_ITERATOR_FUNCS(cgTreeOf##TYPENAME) \
    cgTreeOf##TYPENAME* cgTreeOf##TYPENAME##_clone(cgTreeOf##TYPENAME* this); \
    DECLARE_ARRAY_FUNCS(cgTreeOf##TYPENAME) \
    DECLARE_ARRAY_ITERATOR_FUNCS(cgTreeOf##TYPENAME) \
    cgTreeOf##TYPENAME* cgTreeOf##TYPENAME##__new(TYPENAME* value); \
    void cgTreeOf##TYPENAME##_delete(cgTreeOf##TYPENAME* this); \
    void cgTreeOf##TYPENAME##_addSubTree(cgTreeOf##TYPENAME* this, cgTreeOf##TYPENAME* subTree); \
    cgArrayOfcgTreeOf##TYPENAME* cgTreeOf##TYPENAME##_getSubTrees(cgTreeOf##TYPENAME* this); \
    cgTreeOf##TYPENAME* cgTreeOf##TYPENAME##_getSubTreeAt(cgTreeOf##TYPENAME* this, const unsigned int at); \
    cgTreeOf##TYPENAME* cgTreeOf##TYPENAME##_removeSubTreeAt(cgTreeOf##TYPENAME* this, const unsigned int at); \
    TYPENAME* cgTreeOf##TYPENAME##_getValue(cgTreeOf##TYPENAME* this); \
    cgTreeOf##TYPENAME* cgTreeOf##TYPENAME##_getParent(cgTreeOf##TYPENAME* this); \
    void cgTreeOf##TYPENAME##_setParent(cgTreeOf##TYPENAME* this, cgTreeOf##TYPENAME* parent); \
    unsigned int cgTreeOf##TYPENAME##_getSubTreeSize(cgTreeOf##TYPENAME* this); \
    cgTreeOf##TYPENAME* cgTreeOf##TYPENAME##__newFromInitializerList(TYPENAME* value, cgTreeOf##TYPENAME* subTree, ...); \
    bool cgTreeOf##TYPENAME##_mapConstant(cgTreeOf##TYPENAME* this, bool (*mapFunction)(const TYPENAME*, void *), cgTreeStrategy strategy, void *userData); \

#define DEFINE_TREE_FUNCS(TYPENAME) \
    \
    DEFINE_ARRAY_FUNCS(cgTreeOf##TYPENAME) \
    DEFINE_ARRAY_ITERATOR_FUNCS(cgTreeOf##TYPENAME) \
    cgTreeOf##TYPENAME* cgTreeOf##TYPENAME##__new(TYPENAME* value) { \
        cgTreeOf##TYPENAME* this = malloc(sizeof(*this)); \
        if (this != NULL) { \
            this->parent = NULL; \
            this->value = value; \
            this->subTrees = cgArray__new(cgTreeOf##TYPENAME, 2); \
        } else \
            cgAppState_THROW(cgAppState__getInstance(), Severity_error, cgExceptionID_CannotAllocate, "cannot allocate cgTree"); \
        return this; \
    } \
    \
    /**
        this expects a sentinel parameter (NULL) at the end of the initializer list
    */ \
    cgTreeOf##TYPENAME* cgTreeOf##TYPENAME##__newFromInitializerList(TYPENAME* value, cgTreeOf##TYPENAME* subTree, ...) { \
        cgTreeOf##TYPENAME* this = cgTreeOf##TYPENAME##__new(value); \
        if (this != NULL) { \
            va_list args; \
            va_start(args, subTree); \
            while (subTree) { \
                cgTreeOf##TYPENAME##_addSubTree(this, subTree); \
                if (cgAppState_isExceptionRaised(cgAppState__getInstance())) \
                    break; \
                subTree = va_arg(args, cgTreeOf##TYPENAME*); \
            } \
            va_end(args); \
        } \
        return this; \
    } \
    \
    cgTreeOf##TYPENAME* cgTreeOf##TYPENAME##_clone(cgTreeOf##TYPENAME* this) { \
        printf("cgTree_clone called, undefined function - aborting!\n"); \
        abort(); \
    } \
    \
    void cgTreeOf##TYPENAME##_delete(cgTreeOf##TYPENAME* this) { \
        cgArrayIterator(cgTreeOf##TYPENAME)* iter = cgArrayIterator__new(cgTreeOf##TYPENAME, this->subTrees); \
        while (cgArrayIterator_isInsideBounds(cgTreeOf##TYPENAME, iter)) { \
            free(cgArrayIterator_getCurrentElement(cgTreeOf##TYPENAME, iter)); \
            cgArrayIterator_moveToNextElement(cgTreeOf##TYPENAME, iter); \
        } \
        free(this); \
    } \
    \
    void cgTreeOf##TYPENAME##_deleteValues(cgTreeOf##TYPENAME* this) { \
        cgArrayOfcgTreeOf##TYPENAME##Iterator* iter = cgArrayOfcgTreeOf##TYPENAME##Iterator__new(this->subTrees); \
        cgTreeOf##TYPENAME* tree = NULL; \
        while ((tree = cgArrayOfcgTreeOf##TYPENAME##Iterator_fetch(iter)) != NULL) { \
            TYPENAME##_delete(cgTreeOf##TYPENAME##_getValue(tree)); \
        } \
        TYPENAME##_delete(this->value); \
    } \
    \
    TYPENAME* cgTreeOf##TYPENAME##_getValue(cgTreeOf##TYPENAME* this) { \
        return this->value; \
    } \
    \
    cgTreeOf##TYPENAME* cgTreeOf##TYPENAME##_getParent(cgTreeOf##TYPENAME* this) { \
        return this->parent; \
    } \
    \
    void cgTreeOf##TYPENAME##_setParent(cgTreeOf##TYPENAME* this, cgTreeOf##TYPENAME* parent) { \
        this->parent = parent; \
    } \
    \
    void cgTreeOf##TYPENAME##_addSubTree(cgTreeOf##TYPENAME* this, cgTreeOf##TYPENAME* subTree) { \
        cgArray_add(cgTreeOf##TYPENAME, this->subTrees, subTree); \
        cgTreeOf##TYPENAME##_setParent(subTree, this); \
    } \
    \
    cgTreeOf##TYPENAME* cgTreeOf##TYPENAME##_getSubTreeAt(cgTreeOf##TYPENAME* this, const unsigned int at) { \
        return cgArray_getValueAt(cgTreeOf##TYPENAME, this->subTrees, at); \
    } \
    \
    cgTreeOf##TYPENAME* cgTreeOf##TYPENAME##_removeSubTreeAt(cgTreeOf##TYPENAME* this, const unsigned int at) { \
        return cgArray_removeValueAt(cgTreeOf##TYPENAME, this->subTrees, at); \
    } \
    \
    cgArrayOfcgTreeOf##TYPENAME* cgTreeOf##TYPENAME##_getSubTrees(cgTreeOf##TYPENAME* this) { \
        return this->subTrees; \
    } \
    \
    unsigned int cgTreeOf##TYPENAME##_getSubTreeSize(cgTreeOf##TYPENAME* this) { \
        return cgArray_getSize(cgTreeOf##TYPENAME, this->subTrees); \
    } \
    \
    /*
        returns true if all leaves were mapped, false otherwise
    */ \
    bool cgTreeOf##TYPENAME##_mapConstantDepthFirst_(cgTreeOf##TYPENAME* this, bool (*mapFunction)(const TYPENAME*, void *), void *userData) { \
        cgArrayOfcgTreeOf##TYPENAME##Iterator* iter = cgArrayOfcgTreeOf##TYPENAME##Iterator__new(this->subTrees); \
        cgTreeOf##TYPENAME* tree; \
        while ((tree = cgArrayOfcgTreeOf##TYPENAME##Iterator_fetch(iter)) != NULL) { \
            if (cgTreeOf##TYPENAME##_mapConstantDepthFirst_(tree, mapFunction, userData) == false) \
                return false; \
        } \
        return mapFunction(cgTreeOf##TYPENAME##_getValue(this), userData); \
    } \
    bool cgTreeOf##TYPENAME##_mapConstantBreadthFirst_(cgTreeOf##TYPENAME* this, bool (*mapFunction)(const TYPENAME*, void *), void *userData, bool isRoot) { \
        cgArrayOfcgTreeOf##TYPENAME##Iterator* iter = cgArrayOfcgTreeOf##TYPENAME##Iterator__new(this->subTrees); \
        cgTreeOf##TYPENAME* tree; \
        if (isRoot == true) { \
            if (mapFunction(cgTreeOf##TYPENAME##_getValue(this), userData) == false) \
                return false; \
        } \
        while ((tree = cgArrayOfcgTreeOf##TYPENAME##Iterator_fetch(iter)) != NULL) { \
            if (mapFunction(cgTreeOf##TYPENAME##_getValue(tree), userData) == false) \
                return false; \
        } \
        cgArrayOfcgTreeOf##TYPENAME##Iterator_reset(iter); \
        while ((tree = cgArrayOfcgTreeOf##TYPENAME##Iterator_fetch(iter)) != NULL) { \
            if (cgTreeOf##TYPENAME##_mapConstantBreadthFirst_(tree, mapFunction, userData, false) == false) \
                return false; \
        } \
        return true; \
    } \
    bool cgTreeOf##TYPENAME##_mapConstant(cgTreeOf##TYPENAME* this, bool (*mapFunction)(const TYPENAME*, void *), cgTreeStrategy strategy, void *userData) { \
        if (strategy == cgTreeStrategy_depthFirst) \
            return cgTreeOf##TYPENAME##_mapConstantDepthFirst_(this, mapFunction, userData); \
        else \
            return cgTreeOf##TYPENAME##_mapConstantBreadthFirst_(this, mapFunction, userData, true); \
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

#define cgTree(TYPENAME) cgTreeOf##TYPENAME


/* callers */


#define cgTree__new(TYPENAME, value) cgTreeOf##TYPENAME##__new((value))
#define cgTree__newFromInitializerList(TYPENAME, value, ...) cgTreeOf##TYPENAME##__newFromInitializerList((value), __VA_ARGS__)
/* NOTE: clone for container types does not provide a deep copy, as we cannot know the signature of the constructors of the hosted types */
#define cgTree_clone(TYPENAME, tree) cgTreeOf##TYPENAME##_clone((tree))
#define cgTree_getValue(TYPENAME, tree) cgTreeOf##TYPENAME##_getValue((tree))
#define cgTree_delete(TYPENAME, tree) cgTreeOf##TYPENAME##_delete((tree))
#define cgTree_deleteValues(TYPENAME, tree) cgTreeOf##TYPENAME##_deleteValues((tree))
#define cgTree_addSubTree(TYPENAME, tree, subTree) cgTreeOf##TYPENAME##_addSubTree((tree), (subTree))
#define cgTree_getSubTrees(TYPENAME, tree) cgTreeOf##TYPENAME##_getSubTrees((tree))
#define cgTree_getSubTreeSize(TYPENAME, tree) cgTreeOf##TYPENAME##_getSubTreeSize((tree))
#define cgTree_getSubTreeAt(TYPENAME, tree, at) cgTreeOf##TYPENAME##_getSubTreeAt((tree), (at))
#define cgTree_removeSubTreeAt(TYPENAME, tree, at) cgTreeOf##TYPENAME##_removeSubTreeAt((tree), (at))
#define cgTree_mapConstant(TYPENAME, tree, function, strategy, userData) cgTreeOf##TYPENAME##_mapConstant((tree), (function), (strategy), (userData))
#define cgTree_getParent(TYPENAME, tree) cgTreeOf##TYPENAME##_getParent((tree))
#define cgTree_setParent(TYPENAME, tree, parent) cgTreeOf##TYPENAME##_setParent((tree), (parent))

#endif 
