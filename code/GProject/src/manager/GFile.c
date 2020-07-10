//===============================================
#include "GFile.h"
#include "GDir.h"
#include "GMap.h"
#include "GList.h"
#include "GString.h"
#include "GConfig.h"
#include "GCsv.h"
#include "GDebug.h"
//===============================================
GDECLARE_MAP(GFile, GCHAR_PTR, GVOID_PTR)
GDEFINE_MAP(GFile, GCHAR_PTR, GVOID_PTR)
//===============================================
static GFileO* m_GFileO = 0;
//===============================================
static void GFile_Test(int argc, char** argv);
static void GFile_Exist(char* filename);
static void GFile_Open(char* fileId, char* filename, char* mode);
static char* GFile_GetData(char* fileId);
static void GFile_GetDataMap(char* fileId);
static void GFile_GetDataCsv(char* fileId);
static int GFile_Size(char* fileId);
static void GFile_Show(char* fileId);
static void GFile_Close(char* fileId);
//===============================================
GFileO* GFile_New() {
    GFileO* lObj = (GFileO*)malloc(sizeof(GFileO));

    lObj->m_pFileMap = GMap_New(GFile, GCHAR_PTR, GVOID_PTR)();
    
    lObj->Delete = GFile_Delete;
    lObj->Test = GFile_Test;
    lObj->Exist = GFile_Exist;
    lObj->Open = GFile_Open;
    lObj->GetData = GFile_GetData;
    lObj->GetDataMap = GFile_GetDataMap;
    lObj->GetDataCsv = GFile_GetDataCsv;
    lObj->Size = GFile_Size;
    lObj->Show = GFile_Show;
    lObj->Close = GFile_Close;
    return lObj;
}
//===============================================
void GFile_Delete() {

}
//===============================================
GFileO* GFile() {
    if(m_GFileO == 0) {
        m_GFileO = GFile_New();
    }
    return m_GFileO;
} 
//===============================================
static void GFile_Test(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    char* lFile = "lFile";

    int lId = 3;
    
    if(lId == 1) {
        char lFilePath[256];
        GDir()->Path("data/file/file.txt", lFilePath);
        GFile()->Open(lFile, lFilePath, "r");
        GFile()->Show(lFile);
        GFile()->Close(lFile);
    }
    else if(lId == 2) {
        char lFilePath[256];
        GDir()->Path("data/file/file2.txt", lFilePath);
        GFile()->Open(lFile, lFilePath, "r");
        GFile()->GetDataMap(lFile);
        GConfig()->Remove("MY_KEY_03");
        GConfig()->SetData("MY_KEY_04", "MY_UPDATE");
        GConfig()->Show();
        GFile()->Close(lFile);
    }
    else if(lId == 3) {
        int lWidth, lHeight; char* lData;
        char lFilePath[256];
        GDir()->Path("data/file/file3.txt", lFilePath);
        GFile()->Open(lFile, lFilePath, "r");
        GFile()->GetDataCsv(lFile);
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
        GFile()->Close(lFile);
    }
}
//===============================================
static void GFile_Exist(char* filename) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    FILE* lFile = fopen(filename, "r");
    if(lFile != 0) {printf("erreur: fichier inexistant : %s\n", filename); exit(0);}
    fclose(lFile);
}
//===============================================
static void GFile_Open(char* fileId, char* filename, char* mode) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    GMapO(GFile, GCHAR_PTR, GVOID_PTR)* lpFileMap = m_GFileO->m_pFileMap;
    FILE* lpFile = fopen(filename, mode);
    if(lpFile == 0) {printf("erreur: echec ouverture fichier : %s\n", filename); exit(0);}
    lpFileMap->SetData(lpFileMap, fileId, lpFile, GMap_EqualChar);
}
//===============================================
static char* GFile_GetData(char* fileId) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    GMapO(GFile, GCHAR_PTR, GVOID_PTR)* lpFileMap = m_GFileO->m_pFileMap;
    FILE* lpFile = lpFileMap->GetData(lpFileMap, fileId, GMap_EqualChar);
    int lSize = GFile_Size(fileId);
    char* lData = (char*)malloc(sizeof(char)*(lSize + 1));
    int lBytes = fread(lData, sizeof(char), lSize, lpFile);
    lData[lBytes] = 0;
    return lData;
}
//===============================================
static void GFile_GetDataMap(char* fileId) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    GMapO(GFile, GCHAR_PTR, GVOID_PTR)* lpFileMap = m_GFileO->m_pFileMap;
    FILE* lpFile = lpFileMap->GetData(lpFileMap, fileId, GMap_EqualChar);
    char lLine[256];
    
    while(fgets(lLine, sizeof(lLine), lpFile) != NULL) {
        GString()->Trim(lLine, lLine);
        if(lLine[0] == 0) {continue;}
        char lFirst = lLine[0];
        if(lFirst == '#') {continue;}
        char lKey[256], lValue[256];
        GString()->SplitGet(lLine, lKey, "=", 0);
        GString()->SplitGet(lLine, lValue, "=", 1);
        GString()->Trim(lKey, lKey);
        GString()->Trim(lValue, lValue);
        GConfig()->SetData(lKey, lValue);
    }
}
//===============================================
static void GFile_GetDataCsv(char* fileId) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    GMapO(GFile, GCHAR_PTR, GVOID_PTR)* lpFileMap = m_GFileO->m_pFileMap;
    FILE* lpFile = lpFileMap->GetData(lpFileMap, fileId, GMap_EqualChar);
    char lLine[256];
    
    while(fgets(lLine, sizeof(lLine), lpFile) != NULL) {
        GString()->Trim(lLine, lLine);
        if(lLine[0] == 0) {continue;}
        char lFirst = lLine[0];
        if(lFirst == '#') {continue;}
        int lCount = GString()->SplitCount(lLine, ";");
        
        GCsv()->AddRow();    
        
        char lCol[256];
        for(int i = 0; i < lCount; i++) {
            GString()->SplitGet(lLine, lCol, ";", i);
            GString()->Trim(lCol, lCol);
            GCsv()->AddData(lCol);    
        }
    }
}
//===============================================
static int GFile_Size(char* fileId) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    GMapO(GFile, GCHAR_PTR, GVOID_PTR)* lpFileMap = m_GFileO->m_pFileMap;
    FILE* lpFile = lpFileMap->GetData(lpFileMap, fileId, GMap_EqualChar);
    fseek(lpFile, 0, SEEK_END);
    int lSize = (int)ftell(lpFile);
    rewind(lpFile);
    return lSize;
}
//===============================================
static void GFile_Show(char* fileId) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    char* lData = GFile_GetData(fileId);
    printf("%s\n", lData);
    free(lData);
}
//===============================================
static void GFile_Close(char* fileId) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    GMapO(GFile, GCHAR_PTR, GVOID_PTR)* lpFileMap = m_GFileO->m_pFileMap;
    FILE* lpFile = lpFileMap->GetData(lpFileMap, fileId, GMap_EqualChar);
    fclose(lpFile);
}
//===============================================
