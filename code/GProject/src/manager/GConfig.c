//===============================================
#include "GConfig.h"
#include "GConfigNormal.h"
#include "GConfigTemplate.h"
#include "GString.h"
//===============================================
GConfigO* GConfig_New() {
    GConfigO* lObj = (GConfigO*)malloc(sizeof(GConfigO));
    lObj->m_child = 0;
    return lObj;
}
//===============================================
void GConfig_Delete() {
    GConfigO* lObj = GConfig();
    if(lObj != 0) {
        if(lObj->m_child != 0) {
            free(lObj->m_child);
        }
        free(lObj);
    }
}
//===============================================
GConfigO* GConfig() {
    char* lKey = "TEMPLATE";
    if(GString()->IsEqual(lKey, "NORMAL")) return GConfigNormal();
    if(GString()->IsEqual(lKey, "TEMPLATE")) return GConfigTemplate();
    return GConfigNormal();
}
//===============================================

