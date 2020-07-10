//===============================================
#include "GSoap.h"
#include "GMap.h"
//===============================================
#if defined(_GUSE_GSOAP_ON_)
//===============================================
#include "soapH.h"
//===============================================
typedef void (*GSOAP_FUNC)(void* soap, const char* server, const char* action, void* params);
//===============================================
GDECLARE_MAP(GSoap, GCHAR_PTR, GVOID_PTR)
GDEFINE_MAP(GSoap, GCHAR_PTR, GVOID_PTR)
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
static void GSoap_CallFunc(char* soapName, const char* server, const char* action, void* onFunc, void* params);
static void GSoap_Destroy(char* soapName);
static void GSoap_Serve(char* soapName);
static void GSoap_Bind(char* soapName, char* socketName, char* host, int port, int backlog);
static void GSoap_ValidSocket(char* socketName, char* soapName);
static void GSoap_Accept(char* soapName, char* socketName);
static void GSoap_Done(char* soapName);
static int GSoap_SenderFault(char* soapName, char* faultString, char* faultDetail);
static void GSoap_End(char* soapName);
static void GSoap_FreeSoap(char* soapName);
static void GSoap_FreeSocket(char* socketName);
static void GSoap_Clean();
//===============================================
GSoapO* GSoap_New() {
    GSoapO* lObj = (GSoapO*)malloc(sizeof(GSoapO));

    lObj->m_soapMap = GMap_New(GSoap, GCHAR_PTR, GVOID_PTR)();
    lObj->m_socketMap = GMap_New(GSoap, GCHAR_PTR, GVOID_PTR)();

    lObj->Delete = GSoap_Delete;
    lObj->Soap = GSoap_Soap;
    lObj->Socket = GSoap_Socket;
    lObj->Malloc = GSoap_Malloc;
    lObj->Init = GSoap_Init;
    lObj->Init1 = GSoap_Init1;
    lObj->PrintFault = GSoap_PrintFault;
    lObj->Done = GSoap_Done;
    lObj->CallFunc = GSoap_CallFunc;
    lObj->Destroy = GSoap_Destroy;
    lObj->Serve = GSoap_Serve;
    lObj->Bind = GSoap_Bind;
    lObj->Accept = GSoap_Accept;
    lObj->Done = GSoap_Done;
    lObj->ValidSocket = GSoap_ValidSocket;
    lObj->SenderFault = GSoap_SenderFault;
    lObj->End = GSoap_End;
    lObj->FreeSoap = GSoap_FreeSoap;
    lObj->FreeSocket = GSoap_FreeSocket;
    lObj->Clean = GSoap_Clean;
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
	GMapO(GSoap, GCHAR_PTR, GVOID_PTR)* lSoapMap = m_GSoapO->m_soapMap;
	struct soap* lSoap = (struct soap*)malloc(sizeof(struct soap));
	lSoapMap->SetData(lSoapMap, soapName, lSoap, GMap_EqualChar);
}
//===============================================
static void GSoap_Socket(char* socketName) {
	GMapO(GSoap, GCHAR_PTR, GVOID_PTR)* lSocketMap = m_GSoapO->m_socketMap;
	SOAP_SOCKET* lSocket = (SOAP_SOCKET*)malloc(sizeof(SOAP_SOCKET));
	lSocketMap->SetData(lSocketMap, socketName, lSocket, GMap_EqualChar);
}
//===============================================
static void* GSoap_Malloc(char* soapName, int size) {
	GMapO(GSoap, GCHAR_PTR, GVOID_PTR)* lSoapMap = m_GSoapO->m_soapMap;
	struct soap* lSoap = lSoapMap->GetData(lSoapMap, soapName, GMap_EqualChar);
	return soap_malloc(lSoap, size);
	return 0;
}
//===============================================
static void GSoap_Init(char* soapName) {
	GMapO(GSoap, GCHAR_PTR, GVOID_PTR)* lSoapMap = m_GSoapO->m_soapMap;
	struct soap* lSoap = lSoapMap->GetData(lSoapMap, soapName, GMap_EqualChar);
	soap_init(lSoap);
}
//===============================================
static void GSoap_Init1(char* soapName, int mode) {
	GMapO(GSoap, GCHAR_PTR, GVOID_PTR)* lSoapMap = m_GSoapO->m_soapMap;
	struct soap* lSoap = lSoapMap->GetData(lSoapMap, soapName, GMap_EqualChar);
	soap_init1(lSoap, mode);
}
//===============================================
static void GSoap_PrintFault(char* soapName, FILE* stream) {
	GMapO(GSoap, GCHAR_PTR, GVOID_PTR)* lSoapMap = m_GSoapO->m_soapMap;
	struct soap* lSoap = lSoapMap->GetData(lSoapMap, soapName, GMap_EqualChar);
	soap_print_fault(lSoap, stream);
}
//===============================================
static void GSoap_Done(char* soapName) {
	GMapO(GSoap, GCHAR_PTR, GVOID_PTR)* lSoapMap = m_GSoapO->m_soapMap;
	struct soap* lSoap = lSoapMap->GetData(lSoapMap, soapName, GMap_EqualChar);
	soap_done(lSoap);
}
//===============================================
static void GSoap_CallFunc(char* soapName, const char* server, const char* action, void* onFunc, void* params) {
	GMapO(GSoap, GCHAR_PTR, GVOID_PTR)* lSoapMap = m_GSoapO->m_soapMap;
	struct soap* lSoap = lSoapMap->GetData(lSoapMap, soapName, GMap_EqualChar);
	((GSOAP_FUNC)onFunc)(lSoap, server, action, params);
}
//===============================================
static void GSoap_Destroy(char* soapName) {
	GMapO(GSoap, GCHAR_PTR, GVOID_PTR)* lSoapMap = m_GSoapO->m_soapMap;
	struct soap* lSoap = lSoapMap->GetData(lSoapMap, soapName, GMap_EqualChar);
	soap_destroy(lSoap);
}
//===============================================
static void GSoap_Serve(char* soapName) {
	GMapO(GSoap, GCHAR_PTR, GVOID_PTR)* lSoapMap = m_GSoapO->m_soapMap;
	struct soap* lSoap = lSoapMap->GetData(lSoapMap, soapName, GMap_EqualChar);
	soap_serve(lSoap);
}
//===============================================
static void GSoap_Bind(char* soapName, char* socketName, char* host, int port, int backlog) {
	GMapO(GSoap, GCHAR_PTR, GVOID_PTR)* lSoapMap = m_GSoapO->m_soapMap;
	GMapO(GSoap, GCHAR_PTR, GVOID_PTR)* lSocketMap = m_GSoapO->m_socketMap;
	struct soap* lSoap = lSoapMap->GetData(lSoapMap, soapName, GMap_EqualChar);
	SOAP_SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GMap_EqualChar);
	*lSocket = soap_bind(lSoap, host, port, backlog);
	if(soap_valid_socket(*lSocket) == 0) {printf("[GSoap] Error GSoap_Bind\n"); soap_print_fault(lSoap, stderr); exit(0);}
}
//===============================================
static void GSoap_ValidSocket(char* socketName, char* soapName) {
	GMapO(GSoap, GCHAR_PTR, GVOID_PTR)* lSoapMap = m_GSoapO->m_soapMap;
	GMapO(GSoap, GCHAR_PTR, GVOID_PTR)* lSocketMap = m_GSoapO->m_socketMap;
	struct soap* lSoap = lSoapMap->GetData(lSoapMap, soapName, GMap_EqualChar);
	SOAP_SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GMap_EqualChar);
	int lOk = soap_valid_socket(*lSocket);
	if(lOk == 0) {printf("[GSoap] Error GSoap_ValidSocket\n"); soap_print_fault(lSoap, stderr); exit(0);}
}
//===============================================
static void GSoap_Accept(char* soapName, char* socketName) {
	GMapO(GSoap, GCHAR_PTR, GVOID_PTR)* lSoapMap = m_GSoapO->m_soapMap;
	GMapO(GSoap, GCHAR_PTR, GVOID_PTR)* lSocketMap = m_GSoapO->m_socketMap;
	struct soap* lSoap = lSoapMap->GetData(lSoapMap, soapName, GMap_EqualChar);
	SOAP_SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GMap_EqualChar);
	*lSocket = soap_accept(lSoap);
	if(soap_valid_socket(*lSocket) == 0) {printf("[GSoap] Error GSoap_Accept\n"); soap_print_fault(lSoap, stderr); exit(0);}
}
//===============================================
static void GSoap_End(char* soapName) {
	GMapO(GSoap, GCHAR_PTR, GVOID_PTR)* lSoapMap = m_GSoapO->m_soapMap;
	struct soap* lSoap = lSoapMap->GetData(lSoapMap, soapName, GMap_EqualChar);
	soap_end(lSoap);
} 
//===============================================
static int GSoap_SenderFault(char* soapName, char* faultString, char* faultDetail) {
	GMapO(GSoap, GCHAR_PTR, GVOID_PTR)* lSoapMap = m_GSoapO->m_soapMap;
	struct soap* lSoap = lSoapMap->GetData(lSoapMap, soapName, GMap_EqualChar);
	return soap_sender_fault(lSoap, faultString, faultDetail);
	return 0;
}
//===============================================
static void GSoap_FreeSoap(char* soapName) {
	GMapO(GSoap, GCHAR_PTR, GVOID_PTR)* lSoapMap = m_GSoapO->m_soapMap;
	struct soap* lSoap = lSoapMap->GetData(lSoapMap, soapName, GMap_EqualChar);
	free(lSoap);
}
//===============================================
static void GSoap_FreeSocket(char* socketName) {
	GMapO(GSoap, GCHAR_PTR, GVOID_PTR)* lSocketMap = m_GSoapO->m_socketMap;
	SOAP_SOCKET* lSocket = lSocketMap->GetData(lSocketMap, socketName, GMap_EqualChar);
	free(lSocket);
}
//===============================================
static void GSoap_Clean() {
	GMapO(GSoap, GCHAR_PTR, GVOID_PTR)* lSoapMap = m_GSoapO->m_soapMap;
	GMapO(GSoap, GCHAR_PTR, GVOID_PTR)* lSocketMap = m_GSoapO->m_socketMap;
	lSoapMap->Delete(lSoapMap);
	lSocketMap->Delete(lSocketMap);
}
//===============================================
#endif
//===============================================

