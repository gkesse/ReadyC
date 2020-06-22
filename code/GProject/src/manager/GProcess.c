//===============================================
#include "GProcess.h"
#include "GCcv.h"
#include "GDebug.h"
//===============================================
static GProcessO* m_GProcessO = 0;
//===============================================
static void GProcess_Run(int argc, char** argv);
//===============================================
static void GProcess_Test(int argc, char** argv);
//===============================================
GProcessO* GProcess_New() {
	GDebug()->Write(__FUNCTION__, _EOA_);
	GProcessO* lObj = (GProcessO*)malloc(sizeof(GProcessO));
	lObj->Delete = GProcess_Delete;
	lObj->Run = GProcess_Run;
	return lObj;
}
//===============================================
void GProcess_Delete() {
	GDebug()->Write(__FUNCTION__, _EOA_);
	GProcessO* lObj = GProcess();
	free(lObj);
	m_GProcessO = 0;
}
//===============================================
GProcessO* GProcess() {
	if(m_GProcessO == 0) {
		m_GProcessO = GProcess_New();
	}
	return m_GProcessO;
}
//===============================================
static void GProcess_Run(int argc, char** argv) {
	GDebug()->Write(__FUNCTION__, _EOA_);
	char* lKey = "";
	for(int i = 1; i < argc;) {
		char* lKey = argv[i++];
		if(strcmp(lKey, "test") == 0) {GProcess_Test(argc, argv); return;}
		break;
	}
	printf("[GProcess] : ERREUR : projet inexistant : %s\n", lKey);
}
//===============================================
static void GProcess_Test(int argc, char** argv) {
	GDebug()->Write(__FUNCTION__, _EOA_);
	GDebug()->Test(argc, argv);
}
//===============================================
