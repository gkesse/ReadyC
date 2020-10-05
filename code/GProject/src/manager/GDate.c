//===============================================
#include "GDate.h"
#include "GManager.h"
//===============================================
static GDateO* m_GDateO = 0;
//===============================================
static char * G_MONTH_MAP[] = { 
"Janvier", "Fevrier", "Mars", "Avril", "Mai", "Juin", "Juillet",
"Août", "Septembre", "Octobre", "Novembre", "Decembre"
};
//===============================================
static char * G_DAY_MAP[] = {
"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"
};
//===============================================
static void GDate_Test(int argc, char** argv);
//===============================================
static void GDate_Date(char* buffer);
static void GDate_Time(char* buffer);
static void GDate_DateTime(char* buffer);
static void GDate_DateLetter(char* buffer);
//===============================================
GDateO* GDate_New() {
	GDateO* lObj = (GDateO*)malloc(sizeof(GDateO));

	lObj->Delete = GDate_Delete;
	lObj->Test = GDate_Test;
	lObj->Date = GDate_Date;
	lObj->Time = GDate_Time;
	lObj->DateTime = GDate_DateTime;
	lObj->DateLetter = GDate_DateLetter;
	return lObj;
}
//===============================================
void GDate_Delete() {
    GDateO* lObj = GDate();
    if(lObj != 0) {
        free(lObj);
    }
    m_GDateO = 0;
}
//===============================================
GDateO* GDate() {
	if(m_GDateO == 0) {
		m_GDateO = GDate_New();
	}
	return m_GDateO;
}
//===============================================
static void GDate_Test(int argc, char** argv) {

}
//===============================================
static void GDate_Date(char* buffer) {
    time_t lTime = time(0);
    struct tm* lTimeInfo = localtime(&lTime);
    int lDay = lTimeInfo->tm_mday;
    int lMonth = lTimeInfo->tm_mon + 1;
    int lYear = lTimeInfo->tm_year + 1900;
    sprintf(buffer, "%02d/%02d/%04d", lDay, lMonth, lYear);
}
//===============================================
static void GDate_DateLetter(char* buffer) {
    time_t lTime = time(0);
    struct tm* lTimeInfo = localtime(&lTime);
    int lDay = lTimeInfo->tm_mday;
    int lWeekDay = lTimeInfo->tm_wday;
    int lMonth = lTimeInfo->tm_mon;
    int lYear = lTimeInfo->tm_year + 1900;
    char* lWeekDayL = G_DAY_MAP[lWeekDay];
    char* lMonthL = G_MONTH_MAP[lMonth];
    sprintf(buffer, "%s %02d %s %04d", lWeekDayL, lDay, lMonthL, lYear);
}
//===============================================
static void GDate_Time(char* buffer) {
    time_t lTime = time(0);
    struct tm* lTimeInfo = localtime(&lTime);
    int lHour = lTimeInfo->tm_hour;
    int lMin = lTimeInfo->tm_min;
    int lSec = lTimeInfo->tm_sec;
    sprintf(buffer, "%02d:%02d:%02d", lHour, lMin, lSec);
}
//===============================================
static void GDate_DateTime(char* buffer) {
    time_t lTime = time(0);
    struct tm* lTimeInfo = localtime(&lTime);
    int lDay = lTimeInfo->tm_mday;
    int lMonth = lTimeInfo->tm_mon + 1;
    int lYear = lTimeInfo->tm_year + 1900;
    int lHour = lTimeInfo->tm_hour;
    int lMin = lTimeInfo->tm_min;
    int lSec = lTimeInfo->tm_sec;
    sprintf(buffer, "%02d/%02d/%04d %02d:%02d:%02d", lDay, lMonth, lYear, lHour, lMin, lSec);
}
//===============================================
