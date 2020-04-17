//===============================================
#include "GShell.h"
#include "GDebug.h"
//===============================================
static GShellO* m_GShellO = 0;
//===============================================
static void GShell_Test(int argc, char** argv);
static void GShell_Run(const char* command, char* output, int size, int shift);
//===============================================
GShellO* GShell_New() {
	GDebug()->Write(__FUNCTION__, 0);
	GShellO* lObj = (GShellO*)malloc(sizeof(GShellO));
	lObj->Delete = GShell_Delete;
	lObj->Test = GShell_Test;
	lObj->Run = GShell_Run;
	return lObj;
}
//===============================================
void GShell_Delete() {
	GDebug()->Write(__FUNCTION__, 0);
	GShellO* lObj = GShell();
	free(lObj);
	m_GShellO = 0;
}
//===============================================
GShellO* GShell() {
	if(m_GShellO == 0) {
		m_GShellO = GShell_New();
	}
	return m_GShellO;
}
//===============================================
static void GShell_Test(int argc, char** argv) {
	GDebug()->Write(__FUNCTION__, 0);
	char lCommand[256];
	char lOuput[256];
	sprintf(lCommand, "%s", "echo %HOMEDRIVE%%HOMEPATH%");
	GShell()->Run(lCommand, lOuput, 255, 1);
	printf("%s\n", lOuput);
	printf("%s\n", lOuput);
}
//===============================================
static void GShell_Run(const char* command, char* output, int size, int shift) {
	GDebug()->Write(__FUNCTION__, 0);
	FILE* lpFile = popen(command, "r");
	if(output != 0) {
		int lBytes = fread(output, 1, size, lpFile);
		if(lBytes >= 1) {
			output[lBytes] = 0;
			if(shift == 1) output[lBytes - 1] = 0;
		}
	}
	pclose(lpFile);
}
//===============================================
