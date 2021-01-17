//===============================================
#include "GConfig.h"
#include "GMap.h"
#include "GSQLite.h"
#include "GManager.h"
//===============================================
GDECLARE_MAP(GConfig, GVOID_PTR, GVOID_PTR)
GDEFINE_MAP(GConfig, GVOID_PTR, GVOID_PTR)
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
static int GConfig_CountData(char* key);
static void GConfig_InsertData(char* key, char* value);
static void GConfig_UpdateData(char* key, char* value);
//===============================================
GConfigO* GConfig_New() {
    GConfigO* lObj = (GConfigO*)malloc(sizeof(GConfigO));

    lObj->dataMap = GMap_New(GConfig, GVOID_PTR, GVOID_PTR)();

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
    GMapO(GConfig, GVOID_PTR, GVOID_PTR)* lDataMap = m_GConfigO->dataMap;
    lDataMap->Clear(lDataMap);
}
//===============================================
static void GConfig_Remove(char* key) {
    GMapO(GConfig, GVOID_PTR, GVOID_PTR)* lDataMap = m_GConfigO->dataMap;
    lDataMap->Remove(lDataMap, key, lDataMap->EqualChar);
}
//===============================================
static void GConfig_SetData(char* key, char* value) {
    GMapO(GConfig, GVOID_PTR, GVOID_PTR)* lDataMap = m_GConfigO->dataMap;
    lDataMap->SetData(lDataMap, key, GManager()->CopyStr(value), lDataMap->EqualChar);
}
//===============================================
static char* GConfig_GetData(char* key) {
    GMapO(GConfig, GVOID_PTR, GVOID_PTR)* lDataMap = m_GConfigO->dataMap;
    char* lValue = lDataMap->GetData(lDataMap, key, lDataMap->EqualChar);
    if(lValue == 0) lValue = "";
    return lValue;
}
//===============================================
static void GConfig_SaveData(char* key) {
    char* lValue = GConfig_GetData(key);
    if(GConfig_CountData(key) == 0) GConfig_InsertData(key, lValue);
    else GConfig_UpdateData(key, lValue);
}
//===============================================
static void GConfig_LoadData(char* key) {
    char lQuery[256];
    sprintf(lQuery, "\
    select config_value from config_data\n\
    where config_key = '%s'\n\
    ", key);
    char* lValue = GSQLite()->QueryValue(lQuery);
    GConfig_SetData(key, lValue);
    free(lValue);
}
//===============================================
static int GConfig_CountData(char* key) {
    char lQuery[256];
    sprintf(lQuery, "\
    select count(*) from config_data\n\
    where config_key = '%s'\n\
    ", key);
    char* lValue = GSQLite()->QueryValue(lQuery);
    int lCount = atoi(lValue);
    free(lValue);
    return lCount;
}
//===============================================
static void GConfig_InsertData(char* key, char* value) {
    char lQuery[256]; lQuery[0] = 0;
    sprintf(lQuery, "\
    insert into config_data (config_key, config_value)\n\
    values ('%s','%s')\n\
    ", key, value);
    GSQLite()->QueryWrite(lQuery);
}
//===============================================
static void GConfig_UpdateData(char* key, char* value) {
    char lQuery[256];
    sprintf(lQuery, "\
    update config_data\n\
    set config_value = '%s'\n\
    where config_key = '%s'\n\
    ", value, key);
    GSQLite()->QueryWrite(lQuery);
}
//===============================================
static int GConfig_Size() {
    GMapO(GConfig, GVOID_PTR, GVOID_PTR)* lDataMap = m_GConfigO->dataMap;
    return lDataMap->Size(lDataMap);
}
//===============================================
static void GConfig_Show() {
    GMapO(GConfig, GVOID_PTR, GVOID_PTR)* lDataMap = m_GConfigO->dataMap;
    lDataMap->Show(lDataMap, lDataMap->ShowChar);
}
//===============================================
