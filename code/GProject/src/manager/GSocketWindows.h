#ifndef _GSocketWindows_
#define _GSocketWindows_
//===============================================
#include "GSocket.h"
#include "GMap.h"
//===============================================
typedef struct _GSocketWindowsO GSocketWindowsO;
typedef struct _GMapO_GSocketWindows_GCHAR_PTR_GWSADATA_PTR GMapO_GSocketWindows_GCHAR_PTR_GWSADATA_PTR;
typedef struct _GMapO_GSocketWindows_GCHAR_PTR_GSOCKET_PTR GMapO_GSocketWindows_GCHAR_PTR_GSOCKET_PTR;
typedef struct _GMapO_GSocketWindows_GCHAR_PTR_GSOCKADDR_IN_PTR GMapO_GSocketWindows_GCHAR_PTR_GSOCKADDR_IN_PTR;
//===============================================
struct _GSocketWindowsO {
    GSocketO* m_parent;
#if defined(__WIN32)
    GMapO(GSocketWindows_GCHAR_PTR_GWSADATA_PTR)* m_dataMap;
    GMapO(GSocketWindows_GCHAR_PTR_GSOCKET_PTR)* m_socketMap;
    GMapO(GSocketWindows_GCHAR_PTR_GSOCKADDR_IN_PTR)* m_addressMap;
#endif
};
//===============================================
GSocketO* GSocketWindows_New();
void GSocketWindows_Delete(GSocketO* obj);
GSocketO* GSocketWindows();
//===============================================
#endif
//===============================================
