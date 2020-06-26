#ifndef _GSocket2Windows_
#define _GSocket2Windows_
//===============================================
#include "GSocket2.h"
#include "GMap.h"
//===============================================
#if defined(_GUSE_SOCKET_ON_)
//===============================================
typedef struct _GSocket2WindowsO GSocket2WindowsO;
typedef struct _GMapO_GSocket2Windows_GCHAR_PTR_GWSADATA_PTR GMapO_GSocket2Windows_GCHAR_PTR_GWSADATA_PTR;
typedef struct _GMapO_GSocket2Windows_GCHAR_PTR_GSOCKET_PTR GMapO_GSocket2Windows_GCHAR_PTR_GSOCKET_PTR;
typedef struct _GMapO_GSocket2Windows_GCHAR_PTR_GSOCKADDR_IN_PTR GMapO_GSocket2Windows_GCHAR_PTR_GSOCKADDR_IN_PTR;
//===============================================
struct _GSocket2WindowsO {
    GSocket2O* m_parent;
#if defined(__WIN32)
    GMapO(GSocket2Windows_GCHAR_PTR_GWSADATA_PTR)* m_dataMap;
    GMapO(GSocket2Windows_GCHAR_PTR_GSOCKET_PTR)* m_socketMap;
    GMapO(GSocket2Windows_GCHAR_PTR_GSOCKADDR_IN_PTR)* m_addressMap;
#endif
};
//===============================================
GSocket2O* GSocket2Windows_New();
void GSocket2Windows_Delete(GSocket2O* obj);
GSocket2O* GSocket2Windows();
//===============================================
#endif
//===============================================
#endif
//===============================================
