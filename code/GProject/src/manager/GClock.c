//===============================================
#include "GClock.h"
#include "GMap2.h"
//===============================================
GDECLARE_MAP(GClock, GCHAR_PTR, GVOID_PTR)
GDEFINE_MAP(GClock, GCHAR_PTR, GVOID_PTR)
//===============================================
static GClockO* m_GClockO = 0;
//===============================================
static void GClock_Start(char* clockId);
static void GClock_End(char* clockId);
static double GClock_Time(char* clockId);
//===============================================
GClockO* GClock_New() {
    GClockO* lObj = (GClockO*)malloc(sizeof(GClockO));

    lObj->m_startMap = GMap_New(GClock, GCHAR_PTR, GVOID_PTR)();
    lObj->m_endMap = GMap_New(GClock, GCHAR_PTR, GVOID_PTR)();

    lObj->Delete = GClock_Delete;
    lObj->Start = GClock_Start;
    lObj->End = GClock_End;
    lObj->Time = GClock_Time;
    return lObj;
}
//===============================================
void GClock_Delete() {
    GClockO* lObj = GClock();
    if(lObj != 0) {
        free(lObj);
    }
    m_GClockO = 0;
}
//===============================================
GClockO* GClock() {
    if(m_GClockO == 0) {
        m_GClockO = GClock_New();
    }
    return m_GClockO;
}
//===============================================
static void GClock_Start(char* clockId) {
    GMapO(GClock, GCHAR_PTR, GVOID_PTR)* lStartMap = m_GClockO->m_startMap;
    clock_t lStart = clock();
    lStartMap->SetData(lStartMap, clockId, (void*)lStart, GMap_EqualChar);
}
//===============================================
static void GClock_End(char* clockId) {
    GMapO(GClock, GCHAR_PTR, GVOID_PTR)* lEndMap = m_GClockO->m_endMap;
    clock_t lEnd = clock();
    lEndMap->SetData(lEndMap, clockId, (void*)lEnd, GMap_EqualChar);
}
//===============================================
static double GClock_Time(char* clockId) {
    GMapO(GClock, GCHAR_PTR, GVOID_PTR)* lStartMap = m_GClockO->m_startMap;
    GMapO(GClock, GCHAR_PTR, GVOID_PTR)* lEndMap = m_GClockO->m_endMap;
    clock_t lStart = (clock_t)lStartMap->GetData(lStartMap, clockId, GMap_EqualChar);
    clock_t lEnd = (clock_t)lEndMap->GetData(lEndMap, clockId, GMap_EqualChar);
    clock_t lTicks = lEnd - lStart;
    double lTime_ms = ((double)lTicks * 1000) / CLOCKS_PER_SEC;
    return lTime_ms;
}
//===============================================
