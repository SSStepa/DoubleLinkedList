#include "../includes/doubleLinkedList.h"
#include "../includes/basic.h"

int main()
{
    SetUpLog();

    doubleLinkedList_t linkedList = {};

    LIST_CTOR(&linkedList);
    ListDtor(&linkedList);    

    EndLog();

    return 0;
}