//===============================================
#include "GSoap.h"
//===============================================
typedef char* GCHAR_PTR;
//typedef SOAP_SOCKET* GSOAP_SOCKET_PTR;
typedef char* GSOAP_SOCKET_PTR;
//===============================================
GDECLARE_MAP(GCHAR_PTR, GSOAP_SOCKET_PTR, GSoap_GCHAR_PTR_GSOAP_SOCKET_PTR)
GDEFINE_MAP(GCHAR_PTR, GSOAP_SOCKET_PTR, GSoap_GCHAR_PTR_GSOAP_SOCKET_PTR)
//===============================================
static GSoapO* m_GSoapO = 0;
//===============================================
void GSoap_Socket(char* socketName);
//===============================================
GSoapO* GSoap_New() {
    GSoapO* lObj = (GSoapO*)malloc(sizeof(GSoapO));

    lObj->Delete = GSoap_Delete;
    lObj->Socket = GSoap_Socket;
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
void GSoap_Socket(char* socketName) {

}
//===============================================

