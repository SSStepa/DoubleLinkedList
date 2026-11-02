#include "../includes/doubleLinkedList.h"

WORK_RES ListCtor(doubleLinkedList_t *list ON_DBG(, const char *listVariableName, const char *fileCreationName, const char *functionCreationName, int lineCreationNumber))
{
    assert(list);
    assert(listVariableName);
    assert(fileCreationName);
    assert(functionCreationName);
    assert(lineCreationNumber > 0);

    $INFO("STARTING initialization of list %s", ++listVariableName); // to skip "&" in the begining of name
    ON_DBG(
        if (list -> list != NULL || list -> free != 0)
            return $ERR(WRIN, "CAN'T INIT LIST WITH VALUES");
    )

    list -> free        = 1;
    list -> listLen     = LIST_INIT_SIZE;
    list -> nodesAmount = 1;
    list -> list    = (doubleLinkedListNode_t *) calloc(LIST_INIT_SIZE, sizeof(doubleLinkedListNode_t));
    if (list == NULL) {
        return $ERR(NOMEM, "ERROR WHILE TRYING TO CREATE LIST: NOT ENOUGH MEMORY");
    }

    ON_DBG(
        (list -> debuggingInfo).VariableName         = listVariableName;
        (list -> debuggingInfo).fileCreationName     = fileCreationName;
        (list -> debuggingInfo).functionCreationName = functionCreationName;
        (list -> debuggingInfo).lineCreationNumber   = lineCreationNumber;
    )

    InitFreeValuesList((list -> list) + 1, list -> free, LIST_INIT_SIZE - 1);

    ON_DBG(
        RUN_COMMAND(ListVerify(list), "WRONG LIST AFTER CREATING");
        RUN_COMMAND(ListDump(list), "WRONG LIST TO DUMP");
    )
    
    $INFO("ENDING initialization of list %s", listVariableName);

    return OK;
}

WORK_RES InitFreeValuesList(doubleLinkedListNode_t *EllsToInit, size_t indOfFirstElem, size_t ElemAmount)
{
    assert(EllsToInit);

    $INFO("BEGINNING of initing free elements list from <%p> it's index in array is <%zu> and there are <%zu> elements to init", EllsToInit, indOfFirstElem, ElemAmount);
    
    size_t ind = 0;
    for (; ind < ElemAmount; ind++) {
        EllsToInit[ind].next = indOfFirstElem + ind + 1;
        EllsToInit[ind].prev = -1;

        ON_DBG(
            EllsToInit[ind].val = POISON_VAL;
        )
    }
    EllsToInit[--ind].next = -1;

    $INFO("ENDING of initing free elements list");

    return OK;
}

WORK_RES ListDtor(doubleLinkedList_t *list)
{
    assert(list);

    $INFO("BEGINNING of deconstruction of list");

    WORK_RES statusCode = OK;

    ON_DBG(
        RUN_COMMAND(ListVerify(list), "WRONG LIST WHILE TRYING TO DTOR");
    )

    free(list -> list);

    ON_DBG(
        list -> list = 0;
        list -> free = 0;

        (list -> debuggingInfo).VariableName         = "";
        (list -> debuggingInfo).fileCreationName     = "";
        (list -> debuggingInfo).functionCreationName = "";
        (list -> debuggingInfo).lineCreationNumber   = 0;
    )
    
    $INFO("ENDING of deconstruction of list");

    return OK;
}

WORK_RES ListGetHead(doubleLinkedList_t *list, size_t)
{
    assert(list);

    ON_DBG(
        RUN_COMMAND(ListVerify(list), "WRONG LIST WHILE TRYING TO GET HEAD");
    )


}

// WORK_RES ListAddNode(doubleLinkedList_t *list, size_t nodeIndex, listNodeVal val)
// {
//     assert(list);

//     WORK_RES statusCode = OK;

//     ON_DBG(
//         RUN_COMMAND(ListVerify(list), "WRONG LIST TO ADD NODE");
//     )

//     if (nodeIndex == 0) {
//         if (list -> head == 0) {
//             list -> head = 1;
//             list -> tail = 1;
//             (list -> list)[1].next = 0;
//             (list -> list)[1].prev = 0;
//             (list -> list)[1].val  = val;          
//         } else {
//             size_t newHead = 0;
//             RUN_COMMAND(ListGetBlankNode(list, &newHead), "ERROR WHILE TRYING TO FIND BLANK ELEMENT");

//             (list -> list)[newHead].val  = val;
//             (list -> list)[newHead].prev = 0;
//             (list -> list)[newHead].next = list -> head;
//             (list -> list)[list -> head].prev = newHead;
//             list -> head = newHead;
//         }
//     }

//     size_t newNode = 0;
//     RUN_COMMAND(ListGetBlankNode(list, &newNode), "ERROR WHILE TRYING TO FIND BLANK ELEMENT");
    
//     if (nodeIndex == list -> tail) {
//         list -> tail = newNode;
//     } else 
//         (list -> list)[(list -> list)[nodeIndex].next].prev = newNode;
    
