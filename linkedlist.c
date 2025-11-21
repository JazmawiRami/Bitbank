#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"
#include <math.h>

typedef struct Node {
    ListElement data;
    struct Node* next;
} Node;

struct LinkedList_s {
    Node* head;
    Node* current;
    copyListElemFunc copyFunc;
    freeListElemFunc freeFunc;
    printListElemFunc printFunc;
};

ListResult linkedListCreate(LinkedList *list,
                            copyListElemFunc cpyFunc,
                            freeListElemFunc freeFunc,
                            printListElemFunc printFunc)
{
    if (list == NULL || cpyFunc == NULL || freeFunc == NULL || printFunc == NULL)
        return LIST_BAD_ARGUMENTS;

    LinkedList newList = malloc(sizeof(*newList));
    if (newList == NULL)
        return LIST_OUT_OF_MEMORY;

    newList->head = NULL;
    newList->current = NULL;
    newList->copyFunc = cpyFunc;
    newList->freeFunc = freeFunc;
    newList->printFunc = printFunc;

    *list = newList;
    return LIST_SUCCESS;
}

ListResult linkedListDestroy(LinkedList list) {
    if (list == NULL)
        return LIST_BAD_ARGUMENTS;

    Node* temp;
    while (list->head != NULL) {
        temp = list->head;
        list->head = list->head->next;
        list->freeFunc(temp->data);
        free(temp);
    }
    free(list);
    return LIST_SUCCESS;
}

ListResult linkedListInsertLast(LinkedList list, ListElement element) {
    if (list == NULL || element == NULL)
        return LIST_BAD_ARGUMENTS;

    Node* newNode = malloc(sizeof(Node));
    if (newNode == NULL)
        return LIST_OUT_OF_MEMORY;

    newNode->data = list->copyFunc(element);
    if (newNode->data == NULL) {
        free(newNode);
        return LIST_OUT_OF_MEMORY;
    }
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
        list->current = newNode;
        return LIST_SUCCESS;
    }

    Node* temp = list->head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
    return LIST_SUCCESS;
}

ListResult linkedListGoToHead(LinkedList list) {
    if (list == NULL || list->head == NULL)
        return LIST_BAD_ARGUMENTS;

    list->current = list->head;
    return LIST_SUCCESS;
}

ListResult linkedListGoToNext(LinkedList list) {
    if (list == NULL || list->current == NULL || list->current->next == NULL)
        return LIST_BAD_ARGUMENTS;

    list->current = list->current->next;
    return LIST_SUCCESS;
}

ListResult linkedListGetCurrent(LinkedList list, ListElement *element) {
    if (list == NULL || element == NULL || list->current == NULL)
        return LIST_BAD_ARGUMENTS;

    *element = list->current->data;
    return LIST_SUCCESS;
}

ListResult linkedListRemoveCurrent(LinkedList list) {
    if (list == NULL || list->current == NULL)
        return LIST_BAD_ARGUMENTS;

    Node* temp = list->head;
    Node* prev = NULL;

    while (temp != NULL && temp != list->current) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
        return LIST_BAD_ARGUMENTS;

    if (prev == NULL)
        list->head = temp->next;
    else
        prev->next = temp->next;

    Node* nextCurrent = temp->next;
    list->freeFunc(temp->data);
    free(temp);
    list->current = nextCurrent;

    return LIST_SUCCESS;
}

ListResult linkedListFind(LinkedList list, KeyForListElement key, matchListElemFunc matchFunc) {
    if (list == NULL || key == NULL || matchFunc == NULL)
        return LIST_BAD_ARGUMENTS;

    Node* temp = list->head;
    while (temp != NULL) {
        if (matchFunc(temp->data, key)) {
            list->current = temp;
            return LIST_SUCCESS;
        }
        temp = temp->next;
    }

    return LIST_FAIL;
}
