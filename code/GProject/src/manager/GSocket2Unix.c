//===============================================
#include "GSocket2Unix.h"
#include "GString.h"
#include "GMap.h"
//===============================================
#if defined(__unix2)
//===============================================
GDECLARE_MAP(GSocket2Unix, GCHAR_PTR, GVOID_PTR)
GDEFINE_MAP(GSocket2Unix, GCHAR_PTR, GVOID_PTR)
//===============================================
static GSocket2O* m_GSocket2UnixO = 0;
//===============================================
static void GSocket2Unix_Socket(char* socketName, int family, int type, int protocol);
static void GSocket2Unix_SetSockOpt(char* socketName, int level, int optionName, void* optionVal, int optionSize);
static void GSocket2Unix_AddressInt(char* addressName, int family, int address, int port);
static void GSocket2Unix_AddressChar(char* addressName, int family, char* address, int port);
static void GSocket2Unix_Fdzero(char* fdsetName);
static void GSocket2Unix_Fdset(char* socketName, char* fdsetName);
static void GSocket2Unix_Fdisset(char* socketName, char* fdsetName);
static void GSocket2Unix_Select(char* fdsetName, int nfds);
static void GSocket2Unix_Bind(char* socketName, char* addressName);
static void GSocket2Unix_Listen(char* socketName, int backlog);
static void GSocket2Unix_Accept(char* serverSocket, char* clientSocket, char* clientAddress);
static void GSocket2Unix_Connect(char* clientSocket, char* serverAddress);
static int GSocket2Unix_Write(char* socketName, char* data, int size);
static int GSocket2Unix_Read(char* socketName, char* data, int size);
static int GSocket2Unix_SendTo(char* socketName, char* addressName, char* data, int size, int flags);
static int GSocket2Unix_RecvFrom(char* socketName, char* addressName, char* data, int size, int flags);
static void GSocket2Unix_Shutdown(char* socketName, int mode);
static void GSocket2Unix_Close(char* socketName);
static void GSocket2Unix_Fdclr(char* socketName, char* fdsetName);
//===============================================
GSocket2O* GSocket2Unix_New() {
	GSocket2O* lParent = GSocket2_New();
	GSocket2UnixO* lChild = (GSocket2UnixO*)malloc(sizeof(GSocket2UnixO));

	lChild->m_parent = lParent;
	lChild->m_socketMap = GMap_New(GSocket2Unix, GCHAR_PTR, GVOID_PTR)();
	lChild->m_addressMap = GMap_New(GSocket2Unix, GCHAR_PTR, GVOID_PTR)();
	lChild->m_fdsetMap = GMap_New(GSocket2Unix, GCHAR_PTR, GVOID_PTR)();

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
	lParent->SendTo = GSocket2Unix_SendTo;
	lParent->RecvFrom = GSocket2Unix_RecvFrom;
	lParent->Shutdown = GSocket2Unix_Shutdown;
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
static void GSocket2Unix_Socket(char* socketName, int family, int type, int protocol) {
    //GLog()->Write("Execution de la fonction : GSocket2Unix_Socket");
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GMap_EqualChar);
	*lSocket = socket(GSOCKET2_INIT_FAMILY(family), GSOCKET2_INIT_TYPE(type), GSOCKET2_INIT_PROTOCOL(protocol));
	if(*lSocket == -1) {GConsole()->Print("[ GSocket2Unix ] Error GSocket2Unix_Socket2: %d\n", errno); exit(0);}
}
//===============================================
static void GSocket2Unix_SetSockOpt(char* socketName, int level, int optionName, void* optionVal, int optionSize) {
    //GLog()->Write("Execution de la fonction : GSocket2Unix_SetSockOpt");
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GMap_EqualChar);
    int lOptionSize = optionSize;
    if(optionSize == 0) lOptionSize = sizeof(*optionVal);
	int lRes = setsockopt(*lSocket, level, optionName, optionVal, lOptionSize);
	if(lRes == -1) {GConsole()->Print("[ GSocket2Unix ] Error GSocket2Unix_SetSockOpt: %d\n", errno); exit(0);}
}
//===============================================
static void GSocket2Unix_AddressInt(char* addressName, int family, int address, int port) {
    //GLog()->Write("Execution de la fonction : GSocket2Unix_AddressInt");
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GSOCKADDRIN_PTR)* lAddressMap = lSocketUnix->m_addressMap;
	struct sockaddr_in* lAddress = lAddressMap->GetData(lAddressMap, addressName, GMap_EqualChar);
	memset(lAddress, 0, sizeof(*lAddress));
	lAddress->sin_family = GSOCKET2_INIT_FAMILY(family);
	lAddress->sin_addr.s_addr = htonl(GSOCKET2_INIT_ADDRESS(address));
	lAddress->sin_port = htons(port);
}
//===============================================
static void GSocket2Unix_AddressChar(char* addressName, int family, char* address, int port) {
    //GLog()->Write("Execution de la fonction : GSocket2Unix_AddressChar");
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GSOCKADDRIN_PTR)* lAddressMap = lSocketUnix->m_addressMap;
	struct sockaddr_in* lAddress = lAddressMap->GetData(lAddressMap, addressName, GMap_EqualChar);
	memset(lAddress, 0, sizeof(*lAddress));
	lAddress->sin_family = GSOCKET2_INIT_FAMILY(family);
	lAddress->sin_addr.s_addr = inet_addr(address);
	lAddress->sin_port = htons(port);
}
//===============================================
static void GSocket2Unix_Fdzero(char* fdsetName) {
    //GLog()->Write("Execution de la fonction : GSocket2Unix_Fdzero");
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GFDSET_PTR)* lFdsetMap = lSocketUnix->m_fdsetMap;
	fd_set* lFdset = lFdsetMap->GetData(lFdsetMap, fdsetName, GMap_EqualChar);
	FD_ZERO(lFdset);
}
//===============================================
static void GSocket2Unix_Fdset(char* socketName, char* fdsetName) {
    //GLog()->Write("Execution de la fonction : GSocket2Unix_Fdzero");
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	GMapO(GSocket2Unix_GCHAR_PTR_GFDSET_PTR)* lFdsetMap = lSocketUnix->m_fdsetMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GMap_EqualChar);
	fd_set* lFdset = lFdsetMap->GetData(lFdsetMap, fdsetName, GMap_EqualChar);
	FD_SET(*lSocket, lFdset);
}
//===============================================
static void GSocket2Unix_Fdisset(char* socketName, char* fdsetName) {
    //GLog()->Write("Execution de la fonction : GSocket2Unix_Fdzero");
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	GMapO(GSocket2Unix_GCHAR_PTR_GFDSET_PTR)* lFdsetMap = lSocketUnix->m_fdsetMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GMap_EqualChar);
	fd_set* lFdset = lFdsetMap->GetData(lFdsetMap, fdsetName, GMap_EqualChar);
	FD_ISSET(*lSocket, lFdset);
}
//===============================================
static void GSocket2Unix_Select(char* fdsetName, int nfds) {
    //GLog()->Write("Execution de la fonction : GSocket2Unix_Select");
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GFDSET_PTR)* lFdsetMap = lSocketUnix->m_fdsetMap;
	fd_set* lFdset = lFdsetMap->GetData(lFdsetMap, fdsetName, GMap_EqualChar);
	int lRes = select(nfds, lFdset, 0, 0, 0);
	if(lRes == -1) {GConsole()->Print("[ GSocket2Unix ] Error GSocket2Unix_Select\n"); exit(0);}
}
//===============================================
static void GSocket2Unix_Bind(char* socketName, char* addressName) {
    //GLog()->Write("Execution de la fonction : GSocket2Unix_Bind");
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	GMapO(GSocket2Unix_GCHAR_PTR_GSOCKADDRIN_PTR)* lAddressMap = lSocketUnix->m_addressMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GMap_EqualChar);
	struct sockaddr_in* lAddress = lAddressMap->GetData(lAddressMap, addressName, GMap_EqualChar);
	int lAddressSize = sizeof(*lAddress);
	int lRes = bind(*lSocket, (struct sockaddr*)lAddress, lAddressSize);
	if(lRes == -1) {GConsole()->Print("[ GSocket2Unix ] Error GSocket2Unix_Bind\n"); exit(0);}
}
//===============================================
static void GSocket2Unix_Listen(char* socketName, int backlog) {
    //GLog()->Write("Execution de la fonction : GSocket2Unix_Listen");
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GMap_EqualChar);
	int lRes = listen(*lSocket, backlog);
	if(lRes == -1) {GConsole()->Print("[ GSocket2Unix ] Error GSocket2Unix_Listen\n"); exit(0);}
}
//===============================================
static void GSocket2Unix_Accept(char* serverSocket, char* clientSocket, char* clientAddress) {
    //GLog()->Write("Execution de la fonction : GSocket2Unix_Accept");
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	GMapO(GSocket2Unix_GCHAR_PTR_GSOCKADDRIN_PTR)* lAddressMap = lSocketUnix->m_addressMap;
	int* lServerSocket = lSocketMap->GetData(lSocketMap, serverSocket, GMap_EqualChar);
	int* lClientSocket = lSocketMap->GetData(lSocketMap, clientSocket, GMap_EqualChar);
	struct sockaddr_in* lClientAddress = lAddressMap->GetData(lAddressMap, clientAddress, GMap_EqualChar);
	uint lClientSize = sizeof(*lClientAddress);
	*lClientSocket = accept(*lServerSocket, (struct sockaddr *)lClientAddress, &lClientSize);
	if(*lClientSocket == -1) {GConsole()->Print("[ GSocket2Unix ] Error GSocket2Unix_Accept\n"); exit(0);}
}
//===============================================
static void GSocket2Unix_Connect(char* clientSocket, char* serverAddress) {
    //GLog()->Write("Execution de la fonction : GSocket2Unix_Connect");
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	GMapO(GSocket2Unix_GCHAR_PTR_GSOCKADDRIN_PTR)* lAddressMap = lSocketUnix->m_addressMap;
	int* lClientSocket = lSocketMap->GetData(lSocketMap, clientSocket, GMap_EqualChar);
	struct sockaddr_in* lServerAddress = lAddressMap->GetData(lAddressMap, serverAddress, GMap_EqualChar);
	int lServerSize = sizeof(*lServerAddress);
	int lRes = connect(*lClientSocket, (struct sockaddr *)lServerAddress, lServerSize);
	if(lRes == -1) {GConsole()->Print("[ GSocket2Unix ] Error GSocket2Unix_Connect\n"); exit(0);}
}
//===============================================
static int GSocket2Unix_Write(char* socketName, char* data, int size) {
    //GLog()->Write("Execution de la fonction : GSocket2Unix_Write");
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GMap_EqualChar);
	int lSize = size;
	if(size <= 0) lSize = strlen(data);
	int lBytes = write(*lSocket, data, lSize);
	if(lBytes == -1) {GConsole()->Print("[ GSocket2Unix ] Error GSocket2Unix_Write\n"); exit(0);}
	return lBytes;
	return 0;
}
//===============================================
static int GSocket2Unix_Read(char* socketName, char* data, int size) {
    //GLog()->Write("Execution de la fonction : GSocket2Unix_Read");
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GMap_EqualChar);
	int lSize = size - 1;
	int lBytes = read(*lSocket, data, lSize);
	if(lBytes == -1) {GConsole()->Print("[ GSocket2Unix ] Error GSocket2Unix_Write\n"); exit(0);}
	data[lBytes] = 0;
	return lBytes;
	return 0;
}
//===============================================
static int GSocket2Unix_SendTo(char* socketName, char* addressName, char* data, int size, int flags) {
    //GLog()->Write("Execution de la fonction : GSocket2Unix_SendTo");
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	GMapO(GSocket2Unix_GCHAR_PTR_GSOCKADDRIN_PTR)* lAddressMap = lSocketUnix->m_addressMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GMap_EqualChar);
	int lSize = size;
	if(size <= 0) lSize = strlen(data);
	struct sockaddr_in* lAddress = lAddressMap->GetData(lAddressMap, addressName, GMap_EqualChar);
	int lAddressSize = sizeof(*lAddress);
    int lBytes = sendto(*lSocket, data, lSize, 0, lAddress, lAddressSize);
    if(lBytes == -1) {GConsole()->Print("[ GSocket2Unix ] Error GSocket2Unix_SendTo\n"); exit(0);}
	return lBytes;
	return 0;
}
//===============================================
static int GSocket2Unix_RecvFrom(char* socketName, char* addressName, char* data, int size, int flags) {
    //GLog()->Write("Execution de la fonction : GSocket2Unix_RecvFrom");
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	GMapO(GSocket2Unix_GCHAR_PTR_GSOCKADDRIN_PTR)* lAddressMap = lSocketUnix->m_addressMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GMap_EqualChar);
	struct sockaddr_in* lAddress = lAddressMap->GetData(lAddressMap, addressName, GMap_EqualChar);
	int lAddressSize = sizeof(*lAddress);
	int lSize = size - 1;
    int lBytes = recvfrom(*lSocket, data, lSize, flags, (struct sockaddr*)lAddress, (socklen_t*)&lAddressSize);
	if(lBytes == -1) {GConsole()->Print("[ GSocket2Unix ] Error GSocket2Unix_RecvFrom\n"); exit(0);}
	data[lBytes] = 0;
	return lBytes;
	return 0;
}
//===============================================
static void GSocket2Unix_Shutdown(char* socketName, int mode) {
    //GLog()->Write("Execution de la fonction : GSocket2Unix_Shutdown");
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GMap_EqualChar);
	int lRes = shutdown(*lSocket, GSOCKET2_INIT_SHUTDOWN(mode));
	if(lRes == -1) {GConsole()->Print("[ GSocket2Unix ] Error GSocket2Unix_Shutdown\n"); exit(0);}
}
//===============================================
static void GSocket2Unix_Close(char* socketName) {
    //GLog()->Write("Execution de la fonction : GSocket2Unix_Close");
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GMap_EqualChar);
	int lRes = close(*lSocket);
	if(lRes == -1) {GConsole()->Print("[ GSocket2Unix ] Error GSocket2Unix_Close\n"); exit(0);}
}
//===============================================
static void GSocket2Unix_Fdclr(char* socketName, char* fdsetName) {
    //GLog()->Write("Execution de la fonction : GSocket2Unix_Fdzero");
	GSocket2UnixO* lSocketUnix = m_GSocket2UnixO->m_child;
	GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* lSocketMap = lSocketUnix->m_socketMap;
	GMapO(GSocket2Unix_GCHAR_PTR_GFDSET_PTR)* lFdsetMap = lSocketUnix->m_fdsetMap;
	int* lSocket = lSocketMap->GetData(lSocketMap, socketName, GMap_EqualChar);
	fd_set* lFdset = lFdsetMap->GetData(lFdsetMap, fdsetName, GMap_EqualChar);
	FD_CLR(*lSocket, lFdset);
}
//===============================================
#endif
//===============================================
