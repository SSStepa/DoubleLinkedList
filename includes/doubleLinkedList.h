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

WORK_RES ListGetHead(doubleLinkedList_t *list, size_t *headInd);
WORK_RES ListGetTail(doubleLinkedList_t *list, size_t *tailInd);
WORK_RES ListGetNextElem(doubleLinkedList_t *list, size_t ind, size_t *nextInd);
WORK_RES ListGetPrevElem(doubleLinkedList_t *list, size_t ind, size_t *prevInd);
WORK_RES ListGetElementByNumber(doubleLinkedList_t *list, size_t numberInList, size_t *elemInd);
WORK_RES ListGetElementByValue (doubleLinkedList_t *list, listNodeVal nodeVal, size_t *elemInd);

WORK_RES ListDump(doubleLinkedList_t *list);
WORK_RES ListVerify(doubleLinkedList_t *list);

WORK_RES ListAddNewNode(doubleLinkedList_t *list, size_t nodeInd, listNodeVal nodeVal);
WORK_RES ListDeleteNode(doubleLinkedList_t *list, size_t NodeInd);

#define LIST_CTOR(listToCreatePtr) ListCtor(listToCreatePtr ON_DBG(, TO_STR(listToCreatePtr), __FILE__, __FUNCTION__, __LINE__))

#endif