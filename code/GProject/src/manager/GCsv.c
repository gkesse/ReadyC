//===============================================
#include "GCsv.h"
#include "GList.h"
#include "GDebug.h"
//===============================================
GDECLARE_LIST(GCsv, GVOID_PTR)
GDEFINE_LIST(GCsv, GVOID_PTR)
//===============================================
static GCsvO* m_GCsvO = 0;
//===============================================
static void GCsv_Clear();
static void GCsv_Remove(int key);
static void GCsv_AddRow();
static void GCsv_AddData(char* value);
static void GCsv_SetData(int row, int col, char* data);
static char* GCsv_GetData(int row, int col);
static void GCsv_Size(int* width, int* height);
static void GCsv_Show();
//===============================================
GCsvO* GCsv_New() {
    GCsvO* lObj = (GCsvO*)malloc(sizeof(GCsvO));

    lObj->m_dataMap = GList_New(GCsv, GVOID_PTR)();
    lObj->m_listMap = 0;

    lObj->Delete = GCsv_Delete;
    lObj->Clear = GCsv_Clear;
    lObj->Remove = GCsv_Remove;
    lObj->AddRow = GCsv_AddRow;
    lObj->AddData = GCsv_AddData;
    lObj->SetData = GCsv_SetData;
    lObj->GetData = GCsv_GetData;
    lObj->Size = GCsv_Size;
    lObj->Show = GCsv_Show;
    return lObj;
}
//===============================================
void GCsv_Delete() {
    GCsv_Clear();
}
//===============================================
GCsvO* GCsv() {
    if(m_GCsvO == 0) {
        m_GCsvO = GCsv_New();
    }
    return m_GCsvO;
}
//===============================================
static void GCsv_Clear() {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    GListO(GCsv, GVOID_PTR)* lDataMap = m_GCsvO->m_dataMap;
    int lSize = lDataMap->Size(lDataMap);
    for(int i = 0; i< lSize; i++) {
        GListO(GCsv, GVOID_PTR)* lItemMap = lDataMap->GetData(lDataMap, i);
        lItemMap->Clear(lItemMap, 0);
    }
    lDataMap->Clear(lDataMap, 0);
}
//===============================================
static void GCsv_Remove(int row) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    GListO(GCsv, GVOID_PTR)* lDataMap = m_GCsvO->m_dataMap;
    GListO(GCsv, GVOID_PTR)* lItemMap = lDataMap->GetData(lDataMap, row);
    lItemMap->Clear(lItemMap, 0);
    lDataMap->RemoveIndex(lDataMap, row, 0);
}
//===============================================
static void GCsv_AddRow() {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    GListO(GCsv, GVOID_PTR)* lDataMap = m_GCsvO->m_dataMap;
    m_GCsvO->m_listMap = GList_New(GCsv, GVOID_PTR)();
    lDataMap->AddData(lDataMap, m_GCsvO->m_listMap);
}
//===============================================
static void GCsv_AddData(char* value) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    GListO(GCsv, GVOID_PTR)* lItemMap = m_GCsvO->m_listMap;
    lItemMap->AddData(lItemMap, value);
}
//===============================================
static void GCsv_SetData(int row, int col, char* data) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    GListO(GCsv, GVOID_PTR)* lDataMap = m_GCsvO->m_dataMap;
    GListO(GCsv, GVOID_PTR)* lItemMap = lDataMap->GetData(lDataMap, row);
    lItemMap->SetData(lItemMap, col, data, 0);
}
//===============================================
static char* GCsv_GetData(int row, int col) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    int lWidth, lHeight;
    GCsv_Size(&lWidth, &lHeight);
    if(lWidth == 0 || lHeight == 0) return 0;
    GListO(GCsv, GVOID_PTR)* lDataMap = m_GCsvO->m_dataMap;
    GListO(GCsv, GVOID_PTR)* lItemMap = lDataMap->GetData(lDataMap, row);
    char* lData = lItemMap->GetData(lItemMap, col);
    return lData;
}
//===============================================
static void GCsv_Size(int* width, int* height) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    GListO(GCsv, GVOID_PTR)* lDataMap = m_GCsvO->m_dataMap;
    *width = lDataMap->Size(lDataMap);
    *height = 0;
    if(*width != 0) {
        GListO(GCsv, GVOID_PTR)* lItemMap = lDataMap->GetData(lDataMap, 0);
        *height = lItemMap->Size(lItemMap);
    }
}
//===============================================
static void GCsv_Show() {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    GListO(GCsv, GVOID_PTR)* lDataMap = m_GCsvO->m_dataMap;
    int lSize = lDataMap->Size(lDataMap);
    for(int i = 0; i < lSize; i++) {
        GListO(GCsv, GVOID_PTR)* lItemMap = lDataMap->GetData(lDataMap, i);
        lItemMap->Show(lItemMap, GList_ShowChar);
        printf("\n");
    }
}
//===============================================
