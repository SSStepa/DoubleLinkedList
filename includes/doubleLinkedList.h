#ifndef DOUBLE_LINKED_LIST

#include <stdio.h>

struct doubleLinkedListNode_t {
    int val;
    doubleLinkedListNode_t *next;
    doubleLinkedListNode_t *prev;
};


struct doubleLinkedList_t {
    size_t head;
    size_t tail;
    doubleLinkedListNode_t *list;
};



#endif