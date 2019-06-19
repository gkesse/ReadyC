//===============================================
#include "GSocketWindows.h"
#include "GString.h"
#include "GConsole.h"
//===============================================
#if defined(__WIN32)
typedef char* GCHAR_PTR;
typedef WSADATA* GWSADATA_PTR;
typedef SOCKET* GSOCKET_PTR;
typedef SOCKADDR_IN* GSOCKADDR_IN_PTR;
//===============================================
GDECLARE_MAP(GCHAR_PTR, GWSADATA_PTR, GSocketWindows_GCHAR_PTR_GWSADATA_PTR)
GDEFINE_MAP(GCHAR_PTR, GWSADATA_PTR, GSocketWindows_GCHAR_PTR_GWSADATA_PTR)
//===============================================
GDECLARE_MAP(GCHAR_PTR, GSOCKET_PTR, GSocketWindows_GCHAR_PTR_GSOCKET_PTR)
GDEFINE_MAP(GCHAR_PTR, GSOCKET_PTR, GSocketWindows_GCHAR_PTR_GSOCKET_PTR)
//===============================================
GDECLARE_MAP(GCHAR_PTR, GSOCKADDR_IN_PTR, GSocketWindows_GCHAR_PTR_GSOCKADDR_IN_PTR)
GDEFINE_MAP(GCHAR_PTR, GSOCKADDR_IN_PTR, GSocketWindows_GCHAR_PTR_GSOCKADDR_IN_PTR)
#endif
//===============================================
static GSocketO* m_GSocketWindowsO = 0;
//===============================================
static void GSocketWindows_WsaData(char* dataName);
static void GSocketWindows_Start(char* dataName, int major, int minor);
static void GSocketWindows_Status(char* dataName);
static void GSocketWindows_Major(char* dataName);
static void GSocketWindows_Minor(char* dataName);
static void GSocketWindows_MajorMax(char* dataName);
static void GSocketWindows_MinorMax(char* dataName);
static void GSocketWindows_Address(char* addressName);
static void GSocketWindows_Address2(char* addressName, int family, int address, int port);
static void GSocketWindows_Socket(char* socketName);
static void GSocketWindows_Socket2(char* socketName, int family, int type, int protocol);
static void GSocketWindows_SocketName(char* socketName, char* addressName);
static void GSocketWindows_AddressIp(char* addressName);
static void GSocketWindows_Port(char* socketName);
static void GSocketWindows_Bind(char* socketName, char* addressName);
static void GSocketWindows_Listen(char* socketName, int backlog);
static void GSocketWindows_Accept(char* socketName, char* clientName);
static void GSocketWindows_Connect(char* socketName, char* addressName);
static void GSocketWindows_Send(char* socketName, char* message, int size);
static void GSocketWindows_Recv(char* socketName, char* message, int size);
static void GSocketWindows_Close(char* socketName);
static void GSocketWindows_Clean(char* datatName);
static void GSocketWindows_Clean2(char* socketName);
static void GSocketWindows_Clean3(char* addressName);
//===============================================
#if defined(__WIN32)
static int GSocketWindows_MapEqual(char* key1, char* key2);
#endif
//===============================================
GSocketO* GSocketWindows_New() {
	GSocketO* lParent = GSocket_New();
	GSocketWindowsO* lChild = (GSocketWindowsO*)malloc(sizeof(GSocketWindowsO));

	lChild->m_parent = lParent;
#if defined(__WIN32)
	lChild->m_wsaDataMap = GMap_New_GSocketWindows_GCHAR_PTR_GWSADATA_PTR();
	lChild->m_socketMap = GMap_New_GSocketWindows_GCHAR_PTR_GSOCKET_PTR();
	lChild->m_addressMap = GMap_New_GSocketWindows_GCHAR_PTR_GSOCKADDR_IN_PTR();
#endif

	lParent->m_child = lChild;
	lParent->Delete = GSocketWindows_Delete;
	lParent->WsaData = GSocketWindows_WsaData;
	lParent->Start = GSocketWindows_Start;
	lParent->Status = GSocketWindows_Status;
	lParent->Major = GSocketWindows_Major;
	lParent->Minor = GSocketWindows_Minor;
	lParent->MajorMax = GSocketWindows_MajorMax;
	lParent->MinorMax = GSocketWindows_MinorMax;
	lParent->Socket = GSocketWindows_Socket;
	lParent->Socket2 = GSocketWindows_Socket2;
	lParent->SocketName = GSocketWindows_SocketName;
	lParent->AddressIp = GSocketWindows_AddressIp;
	lParent->Port = GSocketWindows_Port;
	lParent->Address = GSocketWindows_Address;
	lParent->Address2 = GSocketWindows_Address2;
	lParent->Bind = GSocketWindows_Bind;
	lParent->Listen = GSocketWindows_Listen;
	lParent->Accept = GSocketWindows_Accept;
	lParent->Connect = GSocketWindows_Connect;
	lParent->Send = GSocketWindows_Send;
	lParent->Recv = GSocketWindows_Recv;
	lParent->Close = GSocketWindows_Close;
	lParent->Clean = GSocketWindows_Clean;
	lParent->Clean2 = GSocketWindows_Clean2;
	lParent->Clean3 = GSocketWindows_Clean3;
	return lParent;
}
//===============================================
void GSocketWindows_Delete(GSocketO* obj) {
	GSocket_Delete(obj);
	m_GSocketWindowsO = 0;
}
//===============================================
GSocketO* GSocketWindows() {
	if(m_GSocketWindowsO == 0) {
		m_GSocketWindowsO = GSocketWindows_New();
	}
	return m_GSocketWindowsO;
}
//===============================================
static void GSocketWindows_WsaData(char* dataName) {
#if defined(__WIN32)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketWindows_GCHAR_PTR_GWSADATA_PTR)* lWsaDataMap = lSocketWindows->m_wsaDataMap;
	WSADATA* lWsaData = (WSADATA*)malloc(sizeof(WSADATA));
	lWsaDataMap->SetData(lWsaDataMap, dataName, lWsaData, GSocketWindows_MapEqual);
#endif
}
//===============================================
static void GSocketWindows_Start(char* dataName, int major, int minor) {
#if defined(__WIN32)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketWindows_GCHAR_PTR_GWSADATA_PTR)* lWsaDataMap = lSocketWindows->m_wsaDataMap;
	WSADATA* lWsaData = lWsaDataMap->GetData(lWsaDataMap, dataName, GSocketWindows_MapEqual);
	int lOk = WSAStartup(MAKEWORD(major, minor), lWsaData);
	if(lOk != 0) {GConsole()->Print(" [ GSocketWindows ] Error GSocketWindows_Start: %d\n", WSAGetLastError()); exit(0);}
#endif
}
//===============================================
static void GSocketWindows_Status(char* dataName) {
#if defined(__WIN32)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketWindows_GCHAR_PTR_GWSADATA_PTR)* lWsaDataMap = lSocketWindows->m_wsaDataMap;
	WSADATA* lWsaData = lWsaDataMap->GetData(lWsaDataMap, dataName, GSocketWindows_MapEqual);
	char* lStatus = lWsaData->szSystemStatus;
	GConsole()->Print("[ GSocketWindows ] Status: %s\n", lStatus);
#endif
}
//===============================================
static void GSocketWindows_Major(char* dataName) {
#if defined(__WIN32)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketWindows_GCHAR_PTR_GWSADATA_PTR)* lWsaDataMap = lSocketWindows->m_wsaDataMap;
	WSADATA* lWsaData = lWsaDataMap->GetData(lWsaDataMap, dataName, GSocketWindows_MapEqual);
	int lMajor = LOBYTE(lWsaData->wVersion);
	GConsole()->Print("[ GSocketWindows ] Version Major: %s\n", lMajor);
#endif
}
//===============================================
static void GSocketWindows_Minor(char* dataName) {
#if defined(__WIN32)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketWindows_GCHAR_PTR_GWSADATA_PTR)* lWsaDataMap = lSocketWindows->m_wsaDataMap;
	WSADATA* lWsaData = lWsaDataMap->GetData(lWsaDataMap, dataName, GSocketWindows_MapEqual);
	int lMinor = HIBYTE(lWsaData->wVersion);
	GConsole()->Print("[ GSocketWindows ] Version Minor: %s\n", lMinor);
#endif
}
//===============================================
static void GSocketWindows_MajorMax(char* dataName) {
#if defined(__WIN32)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketWindows_GCHAR_PTR_GWSADATA_PTR)* lWsaDataMap = lSocketWindows->m_wsaDataMap;
	WSADATA* lWsaData = lWsaDataMap->GetData(lWsaDataMap, dataName, GSocketWindows_MapEqual);
	int lMajor = LOBYTE(lWsaData->wHighVersion);
	GConsole()->Print("[ GSocketWindows ] Version Major Max: %s\n", lMajor);
#endif
}
//===============================================
static void GSocketWindows_MinorMax(char* dataName) {
#if defined(__WIN32)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketWindows_GCHAR_PTR_GWSADATA_PTR)* lWsaDataMap = lSocketWindows->m_wsaDataMap;
	WSADATA* lWsaData = lWsaDataMap->GetData(lWsaDataMap, dataName, GSocketWindows_MapEqual);
	int lMinor = HIBYTE(lWsaData->wHighVersion);
	GConsole()->Print("[ GSocketWindows ] Version Minor Max: %s\n", lMinor);
#endif
}
//===============================================
static void GSocketWindows_Address(char* addressName) {
#if defined(__WIN32)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketWindows_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKADDR_IN* lAddress = (SOCKADDR_IN*)malloc(sizeof(SOCKADDR_IN));
	lAddressMap->SetData(lAddressMap, addressName, lAddress, GSocketWindows_MapEqual);
#endif
}
//===============================================
static void GSocketWindows_Address2(char* addressName, int family, int address, int port) {
#if defined(__WIN32)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketWindows_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKADDR_IN* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocketWindows_MapEqual);
	lAddress->sin_addr.s_addr = htonl(address);
	lAddress->sin_family = family;
	lAddress->sin_port = htons(port);
#endif
}
//===============================================
static void GSocketWindows_Socket(char* socketName) {
#if defined(__WIN32)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketWindows_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	SOCKET* lSocket = (SOCKET*)malloc(sizeof(SOCKET));
	lSocketMap->SetData(lSocketMap, socketName, lSocket, GSocketWindows_MapEqual);
#endif
}
//===============================================
static void GSocketWindows_Socket2(char* socketName, int family, int type, int protocol) {
#if defined(__WIN32)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketWindows_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocketWindows_MapEqual);
	*lSocket = socket(family, type, protocol);
	if(*lSocket == INVALID_SOCKET) {GConsole()->Print(" [ GSocketWindows ] Error GSocketWindows_Socket2: %d\n", WSAGetLastError()); exit(0);}
#endif
}
//===============================================
static void GSocketWindows_SocketName(char* socketName, char* addressName) {
#if defined(__WIN32)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketWindows_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	GMapO(GSocketWindows_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocketWindows_MapEqual);
	SOCKADDR_IN* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocketWindows_MapEqual);
	int lSize = sizeof(*lAddress);
	int lOk = getsockname(*lSocket, (SOCKADDR*)lAddress, &lSize);
	if(lOk == SOCKET_ERROR) {GConsole()->Print(" [ GSocketWindows ] Error GSocketWindows_SocketName: %d\n", WSAGetLastError()); exit(0);}
