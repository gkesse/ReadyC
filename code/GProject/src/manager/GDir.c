//===============================================
#include "GDir.h"
#include "GDebug.h"
//===============================================
static GDirO* m_GDirO = 0;
//===============================================
static void GDir_Test(int argc, char** argv);
static char* GDir_HomePath();
static char* GDir_DataPath();
//===============================================
GDirO* GDir_New() {
	GDebug()->Write(__FUNCTION__, 0);
	GDirO* lObj = (GDirO*)malloc(sizeof(GDirO));
	lObj->Delete = GDir_Delete;
	lObj->Test = GDir_Test;
	lObj->HomePath = GDir_HomePath;
	lObj->DataPath = GDir_DataPath;
	return lObj;
}
//===============================================
void GDir_Delete() {
	GDebug()->Write(__FUNCTION__, 0);
	GDirO* lObj = GDir();
	free(lObj);
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
static void GDir_Test(int argc, char** argv) {
	GDebug()->Write(__FUNCTION__, 0);
}
//===============================================
static char* GDir_HomePath() {
	return m_GDirO->m_homePath;
}
//===============================================
static char* GDir_DataPath() {
	return m_GDirO->m_dataPath;
}
//===============================================
