#ifndef DOUBLE_LINKED_LIST
#define DOUBLE_LINKED_LIST

#include <stdio.h>
#include "basic.h"

typedef int listNodeVal;

const int LIST_INIT_SIZE = 20;
const int RESIZE_UP_SIZE = 2;

ON_DBG(
    const listNodeVal POISON_VAL = -6767;
)

struct doubleLinkedListNode_t {
    listNodeVal val;
    ssize_t next;
    ssize_t prev;
};

struct doubleLinkedList_t {
    doubleLinkedListNode_t *list;
    size_t listLen;
    size_t nodesAmount;
    size_t free;

    ON_DBG(
        debuggingInfo_t debuggingInfo;
    )
};

WORK_RES ListCtor(doubleLinkedList_t *list ON_DBG(, const char *listVariableName, const char *fileCreationName, const char *functionCreationName, int lineCreationNumber));
WORK_RES InitFreeValuesList(doubleLinkedListNode_t *EllsToInit, size_t indOfFirstElem, size_t ElemAmount);
WORK_RES ListDtor(doubleLinkedList_t *list);

WORK_RES ListDump(doubleLinkedList_t *list);
WORK_RES ListVerify(doubleLinkedList_t *list);

WORK_RES ListAddNode(doubleLinkedList_t *list, size_t nodeIndex, listNodeVal val);
WORK_RES ListGetBlankNode(doubleLinkedList_t *list, size_t *indToFill);

#define LIST_CTOR(listToCreatePtr) ListCtor(listToCreatePtr ON_DBG(, TO_STR(listToCreatePtr), __FILE__, __FUNCTION__, __LINE__))

#endif