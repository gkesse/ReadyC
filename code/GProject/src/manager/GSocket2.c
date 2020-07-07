//===============================================
#include "GSocket2.h"
#include "GSocket2Win.h"
#include "GSocket2Unix.h"
//===============================================
#if defined(_GUSE_SOCKET_ON_)
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
#if defined(__unix)
    return GSocket2Unix();
#endif
#if defined(__WIN32)
    return GSocket2Win();
#endif
    return 0;
}
//===============================================
#endif
//===============================================
