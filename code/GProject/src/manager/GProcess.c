//===============================================
#include "GProcess.h"
#include "GDebug.h"
//===============================================
static GProcessO* m_GProcessO = 0;
//===============================================
static void GProcess_Process(int argc, char** argv);
static void GProcess_Test(int argc, char** argv);
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
}
//===============================================
static void GProcess_Test(int argc, char** argv) {
	GDebug()->Write(__FUNCTION__, 0);
}
//===============================================
