//===============================================
#include "GDBus.h"
#include "GDebug.h"
//===============================================
#if defined(_GUSE_DBUS_ON_)
//===============================================
static GDBusO* m_GDBusO = 0;
//===============================================
static void GDBus_Test(int argc, char** argv);
//===============================================
static void GDBus_SendSignal(int argc, char** argv);
//===============================================
GDBusO* GDBus_New() {
	GDebug()->Write(1, __FUNCTION__, _EOA_);
	GDBusO* lObj = (GDBusO*)malloc(sizeof(GDBusO));
	lObj->Delete = GDBus_Delete;
	lObj->Test = GDBus_Test;
	return lObj;
}
//===============================================
void GDBus_Delete() {
	GDebug()->Write(1, __FUNCTION__, _EOA_);
	GDBusO* lObj = GDBus();
	free(lObj);
	m_GDBusO = 0;
}
//===============================================
GDBusO* GDBus() {
	if(m_GDBusO == 0) {
		m_GDBusO = GDBus_New();
	}
	return m_GDBusO;
}
//===============================================
static void GDBus_Test(int argc, char** argv) {
	GDebug()->Write(1, __FUNCTION__, _EOA_);
	GDBus_SendSignal(argc, argv);
}
//===============================================
static void GDBus_SendSignal(int argc, char** argv) {
	GDebug()->Write(1, __FUNCTION__, _EOA_);
	if(argc < 4) {printf("erreur arguments\n"); return;}
	char* lData = argv[3];
	DBusError lError;
	dbus_error_init(&lError);
	DBusConnection* lConnect = dbus_bus_get(DBUS_BUS_SESSION, &lError);
	if(dbus_error_is_set(&lError)) {printf("erreur connexion: %s\n", lError.message); dbus_error_free(&lError); exit(0);}
	if(lConnect == 0) {printf("erreur connexion\n"); exit(1);}
	int lRes = dbus_bus_request_name(lConnect, "test.method.server", DBUS_NAME_FLAG_REPLACE_EXISTING, &lError);
	if(dbus_error_is_set(&lError)) {printf("erreur nom connexion: %s\n", lError.message); dbus_error_free(&lError); exit(0);}
	if(lRes != DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER) {printf("erreur nom connexion\n"); exit(1);}

	DBusMessage* lMessage = dbus_message_new_signal(
			"/test/signal/Object", // object name of the signal
			"test.signal.Type", // interface name of the signal
			"Test"); // name of the signal

	if(lMessage == 0) {printf("erreur message: %s\n", lError.message); dbus_error_free(&lError); exit(0);}

	DBusMessageIter lArgs;
	dbus_message_iter_init_append(lMessage, &lArgs);
	lRes = dbus_message_iter_append_basic(&lArgs, DBUS_TYPE_STRING, &lData);
	if (lRes == 0) {printf("erreur parametrage message\n");	exit(0);}
	uint lSerial;
	lRes = dbus_connection_send(lConnect, lMessage, &lSerial);
	if (lRes == 0) {printf("erreur envoi message\n"); exit(0);}

	dbus_connection_flush(lConnect);
	dbus_message_unref(lMessage);
	dbus_connection_close(lConnect) ;
}
//===============================================
#endif
//===============================================
