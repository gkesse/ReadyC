//===============================================
#include "GManagerUnix.h"
//===============================================
static GManagerO* m_GManagerUnixO = 0;
//===============================================
static void GManagerUnix_Init(GManagerO* obj);
//===============================================
GManagerO* GManagerUnix_New() {
    GManagerO* lParent = GManager_New();
    GManagerUnixO* lChild = (GManagerUnixO*)malloc(sizeof(GManagerUnixO));
    
    lChild->parent = lParent;
    
    GManagerUnix_Init(lParent);
    
    lParent->child = lChild;
    lParent->Delete = GManagerUnix_Delete;
    return lParent;
}
//===============================================
void GManagerUnix_Delete() {
    GManager_Delete();
    m_GManagerUnixO = 0;
}
//===============================================
GManagerO* GManagerUnix() {
    if(m_GManagerUnixO == 0) {
        m_GManagerUnixO = GManagerUnix_New();
    }
    return m_GManagerUnixO;
}
//===============================================
// obj
//===============================================
static void GManagerUnix_Init(GManagerO* obj) {
    // sqlite
    strcpy(obj->m_mgr->sqlite->db_path, "C:\\Users\\Admin\\Downloads\\Programs\\ReadyBin\\win\\.CONFIG_O.dat");
    // json
    strcpy(obj->m_mgr->json->file, "C:\\Users\\Admin\\.readydev\\readyc\\data\\json\\menu.json");
}
//===============================================
