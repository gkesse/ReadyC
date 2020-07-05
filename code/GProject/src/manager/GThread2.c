//===============================================
#include "GThread2.h"
//#include "GThread2Windows.h"
#include "GThread2Unix.h"
#include "GString2.h"
#include "GConfig.h"
//===============================================
GThread2O* GThread2_New() {
    GThread2O* lObj = (GThread2O*)malloc(sizeof(GThread2O));
    lObj->m_child = 0;
    return lObj;
}
//===============================================
void GThread2_Delete(GThread2O* obj) {
    if(obj != 0) {
        if(obj->m_child != 0) {
            free(obj->m_child);
        }
        free(obj);
    }
}
//===============================================
GThread2O* GThread2() {
#if 0
    //if(GString2()->IsEqual(G_PLATEFORM_OS, "WINDOWS")) return GThread2Windows();
    if(GString2()->IsEqual(G_PLATEFORM_OS, "UNIX")) return GThread2Unix();
    return GThread2Unix();
#endif
    return 0;
}
//===============================================
