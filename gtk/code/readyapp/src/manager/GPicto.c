//===============================================
#define _GMAP_EQUAL_CHAR_
//===============================================
#include "GPicto.h"
#include "GMap.h"
#include "GManager.h"
//===============================================
GDECLARE_MAP(GPicto, GVOID_PTR, GVOID_PTR)
GDEFINE_MAP(GPicto, GVOID_PTR, GVOID_PTR)
//===============================================
static GPictoO* m_GPictoO = 0;
//===============================================
static void GPicto_Load();
static char* GPicto_Get(char* key);
//===============================================
GPictoO* GPicto_New() {
    GPictoO* lObj =(GPictoO*)malloc(sizeof(GPictoO));
    lObj->Delete = GPicto_Delete;
    lObj->Load = GPicto_Load;
    lObj->Get = GPicto_Get;
    return lObj;
}
//===============================================
void GPicto_Delete() {

}
//===============================================
GPictoO* GPicto() {
    if(m_GPictoO == 0) {
        m_GPictoO = GPicto_New();
    }
    return m_GPictoO;
}
//===============================================
// method
//===============================================
static void GPicto_Load() {
    sGApp* lApp = GManager()->GetData()->app;
    GMapO(GPicto, GVOID_PTR, GVOID_PTR)* lPictoMap = lApp->picto_map;
    lPictoMap->SetData(lPictoMap, "addressbook", "\uf2b9", GMAP_EQUAL_CHAR);
}
//===============================================
static char* GPicto_Get(char* key) {
    sGApp* lApp = GManager()->GetData()->app;
    GMapO(GPicto, GVOID_PTR, GVOID_PTR)* lPictoMap = lApp->picto_map;
    char* lValue = lPictoMap->GetData(lPictoMap, key, GMAP_EQUAL_CHAR);
    return lValue;
}
//===============================================
