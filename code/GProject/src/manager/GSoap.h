//===============================================
#ifndef _GSoap_
#define _GSoap_
//===============================================
#include "GInclude.h"
#include "GMap.h"
//===============================================
typedef struct _GSoapO GSoapO;
typedef struct _GMapO_GSoap_GCHAR_PTR_GSOAP_PTR GMapO_GSoap_GCHAR_PTR_GSOAP_PTR;
typedef struct _GMapO_GSoap_GCHAR_PTR_GSOAP_SOCKET_PTR GMapO_GSoap_GCHAR_PTR_GSOAP_SOCKET_PTR;
//===============================================
struct _GSoapO {
    void (*Delete)();
    void (*Soap)(char* socketName);
    void (*Socket)(char* socketName);
    void* (*Malloc)(char* soapName, int size);
    void (*Init1)(char* soapName, int mode);
    void (*Serve)(char* socketName);
    void (*Bind)(char* soapName, char* socketName, char* host, int port, int backlog);
    void (*Accept)(char* soapName, char* socketName);
    int (*SenderFault)(char* soapName, char* faultString, char* faultDetail);
    void (*End)(char* soapName);
    GMapO(GSoap_GCHAR_PTR_GSOAP_PTR)* m_soapMap;
    GMapO(GSoap_GCHAR_PTR_GSOAP_SOCKET_PTR)* m_socketMap;
};
//===============================================
GSoapO* GSoap_New();
void GSoap_Delete();
GSoapO* GSoap();
//===============================================
#endif
//===============================================
