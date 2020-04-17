//===============================================
#ifndef _GSocket2_
#define _GSocket2_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GSocket2O GSocket2O;
//===============================================
typedef enum _GSOCKET2_INITIALIZER {
	GSOCKET2_INIT_AF_INET,
	GSOCKET2_INIT_SOCK_STREAM,
	GSOCKET2_INIT_SOCK_DGRAM,
	GSOCKET2_INIT_IPPROTO_TCP,
	GSOCKET2_INIT_INADDR_ANY
} GSOCKET2_INITIALIZER;
//===============================================
struct _GSocket2O {
	void* m_child;
	void (*Delete)(GSocket2O* obj);
	void (*MallocSocket)(char* socketName);
	void (*MallocAddress)(char* addressName);
	void (*MallocData)(char* dataName);
	void (*Start)(char* dataName, int major, int minor);
	void (*Status)(char* dataName);
	void (*Major)(char* dataName);
	void (*Minor)(char* dataName);
	void (*MajorMax)(char* dataName);
	void (*MinorMax)(char* dataName);
	void (*Socket)(char* socketName, int family, int type, int protocol);
	void (*AddressInt)(char* addressName, int family, int address, int port);
	void (*AddressChar)(char* addressName, int family, char* address, int port);
	void (*SocketName)(char* socketName, char* addressName);
	void (*AddressIp)(char* addressName);
	void (*Port)(char* addressName);
	void (*Bind)(char* socketName, char* addressName);
	void (*Listen)(char* socketName, int backlog);
	void (*Accept)(char* serverSocket, char* clientSocket, char* clientAddress);
	void (*Connect)(char* clientSocket, char* serverAddress);
	int (*Write)(char* socketName, char* data, int size);
	int (*Read)(char* socketName, char* data, int size);
	void (*Send)(char* socketName, char* message, int size);
	void (*Recv)(char* socketName, char* message, int size);
    int (*SendTo)(char* socketName, char* addressName, char* data, int size, int flags);
    int (*RecvFrom)(char* socketName, char* addressName, char* data, int size, int flags);
	void (*Close)(char* socketName);
	void (*Clean)();
	void (*FreeSocket)(char* socketName);
	void (*FreeAddress)(char* socketName);
	void (*FreeData)(char* dataName);
};
//===============================================
GSocket2O* GSocket2_New();
void GSocket2_Delete(GSocket2O* obj);
GSocket2O* GSocket2();
//===============================================
#endif
//===============================================
