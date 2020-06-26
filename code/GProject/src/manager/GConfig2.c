//===============================================
#include "GConfig2.h"
#include "GMap2.h"
#include "GDebug.h"
//===============================================
GDECLARE_MAP(GConfig2, GCHAR_PTR, GVOID_PTR)
GDEFINE_MAP(GConfig2, GCHAR_PTR, GVOID_PTR)
//===============================================
static GConfig2O* m_GConfig2O = 0;
//===============================================
static void GConfig2_Clear();
static void GConfig2_Remove(char* key);
static void GConfig2_SetData(char* key, char* value);
static char* GConfig2_GetData(char* key);
static int GConfig2_Size();
static void GConfig2_Show();
//===============================================
GConfig2O* GConfig2_New() {
    GConfig2O* lObj = (GConfig2O*)malloc(sizeof(GConfig2O));

    lObj->m_dataMap = GMap_New(GConfig2, GCHAR_PTR, GVOID_PTR)();

    lObj->Delete = GConfig2_Delete;
    lObj->Clear = GConfig2_Clear;
    lObj->Remove = GConfig2_Remove;
    lObj->SetData = GConfig2_SetData;
    lObj->GetData = GConfig2_GetData;
    lObj->Size = GConfig2_Size;
    lObj->Show = GConfig2_Show;
    return lObj;
}
//===============================================
void GConfig2_Delete() {
    GConfig2_Clear();
}
//===============================================
GConfig2O* GConfig2() {
    if(m_GConfig2O == 0) {
        m_GConfig2O = GConfig2_New();
    }
    return m_GConfig2O;
}
//===============================================
static void GConfig2_Clear() {
    GDebug()->Write(__FUNCTION__, "()", _EOA_);
    GMapO(GConfig2, GCHAR_PTR, GVOID_PTR)* lDataMap = m_GConfig2O->m_dataMap;
    lDataMap->Clear(lDataMap);
}
//===============================================
static void GConfig2_Remove(char* key) {
    GDebug()->Write(__FUNCTION__, "()", _EOA_);
    GMapO(GConfig2, GCHAR_PTR, GVOID_PTR)* lDataMap = m_GConfig2O->m_dataMap;
    lDataMap->Remove(lDataMap, key, GMap_EqualChar);
}
//===============================================
static void GConfig2_SetData(char* key, char* value) {
    GDebug()->Write(__FUNCTION__, "()", _EOA_);
    GMapO(GConfig2, GCHAR_PTR, GVOID_PTR)* lDataMap = m_GConfig2O->m_dataMap;
    lDataMap->SetData(lDataMap, key, value, GMap_EqualChar);
}
//===============================================
static char* GConfig2_GetData(char* key) {
    GDebug()->Write(__FUNCTION__, "()", _EOA_);
    GMapO(GConfig2, GCHAR_PTR, GVOID_PTR)* lDataMap = m_GConfig2O->m_dataMap;
    char* lValue = lDataMap->GetData(lDataMap, key, GMap_EqualChar);
    return lValue;
}
//===============================================
static int GConfig2_Size() {
    GDebug()->Write(__FUNCTION__, "()", _EOA_);
    GMapO(GConfig2, GCHAR_PTR, GVOID_PTR)* lDataMap = m_GConfig2O->m_dataMap;
    return lDataMap->Size(lDataMap);
}
//===============================================
static void GConfig2_Show() {
    GDebug()->Write(__FUNCTION__, "()", _EOA_);
    GMapO(GConfig2, GCHAR_PTR, GVOID_PTR)* lDataMap = m_GConfig2O->m_dataMap;
    lDataMap->Show(lDataMap, GMap_ShowChar);
}
//===============================================
