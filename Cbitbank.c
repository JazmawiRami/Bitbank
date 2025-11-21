#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "pr2cbitbank.h"
#include "linked_list.h"
#include "Cbitbank.h"
// Typedef structs in our program

struct Cbitbank_s
{
    LinkedList branchList;
};
// the struct for the diffrent branches the bitbank corp has .
typedef struct Branch_Node
{
    const char *name;
    int id;
    CbitbankType type;
    const char *country;
    double revenue;
    double expenses;
    GpsCoord location;
} *Branch;

// Functions
int branchIdMatchFunc(ListElement element, ListElement key)
{
    if (element == NULL || key == NULL)
        return 0;

    Branch b = (Branch)element;
    int Branch_id = *(int *)key;
    return (b->id == Branch_id);
}
ListElement copyBranch(ListElement element)
{
    if (element == NULL)
        return NULL;
    Branch original = (Branch)element;
    Branch copy = malloc(sizeof(struct Branch_Node));
    if (copy == NULL)
        return NULL;

    copy->name = strdup(original->name);
    copy->country = strdup(original->country);
    copy->id = original->id;
    copy->type = original->type;
    copy->revenue = original->revenue;
    copy->expenses = original->expenses;
    copy->location = original->location;
    return copy;
}
void freeBranch(ListElement element)
{
    if (element == NULL)
        return;

    Branch branchfree = (Branch)element;
    free((char *)branchfree->name);
    free((char *)branchfree->country);
    free(branchfree);
}
void printBranch(FILE *out, ListElement element)
{
    if (element == NULL)
        return;
    Branch b = (Branch)element;
    prog2_report_branch(b->id, b->name, b->type, b->country, &b->location, b->revenue, b->expenses, out);
}

