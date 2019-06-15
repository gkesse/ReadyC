//===============================================
#include "GSocketWindows.h"
#include "GString.h"
//===============================================
static GSocketO* m_GSocketWindowsO = 0;
//===============================================
static void GSocketWindows_Start(int major, int minor);
static void GSocketWindows_Status();
static void GSocketWindows_Major();
static void GSocketWindows_Minor();
static void GSocketWindows_MajorMax();
static void GSocketWindows_MinorMax();
static void GSocketWindows_Socket(int addressFamily, int type, int protocol);
static void GSocketWindows_SocketName();
static void GSocketWindows_IpAddress();
static void GSocketWindows_Port();
static void GSocketWindows_Address(int addressFamily, char* ipAddress, int port);
static void GSocketWindows_Address2(int addressFamily, ulong ipAddress, int port);
static void GSocketWindows_Bind();
static void GSocketWindows_Listen(int backlog);
static int GSocketWindows_Accept();
static void GSocketWindows_Connect();
static void GSocketWindows_Send();
static void GSocketWindows_Recv();
static void GSocketWindows_Close();
static void GSocketWindows_Close2();
static void GSocketWindows_Clean();
//===============================================
GSocketO* GSocketWindows_New() {
	GSocketO* lParent = GSocket_New();
	GSocketWindowsO* lChild = (GSocketWindowsO*)malloc(sizeof(GSocketWindowsO));

	lChild->m_parent = lParent;

	lParent->m_child = lChild;
	lParent->Delete = GSocketWindows_Delete;
	lParent->Start = GSocketWindows_Start;
	lParent->Status = GSocketWindows_Status;
	lParent->Major = GSocketWindows_Major;
	lParent->Minor = GSocketWindows_Minor;
	lParent->MajorMax = GSocketWindows_MajorMax;
	lParent->MinorMax = GSocketWindows_MinorMax;
	lParent->Socket = GSocketWindows_Socket;
	lParent->SocketName = GSocketWindows_SocketName;
	lParent->IpAddress = GSocketWindows_IpAddress;
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
	lParent->Close2 = GSocketWindows_Close2;
	lParent->Clean = GSocketWindows_Clean;
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
static void GSocketWindows_Start(int major, int minor) {
#if defined(__WIN32)
	printf("[ SOCKET ] Start %d.%d...\n", major, minor);
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	WSADATA* lWsaData = &lSocketWindows->m_wsaData;
	WSAStartup(MAKEWORD(major, minor), lWsaData);
#endif
}
//===============================================
static void GSocketWindows_Status() {
#if defined(__WIN32)
	printf("[ SOCKET ] Status...\n");
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	WSADATA* lWsaData = &lSocketWindows->m_wsaData;
	char* lStatus = lWsaData->szSystemStatus;
	printf("[ STATUS ] %s...\n", lStatus);
#endif
}
//===============================================
static void GSocketWindows_Major() {
#if defined(__WIN32)
	printf("[ SOCKET ] Major...\n");
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	WSADATA* lWsaData = &lSocketWindows->m_wsaData;
	int lMajor = LOBYTE(lWsaData->wVersion);
	printf("[ MAJOR ] %d...\n", lMajor);
#endif
}
//===============================================
static void GSocketWindows_Minor() {
#if defined(__WIN32)
	printf("[ SOCKET ] Minor...\n");
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	WSADATA* lWsaData = &lSocketWindows->m_wsaData;
	int lMinor = HIBYTE(lWsaData->wVersion);
	printf("[ MINOR ] %d...\n", lMinor);
#endif
}
//===============================================
static void GSocketWindows_MajorMax() {
#if defined(__WIN32)
	printf("[ SOCKET ] MajorMax...\n");
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	WSADATA* lWsaData = &lSocketWindows->m_wsaData;
	int lMajor = LOBYTE(lWsaData->wHighVersion);
	printf("[ MAJOR MAX ] %d...\n", lMajor);
#endif
}
//===============================================
static void GSocketWindows_MinorMax() {
#if defined(__WIN32)
	printf("[ SOCKET ] MinorMax...\n");
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	WSADATA* lWsaData = &lSocketWindows->m_wsaData;
	int lMinor = HIBYTE(lWsaData->wHighVersion);
	printf("[ MINOR MAX ] %d...\n", lMinor);
#endif
}
//===============================================
static void GSocketWindows_Socket(int addressFamily, int type, int protocol) {
#if defined(__WIN32)
	printf("[ SOCKET ] Socket...\n");
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	SOCKET* lSocket = &lSocketWindows->m_socket;
	*lSocket = socket(addressFamily, type, protocol);
#endif
}
//===============================================
static void GSocketWindows_SocketName() {
#if defined(__WIN32)
	printf("[ SOCKET ] SocketName...\n");
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	SOCKET* lSocket = &lSocketWindows->m_socket;
	SOCKADDR_IN* lAddress = &lSocketWindows->m_address;
	int lSize = sizeof(*lAddress);
	getsockname(*lSocket, (SOCKADDR*)lAddress, &lSize);
#endif
}
//===============================================
static void GSocketWindows_IpAddress() {
#if defined(__WIN32)
	printf("[ SOCKET ] IpAddress...\n");
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	SOCKADDR_IN* lAddress = &lSocketWindows->m_address;
	char* lIpAddress = inet_ntoa(lAddress->sin_addr);
	printf("[ IP_ADDRESS ] %s...\n", lIpAddress);
#endif
}
//===============================================
static void GSocketWindows_Port() {
#if defined(__WIN32)
	printf("[ SOCKET ] Port...\n");
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	SOCKADDR_IN* lAddress = &lSocketWindows->m_address;
	int lPort = htons(lAddress->sin_port);
	printf("[ PORT ] %d...\n", lPort);
#endif
}
//===============================================
static void GSocketWindows_Address(int addressFamily, char* ipAddress, int port) {
#if defined(__WIN32)
	printf("[ SOCKET ] Address...\n");
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	SOCKADDR_IN* lAddress = &lSocketWindows->m_address;
	lAddress->sin_addr.s_addr = inet_addr(ipAddress);
	lAddress->sin_family = addressFamily;
	lAddress->sin_port = htons(port);
#endif
}
//===============================================
static void GSocketWindows_Address2(int addressFamily, ulong ipAddress, int port) {
#if defined(__WIN32)
	printf("[ SOCKET ] Address2...\n");
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	SOCKADDR_IN* lAddress = &lSocketWindows->m_address;
	lAddress->sin_addr.s_addr = htonl(ipAddress);
	lAddress->sin_family = addressFamily;
	lAddress->sin_port = htons(port);
#endif
}
//===============================================
static void GSocketWindows_Bind() {
#if defined(__WIN32)
	printf("[ SOCKET ] Bind...\n");
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	SOCKET* lSocket = &lSocketWindows->m_socket;
	SOCKADDR_IN* lAddress = &lSocketWindows->m_address;
	int lSize = sizeof(*lAddress);
	bind(*lSocket, (SOCKADDR*)lAddress, lSize);
#endif
}
//===============================================
static void GSocketWindows_Listen(int backlog) {
#if defined(__WIN32)
	printf("[ SOCKET ] Listen...\n");
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	SOCKET* lSocket = &lSocketWindows->m_socket;
	listen(*lSocket, backlog);
#endif
}
//===============================================
static int GSocketWindows_Accept() {
#if defined(__WIN32)
	printf("[ SOCKET ] Accept...\n");
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	SOCKET* lSocket = &lSocketWindows->m_socket;
	SOCKET* lSocket2 = &lSocketWindows->m_socket2;
	SOCKADDR_IN* lAddress2 = &lSocketWindows->m_address2;
	int lSize2 = sizeof(*lAddress2);
	*lSocket2 = accept(*lSocket, (SOCKADDR*)lAddress2, &lSize2);
	int lOk = (*lSocket2 != INVALID_SOCKET) ? TRUE : FALSE;
	return lOk;
#endif
	return 0;
}
//===============================================
static void GSocketWindows_Connect() {
#if defined(__WIN32)
	printf("[ SOCKET ] Connect...\n");
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	SOCKET* lSocket = &lSocketWindows->m_socket;
	SOCKADDR_IN* lAddress = &lSocketWindows->m_address;
	int lSize = sizeof(*lAddress);
	connect(*lSocket, (SOCKADDR*)lAddress, lSize);
#endif
}
//===============================================
static void GSocketWindows_Send() {
#if defined(__WIN32)
	printf("[ SOCKET ] Send...\n");
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	SOCKET* lSocket2 = &lSocketWindows->m_socket2;
	char* lBuffer = "Bonjour tout le monde";
	int lSize = strlen(lBuffer) + 1;
	printf("[ SEND ] %s...\n", lBuffer);
	send(*lSocket2, lBuffer, lSize, 0);
#endif
}
//===============================================
static void GSocketWindows_Recv() {
#if defined(__WIN32)
	printf("[ SOCKET ] Recv...\n");
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	SOCKET* lSocket = &lSocketWindows->m_socket;
	char lBuffer[255];
	int lSize = sizeof(lBuffer);
	recv(*lSocket, lBuffer, lSize, 0);
	printf("[ RECV ] %s...\n", lBuffer);
#endif
}
//===============================================
static void GSocketWindows_Close() {
#if defined(__WIN32)
	printf("[ SOCKET ] Close...\n");
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	SOCKET* lSocket = &lSocketWindows->m_socket;
	closesocket(*lSocket);
#endif
}
//===============================================
static void GSocketWindows_Close2() {
#if defined(__WIN32)
	printf("[ SOCKET ] Close2...\n");
	GSocketWindowsO* lSocketWindows = m_GSocketWindowsO->m_child;
	SOCKET* lSocket2 = &lSocketWindows->m_socket2;
	closesocket(*lSocket2);
#endif
}
//===============================================
static void GSocketWindows_Clean() {
#if defined(__WIN32)
	printf("[ SOCKET ] Clean...\n");
	WSACleanup();
#endif
}
//===============================================
