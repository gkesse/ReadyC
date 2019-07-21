//===============================================
#include "GDBus.h"
#include "GConsole.h"
//===============================================
#if defined(__unix)
typedef char* GCHAR_PTR;
typedef DBusConnection* GDBUSCONNECTION_PTR;
typedef DBusMessage* GDBUSMESSAGE_PTR;
typedef DBusError* GDBUSERROR_PTR;
typedef DBusPendingCall* GDBUSPENDINGCALL_PTR;
//===============================================
GDECLARE_MAP(GCHAR_PTR, GDBUSCONNECTION_PTR, GDBus_GCHAR_PTR_GDBUSCONNECTION_PTR)
GDEFINE_MAP(GCHAR_PTR, GDBUSCONNECTION_PTR, GDBus_GCHAR_PTR_GDBUSCONNECTION_PTR)
//===============================================
GDECLARE_MAP(GCHAR_PTR, GDBUSMESSAGE_PTR, GDBus_GCHAR_PTR_GDBUSMESSAGE_PTR)
GDEFINE_MAP(GCHAR_PTR, GDBUSMESSAGE_PTR, GDBus_GCHAR_PTR_GDBUSMESSAGE_PTR)
//===============================================
GDECLARE_MAP(GCHAR_PTR, GDBUSERROR_PTR, GDBus_GCHAR_PTR_GDBUSERROR_PTR)
GDEFINE_MAP(GCHAR_PTR, GDBUSERROR_PTR, GDBus_GCHAR_PTR_GDBUSERROR_PTR)
//===============================================
GDECLARE_MAP(GCHAR_PTR, GDBUSPENDINGCALL_PTR, GDBus_GCHAR_PTR_GDBUSPENDINGCALL_PTR)
GDEFINE_MAP(GCHAR_PTR, GDBUSPENDINGCALL_PTR, GDBus_GCHAR_PTR_GDBUSPENDINGCALL_PTR)
#endif
//===============================================
static GDBusO* m_GDBusO = 0;
//===============================================
static void GDBus_MallocError(char* errorName);
static void GDBus_Init(char* errorName);
static void GDBus_Connection(char* connName, char* errorName, int type);
static void GDBus_RequestName(char* connName, char* errorName, char* serverName, int flags);
static void GDBus_ReadWriteDispatch(char* connName, int timeout);
static int GDBus_PopMessage(char* connName, char* messageName);
static int GDBus_IsMathodCall(char* messageName, char* interface, char* method);
static void GDBus_GetArgs(char* messageName, char* errorName, int type, char** message);
static void GDBus_NewMethodReturn(char* messageName, char* replyName);
static void GDBus_IterInitAppend(char* replyName, int type, char** message);
static void GDBus_Send(char* connName, char* sendName);
static void GDBus_SendWithReply(char* connName, char* sendName, char* pendingName, int timeout);
static void GDBus_FFlush(char* connName);
static void GDBus_UnrefMessage(char* replyName);
static void GDBus_UnrefPendingCall(char* pendingName);
static void GDBus_NewError(char* messageName, char* message);
static void GDBus_ReleaseBus(char* connName, char* busName, char* errorName);
static void GDBus_FreeError(char* errorName);
//===============================================
static int GDBus_MapEqual(char* key1, char* key2);
//===============================================
GDBusO* GDBus_New() {
    GDBusO* lObj = (GDBusO*)malloc(sizeof(GDBusO));

    lObj->m_connMap = GMap_New_GDBus_GCHAR_PTR_GDBUSCONNECTION_PTR();
    lObj->m_messageMap = GMap_New_GDBus_GCHAR_PTR_GDBUSMESSAGE_PTR();
    lObj->m_errorMap = GMap_New_GDBus_GCHAR_PTR_GDBUSERROR_PTR();
    lObj->m_pendingMap = GMap_New_GDBus_GCHAR_PTR_GDBUSPENDINGCALL_PTR();

    lObj->Delete = GDBus_Delete;
    lObj->MallocError = GDBus_MallocError;
    lObj->Init = GDBus_Init;
    lObj->Connection = GDBus_Connection;
    lObj->RequestName = GDBus_RequestName;
    lObj->ReadWriteDispatch = GDBus_ReadWriteDispatch;
    lObj->PopMessage = GDBus_PopMessage;
    lObj->IsMathodCall = GDBus_IsMathodCall;
    lObj->GetArgs = GDBus_GetArgs;
    lObj->NewMethodReturn = GDBus_NewMethodReturn;
    lObj->IterInitAppend = GDBus_IterInitAppend;
    lObj->Send = GDBus_Send;
    lObj->SendWithReply = GDBus_SendWithReply;
    lObj->FFlush = GDBus_FFlush;
    lObj->UnrefMessage = GDBus_UnrefMessage;
    lObj->UnrefPendingCall = GDBus_UnrefPendingCall;
    lObj->NewError = GDBus_NewError;
    lObj->ReleaseBus= GDBus_ReleaseBus;
    lObj->FreeError = GDBus_FreeError;
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
static void GDBus_MallocError(char* errorName) {
	GMapO(GDBus_GCHAR_PTR_GDBUSERROR_PTR)* lErrorMap = m_GDBusO->m_errorMap;
	DBusError* lError = (DBusError*)malloc(sizeof(DBusError));
	if(lError == 0) {GConsole()->Print("[ GDBus ] Error GDBus_MallocError\n"); exit(0);}
	lErrorMap->SetData(lErrorMap, errorName, lError, GDBus_MapEqual);
}
//===============================================
static void GDBus_Init(char* errorName) {
	GMapO(GDBus_GCHAR_PTR_GDBUSERROR_PTR)* lErrorMap = m_GDBusO->m_errorMap;
	DBusError* lError = lErrorMap->GetData(lErrorMap, errorName, GDBus_MapEqual);
	dbus_error_init(lError);
	int lOk = dbus_error_is_set (lError);
	if(lOk == 0) {GConsole()->Print("[ GDBus ] Error GDBus_Init: %s\n", lError->message); GDBus_FreeError(errorName); exit(0);}
}
//===============================================
static void GDBus_Connection(char* connName, char* errorName, int type) {
	GMapO(GDBus_GCHAR_PTR_GDBUSERROR_PTR)* lErrorMap = m_GDBusO->m_errorMap;
	DBusError* lError = lErrorMap->GetData(lErrorMap, errorName, GDBus_MapEqual);
	DBusConnection* lConn = dbus_bus_get(type, lError);
	int lOk = dbus_error_is_set (lError);
	if(lOk == 0) {GConsole()->Print("[ GDBus ] Error GDBus_Connection: %s\n", lError->message); GDBus_FreeError(errorName); exit(0);}
	if(lConn == 0) {GConsole()->Print("[ GDBus ] Error GDBus_Connection\n"); exit(0);}
	GMapO(GDBus_GCHAR_PTR_GDBUSCONNECTION_PTR)* lConnMap = m_GDBusO->m_connMap;
	lConnMap->SetData(lConnMap, connName, lConn, GDBus_MapEqual);
}
//===============================================
static void GDBus_RequestName(char* connName, char* errorName, char* serverName, int flags) {
	GMapO(GDBus_GCHAR_PTR_GDBUSCONNECTION_PTR)* lConnMap = m_GDBusO->m_connMap;
	GMapO(GDBus_GCHAR_PTR_GDBUSERROR_PTR)* lErrorMap = m_GDBusO->m_errorMap;
	DBusConnection* lConn = lConnMap->GetData(lConnMap, connName, GDBus_MapEqual);
	DBusError* lError = lErrorMap->GetData(lErrorMap, errorName, GDBus_MapEqual);
    int lRes = dbus_bus_request_name (lConn, serverName, flags, lError);
	int lOk = dbus_error_is_set (lError);
	if(lOk == 0) {GConsole()->Print("[ GDBus ] Error GDBus_RequestName: %s\n", lError->message); GDBus_FreeError(errorName); exit(0);}
	if(lRes != DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER) {GConsole()->Print("[ GDBus ] Error GDBus_RequestName\n"); exit(0);}
}
//===============================================
static void GDBus_ReadWriteDispatch(char* connName, int timeout) {
	GMapO(GDBus_GCHAR_PTR_GDBUSCONNECTION_PTR)* lConnMap = m_GDBusO->m_connMap;
	DBusConnection* lConn = lConnMap->GetData(lConnMap, connName, GDBus_MapEqual);
    int lRes = dbus_connection_read_write_dispatch (lConn, timeout);
	if(lRes == 0) {GConsole()->Print("[ GDBus ] Error GDBus_RequestName\n"); exit(0);}
}
//===============================================
static int GDBus_PopMessage(char* connName, char* messageName) {
	GMapO(GDBus_GCHAR_PTR_GDBUSCONNECTION_PTR)* lConnMap = m_GDBusO->m_connMap;
	GMapO(GDBus_GCHAR_PTR_GDBUSMESSAGE_PTR)* lMessageMap = m_GDBusO->m_messageMap;
	DBusConnection* lConn = lConnMap->GetData(lConnMap, connName, GDBus_MapEqual);
    DBusMessage* lMessage = dbus_connection_pop_message (lConn);
	if(lMessage == 0) {GConsole()->Print("[ GDBus ] Warning GDBus_PopMessage\n"); return 0;}
	lMessageMap->SetData(lMessageMap, messageName, lMessage, GDBus_MapEqual);
	return 1;
}
//===============================================
static int GDBus_IsMathodCall(char* messageName, char* interface, char* method) {
	GMapO(GDBus_GCHAR_PTR_GDBUSMESSAGE_PTR)* lMessageMap = m_GDBusO->m_messageMap;
	DBusMessage* lMessage = lMessageMap->GetData(lMessageMap, messageName, GDBus_MapEqual);
    int lRes = dbus_message_is_method_call (lMessage, interface, method);
	return lRes;
}
//===============================================
static void GDBus_GetArgs(char* messageName, char* errorName, int type, char** message) {
	GMapO(GDBus_GCHAR_PTR_GDBUSMESSAGE_PTR)* lMessageMap = m_GDBusO->m_messageMap;
	GMapO(GDBus_GCHAR_PTR_GDBUSERROR_PTR)* lErrorMap = m_GDBusO->m_errorMap;
	DBusMessage* lMessage = lMessageMap->GetData(lMessageMap, messageName, GDBus_MapEqual);
	DBusError* lError = lErrorMap->GetData(lErrorMap, errorName, GDBus_MapEqual);
	int lRes = dbus_message_get_args(lMessage, lError, type, message, DBUS_TYPE_INVALID);
	int lOk = dbus_error_is_set (lError);
	if(lOk == 0) {GConsole()->Print("[ GDBus ] Error GDBus_GetArgs: %s\n", lError->message); GDBus_FreeError(errorName); exit(0);}
	if(lRes == 0) {GConsole()->Print("[ GDBus ] Error GDBus_GetArgs\n"); exit(0);}
}
//===============================================
static void GDBus_NewMethodReturn(char* messageName, char* replyName) {
	GMapO(GDBus_GCHAR_PTR_GDBUSMESSAGE_PTR)* lMessageMap = m_GDBusO->m_messageMap;
	DBusMessage* lMessage = lMessageMap->GetData(lMessageMap, messageName, GDBus_MapEqual);
    DBusMessage* lReply = dbus_message_new_method_return (lMessage);
	if(lReply == 0) {GConsole()->Print("[ GDBus ] Error GDBus_NewMethodReturn\n"); exit(0);}
	lMessageMap->SetData(lMessageMap, replyName, lReply, GDBus_MapEqual);
}
//===============================================
static void GDBus_IterInitAppend(char* replyName, int type, char** message) {
	GMapO(GDBus_GCHAR_PTR_GDBUSMESSAGE_PTR)* lMessageMap = m_GDBusO->m_messageMap;
	DBusMessage* lReply = lMessageMap->GetData(lMessageMap, replyName, GDBus_MapEqual);
    DBusMessageIter lIter;
	dbus_message_iter_init_append (lReply, &lIter);
    int lRes = dbus_message_iter_append_basic (&lIter, type, message);
	if(lRes == 0) {GConsole()->Print("[ GDBus ] Error GDBus_IterInitAppend\n"); exit(0);}
}
//===============================================
static void GDBus_Send(char* connName, char* sendName) {
	GMapO(GDBus_GCHAR_PTR_GDBUSCONNECTION_PTR)* lConnMap = m_GDBusO->m_connMap;
	GMapO(GDBus_GCHAR_PTR_GDBUSMESSAGE_PTR)* lMessageMap = m_GDBusO->m_messageMap;
	DBusConnection* lConn = lConnMap->GetData(lConnMap, connName, GDBus_MapEqual);
	DBusMessage* lSend = lMessageMap->GetData(lMessageMap, sendName, GDBus_MapEqual);
    int lRes = dbus_connection_send (lConn, lSend, 0);
	if(lRes == 0) {GConsole()->Print("[ GDBus ] Error GDBus_Send\n"); exit(0);}
}
//===============================================
static void GDBus_SendWithReply(char* connName, char* sendName, char* pendingName, int timeout) {
	GMapO(GDBus_GCHAR_PTR_GDBUSCONNECTION_PTR)* lConnMap = m_GDBusO->m_connMap;
	GMapO(GDBus_GCHAR_PTR_GDBUSMESSAGE_PTR)* lMessageMap = m_GDBusO->m_messageMap;
	GMapO(GDBus_GCHAR_PTR_GDBUSPENDINGCALL_PTR)* lPendingMap = m_GDBusO->m_pendingMap;
	DBusConnection* lConn = lConnMap->GetData(lConnMap, connName, GDBus_MapEqual);
	DBusMessage* lSend = lMessageMap->GetData(lMessageMap, sendName, GDBus_MapEqual);
	DBusPendingCall* lPendingCall;
	int lRes = dbus_connection_send_with_reply (lConn, lSend, &lPendingCall, timeout);
	if(lRes == 0) {GConsole()->Print("[ GDBus ] Error GDBus_SendWithReply\n"); exit(0);}
	if(lPendingCall == 0) {GConsole()->Print("[ GDBus ] Error GDBus_SendWithReply\n"); exit(0);}
	lPendingMap->SetData(lPendingMap, pendingName, lPendingCall, GDBus_MapEqual);
}
//===============================================
static void GDBus_FFlush(char* connName) {
	GMapO(GDBus_GCHAR_PTR_GDBUSCONNECTION_PTR)* lConnMap = m_GDBusO->m_connMap;
	DBusConnection* lConn = lConnMap->GetData(lConnMap, connName, GDBus_MapEqual);
    dbus_connection_flush(lConn);
}
//===============================================
static void GDBus_UnrefMessage(char* replyName) {
	GMapO(GDBus_GCHAR_PTR_GDBUSMESSAGE_PTR)* lMessageMap = m_GDBusO->m_messageMap;
	DBusMessage* lReply = lMessageMap->GetData(lMessageMap, replyName, GDBus_MapEqual);
    dbus_message_unref (lReply);
}
//===============================================
static void GDBus_UnrefPendingCall(char* pendingName) {
	GMapO(GDBus_GCHAR_PTR_GDBUSPENDINGCALL_PTR)* lPendingMap = m_GDBusO->m_pendingMap;
	DBusPendingCall* lPendingCall = lPendingMap->GetData(lPendingMap, pendingName, GDBus_MapEqual);
    dbus_pending_call_unref(lPendingCall);
}
//===============================================
static void GDBus_NewError(char* messageName, char* message) {
	GMapO(GDBus_GCHAR_PTR_GDBUSMESSAGE_PTR)* lMessageMap = m_GDBusO->m_messageMap;
	DBusMessage* lMessage = lMessageMap->GetData(lMessageMap, messageName, GDBus_MapEqual);
    DBusMessage* lError = dbus_message_new_error (lMessage, DBUS_ERROR_FAILED, message);
	if(lError == 0) {GConsole()->Print("[ GDBus ] Error GDBus_NewError\n"); exit(0);}
}
//===============================================
static void GDBus_ReleaseBus(char* connName, char* busName, char* errorName) {
	GMapO(GDBus_GCHAR_PTR_GDBUSCONNECTION_PTR)* lConnMap = m_GDBusO->m_connMap;
	GMapO(GDBus_GCHAR_PTR_GDBUSERROR_PTR)* lErrorMap = m_GDBusO->m_errorMap;
	DBusConnection* lConn = lConnMap->GetData(lConnMap, connName, GDBus_MapEqual);
	DBusError* lError = lErrorMap->GetData(lErrorMap, errorName, GDBus_MapEqual);
    int lRes = dbus_bus_release_name(lConn, busName, lError);
	int lOk = dbus_error_is_set (lError);
	if(lOk == 0) {GConsole()->Print("[ GDBus ] Error GDBus_ReleaseBus: %s\n", lError->message); GDBus_FreeError(errorName); exit(0);}
	if(lRes == 0) {GConsole()->Print("[ GDBus ] Error GDBus_ReleaseBus\n"); exit(0);}
}
//===============================================
static void GDBus_FreeError(char* errorName) {
	GMapO(GDBus_GCHAR_PTR_GDBUSERROR_PTR)* lErrorMap = m_GDBusO->m_errorMap;
	DBusError* lError = lErrorMap->GetData(lErrorMap, errorName, GDBus_MapEqual);
    dbus_error_free (lError);
    free(lError);
}
//===============================================
static int GDBus_MapEqual(char* key1, char* key2) {
    int lStrcmp = strcmp(key1, key2);
    if(lStrcmp == 0) return TRUE;
    return FALSE;
}
//===============================================
