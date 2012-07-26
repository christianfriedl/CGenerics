
#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>

#define DEBUG 1

#include"cgAppState.h"
#include"cgInteger.h"
#include"cgString.h"
#include"cgKVPair.h"
#include"cgHashMap.h"

typedef struct {
    cgString* firstName;
    cgString* lastName;
} Person;


Person* Person__new(cgString* firstName, cgString* lastName) {
    Person* this = malloc(sizeof(*this));
    if (this != NULL) {
        this->firstName = firstName;
        this->lastName = lastName;
    } else
        cgAppState_THROW(cgAppState__getInstance(), Severity_fatal, cgExceptionID_GeneralFatalException, "unable to allocate Person");
    return this;
}
        

Person* Person_clone(Person* this) {
    return Person__new(cgString_clone(this->firstName), cgString_clone(this->lastName));
}
void Person_delete(Person* this) {
    cgString_delete(this->firstName);
    cgString_delete(this->lastName);
    free(this);
}

INIT_ARRAY(cgString)

DECLARE_KV_PAIR_TYPE(cgString, Person)
DECLARE_KV_PAIR_FUNCS(cgString, Person)
DEFINE_KV_PAIR(cgString, Person)

DECLARE_KV_PAIR_TYPE(cgString, cgString)
DECLARE_KV_PAIR_FUNCS(cgString, cgString)
DEFINE_KV_PAIR(cgString, cgString)

DECLARE_ARRAY(cgKVPairOfcgStringcgString)
DEFINE_ARRAY(cgKVPairOfcgStringcgString)

DECLARE_HASH_MAP_TYPE(cgString, cgString)
DECLARE_HASH_MAP_FUNCS(cgString, cgString)
DEFINE_HASH_MAP(cgString, cgString)

cgAppState *appState;

void testNewDelete() {
    printf("%s... ", __func__);

    cgString* s1 = cgString__new("s1");
    cgString* s2 = cgString__new("s2");
    cgKVPair(cgString, cgString)* spPair = cgKVPair__new(cgString, cgString, s1, s2);

    cgHashMap(cgString, cgString)* map = cgHashMap__new(cgString, cgString);

    cgHashMap_deleteValues(cgString, cgString, map);
    cgHashMap_delete(cgString, cgString, map);

    printf("ok -- ");
}

void testClone() {
    printf("%s... ", __func__);

    cgString* s1 = cgString__new("s1");
    Person* p1 = Person__new(cgString__new("vorname"), cgString__new("nachname"));

    cgKVPair(cgString, Person)* spPair = cgKVPair__new(cgString, Person, s1, p1);
    cgKVPair(cgString, Person)* spPair2 = cgKVPair_clone(cgString, Person, spPair);

    assert(cgString__compare(s1, cgKVPair_getKey(cgString, Person, spPair2)) == 0);
    assert(cgString__compare(p1->firstName, (cgKVPair_getValue(cgString, Person, spPair2))->firstName) == 0);
    assert(cgString__compare(p1->lastName, (cgKVPair_getValue(cgString, Person, spPair2))->lastName) == 0);
    assert(cgKVPair_getKey(cgString, Person, spPair2) != s1);
    assert(cgKVPair_getValue(cgString, Person, spPair2) != p1);

    cgKVPair_deleteValues(cgString, Person, spPair);
    cgKVPair_delete(cgString, Person, spPair);
    cgKVPair_deleteValues(cgString, Person, spPair2);
    cgKVPair_delete(cgString, Person, spPair2);


    printf("ok -- ");
}

void testAddPair() {
    printf("%s... ", __func__);

    cgString* key1 = cgString__new("key1");
    cgString* value1 = cgString__new("value1");
    cgString* key2 = cgString__new("key2");
    cgString* value2 = cgString__new("value2");

    cgHashMap(cgString, cgString)* map = cgHashMap__new(cgString, cgString);
    cgHashMap_add(cgString, cgString, map, key1, value1);
    if (cgAppState_isExceptionRaised(cgAppState__getInstance()))
        printf("%s\n", cgException_getMsg(cgAppState_catchException(cgAppState__getInstance())));
    cgHashMap_add(cgString, cgString, map, key2, value2);
    if (cgAppState_isExceptionRaised(cgAppState__getInstance()))
        printf("%s\n", cgException_getMsg(cgAppState_catchException(cgAppState__getInstance())));

    assert(cgHashMap_get(cgString, cgString, map, key1) == value1);
    assert(cgHashMap_get(cgString, cgString, map, key2) == value2);

    cgString_deleteAll(key1, key2, value1, value2, NULL);


    printf("ok -- ");
}

void testAddSamePair() {
    printf("%s... ", __func__);

    cgString* key1 = cgString__new("key1");
    cgString* value1 = cgString__new("value1");
    cgString* key2 = cgString__new("key2");
    cgString* value2 = cgString__new("value2");

    cgHashMap(cgString, cgString)* map = cgHashMap__new(cgString, cgString);
    cgHashMap_add(cgString, cgString, map, key1, value1);
    cgHashMap_add(cgString, cgString, map, key1, value1);
    cgArray(cgString)* foundValues = cgHashMap_getAll(cgString, cgString, map, key1);
    assert(cgArray_getSize(cgString, foundValues) == 2);
    assert(cgArray_getValueAt(cgString, foundValues, 0) == value1);
    assert(cgArray_getValueAt(cgString, foundValues, 1) == value1);

    cgString_deleteAll(key1, key2, value1, value2, NULL);


    printf("ok -- ");
}

void testGetKeysAndValues() {
    printf("%s... ", __func__);

    cgString* key1 = cgString__new("key1");
    cgString* value1 = cgString__new("value1");
    cgString* key2 = cgString__new("key2");
    cgString* value2 = cgString__new("value2");

    cgHashMap(cgString, cgString)* map = cgHashMap__new(cgString, cgString);
    cgHashMap_add(cgString, cgString, map, key1, value1);
    cgHashMap_add(cgString, cgString, map, key2, value2);
    cgArray(cgString)* foundKeys = cgHashMap_getKeys(cgString, cgString, map);
    assert(cgArray_getSize(cgString, foundKeys) == 2);
    assert(cgArray_getValueAt(cgString, foundKeys, 0) == key1);
    assert(cgArray_getValueAt(cgString, foundKeys, 1) == key2);

    cgArray(cgString)* foundValues = cgHashMap_getValues(cgString, cgString, map);
    assert(cgArray_getSize(cgString, foundValues) == 2);
    assert(cgArray_getValueAt(cgString, foundValues, 0) == value1);
    assert(cgArray_getValueAt(cgString, foundValues, 1) == value2);

    cgString_deleteAll(key1, key2, value1, value2, NULL);


    printf("ok -- ");
}

int main() {
    printf("=== %s ===\n", __FILE__);

    cgAppState__init(__FILE__);
    appState = cgAppState__getInstance();
    testNewDelete();
    testClone();
    testAddPair();
    testAddSamePair();
    testGetKeysAndValues();

    cgAppState__deInit();
    printf("=== %s ok ===\n", __FILE__);
    return 0;
}
