//===============================================
#include "GDir.h"
#include "GShell.h"
#include "GDebug.h"
//===============================================
static GDirO* m_GDirO = 0;
//===============================================
static void GDir_Test(int argc, char** argv);
static void GDir_DataPath(char* path, char* output);
//===============================================
static void GDir_HomePath(GDirO* obj);
//===============================================
#if defined(__unix)
static void GDir_HomePathUnix(GDirO* obj);
static void GDir_TestUnix(int argc, char** argv);
#elif defined(__WIN32)
static void GDir_HomePathWin(GDirO* obj);
static void GDir_TestWin(int argc, char** argv);
#endif
//===============================================
GDirO* GDir_New() {
    GDirO* lObj = (GDirO*)malloc(sizeof(GDirO));

    GDir_HomePath(lObj);

    lObj->Delete = GDir_Delete;
    lObj->Test = GDir_Test;
    lObj->DataPath = GDir_DataPath;
    return lObj;
}
//===============================================
void GDir_Delete() {

}
//===============================================
GDirO* GDir() {
    if(m_GDirO == 0) {
        m_GDirO = GDir_New();
    }
    return m_GDirO;
}
//===============================================
static void GDir_Test(int argc, char** argv) {
    GDebug()->Write(__FUNCTION__, "()", _EOA_);
#if defined(__unix)
    GDir_TestUnix(argc, argv);
#elif defined(__WIN32)
    GDir_TestWin(argc, argv);
#endif
}
//===============================================
#if defined(__unix)
static void GDir_TestUnix(int argc, char** argv) {
    GDebug()->Write(__FUNCTION__, "()", _EOA_);
    char lDebugFile[256];
    GDir()->DataPath("data/debug/debug.txt", lDebugFile);
    printf("%s: %s\n", "m_homePath", GDir()->m_homePath);
    printf("%s: %s\n", "m_dataPath", GDir()->m_dataPath);
    printf("%s: %s\n", "lDebugFile", lDebugFile);
}
#endif
//===============================================
#if defined(__WIN32)
static void GDir_TestWin(int argc, char** argv) {
    GDebug()->Write(__FUNCTION__, "()", _EOA_);
}
#endif
//===============================================
static void GDir_DataPath(char* path, char* output) {
    GDebug()->Write(__FUNCTION__, "()", _EOA_);
    sprintf(output, "%s%s", m_GDirO->m_dataPath, path);
}
//===============================================
static void GDir_HomePath(GDirO* obj) {
    GDebug()->Write(__FUNCTION__, "()", _EOA_);
#if defined(__unix)
    GDir_HomePathUnix(obj);
#elif defined(__WIN32)
    GDir_HomePathWin(obj);
#endif
}
//===============================================
#if defined(__unix)
static void GDir_HomePathUnix(GDirO* obj) {
    GDebug()->Write(__FUNCTION__, "()", _EOA_);
	char lCommand[256];
	sprintf(lCommand, "%s", "echo $HOME");
	GShell()->Run(lCommand, obj->m_homePath, 255, 1);
    sprintf(obj->m_dataPath, "%s%s", obj->m_homePath, GDIR_DATA_PATH);
}
#endif
//===============================================
#if defined(__WIN32)
static void GDir_HomePathWin(GDirO* obj) {
    GDebug()->Write(__FUNCTION__, "()", _EOA_);
}
#endif
//===============================================
