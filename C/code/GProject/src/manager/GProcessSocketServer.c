//===============================================
#include "GProcessSocketServer.h"
#include "GSocket.h"
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
void GProcessSocketServer_Delete(GProcessO* obj) {
	GProcess_Delete(obj);
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
	GSocket()->Data("SERVER");
	GSocket()->Socket("SERVER");
	GSocket()->Socket("CLIENT");
	GSocket()->Address("SERVER");
	GSocket()->Address("CLIENT");

	GSocket()->Start("SERVER", 2, 0);
	GSocket()->Socket2("SERVER", AF_INET, SOCK_STREAM, 0);
	GSocket()->Address2("SERVER", AF_INET, INADDR_ANY, 5566);
	GSocket()->Bind("SERVER", "SERVER");
	GSocket()->Listen("SERVER", 5);

	while(1) {
		GSocket()->Accept("SERVER", "CLIENT");
		GSocket()->Send("CLIENT", "Bonjour tout le monde", 0);
		GSocket()->Recv("CLIENT", lMessage, 255);
		GConsole()->Print("[ SERVER ] Recv: %s\n", lMessage);
		GSocket()->Close("CLIENT");
	}

	GSocket()->Close("SERVER");
	GSocket()->Clean("SERVER");
	GSocket()->Clean2("SERVER");
	GSocket()->Clean2("CLIENT");
	GSocket()->Clean3("SERVER");
	GSocket()->Clean3("CLIENT");
#elif defined(__unix)
	GSocket()->Socket("SERVER");
	GSocket()->Socket("CLIENT");
	GSocket()->Address("SERVER");
	GSocket()->Address("CLIENT");

	GSocket()->Socket2("SERVER", AF_INET, SOCK_STREAM, IPPROTO_TCP);
	GSocket()->Address2("SERVER", AF_INET, INADDR_ANY, 5566);
	GSocket()->Bind("SERVER", "SERVER");
	GSocket()->Listen("SERVER", 5);

	while(1) {
		GSocket()->Accept("SERVER", "CLIENT");
		GSocket()->Write("CLIENT", "Bonjour tout le monde", 0);
		GSocket()->Read("CLIENT", lMessage, 255);
		GConsole()->Print("[ SERVER ] Read: %s\n", lMessage);
		GSocket()->Close("CLIENT");
	}

	GSocket()->Close("SERVER");
	GSocket()->Clean2("SERVER");
	GSocket()->Clean2("CLIENT");
	GSocket()->Clean3("SERVER");
	GSocket()->Clean3("CLIENT");
#endif
}
//===============================================
