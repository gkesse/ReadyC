//===============================================
#include "GProcessDbusClient.h"
#include "GDBus.h"
#include "GConsole.h"
#include "GLog.h"
//===============================================
static GProcessO* m_GProcessDbusClientO = 0;
//===============================================
static void GProcessDbusClient_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessDbusClient_New() {
	GProcessO* lParent = GProcess_New();
	GProcessDbusClientO* lChild = (GProcessDbusClientO*)malloc(sizeof(GProcessDbusClientO));

	lChild->m_parent = lParent;

	lParent->m_child = lChild;
	lParent->Delete = GProcessDbusClient_Delete;
	lParent->Run = GProcessDbusClient_Run;
	return lParent;
}
//===============================================
void GProcessDbusClient_Delete() {
	GProcess_Delete(m_GProcessDbusClientO);
	m_GProcessDbusClientO = 0;
}
//===============================================
GProcessO* GProcessDbusClient() {
	if(m_GProcessDbusClientO == 0) {
		m_GProcessDbusClientO = GProcessDbusClient_New();
	}
	return m_GProcessDbusClientO;
}
//===============================================
#if defined(__unix)
const char* G_INTERFACE_NAME_2 = "in.readydev.dbus_service";
const char* G_SERVER_BUS_NAME = "in.readydev.add_server";
const char* G_CLIENT_BUS_NAME = "in.readydev.add_client";
const char* G_SERVER_OBJECT_PATH_NAME = "/in/readydev/adder";
const char* G_CLIENT_OBJECT_PATH_NAME = "/in/readydev/add_client";
const char* G_METHOD_NAME_2 = "add_numbers";
#endif
//===============================================
static void GProcessDbusClient_Run(int argc, char** argv) {
#if defined(_GUSE_DBUS_ON_)
    //GLog()->Write("#================================================");
    //GLog()->Write("# Execution de la fonction : GProcessDbusClient_Run");
    //GLog()->Write("#================================================");
	GDBus()->MallocError("CLIENT");
	GDBus()->Init("CLIENT");
	GDBus()->Connection("CLIENT", "CLIENT", DBUS_BUS_SESSION);

	while(1) {
		int lRes = GDBus()->RequestName("CLIENT", "CLIENT", G_CLIENT_BUS_NAME, 0);
		if (lRes == DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER) break;
		if (lRes == DBUS_REQUEST_NAME_REPLY_IN_QUEUE) continue;
	}

	char* lAnswer;
	char* lReply;
	GDBus()->NewMethodCall("CLIENT", G_SERVER_BUS_NAME, G_SERVER_OBJECT_PATH_NAME, G_INTERFACE_NAME_2, G_METHOD_NAME_2);
	GDBus()->IterInitAppend("CLIENT", "CLIENT");
	GDBus()->IterInitAppendBasic("CLIENT", DBUS_TYPE_STRING, &lAnswer);
	GDBus()->SendWithReply("CLIENT", "CLIENT", "CLIENT", -1);
	GDBus()->FFlushConnection("CLIENT");
	GDBus()->UnrefMessage("CLIENT");
	GDBus()->PendingCallBlock("CLIENT");
	GDBus()->PendingCallStealReply("CLIENT");
	GDBus()->GetMessageArgs("CLIENT", "CLIENT", DBUS_TYPE_STRING, &lReply);
	GDBus()->UnrefMessage("CLIENT");
	//GDBus()->ReleaseName("CLIENT", G_CLIENT_BUS_NAME, "CLIENT");
#endif
}
//===============================================
