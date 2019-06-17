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
	void (*WsaData)(char* wsaDataName);
	void (*Start)(char* wsaDataName, int major, int minor);
	void (*Status)(char* wsaDataName);
	void (*Major)(char* wsaDataName);
	void (*Minor)(char* wsaDataName);
	void (*MajorMax)(char* wsaDataName);
	void (*MinorMax)(char* wsaDataName);
	void (*Address)(char* addressName);
	void (*Address2)(char* addressName, int family, int address, int port);
	void (*Socket)(char* socketName);
	void (*Socket2)(char* socketName, int family, int type, int protocol);
	void (*SocketName)(char* socketName, char* addressName);
	void (*AddressIp)(char* addressName);
	void (*Port)(char* addressName);
	void (*Bind)(char* socketName, char* addressName);
	void (*Listen)(char* socketName, int backlog);
	void (*Accept)(char* socketName, char* clientName);
	void (*Connect)(char* socketName);
	void (*Write)(char* socketName, char* message, int size);
	void (*Read)(char* socketName, char* message, int size);
	void (*Send)(char* socketName, char* message, int size);
	void (*Recv)(char* socketName, char* message, int size);
	void (*Close)(char* socketName);
	void (*Clean)(char* socketName);
};
//===============================================
GSocketO* GSocket_New();
void GSocket_Delete(GSocketO* obj);
GSocketO* GSocket();
//===============================================
#endif
//===============================================
