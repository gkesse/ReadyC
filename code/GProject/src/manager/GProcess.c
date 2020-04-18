//===============================================
#include "GProcess.h"
#include "GShell.h"
#include "GDir.h"
#include "GDebug.h"
//===============================================
static GProcessO* m_GProcessO = 0;
//===============================================
static void GProcess_Process(int argc, char** argv);
//===============================================
static void GProcess_Test(int argc, char** argv);
static void GProcess_Help();
//===============================================
GProcessO* GProcess_New() {
	GDebug()->Write(__FUNCTION__, 0);
	GProcessO* lObj = (GProcessO*)malloc(sizeof(GProcessO));
	lObj->Delete = GProcess_Delete;
	lObj->Process = GProcess_Process;
	return lObj;
}
//===============================================
void GProcess_Delete() {
	GDebug()->Write(__FUNCTION__, 0);
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
static void GProcess_Process(int argc, char** argv) {
	GDebug()->Write(__FUNCTION__, 0);
	int lRunFlag = 0;
	for(int i = 1; i < argc;) {
		char* lKey = argv[i++];
		if(strcmp(lKey, "test") == 0) {
			GProcess_Test(argc, argv); lRunFlag = 1; break;
		}
		break;
	}
	if(lRunFlag == 0) GProcess_Help();
}
//===============================================
static void GProcess_Test(int argc, char** argv) {
	GDebug()->Write(__FUNCTION__, 0);
	GDebug()->Test(argc, argv);
}
//===============================================
static void GProcess_Help() {
	GDebug()->Write(__FUNCTION__, 0);
	const char* lModule = "gp_c";
	printf("\n");
	printf("%s\n", "Description:");
	printf("\t%s\n", "Operations sur le module gp_c.");
	printf("\n");
	printf("%s\n", "Utilisation:");
	printf("\t\%s : %s\n", lModule, "afficher aide");
	printf("\t\%s %s : %s\n", lModule, "test", "tester module");
	printf("\n");
}
//===============================================
