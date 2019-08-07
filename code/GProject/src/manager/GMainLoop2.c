//===============================================
#include "GMainLoop2.h"
#include "GPause.h"
#include "GAlarm.h"
//===============================================
static GMainLoop2O* m_GMainLoop2O = 0;
//===============================================
static void GMainLoop2_Exec();
//===============================================
GMainLoop2O* GMainLoop2_New() {
    GMainLoop2O* lObj = (GMainLoop2O*)malloc(sizeof(GMainLoop2O));
    lObj->Delete = GMainLoop2_Delete;
    lObj->Exec = GMainLoop2_Exec;
    return lObj;
}
//===============================================
void GMainLoop2_Delete() {
    GMainLoop2O* lObj = GMainLoop2();
    if(lObj != 0) {
        free(lObj);
    }
    m_GMainLoop2O = 0;
}
//===============================================
GMainLoop2O* GMainLoop2() {
    if(m_GMainLoop2O == 0) {
        m_GMainLoop2O = GMainLoop2_New();
    }
    return m_GMainLoop2O;
}
//===============================================
static void GMainLoop2_Exec() {
	while(1) {
        GPause()->Pause();
        GAlarm()->Exec();
    }
}
//===============================================
