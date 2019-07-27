//===============================================
#include "GSocket2Windows.h"
#include "GConsole.h"
#include "GString2.h"
//===============================================
#if defined(__WIN32)
typedef char* GCHAR_PTR;
typedef WSADATA* GWSADATA_PTR;
typedef SOCKET* GSOCKET_PTR;
typedef SOCKADDR_IN* GSOCKADDR_IN_PTR;
//===============================================
GDECLARE_MAP(GCHAR_PTR, GWSADATA_PTR, GSocket2Windows_GCHAR_PTR_GWSADATA_PTR)
GDEFINE_MAP(GCHAR_PTR, GWSADATA_PTR, GSocket2Windows_GCHAR_PTR_GWSADATA_PTR)
//===============================================
GDECLARE_MAP(GCHAR_PTR, GSOCKET_PTR, GSocket2Windows_GCHAR_PTR_GSOCKET_PTR)
GDEFINE_MAP(GCHAR_PTR, GSOCKET_PTR, GSocket2Windows_GCHAR_PTR_GSOCKET_PTR)
//===============================================
GDECLARE_MAP(GCHAR_PTR, GSOCKADDR_IN_PTR, GSocket2Windows_GCHAR_PTR_GSOCKADDR_IN_PTR)
GDEFINE_MAP(GCHAR_PTR, GSOCKADDR_IN_PTR, GSocket2Windows_GCHAR_PTR_GSOCKADDR_IN_PTR)
#endif
//===============================================
static GSocket2O* m_GSocket2WindowsO = 0;
//===============================================
static void GSocket2Windows_MallocData(char* dataName);
static void GSocket2Windows_MallocAddress(char* addressName);
static void GSocket2Windows_MallocSocket(char* socketName);
static void GSocket2Windows_Start(char* dataName, int major, int minor);
static void GSocket2Windows_Status(char* dataName);
static void GSocket2Windows_Major(char* dataName);
static void GSocket2Windows_Minor(char* dataName);
static void GSocket2Windows_MajorMax(char* dataName);
static void GSocket2Windows_MinorMax(char* dataName);
static void GSocket2Windows_AddressInt(char* addressName, int family, int address, int port);
static void GSocket2Windows_AddressChar(char* addressName, int family, char* address, int port);
static void GSocket2Windows_Socket(char* socketName, int family, int type, int protocol);
static void GSocket2Windows_SocketName(char* socketName, char* addressName);
static void GSocket2Windows_AddressIp(char* addressName);
static void GSocket2Windows_Port(char* socketName);
static void GSocket2Windows_Bind(char* socketName, char* addressName);
static void GSocket2Windows_Listen(char* socketName, int backlog);
static void GSocket2Windows_Accept(char* serverSocket, char* clientSocket, char* clientAddress);
static void GSocket2Windows_Connect(char* socketName, char* addressName);
static void GSocket2Windows_Send(char* socketName, char* message, int size);
static void GSocket2Windows_Recv(char* socketName, char* message, int size);
static void GSocket2Windows_Close(char* socketName);
static void GSocket2Windows_Clean();
static void GSocket2Windows_FreeData(char* datatName);
static void GSocket2Windows_FreeSocket(char* socketName);
static void GSocket2Windows_FreeAddress(char* addressName);
//===============================================
#if defined(__WIN32)
static int GSocket2Windows_MapEqual(char* key1, char* key2);
#endif
//===============================================
GSocket2O* GSocket2Windows_New() {
	GSocket2O* lParent = GSocket2_New();
	GSocket2WindowsO* lChild = (GSocket2WindowsO*)malloc(sizeof(GSocket2WindowsO));

	lChild->m_parent = lParent;
#if defined(__WIN32)
	lChild->m_dataMap = GMap_New_GSocket2Windows_GCHAR_PTR_GWSADATA_PTR();
	lChild->m_socketMap = GMap_New_GSocket2Windows_GCHAR_PTR_GSOCKET_PTR();
	lChild->m_addressMap = GMap_New_GSocket2Windows_GCHAR_PTR_GSOCKADDR_IN_PTR();
#endif

	lParent->m_child = lChild;
	lParent->Delete = GSocket2Windows_Delete;
	lParent->MallocData = GSocket2Windows_MallocData;
	lParent->MallocAddress = GSocket2Windows_MallocAddress;
	lParent->MallocSocket = GSocket2Windows_MallocSocket;
	lParent->Start = GSocket2Windows_Start;
	lParent->Status = GSocket2Windows_Status;
	lParent->Major = GSocket2Windows_Major;
	lParent->Minor = GSocket2Windows_Minor;
	lParent->MajorMax = GSocket2Windows_MajorMax;
	lParent->MinorMax = GSocket2Windows_MinorMax;
	lParent->Socket = GSocket2Windows_Socket;
	lParent->AddressInt = GSocket2Windows_AddressInt;
	lParent->AddressChar = GSocket2Windows_AddressChar;
	lParent->SocketName = GSocket2Windows_SocketName;
	lParent->AddressIp = GSocket2Windows_AddressIp;
	lParent->Port = GSocket2Windows_Port;
	lParent->Bind = GSocket2Windows_Bind;
	lParent->Listen = GSocket2Windows_Listen;
	lParent->Accept = GSocket2Windows_Accept;
	lParent->Connect = GSocket2Windows_Connect;
	lParent->Send = GSocket2Windows_Send;
	lParent->Recv = GSocket2Windows_Recv;
	lParent->Close = GSocket2Windows_Close;
	lParent->Clean = GSocket2Windows_Clean;
	lParent->FreeData = GSocket2Windows_FreeData;
	lParent->FreeSocket = GSocket2Windows_FreeSocket;
	lParent->FreeAddress = GSocket2Windows_FreeAddress;
	return lParent;
}
//===============================================
void GSocket2Windows_Delete(GSocket2O* obj) {
	GSocket2_Delete(obj);
	m_GSocket2WindowsO = 0;
}
//===============================================
GSocket2O* GSocket2Windows() {
	if(m_GSocket2WindowsO == 0) {
		m_GSocket2WindowsO = GSocket2Windows_New();
	}
	return m_GSocket2WindowsO;
}
//===============================================
static void GSocket2Windows_MallocData(char* dataName) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GWSADATA_PTR)* lDataMap = lSocketWindows->m_dataMap;
	WSADATA* lData = (WSADATA*)malloc(sizeof(WSADATA));
	if(lData == 0) {GConsole()->Print("[ GSocket2Windows ] Error GSocket2Windows_MallocData\n"); exit(0);}
	lDataMap->SetData(lDataMap, dataName, lData, GSocket2Windows_MapEqual);
