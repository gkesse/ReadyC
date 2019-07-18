//===============================================
#include "GSoap.h"
#include "GConsole.h"
#include "soapH.h"
//===============================================
typedef char* GCHAR_PTR;
typedef struct soap* GSOAP_PTR;
typedef SOAP_SOCKET* GSOAP_SOCKET_PTR;
//===============================================
GDECLARE_MAP(GCHAR_PTR, GSOAP_PTR, GSoap_GCHAR_PTR_GSOAP_PTR)
GDEFINE_MAP(GCHAR_PTR, GSOAP_PTR, GSoap_GCHAR_PTR_GSOAP_PTR)
//===============================================
GDECLARE_MAP(GCHAR_PTR, GSOAP_SOCKET_PTR, GSoap_GCHAR_PTR_GSOAP_SOCKET_PTR)
GDEFINE_MAP(GCHAR_PTR, GSOAP_SOCKET_PTR, GSoap_GCHAR_PTR_GSOAP_SOCKET_PTR)
//===============================================
static GSoapO* m_GSoapO = 0;
//===============================================
static void GSoap_Soap(char* soapName);
static void GSoap_Socket(char* socketName);
static void* GSoap_Malloc(char* soapName, int size);
static void GSoap_Init(char* soapName);
static void GSoap_Init1(char* soapName, int mode);
static void GSoap_PrintFault(char* soapName, FILE* stream);
static void GSoap_Done(char* soapName);
static void GSoap_Call(char* soapName, const char* server, const char* action, double a, double b, double* result);
static void GSoap_Destroy(char* soapName);
static void GSoap_Serve(char* soapName);
static void GSoap_Bind(char* soapName, char* socketName, char* host, int port, int backlog);
static void GSoap_ValidSocket(char* socketName, char* soapName);
static void GSoap_Accept(char* soapName, char* socketName);
static void GSoap_Done(char* soapName);
static int GSoap_SenderFault(char* soapName, char* faultString, char* faultDetail);
static void GSoap_End(char* soapName);
//===============================================
static int GSoap_MapEqual(char* key1, char* key2);
//===============================================
GSoapO* GSoap_New() {
    GSoapO* lObj = (GSoapO*)malloc(sizeof(GSoapO));

    lObj->Delete = GSoap_Delete;
    lObj->Soap = GSoap_Soap;
    lObj->Socket = GSoap_Socket;
    lObj->Malloc = GSoap_Malloc;
    lObj->Init = GSoap_Init;
    lObj->Init1 = GSoap_Init1;
    lObj->PrintFault = GSoap_PrintFault;
    lObj->Done = GSoap_Done;
    lObj->Call = GSoap_Call;
    lObj->Destroy = GSoap_Destroy;
    lObj->Serve = GSoap_Serve;
    lObj->Bind = GSoap_Bind;
    lObj->Accept = GSoap_Accept;
    lObj->Done = GSoap_Done;
    lObj->ValidSocket = GSoap_ValidSocket;
    lObj->SenderFault = GSoap_SenderFault;
    lObj->End = GSoap_End;
    return lObj;
}
//===============================================
void GSoap_Delete() {
    GSoapO* lObj = GSoap();
    if(lObj != 0) {
        free(lObj);
    }
    m_GSoapO = 0;
}
//===============================================
GSoapO* GSoap() {
    if(m_GSoapO == 0) {
        m_GSoapO = GSoap_New();
    }
    return m_GSoapO;
}
//===============================================
static void GSoap_Soap(char* soapName) {
	GMapO(GSoap_GCHAR_PTR_GSOAP_PTR)* lSoapMap = m_GSoapO->m_soapMap;
	struct soap* lSoap = (struct soap*)malloc(sizeof(struct soap));
	lSoapMap->SetData(lSoapMap, soapName, lSoap, GSoap_MapEqual);
}
//===============================================
static void GSoap_Socket(char* socketName) {
	GMapO(GSoap_GCHAR_PTR_GSOAP_SOCKET_PTR)* lSocketMap = m_GSoapO->m_socketMap;
	SOAP_SOCKET* lSocket = (SOAP_SOCKET*)malloc(sizeof(SOAP_SOCKET));
	lSocketMap->SetData(lSocketMap, socketName, lSocket, GSoap_MapEqual);
}
//===============================================
static void* GSoap_Malloc(char* soapName, int size) {
	GMapO(GSoap_GCHAR_PTR_GSOAP_PTR)* lSoapMap = m_GSoapO->m_soapMap;
	struct soap* lSoap = lSoapMap->GetData(lSoapMap, soapName, GSoap_MapEqual);
	return soap_malloc(lSoap, size);
}
//===============================================
static void GSoap_Init(char* soapName) {
	GMapO(GSoap_GCHAR_PTR_GSOAP_PTR)* lSoapMap = m_GSoapO->m_soapMap;
	struct soap* lSoap = lSoapMap->GetData(lSoapMap, soapName, GSoap_MapEqual);
	soap_init(lSoap);
}
//===============================================
static void GSoap_Init1(char* soapName, int mode) {
	GMapO(GSoap_GCHAR_PTR_GSOAP_PTR)* lSoapMap = m_GSoapO->m_soapMap;
	struct soap* lSoap = lSoapMap->GetData(lSoapMap, soapName, GSoap_MapEqual);
	soap_init1(lSoap, mode);
}
//===============================================
static void GSoap_PrintFault(char* soapName, FILE* stream) {
	GMapO(GSoap_GCHAR_PTR_GSOAP_PTR)* lSoapMap = m_GSoapO->m_soapMap;
	struct soap* lSoap = lSoapMap->GetData(lSoapMap, soapName, GSoap_MapEqual);
	soap_print_fault(lSoap, stream);
}
//===============================================
static void GSoap_Done(char* soapName) {
	GMapO(GSoap_GCHAR_PTR_GSOAP_PTR)* lSoapMap = m_GSoapO->m_soapMap;
	struct soap* lSoap = lSoapMap->GetData(lSoapMap, soapName, GSoap_MapEqual);
	soap_done(lSoap);
}
//===============================================
static void GSoap_Call(char* soapName, const char* server, const char* action, double a, double b, double* result) {
	GMapO(GSoap_GCHAR_PTR_GSOAP_PTR)* lSoapMap = m_GSoapO->m_soapMap;
	struct soap* lSoap = lSoapMap->GetData(lSoapMap, soapName, GSoap_MapEqual);
	soap_call_ns__add(lSoap, server, action, a, b, result);
	int lOk = lSoap->error;
	if(lOk != 0) {GConsole()->Print("[ GSoap ] Error GSoap_Call\n"); soap_print_fault(lSoap, stderr); exit(0);}
}
//===============================================
static void GSoap_Destroy(char* soapName) {
	GMapO(GSoap_GCHAR_PTR_GSOAP_PTR)* lSoapMap = m_GSoapO->m_soapMap;
	struct soap* lSoap = lSoapMap->GetData(lSoapMap, soapName, GSoap_MapEqual);
	soap_destroy(lSoap);
}
//===============================================
static void GSoap_Serve(char* soapName) {
	GMapO(GSoap_GCHAR_PTR_GSOAP_PTR)* lSoapMap = m_GSoapO->m_soapMap;
	struct soap* lSoap = lSoapMap->GetData(lSoapMap, soapName, GSoap_MapEqual);
	soap_serve(lSoap);
}
//===============================================
static void GSoap_Bind(char* soapName, char* socketName, char* host, int port, int backlog) {
	GMapO(GSoap_GCHAR_PTR_GSOAP_PTR)* lSoapMap = m_GSoapO->m_soapMap;
	GMapO(GSoap_GCHAR_PTR_GSOAP_SOCKET_PTR)* lSocketMap = m_GSoapO->m_socketMap;
	struct soap* lSoap = lSoapMap->GetData(lSoapMap, soapName, GSoap_MapEqual);
	SOAP_SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSoap_MapEqual);
	*lSocket = soap_bind(lSoap, host, port, backlog);
	if(soap_valid_socket(*lSocket) == 0) {GConsole()->Print("[ GSoap ] Error GSoap_Bind\n"); soap_print_fault(lSoap, stderr); exit(0);}
}
//===============================================
static void GSoap_ValidSocket(char* socketName, char* soapName) {
	GMapO(GSoap_GCHAR_PTR_GSOAP_PTR)* lSoapMap = m_GSoapO->m_soapMap;
	GMapO(GSoap_GCHAR_PTR_GSOAP_SOCKET_PTR)* lSocketMap = m_GSoapO->m_socketMap;
	struct soap* lSoap = lSoapMap->GetData(lSoapMap, soapName, GSoap_MapEqual);
	SOAP_SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSoap_MapEqual);
	int lOk = soap_valid_socket(*lSocket);
	if(lOk == 0) {GConsole()->Print("[ GSoap ] Error GSoap_ValidSocket\n"); soap_print_fault(lSoap, stderr); exit(0);}
}
//===============================================
static void GSoap_Accept(char* soapName, char* socketName) {
	GMapO(GSoap_GCHAR_PTR_GSOAP_PTR)* lSoapMap = m_GSoapO->m_soapMap;
	GMapO(GSoap_GCHAR_PTR_GSOAP_SOCKET_PTR)* lSocketMap = m_GSoapO->m_socketMap;
	struct soap* lSoap = lSoapMap->GetData(lSoapMap, soapName, GSoap_MapEqual);
	SOAP_SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GSoap_MapEqual);
	*lSocket = soap_accept(lSoap);
	if(soap_valid_socket(*lSocket) == 0) {GConsole()->Print("[ GSoap ] Error GSoap_Accept\n"); soap_print_fault(lSoap, stderr); exit(0);}
}
//===============================================
static void GSoap_Done(char* soapName) {
	GMapO(GSoap_GCHAR_PTR_GSOAP_PTR)* lSoapMap = m_GSoapO->m_soapMap;
	struct soap* lSoap = lSoapMap->GetData(lSoapMap, soapName, GSoap_MapEqual);
	soap_done(lSoap);
}
//===============================================
static void GSoap_End(char* soapName) {
	GMapO(GSoap_GCHAR_PTR_GSOAP_PTR)* lSoapMap = m_GSoapO->m_soapMap;
	struct soap* lSoap = lSoapMap->GetData(lSoapMap, soapName, GSoap_MapEqual);
	soap_end(lSoap);
}
//===============================================
static int GSoap_SenderFault(char* soapName, char* faultString, char* faultDetail) {
	GMapO(GSoap_GCHAR_PTR_GSOAP_PTR)* lSoapMap = m_GSoapO->m_soapMap;
	struct soap* lSoap = lSoapMap->GetData(lSoapMap, soapName, GSoap_MapEqual);
	return soap_sender_fault(lSoap, faultString, faultDetail);
}
//===============================================
static int GSoap_MapEqual(char* key1, char* key2) {
    int lStrcmp = strcmp(key1, key2);
    if(lStrcmp == 0) return TRUE;
    return FALSE;
}
//===============================================

