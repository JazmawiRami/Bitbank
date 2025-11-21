#include "pr2cbitbank.h"

#define HANDLE_RESULT(res, operation)                          \
    do                                                         \
    {                                                          \
        printf("[%s:%d] %s\n", __func__, __LINE__, operation); \
        if (res != CBIT_SUCCESS)                               \
        {                                                      \
            prog2_report_error(res);                           \
        }                                                      \
    } while (0)

static const GpsCoord loc1 = {34.0522, -118.2437};  // Los Angeles
static const GpsCoord loc2 = {40.7128, -74.0060};   // New York
static const GpsCoord loc3 = {51.5074, -0.1278};    // London
static const GpsCoord loc4 = {35.6895, 139.6917};   // Tokyo
static const GpsCoord loc5 = {48.8566, 2.3522};     // Paris
static const GpsCoord loc6 = {55.7558, 37.6173};    // Moscow
static const GpsCoord loc7 = {37.7749, -122.4194};  // San Francisco
static const GpsCoord loc8 = {52.5200, 13.4050};    // Berlin
static const GpsCoord loc9 = {41.9028, 12.4964};    // Rome
static const GpsCoord loc10 = {39.9042, 116.4074};  // Beijing
static const GpsCoord loc11 = {19.4326, -99.1332};  // Mexico City
static const GpsCoord loc12 = {55.6761, 12.5683};   // Copenhagen
static const GpsCoord loc13 = {37.9838, 23.7275};   // Athens
static const GpsCoord loc14 = {59.9139, 10.7522};   // Oslo
static const GpsCoord loc15 = {34.0522, -118.2437}; // Los Angeles (duplicate for testing)
static const GpsCoord loc16 = {40.7128, -74.0060};  // New York (duplicate for testing)

