#ifndef __PR2EX3_H__
#define __PR2EX3_H__

#define LAT_MIN (-90)
#define LAT_MAX (+90)
#define LON_MIN (-180)
#define LON_MAX (+180)

typedef enum {FALSE, TRUE} Cbool;

 /* Result type and values for Cbitbank module */
typedef enum {
    CBIT_SUCCESS,
    CBIT_OUT_OF_MEMORY,
    CBIT_NULL_ARGUMENT,
    CBIT_INVALID_ID,
    CBIT_INVALID_TYPE,
    CBIT_INVALID_REVENUE,
    CBIT_INVALID_EXPENSES,
    CBIT_INVALID_GPS_COORD,
    CBIT_BRANCH_ALREADY_EXISTS,
    CBIT_BRANCH_DOESNT_EXIST,
    CBIT_NO_BRANCHES
} CbitResult;

/* Cbitbank branches types */
typedef enum CbitbankType_t {
    CBIT_TYPE_REGULAR,
    CBIT_TYPE_CENTRAL,
    CBIT_TYPE_MORTGAGE,
    CBIT_TYPE_INVESTMENT,
    CBIT_TYPE_BUSINESS,
    CBIT_TYPE_SELF_SERVICE,
    CBIT_TYPE_ALL
} CbitbankType;


typedef struct {
    double latitude;
    double longitude;
} GpsCoord;

double GpsCoordDistance(GpsCoord *loc1, GpsCoord *loc2);

void prog2_report_branch(int id, const char *name, CbitbankType type, const char *country,
    GpsCoord *location, double revenue, double expenses, FILE* outChannel);

void prog2_report_error(CbitResult res);

#endif