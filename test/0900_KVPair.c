#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include"cgAppState.h"
#include"cgInteger.h"
#include"cgString.h"

typedef struct {
    cgString* firstName;
    cgString* lastName;
} Person;

#include"cgKVPair.h"

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

DECLARE_KV_PAIR_TYPE(cgString, Person)
DECLARE_KV_PAIR_FUNCS(cgString, Person)
DEFINE_KV_PAIR(cgString, Person)

DECLARE_KV_PAIR_TYPE(cgString, cgString)
DECLARE_KV_PAIR_FUNCS(cgString, cgString)
DEFINE_KV_PAIR(cgString, cgString)

cgAppState *appState;

void testNewDelete() {
    printf("%s... ", __func__);

    cgString* s1 = cgString__new("s1");
    Person* p1 = Person__new(cgString__new("vorname"), cgString__new("nachname"));

    cgKVPair(cgString, Person)* spPair = cgKVPair__new(cgString, Person, s1, p1);
    assert(cgKVPair_getKey(cgString, Person, spPair) == s1);
    assert(cgKVPair_getValue(cgString, Person, spPair) == p1);

    cgKVPair_deleteValues(cgString, Person, spPair);
    cgKVPair_delete(cgString, Person, spPair);

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

void testGetterSetter() {
    printf("%s... ", __func__);

    cgString* key1 = cgString__new("key1");
    cgString* key2 = cgString__new("key2");
    cgString* value1 = cgString__new("value1");
    cgString* value2 = cgString__new("value2");

    cgKVPair(cgString, cgString)* ssPair = cgKVPair__new(cgString, cgString, key1, value1);

    assert(cgKVPair_getKey(cgString, cgString, ssPair) == key1);
    assert(cgKVPair_getValue(cgString, cgString, ssPair) == value1);

    cgKVPair_setKey(cgString, cgString, ssPair, key2);
    cgKVPair_setValue(cgString, cgString, ssPair, value2);

    assert(cgKVPair_getKey(cgString, cgString, ssPair) == key2);
    assert(cgKVPair_getValue(cgString, cgString, ssPair) == value2);

    cgString_deleteAll(key1, key2, value1, value2, NULL);
    cgKVPair_delete(cgString, cgString, ssPair);


    printf("ok -- ");
}

int main() {
    printf("=== %s ===\n", __FILE__);

    cgAppState__init(__FILE__);
    appState = cgAppState__getInstance();
    testNewDelete();
    testClone();

    cgAppState__deInit();
    printf("=== %s ok ===\n", __FILE__);
    return 0;
}
