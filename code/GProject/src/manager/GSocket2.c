//===============================================
#include "GSocket2.h"
#include "GSocket2Win.h"
#include "GSocket2Unix.h"
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
#if defined(__unix2)
    return GSocket2Unix();
#elif defined(__WIN32)
    return GSocket2Win();
#endif
    return 0;
}
//===============================================
