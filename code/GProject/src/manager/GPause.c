//===============================================
#include "GPause.h"
//===============================================
static GPauseO* m_GPauseO = 0;
//===============================================
static void GPause_Pause();
//===============================================
GPauseO* GPause_New() {
    GPauseO* lObj = (GPauseO*)malloc(sizeof(GPauseO));
    lObj->Delete = GPause_Delete;
    lObj->Pause = GPause_Pause;
    return lObj;
}
//===============================================
void GPause_Delete() {
    GPauseO* lObj = GPause();
    if(lObj != 0) {
        free(lObj);
    }
    m_GPauseO = 0;
}
//===============================================
GPauseO* GPause() {
    if(m_GPauseO == 0) {
        m_GPauseO = GPause_New();
    }
    return m_GPauseO;
}
//===============================================
static void GPause_Pause() {
#if defined(__unix)
	pause();
#endif
}
//===============================================
