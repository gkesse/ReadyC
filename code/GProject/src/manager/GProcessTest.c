//===============================================
#include "GProcessTest.h"
#include "GList.h"
#include "GString2.h"
#include "GConsole.h"
//===============================================
#if defined(__unix)
typedef int* GINT_PTR;
typedef char* GCHAR_PTR;
//===============================================
GDECLARE_LIST(GINT_PTR, GProcessTest_GINT_PTR)
GDEFINE_LIST(GINT_PTR, GProcessTest_GINT_PTR)
//===============================================
GDECLARE_LIST(GCHAR_PTR, GProcessTest_GCHAR_PTR)
GDEFINE_LIST(GCHAR_PTR, GProcessTest_GCHAR_PTR)
#endif
//===============================================
static GProcessO* m_GProcessTestO = 0;
//===============================================
static void GProcessTest_Run(int argc, char** argv);
//===============================================
static void GProcessTest_ListShowInt(int index, int* data);
static void GProcessTest_ListShowChar(int index, char* data);
static int GProcessTest_ListEqualInt(int* data1, char* data2);
//===============================================
GProcessO* GProcessTest_New() {
	GProcessO* lParent = GProcess_New();
	GProcessTestO* lChild = (GProcessTestO*)malloc(sizeof(GProcessTestO));

	lChild->m_parent = lParent;

	lParent->m_child = lChild;
	lParent->Delete = GProcessTest_Delete;
	lParent->Run = GProcessTest_Run;
	return lParent;
}
//===============================================
void GProcessTest_Delete() {
	GProcess_Delete(m_GProcessTestO);
	m_GProcessTestO = 0;
}
//===============================================
GProcessO* GProcessTest() {
	if(m_GProcessTestO == 0) {
		m_GProcessTestO = GProcessTest_New();
	}
	return m_GProcessTestO;
}
//===============================================
static void GProcessTest_Run(int argc, char** argv) {
    int* lIntIdx1 = 0;
    //===============================================
    GConsole()->Print("=================================================\n");
    GConsole()->Print("Je suis une liste generique\n");
    GConsole()->Print("=================================================\n");
    GConsole()->Print("Je suis une liste d'entier\n");
    GListO(GProcessTest_GINT_PTR)* lListInt = GList_New_GProcessTest_GINT_PTR();
    for(int i = 0; i < 5; i++) {
        int* lInt = (int*)malloc(sizeof(int));
        *lInt = i*10;
        lListInt->AddData(lListInt, lInt);
        if(i == 1) lIntIdx1 = lInt;
    }
    GConsole()->Print("J'ai une longueur de: %d\n", lListInt->Size(lListInt));
    GConsole()->Print("Je contiens les nombres suivants\n");
    lListInt->Show(lListInt, GProcessTest_ListShowInt);
    //===============================================
    GConsole()->Print("J'ajoute le nombre 20\n");
    int* lInt = (int*)malloc(sizeof(int));
    *lInt = 20;
    lListInt->AddData(lListInt, lInt);
    lListInt->Show(lListInt, GProcessTest_ListShowInt);
    //===============================================
    GConsole()->Print("Je supprime le nombre d'indice 1\n");
    lListInt->RemoveIndex(lListInt, 1);
    lListInt->Show(lListInt, GProcessTest_ListShowInt);
    //===============================================
    GConsole()->Print("Par contre le pointeur de donnee du nombre d'indice 1 est toujours vivant\n");
    GConsole()->Print("Je suis le pointeur de donnee du nombre d'indice 1: %d\n", *lIntIdx1);
    //===============================================
    GConsole()->Print("Je supprime la premiere occurence du nombres 20\n");
    lListInt->RemoveData(lListInt, "20", GProcessTest_ListEqualInt);
    lListInt->Show(lListInt, GProcessTest_ListShowInt);
    //===============================================
    GConsole()->Print("=================================================\n");
    GConsole()->Print("Je suis une liste de chaine\n");
    GListO(GProcessTest_GCHAR_PTR)* lListChar = GList_New_GProcessTest_GCHAR_PTR();
    for(int i = 0; i < 5; i++) {
        int lLength = 32;
        char* lChar = (char*)malloc(sizeof(char)*lLength);
        sprintf(lChar, "Je suis la chaine %d", i + 1);
        lListChar->AddData(lListChar, lChar);
    }
    GConsole()->Print("J'ai une longueur de: %d\n", lListChar->Size(lListChar));
    GConsole()->Print("Je contiens les chaines suivantes\n");
    lListChar->Show(lListChar, GProcessTest_ListShowChar);
    GConsole()->Print("=================================================\n");
    lListInt->Delete(lListInt);
    lListChar->Delete(lListChar);
}
//===============================================
static void GProcessTest_ListShowInt(int index, int* data) {
    GConsole()->Print("[ %2d ] : [ %5d ]\n", index, *data);
}
//===============================================
static void GProcessTest_ListShowChar(int index, char* data) {
    GConsole()->Print("[ %2d ] : [ %16s ]\n", index, data);
}
//===============================================
static int GProcessTest_ListEqualInt(int* data1, char* data2) {
    int lData2 = GString2()->ToInt(data2);
	if(lData2 == *data1) return TRUE;
	return FALSE;
}
//===============================================
