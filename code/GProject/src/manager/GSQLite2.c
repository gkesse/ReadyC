//===============================================
#include "GSQLite2.h"
#include "GMap2.h"
//===============================================
GDECLARE_MAP(GSQLite2, GCHAR_PTR, GVOID_PTR)
GDEFINE_MAP(GSQLite2, GCHAR_PTR, GVOID_PTR)
//===============================================
static GSQLite2O* m_GSQLite2O = 0;
//===============================================
static void GSQLite2_Version();
static void GSQLite2_Open(char* dbId, char* path);
//===============================================
GSQLite2O* GSQLite2_New() {
    GSQLite2O* lObj = (GSQLite2O*)malloc(sizeof(GSQLite2O));

    lObj->m_dbMap = GMap_New(GSQLite2, GCHAR_PTR, GVOID_PTR)();

    lObj->Delete = GSQLite2_Delete;
    lObj->Version = GSQLite2_Version;
    lObj->Open = GSQLite2_Open;
    return lObj;
}
//===============================================
void GSQLite2_Delete() {
    GSQLite2O* lObj = GSQLite2();
    if(lObj != 0) {
        free(lObj);
    }
    m_GSQLite2O = 0;
}
//===============================================
GSQLite2O* GSQLite2() {
    if(m_GSQLite2O == 0) {
        m_GSQLite2O = GSQLite2_New();
    }
    return m_GSQLite2O;
}
//===============================================
static void GSQLite2_Version() {
	const char* lVersion = sqlite3_libversion();
    printf("SQLite version : %s\n", lVersion);
}
//===============================================
static void GSQLite2_Open(char* dbId, char* path) {
    GMapO(GSQLite2, GCHAR_PTR, GVOID_PTR)* lDbMap = m_GSQLite2O->m_dbMap;
	sqlite3* lDb;
	int lOk = sqlite3_open(path, &lDb);
	if(lOk != SQLITE_OK) {printf("[GSQLite2] : Erreur ouverture :\n%s\n", path); exit(0);}
    lDbMap->SetData(lDbMap, dbId, (void*)lDb, GMap_EqualChar);
}
//===============================================
