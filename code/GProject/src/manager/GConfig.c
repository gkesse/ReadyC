//===============================================
#define _GMAP_SHOW_CHAR_
//===============================================
#include "GConfig.h"
#include "GMap.h"
#include "GSQLite.h"
#include "GManager.h"
//===============================================
#define B_VALUE (256)
#define B_QUERY (256)
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
static void GConfig_SaveData(char* key);
static void GConfig_LoadData(char* key);
static int GConfig_Size();
static void GConfig_Show();
//===============================================
static int GConfig_CheckData(char* key);
static void GConfig_InsertData(char* key, char* value);
static void GConfig_UpdateData(char* key, char* value);
//===============================================
GConfigO* GConfig_New() {
    GConfigO* lObj = (GConfigO*)malloc(sizeof(GConfigO));

    lObj->m_dataMap = GMap_New(GConfig, GCHAR_PTR, GVOID_PTR)();

    lObj->Delete = GConfig_Delete;
    lObj->Clear = GConfig_Clear;
    lObj->Remove = GConfig_Remove;
    lObj->SetData = GConfig_SetData;
    lObj->GetData = GConfig_GetData;
    lObj->SaveData = GConfig_SaveData;
    lObj->LoadData = GConfig_LoadData;
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
    GMapO(GConfig, GCHAR_PTR, GVOID_PTR)* lDataMap = m_GConfigO->m_dataMap;
    lDataMap->Clear(lDataMap);
}
//===============================================
static void GConfig_Remove(char* key) {
    GMapO(GConfig, GCHAR_PTR, GVOID_PTR)* lDataMap = m_GConfigO->m_dataMap;
    lDataMap->Remove(lDataMap, key, GMap_EqualChar);
}
//===============================================
static void GConfig_SetData(char* key, char* value) {
    char* lValue = GManager()->Copy(value);
    GMapO(GConfig, GCHAR_PTR, GVOID_PTR)* lDataMap = m_GConfigO->m_dataMap;
    lDataMap->SetData(lDataMap, key, lValue, GMap_EqualChar);
}
//===============================================
static char* GConfig_GetData(char* key) {
    GMapO(GConfig, GCHAR_PTR, GVOID_PTR)* lDataMap = m_GConfigO->m_dataMap;
    char* lValue = lDataMap->GetData(lDataMap, key, GMap_EqualChar);
    if(lValue == 0) lValue = "";
    return lValue;
}
//===============================================
static void GConfig_SaveData(char* key) {
    char* lValue = GConfig_GetData(key);
    if(GConfig_CheckData(key) == 0) GConfig_InsertData(key, lValue);
    else GConfig_UpdateData(key, lValue);
}
//===============================================
static void GConfig_LoadData(char* key) {
    char lValue[B_VALUE+1];
    char lQuery[B_QUERY+1];
    sprintf(lQuery, "\
    select CONFIG_VALUE from CONFIG_C \
    where CONFIG_KEY = '%s' \
    ", key);
    GSQLite()->QueryValue(lQuery, lValue);
    GConfig_SetData(key, lValue);
}
//===============================================
static int GConfig_CheckData(char* key) {
    char lValue[B_VALUE+1];
    char lQuery[B_QUERY+1];
    sprintf(lQuery, "\
    select count(*) from CONFIG_C \
    where CONFIG_KEY = '%s' \
    ", key);
    GSQLite()->QueryValue(lQuery, lValue);
    int lCount = atoi(lValue);
    return lCount;
}
//===============================================
static void GConfig_InsertData(char* key, char* value) {
    char lQuery[B_QUERY+1];
    sprintf(lQuery, "\
    insert into CONFIG_C (CONFIG_KEY, CONFIG_VALUE)\
    values ('%s', '%s') \
    ", key, value);
    GSQLite()->QueryWrite(lQuery);
}
//===============================================
static void GConfig_UpdateData(char* key, char* value) {
    char lQuery[B_QUERY+1];
    sprintf(lQuery, "\
    update CONFIG_C \
    set CONFIG_VALUE = '%s' \
    where CONFIG_KEY = '%s' \
    ", value, key);
    GSQLite()->QueryWrite(lQuery);
}
//===============================================
static int GConfig_Size() {
    GMapO(GConfig, GCHAR_PTR, GVOID_PTR)* lDataMap = m_GConfigO->m_dataMap;
    return lDataMap->Size(lDataMap);
}
//===============================================
static void GConfig_Show() {
    GMapO(GConfig, GCHAR_PTR, GVOID_PTR)* lDataMap = m_GConfigO->m_dataMap;
    lDataMap->Show(lDataMap, GMap_ShowChar);
}
//===============================================