#endif
}
//===============================================
static void GSocket2Windows_MallocAddress(char* addressName) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKADDR_IN* lAddress = (SOCKADDR_IN*)malloc(sizeof(SOCKADDR_IN));
	lAddressMap->SetData(lAddressMap, addressName, lAddress, GSocket2Windows_MapEqual);
#endif
}
//===============================================
static void GSocket2Windows_Start(char* dataName, int major, int minor) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GWSADATA_PTR)* lDataMap = lSocketWindows->m_dataMap;
	WSADATA* lData = lDataMap->GetData(lDataMap, dataName, GSocket2Windows_MapEqual);
	int lOk = WSAStartup(MAKEWORD(major, minor), lData);
	if(lOk != 0) {GConsole()->Print("[ GSocket2Windows ] Error GSocket2Windows_Start: %d\n", WSAGetLastError()); exit(0);}
#endif
}
//===============================================
static void GSocket2Windows_Status(char* dataName) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GWSADATA_PTR)* lDataMap = lSocketWindows->m_dataMap;
	WSADATA* lData = lDataMap->GetData(lDataMap, dataName, GSocket2Windows_MapEqual);
	char* lStatus = lData->szSystemStatus;
	GConsole()->Print("[ GSocket2Windows ] Status: %s\n", lStatus);
#endif
}
//===============================================
static void GSocket2Windows_Major(char* dataName) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GWSADATA_PTR)* lDataMap = lSocketWindows->m_dataMap;
	WSADATA* lData = lDataMap->GetData(lDataMap, dataName, GSocket2Windows_MapEqual);
	int lMajor = LOBYTE(lData->wVersion);
	GConsole()->Print("[ GSocket2Windows ] Version Major: %d\n", lMajor);
