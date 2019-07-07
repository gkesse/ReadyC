//===============================================
#include "GProcessSoapClient.h"
#include "GConsole.h"
#include "soapH.h"
//===============================================
#if defined(G_SOAP_CLIENT)
#include "calc.nsmap"
#endif
//===============================================
const char server[] = "http://websrv.cs.fsu.edu/~engelen/calcserver.cgi";
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
	GConsole()->Print("[ GSoap ] Client Start...\n");
<<<<<<< HEAD
	struct soap *soap = soap_new();
	int a, b, result;
	if(argc > 3 )
	{ a = atoi(argv[1]);
	b = atoi(argv[3]);
=======
	struct soap soap;
	double a, b, result;
	if (argc < 4)
	{ fprintf(stderr, "Usage: [add|sub|mul|div|pow] num num\n");
	exit(0);
>>>>>>> e856714f5bde9182b2f094384f4252baeff32698
	}
	soap_init1(&soap, SOAP_XML_INDENT);
	a = strtod(argv[2], NULL);
	b = strtod(argv[3], NULL);
	switch (*argv[1])
	{ case 'a':
		soap_call_ns__add(&soap, server, "", a, b, &result);
		break;
	case 's':
		soap_call_ns__sub(&soap, server, "", a, b, &result);
		break;
	case 'm':
		soap_call_ns__mul(&soap, server, "", a, b, &result);
		break;
	case 'd':
		soap_call_ns__div(&soap, server, "", a, b, &result);
		break;
<<<<<<< HEAD
	}
=======
	case 'p':
		soap_call_ns__pow(&soap, server, "", a, b, &result);
		break;
	default:
		fprintf(stderr, "Unknown command\n");
		exit(0);
	}
	if (soap.error)
	{ soap_print_fault(&soap, stderr);
	exit(1);
	}
	else
		printf("result = %g\n", result);
	soap_destroy(&soap);
	soap_end(&soap);
	soap_done(&soap);
>>>>>>> e856714f5bde9182b2f094384f4252baeff32698
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
