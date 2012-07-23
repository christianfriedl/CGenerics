
#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>

#define DEBUG 1

#include"CGAppState.h"
#include"CGInteger.h"
#include"CGString.h"
#include"CGKVPair.h"
#include"CGHashMap.h"

typedef struct {
    CGString* firstName;
    CGString* lastName;
} Person;


Person* Person__new(CGString* firstName, CGString* lastName) {
    Person* this = malloc(sizeof(*this));
    if (this != NULL) {
        this->firstName = firstName;
        this->lastName = lastName;
    } else
        CGAppState_THROW(CGAppState__getInstance(), Severity_fatal, CGExceptionID_GeneralFatalException, "unable to allocate Person");
    return this;
}
        

Person* Person_clone(Person* this) {
    return Person__new(CGString_clone(this->firstName), CGString_clone(this->lastName));
}
void Person_delete(Person* this) {
    CGString_delete(this->firstName);
    CGString_delete(this->lastName);
    free(this);
}

INIT_ARRAY(CGString)

DECLARE_KV_PAIR_TYPE(CGString, Person)
DECLARE_KV_PAIR_FUNCS(CGString, Person)
DEFINE_KV_PAIR(CGString, Person)

DECLARE_KV_PAIR_TYPE(CGString, CGString)
DECLARE_KV_PAIR_FUNCS(CGString, CGString)
DEFINE_KV_PAIR(CGString, CGString)

DECLARE_ARRAY(CGKVPairOfCGStringCGString)
DEFINE_ARRAY(CGKVPairOfCGStringCGString)

DECLARE_HASH_MAP_TYPE(CGString, CGString)
DECLARE_HASH_MAP_FUNCS(CGString, CGString)
DEFINE_HASH_MAP(CGString, CGString)

CGAppState *appState;

void testNewDelete() {
    printf("%s... ", __func__);

    CGString* s1 = CGString__new("s1");
    CGString* s2 = CGString__new("s2");
    CGKVPair(CGString, CGString)* spPair = CGKVPair__new(CGString, CGString, s1, s2);

    CGHashMap(CGString, CGString)* map = CGHashMap__new(CGString, CGString);

    CGHashMap_deleteValues(CGString, CGString, map);
    CGHashMap_delete(CGString, CGString, map);

    printf("ok -- ");
}

void testClone() {
    printf("%s... ", __func__);

    CGString* s1 = CGString__new("s1");
    Person* p1 = Person__new(CGString__new("vorname"), CGString__new("nachname"));

    CGKVPair(CGString, Person)* spPair = CGKVPair__new(CGString, Person, s1, p1);
    CGKVPair(CGString, Person)* spPair2 = CGKVPair_clone(CGString, Person, spPair);

    assert(CGString__compare(s1, CGKVPair_getKey(CGString, Person, spPair2)) == 0);
    assert(CGString__compare(p1->firstName, (CGKVPair_getValue(CGString, Person, spPair2))->firstName) == 0);
    assert(CGString__compare(p1->lastName, (CGKVPair_getValue(CGString, Person, spPair2))->lastName) == 0);
    assert(CGKVPair_getKey(CGString, Person, spPair2) != s1);
    assert(CGKVPair_getValue(CGString, Person, spPair2) != p1);

    CGKVPair_deleteValues(CGString, Person, spPair);
    CGKVPair_delete(CGString, Person, spPair);
    CGKVPair_deleteValues(CGString, Person, spPair2);
    CGKVPair_delete(CGString, Person, spPair2);


    printf("ok -- ");
}

void testAddPair() {
    printf("%s... ", __func__);

    CGString* key1 = CGString__new("key1");
    CGString* value1 = CGString__new("value1");
    CGString* key2 = CGString__new("key2");
    CGString* value2 = CGString__new("value2");

    CGHashMap(CGString, CGString)* map = CGHashMap__new(CGString, CGString);
    CGHashMap_add(CGString, CGString, map, key1, value1);
    if (CGAppState_isExceptionRaised(CGAppState__getInstance()))
        printf("%s\n", CGException_getMsg(CGAppState_catchException(CGAppState__getInstance())));
    CGHashMap_add(CGString, CGString, map, key2, value2);
    if (CGAppState_isExceptionRaised(CGAppState__getInstance()))
        printf("%s\n", CGException_getMsg(CGAppState_catchException(CGAppState__getInstance())));

    assert(CGHashMap_get(CGString, CGString, map, key1) == value1);
    assert(CGHashMap_get(CGString, CGString, map, key2) == value2);

    CGString_deleteAll(key1, key2, value1, value2, NULL);


    printf("ok -- ");
}

void testAddSamePair() {
    printf("%s... ", __func__);

    CGString* key1 = CGString__new("key1");
    CGString* value1 = CGString__new("value1");
    CGString* key2 = CGString__new("key2");
    CGString* value2 = CGString__new("value2");

    CGHashMap(CGString, CGString)* map = CGHashMap__new(CGString, CGString);
    CGHashMap_add(CGString, CGString, map, key1, value1);
    CGHashMap_add(CGString, CGString, map, key1, value1);
    CGArray(CGString)* foundValues = CGHashMap_getAll(CGString, CGString, map, key1);
    assert(CGArray_getSize(CGString, foundValues) == 2);
    assert(CGArray_getValueAt(CGString, foundValues, 0) == value1);
    assert(CGArray_getValueAt(CGString, foundValues, 1) == value1);

    CGString_deleteAll(key1, key2, value1, value2, NULL);


    printf("ok -- ");
}

void testGetKeysAndValues() {
    printf("%s... ", __func__);

    CGString* key1 = CGString__new("key1");
    CGString* value1 = CGString__new("value1");
    CGString* key2 = CGString__new("key2");
    CGString* value2 = CGString__new("value2");

    CGHashMap(CGString, CGString)* map = CGHashMap__new(CGString, CGString);
    CGHashMap_add(CGString, CGString, map, key1, value1);
    CGHashMap_add(CGString, CGString, map, key2, value2);
    CGArray(CGString)* foundKeys = CGHashMap_getKeys(CGString, CGString, map);
    assert(CGArray_getSize(CGString, foundKeys) == 2);
    assert(CGArray_getValueAt(CGString, foundKeys, 0) == key1);
    assert(CGArray_getValueAt(CGString, foundKeys, 1) == key2);

    CGArray(CGString)* foundValues = CGHashMap_getValues(CGString, CGString, map);
    assert(CGArray_getSize(CGString, foundValues) == 2);
    assert(CGArray_getValueAt(CGString, foundValues, 0) == value1);
    assert(CGArray_getValueAt(CGString, foundValues, 1) == value2);

    CGString_deleteAll(key1, key2, value1, value2, NULL);


    printf("ok -- ");
}

int main() {
    printf("=== %s ===\n", __FILE__);

    CGAppState__init(__FILE__);
    appState = CGAppState__getInstance();
    testNewDelete();
    testClone();
    testAddPair();
    testAddSamePair();
    testGetKeysAndValues();

    CGAppState__deInit();
    printf("=== %s ok ===\n", __FILE__);
    return 0;
}
