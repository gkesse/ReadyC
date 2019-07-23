//===============================================
#include "GProcessMySQL.h"
#include "GMySQL.h"
//===============================================
static GProcessO* m_GProcessMySQLO = 0;
//===============================================
static void GProcessMySQL_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessMySQL_New() {
	GProcessO* lParent = GProcess_New();
	GProcessMySQLO* lChild = (GProcessMySQLO*)malloc(sizeof(GProcessMySQLO));

	lChild->m_parent = lParent;

	lParent->m_child = lChild;
	lParent->Delete = GProcessMySQL_Delete;
	lParent->Run = GProcessMySQL_Run;
	return lParent;
}
//===============================================
void GProcessMySQL_Delete(GProcessO* obj) {
	// Delete All Attributes Before
	GProcess_Delete(m_GProcessMySQLO);
	m_GProcessMySQLO = 0;
}
//===============================================
GProcessO* GProcessMySQL() {
	if(m_GProcessMySQLO == 0) {
		m_GProcessMySQLO = GProcessMySQL_New();
	}
	return m_GProcessMySQLO;
}
//===============================================
static void GProcessMySQL_Run(int argc, char** argv) {
	GMySQL()->Version();
	GMySQL()->MallocRow("CLIENT");
	GMySQL()->RealConnect("CLIENT", "localhost", "root", "test", 0);
	GMySQL()->Query();
	/*while(1) {
		int lFetchRow = GMySQL()->FetchRow();
		if(lFetchRow == 0) break;
		GMySQL()->Version();
		GMySQL()->Version();
		GMySQL()->Version();
	}*/
	GMySQL()->Close("CLIENT");
	GMySQL()->FetchRow("CLIENT");
}
//===============================================
