//===============================================
#ifndef _GSoap_
#define _GSoap_
//===============================================
#include "GInclude.h"
#include "GMap.h"
//===============================================
typedef struct _GSoapO GSoapO;
typedef struct _GMapO_GSoap_GCHAR_PTR_GSOAP_SOCKET_PTR GMapO_GSoap_GCHAR_PTR_GSOAP_SOCKET_PTR;
//===============================================
struct _GSoapO {
    void (*Delete)();
    void Socket(char* socketName);
    GMapO(GSoap_GCHAR_PTR_GSOAP_SOCKET_PTR)* m_socketMap;
};
//===============================================
GSoapO* GSoap_New();
void GSoap_Delete();
GSoapO* GSoap();
//===============================================
#endif
//===============================================
