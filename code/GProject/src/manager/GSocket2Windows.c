//===============================================
#include "GSocket2Windows.h"
#include "GConsole.h"
#include "GString2.h"
//===============================================
#if defined(__WIN32)
typedef char* GCHAR_PTR;
typedef WSADATA* GWSADATA_PTR;
typedef SOCKET* GSocket2_PTR;
typedef SOCKADDR_IN* GSOCKADDR_IN_PTR;
//===============================================
GDECLARE_MAP(GCHAR_PTR, GWSADATA_PTR, GSocket2Windows_GCHAR_PTR_GWSADATA_PTR)
GDEFINE_MAP(GCHAR_PTR, GWSADATA_PTR, GSocket2Windows_GCHAR_PTR_GWSADATA_PTR)
//===============================================
GDECLARE_MAP(GCHAR_PTR, GSocket2_PTR, GSocket2Windows_GCHAR_PTR_GSocket2_PTR)
GDEFINE_MAP(GCHAR_PTR, GSocket2_PTR, GSocket2Windows_GCHAR_PTR_GSocket2_PTR)
//===============================================
GDECLARE_MAP(GCHAR_PTR, GSOCKADDR_IN_PTR, GSocket2Windows_GCHAR_PTR_GSOCKADDR_IN_PTR)
GDEFINE_MAP(GCHAR_PTR, GSOCKADDR_IN_PTR, GSocket2Windows_GCHAR_PTR_GSOCKADDR_IN_PTR)
#endif
//===============================================
static GSocket2O* m_GSocket2WindowsO = 0;
//===============================================
static void GSocket2Windows_MallocData(char* dataName);
static void GSocket2Windows_Start(char* dataName, int major, int minor);
static void GSocket2Windows_Status(char* dataName);
static void GSocket2Windows_Major(char* dataName);
static void GSocket2Windows_Minor(char* dataName);
static void GSocket2Windows_MajorMax(char* dataName);
static void GSocket2Windows_MinorMax(char* dataName);
static void GSocket2Windows_Address(char* addressName);
static void GSocket2Windows_Address2(char* addressName, int family, int address, int port);
static void GSocket2Windows_Address3(char* addressName, int family, char* address, int port);
static void GSocket2Windows_Socket(char* socketName);
static void GSocket2Windows_Socket2(char* socketName, int family, int type, int protocol);
static void GSocket2Windows_SocketName(char* socketName, char* addressName);
static void GSocket2Windows_AddressIp(char* addressName);
static void GSocket2Windows_Port(char* socketName);
static void GSocket2Windows_Bind(char* socketName, char* addressName);
static void GSocket2Windows_Listen(char* socketName, int backlog);
static void GSocket2Windows_Accept(char* socketName, char* clientName);
static void GSocket2Windows_Connect(char* socketName, char* addressName);
static void GSocket2Windows_Send(char* socketName, char* message, int size);
static void GSocket2Windows_Recv(char* socketName, char* message, int size);
static void GSocket2Windows_Close(char* socketName);
static void GSocket2Windows_Clean(char* datatName);
static void GSocket2Windows_Clean2(char* socketName);
static void GSocket2Windows_Clean3(char* addressName);
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
	lChild->m_MallocDataMap = GMap_New_GSocket2Windows_GCHAR_PTR_GWSADATA_PTR();
	lChild->m_socketMap = GMap_New_GSocket2Windows_GCHAR_PTR_GSocket2_PTR();
	lChild->m_addressMap = GMap_New_GSocket2Windows_GCHAR_PTR_GSOCKADDR_IN_PTR();
