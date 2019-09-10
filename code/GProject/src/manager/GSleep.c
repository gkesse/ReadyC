//===============================================
#include "GSleep.h"
//===============================================
static GSleepO* m_GSleepO = 0;
//===============================================
static void GSleep_Sleep(int delay);
//===============================================
GSleepO* GSleep_New() {
    GSleepO* lObj = (GSleepO*)malloc(sizeof(GSleepO));
    lObj->Delete = GSleep_Delete;
    lObj->Sleep = GSleep_Sleep;
    return lObj;
}
//===============================================
void GSleep_Delete() {
    GSleepO* lObj = GSleep();
    if(lObj != 0) {
        free(lObj);
    }
    m_GSleepO = 0;
}
//===============================================
GSleepO* GSleep() {
    if(m_GSleepO == 0) {
        m_GSleepO = GSleep_New();
    }
    return m_GSleepO;
}
//===============================================
static void GSleep_Sleep(int delay) {
#if defined(__UNIX)
	sleep(delay);
#elif defined(__MINGW32__)
	Sleep(delay);
#endif
}
//===============================================