#endif
}
//===============================================
static void GSocket2Windows_Minor(char* dataName) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GWSADATA_PTR)* lDataMap = lSocketWindows->m_dataMap;
	WSADATA* lData = lDataMap->GetData(lDataMap, dataName, GSocket2Windows_MapEqual);
	int lMinor = HIBYTE(lData->wVersion);
	GConsole()->Print("[ GSocket2Windows ] Version Minor: %d\n", lMinor);
#endif
}
//===============================================
static void GSocket2Windows_MajorMax(char* dataName) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GWSADATA_PTR)* lDataMap = lSocketWindows->m_dataMap;
	WSADATA* lData = lDataMap->GetData(lDataMap, dataName, GSocket2Windows_MapEqual);
	int lMajor = LOBYTE(lData->wHighVersion);
	GConsole()->Print("[ GSocket2Windows ] Version Major Max: %d\n", lMajor);
#endif
}
//===============================================
static void GSocket2Windows_MinorMax(char* dataName) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GWSADATA_PTR)* lDataMap = lSocketWindows->m_dataMap;
	WSADATA* lData = lDataMap->GetData(lDataMap, dataName, GSocket2Windows_MapEqual);
	int lMinor = HIBYTE(lData->wHighVersion);
	GConsole()->Print("[ GSocket2Windows ] Version Minor Max: %d\n", lMinor);
#endif
}
//===============================================
static void GSocket2Windows_AddressInt(char* addressName, int family, int address, int port) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKADDR_IN* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocket2Windows_MapEqual);
	lAddress->sin_family = family;
	lAddress->sin_addr.s_addr = htonl(address);
	lAddress->sin_port = htons(port);
#endif
}
//===============================================
static void GSocket2Windows_AddressChar(char* addressName, int family, char* address, int port) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKADDR_IN* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocket2Windows_MapEqual);
	lAddress->sin_family = family;
	lAddress->sin_addr.s_addr = inet_addr(address);
	lAddress->sin_port = htons(port);
#endif
}
//===============================================
static void GSocket2Windows_MallocSocket(char* socketName) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	SOCKET* lSocket = (SOCKET*)malloc(sizeof(SOCKET));
	if(lSocket == 0) {GConsole()->Print("[ GSocket2Windows ] Error GSocket2Windows_MallocSocket\n"); exit(0);}
	lSocketMap->SetData(lSocketMap, socketName, lSocket, GSocket2Windows_MapEqual);
#endif
}
//===============================================
static void GSocket2Windows_Socket(char* socketName, int family, int type, int protocol) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Windows_MapEqual);
	*lSocket = socket(family, type, protocol);
	if(*lSocket == INVALID_SOCKET) {GConsole()->Print("[ GSocket2Windows ] Error GSocket2Windows_Socket2: %d\n", WSAGetLastError()); exit(0);}
#endif
}
//===============================================
static void GSocket2Windows_SocketName(char* socketName, char* addressName) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	GMapO(GSocket2Windows_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Windows_MapEqual);
	SOCKADDR_IN* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocket2Windows_MapEqual);
	int lSize = sizeof(*lAddress);
	int lOk = getsockname(*lSocket, (SOCKADDR*)lAddress, &lSize);
	if(lOk == SOCKET_ERROR) {GConsole()->Print("[ GSocket2Windows ] Error GSocket2Windows_SocketName: %d\n", WSAGetLastError()); exit(0);}
#endif
}
//===============================================
static void GSocket2Windows_AddressIp(char* addressName) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKADDR_IN* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocket2Windows_MapEqual);
	char* lIpAddress = inet_ntoa(lAddress->sin_addr);
	GConsole()->Print("[ GSocket2Windows ] Address IP: %s\n", lIpAddress);
#endif
}
//===============================================
static void GSocket2Windows_Port(char* addressName) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKADDR_IN* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocket2Windows_MapEqual);
	int lPort = htons(lAddress->sin_port);
	GConsole()->Print("[ GSocket2Windows ] Port: %d\n", lPort);
#endif
}
//===============================================
static void GSocket2Windows_Bind(char* socketName, char* addressName) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	GMapO(GSocket2Windows_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Windows_MapEqual);
	SOCKADDR_IN* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocket2Windows_MapEqual);
	int lSize = sizeof(*lAddress);
	int lOk = bind(*lSocket, (SOCKADDR*)lAddress, lSize);
	if(lOk == SOCKET_ERROR) {GConsole()->Print("[ GSocket2Windows ] Error GSocket2Windows_Bind: %d\n", WSAGetLastError()); exit(0);}
