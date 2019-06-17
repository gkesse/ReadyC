//===============================================
#include "GSocketUnix.h"
#include "GString.h"
#include "GConsole.h"
//===============================================
#if defined(__unix)
typedef char* GCHAR_PTR;
typedef int* GINT_PTR;
typedef struct sockaddr_in* GSOCKADDR_IN_PTR;
//===============================================
GDECLARE_MAP(GCHAR_PTR, GINT_PTR, GSocketUnix_GCHAR_PTR_GINT_PTR)
GDEFINE_MAP(GCHAR_PTR, GINT_PTR, GSocketUnix_GCHAR_PTR_GINT_PTR)
//===============================================
GDECLARE_MAP(GCHAR_PTR, GSOCKADDR_IN_PTR, GSocketUnix_GCHAR_PTR_GSOCKADDR_IN_PTR)
GDEFINE_MAP(GCHAR_PTR, GSOCKADDR_IN_PTR, GSocketUnix_GCHAR_PTR_GSOCKADDR_IN_PTR)
#endif
//===============================================
static GSocketO* m_GSocketUnixO = 0;
//===============================================
static void GSocketUnix_Address(char* addressName);
static void GSocketUnix_Address2(char* addressName, int family, int address, int port);
static void GSocketUnix_Address3(char* addressName, int family, char* address, int port);
static void GSocketUnix_Socket(char* socketName);
static void GSocketUnix_Socket2(char* socketName, int family, int type, int protocol);
static void GSocketUnix_SocketName(char* socketName, char* addressName);
static void GSocketUnix_AddressIp(char* addressName);
static void GSocketUnix_Port(char* socketName);
static void GSocketUnix_Bind(char* socketName, char* addressName);
static void GSocketUnix_Listen(char* socketName, int backlog);
static void GSocketUnix_Accept(char* socketName, char* clientName);
static void GSocketUnix_Connect(char* socketName, char* addressName);
static void GSocketUnix_Write(char* socketName, char* message, int size);
static void GSocketUnix_Read(char* socketName, char* message, int size);
static void GSocketUnix_Send(char* socketName, char* message, int size);
static void GSocketUnix_Recv(char* socketName, char* message, int size);
static void GSocketUnix_Close(char* socketName);
static void GSocketUnix_Clean2(char* socketName);
static void GSocketUnix_Clean3(char* addressName);
//===============================================
#if defined(__unix)
static int GSocketUnix_MapEqual(char* key1, char* key2);
#endif
//===============================================
GSocketO* GSocketUnix_New() {
	GSocketO* lParent = GSocket_New();
	GSocketUnixO* lChild = (GSocketUnixO*)malloc(sizeof(GSocketUnixO));

	lChild->m_parent = lParent;
	lChild->m_socketMap = GMap_New_GSocketUnix_GCHAR_PTR_GINT_PTR();
	lChild->m_addressMap = GMap_New_GSocketUnix_GCHAR_PTR_GSOCKADDR_IN_PTR();

	lParent->m_child = lChild;
	lParent->Delete = GSocketUnix_Delete;
	lParent->Socket = GSocketUnix_Socket;
	lParent->Socket2 = GSocketUnix_Socket2;
	lParent->SocketName = GSocketUnix_SocketName;
	lParent->AddressIp = GSocketUnix_AddressIp;
	lParent->Port = GSocketUnix_Port;
	lParent->Address = GSocketUnix_Address;
	lParent->Address2 = GSocketUnix_Address2;
	lParent->Address3 = GSocketUnix_Address3;
	lParent->Bind = GSocketUnix_Bind;
	lParent->Listen = GSocketUnix_Listen;
	lParent->Accept = GSocketUnix_Accept;
	lParent->Connect = GSocketUnix_Connect;
	lParent->Write = GSocketUnix_Write;
	lParent->Read = GSocketUnix_Read;
	lParent->Send = GSocketUnix_Send;
	lParent->Recv = GSocketUnix_Recv;
	lParent->Close = GSocketUnix_Close;
	lParent->Clean2 = GSocketUnix_Clean2;
	lParent->Clean3= GSocketUnix_Clean3;
	return lParent;
}
//===============================================
void GSocketUnix_Delete(GSocketO* obj) {
	GSocket_Delete(obj);
	m_GSocketUnixO = 0;
}
//===============================================
GSocketO* GSocketUnix() {
	if(m_GSocketUnixO == 0) {
		m_GSocketUnixO = GSocketUnix_New();
	}
	return m_GSocketUnixO;
}
//===============================================
static void GSocketUnix_Address(char* addressName) {
#if defined(__unix)
	GSocketUnixO* lSocketUnix = m_GSocketUnixO->m_child;
	GMapO(GSocketUnix_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketUnix->m_addressMap;
	struct sockaddr_in* lAddress = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
	lAddressMap->SetData(lAddressMap, addressName, lAddress, GSocketUnix_MapEqual);
#endif
}
//===============================================
static void GSocketUnix_Address2(char* addressName, int family, int address, int port) {
#if defined(__unix)
	GSocketUnixO* lSocketUnix = m_GSocketUnixO->m_child;
	GMapO(GSocketUnix_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketUnix->m_addressMap;
	struct sockaddr_in* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocketUnix_MapEqual);
	bzero(lAddress, sizeof(lAddress));
	lAddress->sin_family = family;
	lAddress->sin_addr.s_addr = htonl(address);
	lAddress->sin_port = htons(port);
#endif
}
//===============================================
static void GSocketUnix_Address3(char* addressName, int family, char* address, int port) {
#if defined(__unix)
	GSocketUnixO* lSocketUnix = m_GSocketUnixO->m_child;
	GMapO(GSocketUnix_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketUnix->m_addressMap;
	struct sockaddr_in* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocketUnix_MapEqual);
	bzero(lAddress, sizeof(lAddress));
	lAddress->sin_family = family;
	lAddress->sin_addr.s_addr = inet_addr(address);
	lAddress->sin_port = htons(port);
#endif
}
//===============================================
static void GSocketUnix_Socket(char* socketName) {
#if defined(__unix)
	GSocketUnixO* lSocketUnix = m_GSocketUnixO->m_child;
	GMapO(GSocketUnix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	int* lSocket = (int*)malloc(sizeof(int));
	lSocketMap->SetData(lSocketMap, socketName, lSocket, GSocketUnix_MapEqual);
#endif
}
//===============================================
static void GSocketUnix_Socket2(char* socketName, int family, int type, int protocol) {
#if defined(__unix)
	GSocketUnixO* lSocketUnix = m_GSocketUnixO->m_child;
	GMapO(GSocketUnix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocketUnix_MapEqual);
	*lSocket = socket(family, type, protocol);
	if(*lSocket == -1) {GConsole()->Print("[ GSocketUnix ] Error GSocketUnix_Socket2: %d\n", errno); exit(0);}
#endif
}
//===============================================
static void GSocketUnix_SocketName(char* socketName, char* addressName) {
#if defined(__unix)

#endif
}
//===============================================
static void GSocketUnix_AddressIp(char* addressName) {
#if defined(__unix)

#endif
}
//===============================================
static void GSocketUnix_Port(char* addressName) {
#if defined(__unix)

#endif
}
//===============================================
static void GSocketUnix_Bind(char* socketName, char* addressName) {
#if defined(__unix)
	GSocketUnixO* lSocketUnix = m_GSocketUnixO->m_child;
	GMapO(GSocketUnix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	GMapO(GSocketUnix_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketUnix->m_addressMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocketUnix_MapEqual);
	struct sockaddr_in* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocketUnix_MapEqual);
	int lSize = sizeof(lAddress);
	int lOk = bind(*lSocket, (struct sockaddr*)lAddress, lSize);
	if(lOk == -1) {GConsole()->Print("[ GSocketUnix ] Error GSocketUnix_Bind: %d\n", lAddress->sin_port); exit(0);}
#endif
}
//===============================================
static void GSocketUnix_Listen(char* socketName, int backlog) {
#if defined(__unix)
	GSocketUnixO* lSocketUnix = m_GSocketUnixO->m_child;
	GMapO(GSocketUnix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocketUnix_MapEqual);
	int lOk = listen(*lSocket, backlog);
	if(lOk == -1) {GConsole()->Print("[ GSocketUnix ] Error GSocketUnix_Listen: %d\n", errno); exit(0);}
#endif
}
//===============================================
static void GSocketUnix_Accept(char* socketName, char* clientName) {
#if defined(__unix)
	GSocketUnixO* lSocketUnix = m_GSocketUnixO->m_child;
	GMapO(GSocketUnix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	GMapO(GSocketUnix_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketUnix->m_addressMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocketUnix_MapEqual);
	int* lSocket2 = lSocketMap->GetData(lSocketMap, clientName, GSocketUnix_MapEqual);
	struct sockaddr_in* lAddress2 = lAddressMap->GetData(lAddressMap, clientName, GSocketUnix_MapEqual);
	bzero(lAddress2, sizeof(lAddress2));
	int lSize2 = sizeof(lAddress2);
	*lSocket2 = accept(*lSocket, (struct sockaddr*)lAddress2, (socklen_t*)&lSize2);
	if(*lSocket2 == -1) {GConsole()->Print("[ GSocketUnix ] Error GSocketUnix_Accept: %d\n", errno); exit(0);}
#endif
}
//===============================================
static void GSocketUnix_Connect(char* socketName, char* addressName) {
#if defined(__unix)
	GSocketUnixO* lSocketUnix = m_GSocketUnixO->m_child;
	GMapO(GSocketUnix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	GMapO(GSocketUnix_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketUnix->m_addressMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocketUnix_MapEqual);
	struct sockaddr_in* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocketUnix_MapEqual);
	int lSize = sizeof(lAddress);
	int lOk = connect(*lSocket, (struct sockaddr*)lAddress, lSize);
	if(lOk == -1) {GConsole()->Print("[ GSocketUnix ] Error GSocketUnix_Connect: %d\n", errno); exit(0);}
#endif
}
//===============================================
static void GSocketUnix_Write(char* socketName, char* message, int size) {
#if defined(__unix)
	GSocketUnixO* lSocketUnix = m_GSocketUnixO->m_child;
	GMapO(GSocketUnix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocketUnix_MapEqual);
	int lSize = size;
	if(lSize <= 0) lSize = strlen(message);
	int lBytes = write(*lSocket, message, lSize);
	if(lBytes == -1) {GConsole()->Print("[ GSocketUnix ] Error GSocketUnix_Write: %d\n", errno); exit(0);}
#endif
}
//===============================================
static void GSocketUnix_Read(char* socketName, char* message, int size) {
#if defined(__unix)
	GSocketUnixO* lSocketUnix = m_GSocketUnixO->m_child;
	GMapO(GSocketUnix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocketUnix_MapEqual);
	int lSize = size;
	if(lSize <= 0) lSize = strlen(message);
	int lBytes = read(*lSocket, message, lSize);
	if(lBytes == -1) {GConsole()->Print("[ GSocketUnix ] Error GSocketUnix_Read: %d\n", errno); exit(0);}
	message[lBytes] = 0;
#endif
}
//===============================================
static void GSocketUnix_Send(char* socketName, char* message, int size) {
#if defined(__unix)

#endif
}
//===============================================
static void GSocketUnix_Recv(char* socketName, char* message, int size) {
#if defined(__unix)

#endif
}
//===============================================
static void GSocketUnix_Close(char* socketName) {
#if defined(__unix)
	GSocketUnixO* lSocketUnix = m_GSocketUnixO->m_child;
	GMapO(GSocketUnix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocketUnix_MapEqual);
	int lOk = close(*lSocket);
	if(lOk == -1) {GConsole()->Print("[ GSocketUnix ] Error GSocketUnix_Close: %d\n", errno); exit(0);}
#endif
}
//===============================================
static void GSocketUnix_Clean2(char* socketName) {
#if defined(__unix)
	GSocketUnixO* lSocketUnix = m_GSocketUnixO->m_child;
	GMapO(GSocketUnix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocketUnix_MapEqual);
	free(lSocket);
#endif
}
//===============================================
static void GSocketUnix_Clean3(char* addressName) {
#if defined(__unix)
	GSocketUnixO* lSocketUnix = m_GSocketUnixO->m_child;
	GMapO(GSocketUnix_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketUnix->m_addressMap;
	struct sockaddr_in* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocketUnix_MapEqual);
	free(lAddress);
#endif
}
//===============================================
#if defined(__unix)
static int GSocketUnix_MapEqual(char* key1, char* key2) {
    int lStrcmp = strcmp(key1, key2);
    if(lStrcmp == 0) return TRUE;
    return FALSE;
}
#endif
//===============================================
