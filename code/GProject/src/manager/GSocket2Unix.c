//===============================================
#include "GSocket2Unix.h"
#include "GConsole.h"
#include "GString2.h"
//===============================================
#if defined(__unix)
typedef char* GCHAR_PTR;
typedef int* GINT_PTR;
typedef struct sockaddr_in* GSOCKADDR_IN_PTR;
//===============================================
GDECLARE_MAP(GCHAR_PTR, GINT_PTR, GSocket2Unix_GCHAR_PTR_GINT_PTR)
GDEFINE_MAP(GCHAR_PTR, GINT_PTR, GSocket2Unix_GCHAR_PTR_GINT_PTR)
//===============================================
GDECLARE_MAP(GCHAR_PTR, GSOCKADDR_IN_PTR, GSocket2Unix_GCHAR_PTR_GSOCKADDR_IN_PTR)
GDEFINE_MAP(GCHAR_PTR, GSOCKADDR_IN_PTR, GSocket2Unix_GCHAR_PTR_GSOCKADDR_IN_PTR)
#endif
//===============================================
static GSocket2O* m_GSocket2UnixO = 0;
//===============================================
static void GSocket2Unix_Address(char* addressName);
static void GSocket2Unix_Address2(char* addressName, int family, int address, int port);
static void GSocket2Unix_Address3(char* addressName, int family, char* address, int port);
static void GSocket2Unix_Socket(char* socketName);
static void GSocket2Unix_Socket2(char* socketName, int family, int type, int protocol);
static void GSocket2Unix_SocketName(char* socketName, char* addressName);
static void GSocket2Unix_AddressIp(char* addressName);
static void GSocket2Unix_Port(char* socketName);
static void GSocket2Unix_Bind(char* socketName, char* addressName);
static void GSocket2Unix_Listen(char* socketName, int backlog);
static void GSocket2Unix_Accept(char* socketName, char* clientName);
static void GSocket2Unix_Connect(char* socketName, char* addressName);
static void GSocket2Unix_Write(char* socketName, char* message, int size);
static void GSocket2Unix_Read(char* socketName, char* message, int size);
static void GSocket2Unix_Send(char* socketName, char* message, int size);
static void GSocket2Unix_Recv(char* socketName, char* message, int size);
static void GSocket2Unix_Close(char* socketName);
static void GSocket2Unix_Clean2(char* socketName);
static void GSocket2Unix_Clean3(char* addressName);
//===============================================
#if defined(__unix)
static int GSocket2Unix_MapEqual(char* key1, char* key2);
#endif
//===============================================
GSocket2O* GSocket2Unix_New() {
	GSocket2O* lParent = GSocket2_New();
	GSocket2UnixO* lChild = (GSocket2UnixO*)malloc(sizeof(GSocket2UnixO));

	lChild->m_parent = lParent;
#if defined(__unix)
	lChild->m_socketMap = GMap_New_GSocket2Unix_GCHAR_PTR_GINT_PTR();
	lChild->m_addressMap = GMap_New_GSocket2Unix_GCHAR_PTR_GSOCKADDR_IN_PTR();
#endif

	lParent->m_child = lChild;
	lParent->Delete = GSocket2Unix_Delete;
	lParent->Socket = GSocket2Unix_Socket;
	lParent->Socket2 = GSocket2Unix_Socket2;
	lParent->SocketName = GSocket2Unix_SocketName;
	lParent->AddressIp = GSocket2Unix_AddressIp;
	lParent->Port = GSocket2Unix_Port;
	lParent->Address = GSocket2Unix_Address;
	lParent->Address2 = GSocket2Unix_Address2;
	lParent->Address3 = GSocket2Unix_Address3;
	lParent->Bind = GSocket2Unix_Bind;
	lParent->Listen = GSocket2Unix_Listen;
	lParent->Accept = GSocket2Unix_Accept;
	lParent->Connect = GSocket2Unix_Connect;
	lParent->Write = GSocket2Unix_Write;
	lParent->Read = GSocket2Unix_Read;
	lParent->Send = GSocket2Unix_Send;
	lParent->Recv = GSocket2Unix_Recv;
	lParent->Close = GSocket2Unix_Close;
	lParent->Clean2 = GSocket2Unix_Clean2;
	lParent->Clean3= GSocket2Unix_Clean3;
	return lParent;
}
//===============================================
void GSocket2Unix_Delete(GSocket2O* obj) {
	GSocket2_Delete(obj);
	m_GSocket2UnixO = 0;
}
//===============================================
GSocket2O* GSocket2Unix() {
	if(m_GSocket2UnixO == 0) {
		m_GSocket2UnixO = GSocket2Unix_New();
	}
	return m_GSocket2UnixO;
}
//===============================================
static void GSocket2Unix_Address(char* addressName) {
#if defined(__unix)
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketUnix->m_addressMap;
	struct sockaddr_in* lAddress = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
	lAddressMap->SetData(lAddressMap, addressName, lAddress, GSocket2Unix_MapEqual);
#endif
}
//===============================================
static void GSocket2Unix_Address2(char* addressName, int family, int address, int port) {
#if defined(__unix)
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketUnix->m_addressMap;
	struct sockaddr_in* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocket2Unix_MapEqual);
	bzero(lAddress, sizeof(lAddress));
	lAddress->sin_family = family;
	lAddress->sin_addr.s_addr = htonl(address);
	lAddress->sin_port = htons(port);
#endif
}
//===============================================
static void GSocket2Unix_Address3(char* addressName, int family, char* address, int port) {
#if defined(__unix)
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketUnix->m_addressMap;
	struct sockaddr_in* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocket2Unix_MapEqual);
	bzero(lAddress, sizeof(lAddress));
	lAddress->sin_family = family;
	lAddress->sin_addr.s_addr = inet_addr(address);
	lAddress->sin_port = htons(port);
