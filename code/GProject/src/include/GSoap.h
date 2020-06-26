//===============================================
#ifndef _GSoap_
#define _GSoap_
//===============================================
#include "GInclude.h"
#include "GMap.h"
//===============================================
#if defined(_GUSE_GSOAP_ON_)
//===============================================
typedef struct _GSoapO GSoapO;
typedef struct _GMapO_GSoap_GCHAR_PTR_GSOAP_PTR GMapO_GSoap_GCHAR_PTR_GSOAP_PTR;
typedef struct _GMapO_GSoap_GCHAR_PTR_GSOAP_SOCKET_PTR GMapO_GSoap_GCHAR_PTR_GSOAP_SOCKET_PTR;
//===============================================
typedef void (*GSOAP_CALL_FUNC)(GSOAP_STRUCT soap, const char* server, const char* action, void* params);
//===============================================
struct _GSoapO {
    void (*Delete)();
    void (*Soap)(char* socketName);
    void (*Socket)(char* socketName);
    void* (*Malloc)(char* soapName, int size);
    void (*Init)(char* soapName);
    void (*Init1)(char* soapName, int mode);
    void (*PrintFault)(char* soapName, FILE* stream);
    void (*CallFunc)(char* soapName, const char* server, const char* action, GSOAP_CALL_FUNC callFunc, void* params);
    void (*Destroy)(char* soapName);
    void (*Serve)(char* socketName);
    void (*Bind)(char* soapName, char* socketName, char* host, int port, int backlog);
    void (*ValidSocket)(char* socketName, char* soapName);
    void (*Accept)(char* soapName, char* socketName);
    void (*Done)(char* soapName);
    int (*SenderFault)(char* soapName, char* faultString, char* faultDetail);
    void (*End)(char* soapName);
    void (*FreeSoap)(char* soapName);
    void (*FreeSocket)(char* socketName);
    void (*Clean)();
    //===============================================
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
#endif
//===============================================