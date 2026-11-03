#include "../includes/doubleLinkedList.h"

WORK_RES ListCtor(doubleLinkedList_t *list ON_DBG(, const char *listVariableName, const char *fileCreationName, const char *functionCreationName, int lineCreationNumber))
{
    assert(list);
    assert(listVariableName);
    assert(fileCreationName);
    assert(functionCreationName);
    assert(lineCreationNumber > 0);

    WORK_RES statusCode = OK;

    $INFO("STARTING initialization of list %s", ++listVariableName); // to skip "&" in the begining of name
    ON_DBG(
        if (list -> list != NULL || list -> free != 0)
            return $ERR(WRIN, "CAN'T INIT LIST WITH VALUES");
    )

    list -> free        = 1;
    list -> listLen     = LIST_INIT_SIZE;
    list -> nodesAmount = 0;
    list -> list    = (doubleLinkedListNode_t *) calloc(LIST_INIT_SIZE, sizeof(doubleLinkedListNode_t));
    if (list -> list == NULL) {
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
        RUN_COMMAND(ListDump(list), "WRONG LIST TO DUMP");
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

WORK_RES ListGetHead(doubleLinkedList_t *list, size_t *headInd)
{
    assert(list);
    assert(headInd);

    WORK_RES statusCode = OK;

    $INFO("STARTING getting head of list %s", (list -> debuggingInfo).VariableName);
    ON_DBG(
        RUN_COMMAND(ListVerify(list), "WRONG LIST WHILE TRYING TO GET HEAD");
        RUN_COMMAND(ListDump(list), "WRONG LIST TO DUMP");
    )

    *headInd = (list -> list)[0].next;

    $INFO("ENDING getting head of list %s", (list -> debuggingInfo).VariableName);

    return statusCode;
}

WORK_RES ListGetTail(doubleLinkedList_t *list, size_t *tailInd)
{
    assert(list);
    assert(tailInd);

    WORK_RES statusCode = OK;

    $INFO("STARTING getting tail of list %s", (list -> debuggingInfo).VariableName);
    ON_DBG(
        RUN_COMMAND(ListVerify(list), "WRONG LIST WHILE TRYING TO GET TAIL");
        RUN_COMMAND(ListDump(list), "WRONG LIST TO DUMP");
    )

    *tailInd = (list -> list)[0].prev;

    $INFO("ENDING getting tail of list %s", (list -> debuggingInfo).VariableName);

    return statusCode;
}

WORK_RES ListGetNextElem(doubleLinkedList_t *list, size_t ind, size_t *nextInd)
{
    assert(list);
    assert(nextInd);

    WORK_RES statusCode = OK;

    $INFO("STARTING getting next element of list %s to <%zu> element", (list -> debuggingInfo).VariableName, ind);
    ON_DBG(
        RUN_COMMAND(ListVerify(list), "WRONG LIST WHILE TRYING TO GET NEXT ELEMENT TO INDEX");
        RUN_COMMAND(ListDump(list), "WRONG LIST TO DUMP");
        if (ind == (size_t) (list -> list)[0].prev || (list -> list)[ind].prev == -1)
            return $ERR(WRIN, "WRONG INDEX TO GET ELEMENT");
    )

    *nextInd = (list -> list)[ind].next;

    $INFO("ENDING getting next element of list %s to <%zu> element", (list -> debuggingInfo).VariableName, ind);

    return statusCode;
}

WORK_RES ListGetPrevElem(doubleLinkedList_t *list, size_t ind, size_t *prevInd)
{
    assert(list);
    assert(prevInd);

    WORK_RES statusCode = OK;

    $INFO("STARTING getting prev element of list %s to <%zu> element", (list -> debuggingInfo).VariableName, ind);
    ON_DBG(
        RUN_COMMAND(ListVerify(list), "WRONG LIST WHILE TRYING TO GET PREV ELEMENT");
        RUN_COMMAND(ListDump(list), "WRONG LIST TO DUMP");
        if (ind == (size_t) (list -> list)[0].next || (list -> list)[ind].prev == -1)
            return $ERR(WRIN, "WRONG INDEX TO GET ELEMENT");
    )

    *prevInd = (list -> list)[ind].prev;

    $INFO("ENDING getting prev element of list %s to <%zu> element", (list -> debuggingInfo).VariableName, ind);

    return statusCode;
}

WORK_RES ListGetElementByNumber(doubleLinkedList_t *list, size_t numberInList, size_t *elemInd)
{
    assert(list);
    assert(elemInd);

    WORK_RES statusCode = OK;

    $INFO("STARTING getting element of list %s to with number <%zu>", (list -> debuggingInfo).VariableName, numberInList);
    ON_DBG(
        RUN_COMMAND(ListVerify(list), "WRONG LIST WHILE TRYING TO GET ELEMENT BY IT'S NUMBER");
        RUN_COMMAND(ListDump(list), "WRONG LIST TO DUMP");
        if (numberInList <= list -> nodesAmount || numberInList == 0)
            return $ERR(WRIN, "WRONG INDEX TO GET ELEMENT");
    )

    ssize_t nodeInd = 0;
    for (size_t ind = 0; ind <= numberInList; ind++) {
        nodeInd = (list -> list)[nodeInd].next;
    }

    *elemInd = nodeInd;

    $INFO("ENDING getting element of list %s to with number <%zu>", (list -> debuggingInfo).VariableName, numberInList);

    return OK;
}

WORK_RES ListGetElementByValue(doubleLinkedList_t *list, listNodeVal nodeVal, size_t *elemInd)
{
    assert(list);
    assert(elemInd);

    WORK_RES statusCode = OK;

    $INFO("STARTING getting first element of list %s to with value <%d>", (list -> debuggingInfo).VariableName, nodeVal);
    ON_DBG(
        RUN_COMMAND(ListVerify(list), "WRONG LIST WHILE TRYING TO GET ELEMENT BY IT'S NUMBER");
        RUN_COMMAND(ListDump(list), "WRONG LIST TO DUMP");
    )

    *elemInd = 0;
    for (size_t ind = 0; ind < list -> listLen; ind++) {
        *elemInd = (list -> list)[*elemInd].next;
        if ((list -> list)[*elemInd].val == nodeVal) {
            $INFO("ENDING getting element of list %s to with value <%d>", (list -> debuggingInfo).VariableName, nodeVal);
            return OK;
        }
    }

    $INFO("ENDING getting first element of list %s to with value <%d>", (list -> debuggingInfo).VariableName, nodeVal);

    return $ERR(WRIN, "NO SUCH ELEMENT IN LIST");
}

WORK_RES ListResizeUp(doubleLinkedList_t *list)
{
    assert(list);

    WORK_RES statusCode = OK;

    $INFO("STARTING resizing up list %s", (list -> debuggingInfo).VariableName);
    ON_DBG(
        RUN_COMMAND(ListVerify(list), "WRONG LIST BEFORE RESIZE");
        RUN_COMMAND(ListDump(list),   "WRONG LIST TO DUMP");
    )

    doubleLinkedListNode_t *temp = (doubleLinkedListNode_t *) realloc(list -> list, sizeof(doubleLinkedListNode_t) * (list -> listLen) * 2);
    if (temp == NULL)
        return $ERR(NOMEM, "NOT ENOUGH MEMORY TO RESIZE UP");
    list -> list = temp;

    RUN_COMMAND(InitFreeValuesList(&((list -> list)[list -> listLen]), list -> listLen, list -> listLen), "ERROR WHILE INITING NEW VALUES");
    list -> listLen *= 2;

    ON_DBG(
        RUN_COMMAND(ListVerify(list), "WRONG LIST AFTER RESIZE");
        RUN_COMMAND(ListDump(list),   "WRONG LIST TO DUMP");
    )
    $INFO("ENDING resizing up list %s", (list -> debuggingInfo).VariableName);
    return statusCode;
}

WORK_RES ListAddNewNode(doubleLinkedList_t *list, size_t NodeInd, listNodeVal NodeVal)
{
    assert(list);

    WORK_RES statusCode = OK;

    $INFO("STARTING adding new element to list %s after <%zu>", (list -> debuggingInfo).VariableName, NodeInd);
    ON_DBG(
        RUN_COMMAND(ListVerify(list), "WRONG LIST WHILE TRYING TO ADD NEW ELEMENT");
        RUN_COMMAND(ListDump(list),   "WRONG LIST TO DUMP");
    )

    size_t freeTemp = (list -> list)[list -> free].next;

    (list -> list)[list -> free].val                  = NodeVal;
    (list -> list)[list -> free].next                 = (list -> list)[NodeInd].next;
    (list -> list)[(list -> list)[NodeInd].next].prev = list -> free;
    (list -> list)[list -> free].prev                 = NodeInd;
    (list -> list)[NodeInd].next                      = list -> free;

    list -> nodesAmount++;

    list -> free = freeTemp;
    if (list -> free == -1) {
        RUN_COMMAND(ListResizeUp(list), "PROBLEM WHILE TRYING TO RESIZE LIST UP");
    }
    
    ON_DBG(
        RUN_COMMAND(ListVerify(list), "WRONG LIST AFTER ADDING NEW ELEMENT");
        RUN_COMMAND(ListDump(list),   "WRONG LIST TO DUMP");
    )
    $INFO("ENDING adding new element to list %s after <%zu>", (list -> debuggingInfo).VariableName, NodeInd);

    return statusCode;
}

WORK_RES ListDeleteNode(doubleLinkedList_t *list, size_t NodeInd)
{
    assert(list);

    WORK_RES statusCode = OK;

    $INFO("STARTING deleting element form list %s with index <%zu>", (list -> debuggingInfo).VariableName, NodeInd);

    ON_DBG(
        RUN_COMMAND(ListVerify(list), "WRONG LIST BEFORE DELETING ELEMENT");
        RUN_COMMAND(ListDump(list),   "WRONG LIST TO DUMP");
        if (NodeInd == 0 || NodeInd >= list -> listLen || (list -> list)[NodeInd].prev == -1)
            return $ERR(WRIN, "WRONG INPUT DATA FOR FUNCTION TO DELETE NODE");
    )

    (list -> list)[(list -> list)[NodeInd].next].prev = (list -> list)[NodeInd].prev;
    (list -> list)[(list -> list)[NodeInd].prev].next = (list -> list)[NodeInd].next;

    (list -> list)[NodeInd].next = list -> free;
    (list -> list)[NodeInd].prev = -1;

    list -> nodesAmount--;
    list -> free = NodeInd;

    ON_DBG(
        (list -> list)[NodeInd].val = POISON_VAL;
        RUN_COMMAND(ListVerify(list), "WRONG LIST AFTER DELETING ELEMENT");
        RUN_COMMAND(ListDump(list),   "WRONG LIST TO DUMP");
    )

    $INFO("ENDING deleting element form list %s with index <%zu>", (list -> debuggingInfo).VariableName, NodeInd);
    return OK;
}

WORK_RES ListDump(doubleLinkedList_t *list)
{
    assert(list);

    WORK_RES statusCode = OK;

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

    LOG_PRINTF("List text dump:\n");
    LOG_PRINTF("free = <%zd>\nnodesAmount = <%zu>\nlistLen = <%zu>\n", list -> free, list -> nodesAmount, list -> listLen);
    LOG_PRINTF("val        next       prev\n");
    for (size_t ind = 0; ind < list -> listLen; ind++) {
        LOG_PRINTF("<%4d>  <%4zd>  <%4zd>\n", (list -> list)[ind].val, (list -> list)[ind].next, (list -> list)[ind].prev);
    }
    LOG_PRINTF("List text dump end\n");
    LOG_PRINTF("List graphviz dump:\n");

    char *fileWithPictureName = {};
    RUN_COMMAND(GenerateGraphvizFile(list, &fileWithPictureName), "PROBLEM WHILE TRYING TO GENERATE GRAPHVIZ FILE");
    LOG_PRINTF("<img src=\"%s\">", fileWithPictureName);
    free(fileWithPictureName);

    LOG_PRINTF("List graphviz dump end\n");

    LOG_PRINTF("<h2>END of the list dump</h2>\n<hr>\n")
    LOG_END();

    return OK;
}

WORK_RES ListVerify(doubleLinkedList_t *list)
{
    assert(list);

    if (list -> nodesAmount >= list -> listLen)
        return $ERR(WRIN, "LIST STRUCTURE IS UNVALID: NODES AMOUNT IS BIGGER THEN LIST LEN");
    
    ssize_t node = 0;
    for (size_t ind = 0; ind <= list -> nodesAmount; ind++) {
        if ((list -> list)[node].prev == -1)
            return $ERR(WRLINK, "ELEMENT WITH PREV -1 IN LIST <%s> AT NODE <%zu>", list -> debuggingInfo.VariableName, node);

        if ((list -> list)[(list -> list)[node].next].prev != node)
            return $ERR(WRLINK, "NEXT != PREV IN LIST <%s> WITH NODE <%zu>", list -> debuggingInfo.VariableName, node);

        if ((list -> list)[node].next >= (ssize_t) list -> listLen)
            return $ERR(WRLINK, "ELEMENT WITH IND <%zu> POINTS OUT OF LIST", node);
        
        node = (list -> list)[node].next;
    }
    if (node != 0)
        return $ERR(WRLINK, "DOES NOT CAME BACK TO THE 0 NODE NOW AT <%zu>", node);
    
    if (list -> free != -1)
        node = (size_t) list -> free;
    else
        return $ERR(WRIN, "FULL LIST WAS GIVEN TO VERIFY");

    for (size_t ind = 0; ind < list -> listLen - list -> nodesAmount - 2; ind++) {
        if ((list -> list)[node].prev != -1)
            return $ERR(WRLINK, "NOT BLANK NODE IN LIST FREE WITH INDEX <%zu>", node);

        if ((list -> list)[node].next >= (ssize_t) list -> listLen)
            return $ERR(WRLINK, "FREE ELEMENT WITH IND <%zu> POINTS OUT OF LIST to <%zd>", node, (list -> list)[node].next);
        node = (list -> list)[node].next;
    }
    if ((list -> list)[node].next != -1)
        return $ERR(WRLINK, "LAST ELELEMENT IF FREE WITH INDEX <%zu> DOESN'T HAVE -1 IN NEXT FIELD", node);

    return OK;
}

WORK_RES InitLogDir()
{
    time_t rawtime;
    struct tm *timeinfo;
    char folderName[NAME_MAX_LENGTH];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(folderName, sizeof(folderName), "%Y-%m-%d_%H-%M-%S", timeinfo);
    if (_mkdir(folderName) != 0)
        return $ERR(WRIN, "ERROR WHILE TRYING TO CREATE LOG FOLDER");
    if (_chdir(folderName) != 0)
        return $ERR(WRIN, "ERROR WHILE TRYING TO CD LOG FOLDER");
    
    return OK;
}

WORK_RES GenerateGraphvizFile(doubleLinkedList_t *list, char **PictureFileName)
{
    assert(list);
    static size_t callNum = 0;
    callNum++;
    char commandName[MAX_MESS_LENGTH] = {};
    char *fileName = (char *) calloc(NAME_MAX_LENGTH, sizeof(char));
    sprintf(fileName, "%s.txt", GRAPHVIZ_FILE_BASE);

    FILE *outFile = fopen(fileName, "w");
    if (outFile == NULL)
        return $ERR(WRIN, "IMPOSSIBLE TO OPEN GRAPHVIZ FILE");

    fprintf(outFile, "digraph {\nrankdir = LR;\nsplines=true;\n");
    fprintf(outFile, "node [shape=Mrecord, style=filled]\n");

    const char *color     = "";
    const char *fillColor = "";
    for (size_t ind = 0; ind < list -> listLen; ind++) {
        if (ind == 0) {
            color     = "#171917";
            fillColor = "#888a88";
        } else if ((list -> list)[ind].prev >= 0) {
            color     = "#008000";
            fillColor = "#c0FFc0";
        } else if ((list -> list)[ind].prev == -1) {
            color     = "#000080";
            fillColor = "#c0c0FF";
        } else {
            color     = "#800000";
            fillColor = "#e43131";
        }
        fprintf(outFile, "N%zu [label=\" <n> Index: %zu | {prev: %zd | next: %zd} | <p> Val: %d\", fillcolor=\"%s\", color=\"%s\"];\n",
            ind, ind, (list -> list)[ind].prev, (list -> list)[ind].next, (list -> list)[ind].val, fillColor, color);
    }
    for (size_t ind = 0; ind < list -> listLen - 1; ind++) {
        fprintf(outFile, "N%zu -> N%zu[color=\"white\", weight=100];\n", ind, ind + 1);
    }

    const char *lineStyle = "";
    const char *placeToCon = "";
    for (ssize_t ind = 0; ind < (ssize_t) list -> listLen - 1; ind++) {
        lineStyle = "";
        if ((list -> list)[(list -> list)[ind].next].prev != ind) {
            if ((list -> list)[(list -> list)[ind].next].prev != -1) {
                lineStyle = "color=\"#e62222\", penwidth=3, constraint=false, tailport=nw, headport=ne";
                placeToCon = ":n";
            } else 
                placeToCon = ":p";
        } else {
            lineStyle = "dir=both, tailport=nw, headport=ne";
            placeToCon = ":n";
        }
        fprintf(outFile, "N%zu%s -> N%zu%s [%s];\n", ind, placeToCon, (list -> list)[ind].next, placeToCon, lineStyle);
    }

    fprintf(outFile, "Head [color=\"#846a04\", fillcolor=\"#f5f74e\"];\n");
    fprintf(outFile, "Tail [color=\"#5d0367\", fillcolor=\"#db4ef7\"];\n");
    fprintf(outFile, "Free [color=\"#090969\", fillcolor=\"#5454ff\"];\n");
    
    fprintf(outFile, "Head -> N%zu:n [color=\"#846a04\"];\n", (list -> list)[0].next);
    fprintf(outFile, "Tail -> N%zu:p [color=\"#5d0367\"];\n", (list -> list)[0].prev);
    fprintf(outFile, "Free -> N%zu:p [color=\"#090969\"];\n", list -> free);

    fprintf(outFile, "}\n");

    fclose(outFile);

    sprintf(fileName, "%s%zu.png", GRAPHVIZ_FILE_BASE, callNum);
    sprintf(commandName, "\"\"C:\\Program Files\\Graphviz\\bin\\dot.exe\" .\\dumpGraphviz.txt -Tpng -o .\\%s\"", fileName);
    system(commandName);
    *PictureFileName = fileName;

    return OK;
}
