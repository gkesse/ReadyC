//===============================================
#include "GSocketUnix.h"
#include "GString.h"
//===============================================
static GSocketO* m_GSocketUnixO = 0;
//===============================================
static void GSocketUnix_Start(int major, int minor);
static void GSocketUnix_Socket(int addressFamily, int type, int protocol);
static void GSocketUnix_Address(int addressFamily, char* ipAddress, int port);
static void GSocketUnix_Address2(int addressFamily, ulong ipAddress, int port);
static void GSocketUnix_Bind();
static void GSocketUnix_Listen();
static int GSocketUnix_Accept();
static void GSocketUnix_Connect();
static void GSocketUnix_Send();
static void GSocketUnix_Recv();
static void GSocketUnix_Close();
static void GSocketUnix_Close2();
static void GSocketUnix_Clean();
//===============================================
GSocketO* GSocketUnix_New() {
	GSocketO* lParent = GSocket_New();
	GSocketUnixO* lChild = (GSocketUnixO*)malloc(sizeof(GSocketUnixO));

	lChild->m_parent = lParent;

	lParent->m_child = lChild;
	lParent->Delete = GSocketUnix_Delete;
	lParent->Start = GSocketUnix_Start;
	lParent->Socket = GSocketUnix_Socket;
	lParent->Address = GSocketUnix_Address;
	lParent->Address2 = GSocketUnix_Address2;
	lParent->Bind = GSocketUnix_Bind;
	lParent->Listen = GSocketUnix_Listen;
	lParent->Accept = GSocketUnix_Accept;
	lParent->Connect = GSocketUnix_Connect;
	lParent->Send = GSocketUnix_Send;
	lParent->Recv = GSocketUnix_Recv;
	lParent->Close = GSocketUnix_Close;
	lParent->Close2 = GSocketUnix_Close2;
	lParent->Clean = GSocketUnix_Clean;
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
static void GSocketUnix_Start(int major, int minor) {
#if defined(__unix)
	printf("[ SOCKET ] Start...\n");
#endif
}
//===============================================
static void GSocketUnix_Socket(int addressFamily, int type, int protocol) {
#if defined(__unix)
	printf("[ SOCKET ] Socket...\n");
#endif
}
//===============================================
static void GSocketUnix_Address(int addressFamily, char* ipAddress, int port) {
#if defined(__unix)
	printf("[ SOCKET ] Address...\n");
#endif
}
//===============================================
static void GSocketUnix_Address2(int addressFamily, ulong ipAddress, int port) {
#if defined(__unix)
	printf("[ SOCKET ] Address2...\n");
#endif
}
//===============================================
static void GSocketUnix_Bind() {
#if defined(__unix)
	printf("[ SOCKET ] Bind2...\n");
#endif
}
//===============================================
static void GSocketUnix_Listen() {
#if defined(__unix)
	printf("[ SOCKET ] Listen...\n");
#endif
}
//===============================================
static int GSocketUnix_Accept() {
#if defined(__unix)
	printf("[ SOCKET ] Accept...\n");
#endif
	return 0;
}
//===============================================
static void GSocketUnix_Connect() {
#if defined(__unix)
	printf("[ SOCKET ] Connect...\n");
#endif
}
//===============================================
static void GSocketUnix_Send() {
#if defined(__unix)
	printf("[ SOCKET ] Send...\n");
#endif
}
//===============================================
static void GSocketUnix_Recv() {
#if defined(__unix)
	printf("[ SOCKET ] Recv...\n");
#endif
}
//===============================================
static void GSocketUnix_Close() {
#if defined(__unix)
	printf("[ SOCKET ] Close...\n");
#endif
}
//===============================================
static void GSocketUnix_Close2() {
#if defined(__unix)
	printf("[ SOCKET ] Close2...\n");
#endif
}
//===============================================
static void GSocketUnix_Clean() {
#if defined(__unix)
	printf("[ SOCKET ] Clean...\n");
#endif
}
//===============================================
