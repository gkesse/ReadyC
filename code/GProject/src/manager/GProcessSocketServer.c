//===============================================
#include "GProcessSocketServer.h"
#include "GSocket2.h"
#include "GConsole.h"
//===============================================
static GProcessO* m_GProcessSocketServerO = 0;
//===============================================
static void GProcessSocketServer_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessSocketServer_New() {
	GProcessO* lParent = GProcess_New();
	GProcessSocketServerO* lChild = (GProcessSocketServerO*)malloc(sizeof(GProcessSocketServerO));

	lChild->m_parent = lParent;

	lParent->m_child = lChild;
	lParent->Delete = GProcessSocketServer_Delete;
	lParent->Run = GProcessSocketServer_Run;
	return lParent;
}
//===============================================
void GProcessSocketServer_Delete() {
	// Delete All Attributes Before
	GProcess_Delete(m_GProcessSocketServerO);
	m_GProcessSocketServerO = 0;
}
//===============================================
GProcessO* GProcessSocketServer() {
	if(m_GProcessSocketServerO == 0) {
		m_GProcessSocketServerO = GProcessSocketServer_New();
	}
	return m_GProcessSocketServerO;
}
//===============================================
static void GProcessSocketServer_Run(int argc, char** argv) {
	GConsole()->Print("[ SERVER ] Start\n");
	char lMessage[256];

#if defined(__WIN32)
	GSocket2()->Data("SERVER");
	GSocket2()->Socket("SERVER");
	GSocket2()->Socket("CLIENT");
	GSocket2()->Address("SERVER");
	GSocket2()->Address("CLIENT");

	GSocket2()->Start("SERVER", 2, 0);
	GSocket2()->Socket2("SERVER", AF_INET, SOCK_STREAM, 0);
	GSocket2()->Address2("SERVER", AF_INET, INADDR_ANY, 5566);
	GSocket2()->Bind("SERVER", "SERVER");
	GSocket2()->Listen("SERVER", 5);

	while(1) {
		GSocket2()->Accept("SERVER", "CLIENT");
		GSocket2()->Send("CLIENT", "Bonjour tout le monde", 0);
		GSocket2()->Recv("CLIENT", lMessage, 255);
		GConsole()->Print("[ SERVER ] Recv: %s\n", lMessage);
		GSocket2()->Close("CLIENT");
	}

	GSocket2()->Close("SERVER");
	GSocket2()->Clean("SERVER");
	GSocket2()->Clean2("SERVER");
	GSocket2()->Clean2("CLIENT");
	GSocket2()->Clean3("SERVER");
	GSocket2()->Clean3("CLIENT");
#endif
}
//===============================================