//     (list -> list)[newNode].next   = (list -> list)[nodeIndex].next;
//     (list -> list)[newNode].prev   = nodeIndex;
//     (list -> list)[nodeIndex].next = newNode;
//     (list -> list)[newNode].val    = val;

//     ON_DBG(
//         RUN_COMMAND(ListVerify(list), "WRONG LIST TO ADD NODE");
//     )

//     return statusCode;
// }

// WORK_RES ListGetBlankNode(doubleLinkedList_t *list, size_t *indToFill)
// {
//     assert(list);

//     for (size_t ind = 0; ind < list -> listLen; ind++) {
//         if ((list -> list)[ind].next == -1) {
//             *indToFill = ind;
//             return OK;
//         }
//     }

//     doubleLinkedList_t *temp = (doubleLinkedList_t *) realloc(list, (list -> listLen) * RESIZE_UP_SIZE);
//     if (temp == NULL)
//         return $ERR(NOMEM, "NOT ENOUGH MEMORY TO RESIZE LIST UP");
//     list = temp;

//     for (size_t ind = list -> listLen; ind < (list -> listLen) * RESIZE_UP_SIZE; ind++) {
//         (list -> list)[ind].next = -1;
//         (list -> list)[ind].prev = -1;

//         ON_DBG(
//             (list -> list)[ind].val = POISON_VAL;
//         )
//     }

//     *indToFill = list -> listLen;
//     list -> listLen *= RESIZE_UP_SIZE;

//     return OK;
// }

// WORK_RES ListDeleteNode(doubleLinkedList_t *list, size_t nodeIndex)
// {
//     assert(list); //TODO: check if element index is in out data

//     if (nodeIndex == list -> head) {
//         (list -> list)[(list -> list)[nodeIndex].next].prev = 0;
//         list -> head = (list -> list)[nodeIndex].next;

//         (list -> list)[nodeIndex].next = -1;
//         (list -> list)[nodeIndex].prev = -1;

//         ON_DBG(
//             (list -> list)[nodeIndex].val = POISON_VAL;
//         )

//     } else if (nodeIndex == list -> tail) {
//         (list -> list)[(list -> list)[nodeIndex].prev].next = 0;
//         list -> tail = (list -> list)[nodeIndex].prev;

//         (list -> list)[nodeIndex].next = -1;
//         (list -> list)[nodeIndex].prev = -1;

//         ON_DBG(
//             (list -> list)[nodeIndex].val = POISON_VAL;
//         )

//     } else {
//         (list -> list)[(list -> list)[nodeIndex].next].prev = (list -> list)[nodeIndex].prev;
//         (list -> list)[(list -> list)[nodeIndex].prev].next = (list -> list)[nodeIndex].next;
        
//         (list -> list)[nodeIndex].next = -1;
//         (list -> list)[nodeIndex].prev = -1;

//         ON_DBG(
//             (list -> list)[nodeIndex].val = POISON_VAL;
//         )

//     }
    
//     return OK;
// }

WORK_RES ListDump(doubleLinkedList_t *list)
{
    assert(list); // TODO: check that pointer is valid

    LOG_START();
    LOG_PRINTF("<h2>Hi it is BEGINING of the list dump</h2>\n")
    ON_DBG(
        LOG_PRINTF("<h3>This list called %s. It was created in %s:%d by function %s</h3>\n",
            (list -> debuggingInfo).VariableName, 
            (list -> debuggingInfo).fileCreationName,
            (list -> debuggingInfo).lineCreationNumber,
            (list -> debuggingInfo).functionCreationName
        )
        LOG_PRINTF("<h3>It has error status %d and error message <%s> now </h3>\n", (list -> debuggingInfo).err, (list -> debuggingInfo).errorText);
    )

    LOG_PRINTF("Stack text dump:\n");
    LOG_PRINTF("val        next       prev\n");
    for (size_t ind = 0; ind < list -> listLen; ind++) {
        LOG_PRINTF("<%4d>  <%4zd>  <%4zd>\n", (list -> list)[ind].val, (list -> list)[ind].next, (list -> list)[ind].prev);
    }
    LOG_PRINTF("Stack text dump end\n");

    LOG_PRINTF("<h2>END of the list dump</h2>\n<hr>\n")
    LOG_END();

    return OK;
}

WORK_RES ListVerify(doubleLinkedList_t *list)
{
    return OK;
}

// WORK_RES FindListNode(doubleLinkedList_t *list, size_t listNodeNumber)
// {
//     assert(list);

//     WORK_RES statusCode = OK;

//     ON_DBG(
//         RUN_COMMAND(ListVerify(list), "VERIFICATION FAILED WHILE TRYING TO FIND ELEMENT");
//         if (listNodeNumber > list -> nodesAmount) {
//             return $ERR(WRIN, "NUMBER OF LIST ELEMENT IS OUT OF LIST");
//         }
//     )

//     size_t NodeInd = 0;

//     doubleLinkedListNode_t node = list -> head;

//     for (size_t el = 2; el <= listNodeNumber - 1; el++) {
//         NodeInd = node.next;


//     }

// }