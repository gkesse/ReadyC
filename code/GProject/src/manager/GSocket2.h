//===============================================
#ifndef _GSocket2_
#define _GSocket2_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GSocket2O GSocket2O;
//===============================================
// ADATPER A LA CONNEXION MULTIPLE
//===============================================
struct _GSocket2O {
	void* m_child;
	void (*Delete)(GSocket2O* obj);
	//===============================================
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
	void (*Close)(char* socketName);
	void (*FreeSocket)(char* socketName);
	void (*FreeAddress)(char* socketName);
	//===============================================
	void (*Send)(char* socketName, char* message, int size);
	void (*Recv)(char* socketName, char* message, int size);
	void (*Clean)(char* dataName);
	void (*Clean2)(char* socketName);
	void (*Clean3)(char* addressName);
};
//===============================================
GSocket2O* GSocket2_New();
void GSocket2_Delete(GSocket2O* obj);
GSocket2O* GSocket2();
//===============================================
#endif
//===============================================
