//===============================================
#ifndef _GDBus_
#define _GDBus_
//===============================================
#include "GInclude.h"
#include "GMap.h"
//===============================================
typedef struct _GDBusO GDBusO;
typedef struct _GMapO_GDBus_GCHAR_PTR_GDBUSCONNECTION_PTR GMapO_GDBus_GCHAR_PTR_GDBUSCONNECTION_PTR;
typedef struct _GMapO_GDBus_GCHAR_PTR_GDBUSMESSAGE_PTR GMapO_GDBus_GCHAR_PTR_GDBUSMESSAGE_PTR;
typedef struct _GMapO_GDBus_GCHAR_PTR_GDBUSERROR_PTR GMapO_GDBus_GCHAR_PTR_GDBUSERROR_PTR;
typedef struct _GMapO_GDBus_GCHAR_PTR_GDBUSPENDINGCALL_PTR GMapO_GDBus_GCHAR_PTR_GDBUSPENDINGCALL_PTR;
typedef struct _GMapO_GDBus_GCHAR_PTR_GDBUSMESSAGEITR_PTR GMapO_GDBus_GCHAR_PTR_GDBUSMESSAGEITR_PTR;
//===============================================
struct _GDBusO {
	void (*Delete)();
	void (*MallocError)(char* errorName);
	void (*MallocIterator)(char* iteratorName);
	void (*Init)(char* errorName);
	void (*Connection)(char* connName, char* errorName, int type);
	int (*RequestName)(char* connName, char* errorName, const char* serverName, int flags);
	void (*ReadWriteDispatch)(char* connName, int timeout);
	int (*PopMessage)(char* connName, char* messageName);
	int (*IsMethodCall)(char* messageName, const char* interfaceName, const char* methodName);
	void (*NewMethodCall)(char* requestName, const char* serverName, const char* objectName, const char* interfaceName, const char* methodName);
	void (*GetMessageArgs)(char* messageName, char* errorName, int type, char** message);
	void (*NewMethodReturn)(char* messageName, char* replyName);
	void (*IterInitAppend)(char* replyName, char* iteratorName);
	void (*IterInitAppendBasic)(char* iteratorName, int type, char** message);
	void (*SendConnection)(char* connName, char* sendName);
	void (*SendWithReply)(char* connName, char* sendName, char* pendingName, int timeout);
	void (*PendingCallBlock)(char* pendingName);
	void (*PendingCallStealReply)(char* pendingName);
	void (*FFlushConnection)(char* connName);
	void (*UnrefMessage)(char* replyName);
	void (*UnrefPendingCall)(char* pendingName);
	void (*NewError)(char* messageName, char* errorName, char* type, char* message);
	void (*ReleaseName)(char* connName, char* busName, char* errorName);
	void (*FreeError)(char* errorName);
#if defined(__unix)
	GMapO(GDBus_GCHAR_PTR_GDBUSCONNECTION_PTR)* m_connMap;
	GMapO(GDBus_GCHAR_PTR_GDBUSMESSAGE_PTR)* m_messageMap;
	GMapO(GDBus_GCHAR_PTR_GDBUSERROR_PTR)* m_errorMap;
	GMapO(GDBus_GCHAR_PTR_GDBUSPENDINGCALL_PTR)* m_pendingMap;
	GMapO(GDBus_GCHAR_PTR_GDBUSMESSAGEITR_PTR)* m_iteratorMap;
#endif
};
//===============================================
GDBusO* GDBus_New();
void GDBus_Delete();
GDBusO* GDBus();
//===============================================
#endif
//===============================================
