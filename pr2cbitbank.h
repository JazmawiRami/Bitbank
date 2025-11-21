#ifndef __CBITBANK_H__
#define __CBITBANK_H__

#include <stdio.h>
#include "Cbitbank.h"


/******************************************************************************/
/*                                                                            
 * File: pr2cbitbank.h
 * Description: Header file for the CBITBANK module
 * Author: David Avdat 
 * Copyright (C) 2025 David Avdat
 */
/*******************************************************************************/

/*
 * An ADT module interface for managing bank branches.
 *
 * Below you'll find the functions you need to implement for this module.
 * Each function has a description of what it should do and what its input and output are.
 * 
 * You should not change the function prototypes or the defined types.
 * 
 * *** NOTE! ***
 * Each function that returns CbitResult may return one of the following in addition to the description:
 * CBIT_SUCCESS, CBIT_OUT_OF_MEMORY or CBIT_NULL_ARGUMENT
 * 
 */

/* The ADT main structure type definition */
typedef struct Cbitbank_s *Cbitbank;

/*
 * Function: CbitbankCreate
 * Parameters:
 *           None
 * Returns:
 *           A new Cbitbank instance
 * Description:
 *           Creates a new CBITBANK instance.
 */
Cbitbank CbitbankCreate(void);
/******************************************************************************/

/*
 * Function: CbitbankDestroy
 * Parameters:
 *           bank - a pointer to the Cbitbank instance to destroy
 * Returns:
 *           None
 * Description:
 *           Destroys the given Cbitbank instance.
 */
void CbitbankDestroy(Cbitbank bank);
/******************************************************************************/

/*
 * Function: CbitbankAddBranch
 * Parameters:
 *           bank - a pointer to the Cbitbank instance
 *           id - the ID of the branch to add
 *           name - the name of the branch
 *           country - the country of the branch
 *           type - the type of the branch
 *           revenue - the annual revenue of the branch
 *           expenses - the annual expenses of the branch
 *           location - the GPS coordinates of the branch
 * Returns:
 *           CBIT_INVALID_ID if the ID is invalid (negative or zero).
 *           CBIT_INVALID_TYPE if the type is invalid.
 *           CBIT_INVALID_REVENUE if the revenue is negative.
 *           CBIT_INVALID_EXPENSES if the expenses are negative.
 *           CBIT_INVALID_GPS_COORD if the GPS coordinates are invalid.
 *           CBIT_BRANCH_ALREADY_EXISTS if a branch with the same ID already exists.
 * Description:
 *           Adds a new branch to the given Cbitbank instance.
 */
CbitResult CbitbankAddBranch(Cbitbank bank, int id, const char *name,
    const char *country, CbitbankType type, double revenue, double expenses,
    GpsCoord location);
/******************************************************************************/


/*
 * Function: CbitbankRemoveBranch
 * Parameters:
 *           bank - a pointer to the Cbitbank instance
 *           id - the ID of the branch to remove
 * Returns:
 *           CBIT_INVALID_ID if the ID is invalid (negative or zero).
 *           CBIT_BRANCH_DOESNT_EXIST if a branch with the given ID does not exist.
 * Description:
 *           Removes a branch from the given Cbitbank instance.
 */
CbitResult CbitbankRemoveBranch(Cbitbank bank, int id);
/******************************************************************************/


/*
 * Function: CbitbankUpdateRevenue
 * Parameters:
 *           bank - a pointer to the Cbitbank instance
 *           id - the ID of the branch to get
 *          revenue - the new revenue of the branch
 * Returns:
 *           CBIT_INVALID_ID if the ID is invalid (negative or zero).
 *           CBIT_BRANCH_DOESNT_EXIST if a branch with the given ID does not exist.
 *           CBIT_INVALID_REVENUE if the revenue is negative.
 * Description:
 *          Updates the revenue of a branch in the given Cbitbank instance.
 */
CbitResult CbitbankUpdateRevenue(Cbitbank bank, int id, double revenue);
/******************************************************************************/


/*
 * Function: CbitbankUpdateExpenses
 * Parameters:
 *           bank - a pointer to the Cbitbank instance
 *           id - the ID of the branch to get
 *          expenses - the new expenses of the branch
 * Returns:
 *           CBIT_INVALID_ID if the ID is invalid (negative or zero).
 *           CBIT_BRANCH_DOESNT_EXIST if a branch with the given ID does not exist.
 *           CBIT_INVALID_EXPENSES if the expenses are negative.
 * Description:
 *          Updates the expenses of a branch in the given Cbitbank instance.
 */
CbitResult CbitbankUpdateExpenses(Cbitbank bank, int id, double expenses);
/******************************************************************************/


/*
 * Function: CbitbankMerge
 * Parameters:
 *           bank1 - a pointer to the first Cbitbank instance
 *           bank2 - a pointer to the second Cbitbank instance
 *           merged - [out] a pointer to the merged Cbitbank instance
 * Returns:
 *           CBIT_BRANCH_ALREADY_EXISTS if a branch with the same ID exists
 *           in both bank1 and bank2.
 * Description:
 *           Merges two Cbitbank instances into a new one.
 *           The merged instance will contain all branches from both banks.
 * 
 * ** NOTE! **
 * The merged instance will be created using the CbitbankCreate function.
 * The caller is responsible for destroying the merged instance using
 * CbitbankDestroy.
 */
 CbitResult CbitbankMerge(Cbitbank bank1, Cbitbank bank2, /* OUT */ Cbitbank *merged);
 /******************************************************************************/


/*
 * Function: CbitbankReportClosestBranch
 * Parameters:
 *           bank - a pointer to the Cbitbank instance
 *           type - the type of the branch to report
 *           myLocation - the GPS coordinates of the user
 *           outChannel - the output channel to write the report to
 * 
 * Returns:
 *           CBIT_INVALID_TYPE if the type is invalid.
 *           CBIT_INVALID_GPS_COORD if the GPS coordinates are invalid.
 *           CBIT_NO_BRANCHES if there are no branches in the bank.
 * Description:
 *          Gets a branch from the given Cbitbank instance.
 */
CbitResult CbitbankReportClosestBranch(Cbitbank bank, CbitbankType type,
    GpsCoord myLocation, FILE *outChannel);
/******************************************************************************/

/*
 * Function: CbitbankReportUnprofitableBranches
 * Parameters:
 *           bank - a pointer to the Cbitbank instance
 *           outChannel - the output channel to write the report to
 * 
 * Returns:
 *           CBIT_NO_BRANCHES if there are no branches in the bank.
 * Description:
 *          Gets all unprofitable branches from the given Cbitbank instance.
 */
CbitResult CbitbankReportUnprofitableBranches(Cbitbank bank, FILE *outChannel);
/******************************************************************************/


/*
 * Function: CbitbankReportCountryBranches
 * Parameters:
 *           bank - a pointer to the Cbitbank instance
 *           country - the country of the branches to report
 *           type - the type of the branches to report
 *           outChannel - the output channel to write the report to
 * 
 * Returns:
 *           CBIT_INVALID_TYPE if the type is invalid.
 *           CBIT_NO_BRANCHES if there are no branches in the bank.
 * Description:
 *          Gets all branches from the given Cbitbank instance that are in a specific country.
 */
CbitResult CbitbankReportCountryBranches(Cbitbank bank, const char *country,
    CbitbankType type, FILE *outChannel);
/******************************************************************************/


#endif /* __CBITBANK_H__ */