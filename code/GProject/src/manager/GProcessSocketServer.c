//===============================================
#include "GProcessSocketServer.h"
#include "GSocket.h"
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
    GSocket()->Start(2, 0);
    GSocket()->Status();
    GSocket()->Major();
    GSocket()->Minor();
    GSocket()->MajorMax();
    GSocket()->MinorMax();
    GSocket()->Socket(AF_INET, SOCK_STREAM, 0);
    GSocket()->Address2(AF_INET, INADDR_ANY, 5566);
    GSocket()->Bind();
    GSocket()->Listen(5);
    while(1) {
    	GSocket()->Accept();
    	GSocket()->SocketName();
    	GSocket()->IpAddress();
    	GSocket()->Port();
    	GSocket()->Send();
    	GSocket()->Close2();
    }
    GSocket()->Close();
    GSocket()->Clean();
}
//===============================================
