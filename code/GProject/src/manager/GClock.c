//===============================================
#include "GClock.h"
//===============================================
static GClockO* m_GClockO = 0;
//===============================================
static long GClock_GetClock();
static long GClock_GetClockPerSec();
static double GClock_GetSecond(long clock);
//===============================================
GClockO* GClock_New() {
    GClockO* lObj = (GClockO*)malloc(sizeof(GClockO));
    lObj->Delete = GClock_Delete;
    lObj->GetClock = GClock_GetClock;
    lObj->GetClockPerSec = GClock_GetClockPerSec;
    lObj->GetSecond = GClock_GetSecond;
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
static long GClock_GetClock() {
#if defined(__unix)
    long lClock = clock();
	return lClock;
#endif
	return 0;
}
//===============================================
static long GClock_GetClockPerSec() {
#if defined(__unix)
    long lClockPerSec = CLOCKS_PER_SEC;
	return lClockPerSec;
#endif
	return 0;
}
//===============================================
static double GClock_GetSecond(long clockTick) {
#if defined(__unix)
    double lSecond = (double)clockTick/CLOCKS_PER_SEC;
	return lSecond;
#endif
	return 0.0;
}
//===============================================
