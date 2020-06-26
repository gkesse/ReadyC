//===============================================
#include "GProcessList.h"
#include "GList.h"
#include "GString2.h"
#include "GConsole.h"
#include "GLog.h"
//===============================================
typedef int* GINT_PTR;
typedef char* GCHAR_PTR;
//===============================================
GDECLARE_LIST(GINT_PTR, GProcessList_GINT_PTR)
GDEFINE_LIST(GINT_PTR, GProcessList_GINT_PTR)
//===============================================
GDECLARE_LIST(GCHAR_PTR, GProcessList_GCHAR_PTR)
GDEFINE_LIST(GCHAR_PTR, GProcessList_GCHAR_PTR)
//===============================================
static GProcessO* m_GProcessListO = 0;
//===============================================
static void GProcessList_Run(int argc, char** argv);
//===============================================
static void GProcessList_ListShowInt(int index, int* data);
static void GProcessList_ListShowChar(int index, char* data);
static int GProcessList_ListEqualInt(int* data1, char* data2);
static int GProcessList_ListEqualChar(char* data1, char* data2);
//===============================================
GProcessO* GProcessList_New() {
	GProcessO* lParent = GProcess_New();
	GProcessListO* lChild = (GProcessListO*)malloc(sizeof(GProcessListO));

	lChild->m_parent = lParent;

	lParent->m_child = lChild;
	lParent->Delete = GProcessList_Delete;
	lParent->Run = GProcessList_Run;
	return lParent;
}
//===============================================
void GProcessList_Delete() {
	GProcess_Delete(m_GProcessListO);
	m_GProcessListO = 0;
}
//===============================================
GProcessO* GProcessList() {
	if(m_GProcessListO == 0) {
		m_GProcessListO = GProcessList_New();
	}
	return m_GProcessListO;
}
//===============================================
static void GProcessList_Run(int argc, char** argv) {
    //GLog()->Write("#================================================");
    //GLog()->Write("# Execution de la fonction : GProcessList_Run");
    //GLog()->Write("#================================================");
    GConsole()->Print("=================================================\n");
    GConsole()->Print("Je suis une liste generique\n");
    GConsole()->Print("=================================================\n");
    GConsole()->Print("Je suis une liste d'entier\n");
    GConsole()->Print("=================================================\n");
    GListO(GProcessList_GINT_PTR)* lListInt = GList_New_GProcessList_GINT_PTR();
    for(int i = 0; i < 5; i++) {
        int* lInt = (int*)malloc(sizeof(int));
        *lInt = i*10;
        lListInt->AddData(lListInt, lInt);
    }
    //===============================================
    GConsole()->Print("J'ai une longueur de:\n");
    GConsole()->Print("%d\n", lListInt->Size(lListInt));
    //===============================================
    GConsole()->Print("Je contiens les nombres suivants:\n");
    lListInt->Show(lListInt, GProcessList_ListShowInt);
    //===============================================
    GConsole()->Print("J'ajoute le nombre 20, 40, 60, 40:\n");
    int* lInt = 0;
    lInt = (int*)malloc(sizeof(int));
    *lInt = 20;
    lListInt->AddData(lListInt, lInt);
    lInt = (int*)malloc(sizeof(int));
    *lInt = 40;
    lListInt->AddData(lListInt, lInt);
    lInt = (int*)malloc(sizeof(int));
    *lInt = 60;
    lListInt->AddData(lListInt, lInt);
    lInt = (int*)malloc(sizeof(int));
    *lInt = 40;
    lListInt->AddData(lListInt, lInt);
    lListInt->Show(lListInt, GProcessList_ListShowInt);
    //===============================================
    GConsole()->Print("Je compte les occurences du nombre 40:\n");
    GConsole()->Print("%d\n", lListInt->CountData(lListInt, "40", GProcessList_ListEqualInt));
    //===============================================
    GConsole()->Print("Je modifie le nombre d'indice 0:\n");
    int* lIntIdx0 = (int*)malloc(sizeof(int));
    *lIntIdx0 = 1000;
    lListInt->SetData(lListInt, 0, lIntIdx0, 0);
    lListInt->Show(lListInt, GProcessList_ListShowInt);
    //===============================================
    GConsole()->Print("Je supprime le nombre d'indice 1:\n");
    lListInt->RemoveIndex(lListInt, 1, 0);
    lListInt->Show(lListInt, GProcessList_ListShowInt);
    //===============================================
    GConsole()->Print("Je supprime la premiere occurence du nombre 20:\n");
    lListInt->RemoveData(lListInt, "20", GProcessList_ListEqualInt, 0);
    lListInt->Show(lListInt, GProcessList_ListShowInt);
    //===============================================
    GConsole()->Print("Je supprime toutes les occurences du nombre 40:\n");
    lListInt->RemoveDataAll(lListInt, "40", GProcessList_ListEqualInt, 0);
    lListInt->Show(lListInt, GProcessList_ListShowInt);
    //===============================================
    GConsole()->Print("Je vide la liste:\n");
    lListInt->Clear(lListInt, 0);
    lListInt->Show(lListInt, GProcessList_ListShowInt);
    GConsole()->Print("%d\n", lListInt->Size(lListInt));
    //===============================================
    GConsole()->Print("Je supprime la liste:\n");
    lListInt->Delete(lListInt, 0);
    GConsole()->Print("%d\n", lListInt->Size(lListInt));
    //===============================================
    GConsole()->Print("=================================================\n");
    GConsole()->Print("Je suis une liste de chaine\n");
    GConsole()->Print("=================================================\n");
    GListO(GProcessList_GCHAR_PTR)* lListChar = GList_New_GProcessList_GCHAR_PTR();
    for(int i = 0; i < 5; i++) {
        int lLength = 32;
        char* lChar = (char*)malloc(sizeof(char)*lLength);
        sprintf(lChar, "Je suis la chaine %d", i*10);
        lListChar->AddData(lListChar, lChar);
    }
    //===============================================
    GConsole()->Print("J'ai une longueur de: %d\n", lListChar->Size(lListChar));
    GConsole()->Print("Je contiens les chaines suivantes:\n");
    lListChar->Show(lListChar, GProcessList_ListShowChar);
    //===============================================
    GConsole()->Print("J'ajoute les chaines 20, 40, 60, 40:\n");
    int lLength = 32;
    char* lChar;
    lChar = (char*)malloc(sizeof(char)*lLength);
    sprintf(lChar, "Je suis la chaine %d", 20);
    lListChar->AddData(lListChar, lChar);
    lChar = (char*)malloc(sizeof(char)*lLength);
    sprintf(lChar, "Je suis la chaine %d", 40);
    lListChar->AddData(lListChar, lChar);
    lChar = (char*)malloc(sizeof(char)*lLength);
    sprintf(lChar, "Je suis la chaine %d", 60);
    lListChar->AddData(lListChar, lChar);
    lChar = (char*)malloc(sizeof(char)*lLength);
    sprintf(lChar, "Je suis la chaine %d", 40);
    lListChar->AddData(lListChar, lChar);
    lListChar->Show(lListChar, GProcessList_ListShowChar);
    //===============================================
    GConsole()->Print("Je compte les occurences de la chaine 40:\n");
    GConsole()->Print("%d\n", lListChar->CountData(lListChar, "Je suis la chaine 40", GProcessList_ListEqualChar));
    //===============================================
    GConsole()->Print("Je modifie la chaine d'indice 0:\n");
    char* lCharIdx0 = (char*)malloc(sizeof(char)*lLength);
    sprintf(lCharIdx0, "Je suis la chaine %d", 1000);
    lListChar->SetData(lListChar, 0, lCharIdx0, 0);
    lListChar->Show(lListChar, GProcessList_ListShowChar);
    //===============================================
    GConsole()->Print("Je supprime la chaine d'indice 1:\n");
    lListChar->RemoveIndex(lListChar, 1, 0);
    lListChar->Show(lListChar, GProcessList_ListShowChar);
    //===============================================
    GConsole()->Print("Je supprime la premiere occurence de la chaine 20:\n");
    lListChar->RemoveData(lListChar, "Je suis la chaine 20", GProcessList_ListEqualChar, 0);
    lListChar->Show(lListChar, GProcessList_ListShowChar);
    //===============================================
    GConsole()->Print("Je supprime toutes les occurences de la chaine 40:\n");
    lListChar->RemoveDataAll(lListChar, "Je suis la chaine 40", GProcessList_ListEqualChar, 0);
    lListChar->Show(lListChar, GProcessList_ListShowChar);
    //===============================================
    GConsole()->Print("Je vide la liste:\n");
    lListChar->Clear(lListChar, 0);
    lListChar->Show(lListChar, GProcessList_ListShowChar);
    GConsole()->Print("%d\n", lListChar->Size(lListChar));
    //===============================================
    GConsole()->Print("Je supprime la liste:\n");
    lListChar->Delete(lListChar, 0);
    GConsole()->Print("%d\n", lListChar->Size(lListChar));
    GConsole()->Print("=================================================\n");
}
//===============================================
static void GProcessList_ListShowInt(int index, int* data) {
    GConsole()->Print("[ %2d ] : [ %5d ]\n", index, *data);
}
//===============================================
static void GProcessList_ListShowChar(int index, char* data) {
    GConsole()->Print("[ %2d ] : [ %-22s ]\n", index, data);
}
//===============================================
static int GProcessList_ListEqualInt(int* data1, char* data2) {
    int lData2 = GString2()->ToInt(data2);
	if(lData2 == *data1) return TRUE;
	return FALSE;
}
//===============================================
static int GProcessList_ListEqualChar(char* data1, char* data2) {
    int lStrcmp = strcmp(data1, data2);
	if(lStrcmp == 0) return TRUE;
	return FALSE;
}
//===============================================