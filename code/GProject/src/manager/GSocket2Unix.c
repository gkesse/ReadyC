//===============================================
#include "GSocket2Unix.h"
#include "GConsole.h"
#include "GString2.h"
//===============================================
#if defined(__unix)
typedef char* GCHAR_PTR;
typedef int* GINT_PTR;
typedef struct sockaddr_in* GSOCKADDRIN_PTR;
//===============================================
GDECLARE_MAP(GCHAR_PTR, GINT_PTR, GSocket2Unix_GCHAR_PTR_GINT_PTR)
GDEFINE_MAP(GCHAR_PTR, GINT_PTR, GSocket2Unix_GCHAR_PTR_GINT_PTR)
//===============================================
GDECLARE_MAP(GCHAR_PTR, GSOCKADDRIN_PTR, GSocket2Unix_GCHAR_PTR_GSOCKADDRIN_PTR)
GDEFINE_MAP(GCHAR_PTR, GSOCKADDRIN_PTR, GSocket2Unix_GCHAR_PTR_GSOCKADDRIN_PTR)
#endif
//===============================================
static GSocket2O* m_GSocket2UnixO = 0;
//===============================================
static void GSocket2Unix_MallocSocket(char* socketName);
static void GSocket2Unix_MallocAddress(char* addressName);
static void GSocket2Unix_Socket(char* socketName, int family, int type, int protocol);
static void GSocket2Unix_AddressInt(char* addressName, int family, int address, int port);
static void GSocket2Unix_AddressChar(char* addressName, int family, char* address, int port);
static void GSocket2Unix_Bind(char* socketName, char* addressName);
static void GSocket2Unix_Listen(char* socketName, int backlog);
static void GSocket2Unix_Accept(char* serverSocket, char* clientSocket, char* clientAddress);
static void GSocket2Unix_Connect(char* clientSocket, char* serverAddress);
static int GSocket2Unix_Write(char* socketName, char* data, int size);
static int GSocket2Unix_Read(char* socketName, char* data, int size);
static void GSocket2Unix_Close(char* socketName);
static void GSocket2Unix_FreeSocket(char* socketName);
static void GSocket2Unix_FreeAddress(char* socketName);
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
	lChild->m_addressMap = GMap_New_GSocket2Unix_GCHAR_PTR_GSOCKADDRIN_PTR();
#endif

	lParent->m_child = lChild;
	lParent->Delete = GSocket2Unix_Delete;
	lParent->MallocSocket = GSocket2Unix_MallocSocket;
	lParent->MallocAddress = GSocket2Unix_MallocAddress;
	lParent->Socket = GSocket2Unix_Socket;
	lParent->AddressInt = GSocket2Unix_AddressInt;
	lParent->AddressChar = GSocket2Unix_AddressChar;
	lParent->Bind = GSocket2Unix_Bind;
	lParent->Listen = GSocket2Unix_Listen;
	lParent->Accept = GSocket2Unix_Accept;
	lParent->Connect = GSocket2Unix_Connect;
	lParent->Write = GSocket2Unix_Write;
	lParent->Read = GSocket2Unix_Read;
	lParent->Close = GSocket2Unix_Close;
	lParent->FreeSocket = GSocket2Unix_FreeSocket;
	lParent->FreeAddress = GSocket2Unix_FreeAddress;
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
static void GSocket2Unix_MallocSocket(char* socketName) {
#if defined(__unix)
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	int* lSocket = (int*)malloc(sizeof(int));
	lSocketMap->SetData(lSocketMap, socketName, lSocket, GSocket2Unix_MapEqual);
#endif
}
//===============================================
static void GSocket2Unix_MallocAddress(char* addressName) {
#if defined(__unix)
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GSOCKADDRIN_PTR)* lAddressMap = lSocketUnix->m_addressMap;
	struct sockaddr_in* lAddress = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
	if(lAddress == 0) {GConsole()->Print("[ GSocket2Unix ] Error GSocket2Unix_MallocAddress\n"); exit(0);}
	lAddressMap->SetData(lAddressMap, addressName, lAddress, GSocket2Unix_MapEqual);
#endif
}
//===============================================
static void GSocket2Unix_Socket(char* socketName, int family, int type, int protocol) {
#if defined(__unix)
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Unix_MapEqual);
	*lSocket = socket(family, type, protocol);
	if(*lSocket == -1) {GConsole()->Print("[ GSocket2Unix ] Error GSocket2Unix_Socket2: %d\n", errno); exit(0);}
#endif
}
//===============================================
static void GSocket2Unix_AddressInt(char* addressName, int family, int address, int port) {
#if defined(__unix)
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GSOCKADDRIN_PTR)* lAddressMap = lSocketUnix->m_addressMap;
	struct sockaddr_in* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocket2Unix_MapEqual);
	memset(lAddress, 0, sizeof(*lAddress));
	lAddress->sin_family = family;
	lAddress->sin_addr.s_addr = htonl(address);
	lAddress->sin_port = htons(port);
