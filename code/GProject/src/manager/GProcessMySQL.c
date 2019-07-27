//===============================================
#include "GProcessMySQL.h"
#include "GMySQL.h"
#include "GConfig.h"
#include "GConsole.h"
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

	GMySQL()->Init("MYSQL");

	GMySQL()->RealConnect("MYSQL", "localhost", "gkesse", "admin", "hellodb", 0);

	GMySQL()->Query("MYSQL", ""
			"DROP TABLE IF EXISTS Persons;"
	);
	GMySQL()->Query("MYSQL", ""
			"CREATE TABLE Persons ("
			"Id INT PRIMARY KEY NOT NULL AUTO_INCREMENT,"
			"Name VARCHAR(255),"
			"Address VARCHAR(255),"
			"Email VARCHAR(255),"
			"Phone VARCHAR(255)"
			");"
	);
	GMySQL()->Query("MYSQL", ""
			"INSERT INTO Persons (Name, Address, Email, Phone) VALUES "
			"('NAME_1', 'ADDRESS_1', 'tiakagerard@hotmail.com', '06.07.08.08.10'),"
			"('NAME_2', 'ADDRESS_2', 'EMAIL_2', 'PHONE_2'),"
			"('NAME_3', 'ADDRESS_3', 'EMAIL_3', 'PHONE_3'),"
			"('NAME_4', 'ADDRESS_4', 'EMAIL_4', 'PHONE_4'),"
			"('NAME_5', 'ADDRESS_5', 'EMAIL_5', 'PHONE_5');"
	);
	GMySQL()->QueryPrint("MYSQL", "MYSQL", "MYSQL", "MYSQL", ""
			"CALL GProcSelectPersons()"
	);

	GMySQL()->Close("MYSQL");
	GMySQL()->FreeRow("MYSQL");

	GMySQL()->Close("SQLITE");
	GMySQL()->FreeRow("SQLITE");
}
//===============================================
