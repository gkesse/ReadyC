//===============================================
#include "GProcessSoapClient.h"
#include "GConsole.h"
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
	struct soap *soap = soap_new();
	int a, b, result;
	if(argc > 3 )
	{ a = atoi(argv[1]);
	b = atoi(argv[3]);
	}
	else
		return;
	switch (*argv[2]) {
	case '+':
	if(soap_call_ns__add(soap, "xmlcomponents.com/CalcBin/Calc.dll", NULL, a, b, &result) == 0)
		printf("%d+%d=%d\n", a, b, result);
	else
		soap_print_fault(soap, stderr);
	break;
	case '-':
		if(soap_call_ns__subtract(soap, "xmlcomponents.com/CalcBin/Calc.dll", NULL, a, b, &result) == 0)
			printf("%d-%d=%d\n", a, b, result);
		else
			soap_print_fault(soap, stderr);
		break;
	case '*':
		if(soap_call_ns__multiply(soap, "xmlcomponents.com/CalcBin/Calc.dll", NULL, a, b, &result) == 0)
			printf("%d*%d=%d\n", a, b, result);
		else
			soap_print_fault(soap, stderr);
		break;
	case '/':
		if(soap_call_ns__divide(soap, "xmlcomponents.com/CalcBin/Calc.dll", NULL, a, b, &result) == 0)
			printf("%d/%d=%d\n", a, b, result);
		else
			soap_print_fault(soap, stderr);
		break;
	}
}
//===============================================
