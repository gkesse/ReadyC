//===============================================
#include "GSocket2Win.h"
#include "GConsole.h"
#include "GString2.h"
//===============================================
#if defined(_GUSE_SOCKET_ON_)
//===============================================
typedef char* GCHAR_PTR;
typedef WSADATA* GWSADATA_PTR;
typedef SOCKET* GSOCKET_PTR;
typedef SOCKADDR_IN* GSOCKADDR_IN_PTR;
//===============================================
GDECLARE_MAP(GCHAR_PTR, GWSADATA_PTR, GSocket2Win_GCHAR_PTR_GWSADATA_PTR)
GDEFINE_MAP(GCHAR_PTR, GWSADATA_PTR, GSocket2Win_GCHAR_PTR_GWSADATA_PTR)
//===============================================
GDECLARE_MAP(GCHAR_PTR, GSOCKET_PTR, GSocket2Win_GCHAR_PTR_GSOCKET_PTR)
GDEFINE_MAP(GCHAR_PTR, GSOCKET_PTR, GSocket2Win_GCHAR_PTR_GSOCKET_PTR)
//===============================================
GDECLARE_MAP(GCHAR_PTR, GSOCKADDR_IN_PTR, GSocket2Win_GCHAR_PTR_GSOCKADDR_IN_PTR)
GDEFINE_MAP(GCHAR_PTR, GSOCKADDR_IN_PTR, GSocket2Win_GCHAR_PTR_GSOCKADDR_IN_PTR)
//===============================================
static GSocket2O* m_GSocket2WinO = 0;
//===============================================
static void GSocket2Win_MallocData(char* dataName);
static void GSocket2Win_MallocAddress(char* addressName);
static void GSocket2Win_MallocSocket(char* socketName);
static void GSocket2Win_Start(char* dataName, int major, int minor);
static void GSocket2Win_Status(char* dataName);
static void GSocket2Win_Major(char* dataName);
static void GSocket2Win_Minor(char* dataName);
static void GSocket2Win_MajorMax(char* dataName);
static void GSocket2Win_MinorMax(char* dataName);
static void GSocket2Win_AddressInt(char* addressName, int family, int address, int port);
static void GSocket2Win_AddressChar(char* addressName, int family, char* address, int port);
static void GSocket2Win_Socket(char* socketName, int family, int type, int protocol);
static void GSocket2Win_SocketName(char* socketName, char* addressName);
static void GSocket2Win_AddressIp(char* addressName);
static void GSocket2Win_Port(char* socketName);
static void GSocket2Win_Bind(char* socketName, char* addressName);
static void GSocket2Win_Listen(char* socketName, int backlog);
static void GSocket2Win_Accept(char* serverSocket, char* clientSocket, char* clientAddress);
static void GSocket2Win_Connect(char* socketName, char* addressName);
static void GSocket2Win_Send(char* socketName, char* message, int size);
static void GSocket2Win_Recv(char* socketName, char* message, int size);
static void GSocket2Win_Close(char* socketName);
static void GSocket2Win_Clean();
static void GSocket2Win_FreeData(char* datatName);
static void GSocket2Win_FreeSocket(char* socketName);
static void GSocket2Win_FreeAddress(char* addressName);
//===============================================
static int GSocket2Win_MapEqual(char* key1, char* key2);
//===============================================
GSocket2O* GSocket2Win_New() {
	GSocket2O* lParent = GSocket2_New();
	GSocket2WinO* lChild = (GSocket2WinO*)malloc(sizeof(GSocket2WinO));

	lChild->m_parent = lParent;
	lChild->m_dataMap = GMap_New_GSocket2Win_GCHAR_PTR_GWSADATA_PTR();
	lChild->m_socketMap = GMap_New_GSocket2Win_GCHAR_PTR_GSOCKET_PTR();
	lChild->m_addressMap = GMap_New_GSocket2Win_GCHAR_PTR_GSOCKADDR_IN_PTR();

	lParent->m_child = lChild;
	lParent->Delete = GSocket2Win_Delete;
	lParent->MallocData = GSocket2Win_MallocData;
	lParent->MallocAddress = GSocket2Win_MallocAddress;
	lParent->MallocSocket = GSocket2Win_MallocSocket;
	lParent->Start = GSocket2Win_Start;
	lParent->Status = GSocket2Win_Status;
	lParent->Major = GSocket2Win_Major;
	lParent->Minor = GSocket2Win_Minor;
	lParent->MajorMax = GSocket2Win_MajorMax;
	lParent->MinorMax = GSocket2Win_MinorMax;
	lParent->Socket = GSocket2Win_Socket;
	lParent->AddressInt = GSocket2Win_AddressInt;
	lParent->AddressChar = GSocket2Win_AddressChar;
	lParent->SocketName = GSocket2Win_SocketName;
	lParent->AddressIp = GSocket2Win_AddressIp;
	lParent->Port = GSocket2Win_Port;
	lParent->Bind = GSocket2Win_Bind;
	lParent->Listen = GSocket2Win_Listen;
	lParent->Accept = GSocket2Win_Accept;
	lParent->Connect = GSocket2Win_Connect;
	lParent->Send = GSocket2Win_Send;
	lParent->Recv = GSocket2Win_Recv;
	lParent->Close = GSocket2Win_Close;
	lParent->Clean = GSocket2Win_Clean;
	lParent->FreeData = GSocket2Win_FreeData;
	lParent->FreeSocket = GSocket2Win_FreeSocket;
	lParent->FreeAddress = GSocket2Win_FreeAddress;
	return lParent;
}
//===============================================
void GSocket2Win_Delete(GSocket2O* obj) {
	GSocket2_Delete(obj);
	m_GSocket2WinO = 0;
}
//===============================================
GSocket2O* GSocket2Win() {
	if(m_GSocket2WinO == 0) {
		m_GSocket2WinO = GSocket2Win_New();
	}
	return m_GSocket2WinO;
}
//===============================================
static void GSocket2Win_MallocData(char* dataName) {
	GSocket2WinO* lSocketWindows = m_GSocket2WinO->m_child;
	GMapO(GSocket2Win_GCHAR_PTR_GWSADATA_PTR)* lDataMap = lSocketWindows->m_dataMap;
	WSADATA* lData = (WSADATA*)malloc(sizeof(WSADATA));
	if(lData == 0) {GConsole()->Print("[ GSocket2Win ] Error GSocket2Win_MallocData\n"); exit(0);}
	lDataMap->SetData(lDataMap, dataName, lData, GSocket2Win_MapEqual);
}
//===============================================
static void GSocket2Win_MallocAddress(char* addressName) {
	GSocket2WinO* lSocketWindows = m_GSocket2WinO->m_child;
	GMapO(GSocket2Win_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKADDR_IN* lAddress = (SOCKADDR_IN*)malloc(sizeof(SOCKADDR_IN));
	lAddressMap->SetData(lAddressMap, addressName, lAddress, GSocket2Win_MapEqual);
}
//===============================================
static void GSocket2Win_Start(char* dataName, int major, int minor) {
	GSocket2WinO* lSocketWindows = m_GSocket2WinO->m_child;
	GMapO(GSocket2Win_GCHAR_PTR_GWSADATA_PTR)* lDataMap = lSocketWindows->m_dataMap;
	WSADATA* lData = lDataMap->GetData(lDataMap, dataName, GSocket2Win_MapEqual);
	int lOk = WSAStartup(MAKEWORD(major, minor), lData);
	if(lOk != 0) {GConsole()->Print("[ GSocket2Win ] Error GSocket2Win_Start: %d\n", WSAGetLastError()); exit(0);}
}
//===============================================
static void GSocket2Win_Status(char* dataName) {
	GSocket2WinO* lSocketWindows = m_GSocket2WinO->m_child;
	GMapO(GSocket2Win_GCHAR_PTR_GWSADATA_PTR)* lDataMap = lSocketWindows->m_dataMap;
	WSADATA* lData = lDataMap->GetData(lDataMap, dataName, GSocket2Win_MapEqual);
	char* lStatus = lData->szSystemStatus;
	GConsole()->Print("[ GSocket2Win ] Status: %s\n", lStatus);
}
//===============================================
static void GSocket2Win_Major(char* dataName) {
	GSocket2WinO* lSocketWindows = m_GSocket2WinO->m_child;
	GMapO(GSocket2Win_GCHAR_PTR_GWSADATA_PTR)* lDataMap = lSocketWindows->m_dataMap;
	WSADATA* lData = lDataMap->GetData(lDataMap, dataName, GSocket2Win_MapEqual);
	int lMajor = LOBYTE(lData->wVersion);
	GConsole()->Print("[ GSocket2Win ] Version Major: %d\n", lMajor);
}
//===============================================
static void GSocket2Win_Minor(char* dataName) {
	GSocket2WinO* lSocketWindows = m_GSocket2WinO->m_child;
	GMapO(GSocket2Win_GCHAR_PTR_GWSADATA_PTR)* lDataMap = lSocketWindows->m_dataMap;
	WSADATA* lData = lDataMap->GetData(lDataMap, dataName, GSocket2Win_MapEqual);
	int lMinor = HIBYTE(lData->wVersion);
	GConsole()->Print("[ GSocket2Win ] Version Minor: %d\n", lMinor);
}
//===============================================
static void GSocket2Win_MajorMax(char* dataName) {
	GSocket2WinO* lSocketWindows = m_GSocket2WinO->m_child;
	GMapO(GSocket2Win_GCHAR_PTR_GWSADATA_PTR)* lDataMap = lSocketWindows->m_dataMap;
	WSADATA* lData = lDataMap->GetData(lDataMap, dataName, GSocket2Win_MapEqual);
	int lMajor = LOBYTE(lData->wHighVersion);
	GConsole()->Print("[ GSocket2Win ] Version Major Max: %d\n", lMajor);
}
//===============================================
static void GSocket2Win_MinorMax(char* dataName) {
	GSocket2WinO* lSocketWindows = m_GSocket2WinO->m_child;
	GMapO(GSocket2Win_GCHAR_PTR_GWSADATA_PTR)* lDataMap = lSocketWindows->m_dataMap;
	WSADATA* lData = lDataMap->GetData(lDataMap, dataName, GSocket2Win_MapEqual);
	int lMinor = HIBYTE(lData->wHighVersion);
	GConsole()->Print("[ GSocket2Win ] Version Minor Max: %d\n", lMinor);
}
//===============================================
static void GSocket2Win_AddressInt(char* addressName, int family, int address, int port) {
	GSocket2WinO* lSocketWindows = m_GSocket2WinO->m_child;
	GMapO(GSocket2Win_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKADDR_IN* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocket2Win_MapEqual);
	lAddress->sin_family = family;
	lAddress->sin_addr.s_addr = htonl(address);
	lAddress->sin_port = htons(port);
}
//===============================================
static void GSocket2Win_AddressChar(char* addressName, int family, char* address, int port) {
	GSocket2WinO* lSocketWindows = m_GSocket2WinO->m_child;
	GMapO(GSocket2Win_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKADDR_IN* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocket2Win_MapEqual);
	lAddress->sin_family = family;
	lAddress->sin_addr.s_addr = inet_addr(address);
	lAddress->sin_port = htons(port);
}
//===============================================
static void GSocket2Win_MallocSocket(char* socketName) {
	GSocket2WinO* lSocketWindows = m_GSocket2WinO->m_child;
	GMapO(GSocket2Win_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	SOCKET* lSocket = (SOCKET*)malloc(sizeof(SOCKET));
	if(lSocket == 0) {GConsole()->Print("[ GSocket2Win ] Error GSocket2Win_MallocSocket\n"); exit(0);}
	lSocketMap->SetData(lSocketMap, socketName, lSocket, GSocket2Win_MapEqual);
}
//===============================================
static void GSocket2Win_Socket(char* socketName, int family, int type, int protocol) {
	GSocket2WinO* lSocketWindows = m_GSocket2WinO->m_child;
	GMapO(GSocket2Win_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Win_MapEqual);
	*lSocket = socket(family, type, protocol);
	if(*lSocket == INVALID_SOCKET) {GConsole()->Print("[ GSocket2Win ] Error GSocket2Win_Socket2: %d\n", WSAGetLastError()); exit(0);}
}
//===============================================
static void GSocket2Win_SocketName(char* socketName, char* addressName) {
	GSocket2WinO* lSocketWindows = m_GSocket2WinO->m_child;
	GMapO(GSocket2Win_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	GMapO(GSocket2Win_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Win_MapEqual);
	SOCKADDR_IN* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocket2Win_MapEqual);
	int lSize = sizeof(*lAddress);
	int lOk = getsockname(*lSocket, (SOCKADDR*)lAddress, &lSize);
	if(lOk == SOCKET_ERROR) {GConsole()->Print("[ GSocket2Win ] Error GSocket2Win_SocketName: %d\n", WSAGetLastError()); exit(0);}
}
//===============================================
static void GSocket2Win_AddressIp(char* addressName) {
	GSocket2WinO* lSocketWindows = m_GSocket2WinO->m_child;
	GMapO(GSocket2Win_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKADDR_IN* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocket2Win_MapEqual);
	char* lIpAddress = inet_ntoa(lAddress->sin_addr);
	GConsole()->Print("[ GSocket2Win ] Address IP: %s\n", lIpAddress);
}
//===============================================
static void GSocket2Win_Port(char* addressName) {
	GSocket2WinO* lSocketWindows = m_GSocket2WinO->m_child;
	GMapO(GSocket2Win_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKADDR_IN* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocket2Win_MapEqual);
	int lPort = htons(lAddress->sin_port);
	GConsole()->Print("[ GSocket2Win ] Port: %d\n", lPort);
}
//===============================================
static void GSocket2Win_Bind(char* socketName, char* addressName) {
	GSocket2WinO* lSocketWindows = m_GSocket2WinO->m_child;
	GMapO(GSocket2Win_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	GMapO(GSocket2Win_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Win_MapEqual);
	SOCKADDR_IN* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocket2Win_MapEqual);
	int lSize = sizeof(*lAddress);
	int lOk = bind(*lSocket, (SOCKADDR*)lAddress, lSize);
	if(lOk == SOCKET_ERROR) {GConsole()->Print("[ GSocket2Win ] Error GSocket2Win_Bind: %d\n", WSAGetLastError()); exit(0);}
}
//===============================================
static void GSocket2Win_Listen(char* socketName, int backlog) {
	GSocket2WinO* lSocketWindows = m_GSocket2WinO->m_child;
	GMapO(GSocket2Win_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Win_MapEqual);
	int lOk = listen(*lSocket, backlog);
	if(lOk == SOCKET_ERROR) {GConsole()->Print("[ GSocket2Win ] Error GSocket2Win_Listen: %d\n", WSAGetLastError()); exit(0);}
}
//===============================================
static void GSocket2Win_Accept(char* serverSocket, char* clientSocket, char* clientAddress) {
	GSocket2WinO* lSocketWindows = m_GSocket2WinO->m_child;
	GMapO(GSocket2Win_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	GMapO(GSocket2Win_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKET* lServerSocket = lSocketMap->GetData(lSocketMap, serverSocket, GSocket2Win_MapEqual);
	SOCKET* lClientSocket = lSocketMap->GetData(lSocketMap, clientSocket, GSocket2Win_MapEqual);
	SOCKADDR_IN* lClientAddress = lAddressMap->GetData(lAddressMap, clientAddress, GSocket2Win_MapEqual);
	int lClientSize = sizeof(*lClientAddress);
	*lClientSocket = accept(*lServerSocket, (SOCKADDR*)lClientAddress, &lClientSize);
	if(*lClientSocket == INVALID_SOCKET) {GConsole()->Print("[ GSocket2Win ] Error GSocket2Win_Accept: %d\n", WSAGetLastError()); exit(0);}
}
//===============================================
static void GSocket2Win_Connect(char* socketName, char* addressName) {
	GSocket2WinO* lSocketWindows = m_GSocket2WinO->m_child;
	GMapO(GSocket2Win_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	GMapO(GSocket2Win_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Win_MapEqual);
	SOCKADDR_IN* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocket2Win_MapEqual);
	int lSize = sizeof(*lAddress);
	int lOk = connect(*lSocket, (SOCKADDR*)lAddress, lSize);
	if(lOk == SOCKET_ERROR) {GConsole()->Print("[ GSocket2Win ] Error GSocket2Win_Connect: %d\n", WSAGetLastError()); exit(0);}
}
//===============================================
static void GSocket2Win_Send(char* socketName, char* message, int size) {
	GSocket2WinO* lSocketWindows = m_GSocket2WinO->m_child;
	GMapO(GSocket2Win_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Win_MapEqual);
	int lSize = size;
	if(lSize <= 0) lSize = strlen(message);
	int lBytes = send(*lSocket, message, lSize, 0);
	if(lBytes == SOCKET_ERROR) {GConsole()->Print("[ GSocket2Win ] Error GSocket2Win_Send: %d\n", WSAGetLastError()); exit(0);}
}
//===============================================
static void GSocket2Win_Recv(char* socketName, char* message, int size) {
	GSocket2WinO* lSocketWindows = m_GSocket2WinO->m_child;
	GMapO(GSocket2Win_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Win_MapEqual);
	int lSize = size;
	if(lSize <= 0) lSize = strlen(message);
	int lBytes = recv(*lSocket, message, lSize, 0);
	if(lBytes == SOCKET_ERROR) {GConsole()->Print("[ GSocket2Win ] Error GSocket2Win_Recv: %d\n", WSAGetLastError()); exit(0);}
	message[lBytes] = 0;
}
//===============================================
static void GSocket2Win_Close(char* socketName) {
	GSocket2WinO* lSocketWindows = m_GSocket2WinO->m_child;
	GMapO(GSocket2Win_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Win_MapEqual);
	int lOk = closesocket(*lSocket);
	if(lOk == SOCKET_ERROR) {GConsole()->Print("[ GSocket2Win ] Error GSocket2Win_Close: %d\n", WSAGetLastError()); exit(0);}
}
//===============================================
static void GSocket2Win_Clean() {
	WSACleanup();
}
//===============================================
static void GSocket2Win_FreeData(char* dataName) {
	GSocket2WinO* lSocketWindows = m_GSocket2WinO->m_child;
	GMapO(GSocket2Win_GCHAR_PTR_GWSADATA_PTR)* lDataMap = lSocketWindows->m_dataMap;
	WSADATA* lData = lDataMap->GetData(lDataMap, dataName, GSocket2Win_MapEqual);
	free(lData);
}
//===============================================
static void GSocket2Win_FreeSocket(char* socketName) {
	GSocket2WinO* lSocketWindows = m_GSocket2WinO->m_child;
	GMapO(GSocket2Win_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Win_MapEqual);
	free(lSocket);
}
//===============================================
static void GSocket2Win_FreeAddress(char* addressName) {
	GSocket2WinO* lSocketWindows = m_GSocket2WinO->m_child;
	GMapO(GSocket2Win_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKADDR_IN* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocket2Win_MapEqual);
	free(lAddress);
}
//===============================================
static int GSocket2Win_MapEqual(char* key1, char* key2) {
    int lStrcmp = strcmp(key1, key2);
    if(lStrcmp == 0) return TRUE;
    return FALSE;
}
//===============================================
#endif
//===============================================