#endif

	lParent->m_child = lChild;
	lParent->Delete = GSocket2Windows_Delete;
	lParent->Data = GSocket2Windows_MallocData;
	lParent->Start = GSocket2Windows_Start;
	lParent->Status = GSocket2Windows_Status;
	lParent->Major = GSocket2Windows_Major;
	lParent->Minor = GSocket2Windows_Minor;
	lParent->MajorMax = GSocket2Windows_MajorMax;
	lParent->MinorMax = GSocket2Windows_MinorMax;
	lParent->Socket = GSocket2Windows_Socket;
	lParent->Socket2 = GSocket2Windows_Socket2;
	lParent->SocketName = GSocket2Windows_SocketName;
	lParent->AddressIp = GSocket2Windows_AddressIp;
	lParent->Port = GSocket2Windows_Port;
	lParent->Address = GSocket2Windows_Address;
	lParent->Address2 = GSocket2Windows_Address2;
	lParent->Address3 = GSocket2Windows_Address3;
	lParent->Bind = GSocket2Windows_Bind;
	lParent->Listen = GSocket2Windows_Listen;
	lParent->Accept = GSocket2Windows_Accept;
	lParent->Connect = GSocket2Windows_Connect;
	lParent->Send = GSocket2Windows_Send;
	lParent->Recv = GSocket2Windows_Recv;
	lParent->Close = GSocket2Windows_Close;
	lParent->Clean = GSocket2Windows_Clean;
	lParent->Clean2 = GSocket2Windows_Clean2;
	lParent->Clean3 = GSocket2Windows_Clean3;
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
	GMapO(GSocket2Windows_GCHAR_PTR_GWSADATA_PTR)* lDataMap = lSocketWindows->m_MallocDataMap;
	WSADATA* lData = (WSADATA*)malloc(sizeof(WSADATA));
	lDataMap->SetData(lDataMap, dataName, lData, GSocket2Windows_MapEqual);
#endif
}
//===============================================
static void GSocket2Windows_Start(char* dataName, int major, int minor) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GWSADATA_PTR)* lDataMap = lSocketWindows->m_MallocDataMap;
	WSADATA* lData = lDataMap->GetData(lDataMap, dataName, GSocket2Windows_MapEqual);
	int lOk = WSAStartup(MAKEWORD(major, minor), lData);
	if(lOk != 0) {GConsole()->Print("[ GSocket2Windows ] Error GSocket2Windows_Start: %d\n", WSAGetLastError()); exit(0);}
#endif
}
//===============================================
static void GSocket2Windows_Status(char* dataName) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GWSADATA_PTR)* lDataMap = lSocketWindows->m_MallocDataMap;
	WSADATA* lData = lDataMap->GetData(lDataMap, dataName, GSocket2Windows_MapEqual);
	char* lStatus = lData->szSystemStatus;
	GConsole()->Print("[ GSocket2Windows ] Status: %s\n", lStatus);
#endif
}
//===============================================
static void GSocket2Windows_Major(char* dataName) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GWSADATA_PTR)* lDataMap = lSocketWindows->m_MallocDataMap;
	WSADATA* lData = lDataMap->GetData(lDataMap, dataName, GSocket2Windows_MapEqual);
	int lMajor = LOBYTE(lData->wVersion);
	GConsole()->Print("[ GSocket2Windows ] Version Major: %d\n", lMajor);
#endif
}
//===============================================
static void GSocket2Windows_Minor(char* dataName) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GWSADATA_PTR)* lDataMap = lSocketWindows->m_MallocDataMap;
	WSADATA* lData = lDataMap->GetData(lDataMap, dataName, GSocket2Windows_MapEqual);
	int lMinor = HIBYTE(lData->wVersion);
	GConsole()->Print("[ GSocket2Windows ] Version Minor: %d\n", lMinor);
#endif
}
//===============================================
static void GSocket2Windows_MajorMax(char* dataName) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GWSADATA_PTR)* lDataMap = lSocketWindows->m_MallocDataMap;
	WSADATA* lData = lDataMap->GetData(lDataMap, dataName, GSocket2Windows_MapEqual);
	int lMajor = LOBYTE(lData->wHighVersion);
	GConsole()->Print("[ GSocket2Windows ] Version Major Max: %d\n", lMajor);
#endif
}
//===============================================
static void GSocket2Windows_MinorMax(char* dataName) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GWSADATA_PTR)* lDataMap = lSocketWindows->m_MallocDataMap;
	WSADATA* lData = lDataMap->GetData(lDataMap, dataName, GSocket2Windows_MapEqual);
	int lMinor = HIBYTE(lData->wHighVersion);
	GConsole()->Print("[ GSocket2Windows ] Version Minor Max: %d\n", lMinor);
#endif
}
//===============================================
static void GSocket2Windows_Address(char* addressName) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKADDR_IN* lAddress = (SOCKADDR_IN*)malloc(sizeof(SOCKADDR_IN));
	lAddressMap->SetData(lAddressMap, addressName, lAddress, GSocket2Windows_MapEqual);
