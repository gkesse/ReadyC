//===============================================
#include "GDir2.h"
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
static void GDir2_Path(char* pathIn, char* pathOut);
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
static void GDir2_Path(char* pathIn, char* pathOut) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    sprintf(pathOut, "%s/%s", m_GDir2O->m_dataPath, pathIn);
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
    lpFile = popen(lCommand, "r");
    lBytes = fread(lHomePath, 1, 255, lpFile);
    lHomePath[lBytes - 1] = 0;
    pclose(lpFile);
    
    sprintf(obj->m_dataPath, "%s\\%s", lHomePath, GDATA_PATH);
    sprintf(lCommand, "if not exist \"%s\" ( mkdir \"%s\" )", obj->m_dataPath, obj->m_dataPath);
    lpFile = popen(lCommand, "r");
    pclose(lpFile);
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
    lpFile = popen(lCommand, "r");
    lBytes = fread(lHomePath, 1, 255, lpFile);
    lHomePath[lBytes - 1] = 0;
    pclose(lpFile);
    
    sprintf(obj->m_dataPath, "%s/%s", lHomePath, GDATA_PATH);
    sprintf(lCommand, "if ! [ -d \"%s\" ] ; then mkdir -p \"%s\" ; fi", obj->m_dataPath, obj->m_dataPath);
    lpFile = popen(lCommand, "r");
    pclose(lpFile);
}
#endif
//===============================================
