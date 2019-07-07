//===============================================
#include "GProcessSoapServer.h"
#include "GConsole.h"
#include "soapH.h"
//===============================================
#if defined(G_SOAP_SERVER)
#include "calc.nsmap"
#endif
//===============================================
static GProcessO* m_GProcessSoapServerO = 0;
//===============================================
static void GProcessSoapServer_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessSoapServer_New() {
	GProcessO* lParent = GProcess_New();
	GProcessSoapServerO* lChild = (GProcessSoapServerO*)malloc(sizeof(GProcessSoapServerO));

	lChild->m_parent = lParent;

	lParent->m_child = lChild;
	lParent->Delete = GProcessSoapServer_Delete;
	lParent->Run = GProcessSoapServer_Run;
	return lParent;
}
//===============================================
void GProcessSoapServer_Delete() {
	// Delete All Attributes Before
	GProcess_Delete(m_GProcessSoapServerO);
	m_GProcessSoapServerO = 0;
}
//===============================================
GProcessO* GProcessSoapServer() {
	if(m_GProcessSoapServerO == 0) {
		m_GProcessSoapServerO = GProcessSoapServer_New();
	}
	return m_GProcessSoapServerO;
}
//===============================================
static void GProcessSoapServer_Run(int argc, char** argv) {
	GConsole()->Print("[ GSoap ] Server Start...\n");
	SOAP_SOCKET m, s; /* master and slave sockets */
	struct soap soap;
	soap_init(&soap);
	if (argc < 2)
		soap_serve(&soap);	/* serve as CGI application */
	else
	{ m = soap_bind(&soap, NULL, atoi(argv[1]), 100);
	if (!soap_valid_socket(m))
	{ soap_print_fault(&soap, stderr);
	exit(-1);
	}
	fprintf(stderr, "Socket connection successful: master socket = %d\n", m);
	for ( ; ; )
	{ s = soap_accept(&soap);
	fprintf(stderr, "Socket connection successful: slave socket = %d\n", s);
	if (!soap_valid_socket(s))
	{ soap_print_fault(&soap, stderr);
	exit(-1);
	}
	soap_serve(&soap);
	soap_end(&soap);
	}
	}
}
//===============================================
int ns__add(struct soap *soap, double a, double b, double *result)
{ *result = a + b;
  return SOAP_OK;
}

int ns__sub(struct soap *soap, double a, double b, double *result)
{ *result = a - b;
  return SOAP_OK;
}

int ns__mul(struct soap *soap, double a, double b, double *result)
{ *result = a * b;
  return SOAP_OK;
}

int ns__div(struct soap *soap, double a, double b, double *result)
{ if (b)
    *result = a / b;
  else
  { char *s = (char*)soap_malloc(soap, 1024);
    sprintf(s, "<error xmlns=\"http://tempuri.org/\">Can't divide %f by %f</error>", a, b);
    return soap_sender_fault(soap, "Division by zero", s);
  }
  return SOAP_OK;
}

int ns__pow(struct soap *soap, double a, double b, double *result)
{ *result = pow(a, b);
  if (soap_errno == EDOM)	/* soap_errno is like errno, but compatible with Win32 */
  { char *s = (char*)soap_malloc(soap, 1024);
    sprintf(s, "Can't take the power of %f to %f", a, b);
    sprintf(s, "<error xmlns=\"http://tempuri.org/\">Can't take power of %f to %f</error>", a, b);
    return soap_sender_fault(soap, "Power function domain error", s);
  }
  return SOAP_OK;
}
//===============================================
