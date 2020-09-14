//===============================================
#include "GDate.h"
#include "GManager.h"
//===============================================
static GDateO* m_GDateO = 0;
//===============================================
static void GDate_Test(int argc, char** argv);
//===============================================
static void GDate_Date(char* buffer);
static void GDate_Time(char* buffer);
static void GDate_DateTime(char* buffer);
//===============================================
GDateO* GDate_New() {
	GDateO* lObj = (GDateO*)malloc(sizeof(GDateO));

	lObj->Delete = GDate_Delete;
	lObj->Test = GDate_Test;
	lObj->Date = GDate_Date;
	lObj->Time = GDate_Time;
	lObj->DateTime = GDate_DateTime;
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

}
//===============================================
static void GDate_Time(char* buffer) {

}
//===============================================
static void GDate_DateTime(char* buffer) {

}
//===============================================
