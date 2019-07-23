//===============================================
#include "GProcessMySQL.h"
#include "GMySQL.h"
#include "GConfig.h"
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
	// CONNEXION MULTIPLE
	GMySQL()->MallocRow("MYSQL");
	GMySQL()->MallocRow("SQLITE");

	GMySQL()->Init("MYSQL");
	GMySQL()->Init("SQLITE");


	GMySQL()->RealConnect("MYSQL", "localhost", "gkesse", "admin", "pmcdev", 0);
	GMySQL()->RealConnect("SQLITE", "localhost", "root", "super", "dbmysql", 0);

	GMySQL()->Query("MYSQL", ""
			"CREATE TABLE sqlite_pers ("
			"Id INT PRIMARY KEY NOT NULL AUTO_INCREMENT,"
			"Name varchar(255),"
			"Address varchar(255),"
			"Email varchar(255)"
			");"
	);

	GMySQL()->Query("SQLITE", ""
			"CREATE TABLE mysql_pers ("
			"Id INT PRIMARY KEY NOT NULL AUTO_INCREMENT,"
			"Name varchar(255),"
			"Address varchar(255),"
			"Email varchar(255)"
			");"
	);

	GMySQL()->Close("MYSQL");
	GMySQL()->FreeRow("MYSQL");

	GMySQL()->Close("SQLITE");
	GMySQL()->FreeRow("SQLITE");
}
//===============================================
