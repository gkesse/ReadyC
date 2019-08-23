//===============================================
#include "GProcessArgTable.h"
#include "GConsole.h"
//===============================================
static GProcessO* m_GProcessArgTableO = 0;
//===============================================
static void GProcessArgTable_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessArgTable_New() {
	GProcessO* lParent = GProcess_New();
	GProcessArgTableO* lChild = (GProcessArgTableO*)malloc(sizeof(GProcessArgTableO));

	lChild->m_parent = lParent;

	lParent->m_child = lChild;
	lParent->Delete = GProcessArgTable_Delete;
	lParent->Run = GProcessArgTable_Run;
	return lParent;
}
//===============================================
void GProcessArgTable_Delete() {
	GProcess_Delete(m_GProcessArgTableO);
	m_GProcessArgTableO = 0;
}
//===============================================
GProcessO* GProcessArgTable() {
	if(m_GProcessArgTableO == 0) {
		m_GProcessArgTableO = GProcessArgTable_New();
	}
	return m_GProcessArgTableO;
}
//===============================================
struct arg_lit *verb, *help, *version;
struct arg_int *level;
struct arg_file *o, *file;
struct arg_end *end;
//===============================================
static void GProcessArgTable_Run(int argc, char** argv) {
	GConsole()->Print("=================================================\n");
	GConsole()->Print("Je suis un gestionnaire d'options\n");
	GConsole()->Print("=================================================\n");
	void *argtable[] = {
			help    = arg_litn(NULL, "help", 0, 1, "display this help and exit"),
			version = arg_litn(NULL, "version", 0, 1, "display version info and exit"),
			level   = arg_intn(NULL, "level", "<n>", 0, 1, "foo value"),
			verb    = arg_litn("v", "verbose", 0, 1, "verbose output"),
			o       = arg_filen("o", NULL, "myfile", 0, 1, "output file"),
			file    = arg_filen(NULL, NULL, "<file>", 1, 100, "input files"),
			end     = arg_end(20),
	};
	GConsole()->Print("=================================================\n");
}
//===============================================
