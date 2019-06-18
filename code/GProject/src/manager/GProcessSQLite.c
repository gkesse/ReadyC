//===============================================
#include "GProcessSQLite.h"
#include "GSQLite.h"
//===============================================
static GProcessO* m_GProcessSQLiteO = 0;
//===============================================
static void GProcessSQLite_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessSQLite_New() {
	GProcessO* lParent = GProcess_New();
	GProcessSQLiteO* lChild = (GProcessSQLiteO*)malloc(sizeof(GProcessSQLiteO));

	lChild->m_parent = lParent;

	lParent->m_child = lChild;
	lParent->Delete = GProcessSQLite_Delete;
	lParent->Run = GProcessSQLite_Run;
	return lParent;
}
//===============================================
void GProcessSQLite_Delete(GProcessO* obj) {
	GProcess_Delete(obj);
	m_GProcessSQLiteO = 0;
}
//===============================================
GProcessO* GProcessSQLite() {
	if(m_GProcessSQLiteO == 0) {
		m_GProcessSQLiteO = GProcessSQLite_New();
	}
	return m_GProcessSQLiteO;
}
//===============================================
static void GProcessSQLite_Run(int argc, char** argv) {
	GSQLite()->Version();
	GSQLite()->Open("ELEPHANT", "data/data/elephant.db");

	GSQLite()->Exec("ELEPHANT", 0,
			"DROP TABLE Persons");

	GSQLite()->Exec("ELEPHANT", 0,
			"CREATE TABLE Persons ("
			"PersonID INT,"
			"LastName VARCHAR(255),"
			"Address VARCHAR(255),"
			"City VARCHAR(255))");

	GSQLite()->ShowTables("ELEPHANT");

	GSQLite()->Close("ELEPHANT");
}
//===============================================
