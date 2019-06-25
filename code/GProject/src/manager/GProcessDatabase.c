//===============================================
#include "GProcessDatabase.h"
#include "GDatabase.h"
//===============================================
static GProcessO* m_GProcessDatabaseO = 0;
//===============================================
static void GProcessDatabase_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessDatabase_New() {
	GProcessO* lParent = GProcess_New();
	GProcessDatabaseO* lChild = (GProcessDatabaseO*)malloc(sizeof(GProcessDatabaseO));

	lChild->m_parent = lParent;

	lParent->m_child = lChild;
	lParent->Delete = GProcessDatabase_Delete;
	lParent->Run = GProcessDatabase_Run;
	return lParent;
}
//===============================================
void GProcessDatabase_Delete(GProcessO* obj) {
	// Delete All Attributes Before
	GProcess_Delete(m_GProcessDatabaseO);
	m_GProcessDatabaseO = 0;
}
//===============================================
GProcessO* GProcessDatabase() {
	if(m_GProcessDatabaseO == 0) {
		m_GProcessDatabaseO = GProcessDatabase_New();
	}
	return m_GProcessDatabaseO;
}
//===============================================
static void GProcessDatabase_Run(int argc, char** argv) {
	GDatabase()->Version();
	GDatabase()->Open("ELEPHANT", "data/data/elephant.db");

	GDatabase()->Exec("ELEPHANT", 0,
			"DROP TABLE Persons");

	GDatabase()->Exec("ELEPHANT", 0,
			"CREATE TABLE Persons ("
			"PersonID INT,"
			"LastName VARCHAR(255),"
			"Address VARCHAR(255),"
			"City VARCHAR(255))");

	GDatabase()->ShowTables("ELEPHANT");

	GDatabase()->Close("ELEPHANT");

	GDatabase()->Delete();
}
//===============================================
