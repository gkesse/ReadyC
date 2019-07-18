//===============================================
#include "GProcessSoapClient.h"
#include "GConsole.h"
#include "GSoap.h"
//===============================================
const char* G_SERVER = "http://192.168.43.120:8228/cgi-bin/";
//===============================================
static GProcessO* m_GProcessSoapClientO = 0;
//===============================================
static void GProcessSoapClient_Run(int argc, char** argv);
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
	GSoap()->Soap("CLIENT");
	GSoap()->Soap("CLIENT");

	double lResult = 0;
	GSoap()->Call("CLIENT", G_SERVER, "", 10, 20, &lResult);

	GConsole()->Print("[ GSoap ] result = %g\n", lResult);
	GSoap()->Destroy("CLIENT");
	GSoap()->End("CLIENT");
	GSoap()->Done("CLIENT");
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