#endif
}
//===============================================
static void GSocket2Windows_Listen(char* socketName, int backlog) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Windows_MapEqual);
	int lOk = listen(*lSocket, backlog);
	if(lOk == SOCKET_ERROR) {GConsole()->Print("[ GSocket2Windows ] Error GSocket2Windows_Listen: %d\n", WSAGetLastError()); exit(0);}
#endif
}
//===============================================
static void GSocket2Windows_Accept(char* serverSocket, char* clientSocket, char* clientAddress) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	GMapO(GSocket2Windows_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKET* lServerSocket = lSocketMap->GetData(lSocketMap, serverSocket, GSocket2Windows_MapEqual);
	SOCKET* lClientSocket = lSocketMap->GetData(lSocketMap, clientSocket, GSocket2Windows_MapEqual);
	SOCKADDR_IN* lClientAddress = lAddressMap->GetData(lAddressMap, clientAddress, GSocket2Windows_MapEqual);
	int lClientSize = sizeof(*lClientAddress);
	*lClientSocket = accept(*lServerSocket, (SOCKADDR*)lClientAddress, &lClientSize);
	if(*lClientSocket == INVALID_SOCKET) {GConsole()->Print("[ GSocket2Windows ] Error GSocket2Windows_Accept: %d\n", WSAGetLastError()); exit(0);}
#endif
}
//===============================================
static void GSocket2Windows_Connect(char* socketName, char* addressName) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	GMapO(GSocket2Windows_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Windows_MapEqual);
	SOCKADDR_IN* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocket2Windows_MapEqual);
	int lSize = sizeof(*lAddress);
	int lOk = connect(*lSocket, (SOCKADDR*)lAddress, lSize);
	if(lOk == SOCKET_ERROR) {GConsole()->Print("[ GSocket2Windows ] Error GSocket2Windows_Connect: %d\n", WSAGetLastError()); exit(0);}
#endif
}
//===============================================
static void GSocket2Windows_Send(char* socketName, char* message, int size) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Windows_MapEqual);
	int lSize = size;
	if(lSize <= 0) lSize = strlen(message);
	int lBytes = send(*lSocket, message, lSize, 0);
	if(lBytes == SOCKET_ERROR) {GConsole()->Print("[ GSocket2Windows ] Error GSocket2Windows_Send: %d\n", WSAGetLastError()); exit(0);}
#endif
}
//===============================================
static void GSocket2Windows_Recv(char* socketName, char* message, int size) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Windows_MapEqual);
	int lSize = size;
	if(lSize <= 0) lSize = strlen(message);
	int lBytes = recv(*lSocket, message, lSize, 0);
	if(lBytes == SOCKET_ERROR) {GConsole()->Print("[ GSocket2Windows ] Error GSocket2Windows_Recv: %d\n", WSAGetLastError()); exit(0);}
	message[lBytes] = 0;
#endif
}
//===============================================
static void GSocket2Windows_Close(char* socketName) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Windows_MapEqual);
	int lOk = closesocket(*lSocket);
	if(lOk == SOCKET_ERROR) {GConsole()->Print("[ GSocket2Windows ] Error GSocket2Windows_Close: %d\n", WSAGetLastError()); exit(0);}
#endif
}
//===============================================
static void GSocket2Windows_Clean() {
#if defined(__WIN32)
	WSACleanup();
#endif
}
//===============================================
static void GSocket2Windows_FreeData(char* dataName) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GWSADATA_PTR)* lDataMap = lSocketWindows->m_dataMap;
	WSADATA* lData = lDataMap->GetData(lDataMap, dataName, GSocket2Windows_MapEqual);
	free(lData);
#endif
}
//===============================================
static void GSocket2Windows_FreeSocket(char* socketName) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GSOCKET_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Windows_MapEqual);
	free(lSocket);
#endif
}
//===============================================
static void GSocket2Windows_FreeAddress(char* addressName) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKADDR_IN* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocket2Windows_MapEqual);
	free(lAddress);
#endif
}
//===============================================
#if defined(__WIN32)
static int GSocket2Windows_MapEqual(char* key1, char* key2) {
    int lStrcmp = strcmp(key1, key2);
    if(lStrcmp == 0) return TRUE;
    return FALSE;
}
#endif
//===============================================
