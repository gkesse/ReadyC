//===============================================
#include "GManagerWin.h"
//===============================================
static GManagerO* m_GManagerWinO = 0;
//===============================================
static void GManagerWin_Init(GManagerO* obj);
//===============================================
GManagerO* GManagerWin_New() {
    GManagerO* lParent = GManager_New();
    GManagerWinO* lChild = (GManagerWinO*)malloc(sizeof(GManagerWinO));
    
    lChild->parent = lParent;
    
    GManagerWin_Init(lParent);
    
    lParent->child = lChild;
    lParent->Delete = GManagerWin_Delete;
    return lParent;
}
//===============================================
void GManagerWin_Delete() {
    GManager_Delete();
    m_GManagerWinO = 0;
}
//===============================================
GManagerO* GManagerWin() {
    if(m_GManagerWinO == 0) {
        m_GManagerWinO = GManagerWin_New();
    }
    return m_GManagerWinO;
}
//===============================================
// obj
//===============================================
static void GManagerWin_Init(GManagerO* obj) {
    
}
//===============================================
