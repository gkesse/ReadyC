//===============================================
#include "GDir2.h"
#include "GString3.h"
#include "GShell.h"
#include "GDebug.h"
//===============================================
#if defined(__WIN32)
#define GDATA_PATH ".readydev\\readyc"
#endif
//===============================================
#if defined(__unix)
#define GDATA_PATH ".readydev/readyc"
#endif
//===============================================
static GDir2O* m_GDir2O = 0;
//===============================================
static void GDir2_Path(const char* pathIn, char* pathOut);
static void GDir2_PathC(const char* pathIn, char* pathOut);
static void GDir2_Name(const char* pathIn, char* pathOut);
static void GDir2_Create(const char* pathIn);
//===============================================
static void GDir2_DataPath(GDir2O* obj);
//===============================================
#if defined(__WIN32)
static void GDir2_DataPathWin(GDir2O* obj);
#endif
//===============================================
#if defined(__unix)
static void GDir2_DataPathUnix(GDir2O* obj);
#endif
//===============================================
GDir2O* GDir2_New() {
    GDir2O* lObj = (GDir2O*)malloc(sizeof(GDir2O));

    GDir2_DataPath(lObj);

    lObj->Delete = GDir2_Delete;
    lObj->Path = GDir2_Path;
    lObj->PathC = GDir2_PathC;
    lObj->Name = GDir2_Name;
    lObj->Create = GDir2_Create;
    return lObj;
}
//===============================================
void GDir2_Delete() {
    GDir2O* lObj = GDir2();
    if(lObj != 0) {
        free(lObj);
    }
    m_GDir2O = 0;
}
//===============================================
GDir2O* GDir2() {
    if(m_GDir2O == 0) {
        m_GDir2O = GDir2_New();
    }
    return m_GDir2O;
}
//===============================================
static void GDir2_Path(const char* pathIn, char* pathOut) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    sprintf(pathOut, "%s/%s", m_GDir2O->m_dataPath, pathIn);
#if defined(__WIN32)
    GString3()->Replace(pathOut, pathOut, "/", "\\");
#endif
}
//===============================================
static void GDir2_PathC(const char* pathIn, char* pathOut) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    char lPath[256];
    sprintf(pathOut, "%s/%s", m_GDir2O->m_dataPath, pathIn);
#if defined(__WIN32)
    GString3()->Replace(pathOut, pathOut, "/", "\\");
#endif
    GDir2_Name(pathOut, lPath);
    GDir2_Create(lPath);   
}
//===============================================
static void GDir2_Name(const char* pathIn, char* pathOut) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    char lCommand[256], lOutput[256];
    sprintf(lCommand, "dirname \"%s\"", pathIn);
    GShell()->Run(lCommand, lOutput, 255, 1);
    sprintf(pathOut, "%s", lOutput);
}
//===============================================
static void GDir2_Create(const char* pathIn) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    char lCommand[256], lOutput[256];
#if defined(__WIN32)
    sprintf(lCommand, "if not exist \"%s\" ( mkdir \"%s\" )", pathIn, pathIn);
#endif
#if defined(__unix)
    sprintf(lCommand, "if ! [ -d \"%s\" ] ; then mkdir -p \"%s\" ; fi", obj->m_dataPath, obj->m_dataPath);
#endif
    GShell()->Run(lCommand, 0, 0, 0);
}
//===============================================
static void GDir2_DataPath(GDir2O* obj) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
#if defined(__WIN32)
    GDir2_DataPathWin(obj);
#endif
#if defined(__unix)
    GDir2_DataPathUnix(obj);
#endif
}
//===============================================
#if defined(__WIN32)
static void GDir2_DataPathWin(GDir2O* obj) {
    char lCommand[256], lHomePath[256];
    FILE* lpFile;
    int lBytes;
    
    sprintf(lCommand, "%s", "echo %HOMEDRIVE%%HOMEPATH%");
    GShell()->Run(lCommand, lHomePath, 255, 1);
    
    sprintf(obj->m_dataPath, "%s\\%s", lHomePath, GDATA_PATH);
    sprintf(lCommand, "if not exist \"%s\" ( mkdir \"%s\" )", obj->m_dataPath, obj->m_dataPath);
    GShell()->Run(lCommand, 0, 0, 0);
}
#endif
//===============================================
#if defined(__unix)
static void GDir2_DataPathUnix(GDir2O* obj) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    char lCommand[256], lHomePath[256];
    FILE* lpFile;
    int lBytes;
    
    sprintf(lCommand, "%s", "echo $HOME");
    GShell()->Run(lCommand, lHomePath, 255, 1);
    
    sprintf(obj->m_dataPath, "%s/%s", lHomePath, GDATA_PATH);
    sprintf(lCommand, "if ! [ -d \"%s\" ] ; then mkdir -p \"%s\" ; fi", obj->m_dataPath, obj->m_dataPath);
    GShell()->Run(lCommand, 0, 0, 0);
}
#endif
//===============================================
