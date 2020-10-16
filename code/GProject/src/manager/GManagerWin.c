//===============================================
#include "GManagerWin.h"
//===============================================
static GManagerO* m_GManagerWinO = 0;
//===============================================
#define B_COMMAND (256)
//===============================================
// obj
static void GManagerWin_Init(GManagerO* obj);
static void GManagerWin_HomePathObj(GManagerO* obj);
static void GManagerWin_DataPathObj(GManagerO* obj);
//===============================================
// shell
static void GManagerWin_Shell(char* command, char* output, int size, int shift);
//===============================================
// global
//===============================================
GManagerO* GManagerWin_New() {
    GManagerO* lParent = GManager_New();
    GManagerWinO* lChild = (GManagerWinO*)malloc(sizeof(GManagerWinO));
    
    lChild->parent = lParent;
    
    GManagerWin_Init(lParent);
    
    lParent->child = lChild;
    lParent->Delete = GManagerWin_Delete;
    return lParent;
}
//===============================================
void GManagerWin_Delete() {
    GManager_Delete();
    m_GManagerWinO = 0;
}
//===============================================
GManagerO* GManagerWin() {
    if(m_GManagerWinO == 0) {
        m_GManagerWinO = GManagerWin_New();
    }
    return m_GManagerWinO;
}
//===============================================
// obj
//===============================================
static void GManagerWin_Init(GManagerO* obj) {
    // app
    GManagerWin_HomePathObj(obj);
    strcpy(obj->m_mgr->app->data_path, ".readyc\\data");
    GManagerWin_DataPathObj(obj);
    // sqlite
    strcpy(obj->m_mgr->sqlite->db_path, "C:\\Users\\Admin\\Downloads\\Programs\\ReadyBin\\win\\.CONFIG_O.dat");
    // json
    sprintf(obj->m_mgr->json->file, "%s\\json\\menu.json", obj->m_mgr->app->data_path);
}
//===============================================
static void GManagerWin_HomePathObj(GManagerO* obj) {
    char lCommand[B_COMMAND+1];
    sprintf(lCommand, "echo %%HOMEDRIVE%%\%%HOMEPATH%%");
    GManagerWin_Shell(lCommand, obj->m_mgr->app->home_path, B_HOME_PATH, 1);
}
//===============================================
static void GManagerWin_DataPathObj(GManagerO* obj) {
    char lDataPath[B_DATA_PATH+1];
    sprintf(lDataPath, "%s\\%s", obj->m_mgr->app->home_path, obj->m_mgr->app->data_path);
    strcpy(obj->m_mgr->app->data_path, lDataPath);
}
//===============================================
// shell
//===============================================
static void GManagerWin_Shell(char* command, char* output, int size, int shift) {
	FILE* lpFile = popen(command, "r");
	if(output != 0) {
		int lBytes = fread(output, 1, size, lpFile);
		if(lBytes >= 1) {
			output[lBytes] = 0;
			if(shift == 1) output[lBytes - 1] = 0;
		}
	}
	pclose(lpFile);
}
//===============================================
