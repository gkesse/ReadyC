//===============================================
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//===============================================
void GDate_Read(char* buffer);
//===============================================
int main(int argc, char** argv) {
    char lDate[256];
    GDate_Read(lDate);
    printf("%-20s : %s\n", "DATE", lDate);
    return 0;
}
//===============================================
void GDate_Read(char* buffer) {
    time_t lRawTime;
    time(&lRawTime);
    struct tm* lTimeInfo = localtime(&lRawTime);
    int lDay = lTimeInfo->tm_mday;
    int lMonth = lTimeInfo->tm_mon + 1;
    int lYear = lTimeInfo->tm_year + 1900;
    int lHour = lTimeInfo->tm_hour;
    int lMin = lTimeInfo->tm_min;
    int lSec = lTimeInfo->tm_sec;
    if(lTimeInfo->tm_isdst > 1) lHour =+ lTimeInfo->tm_isdst;
    sprintf(buffer, "%02d/%02d/%04d %02d:%02d:%02d", lDay, lMonth, lYear, lHour, lMin, lSec);
}
//===============================================