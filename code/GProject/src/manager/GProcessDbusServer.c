//===============================================
#include "GProcessDbusServer.h"
#include "GDBus.h"
#include "GConsole.h"
//===============================================
static GProcessO* m_GProcessDbusServerO = 0;
//===============================================
static void GProcessDbusServer_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessDbusServer_New() {
	GProcessO* lParent = GProcess_New();
	GProcessDbusServerO* lChild = (GProcessDbusServerO*)malloc(sizeof(GProcessDbusServerO));

	lChild->m_parent = lParent;

	lParent->m_child = lChild;
	lParent->Delete = GProcessDbusServer_Delete;
	lParent->Run = GProcessDbusServer_Run;
	return lParent;
}
//===============================================
void GProcessDbusServer_Delete() {
	// Delete All Attributes Before
	GProcess_Delete(m_GProcessDbusServerO);
	m_GProcessDbusServerO = 0;
}
//===============================================
GProcessO* GProcessDbusServer() {
	if(m_GProcessDbusServerO == 0) {
		m_GProcessDbusServerO = GProcessDbusServer_New();
	}
	return m_GProcessDbusServerO;
}
//===============================================
#if defined(__unix)
const char* G_INTERFACE_NAME = "in.readydev.dbus_service";
const char* G_SERVER_NAME = "in.readydev.add_server";
const char* G_OBJECT_PATH_NAME = "/in/readydev/adder";
const char* G_METHOD_NAME = "add_numbers";
#endif
//===============================================
static void GProcessDbusServer_Run(int argc, char** argv) {
#if defined(__unix)
	GDBus()->MallocError("SERVER");

	GDBus()->Init("SERVER");
	GDBus()->Connection("SERVER", "SERVER", DBUS_BUS_SYSTEM);
	GDBus()->RequestName("SERVER", "SERVER", G_SERVER_NAME, DBUS_NAME_FLAG_DO_NOT_QUEUE);

	char* lMessage;
	char lAnswer[64];

	while(1) {
		GDBus()->ReadWriteDispatch("SERVER", -1);
		if(GDBus()->PopMessage("SERVER", "SERVER") == 0) continue;

		if(GDBus()->IsMethodCall("SERVER", G_INTERFACE_NAME, G_METHOD_NAME) != 0) {
			GDBus()->GetMessageArgs("SERVER", "SERVER", DBUS_TYPE_STRING, &lMessage);
			GConsole()->Print("%s", lMessage);

			int lResult = 50 + 30;
			sprintf(lAnswer, "Reponse du serveur: %d", lResult);

			GDBus()->NewMethodReturn("SERVER", "CLIENT");

			char *lAnswerPtr = lAnswer;

			GDBus()->IterInitAppend("CLIENT", "CLIENT");
			GDBus()->IterInitAppendBasic("CLIENT", DBUS_TYPE_STRING, &lAnswerPtr);
			GDBus()->SendConnection("SERVER", "CLIENT");

			GDBus()->FFlushConnection("SERVER");
			GDBus()->UnrefMessage("CLIENT");
		}
		else {
			char lError[] = "Error in input";
			GDBus()->NewError("SERVER", "CLIENT", DBUS_ERROR_FAILED, lError);
			GDBus()->SendConnection("SERVER", "CLIENT");

			GDBus()->FFlushConnection("SERVER");
			GDBus()->UnrefMessage("CLIENT");
		}
	}
#endif
}
//===============================================
