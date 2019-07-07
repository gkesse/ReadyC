//===============================================
#include "GProcessSocketClient.h"
#include "GSocket2.h"
#include "GConsole.h"
//===============================================
static GProcessO* m_GProcessSocketClientO = 0;
//===============================================
static void GProcessSocketClient_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessSocketClient_New() {
    GProcessO* lParent = GProcess_New();
    GProcessSocketClientO* lChild = (GProcessSocketClientO*)malloc(sizeof(GProcessSocketClientO));

    lChild->m_parent = lParent;

    lParent->m_child = lChild;
    lParent->Delete = GProcessSocketClient_Delete;
    lParent->Run = GProcessSocketClient_Run;
    return lParent;
}
//===============================================
void GProcessSocketClient_Delete() {
	// Delete All Attributes Before
	GProcess_Delete(m_GProcessSocketClientO);
	m_GProcessSocketClientO = 0;
}
//===============================================
GProcessO* GProcessSocketClient() {
    if(m_GProcessSocketClientO == 0) {
        m_GProcessSocketClientO = GProcessSocketClient_New();
    }
    return m_GProcessSocketClientO;
}
//===============================================
static void GProcessSocketClient_Run(int argc, char** argv) {
	GConsole()->Print("[ CLIENT ] Start\n");
	char lMessage[256];

#if defined(__WIN32)
	GSocket2()->Data("CLIENT");
	GSocket2()->Socket("CLIENT");
	GSocket2()->Address("SERVER");

	GSocket2()->Start("CLIENT", 2, 0);

	GSocket2()->Socket2("CLIENT", AF_INET, SOCK_STREAM, 0);
    GSocket2()->Address3("SERVER", AF_INET, "127.0.0.1", 5566);
	GSocket2()->Connect("CLIENT", "SERVER");
	GSocket2()->Recv("CLIENT", lMessage, 255);
	GConsole()->Print("[ CLIENT ] Recv: %s\n", lMessage);
	GSocket2()->Send("CLIENT", "Je veux communiquer", 0);

	GSocket2()->Close("CLIENT");
	GSocket2()->Clean("CLIENT");
	GSocket2()->Clean2("CLIENT");
	GSocket2()->Clean3("SERVER");
#elif defined(__unix)
	// allouer une socket
	GSocket2()->Socket("CLIENT");
	// allouer une adresse
	GSocket2()->Address("SERVER");
	// cr�er une socket
	GSocket2()->Socket2("CLIENT", AF_INET, SOCK_STREAM, IPPROTO_TCP);
	// cr�er une adresse
	GSocket2()->Address3("SERVER", AF_INET, "127.0.0.1", 5566);
	// connecter la socket à l'adresse
	GSocket2()->Connect("CLIENT", "SERVER");
	// Lire un message du serveur
	GSocket2()->Read("CLIENT", lMessage, 255);
	GConsole()->Print("[ SERVER ] Read: %s\n", lMessage);
	// Envoyer un message au serveur
	GSocket2()->Write("CLIENT", "Je communique avec le serveur", 0);
	// Fermer une socket
	GSocket2()->Close("CLIENT");
	// Lib�rer une socket
	GSocket2()->Clean2("CLIENT");
	// Lib�rer une adresse
	GSocket2()->Clean3("SERVER");
#endif
}
//===============================================
