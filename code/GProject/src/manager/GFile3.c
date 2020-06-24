//===============================================
#include "GFile3.h"
#include "GDir2.h"
#include "GMap2.h"
#include "GList2.h"
#include "GString3.h"
#include "GConfig.h"
#include "GCsv.h"
#include "GDebug.h"
//===============================================
GDECLARE_MAP(GFile3, GCHAR_PTR, GVOID_PTR)
GDEFINE_MAP(GFile3, GCHAR_PTR, GVOID_PTR)
//===============================================
static GFile3O* m_GFile3O = 0;
//===============================================
static void GFile3_Test(int argc, char** argv);
static void GFile3_Exist(char* filename);
static void GFile3_Open(char* fileId, char* filename, char* mode);
static char* GFile3_GetData(char* fileId);
static void GFile3_GetDataMap(char* fileId);
static void GFile3_GetDataCsv(char* fileId);
static int GFile3_Size(char* fileId);
static void GFile3_Show(char* fileId);
static void GFile3_Close(char* fileId);
//===============================================
GFile3O* GFile3_New() {
    GFile3O* lObj = (GFile3O*)malloc(sizeof(GFile3O));

    lObj->m_pFileMap = GMap_New(GFile3, GCHAR_PTR, GVOID_PTR)();
    
    lObj->Delete = GFile3_Delete;
    lObj->Test = GFile3_Test;
    lObj->Exist = GFile3_Exist;
    lObj->Open = GFile3_Open;
    lObj->GetData = GFile3_GetData;
    lObj->GetDataMap = GFile3_GetDataMap;
    lObj->GetDataCsv = GFile3_GetDataCsv;
    lObj->Size = GFile3_Size;
    lObj->Show = GFile3_Show;
    lObj->Close = GFile3_Close;
    return lObj;
}
//===============================================
void GFile3_Delete() {

}
//===============================================
GFile3O* GFile3() {
    if(m_GFile3O == 0) {
        m_GFile3O = GFile3_New();
    }
    return m_GFile3O;
} 
//===============================================
static void GFile3_Test(int argc, char** argv) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    char* lFile = "lFile";

    int lId = 3;
    
    if(lId == 1) {
        char lFilePath[256];
        GDir2()->DataPath("data/file/file.txt", lFilePath);
        GFile3()->Open(lFile, lFilePath, "r");
        GFile3()->Show(lFile);
        GFile3()->Close(lFile);
    }
    else if(lId == 2) {
        char lFilePath[256];
        GDir2()->DataPath("data/file/file2.txt", lFilePath);
        GFile3()->Open(lFile, lFilePath, "r");
        GFile3()->GetDataMap(lFile);
        GConfig()->Remove("MY_KEY_03");
        GConfig()->SetData("MY_KEY_04", "MY_UPDATE");
        GConfig()->Show();
        GFile3()->Close(lFile);
    }
    else if(lId == 3) {
        int lWidth, lHeight; char* lData;
        char lFilePath[256];
        GDir2()->DataPath("data/file/file3.txt", lFilePath);
        GFile3()->Open(lFile, lFilePath, "r");
        GFile3()->GetDataCsv(lFile);
        char* lUpdate = "MY_UPDATE";
        GCsv()->SetData(1, 1, lUpdate);
        //GCsv()->Clear();    
        GCsv()->Remove(3);    
        GCsv()->Show();    
        GCsv()->Size(&lWidth, &lHeight);
        lData = GCsv()->GetData(1, 1);
        printf("\n");
        printf("lWidth: %d | lHeight: %d\n", lWidth, lHeight);
        printf("lData : %s\n", lData);
        GFile3()->Close(lFile);
    }
}
//===============================================
static void GFile3_Exist(char* filename) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    FILE* lFile = fopen(filename, "r");
    if(lFile != 0) {printf("erreur: fichier inexistant : %s\n", filename); exit(0);}
    fclose(lFile);
}
//===============================================
static void GFile3_Open(char* fileId, char* filename, char* mode) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    GMapO(GFile3, GCHAR_PTR, GVOID_PTR)* lpFileMap = m_GFile3O->m_pFileMap;
    FILE* lpFile = fopen(filename, mode);
    if(lpFile == 0) {printf("erreur: echec ouverture fichier : %s\n", filename); exit(0);}
    lpFileMap->SetData(lpFileMap, fileId, lpFile, GMap_EqualChar);
}
//===============================================
static char* GFile3_GetData(char* fileId) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    GMapO(GFile3, GCHAR_PTR, GVOID_PTR)* lpFileMap = m_GFile3O->m_pFileMap;
    FILE* lpFile = lpFileMap->GetData(lpFileMap, fileId, GMap_EqualChar);
    int lSize = GFile3_Size(fileId);
    char* lData = (char*)malloc(sizeof(char)*(lSize + 1));
    int lBytes = fread(lData, sizeof(char), lSize, lpFile);
    lData[lBytes] = 0;
    return lData;
}
//===============================================
static void GFile3_GetDataMap(char* fileId) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    GMapO(GFile3, GCHAR_PTR, GVOID_PTR)* lpFileMap = m_GFile3O->m_pFileMap;
    FILE* lpFile = lpFileMap->GetData(lpFileMap, fileId, GMap_EqualChar);
    char lLine[256];
    
    while(fgets(lLine, sizeof(lLine), lpFile) != NULL) {
        GString3()->Trim(lLine, lLine);
        if(lLine[0] == 0) {continue;}
        char lFirst = lLine[0];
        if(lFirst == '#') {continue;}
        char lKey[256], lValue[256];
        GString3()->SplitGet(lLine, lKey, "=", 0);
        GString3()->SplitGet(lLine, lValue, "=", 1);
        GString3()->Trim(lKey, lKey);
        GString3()->Trim(lValue, lValue);
        GConfig()->SetData(lKey, lValue);
    }
}
//===============================================
static void GFile3_GetDataCsv(char* fileId) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    GMapO(GFile3, GCHAR_PTR, GVOID_PTR)* lpFileMap = m_GFile3O->m_pFileMap;
    FILE* lpFile = lpFileMap->GetData(lpFileMap, fileId, GMap_EqualChar);
    char lLine[256];
    
    while(fgets(lLine, sizeof(lLine), lpFile) != NULL) {
        GString3()->Trim(lLine, lLine);
        if(lLine[0] == 0) {continue;}
        char lFirst = lLine[0];
        if(lFirst == '#') {continue;}
        int lCount = GString3()->SplitCount(lLine, ";");
        
        GCsv()->AddRow();    
        
        char lCol[256];
        for(int i = 0; i < lCount; i++) {
            GString3()->SplitGet(lLine, lCol, ";", i);
            GString3()->Trim(lCol, lCol);
            GCsv()->AddData(lCol);    
        }
    }
}
//===============================================
static int GFile3_Size(char* fileId) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    GMapO(GFile3, GCHAR_PTR, GVOID_PTR)* lpFileMap = m_GFile3O->m_pFileMap;
    FILE* lpFile = lpFileMap->GetData(lpFileMap, fileId, GMap_EqualChar);
    fseek(lpFile, 0, SEEK_END);
    int lSize = (int)ftell(lpFile);
    rewind(lpFile);
    return lSize;
}
//===============================================
static void GFile3_Show(char* fileId) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    char* lData = GFile3_GetData(fileId);
    printf("%s\n", lData);
    free(lData);
}
//===============================================
static void GFile3_Close(char* fileId) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    GMapO(GFile3, GCHAR_PTR, GVOID_PTR)* lpFileMap = m_GFile3O->m_pFileMap;
    FILE* lpFile = lpFileMap->GetData(lpFileMap, fileId, GMap_EqualChar);
    fclose(lpFile);
}
//===============================================
