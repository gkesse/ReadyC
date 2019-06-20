#ifndef _GSocketUnix_
#define _GSocketUnix_
//===============================================
#include "GSocket.h"
#include "GMap.h"
//===============================================
typedef struct _GSocketUnixO GSocketUnixO;
typedef struct _GMapO_GSocketUnix_GCHAR_PTR_GINT_PTR GMapO_GSocketUnix_GCHAR_PTR_GINT_PTR;
typedef struct _GMapO_GSocketUnix_GCHAR_PTR_GSOCKADDR_IN_PTR GMapO_GSocketUnix_GCHAR_PTR_GSOCKADDR_IN_PTR;
//===============================================
struct _GSocketUnixO {
    GSocketO* m_parent;
#if defined(__unix)
    GMapO(GSocketUnix_GCHAR_PTR_GINT_PTR)* m_socketMap;
    GMapO(GSocketUnix_GCHAR_PTR_GSOCKADDR_IN_PTR)* m_addressMap;
#endif
};
//===============================================
GSocketO* GSocketUnix_New();
void GSocketUnix_Delete(GSocketO* obj);
GSocketO* GSocketUnix();
//===============================================
#endif
//===============================================
