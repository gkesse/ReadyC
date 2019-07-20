//===============================================
#include "GDBus.h"
#include "GConsole.h"
//===============================================
#if defined(__unix)
typedef char* GCHAR_PTR;
typedef DBusConnection* GDBusCONNECTION_PTR;
//===============================================
GDECLARE_MAP(GCHAR_PTR, GDBusCONNECTION_PTR, GDBus_GCHAR_PTR_GDBusCONNECTION_PTR)
GDEFINE_MAP(GCHAR_PTR, GDBusCONNECTION_PTR, GDBus_GCHAR_PTR_GDBusCONNECTION_PTR)
#endif
//===============================================
static GDBusO* m_GDBusO = 0;
//===============================================
static void GDBus_Init();
static void GDBus_Connection(char* connName, int type);
//===============================================
static int GDBus_MapEqual(char* key1, char* key2);
//===============================================
GDBusO* GDBus_New() {
    GDBusO* lObj = (GDBusO*)malloc(sizeof(GDBusO));

    lObj->m_connMap = GMap_New_GDBus_GCHAR_PTR_GDBusCONNECTION_PTR();

    lObj->Delete = GDBus_Delete;
    lObj->Init = GDBus_Init;
    lObj->Connection = GDBus_Connection;
    return lObj;
}
//===============================================
void GDBus_Delete() {
    GDBusO* lObj = GDBus();
    if(lObj != 0) {
        free(lObj);
    }
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
static void GDBus_Init() {
	DBusError lError;
	dbus_error_init(&lError);
	int lOk = dbus_error_is_set (&lError);
	if(lOk == 0) {GConsole()->Print("[ GDBus ] Error GDBus_Init: %s\n", lError.message); dbus_error_free (&lError); exit(0);}
}
//===============================================
static void GDBus_Connection(char* connName, int type) {
	DBusError lError;
	DBusConnection* lConn = dbus_bus_get(type, &lError);
	int lOk = dbus_error_is_set (&lError);
	if(lOk == 0) {GConsole()->Print("[ GDBus ] Error GDBus_Connection: %s\n", lError.message); dbus_error_free (&lError); exit(0);}
	if(lConn == 0) {GConsole()->Print("[ GDBus ] Error GDBus_Connection\n"); exit(0);}
	GMapO(GDBus_GCHAR_PTR_GDBusCONNECTION_PTR)* lConnMap = m_GDBusO->m_connMap;
	lConnMap->SetData(lConnMap, connName, lConn, GDBus_MapEqual);
}
//===============================================
static void GDBus_RequestName(char* connName, char* serverName, int flags) {
	GMapO(GDBus_GCHAR_PTR_GDBusCONNECTION_PTR)* lConnMap = m_GDBusO->m_connMap;
	DBusConnection* lConn = lConnMap->GetData(lConnMap, connName, GDBus_MapEqual);
	DBusError lError;
    int lRes = dbus_bus_request_name (lConn, serverName, flags, &lError);
	int lOk = dbus_error_is_set (&lError);
	if(lOk == 0) {GConsole()->Print("[ GDBus ] Error GDBus_RequestName: %s\n", lError.message); dbus_error_free (&lError); exit(0);}
	if(lRes != DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER) {GConsole()->Print("[ GDBus ] Error GDBus_RequestName\n"); exit(0);}
}
//===============================================
static void GDBus_ReadWriteDispatch(char* connName, int timeout) {
	GMapO(GDBus_GCHAR_PTR_GDBusCONNECTION_PTR)* lConnMap = m_GDBusO->m_connMap;
	DBusConnection* lConn = lConnMap->GetData(lConnMap, connName, GDBus_MapEqual);
    int lRes = dbus_connection_read_write_dispatch (lConn, timeout);
	if(lRes == 0) {GConsole()->Print("[ GDBus ] Error GDBus_RequestName\n"); exit(0);}
}
//===============================================
static int GDBus_PopMessage(char* connName) {
	GMapO(GDBus_GCHAR_PTR_GDBusCONNECTION_PTR)* lConnMap = m_GDBusO->m_connMap;
	DBusConnection* lConn = lConnMap->GetData(lConnMap, connName, GDBus_MapEqual);
    DBusMessage* lMessage = dbus_connection_pop_message (lConn);
	if(lMessage == 0) {GConsole()->Print("[ GDBus ] Warning GDBus_PopMessage\n"); return 0;}
	return 1;
}
//===============================================
static int GDBus_MapEqual(char* key1, char* key2) {
    int lStrcmp = strcmp(key1, key2);
    if(lStrcmp == 0) return TRUE;
    return FALSE;
}
//===============================================