#endif
}
//===============================================
static void GSocketWindows_AddressIp(char* addressName) {
#if defined(__WIN32)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketWindows_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKADDR_IN* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocketWindows_MapEqual);
	char* lIpAddress = inet_ntoa(lAddress->sin_addr);
	GConsole()->Print(" [ GSocketWindows ] Address IP: %s\n", lIpAddress);
#endif
}
//===============================================
static void GSocketWindows_Port(char* addressName) {
#if defined(__WIN32)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketWindows_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKADDR_IN* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocketWindows_MapEqual);
	int lPort = htons(lAddress->sin_port);
	GConsole()->Print(" [ GSocketWindows ] Port: %s\n", lPort);
#endif
}
//===============================================
static void GSocketWindows_Bind(char* socketName, char* addressName) {
#if defined(__WIN32)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketWindows_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	GMapO(GSocketWindows_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocketWindows_MapEqual);
	SOCKADDR_IN* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocketWindows_MapEqual);
	int lSize = sizeof(*lAddress);
	int lOk = bind(*lSocket, (SOCKADDR*)lAddress, lSize);
	if(lOk == SOCKET_ERROR) {GConsole()->Print(" [ GSocketWindows ] Error GSocketWindows_Bind: %d\n", WSAGetLastError()); exit(0);}
