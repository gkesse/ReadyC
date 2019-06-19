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
	char lMessage[255];

#if defined(__WIN32)
	GSocket()->Socket("SERVER");
	GSocket()->Address("SERVER");
	GSocket()->WsaData("SERVER");

	GSocket()->Start("SERVER", 2, 0);
	GSocket()->Status("SERVER");
	GSocket()->Major("SERVER");
	GSocket()->Minor("SERVER");
	GSocket()->MajorMax("SERVER");
	GSocket()->MinorMax("SERVER");
	GSocket()->Socket2("SERVER", AF_INET, SOCK_STREAM, 0);
	GSocket()->Address2("SERVER", AF_INET, INADDR_ANY, 5566);
	GSocket()->Bind("SERVER", "SERVER");
	GSocket()->Listen("SERVER", 5);
	while(1) {
		GSocket()->Address("CLIENT");
		GSocket()->Accept("SERVER", "CLIENT");
		GSocket()->SocketName("CLIENT", "CLIENT");
		GSocket()->AddressIp("CLIENT");
		GSocket()->Port("CLIENT");
		GSocket()->Send("CLIENT", "Bonjour tout le monde", 0);
		GSocket()->Close("CLIENT");
	}
	GSocket()->Close("SERVER");
	GSocket()->Clean("SERVER");
#elif defined(__unix)
	// allouer une socket
	GSocket()->Socket("SERVER");
	GSocket()->Socket("CLIENT");
	// allouer une adresse
	GSocket()->Address("SERVER");
	GSocket()->Address("CLIENT");
	// créer une socket
	GSocket()->Socket2("SERVER", AF_INET, SOCK_STREAM, IPPROTO_TCP);
	// créer une adresse
	GSocket()->Address2("SERVER", AF_INET, INADDR_ANY, 5566);
	// lier la socket à l'adresse
	GSocket()->Bind("SERVER", "SERVER");
	// définir  le nombre de clients à écouter
	GSocket()->Listen("SERVER", 5);
	while(1) {
		// Accepter une connexion cliente
		GSocket()->Accept("SERVER", "CLIENT");
		// Envoyer un message au client
		GSocket()->Write("CLIENT", "Bonjour tout le monde", 0);
		// Lire un message du client
		GSocket()->Read("CLIENT", lMessage, 255);
		GConsole()->Print("[ SERVER ] Read: %s\n", lMessage);
		// Fermer une socket
	}
	// Fermer une socket
	GSocket()->Close("SERVER");
	// Libérer une socket
	GSocket()->Clean2("SERVER");
	GSocket()->Clean2("CLIENT");
	// Libérer une adresse
	GSocket()->Clean3("SERVER");
	GSocket()->Clean3("CLIENT");
#endif
}
//===============================================