#endif
}
//===============================================
static void GSocket2Unix_AddressChar(char* addressName, int family, char* address, int port) {
#if defined(__unix)
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GSOCKADDRIN_PTR)* lAddressMap = lSocketUnix->m_addressMap;
	struct sockaddr_in* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocket2Unix_MapEqual);
	memset(lAddress, 0, sizeof(*lAddress));
	lAddress->sin_family = family;
	lAddress->sin_addr.s_addr = inet_addr(address);
	lAddress->sin_port = htons(port);
#endif
}
//===============================================
static void GSocket2Unix_Bind(char* socketName, char* addressName) {
#if defined(__unix)
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	GMapO(GSocket2Unix_GCHAR_PTR_GSOCKADDRIN_PTR)* lAddressMap = lSocketUnix->m_addressMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Unix_MapEqual);
	struct sockaddr_in* lAddress = lAddressMap->GetData(lAddressMap, addressName, GSocket2Unix_MapEqual);
	int lSize = sizeof(*lAddress);
	int lRes = bind(*lSocket,(struct sockaddr *)lAddress, lSize);
	if(lRes == -1) {GConsole()->Print("[ GSocket2Unix ] Error GSocket2Unix_Bind\n"); exit(0);}
#endif
}
//===============================================
static void GSocket2Unix_Listen(char* socketName, int backlog) {
#if defined(__unix)
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Unix_MapEqual);
	int lRes = listen(*lSocket, backlog);
	if(lRes == -1) {GConsole()->Print("[ GSocket2Unix ] Error GSocket2Unix_Listen\n"); exit(0);}
#endif
}
//===============================================
static void GSocket2Unix_Accept(char* serverSocket, char* clientSocket, char* clientAddress) {
#if defined(__unix)
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	GMapO(GSocket2Unix_GCHAR_PTR_GSOCKADDRIN_PTR)* lAddressMap = lSocketUnix->m_addressMap;
	int* lServerSocket = lSocketMap->GetData(lSocketMap, serverSocket, GSocket2Unix_MapEqual);
	int* lClientSocket = lSocketMap->GetData(lSocketMap, clientSocket, GSocket2Unix_MapEqual);
	struct sockaddr_in* lClientAddress = lAddressMap->GetData(lAddressMap, clientAddress, GSocket2Unix_MapEqual);
	uint lClientSize = sizeof(*lClientAddress);
	*lClientSocket = accept(*lServerSocket, (struct sockaddr *)lClientAddress, &lClientSize);
	if(*lClientSocket == -1) {GConsole()->Print("[ GSocket2Unix ] Error GSocket2Unix_Accept\n"); exit(0);}
#endif
}
//===============================================
static void GSocket2Unix_Connect(char* clientSocket, char* serverAddress) {
#if defined(__unix)
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	GMapO(GSocket2Unix_GCHAR_PTR_GSOCKADDRIN_PTR)* lAddressMap = lSocketUnix->m_addressMap;
	int* lClientSocket = lSocketMap->GetData(lSocketMap, clientSocket, GSocket2Unix_MapEqual);
	struct sockaddr_in* lServerAddress = lAddressMap->GetData(lAddressMap, serverAddress, GSocket2Unix_MapEqual);
	int lServerSize = sizeof(*lServerAddress);
	int lRes = connect(*lClientSocket, (struct sockaddr *)lServerAddress, lServerSize);
	if(lRes == -1) {GConsole()->Print("[ GSocket2Unix ] Error GSocket2Unix_Connect\n"); exit(0);}
#endif
}
//===============================================
static int GSocket2Unix_Write(char* socketName, char* data, int size) {
#if defined(__unix)
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Unix_MapEqual);
	int lSize = size;
	if(lSize <= 0) lSize = strlen(data);
	int lBytes = write(*lSocket, data, lSize);
	if(lBytes == -1) {GConsole()->Print("[ GSocket2Unix ] Error GSocket2Unix_Write\n"); exit(0);}
	return lBytes;
#endif
	return 0;
}
//===============================================
static int GSocket2Unix_Read(char* socketName, char* data, int size) {
#if defined(__unix)
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Unix_MapEqual);
	int lBytes = read(*lSocket, data, size);
	if(lBytes == -1) {GConsole()->Print("[ GSocket2Unix ] Error GSocket2Unix_Write\n"); exit(0);}
	data[lBytes] = 0;
	return lBytes;
#endif
	return 0;
}
//===============================================
static void GSocket2Unix_Close(char* socketName) {
#if defined(__unix)
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Unix_MapEqual);
	int lRes = close(*lSocket);
	if(lRes == -1) {GConsole()->Print("[ GSocket2Unix ] Error GSocket2Unix_Close\n"); exit(0);}
#endif
}
//===============================================
static void GSocket2Unix_FreeSocket(char* socketName) {
#if defined(__unix)
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSocket2Unix_MapEqual);
	free(lSocket);
#endif
}
//===============================================
static void GSocket2Unix_FreeAddress(char* socketName) {
#if defined(__unix)
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GSOCKADDRIN_PTR)* lAddressMap = lSocketUnix->m_addressMap;
	struct sockaddr_in* lAddress = lAddressMap->GetData(lAddressMap, socketName, GSocket2Unix_MapEqual);
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