#endif
}
//===============================================
static void GSocket2Windows_Address2(char* addressName, int family, int address, int port) {
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
static void GSocket2Windows_Address3(char* addressName, int family, char* address, int port) {
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
static void GSocket2Windows_Socket(char* socketName) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GSocket2_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	SOCKET* lSocket = (SOCKET*)malloc(sizeof(SOCKET));
	lSocketMap->SetData(lSocketMap, socketName, lSocket, GSocket2Windows_MapEqual);
#endif
}
//===============================================
static void GSocket2Windows_Socket2(char* socketName, int family, int type, int protocol) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GSocket2_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Windows_MapEqual);
	*lSocket = socket(family, type, protocol);
	if(*lSocket == INVALID_SOCKET) {GConsole()->Print("[ GSocket2Windows ] Error GSocket2Windows_Socket2: %d\n", WSAGetLastError()); exit(0);}
#endif
}
//===============================================
static void GSocket2Windows_SocketName(char* socketName, char* addressName) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GSocket2_PTR)* lSocketMap = lSocketWindows->m_socketMap;
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
	GMapO(GSocket2Windows_GCHAR_PTR_GSocket2_PTR)* lSocketMap = lSocketWindows->m_socketMap;
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
	GMapO(GSocket2Windows_GCHAR_PTR_GSocket2_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Windows_MapEqual);
	int lOk = listen(*lSocket, backlog);
	if(lOk == SOCKET_ERROR) {GConsole()->Print("[ GSocket2Windows ] Error GSocket2Windows_Listen: %d\n", WSAGetLastError()); exit(0);}
#endif
}
//===============================================
static void GSocket2Windows_Accept(char* socketName, char* clientName) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GSocket2_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	GMapO(GSocket2Windows_GCHAR_PTR_GSOCKADDR_IN_PTR)* lAddressMap = lSocketWindows->m_addressMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Windows_MapEqual);
	SOCKET* lSocket2 = lSocketMap->GetData(lSocketMap, clientName, GSocket2Windows_MapEqual);
	SOCKADDR_IN* lAddress2 = lAddressMap->GetData(lAddressMap, clientName, GSocket2Windows_MapEqual);
	int lSize2 = sizeof(*lAddress2);
	*lSocket2 = accept(*lSocket, (SOCKADDR*)lAddress2, &lSize2);
	if(*lSocket2 == INVALID_SOCKET) {GConsole()->Print("[ GSocket2Windows ] Error GSocket2Windows_Accept: %d\n", WSAGetLastError()); exit(0);}
#endif
}
//===============================================
static void GSocket2Windows_Connect(char* socketName, char* addressName) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GSocket2_PTR)* lSocketMap = lSocketWindows->m_socketMap;
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
	GMapO(GSocket2Windows_GCHAR_PTR_GSocket2_PTR)* lSocketMap = lSocketWindows->m_socketMap;
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
	GMapO(GSocket2Windows_GCHAR_PTR_GSocket2_PTR)* lSocketMap = lSocketWindows->m_socketMap;
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
	GMapO(GSocket2Windows_GCHAR_PTR_GSocket2_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Windows_MapEqual);
	int lOk = closesocket(*lSocket);
	if(lOk == SOCKET_ERROR) {GConsole()->Print("[ GSocket2Windows ] Error GSocket2Windows_Close: %d\n", WSAGetLastError()); exit(0);}
#endif
}
//===============================================
static void GSocket2Windows_Clean(char* dataName) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GWSADATA_PTR)* lDataMap = lSocketWindows->m_MallocDataMap;
	WSADATA* lData = lDataMap->GetData(lDataMap, dataName, GSocket2Windows_MapEqual);
	WSACleanup();
	free(lData);
#endif
}
//===============================================
static void GSocket2Windows_Clean2(char* socketName) {
#if defined(__WIN32)
	GSocket2WindowsO* lSocketWindows = m_GSocket2WindowsO->m_child;
	GMapO(GSocket2Windows_GCHAR_PTR_GSocket2_PTR)* lSocketMap = lSocketWindows->m_socketMap;
	SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Windows_MapEqual);
	free(lSocket);
#endif
}
//===============================================
static void GSocket2Windows_Clean3(char* addressName) {
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