#endif
}
//===============================================
static void GSocketWindows_Listen(char* socketName, int backlog) {
#if defined(__WIN32)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketWindows_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocketWindows_MapEqual);
	int lOk = listen(*lSocket, backlog);
	if(lOk == SOCKET_ERROR) {GConsole()->Print(" [ GSocketWindows ] Error GSocketWindows_Listen: %d\n", WSAGetLastError()); exit(0);}
#endif
}
//===============================================
static void GSocketWindows_Accept(char* socketName, char* clientName) {
#if defined(__WIN32)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketWindows_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	GMapO(GSocketWindows_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocketWindows_MapEqual);
	SOCKET* lSocket2 = lSocketMap->GetData(lSocketMap, clientName, GSocketWindows_MapEqual);
	SOCKADDR_IN* lAddress2 = lAddressMap->GetData(lAddressMap, clientName, GSocketWindows_MapEqual);
	int lSize2 = sizeof(*lAddress2);
	*lSocket2 = accept(*lSocket, (SOCKADDR*)lAddress2, &lSize2);
	if(*lSocket2 == INVALID_SOCKET) {GConsole()->Print(" [ GSocketWindows ] Error GSocketWindows_Accept: %d\n", WSAGetLastError()); exit(0);}
#endif
}
//===============================================
static void GSocketWindows_Connect(char* socketName, char* addressName) {
#if defined(__WIN32)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketWindows_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	GMapO(GSocketWindows_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocketWindows_MapEqual);
	SOCKADDR_IN* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocketWindows_MapEqual);
	int lSize = sizeof(*lAddress);
	int lOk = connect(*lSocket, (SOCKADDR*)lAddress, lSize);
	if(lOk == SOCKET_ERROR) {GConsole()->Print(" [ GSocketWindows ] Error GSocketWindows_Connect: %d\n", WSAGetLastError()); exit(0);}
