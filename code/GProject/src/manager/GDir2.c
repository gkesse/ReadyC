//===============================================
#include "GDir2.h"
#include "GShell.h"
#include "GDebug.h"
//===============================================
static GDir2O* m_GDir2O = 0;
//===============================================
static void GDir2_Test(int argc, char** argv);
static void GDir2_DataPath(char* path, char* output);
//===============================================
static void GDir2_HomePath(GDir2O* obj);
//===============================================
#if defined(__unix)
static void GDir2_HomePathUnix(GDir2O* obj);
static void GDir2_TestUnix(int argc, char** argv);
#elif defined(__WIN32)
static void GDir2_HomePathWin(GDir2O* obj);
static void GDir2_TestWin(int argc, char** argv);
#endif
//===============================================
GDir2O* GDir2_New() {
    GDir2O* lObj = (GDir2O*)malloc(sizeof(GDir2O));

    GDir2_HomePath(lObj);

    lObj->Delete = GDir2_Delete;
    lObj->Test = GDir2_Test;
    lObj->DataPath = GDir2_DataPath;
    return lObj;
}
//===============================================
void GDir2_Delete() {

}
//===============================================
GDir2O* GDir2() {
    if(m_GDir2O == 0) {
        m_GDir2O = GDir2_New();
    }
    return m_GDir2O;
}
//===============================================
static void GDir2_Test(int argc, char** argv) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
#if defined(__unix)
    GDir2_TestUnix(argc, argv);
#elif defined(__WIN32)
    GDir2_TestWin(argc, argv);
#endif
}
//===============================================
#if defined(__unix)
static void GDir2_TestUnix(int argc, char** argv) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    char lDebugFile[256];
    GDir2()->DataPath("data/debug/debug.txt", lDebugFile);
    printf("%s: %s\n", "m_homePath", GDir2()->m_homePath);
    printf("%s: %s\n", "m_dataPath", GDir2()->m_dataPath);
    printf("%s: %s\n", "lDebugFile", lDebugFile);
}
#endif
//===============================================
#if defined(__WIN32)
static void GDir2_TestWin(int argc, char** argv) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
}
#endif
//===============================================
static void GDir2_DataPath(char* path, char* output) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    sprintf(output, "%s%s", m_GDir2O->m_dataPath, path);
}
//===============================================
static void GDir2_HomePath(GDir2O* obj) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
#if defined(__unix)
    GDir2_HomePathUnix(obj);
#elif defined(__WIN32)
    GDir2_HomePathWin(obj);
#endif
}
//===============================================
#if defined(__unix)
static void GDir2_HomePathUnix(GDir2O* obj) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
	char lCommand[256];
	sprintf(lCommand, "%s", "echo $HOME");
	GShell()->Run(lCommand, obj->m_homePath, 255, 1);
    sprintf(obj->m_dataPath, "%s%s", obj->m_homePath, GDIR_DATA_PATH);
}
#endif
//===============================================
#if defined(__WIN32)
static void GDir2_HomePathWin(GDir2O* obj) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
}
#endif
//===============================================
