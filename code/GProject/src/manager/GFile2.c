//===============================================
#include "GFile2.h"
#include "GConsole.h"
#include "GLog.h"
//===============================================
typedef char* GCHAR_PTR;
typedef FILE* GFILE_PTR;
//===============================================
GDECLARE_MAP(GCHAR_PTR, GFILE_PTR, GDBus_GCHAR_PTR_GFILE_PTR)
GDEFINE_MAP(GCHAR_PTR, GFILE_PTR, GDBus_GCHAR_PTR_GFILE_PTR)
//===============================================
static GFile2O* m_GFile2O = 0;
//===============================================
static void GFile2_Exist(char* file);
static void GFile2_Open(char* pFileName, char* file, char* mode);
static int GFile2_Write(char* pFileName, char* data, int size);
static int GFile2_Read(char* pFileName, char* data, int size);
static void GFile2_Close(char* pFileName);
//===============================================
static int GFile2_MapEqual(char* key1, char* key2);
//===============================================
GFile2O* GFile2_New() {
	GFile2O* lObj = (GFile2O*)malloc(sizeof(GFile2O));
    
	lObj->m_pFileMap = GMap_New_GDBus_GCHAR_PTR_GFILE_PTR();

	lObj->Delete = GFile2_Delete;
	lObj->Exist = GFile2_Exist;
	lObj->Open = GFile2_Open;
	lObj->Write = GFile2_Write;
	lObj->Read = GFile2_Read;
	lObj->Format = fprintf;
	lObj->Close = GFile2_Close;
	return lObj;
}
//===============================================
void GFile2_Delete() {
	GFile2O* lObj = GFile2();
	if(lObj != 0) {
		free(lObj);
	}
	m_GFile2O = 0;
}
//===============================================
GFile2O* GFile2() {
	if(m_GFile2O == 0) {
		m_GFile2O = GFile2_New();
	}
	return m_GFile2O;
}
//===============================================
static void GFile2_Exist(char* file) {
    ////GLog()->Write("Execution de la fonction : GFile2_Exist");
	FILE* lFile = fopen(file, "r");
	if(lFile == 0) {GConsole()->Print("[ GFile2 ] Error GFile2_Exist: %s\n", file); exit(0);}
	fclose(lFile);
}
//===============================================
static void GFile2_Open(char* pFileName, char* file, char* mode) {
    ////GLog()->Write("Execution de la fonction : GFile2_Open");
    GMapO(GDBus_GCHAR_PTR_GFILE_PTR)* lpFileMap = m_GFile2O->m_pFileMap;
	FILE* lpFile = fopen(file, mode);
	if(lpFile == 0) {GConsole()->Print("[ GFile2 ] Error GFile2_Open: %s\n", file); exit(0);}
	lpFileMap->SetData(lpFileMap, pFileName, lpFile, GFile2_MapEqual);
}
//===============================================
static int GFile2_Write(char* pFileName, char* data, int size) {
    ////GLog()->Write("Execution de la fonction : GFile2_Write");
    GMapO(GDBus_GCHAR_PTR_GFILE_PTR)* lpFileMap = m_GFile2O->m_pFileMap;
	FILE* lpFile = lpFileMap->GetData(lpFileMap, pFileName, GFile2_MapEqual);
    int lSize = size;
	if(size <= 0) lSize = strlen(data);
    int lBytes = fwrite(data, sizeof(char), lSize, lpFile);
    return lBytes;
}
//===============================================
static int GFile2_Read(char* pFileName, char* data, int size) {
    ////GLog()->Write("Execution de la fonction : GFile2_Read");
    GMapO(GDBus_GCHAR_PTR_GFILE_PTR)* lpFileMap = m_GFile2O->m_pFileMap;
	FILE* lpFile = lpFileMap->GetData(lpFileMap, pFileName, GFile2_MapEqual);
    int lSize = size - 1;
    int lBytes = fread(data, sizeof(char), lSize, lpFile);
    data[lBytes] = 0;
    return lBytes;
}
//===============================================
static void GFile2_Close(char* pFileName) {
    ////GLog()->Write("Execution de la fonction : GFile2_Close");
    GMapO(GDBus_GCHAR_PTR_GFILE_PTR)* lpFileMap = m_GFile2O->m_pFileMap;
	FILE* lpFile = lpFileMap->GetData(lpFileMap, pFileName, GFile2_MapEqual);
    int lRes = fclose(lpFile);
	if(lRes == EOF) {GConsole()->Print("[ GFile2 ] Error GFile2_Close\n"); exit(0);}
}
//===============================================
static int GFile2_MapEqual(char* key1, char* key2) {
	int lStrcmp = strcmp(key1, key2);
	if(lStrcmp == 0) return TRUE;
	return FALSE;
}
//===============================================
