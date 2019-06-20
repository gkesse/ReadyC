//===============================================
#include "GProcessMap.h"
#include "GMap.h"
#include "GConsole.h"
//===============================================
typedef int GINT;
typedef char GCHAR;
typedef char* GCHAR_PTR;
//===============================================
GDECLARE_MAP(GINT, GCHAR, GProcessMap_GINT_GCHAR)
GDEFINE_MAP(GINT, GCHAR, GProcessMap_GINT_GCHAR)
//===============================================
GDECLARE_MAP(GCHAR_PTR, GCHAR_PTR, GProcessMap_GCHAR_PTR_GCHAR_PTR)
GDEFINE_MAP(GCHAR_PTR, GCHAR_PTR, GProcessMap_GCHAR_PTR_GCHAR_PTR)
//===============================================
static GProcessO* m_GProcessMapO = 0;
//===============================================
static void GProcessMap_Run(int argc, char** argv);
//===============================================
static int GProcessMap_MapEqual(char* str1, char* str2);
static void GProcessMap_MapShow(int key, char value);
static void GProcessMap_MapShow2(char* key, char* value);
//===============================================
GProcessO* GProcessMap_New() {
    GProcessO* lParent = GProcess_New();
    GProcessMapO* lChild = (GProcessMapO*)malloc(sizeof(GProcessMapO));

    lChild->m_parent = lParent;

    lParent->m_child = lChild;
    lParent->Delete = GProcessMap_Delete;
    lParent->Run = GProcessMap_Run;
    return lParent;
}
//===============================================
void GProcessMap_Delete(GProcessO* obj) {
    GProcess_Delete(obj);
    m_GProcessMapO = 0;
}
//===============================================
GProcessO* GProcessMap() {
    if(m_GProcessMapO == 0) {
        m_GProcessMapO = GProcessMap_New();
    }
    return m_GProcessMapO;
}
//===============================================
static void GProcessMap_Run(int argc, char** argv) {
	GMapO(GProcessMap_GINT_GCHAR)* lMap = GMap_New_GProcessMap_GINT_GCHAR();
	lMap->SetData(lMap, 0, 'A', 0);
	lMap->SetData(lMap, 1, 'B', 0);
	lMap->SetData(lMap, 2, 'C', 0);
	lMap->SetData(lMap, 3, 'D', 0);
	lMap->Show(lMap, GProcessMap_MapShow);
	lMap->Delete(lMap);

	GConsole()->Print("\n");

	GMapO(GProcessMap_GCHAR_PTR_GCHAR_PTR)* lMap2 = GMap_New_GProcessMap_GCHAR_PTR_GCHAR_PTR();
	lMap2->SetData(lMap2, "Nom", "KESSE", GProcessMap_MapEqual);
	lMap2->SetData(lMap2, "Prenom", "Gerard", GProcessMap_MapEqual);
	lMap2->SetData(lMap2, "Email", "gerard.kesse@readydev.com", GProcessMap_MapEqual);
	lMap2->SetData(lMap2, "Diplome", "Ingenieur", 0);
	lMap2->SetData(lMap2, "Formation", "Informatique Industrielle", GProcessMap_MapEqual);
	lMap2->SetData(lMap2, "Ecole", "Polytech'Montpellier", GProcessMap_MapEqual);
	lMap2->Show(lMap2, GProcessMap_MapShow2);
	lMap2->Delete(lMap2);
}
//===============================================
static int GProcessMap_MapEqual(char* str1, char* str2) {
	int lStrcmp = strcmp(str1, str2);
	if(lStrcmp == 0) return TRUE;
	return FALSE;
}
//===============================================
static void GProcessMap_MapShow(int key, char value) {
	printf("%d = %c\n", key, value);
}
//===============================================
static void GProcessMap_MapShow2(char* key, char* value) {
	printf("%s = %s\n", key, value);
}
//===============================================