Cbitbank CbitbankCreate(void)
{
    Cbitbank bank = malloc(sizeof(*bank));
    if (bank == NULL)
        return NULL;

    if (linkedListCreate(&bank->branchList, copyBranch, freeBranch, printBranch) != LIST_SUCCESS)
    {
        free(bank);
        return NULL;
    }
    return bank;
}
void CbitbankDestroy(Cbitbank bank)
{
    if (bank == NULL)
        return;

    linkedListDestroy(bank->branchList);
    free(bank);
    return;
}
CbitResult CbitbankAddBranch(Cbitbank bank, int id, const char *name, const char *country, CbitbankType type, double revenue, double expenses,
                             GpsCoord location)
{
    if (bank == NULL || name == NULL || country == NULL)
        return CBIT_NULL_ARGUMENT;

    if (id <= 0)
        return CBIT_INVALID_ID;

    if (revenue < 0)
        return CBIT_INVALID_REVENUE;

    if (expenses < 0)
        return CBIT_INVALID_EXPENSES;

    if (location.latitude < -90 || location.latitude > 90 || location.longitude < -180 || location.longitude > 180)
        return CBIT_INVALID_GPS_COORD;

    // Check if Branch Already Exists
    ListElement element;
    if (linkedListGoToHead(bank->branchList) == LIST_SUCCESS)
    {
        do
        {
            linkedListGetCurrent(bank->branchList, &element);
            Branch b = (Branch)element;
            if (b->id == id)
            {
                return CBIT_BRANCH_ALREADY_EXISTS;
            }
        } while (linkedListGoToNext(bank->branchList) == LIST_SUCCESS);
    }

    Branch new_branch = malloc(sizeof(struct Branch_Node));
    if (new_branch == NULL)
        return CBIT_NULL_ARGUMENT;

    new_branch->name = strdup(name);
    if (new_branch->name == NULL)
    {
        free(new_branch);
        return CBIT_NULL_ARGUMENT;
    }
    new_branch->id = id;
    new_branch->type = type;
    new_branch->country = strdup(country);
    if (new_branch->country == NULL)
    {
        free(new_branch);
        return CBIT_NULL_ARGUMENT;
    }
    new_branch->revenue = revenue;
    new_branch->expenses = expenses;
    new_branch->location = location;
    linkedListInsertLast(bank->branchList, new_branch);
    return CBIT_SUCCESS;
}
CbitResult CbitbankRemoveBranch(Cbitbank bank, int id)
{
    if (bank == NULL)
        return CBIT_NULL_ARGUMENT;

    if (id < 0)
        return CBIT_INVALID_ID;

    ListElement element;
    if (linkedListGoToHead(bank->branchList) == LIST_SUCCESS)
    {
        do
        {
            linkedListGetCurrent(bank->branchList, &element);
            Branch b = (Branch)element;
            if (b->id == id)
            {
                linkedListRemoveCurrent(bank->branchList);
                return CBIT_SUCCESS;
            }
        } while (linkedListGoToNext(bank->branchList) == LIST_SUCCESS);
    }
    return CBIT_BRANCH_DOESNT_EXIST;
}
CbitResult CbitbankUpdateRevenue(Cbitbank bank, int id, double revenue)
{
    if (id < 0)
        return CBIT_INVALID_ID;

    if (revenue < 0)
        return CBIT_INVALID_REVENUE;
    ListElement element;
    if (linkedListGoToHead(bank->branchList) == LIST_SUCCESS)
    {
        do
        {
            linkedListGetCurrent(bank->branchList, &element);
            Branch b = (Branch)element;
            if (b->id == id)
            {
                b->revenue = revenue;
                return CBIT_SUCCESS;
            }
        } while (linkedListGoToNext(bank->branchList) == LIST_SUCCESS);
    }
    return CBIT_BRANCH_DOESNT_EXIST;
}
CbitResult CbitbankUpdateExpenses(Cbitbank bank, int id, double expenses)
{
    if (id < 0)
    {
        return CBIT_INVALID_ID;
    }
    if (expenses < 0)
    {
        return CBIT_INVALID_EXPENSES;
    }

    ListElement element;
    if (linkedListGoToHead(bank->branchList) == LIST_SUCCESS)
    {
        do
        {
            linkedListGetCurrent(bank->branchList, &element);
            Branch b = (Branch)element;
            if (b->id == id)
            {
                b->expenses = expenses;
                return CBIT_SUCCESS;
            }
        } while (linkedListGoToNext(bank->branchList) == LIST_SUCCESS);
    }
    return CBIT_BRANCH_DOESNT_EXIST;
}
CbitResult CbitbankMerge(Cbitbank bank1, Cbitbank bank2, Cbitbank *merged)
{
    if (bank1 == NULL || bank2 == NULL)
        return CBIT_NULL_ARGUMENT;

    Cbitbank newBank = CbitbankCreate();
    {
        if (newBank == NULL)
            return CBIT_OUT_OF_MEMORY;
    }
    *merged = newBank;
    LinkedList list1 = bank1->branchList;
    LinkedList list2 = bank2->branchList;
    LinkedList mergedList = (*merged)->branchList;
    ListElement element;
    // Add all elements from bank1
    if (linkedListGoToHead(list1) == LIST_SUCCESS)
    {
        do
        {

            if (linkedListGetCurrent(list1, &element) != LIST_SUCCESS)
            {
                CbitbankDestroy(*merged);
                return CBIT_OUT_OF_MEMORY;
            }

            if (linkedListInsertLast(mergedList, element) != LIST_SUCCESS)
            {
                CbitbankDestroy(*merged);
                return CBIT_OUT_OF_MEMORY;
            }

        } while (linkedListGoToNext(list1) == LIST_SUCCESS);
    }
    if (linkedListGoToHead(list2) == LIST_SUCCESS)
    {
        do
        {
            if (linkedListGetCurrent(list2, &element) != LIST_SUCCESS)
            {
                CbitbankDestroy(*merged);
                return CBIT_OUT_OF_MEMORY;
            }

            Branch branch2 = (Branch)element;

            // Check for duplicate in newBank
            if (linkedListFind(newBank->branchList, &branch2->id, branchIdMatchFunc) == LIST_SUCCESS)
            {
                CbitbankDestroy(*merged);
                return CBIT_BRANCH_ALREADY_EXISTS;
            }

            if (linkedListInsertLast(newBank->branchList, element) != LIST_SUCCESS)
            {
                CbitbankDestroy(*merged);
                return CBIT_OUT_OF_MEMORY;
            }

        } while (linkedListGoToNext(list2) == LIST_SUCCESS);
    }

    return CBIT_SUCCESS;
}
CbitResult CbitbankReportClosestBranch(Cbitbank bank, CbitbankType type, GpsCoord myLocation, FILE *outChannel)
{
    if (bank == NULL || outChannel == NULL)
        return CBIT_NULL_ARGUMENT;

    if (myLocation.latitude < LAT_MIN || myLocation.latitude > LAT_MAX || myLocation.longitude < LON_MIN || myLocation.longitude > LON_MAX)
        return CBIT_INVALID_GPS_COORD;

    if (type < CBIT_TYPE_REGULAR || type > CBIT_TYPE_ALL)
        return CBIT_INVALID_TYPE;

    ListElement element;
    Branch closest = NULL;
    double minDistance = __DBL_MAX__;

    if (linkedListGoToHead(bank->branchList) == LIST_SUCCESS)
    {
        do
        {
            linkedListGetCurrent(bank->branchList, &element);
            Branch b = (Branch)element;
            if (type == CBIT_TYPE_ALL || b->type == type)
            {
                double distance = GpsCoordDistance(&b->location, &myLocation);
                if (distance < minDistance)
                {
                    minDistance = distance;
                    closest = b;
                }
            }
        } while (linkedListGoToNext(bank->branchList) == LIST_SUCCESS);
    }
    if (closest == NULL)
        return CBIT_NO_BRANCHES;

    prog2_report_branch(closest->id, closest->name, closest->type, closest->country, &closest->location, closest->revenue, closest->expenses, outChannel);
    return CBIT_SUCCESS;
}
CbitResult CbitbankReportUnprofitableBranches(Cbitbank bank, FILE *outChannel)
{
    if (bank == NULL)
        return CBIT_NULL_ARGUMENT;

    ListElement element;
    int count = 0;
    if (linkedListGoToHead(bank->branchList) == LIST_SUCCESS)
    {
        do
        {
            linkedListGetCurrent(bank->branchList, &element);
            Branch b = (Branch)element;
            if (b->revenue < b->expenses)
            {
                prog2_report_branch(b->id, b->name, b->type, b->country, &b->location, b->revenue, b->expenses, outChannel);
                count = 1;
            }
        } while (linkedListGoToNext(bank->branchList) == LIST_SUCCESS);
    }
    if (count == 0)
        return CBIT_NO_BRANCHES;

    return CBIT_SUCCESS;
}

CbitResult CbitbankReportCountryBranches(Cbitbank bank, const char *country, CbitbankType type, FILE *outChannel)
{
    if (bank == NULL || outChannel == NULL || country == NULL)
        return CBIT_NULL_ARGUMENT;

    if (type < CBIT_TYPE_REGULAR || type > CBIT_TYPE_ALL)
        return CBIT_INVALID_TYPE;

    int found = 0;
    ListElement element;
    if (linkedListGoToHead(bank->branchList) == LIST_SUCCESS)
    {
        do
        {
            linkedListGetCurrent(bank->branchList, &element);
            Branch b = (Branch)element;
            if ((b->type == type || type == CBIT_TYPE_ALL) && (strcmp(b->country, country) == 0))
            {
                prog2_report_branch(b->id, b->name, b->type, b->country, &b->location, b->revenue, b->expenses, outChannel);
                found = 1;
            }
        } while (linkedListGoToNext(bank->branchList) == LIST_SUCCESS);
    }
    if (found == 0)
        return CBIT_NO_BRANCHES;

    return CBIT_SUCCESS;
}