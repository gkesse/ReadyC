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
//===============================================
struct _GDBusO {
	void (*Delete)();
	void (*MallocError)(char* errorName);
	void (*Init)(char* errorName);
	void (*Connection)(char* connName, char* errorName, int type);
	void (*RequestName)(char* connName, char* errorName, char* serverName, int flags);
	void (*ReadWriteDispatch)(char* connName, int timeout);
	int (*PopMessage)(char* connName, char* messageName);
	int (*IsMathodCall)(char* messageName, char* interface, char* method);
	void (*GetArgs)(char* messageName, char* errorName, int type, char** message);
	void (*NewMethodReturn)(char* messageName, char* replyName);
	void (*IterInitAppend)(char* replyName, int type, char** message);
	void (*Send)(char* connName, char* sendName);
	void (*SendWithReply)(char* connName, char* sendName, char* pendingName, int timeout);
	void (*FFlush)(char* connName);
	void (*UnrefMessage)(char* replyName);
	void (*UnrefPendingCall)(char* pendingName);
	void (*NewError)(char* messageName, char* message);
	void (*ReleaseBus)(char* connName, char* busName, char* errorName);
	void (*FreeError)(char* errorName);
	GMapO(GDBus_GCHAR_PTR_GDBUSCONNECTION_PTR)* m_connMap;
	GMapO(GDBus_GCHAR_PTR_GDBUSMESSAGE_PTR)* m_messageMap;
	GMapO(GDBus_GCHAR_PTR_GDBUSERROR_PTR)* m_errorMap;
	GMapO(GDBus_GCHAR_PTR_GDBUSPENDINGCALL_PTR)* m_pendingMap;
};
//===============================================
GDBusO* GDBus_New();
void GDBus_Delete();
GDBusO* GDBus();
//===============================================
#endif
//===============================================