#endif
}
//===============================================
static void GSocketWindows_Send(char* socketName, char* message, int size) {
#if defined(__WIN32)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketWindows_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocketWindows_MapEqual);
	int lSize = size;
	if(lSize <= 0) lSize = strlen(message);
	int lBytes = send(*lSocket, message, lSize, 0);
	if(lBytes == SOCKET_ERROR) {GConsole()->Print(" [ GSocketWindows ] Error GSocketWindows_Send: %d\n", WSAGetLastError()); exit(0);}
#endif
}
//===============================================
static void GSocketWindows_Recv(char* socketName, char* message, int size) {
#if defined(__WIN32)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketWindows_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocketWindows_MapEqual);
	int lSize = size;
	if(lSize <= 0) lSize = strlen(message);
	int lBytes = recv(*lSocket, message, lSize, 0);
	if(lBytes == SOCKET_ERROR) {GConsole()->Print(" [ GSocketWindows ] Error GSocketWindows_Recv: %d\n", WSAGetLastError()); exit(0);}
	message[lBytes] = 0;
#endif
}
//===============================================
static void GSocketWindows_Close(char* socketName) {
#if defined(__WIN32)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketWindows_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	GMapO(GSocketWindows_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocketWindows_MapEqual);
	SOCKADDR_IN* lAddress = lAddressMap->GetData(lAddressMap, socketName, GSocketWindows_MapEqual);
	int lOk = closesocket(*lSocket);
	if(lOk == SOCKET_ERROR) {GConsole()->Print(" [ GSocketWindows ] Error GSocketWindows_Close: %d\n", WSAGetLastError()); exit(0);}
#endif
}
//===============================================
static void GSocketWindows_Clean(char* dataName) {
#if defined(__WIN32)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketWindows_GCHAR_PTR_GWSADATA_PTR)* lWsaDataMap = lSocketWindows->m_wsaDataMap;
	WSADATA* lWsaData = lWsaDataMap->GetData(lWsaDataMap, dataName, GSocketWindows_MapEqual);
	WSACleanup();
	free(lWsaData);
#endif
}
//===============================================
static void GSocketWindows_Clean2(char* socketName) {
#if defined(__WIN32)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketWindows_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocketWindows_MapEqual);
	free(lSocket);
#endif
}
//===============================================
static void GSocketWindows_Clean3(char* addressName) {
#if defined(__WIN32)
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	GMapO(GSocketWindows_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKADDR_IN* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocketWindows_MapEqual);
	free(lAddress);
#endif
}
//===============================================
#if defined(__WIN32)
static int GSocketWindows_MapEqual(char* key1, char* key2) {
    int lStrcmp = strcmp(key1, key2);
    if(lStrcmp == 0) return TRUE;
    return FALSE;
}
#endif
//===============================================
