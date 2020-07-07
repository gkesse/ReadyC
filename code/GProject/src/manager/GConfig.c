//===============================================
#include "GConfig.h"
#include "GMap2.h"
#include "GString3.h"
#include "GDebug.h"
//===============================================
GDECLARE_MAP(GConfig, GCHAR_PTR, GVOID_PTR)
GDEFINE_MAP(GConfig, GCHAR_PTR, GVOID_PTR)
//===============================================
static GConfigO* m_GConfigO = 0;
//===============================================
static void GConfig_Clear();
static void GConfig_Remove(char* key);
static void GConfig_SetData(char* key, char* value);
static char* GConfig_GetData(char* key);
static int GConfig_Size();
static void GConfig_Show();
//===============================================
GConfigO* GConfig_New() {
    GConfigO* lObj = (GConfigO*)malloc(sizeof(GConfigO));

    lObj->m_dataMap = GMap_New(GConfig, GCHAR_PTR, GVOID_PTR)();

    lObj->Delete = GConfig_Delete;
    lObj->Clear = GConfig_Clear;
    lObj->Remove = GConfig_Remove;
    lObj->SetData = GConfig_SetData;
    lObj->GetData = GConfig_GetData;
    lObj->Size = GConfig_Size;
    lObj->Show = GConfig_Show;
    return lObj;
}
//===============================================
void GConfig_Delete() {
    GConfig_Clear();
    GConfigO* lObj = GConfig();
    if(lObj != 0) {
        free(lObj);
    }
    m_GConfigO = 0;
}
//===============================================
GConfigO* GConfig() {
    if(m_GConfigO == 0) {
        m_GConfigO = GConfig_New();
    }
    return m_GConfigO;
}
//===============================================
static void GConfig_Clear() {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    GMapO(GConfig, GCHAR_PTR, GVOID_PTR)* lDataMap = m_GConfigO->m_dataMap;
    lDataMap->Clear(lDataMap);
}
//===============================================
static void GConfig_Remove(char* key) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    GMapO(GConfig, GCHAR_PTR, GVOID_PTR)* lDataMap = m_GConfigO->m_dataMap;
    lDataMap->Remove(lDataMap, key, GMap_EqualChar);
}
//===============================================
static void GConfig_SetData(char* key, char* value) {
    GDebug()->Write(2, __FUNCTION__, "(", key, ", ", value, ")", _EOA_);
    GMapO(GConfig, GCHAR_PTR, GVOID_PTR)* lDataMap = m_GConfigO->m_dataMap;
    lDataMap->SetData(lDataMap, key, value, GMap_EqualChar);
}
//===============================================
static char* GConfig_GetData(char* key) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    GMapO(GConfig, GCHAR_PTR, GVOID_PTR)* lDataMap = m_GConfigO->m_dataMap;
    char* lValue = lDataMap->GetData(lDataMap, key, GMap_EqualChar);
    return lValue;
}
//===============================================
static int GConfig_Size() {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    GMapO(GConfig, GCHAR_PTR, GVOID_PTR)* lDataMap = m_GConfigO->m_dataMap;
    return lDataMap->Size(lDataMap);
}
//===============================================
static void GConfig_Show() {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    GMapO(GConfig, GCHAR_PTR, GVOID_PTR)* lDataMap = m_GConfigO->m_dataMap;
    lDataMap->Show(lDataMap, GMap_ShowChar);
}
//===============================================
