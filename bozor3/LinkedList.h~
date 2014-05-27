#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef int (*Comparator)(void *a, void *b);
typedef void* (*Clone)(void *a);

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int size;
    Comparator compare;
    Clone clone;
} LinkedList;

/* create a LinkedList, if c is null list will assume node data is 
 * a string and compare data using strcmp. It also takes a clone
 * function ptr used for cloning a list */
LinkedList *LinkedList_create(Comparator comp, Clone clone);

/* add item to the front of the list */
void LinkedList_add(LinkedList *lst, void *data);

/* get the first element that matches the given object */
void *LinkedList_lookup(LinkedList *lst, void *key);

/* get the element at the specified index. 
 * returns null is index out of range */
void *LinkedList_get(LinkedList *lst, int index);

/* clone a list */
LinkedList *LinkedList_clone(LinkedList *lst);

#endif
