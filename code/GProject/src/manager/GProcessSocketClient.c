//===============================================
#include "GProcessSocketClient.h"
#include "GSocket.h"
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
void GProcessSocketClient_Delete(GProcessO* obj) {
    GProcess_Delete(obj);
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
	char lMessage[255];

#if defined(__WIN32)
    GSocket()->Start(2, 0);
    GSocket()->Socket(AF_INET, SOCK_STREAM, 0);
    GSocket()->Address(AF_INET, "127.0.0.1", 5566);
    GSocket()->Connect();
    GSocket()->Recv();
    GSocket()->Close();
    GSocket()->Clean();
#elif defined(__unix)
	// allouer une socket
	GSocket()->Socket("CLIENT");
	// allouer une adresse
	GSocket()->Address("SERVER");
	// créer une socket
	GSocket()->Socket2("CLIENT", AF_INET, SOCK_STREAM, IPPROTO_TCP);
	// créer une adresse
	GSocket()->Address3("SERVER", AF_INET, "127.0.0.1", 5566);
	// connecter la socket à l'adresse
	GSocket()->Connect("CLIENT", "SERVER");
	// Lire un message du serveur
	GSocket()->Read("CLIENT", lMessage, 255);
	GConsole()->Print("[ SERVER ] Read: %s\n", lMessage);
	// Envoyer un message au serveur
	GSocket()->Write("CLIENT", "Je communique avec le serveur", 0);
	// Fermer une socket
	GSocket()->Close("CLIENT");
	// Libérer une socket
	GSocket()->Clean2("CLIENT");
	// Libéree une adresse
	GSocket()->Clean3("SERVER");
#endif
}
//===============================================
