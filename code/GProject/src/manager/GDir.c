//===============================================
#include "GDir.h"
#include "GString.h"
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
static GDirO* m_GDirO = 0;
//===============================================
static void GDir_Path(const char* pathIn, char* pathOut);
static void GDir_PathC(const char* pathIn, char* pathOut);
static void GDir_Name(const char* pathIn, char* pathOut);
static void GDir_Create(const char* pathIn);
//===============================================
static void GDir_DataPath(GDirO* obj);
//===============================================
#if defined(__WIN32)
static void GDir_DataPathWin(GDirO* obj);
#endif
//===============================================
#if defined(__unix)
static void GDir_DataPathUnix(GDirO* obj);
#endif
//===============================================
GDirO* GDir_New() {
    GDirO* lObj = (GDirO*)malloc(sizeof(GDirO));

    GDir_DataPath(lObj);

    lObj->Delete = GDir_Delete;
    lObj->Path = GDir_Path;
    lObj->PathC = GDir_PathC;
    lObj->Name = GDir_Name;
    lObj->Create = GDir_Create;
    return lObj;
}
//===============================================
void GDir_Delete() {
    GDirO* lObj = GDir();
    if(lObj != 0) {
        free(lObj);
    }
    m_GDirO = 0;
}
//===============================================
GDirO* GDir() {
    if(m_GDirO == 0) {
        m_GDirO = GDir_New();
    }
    return m_GDirO;
}
//===============================================
static void GDir_Path(const char* pathIn, char* pathOut) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    sprintf(pathOut, "%s/%s", m_GDirO->m_dataPath, pathIn);
#if defined(__WIN32)
    GString()->Replace(pathOut, pathOut, "/", "\\");
#endif
}
//===============================================
static void GDir_PathC(const char* pathIn, char* pathOut) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    char lPath[256];
    sprintf(pathOut, "%s/%s", m_GDirO->m_dataPath, pathIn);
#if defined(__WIN32)
    GString()->Replace(pathOut, pathOut, "/", "\\");
#endif
    GDir_Name(pathOut, lPath);
    GDir_Create(lPath);   
}
//===============================================
static void GDir_Name(const char* pathIn, char* pathOut) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    char lCommand[256], lOutput[256];
    sprintf(lCommand, "dirname \"%s\"", pathIn);
    GShell()->Run(lCommand, lOutput, 255, 1);
    sprintf(pathOut, "%s", lOutput);
}
//===============================================
static void GDir_Create(const char* pathIn) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    char lCommand[256], lOutput[256];
#if defined(__WIN32)
    sprintf(lCommand, "if not exist \"%s\" ( mkdir \"%s\" )", pathIn, pathIn);
#endif
#if defined(__unix)
    sprintf(lCommand, "if ! [ -d \"%s\" ] ; then mkdir -p \"%s\" ; fi", pathIn, pathIn);
#endif
    GShell()->Run(lCommand, 0, 0, 0);
}
//===============================================
static void GDir_DataPath(GDirO* obj) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
#if defined(__WIN32)
    GDir_DataPathWin(obj);
#endif
#if defined(__unix)
    GDir_DataPathUnix(obj);
#endif
}
//===============================================
#if defined(__WIN32)
static void GDir_DataPathWin(GDirO* obj) {
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
static void GDir_DataPathUnix(GDirO* obj) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
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
