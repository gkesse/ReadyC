//===============================================
#include "GOptions.h"
#include "GString2.h"
#include "GConfig.h"
#include "GConsole.h"
//===============================================
static GOptionsO* m_GOptionsO = 0;
//===============================================
static void GOptions_GetArgs(int argc, char** argv);
//===============================================
GOptionsO* GOptions_New() {
	GOptionsO* lObj = (GOptionsO*)malloc(sizeof(GOptionsO));
	lObj->Delete = GOptions_Delete;
	lObj->GetArgs = GOptions_GetArgs;
	return lObj;
}
//===============================================
void GOptions_Delete() {
	GOptionsO* lObj = GOptions();
	if(lObj != 0) {
		free(lObj);
	}
	m_GOptionsO = 0;
}
//===============================================
GOptionsO* GOptions() {
	if(m_GOptionsO == 0) {
		m_GOptionsO = GOptions_New();
	}
	return m_GOptionsO;
}
//===============================================
static void GOptions_GetArgs(int argc, char** argv) {
	BOOL lShowHelp = TRUE;

	if(argc >= 2) {
		lShowHelp = FALSE;
		char* lOldData = GConfig()->GetData("PROCESS");
        GString2()->Free(lOldData);
		char* lProcess = GString2()->ToUpper(argv[1]);
		GConfig()->SetData("PROCESS", lProcess);
        	/*if(GString2()->IsEqual(lProcess, "CREATE_DATABASE_SQLITE")) {
			lShowHelp = TRUE;
			if(argc >= 2) {
				lShowHelp = false;
				string lDatabaseID = GString::Instance()->toUpper(argv[2]);
				string lDatabaseName = GString::Instance()->toLower(argv[2]);
				GConfig::Instance()->setData("DATABASE_ID", lDatabaseID);
				GConfig::Instance()->setData("DATABASE_NAME", lDatabaseName);
			}
		}*/         
	}

	if(lShowHelp == TRUE) {
		GConfig()->SetData("PROCESS", "HELP");
	}
}
//===============================================