#endif
}
//===============================================
static void GSocket2Unix_Socket(char* socketName) {
#if defined(__unix)
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	int* lSocket = (int*)malloc(sizeof(int));
	lSocketMap->SetData(lSocketMap, socketName, lSocket, GSocket2Unix_MapEqual);
#endif
}
//===============================================
static void GSocket2Unix_Socket2(char* socketName, int family, int type, int protocol) {
#if defined(__unix)
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Unix_MapEqual);
	*lSocket = socket(family, type, protocol);
	if(*lSocket == -1) {GConsole()->Print("[ GSocket2Unix ] Error GSocket2Unix_Socket2: %d\n", errno); exit(0);}
#endif
}
//===============================================
static void GSocket2Unix_SocketName(char* socketName, char* addressName) {
#if defined(__unix)

#endif
}
//===============================================
static void GSocket2Unix_AddressIp(char* addressName) {
#if defined(__unix)

#endif
}
//===============================================
static void GSocket2Unix_Port(char* addressName) {
#if defined(__unix)

#endif
}
//===============================================
static void GSocket2Unix_Bind(char* socketName, char* addressName) {
#if defined(__unix)
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	GMapO(GSocket2Unix_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketUnix->m_addressMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Unix_MapEqual);
	struct sockaddr_in* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocket2Unix_MapEqual);
	int lSize = sizeof(lAddress);
	int lOk = bind(*lSocket, (struct sockaddr*)lAddress, lSize);
	if(lOk == -1) {GConsole()->Print("[ GSocket2Unix ] Error GSocket2Unix_Bind: %d\n", lAddress->sin_port); exit(0);}
#endif
}
//===============================================
static void GSocket2Unix_Listen(char* socketName, int backlog) {
#if defined(__unix)
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Unix_MapEqual);
	int lOk = listen(*lSocket, backlog);
	if(lOk == -1) {GConsole()->Print("[ GSocket2Unix ] Error GSocket2Unix_Listen: %d\n", errno); exit(0);}
#endif
}
//===============================================
static void GSocket2Unix_Accept(char* socketName, char* clientName) {
#if defined(__unix)
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	GMapO(GSocket2Unix_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketUnix->m_addressMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Unix_MapEqual);
	int* lSocket2 = lSocketMap->GetData(lSocketMap, clientName, GSocket2Unix_MapEqual);
	struct sockaddr_in* lAddress2 = lAddressMap->GetData(lAddressMap, clientName, GSocket2Unix_MapEqual);
	bzero(lAddress2, sizeof(lAddress2));
	int lSize2 = sizeof(lAddress2);
	*lSocket2 = accept(*lSocket, (struct sockaddr*)lAddress2, (socklen_t*)&lSize2);
	if(*lSocket2 == -1) {GConsole()->Print("[ GSocket2Unix ] Error GSocket2Unix_Accept: %d\n", errno); exit(0);}
#endif
}
//===============================================
static void GSocket2Unix_Connect(char* socketName, char* addressName) {
#if defined(__unix)
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	GMapO(GSocket2Unix_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketUnix->m_addressMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Unix_MapEqual);
	struct sockaddr_in* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocket2Unix_MapEqual);
	int lSize = sizeof(lAddress);
	int lOk = connect(*lSocket, (struct sockaddr*)lAddress, lSize);
	if(lOk == -1) {GConsole()->Print("[ GSocket2Unix ] Error GSocket2Unix_Connect: %d\n", errno); exit(0);}
#endif
}
//===============================================
static void GSocket2Unix_Write(char* socketName, char* message, int size) {
#if defined(__unix)
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Unix_MapEqual);
	int lSize = size;
	if(lSize <= 0) lSize = strlen(message);
	int lBytes = write(*lSocket, message, lSize);
	if(lBytes == -1) {GConsole()->Print("[ GSocket2Unix ] Error GSocket2Unix_Write: %d\n", errno); exit(0);}
#endif
}
//===============================================
static void GSocket2Unix_Read(char* socketName, char* message, int size) {
#if defined(__unix)
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Unix_MapEqual);
	int lSize = size;
	if(lSize <= 0) lSize = strlen(message);
	int lBytes = read(*lSocket, message, lSize);
	if(lBytes == -1) {GConsole()->Print("[ GSocket2Unix ] Error GSocket2Unix_Read: %d\n", errno); exit(0);}
	message[lBytes] = 0;
#endif
}
//===============================================
static void GSocket2Unix_Send(char* socketName, char* message, int size) {
#if defined(__unix)

#endif
}
//===============================================
static void GSocket2Unix_Recv(char* socketName, char* message, int size) {
#if defined(__unix)

#endif
}
//===============================================
static void GSocket2Unix_Close(char* socketName) {
#if defined(__unix)
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Unix_MapEqual);
	int lOk = close(*lSocket);
	if(lOk == -1) {GConsole()->Print("[ GSocket2Unix ] Error GSocket2Unix_Close: %d\n", errno); exit(0);}
#endif
}
//===============================================
static void GSocket2Unix_Clean2(char* socketName) {
#if defined(__unix)
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Unix_MapEqual);
	free(lSocket);
#endif
}
//===============================================
static void GSocket2Unix_Clean3(char* addressName) {
#if defined(__unix)
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketUnix->m_addressMap;
	struct sockaddr_in* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocket2Unix_MapEqual);
	free(lAddress);
#endif
}
//===============================================
#if defined(__unix)
static int GSocket2Unix_MapEqual(char* key1, char* key2) {
    int lStrcmp = strcmp(key1, key2);
    if(lStrcmp == 0) return TRUE;
    return FALSE;
}
#endif
//===============================================
