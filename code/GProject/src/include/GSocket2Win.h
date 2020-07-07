#ifndef _GSocket2Win_
#define _GSocket2Win_
//===============================================
#include "GSocket2.h"
#include "GMap.h"
//===============================================
#if defined(_GUSE_SOCKET_ON_)
//===============================================
typedef struct _GSocket2WinO GSocket2WinO;
typedef struct _GMapO_GSocket2Win_GCHAR_PTR_GWSADATA_PTR GMapO_GSocket2Win_GCHAR_PTR_GWSADATA_PTR;
typedef struct _GMapO_GSocket2Win_GCHAR_PTR_GSOCKET_PTR GMapO_GSocket2Win_GCHAR_PTR_GSOCKET_PTR;
typedef struct _GMapO_GSocket2Win_GCHAR_PTR_GSOCKADDR_IN_PTR GMapO_GSocket2Win_GCHAR_PTR_GSOCKADDR_IN_PTR;
//===============================================
struct _GSocket2WinO {
    GSocket2O* m_parent;
#if defined(__WIN32)
    GMapO(GSocket2Win_GCHAR_PTR_GWSADATA_PTR)* m_dataMap;
    GMapO(GSocket2Win_GCHAR_PTR_GSOCKET_PTR)* m_socketMap;
    GMapO(GSocket2Win_GCHAR_PTR_GSOCKADDR_IN_PTR)* m_addressMap;
#endif
};
//===============================================
GSocket2O* GSocket2Win_New();
void GSocket2Win_Delete(GSocket2O* obj);
GSocket2O* GSocket2Win();
//===============================================
#endif
//===============================================
#endif
//===============================================
