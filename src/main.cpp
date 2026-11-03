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
    ListDeleteNode(&linkedList, 1);
    ListDtor(&linkedList);    

    EndLog();

    return 0;
}