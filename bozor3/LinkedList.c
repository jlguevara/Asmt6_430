#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "LinkedList.h"

/* same as strcmp, but takes void pointers */
int LinkedList_compare(void *a, void *b) {
    return strcmp((char *) a, (char *) b);
}

/* default clone */
void *LinkedList_default_clone(void *a) {
    char *c = malloc(sizeof(char));
    *c = *(char *)a;
    return c;
}

/* create a LinkedList, if c is null list will assume node data is 
 * a string and compare data using strcmp */
LinkedList *LinkedList_create(Comparator cmp, Clone clone) {
    LinkedList *lst = malloc(sizeof(LinkedList));
    lst->head = NULL;
    lst->size = 0;
    lst->compare = cmp == NULL ? LinkedList_compare : cmp;
    lst->clone = clone == NULL ? LinkedList_default_clone : clone;
    return lst;
}

/* add item to the front of the list */
void LinkedList_add(LinkedList *lst, void *data) {
    Node *node = malloc(sizeof(Node));
    node->data = data;
    node->next = lst->head; 
    lst->head = node;
    lst->size++;
}

/* get the first element that matches the given key */
void *LinkedList_lookup(LinkedList *lst, void *key) {
    Node *tmp;

    if (lst == NULL || key == NULL)
        return NULL;

    for (tmp = lst->head; tmp; tmp = tmp->next) {
        if (lst->compare(tmp->data, key) == 0)
            return tmp->data;
    }
    return NULL;
}

/* get the element at the specified index. 
 * returns null is index out of range */
void *LinkedList_get(LinkedList *lst, int index) {
    Node *tmp;
    int i;

    if (index < 0 || index > lst->size - 1)
        return NULL;
    for (tmp = lst->head, i = 0; tmp && i != index; tmp = tmp->next, i++)
        ;

    return tmp->data;
}

/* clone a list */
LinkedList *LinkedList_clone(LinkedList *lst) {
    if (lst == NULL)
        return NULL;

    LinkedList *copy = LinkedList_create(lst->compare, lst->clone);
    copy->size = lst->size;

    Node *tmp, *prev = NULL, *current;

    for (current = lst->head; current; current = current->next) {
        tmp = malloc(sizeof(Node));
        tmp->data = lst->clone(current->data);
        tmp->next = NULL;
        if (!prev) 
            copy->head = tmp;
        else
           prev->next = tmp;
       prev = tmp; 
    }

    return copy;
}
