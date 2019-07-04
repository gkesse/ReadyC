//===============================================
#include "GSocket2.h"
#include "GSocket2Windows.h"
#include "GSocket2Unix.h"
#include "GString2.h"
#include "GConfig.h"
//===============================================
GSocket2O* GSocket2_New() {
    GSocket2O* lObj = (GSocket2O*)malloc(sizeof(GSocket2O));
    lObj->m_child = 0;
    return lObj;
}
//===============================================
void GSocket2_Delete(GSocket2O* obj) {
    if(obj != 0) {
        if(obj->m_child != 0) {
            free(obj->m_child);
        }
        free(obj);
    }
}
//===============================================
GSocket2O* GSocket2() {
    if(GString2()->IsEqual(G_PLATEFORM_OS, "WINDOWS")) return GSocket2Windows();
    if(GString2()->IsEqual(G_PLATEFORM_OS, "UNIX")) return GSocket2Unix();
    return GSocket2Windows();
}
//===============================================
