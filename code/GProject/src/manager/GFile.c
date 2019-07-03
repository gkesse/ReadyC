//===============================================
#include "GFile.h"
#include "GConsole.h"
//===============================================
static GFileO* m_GFileO = 0;
//===============================================
static void GFile_Exist(char* file);
//===============================================
GFileO* GFile_New() {
    GFileO* lObj = (GFileO*)malloc(sizeof(GFileO));
    lObj->Delete = GFile_Delete;
    lObj->Exist = GFile_Exist;
    return lObj;
}
//===============================================
void GFile_Delete() {
    GFileO* lObj = GFile();
    if(lObj != 0) {
        free(lObj);
    }
    m_GFileO = 0;
}
//===============================================
GFileO* GFile() {
    if(m_GFileO == 0) {
        m_GFileO = GFile_New();
    }
    return m_GFileO;
}
//===============================================
static void GFile_Exist(char* file) {
    FILE* lFile = fopen(file, "r");
	if(lFile == 0) {GConsole()->Print("[ GFile ] Error GFile_Exist\n"); exit(0);}
	fclose(lFile);
}
//===============================================
