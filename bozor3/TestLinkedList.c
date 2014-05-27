#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "LinkedList.h"

typedef struct {
    char *name;
    void *value;
} Binding;

int compare(void *a, void *b) {
    Binding *b1 = (Binding *)a;
    Binding *b2 = (Binding *)b;

    return strcmp(b1->name, b2->name);
}

main() {
    // test using default compare
    LinkedList *lst = LinkedList_create(NULL, NULL);
    char a = 'a';
    LinkedList_add(lst, &a);
    char *x = LinkedList_get(lst, 0);
    assert(*x == a);
    assert(x == &a);
    assert(lst->size == 1);
    assert(*(char *)LinkedList_lookup(lst, &a) == a);

    // add a second item
    char b = 'b';
    LinkedList_add(lst, &b);
    x = LinkedList_get(lst, 0);
    assert(*x == b);
    assert(lst->size == 2);
    assert(*(char *)LinkedList_lookup(lst, &b) == b);
    assert((char *)LinkedList_lookup(lst, &b) == &b);

    // check that a is still there
    assert(*(char *)LinkedList_lookup(lst, &a) == a);
    assert(*(char *)LinkedList_get(lst, 1) == a);

    // test clone
    LinkedList *copy = LinkedList_clone(lst);
    assert(*(char *)LinkedList_get(copy, 0) == 'b');
    assert(*(char *)LinkedList_get(copy, 1) == 'a');
    b = 'c';
    assert(*(char *)LinkedList_lookup(lst, &b) == b);
    assert((char *)LinkedList_lookup(lst, &b) == &b);
    assert(LinkedList_lookup(copy, &b) == NULL);


    // test using custom comparator plust structures for data
    LinkedList *env = LinkedList_create(compare, NULL);
    Binding b1;  
    b1.name = "c"; 
    int value = 7;
    b1.value = &value;
    LinkedList_add(env, &b1);
    Binding *result = LinkedList_lookup(env, &b1);
    char name = *result->name;
    assert(name == *b1.name);
    assert(value == *(int *)result->value);
    assert(env->size == 1);

    // test adding a second element to env
    Binding b2;
    b2.name = "hello";
    value = 13;
    b2.value = &value;
    LinkedList_add(env, &b2);
    result = LinkedList_lookup(env, &b2);
    assert(*b2.name == *result->name);
    assert(value == *(int *)result->value);
    
    // make sure first binding is still there
    result = LinkedList_lookup(env, &b1);
    name = *result->name;
    assert(name == *b1.name);
    assert(value == *(int *)result->value);
    assert(env->size == 2);
}
