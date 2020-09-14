//===============================================
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//===============================================
const char * G_MONTH_MAP[] = { 
"Janvier", "Fevrier", "Mars", "Avril", "Mai", "Juin", "Juillet",
"Août", "Septembre", "Octobre", "Novembre", "Decembre"
};
//===============================================
const char * G_DAY_MAP[] = {
"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"
};
//===============================================
void GDate_DateTime(char* buffer);
void GDate_DayName(char* buffer);
void GDate_MonthName(char* buffer);
//===============================================
int main(int argc, char** argv) {
    char lDate[256];
    char lDay[256];
    char lMonth[256];
    
    GDate_DateTime(lDate);
    GDate_DayName(lDay);
    GDate_MonthName(lMonth);
    
    printf("%-20s : %s\n", "DATE", lDate);
    printf("%-20s : %s\n", "JOUR", lDay);
    printf("%-20s : %s\n", "MOIS", lMonth);
    return 0;
}
//===============================================
void GDate_DateTime(char* buffer) {
    time_t lRawTime;
    time(&lRawTime);
    struct tm* lTimeInfo = localtime(&lRawTime);
    int lDay = lTimeInfo->tm_mday;
    int lMonth = lTimeInfo->tm_mon + 1;
    int lYear = lTimeInfo->tm_year + 1900;
    int lHour = lTimeInfo->tm_hour;
    int lMin = lTimeInfo->tm_min;
    int lSec = lTimeInfo->tm_sec;
    if(lTimeInfo->tm_isdst > 0) lHour =+ lTimeInfo->tm_isdst;
    sprintf(buffer, "%02d/%02d/%04d %02d:%02d:%02d", lDay, lMonth, lYear, lHour, lMin, lSec);
}
//===============================================
void GDate_DayName(char* buffer) {
    time_t lRawTime;
    time(&lRawTime);
    struct tm* lTimeInfo = localtime(&lRawTime);
    int lWeekDay = lTimeInfo->tm_wday;
    sprintf(buffer, "%s", G_DAY_MAP[lWeekDay]);
}
//===============================================
void GDate_MonthName(char* buffer) {
    time_t lRawTime;
    time(&lRawTime);
    struct tm* lTimeInfo = localtime(&lRawTime);
    int lMonth = lTimeInfo->tm_mon;
    sprintf(buffer, "%s", G_MONTH_MAP[lMonth]);
}
//===============================================