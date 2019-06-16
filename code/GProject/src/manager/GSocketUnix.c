//===============================================
#include "GSocketUnix.h"
#include "GString.h"
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
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketUnix_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKADDR_IN* lAddress = (SOCKADDR_IN*)malloc(sizeof(SOCKADDR_IN));
	lAddressMap->SetData(lAddressMap, addressName, lAddress, GSocketUnix_MapEqual);
#endif
}
//===============================================
static void GSocketUnix_Address2(char* addressName, int family, int address, int port) {
#if defined(__unix)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketUnix_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKADDR_IN* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocketUnix_MapEqual);
	lAddress->sin_addr.s_addr = htonl(address);
	lAddress->sin_family = family;
	lAddress->sin_port = htons(port);
#endif
}
//===============================================
static void GSocketUnix_Socket(char* socketName) {
#if defined(__unix)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketUnix_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	SOCKET* lSocket = (SOCKET*)malloc(sizeof(SOCKET));
	lSocketMap->SetData(lSocketMap, socketName, lSocket, GSocketUnix_MapEqual);
#endif
}
//===============================================
static void GSocketUnix_Socket2(char* socketName, int family, int type, int protocol) {
#if defined(__unix)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketUnix_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocketUnix_MapEqual);
	*lSocket = socket(family, type, protocol);
	if(*lSocket == INVALID_SOCKET) {GConsole()->Print(" [ GSocketWindows ] Error GSocketUnix_Socket2: %d\n", WSAGetLastError()); exit(0);}
#endif
}
//===============================================
static void GSocketUnix_SocketName(char* socketName, char* addressName) {
#if defined(__unix)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketUnix_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	GMapO(GSocketUnix_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocketUnix_MapEqual);
	SOCKADDR_IN* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocketUnix_MapEqual);
	int lSize = sizeof(*lAddress);
	int lOk = getsockname(*lSocket, (SOCKADDR*)lAddress, &lSize);
	if(lOk == SOCKET_ERROR) {GConsole()->Print(" [ GSocketWindows ] Error GSocketUnix_SocketName: %d\n", WSAGetLastError()); exit(0);}
#endif
}
//===============================================
static void GSocketUnix_AddressIp(char* addressName) {
#if defined(__unix)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketUnix_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKADDR_IN* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocketUnix_MapEqual);
	char* lIpAddress = inet_ntoa(lAddress->sin_addr);
	GConsole()->Print(" [ GSocketWindows ] Address IP: %s\n", lIpAddress);
#endif
}
//===============================================
static void GSocketUnix_Port(char* addressName) {
#if defined(__unix)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketUnix_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKADDR_IN* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocketUnix_MapEqual);
	int lPort = htons(lAddress->sin_port);
	GConsole()->Print(" [ GSocketWindows ] Port: %s\n", lPort);
#endif
}
//===============================================
static void GSocketUnix_Bind(char* socketName, char* addressName) {
#if defined(__unix)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketUnix_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	GMapO(GSocketUnix_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocketUnix_MapEqual);
	SOCKADDR_IN* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocketUnix_MapEqual);
	int lSize = sizeof(*lAddress);
	int lOk = bind(*lSocket, (SOCKADDR*)lAddress, lSize);
	if(lOk == SOCKET_ERROR) {GConsole()->Print(" [ GSocketWindows ] Error GSocketUnix_Bind: %d\n", WSAGetLastError()); exit(0);}
#endif
}
//===============================================
static void GSocketUnix_Listen(char* socketName, int backlog) {
#if defined(__unix)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketUnix_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocketUnix_MapEqual);
	int lOk = listen(*lSocket, backlog);
	if(lOk == SOCKET_ERROR) {GConsole()->Print(" [ GSocketWindows ] Error GSocketUnix_Listen: %d\n", WSAGetLastError()); exit(0);}
#endif
}
//===============================================
static void GSocketUnix_Accept(char* socketName, char* clientName) {
#if defined(__unix)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketUnix_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	GMapO(GSocketUnix_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocketUnix_MapEqual);
	SOCKET* lSocket2 = lSocketMap->GetData(lSocketMap, clientName, GSocketUnix_MapEqual);
	SOCKADDR_IN* lAddress2 = lAddressMap->GetData(lAddressMap, clientName, GSocketUnix_MapEqual);
	int lSize2 = sizeof(*lAddress2);
	*lSocket2 = accept(*lSocket, (SOCKADDR*)lAddress2, &lSize2);
	if(*lSocket2 == INVALID_SOCKET) {GConsole()->Print(" [ GSocketWindows ] Error GSocketUnix_Accept: %d\n", WSAGetLastError()); exit(0);}
#endif
}
//===============================================
static void GSocketUnix_Connect(char* socketName) {
#if defined(__unix)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketUnix_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	GMapO(GSocketUnix_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocketUnix_MapEqual);
	SOCKADDR_IN* lAddress = lAddressMap->GetData(lAddressMap, socketName, GSocketUnix_MapEqual);
	int lSize = sizeof(*lAddress);
	int lOk = connect(*lSocket, (SOCKADDR*)lAddress, lSize);
	if(lOk == SOCKET_ERROR) {GConsole()->Print(" [ GSocketWindows ] Error GSocketUnix_Connect: %d\n", WSAGetLastError()); exit(0);}
#endif
}
//===============================================
static void GSocketUnix_Send(char* socketName, char* message, int size) {
#if defined(__unix)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketUnix_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocketUnix_MapEqual);
	int lSize = size;
	if(lSize <= 0) lSize = strlen(message);
	int lBytes = send(*lSocket, message, lSize, 0);
	if(lBytes == SOCKET_ERROR) {GConsole()->Print(" [ GSocketWindows ] Error GSocketUnix_Send: %d\n", WSAGetLastError()); exit(0);}
#endif
}
//===============================================
static void GSocketUnix_Recv(char* socketName, char* message, int size) {
#if defined(__unix)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketUnix_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocketUnix_MapEqual);
	int lSize = size;
	if(lSize <= 0) lSize = strlen(message);
	int lBytes = recv(*lSocket, message, lSize, 0);
	if(lBytes == SOCKET_ERROR) {GConsole()->Print(" [ GSocketWindows ] Error GSocketUnix_Recv: %d\n", WSAGetLastError()); exit(0);}
	message[lBytes] = 0;
#endif
}
//===============================================
static void GSocketUnix_Close(char* socketName) {
#if defined(__unix)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketUnix_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	GMapO(GSocketUnix_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocketUnix_MapEqual);
	SOCKADDR_IN* lAddress = lAddressMap->GetData(lAddressMap, socketName, GSocketUnix_MapEqual);
	int lOk = closesocket(*lSocket);
	if(lOk == SOCKET_ERROR) {GConsole()->Print(" [ GSocketWindows ] Error GSocketUnix_Close: %d\n", WSAGetLastError()); exit(0);}
	free(lSocket);
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