void test_1(void)
{
    Cbitbank bank = CbitbankCreate();
    if (!bank)
    {
        fprintf(stderr, "[ERROR] Failed to create Cbitbank instance\n");
        return;
    }

    HANDLE_RESULT(CbitbankAddBranch(bank, 1, "Branch A", "USA", CBIT_TYPE_REGULAR, 1000000, 500000, loc1), "Adding Branch A");
    HANDLE_RESULT(CbitbankAddBranch(bank, 2, "Branch B", "USA", CBIT_TYPE_CENTRAL, 2000000, 1000000, loc2), "Adding Branch B");
    HANDLE_RESULT(CbitbankAddBranch(bank, 3, "Branch C", "UK", CBIT_TYPE_MORTGAGE, 1500000, 700000, loc3), "Adding Branch C");
    HANDLE_RESULT(CbitbankAddBranch(bank, 4, "Branch D", "Japan", CBIT_TYPE_INVESTMENT, 2500000, 1200000, loc4), "Adding Branch D");
    HANDLE_RESULT(CbitbankAddBranch(bank, 5, "Branch E", "France", CBIT_TYPE_BUSINESS, 1800000, 800000, loc5), "Adding Branch E");
    HANDLE_RESULT(CbitbankAddBranch(bank, 6, "Branch F", "Russia", CBIT_TYPE_SELF_SERVICE, 1200000, 600000, loc6), "Adding Branch F");
    HANDLE_RESULT(CbitbankAddBranch(bank, 7, "Branch G", "USA", CBIT_TYPE_REGULAR, 1100000, 550000, loc7), "Adding Branch G");
    HANDLE_RESULT(CbitbankAddBranch(bank, 8, "Branch H", "Germany", CBIT_TYPE_CENTRAL, 2200000, 1050000, loc8), "Adding Branch H");
    HANDLE_RESULT(CbitbankAddBranch(bank, 9, "Branch I", "Italy", CBIT_TYPE_MORTGAGE, 1600000, 750000, loc9), "Adding Branch I");
    HANDLE_RESULT(CbitbankAddBranch(bank, 10, "Branch J", "China", CBIT_TYPE_INVESTMENT, 2700000, 1300000, loc10), "Adding Branch J");
    HANDLE_RESULT(CbitbankAddBranch(bank, 11, "Branch K", "Mexico", CBIT_TYPE_BUSINESS, 1900000, 850000, loc11), "Adding Branch K");
    HANDLE_RESULT(CbitbankAddBranch(bank, 12, "Branch L", "Denmark", CBIT_TYPE_SELF_SERVICE, 1300000, 650000, loc12), "Adding Branch L");
    HANDLE_RESULT(CbitbankAddBranch(bank, 13, "Branch M", "Greece", CBIT_TYPE_REGULAR, 1400000, 700000, loc13), "Adding Branch M");
    HANDLE_RESULT(CbitbankAddBranch(bank, 14, "Branch N", "Norway", CBIT_TYPE_CENTRAL, 2100000, 3000000, loc14), "Adding Branch N");
    HANDLE_RESULT(CbitbankAddBranch(bank, 15, "Branch O", "USA", CBIT_TYPE_REGULAR, 1000000, 500000, loc15), "Adding Branch O");
    HANDLE_RESULT(CbitbankAddBranch(bank, 16, "Branch P", "USA", CBIT_TYPE_CENTRAL, 2000000, 1000000, loc16), "Adding Branch P");
    HANDLE_RESULT(CbitbankAddBranch(bank, 17, "Branch Q", "Sweden", CBIT_TYPE_MORTGAGE, 1700000, 800000, loc1), "Adding Branch Q");
    HANDLE_RESULT(CbitbankAddBranch(bank, 18, "Branch R", "Finland", CBIT_TYPE_INVESTMENT, 2300000, 1100000, loc2), "Adding Branch R");
    HANDLE_RESULT(CbitbankAddBranch(bank, 19, "Branch S", "Spain", CBIT_TYPE_BUSINESS, 2000000, 900000, loc3), "Adding Branch S");

    HANDLE_RESULT(CbitbankRemoveBranch(bank, 1), "Removing Branch A");
    HANDLE_RESULT(CbitbankRemoveBranch(bank, 2), "Removing Branch B");

    HANDLE_RESULT(CbitbankAddBranch(bank, 20, "Branch T", "USA", CBIT_TYPE_REGULAR, 1200000, 600000, loc1), "Adding Branch T");
    HANDLE_RESULT(CbitbankAddBranch(bank, 1, "Branch U", "USA", CBIT_TYPE_REGULAR, 2200000, 1100000, loc2), "Adding Branch U");

    HANDLE_RESULT(CbitbankReportCountryBranches(bank, "USA", CBIT_TYPE_REGULAR, stdout), "Reporting country branches"); // Report all regular branches in the USA
    HANDLE_RESULT(CbitbankReportCountryBranches(bank, "Japan", CBIT_TYPE_ALL, stdout), "Reporting country branches"); // Report all branches in Japan
    HANDLE_RESULT(CbitbankReportCountryBranches(bank, "Germany", CBIT_TYPE_CENTRAL, stdout), "Reporting country branches"); // Report all central branches in Germany

    
    // Report closest branch of type REGULAR to a given location
    GpsCoord myLocation = {34.1411, -119.3452}; // Los Angeles
    HANDLE_RESULT(CbitbankReportClosestBranch(bank, CBIT_TYPE_REGULAR, myLocation, stdout), "Reporting closest regular branch");

    HANDLE_RESULT(CbitbankUpdateRevenue(bank, 3, 660000), "Updating revenue for Branch C");
    HANDLE_RESULT(CbitbankUpdateRevenue(bank, 4, 1100000), "Updating expenses for Branch D");

    HANDLE_RESULT(CbitbankReportUnprofitableBranches(bank, stdout), "Reporting unprofitable branches");

    CbitbankDestroy(bank);
}

