//===============================================
#include "GFile2.h"
#include "GConsole.h"
//===============================================
static GFile2O* m_GFile2O = 0;
//===============================================
static void GFile2_Exist(char* file);
//===============================================
GFile2O* GFile2_New() {
	GFile2O* lObj = (GFile2O*)malloc(sizeof(GFile2O));
	lObj->Delete = GFile2_Delete;
	lObj->Exist = GFile2_Exist;
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
	FILE* lFile = fopen(file, "r");
	if(lFile == 0) {GConsole()->Print("[ GFile2 ] Error GFile2_Exist: %s\n", file); exit(0);}
	fclose(lFile);
}
//===============================================
