#include "../includes/doubleLinkedList.h"
#include "../includes/basic.h"

int main()
{
    InitLogDir();
    SetUpLog();

    doubleLinkedList_t linkedList = {};

    LIST_CTOR(&linkedList);
    ListAddNewNode(&linkedList, 0, 5);
    ListAddNewNode(&linkedList, 0, 6);
    ListAddNewNode(&linkedList, 1, 7);
    ListAddNewNode(&linkedList, 1, 7);
    ListAddNewNode(&linkedList, 1, 7);
    ListAddNewNode(&linkedList, 1, 7);
    ListDeleteNode(&linkedList, 1);
    ListDeleteNode(&linkedList, 4);
    ListAddNewNode(&linkedList, 2, 7);
    linkedList.list[3].prev = -20;
    ListDump(&linkedList);

    ListDtor(&linkedList);    

    EndLog();

    return 0;
}