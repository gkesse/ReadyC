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
//typedef int (*GSOAP_CALL_FUNC)();
//===============================================
struct _GSoapO {
    void (*Delete)();
    void (*Soap)(char* socketName);
    void (*Socket)(char* socketName);
    void* (*Malloc)(char* soapName, int size);
    void (*Init)(char* soapName);
    void (*Init1)(char* soapName, int mode);
    void (*PrintFault)(char* soapName, FILE* stream);
    void (*Done)(char* soapName);
    void (*Call)(char* soapName, const char* server, const char* action, double a, double b, double* result);
    void (*Destroy)(char* soapName);
    void (*Serve)(char* socketName);
    void (*Bind)(char* soapName, char* socketName, char* host, int port, int backlog);
    void (*ValidSocket)(char* socketName, char* soapName);
    void (*Accept)(char* soapName, char* socketName);
    void (*Done)(char* soapName);
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