void test_2(void)
{
    Cbitbank bank = CbitbankCreate();
    if (!bank)
    {
        fprintf(stderr, "[ERROR] Failed to create Cbitbank instance\n");
        return;
    }
    HANDLE_RESULT(CbitbankAddBranch(bank, 1, "Branch A", "USA", CBIT_TYPE_REGULAR, 1000000, 500000, loc1), "Adding Branch A");
    HANDLE_RESULT(CbitbankAddBranch(bank, 2, "Branch B", "USA", CBIT_TYPE_CENTRAL, 2000000, 1000000, loc2), "Adding Branch B");
    HANDLE_RESULT(CbitbankAddBranch(bank, 3, "Branch C", "UK", CBIT_TYPE_MORTGAGE, 1500000, 700000, loc3), "Adding Branch C");
    HANDLE_RESULT(CbitbankAddBranch(bank, 4, "Branch D", "Japan", CBIT_TYPE_INVESTMENT, 2500000, 1200000, loc4), "Adding Branch D");
    HANDLE_RESULT(CbitbankAddBranch(bank, 5, "Branch E", "France", CBIT_TYPE_BUSINESS, 1800000, 800000, loc5), "Adding Branch E");
    HANDLE_RESULT(CbitbankAddBranch(bank, 6, "Branch F", "Russia", CBIT_TYPE_SELF_SERVICE, 1200000, 600000, loc6), "Adding Branch F");
    HANDLE_RESULT(CbitbankAddBranch(bank, 7, "Branch G", "USA", CBIT_TYPE_REGULAR, 1100000, 550000, loc7), "Adding Branch G");
    HANDLE_RESULT(CbitbankAddBranch(bank, 8, "Branch H", "Germany", CBIT_TYPE_CENTRAL, 2200000, 1050000, loc8), "Adding Branch H");
    HANDLE_RESULT(CbitbankAddBranch(bank, 9, "Branch I", "Italy", CBIT_TYPE_MORTGAGE, 1600000, 750000, loc9), "Adding Branch I");
    HANDLE_RESULT(CbitbankAddBranch(bank, 10, "Branch J", "China", CBIT_TYPE_INVESTMENT, 2700000, 1300000, loc10), "Adding Branch J");
    HANDLE_RESULT(CbitbankAddBranch(bank, 10, "Branch K", "Mexico", CBIT_TYPE_BUSINESS, 1900000, 850000, loc11), "Adding Branch K");
    HANDLE_RESULT(CbitbankAddBranch(bank, 12, "Branch L", "Denmark", CBIT_TYPE_SELF_SERVICE, 1300000, 650000, loc12), "Adding Branch L");
    HANDLE_RESULT(CbitbankAddBranch(bank, 13, "Branch M", "Greece", CBIT_TYPE_REGULAR, -1400000, 700000, loc13), "Adding Branch M");
    HANDLE_RESULT(CbitbankAddBranch(bank, 14, "Branch N", "Norway", CBIT_TYPE_CENTRAL, 2100000, 3000000, loc14), "Adding Branch N");
    HANDLE_RESULT(CbitbankAddBranch(bank, 15, "Branch O", "USA", CBIT_TYPE_REGULAR, 1000000, 500000, loc15), "Adding Branch O");
    HANDLE_RESULT(CbitbankAddBranch(bank, 16, "Branch P", "USA", CBIT_TYPE_CENTRAL, 2000000, 1000000, loc16), "Adding Branch P");
    HANDLE_RESULT(CbitbankAddBranch(bank, 17, "Branch Q", "Sweden", CBIT_TYPE_MORTGAGE, 1700000, 800000, loc1), "Adding Branch Q");
    HANDLE_RESULT(CbitbankAddBranch(bank, 18, "Branch R", "Finland", CBIT_TYPE_INVESTMENT, 2300000, 1100000, loc2), "Adding Branch R");
    HANDLE_RESULT(CbitbankAddBranch(bank, 19, "Branch S", "Spain", CBIT_TYPE_BUSINESS, 2000000, 900000, loc3), "Adding Branch S");


    HANDLE_RESULT(CbitbankRemoveBranch(bank, 1), "Removing Branch A");
    HANDLE_RESULT(CbitbankRemoveBranch(NULL, 2), "Removing Branch B");
    HANDLE_RESULT(CbitbankRemoveBranch(bank, 21), "Removing Branch B");
    HANDLE_RESULT(CbitbankAddBranch(bank, 20, "Branch T", "USA", CBIT_TYPE_REGULAR, 1200000, 600000, loc1), "Adding Branch T");
    HANDLE_RESULT(CbitbankAddBranch(bank, 1, "Branch U", "USA", CBIT_TYPE_REGULAR, 2200000, 1100000, loc2), "Adding Branch U");
    HANDLE_RESULT(CbitbankReportCountryBranches(bank, "USA", CBIT_TYPE_REGULAR, stdout), "Reporting country branches"); // Report all regular branches in the USA
    HANDLE_RESULT(CbitbankReportCountryBranches(bank, "Japania", CBIT_TYPE_ALL, stdout), "Reporting country branches"); // Report all branches in Japan
    HANDLE_RESULT(CbitbankReportCountryBranches(bank, "Germany", CBIT_TYPE_CENTRAL, stdout), "Reporting country branches"); // Report all central branches in Germany
    // Report closest branch of type REGULAR to a given location
    GpsCoord myLocation = {34.1411, -199.3452}; // Los Angeles
    HANDLE_RESULT(CbitbankReportClosestBranch(bank, CBIT_TYPE_REGULAR, myLocation, stdout), "Reporting closest regular branch");
    HANDLE_RESULT(CbitbankUpdateRevenue(bank, 3, 660000), "Updating revenue for Branch C");
    HANDLE_RESULT(CbitbankUpdateRevenue(bank, 4, -1100000), "Updating expenses for Branch D");
    HANDLE_RESULT(CbitbankReportUnprofitableBranches(bank, stdout), "Reporting unprofitable branches");
    CbitbankDestroy(bank);

}

#define TEST_1

int main(void)
{
#ifdef TEST_1
    test_1();
#elif defined(TEST_2)
    test_2();
#endif
    return 0;
}
