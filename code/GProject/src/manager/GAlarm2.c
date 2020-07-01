//===============================================
#include "GAlarm2.h"
#include "GAlarm2Win.h"
#include "GString2.h"
//===============================================
GAlarm2O* GAlarm2_New() {
    GAlarm2O* lObj = (GAlarm2O*)malloc(sizeof(GAlarm2O));
    lObj->m_child = 0;
    return lObj;
}
//===============================================
void GAlarm2_Delete(GAlarm2O* obj) {
    if(obj != 0) {
        if(obj->m_child != 0) {
            free(obj->m_child);
        }
        free(obj);
    }
}
//===============================================
GAlarm2O* GAlarm2() {
    if(GString2()->IsEqual(G_PLATEFORM_OS, "WINDOWS")) return GAlarm2Win();
    return GAlarm2Win();
}
//===============================================

