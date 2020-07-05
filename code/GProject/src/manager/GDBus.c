//===============================================
#include "GDBus.h"
#include "GMap2.h"
//===============================================
#if defined(_GUSE_DBUS_ON_)
//===============================================
GDECLARE_MAP(GDBus, GCHAR_PTR, GVOID_PTR)
GDEFINE_MAP(GDBus, GCHAR_PTR, GVOID_PTR)
//===============================================
static GDBusO* m_GDBusO = 0;
//===============================================
static void GDBus_MallocError(char* errorName);
static void GDBus_MallocIterator(char* iteratorName);
static void GDBus_Init(char* errorName);
static void GDBus_Connection(char* connName, char* errorName, int type);
static int GDBus_RequestName(char* connName, char* errorName, const char* serverName, int flags);
static void GDBus_ReadWriteDispatch(char* connName, int timeout);
static int GDBus_PopMessage(char* connName, char* messageName);
static int GDBus_IsMethodCall(char* messageName, const char* interfaceName, const char* methodName);
static void GDBus_NewMethodCall(char* requestName, const char* serverName, const char* objectName, const char* interfaceName, const char* methodName);
static void GDBus_GetMessageArgs(char* messageName, char* errorName, int type, char** message);
static void GDBus_NewMethodReturn(char* messageName, char* replyName);
static void GDBus_IterInitAppend(char* replyName, char* iteratorName);
static void GDBus_IterInitAppendBasic(char* iteratorName, int type, char** message);
static void GDBus_SendConnection(char* connName, char* sendName);
static void GDBus_SendWithReply(char* connName, char* sendName, char* pendingName, int timeout);
static void GDBus_PendingCallBlock(char* pendingName);
static void GDBus_PendingCallStealReply(char* pendingName);
static void GDBus_FFlushConnection(char* connName);
static void GDBus_UnrefMessage(char* replyName);
static void GDBus_UnrefPendingCall(char* pendingName);
static void GDBus_NewError(char* messageName, char* errorName, char* type, char* message);
static void GDBus_ReleaseName(char* connName, char* busName, char* errorName);
static void GDBus_FreeError(char* errorName);
//===============================================
GDBusO* GDBus_New() {
	GDBusO* lObj = (GDBusO*)malloc(sizeof(GDBusO));

	lObj->m_connMap = GMap_New(GDBus, GCHAR_PTR, GVOID_PTR)();
	lObj->m_messageMap = GMap_New(GDBus, GCHAR_PTR, GVOID_PTR)();
	lObj->m_errorMap = GMap_New(GDBus, GCHAR_PTR, GVOID_PTR)();
	lObj->m_pendingMap = GMap_New(GDBus, GCHAR_PTR, GVOID_PTR)();

	lObj->Delete = GDBus_Delete;
	lObj->MallocError = GDBus_MallocError;
	lObj->MallocIterator = GDBus_MallocIterator;
	lObj->Init = GDBus_Init;
	lObj->Connection = GDBus_Connection;
	lObj->RequestName = GDBus_RequestName;
	lObj->ReadWriteDispatch = GDBus_ReadWriteDispatch;
	lObj->PopMessage = GDBus_PopMessage;
	lObj->IsMethodCall = GDBus_IsMethodCall;
	lObj->NewMethodCall = GDBus_NewMethodCall;
	lObj->GetMessageArgs = GDBus_GetMessageArgs;
	lObj->NewMethodReturn = GDBus_NewMethodReturn;
	lObj->IterInitAppend = GDBus_IterInitAppend;
	lObj->IterInitAppendBasic = GDBus_IterInitAppendBasic;
	lObj->SendConnection = GDBus_SendConnection;
	lObj->SendWithReply = GDBus_SendWithReply;
	lObj->PendingCallBlock = GDBus_PendingCallBlock;
	lObj->PendingCallStealReply = GDBus_PendingCallStealReply;
	lObj->FFlushConnection = GDBus_FFlushConnection;
	lObj->UnrefMessage = GDBus_UnrefMessage;
	lObj->UnrefPendingCall = GDBus_UnrefPendingCall;
	lObj->NewError = GDBus_NewError;
	lObj->ReleaseName= GDBus_ReleaseName;
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
	GMapO(GDBus, GCHAR_PTR, GVOID_PTR)* lErrorMap = m_GDBusO->m_errorMap;
	DBusError* lError = (DBusError*)malloc(sizeof(DBusError));
	if(lError == 0) {printf("[GDBus] Error GDBus_MallocError\n"); exit(0);}
	lErrorMap->SetData(lErrorMap, errorName, lError, GMap_EqualChar);
}
//===============================================
static void GDBus_MallocIterator(char* iteratorName) {
	GMapO(GDBus, GCHAR_PTR, GVOID_PTR)* lIteratorMap = m_GDBusO->m_iteratorMap;
	DBusMessageIter* lIterator = (DBusMessageIter*)malloc(sizeof(DBusMessageIter));
	if(lIterator == 0) {printf("[GDBus] Error GDBus_MallocError\n"); exit(0);}
	lIteratorMap->SetData(lIteratorMap, iteratorName, lIterator, GMap_EqualChar);
}
//===============================================
static void GDBus_Init(char* errorName) {
	GMapO(GDBus, GCHAR_PTR, GVOID_PTR)* lErrorMap = m_GDBusO->m_errorMap;
	DBusError* lError = lErrorMap->GetData(lErrorMap, errorName, GMap_EqualChar);
	dbus_error_init(lError);
	int lOk = dbus_error_is_set (lError);
	if(lOk == 0) {printf("[GDBus] Error GDBus_Init: %s\n", lError->message); GDBus_FreeError(errorName);}
}
//===============================================
static void GDBus_Connection(char* connName, char* errorName, int type) {
	GMapO(GDBus, GCHAR_PTR, GVOID_PTR)* lErrorMap = m_GDBusO->m_errorMap;
	DBusError* lError = lErrorMap->GetData(lErrorMap, errorName, GMap_EqualChar);
	DBusConnection* lConn = dbus_bus_get(type, lError);
	int lOk = dbus_error_is_set (lError);
	if(lOk == 0) {printf("[GDBus] Error GDBus_Connection: %s\n", lError->message); GDBus_FreeError(errorName);}
	if(lConn == 0) {printf("[GDBus] Error GDBus_Connection\n"); exit(0);}
	GMapO(GDBus, GCHAR_PTR, GVOID_PTR)* lConnMap = m_GDBusO->m_connMap;
	lConnMap->SetData(lConnMap, connName, lConn, GMap_EqualChar);
}
//===============================================
static int GDBus_RequestName(char* connName, char* errorName, const char* serverName, int flags) {
	GMapO(GDBus, GCHAR_PTR, GVOID_PTR)* lConnMap = m_GDBusO->m_connMap;
	GMapO(GDBus, GCHAR_PTR, GVOID_PTR)* lErrorMap = m_GDBusO->m_errorMap;
	DBusConnection* lConn = lConnMap->GetData(lConnMap, connName, GMap_EqualChar);
	DBusError* lError = lErrorMap->GetData(lErrorMap, errorName, GMap_EqualChar);
	int lRes = dbus_bus_request_name (lConn, serverName, flags, lError);
	int lOk = dbus_error_is_set (lError);
	if(lOk == 0) {printf("[GDBus] Error GDBus_RequestName: %s\n", lError->message); GDBus_FreeError(errorName);}
	return lRes;
	return 0;
}
//===============================================
static void GDBus_ReadWriteDispatch(char* connName, int timeout) {
	GMapO(GDBus, GCHAR_PTR, GVOID_PTR)* lConnMap = m_GDBusO->m_connMap;
	DBusConnection* lConn = lConnMap->GetData(lConnMap, connName, GMap_EqualChar);
	int lRes = dbus_connection_read_write_dispatch (lConn, timeout);
	if(lRes == 0) {printf("[GDBus] Error GDBus_RequestName\n"); exit(0);}
}
//===============================================
static int GDBus_PopMessage(char* connName, char* messageName) {
	GMapO(GDBus, GCHAR_PTR, GVOID_PTR)* lConnMap = m_GDBusO->m_connMap;
	GMapO(GDBus, GCHAR_PTR, GVOID_PTR)* lMessageMap = m_GDBusO->m_messageMap;
	DBusConnection* lConn = lConnMap->GetData(lConnMap, connName, GMap_EqualChar);
	DBusMessage* lMessage = dbus_connection_pop_message (lConn);
	if(lMessage == 0) {printf("[GDBus] Warning GDBus_PopMessage\n"); return 0;}
	lMessageMap->SetData(lMessageMap, messageName, lMessage, GMap_EqualChar);
	return 1;
	return 0;
}
//===============================================
static int GDBus_IsMethodCall(char* messageName, const char* interfaceName, const char* methodName) {
	GMapO(GDBus, GCHAR_PTR, GVOID_PTR)* lMessageMap = m_GDBusO->m_messageMap;
	DBusMessage* lMessage = lMessageMap->GetData(lMessageMap, messageName, GMap_EqualChar);
	int lRes = dbus_message_is_method_call (lMessage, interfaceName, methodName);
	return lRes;
	return 0;
}
//===============================================
static void GDBus_NewMethodCall(char* requestName, const char* serverName, const char* objectName, const char* interfaceName, const char* methodName) {
	GMapO(GDBus, GCHAR_PTR, GVOID_PTR)* lMessageMap = m_GDBusO->m_messageMap;
	DBusMessage* lRequest = dbus_message_new_method_call (serverName, objectName, interfaceName, methodName);
	if(lRequest == 0) {printf("[GDBus] Error GDBus_NewMethodCall\n"); exit(0);}
	lMessageMap->SetData(lMessageMap, requestName, lRequest, GMap_EqualChar);
}
//===============================================
static void GDBus_GetMessageArgs(char* messageName, char* errorName, int type, char** message) {
	GMapO(GDBus, GCHAR_PTR, GVOID_PTR)* lMessageMap = m_GDBusO->m_messageMap;
	GMapO(GDBus, GCHAR_PTR, GVOID_PTR)* lErrorMap = m_GDBusO->m_errorMap;
	DBusMessage* lMessage = lMessageMap->GetData(lMessageMap, messageName, GMap_EqualChar);
	DBusError* lError = lErrorMap->GetData(lErrorMap, errorName, GMap_EqualChar);
	int lRes = dbus_message_get_args(lMessage, lError, type, message, DBUS_TYPE_INVALID);
	int lOk = dbus_error_is_set (lError);
	if(lOk == 0) {printf("[GDBus] Error GDBus_GetMessageArgs: %s\n", lError->message); GDBus_FreeError(errorName); exit(0);}
	if(lRes == 0) {printf("[GDBus] Error GDBus_GetMessageArgs\n"); exit(0);}
}
//===============================================
static void GDBus_NewMethodReturn(char* messageName, char* replyName) {
	GMapO(GDBus, GCHAR_PTR, GVOID_PTR)* lMessageMap = m_GDBusO->m_messageMap;
	DBusMessage* lMessage = lMessageMap->GetData(lMessageMap, messageName, GMap_EqualChar);
	DBusMessage* lReply = dbus_message_new_method_return (lMessage);
	if(lReply == 0) {printf("[GDBus] Error GDBus_NewMethodReturn\n"); exit(0);}
	lMessageMap->SetData(lMessageMap, replyName, lReply, GMap_EqualChar);
}
//===============================================
static void GDBus_IterInitAppend(char* replyName, char* iteratorName) {
	GMapO(GDBus, GCHAR_PTR, GVOID_PTR)* lMessageMap = m_GDBusO->m_messageMap;
	GMapO(GDBus, GCHAR_PTR, GVOID_PTR)* lIteratorMap = m_GDBusO->m_iteratorMap;
	DBusMessage* lReply = lMessageMap->GetData(lMessageMap, replyName, GMap_EqualChar);
	DBusMessageIter* lIterator = lIteratorMap->GetData(lIteratorMap, iteratorName, GMap_EqualChar);
	dbus_message_iter_init_append (lReply, lIterator);
}
//===============================================
static void GDBus_IterInitAppendBasic(char* iteratorName, int type, char** message) {
	GMapO(GDBus, GCHAR_PTR, GVOID_PTR)* lIteratorMap = m_GDBusO->m_iteratorMap;
	DBusMessageIter* lIterator = lIteratorMap->GetData(lIteratorMap, iteratorName, GMap_EqualChar);
	int lRes = dbus_message_iter_append_basic (lIterator, type, message);
	if(lRes == 0) {printf("[GDBus] Error GDBus_IterInitAppendBasic\n"); exit(0);}
}
//===============================================
static void GDBus_SendConnection(char* connName, char* sendName) {
	GMapO(GDBus, GCHAR_PTR, GVOID_PTR)* lConnMap = m_GDBusO->m_connMap;
	GMapO(GDBus, GCHAR_PTR, GVOID_PTR)* lMessageMap = m_GDBusO->m_messageMap;
	DBusConnection* lConn = lConnMap->GetData(lConnMap, connName, GMap_EqualChar);
	DBusMessage* lSend = lMessageMap->GetData(lMessageMap, sendName, GMap_EqualChar);
	int lRes = dbus_connection_send (lConn, lSend, 0);
	if(lRes == 0) {printf("[GDBus] Error GDBus_Send\n"); exit(0);}
}
//===============================================
static void GDBus_SendWithReply(char* connName, char* sendName, char* pendingName, int timeout) {
	GMapO(GDBus, GCHAR_PTR, GVOID_PTR)* lConnMap = m_GDBusO->m_connMap;
	GMapO(GDBus, GCHAR_PTR, GVOID_PTR)* lMessageMap = m_GDBusO->m_messageMap;
	GMapO(GDBus, GCHAR_PTR, GVOID_PTR)* lPendingMap = m_GDBusO->m_pendingMap;
	DBusConnection* lConn = lConnMap->GetData(lConnMap, connName, GMap_EqualChar);
	DBusMessage* lSend = lMessageMap->GetData(lMessageMap, sendName, GMap_EqualChar);
	DBusPendingCall* lPendingCall;
	int lRes = dbus_connection_send_with_reply (lConn, lSend, &lPendingCall, timeout);
	if(lRes == 0) {printf("[GDBus] Error GDBus_SendWithReply\n"); exit(0);}
	if(lPendingCall == 0) {printf("[GDBus] Error GDBus_SendWithReply\n"); exit(0);}
	lPendingMap->SetData(lPendingMap, pendingName, lPendingCall, GMap_EqualChar);
}
//===============================================
static void GDBus_PendingCallBlock(char* pendingName) {
	GMapO(GDBus, GCHAR_PTR, GVOID_PTR)* lPendingMap = m_GDBusO->m_pendingMap;
	DBusPendingCall* lPendingCall = lPendingMap->GetData(lPendingMap, pendingName, GMap_EqualChar);
    dbus_pending_call_block (lPendingCall);
}
//===============================================
static void GDBus_PendingCallStealReply(char* pendingName) {
	GMapO(GDBus, GCHAR_PTR, GVOID_PTR)* lPendingMap = m_GDBusO->m_pendingMap;
	DBusPendingCall* lPendingCall = lPendingMap->GetData(lPendingMap, pendingName, GMap_EqualChar);
    DBusMessage* lReply = dbus_pending_call_steal_reply (lPendingCall);
	if(lReply == 0) {printf("[GDBus] Error GDBus_PendingCallStealReply\n"); exit(0);}
}
//===============================================
static void GDBus_FFlushConnection(char* connName) {
	GMapO(GDBus, GCHAR_PTR, GVOID_PTR)* lConnMap = m_GDBusO->m_connMap;
	DBusConnection* lConn = lConnMap->GetData(lConnMap, connName, GMap_EqualChar);
	dbus_connection_flush(lConn);
}
//===============================================
static void GDBus_UnrefMessage(char* replyName) {
	GMapO(GDBus, GCHAR_PTR, GVOID_PTR)* lMessageMap = m_GDBusO->m_messageMap;
	DBusMessage* lReply = lMessageMap->GetData(lMessageMap, replyName, GMap_EqualChar);
	dbus_message_unref (lReply);
}
//===============================================
static void GDBus_UnrefPendingCall(char* pendingName) {
	GMapO(GDBus, GCHAR_PTR, GVOID_PTR)* lPendingMap = m_GDBusO->m_pendingMap;
	DBusPendingCall* lPendingCall = lPendingMap->GetData(lPendingMap, pendingName, GMap_EqualChar);
	dbus_pending_call_unref(lPendingCall);
}
//===============================================
static void GDBus_NewError(char* messageName, char* errorName, char* type, char* message) {
	GMapO(GDBus, GCHAR_PTR, GVOID_PTR)* lMessageMap = m_GDBusO->m_messageMap;
	DBusMessage* lMessage = lMessageMap->GetData(lMessageMap, messageName, GMap_EqualChar);
	DBusMessage* lError = dbus_message_new_error (lMessage, type, message);
	if(lError == 0) {printf("[GDBus] Error GDBus_NewError\n"); exit(0);}
	lMessageMap->SetData(lMessageMap, errorName, lError, GMap_EqualChar);
}
//===============================================
static void GDBus_ReleaseName(char* connName, char* busName, char* errorName) {
	GMapO(GDBus, GCHAR_PTR, GVOID_PTR)* lConnMap = m_GDBusO->m_connMap;
	GMapO(GDBus, GCHAR_PTR, GVOID_PTR)* lErrorMap = m_GDBusO->m_errorMap;
	DBusConnection* lConn = lConnMap->GetData(lConnMap, connName, GMap_EqualChar);
	DBusError* lError = lErrorMap->GetData(lErrorMap, errorName, GMap_EqualChar);
	int lRes = dbus_bus_release_name(lConn, busName, lError);
	int lOk = dbus_error_is_set (lError);
	if(lOk == 0) {printf("[GDBus] Error GDBus_ReleaseName: %s\n", lError->message); GDBus_FreeError(errorName); exit(0);}
	if(lRes == 0) {printf("[GDBus] Error GDBus_ReleaseName\n"); exit(0);}
}
//===============================================
static void GDBus_FreeError(char* errorName) {
	GMapO(GDBus, GCHAR_PTR, GVOID_PTR)* lErrorMap = m_GDBusO->m_errorMap;
	DBusError* lError = lErrorMap->GetData(lErrorMap, errorName, GMap_EqualChar);
	dbus_error_free (lError);
	free(lError);
}
//===============================================
#endif
//===============================================
