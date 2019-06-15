//===============================================
#ifndef _GSocket_
#define _GSocket_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GSocketO GSocketO;
//===============================================
struct _GSocketO {
	void* m_child;
	void (*Delete)(GSocketO* obj);
	void (*Start)(const int major, const int minor);
	void (*Status)();
	void (*Major)();
	void (*Minor)();
	void (*MajorMax)();
	void (*MinorMax)();
	void (*Socket)(const int addressFamily, const int type, const int protocol);
	void (*SocketName)();
	void (*IpAddress)();
	void (*Port)();
	void (*Address)(const int addressFamily, const char* ipAddress, const int port);
	void (*Address2)(const int addressFamily, const ulong ipAddress, const int port);
	void (*Bind)();
	void (*Listen)(const int backlog);
	int (*Accept)();
	void (*Connect)();
	void (*Send)();
	void (*Recv)();
	void (*Close)();
	void (*Close2)();
	void (*Clean)();
};
//===============================================
GSocketO* GSocket_New();
void GSocket_Delete(GSocketO* obj);
GSocketO* GSocket();
//===============================================
#endif
//===============================================
