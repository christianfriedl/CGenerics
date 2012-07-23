#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include"CGAppState.h"
#include"CGInteger.h"
#include"CGString.h"

typedef struct {
    CGString* firstName;
    CGString* lastName;
} Person;

#include"CGKVPair.h"

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

DECLARE_KV_PAIR_TYPE(CGString, Person)
DECLARE_KV_PAIR_FUNCS(CGString, Person)
DEFINE_KV_PAIR(CGString, Person)

DECLARE_KV_PAIR_TYPE(CGString, CGString)
DECLARE_KV_PAIR_FUNCS(CGString, CGString)
DEFINE_KV_PAIR(CGString, CGString)

CGAppState *appState;

void testNewDelete() {
    printf("%s... ", __func__);

    CGString* s1 = CGString__new("s1");
    Person* p1 = Person__new(CGString__new("vorname"), CGString__new("nachname"));

    CGKVPair(CGString, Person)* spPair = CGKVPair__new(CGString, Person, s1, p1);
    assert(CGKVPair_getKey(CGString, Person, spPair) == s1);
    assert(CGKVPair_getValue(CGString, Person, spPair) == p1);

    CGKVPair_deleteValues(CGString, Person, spPair);
    CGKVPair_delete(CGString, Person, spPair);

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

void testGetterSetter() {
    printf("%s... ", __func__);

    CGString* key1 = CGString__new("key1");
    CGString* key2 = CGString__new("key2");
    CGString* value1 = CGString__new("value1");
    CGString* value2 = CGString__new("value2");

    CGKVPair(CGString, CGString)* ssPair = CGKVPair__new(CGString, CGString, key1, value1);

    assert(CGKVPair_getKey(CGString, CGString, ssPair) == key1);
    assert(CGKVPair_getValue(CGString, CGString, ssPair) == value1);

    CGKVPair_setKey(CGString, CGString, ssPair, key2);
    CGKVPair_setValue(CGString, CGString, ssPair, value2);

    assert(CGKVPair_getKey(CGString, CGString, ssPair) == key2);
    assert(CGKVPair_getValue(CGString, CGString, ssPair) == value2);

    CGString_deleteAll(key1, key2, value1, value2, NULL);
    CGKVPair_delete(CGString, CGString, ssPair);


    printf("ok -- ");
}

int main() {
    printf("=== %s ===\n", __FILE__);

    CGAppState__init(__FILE__);
    appState = CGAppState__getInstance();
    testNewDelete();
    testClone();

    CGAppState__deInit();
    printf("=== %s ok ===\n", __FILE__);
    return 0;
}
