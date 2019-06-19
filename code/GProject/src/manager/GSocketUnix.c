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
static void GSocketUnix_Socket(char* socketName);
static void GSocketUnix_Socket2(char* socketName, int family, int type, int protocol);
static void GSocketUnix_SocketName(char* socketName, char* addressName);
static void GSocketUnix_AddressIp(char* addressName);
static void GSocketUnix_Port(char* socketName);
static void GSocketUnix_Bind(char* socketName, char* addressName);
static void GSocketUnix_Listen(char* socketName, int backlog);
static void GSocketUnix_Accept(char* socketName, char* clientName);
static void GSocketUnix_Connect(char* socketName);
static void GSocketUnix_Send(char* socketName, char* message, int size);
static void GSocketUnix_Recv(char* socketName, char* message, int size);
static void GSocketUnix_Close(char* socketName);
//===============================================
#if defined(__unix)
static int GSocketUnix_MapEqual(char* key1, char* key2);
#endif
//===============================================
GSocketO* GSocketUnix_New() {
	GSocketO* lParent = GSocket_New();
	GSocketUnixO* lChild = (GSocketUnixO*)malloc(sizeof(GSocketUnixO));

	lChild->m_parent = lParent;
#if defined(__unix)
	lChild->m_socketMap = GMap_New_GSocketUnix_GCHAR_PTR_GINT_PTR();
	lChild->m_addressMap = GMap_New_GSocketUnix_GCHAR_PTR_GSOCKADDR_IN_PTR();
#endif

	lParent->m_child = lChild;
	lParent->Delete = GSocketUnix_Delete;
	lParent->Socket = GSocketUnix_Socket;
	lParent->Socket2 = GSocketUnix_Socket2;
	lParent->SocketName = GSocketUnix_SocketName;
	lParent->AddressIp = GSocketUnix_AddressIp;
	lParent->Port = GSocketUnix_Port;
	lParent->Address = GSocketUnix_Address;
	lParent->Address2 = GSocketUnix_Address2;
	lParent->Bind = GSocketUnix_Bind;
	lParent->Listen = GSocketUnix_Listen;
	lParent->Accept = GSocketUnix_Accept;
	lParent->Connect = GSocketUnix_Connect;
	lParent->Send = GSocketUnix_Send;
	lParent->Recv = GSocketUnix_Recv;
	lParent->Close = GSocketUnix_Close;
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
	lAddress->sin_addr.s_addr = htonl(address);
	lAddress->sin_family = family;
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
	if(*lSocket == -1) {GConsole()->Print(" [ GSocketWindows ] Error GSocketUnix_Socket2: %d\n", errno); exit(0);}
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

#endif
}
//===============================================
static void GSocketUnix_Listen(char* socketName, int backlog) {
#if defined(__unix)

#endif
}
//===============================================
static void GSocketUnix_Accept(char* socketName, char* clientName) {
#if defined(__unix)

#endif
}
//===============================================
static void GSocketUnix_Connect(char* socketName) {
#if defined(__unix)

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
