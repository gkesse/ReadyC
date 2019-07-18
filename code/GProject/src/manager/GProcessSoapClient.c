//===============================================
#include "GProcessSoapClient.h"
#include "GConsole.h"
#include "GSoap.h"
#include "soapStub.h"
//===============================================
typedef struct _GSoapMath GSoapMath ;
//===============================================
struct _GSoapMath {
	double a;
	double b;
	double r;
};
//===============================================
const char* G_SERVER_URL = "http://192.168.43.120:8338/";
//===============================================
static GProcessO* m_GProcessSoapClientO = 0;
//===============================================
static void GProcessSoapClient_Run(int argc, char** argv);
//===============================================
static void GProcessSoapClient_AddFunc(struct soap* soap, const char* server, const char* action, void* params);
static void GProcessSoapClient_SubFunc(struct soap* soap, const char* server, const char* action, void* params);
static void GProcessSoapClient_MulFunc(struct soap* soap, const char* server, const char* action, void* params);
static void GProcessSoapClient_DivFunc(struct soap* soap, const char* server, const char* action, void* params);
//===============================================
GProcessO* GProcessSoapClient_New() {
	GProcessO* lParent = GProcess_New();
	GProcessSoapClientO* lChild = (GProcessSoapClientO*)malloc(sizeof(GProcessSoapClientO));

	lChild->m_parent = lParent;

	lParent->m_child = lChild;
	lParent->Delete = GProcessSoapClient_Delete;
	lParent->Run = GProcessSoapClient_Run;
	return lParent;
}
//===============================================
void GProcessSoapClient_Delete() {
	// Delete All Attributes Before
	GProcess_Delete(m_GProcessSoapClientO);
	m_GProcessSoapClientO = 0;
}
//===============================================
GProcessO* GProcessSoapClient() {
	if(m_GProcessSoapClientO == 0) {
		m_GProcessSoapClientO = GProcessSoapClient_New();
	}
	return m_GProcessSoapClientO;
}
//===============================================
static void GProcessSoapClient_Run(int argc, char** argv) {
	GSoap()->Soap("CLIENT");

	GSoap()->Init1("CLIENT", SOAP_XML_INDENT);

	GSoapMath lSoapMath;

	lSoapMath.a = 50;
	lSoapMath.b = 30;
	GSoap()->CallFunc("CLIENT", G_SERVER_URL, "", GProcessSoapClient_AddFunc, &lSoapMath);
	GConsole()->Print("[ GSoap ] add(a, b) = %g\n", lSoapMath.r);

	lSoapMath.a = 50;
	lSoapMath.b = 20;
	GSoap()->CallFunc("CLIENT", G_SERVER_URL, "", GProcessSoapClient_SubFunc, &lSoapMath);
	GConsole()->Print("[ GSoap ] Sub(a, b) = %g\n", lSoapMath.r);

	lSoapMath.a = 50;
	lSoapMath.b = 20;
	GSoap()->CallFunc("CLIENT", G_SERVER_URL, "", GProcessSoapClient_MulFunc, &lSoapMath);
	GConsole()->Print("[ GSoap ] mul(a, b) = %g\n", lSoapMath.r);

	lSoapMath.a = 50;
	lSoapMath.b = 20;
	GSoap()->CallFunc("CLIENT", G_SERVER_URL, "", GProcessSoapClient_DivFunc, &lSoapMath);
	GConsole()->Print("[ GSoap ] div(a, b) = %g\n", lSoapMath.r);

	GSoap()->Destroy("CLIENT");
	GSoap()->End("CLIENT");
	GSoap()->Done("CLIENT");

	GSoap()->FreeSoap("CLIENT");
	GSoap()->Clean();
}
//===============================================
static void GProcessSoapClient_AddFunc(struct soap* soap, const char* server, const char* action, void* params) {
	GSoapMath* lSoapMath = (GSoapMath*)params;
	double lA = lSoapMath->a;
	double lB = lSoapMath->b;
	double lResult;
	soap_call_ns__add(soap, server, action, lA, lB, &lResult);
	int lOk = soap->error;
	if(lOk != 0) {GConsole()->Print("[ GSoap ] Error GProcessSoapClient_AddFunc\n"); soap_print_fault(soap, stderr); exit(0);}
	lSoapMath->r = lResult;
}
//===============================================
static void GProcessSoapClient_SubFunc(struct soap* soap, const char* server, const char* action, void* params) {
	GSoapMath* lSoapMath = (GSoapMath*)params;
	double lA = lSoapMath->a;
	double lB = lSoapMath->b;
	double lResult;
	soap_call_ns__sub(soap, server, action, lA, lB, &lResult);
	int lOk = soap->error;
	if(lOk != 0) {GConsole()->Print("[ GSoap ] Error GProcessSoapClient_SubFunc\n"); soap_print_fault(soap, stderr); exit(0);}
	lSoapMath->r = lResult;
}
//===============================================
static void GProcessSoapClient_MulFunc(struct soap* soap, const char* server, const char* action, void* params) {
	GSoapMath* lSoapMath = (GSoapMath*)params;
	double lA = lSoapMath->a;
	double lB = lSoapMath->b;
	double lResult;
	soap_call_ns__mul(soap, server, action, lA, lB, &lResult);
	int lOk = soap->error;
	if(lOk != 0) {GConsole()->Print("[ GSoap ] Error GProcessSoapClient_MulFunc\n"); soap_print_fault(soap, stderr); exit(0);}
	lSoapMath->r = lResult;
}
//===============================================
static void GProcessSoapClient_DivFunc(struct soap* soap, const char* server, const char* action, void* params) {
	GSoapMath* lSoapMath = (GSoapMath*)params;
	double lA = lSoapMath->a;
	double lB = lSoapMath->b;
	double lResult;
	soap_call_ns__div(soap, server, action, lA, lB, &lResult);
	int lOk = soap->error;
	if(lOk != 0) {GConsole()->Print("[ GSoap ] Error GProcessSoapClient_DivFunc\n"); soap_print_fault(soap, stderr); exit(0);}
	lSoapMath->r = lResult;
}
//===============================================
struct Namespace namespaces[] = {
		{ "SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/" },
		{ "SOAP-ENC","http://schemas.xmlsoap.org/soap/encoding/"},
		{ "xsi", "http://www.w3.org/1999/XMLSchema-instance" },
		{ "xsd", "http://www.w3.org/1999/XMLSchema" },
		{ "ns", "urn:Calc"},
		{ NULL, NULL }
};
//===============================================
